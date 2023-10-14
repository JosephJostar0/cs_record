import sys
from pathlib import Path
import re
from constVM import *


class VMTranslator:
    def __init__(self, fpath: Path, savePath: Path = None):
        self.setAll(fpath, savePath)

    def setAll(self, filePath: Path, savePath: Path = None):
        self.filePath = filePath
        if savePath is None:
            if not filePath.exists():
                raise FileNotFoundError(f"File '{filePath}' does not exist.")
            savePath = Path(f'{filePath.parent}/{filePath.stem}.asm')
        self.savePath = savePath
        self.cnt = 0
        self.lines = None
        self.result = []

    def readAndCleanLines(self):
        def cleanLines(content: str) -> list:
            cleanedLines = []
            for line in content.split('\n'):
                cline = re.sub(CUTOFF, '', line.strip())
                if len(cline) == 0:
                    continue
                cleanedLines.append(cline.strip())
            return cleanedLines

        fpath = self.filePath
        if not fpath:
            raise Exception("File path is not ready to read.")
        try:
            with fpath.open('r', encoding=ENCODE) as file:
                self.lines = cleanLines(file.read())
        except UnicodeDecodeError:
            raise f"File '{fpath}' is not a valid text file." from None
        except FileNotFoundError:
            raise f"File '{fpath}' does not exist." from None

    def transeInstruction(self):
        def parseCommand(line: str) -> tuple[str, str, str]:
            parts = line.split(' ')
            if len(parts) != 3:
                raise ValueError(f'{line} is ungrammatical')
            return parts[0], parts[1], parts[2]

        def isInt(index: str) -> bool:
            try:
                int(index)
                return True
            except ValueError:
                return False

        def transPush(line: str) -> list[str]:
            command, segment, index = parseCommand(line)
            if command != 'push' or segment not in PUSH_SEGMENT or not isInt(index):
                raise ValueError(f'{line} is ungrammatical')

            if segment in SEG_CONST:
                result = [f'@{index}', 'D=A']
            elif segment in SEG_BASIC:
                result = [
                    BASIC_ALTER[segment], 'D=M',
                    f'@{index}', 'A=D+A', 'D=M'
                ]
            elif segment in SEG_STATIC:
                result = [f'@{self.filePath.stem}.{index}', 'D=M']
            elif segment in SEG_TEMP:
                if not 0 <= int(index) <= INDEX_MAX:
                    raise f'{line} is ungrammatical: {index} is out of range'
                result = [
                    f'@{TEMP}', 'D=A',
                    f'@{index}', 'A=D+A', 'D=M',
                ]
            elif segment in SEG_POINT:
                if index != '0' and index != '1':
                    raise f'{line} is ungrammatical: i must be 0 or 1'
                current = 'THIS' if index == '0' else 'THAT'
                result = [f'@{current}', 'D=M']
            else:
                raise ValueError(f'{line} is ungrammatical')
            result.extend(PUSH_COMMON)
            return result

        def transPop(line: str) -> list[str]:
            command, segment, index = parseCommand(line)
            if command != 'pop' or segment not in POP_SEGMENT or not isInt(index):
                raise ValueError(f'{line} is ungrammatical')

            if segment in SEG_BASIC:
                result = [
                    BASIC_ALTER[segment], 'D=M', f'@{index}',
                    'D=D+A', ADDR, 'M=D',  # R15=addr
                    '@SP', 'AM=M-1', 'D=M',  # D=M[--sp]
                    ADDR, 'A=M', 'M=D',  # M[R15]=D
                ]
            elif segment in SEG_STATIC:
                result = POP_COMMON + [f'@{self.filePath.stem}.{index}', 'M=D']
            elif segment in SEG_TEMP:
                if not 0 <= int(index) <= INDEX_MAX:
                    raise f'{line} is ungrammatical: {index} is out of range'
                result = [
                    f'@{TEMP}', 'D=A', f'@{index}', 'D=D+A',  # D=addr
                    ADDR, 'M=D',  # R15=addr
                    '@SP', 'AM=M-1', 'D=M',  # D=M[--sp]
                    ADDR, 'A=M', 'M=D',  # M[R15]=D
                ]
            elif segment in SEG_POINT:
                if index != '0' and index != '1':
                    raise f'{line} is ungrammatical: i must be 0 or 1'
                current = 'THIS' if index == '0' else 'THAT'
                result = POP_COMMON + [f'@{current}', 'M=D']
            else:
                raise ValueError(f'{line} is ungrammatical')
            return result

        def transAriLogi(line: str) -> list[str]:
            result = []
            if line in ARI1.keys():
                result.extend(ARI1[line])
            elif line in ARI2.keys():
                result.extend(ARI2[line])
            elif line in LOGI.keys():
                symbol = f'_{line}_{self.cnt}'
                self.cnt += 1
                result.extend(LOGI_PRE)
                result.append('@'+symbol)
                result.extend(LOGI[line])
                result.extend(LOGI_POST)
                result.append(f'({symbol})')
            else:
                raise ValueError(f'{line} is ungrammatical')
            return result

        def transLabel(line: str) -> list[str]:
            reMatch = re.match(IS_LABEL, line)
            if not reMatch:
                raise f'{line} is ungrammatical'
            return [f'({reMatch.group(2)})']

        def transGoto(line: str) -> list[str]:
            reMatch = re.match(IS_GOTO, line)
            if not reMatch:
                raise '{line} is ungrammatical'
            gotoType, label = reMatch.groups()
            if gotoType == 'goto':
                return [f'@{label}', 'D;JMP']
            else:
                return IFGOTO_INS + [f'@{label}', 'D;JNE']

        def isGoto(line: str) -> bool:
            reMatch = re.match(IS_GOTO, line)
            return True if reMatch else False

        if not self.lines:
            raise Exception("Lines is not ready to translate.")
        for line in self.lines:
            line: str
            if line.startswith('push'):
                self.result.extend(transPush(line))
            elif line.startswith('pop'):
                self.result.extend(transPop(line))
            elif line.startswith('label'):
                self.result.extend(transLabel(line))
            elif isGoto(line):
                self.result.extend(transGoto(line))
            else:
                self.result.extend(transAriLogi(line))

    def saveResult(self):
        if not self.savePath:
            raise Exception("Save path is not ready to save.")
        if not self.result:
            raise Exception("Result is not ready to save.")
        try:
            with open(self.savePath, 'w', encoding=ENCODE) as file:
                for item in self.result:
                    file.write(item+'\n')
        except FileNotFoundError:
            raise f"File '{self.savePath}' does not exist." from None

    def runVMTranslator(self):
        self.readAndCleanLines()
        self.transeInstruction()
        self.saveResult()

    @staticmethod
    def getVMTranslator():
        def getPath() -> tuple[Path, Path]:
            arguments = sys.argv

            if len(arguments) < 2:
                raise IndexError("Please provide target file_path argument")
            if len(arguments) > 3:
                raise Exception("Too Many arguments")

            fpath = Path(arguments[1])
            if not fpath.exists():
                raise FileNotFoundError(f"File '{fpath}' does not exist.")
            savePath = Path(f'{fpath.parent}/{fpath.stem}.asm')
            if len(arguments) == 3:
                savePath = Path(arguments[2])
            return fpath, savePath

        fpath, savePath = getPath()
        return VMTranslator(fpath, savePath)


if __name__ == '__main__':
    VMTranslator.getVMTranslator().runVMTranslator()

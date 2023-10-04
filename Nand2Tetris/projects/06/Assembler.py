import sys
from pathlib import Path
import re
from const import *


class Assembler:
    def __init__(self, filePath: Path, savePath: Path):
        self.setPaths(filePath, savePath)

    def setPaths(self, filePath: Path, savePath: Path):
        self.labelDict = {}
        self.memCnt = MEM_CNT
        self.filePath = filePath
        self.savePath = savePath
        self.lines = None
        self.result = None

    def runAssembler(self):
        self.readAndCleanLines()
        self.transInstruction()
        self.saveResult()

    def readAndCleanLines(self):
        def cleanLines(content: str) -> list:
            cleanedLines = []
            cnt = 0
            for line in content.split('\n'):
                cline = re.sub(r'//.*', '', line.strip())
                if len(cline) == 0:
                    continue
                if not cline.startswith('('):
                    cleanedLines.append(cline.replace(" ", ""))
                    cnt += 1
                elif cline.startswith('(') and cline.endswith(')'):
                    label = re.findall(r'\((.*?)\)', cline)
                    if len(label) != 1:
                        raise ValueError(f'{line} is ungrammatical')
                    if cnt > MAX_INT:
                        raise ValueError(
                            f'program is too long to run in memery')
                    self.labelDict[label[0]] = cnt
                else:
                    raise ValueError(f'{line} is ungrammatical')
            return cleanedLines

        fpath = self.filePath
        if not fpath:
            raise Exception("File path is not ready to read.")
        try:
            with fpath.open('r', encoding='utf-8') as file:
                self.lines = cleanLines(file.read())
        except UnicodeDecodeError:
            raise f"File '{fpath}' is not a valid text file." from None
        except FileNotFoundError:
            raise f"File '{fpath}' does not exist." from None

    def transInstruction(self):
        def aInstruction(line: str) -> str:
            def isInt(line: str) -> bool:
                try:
                    int(line)
                    return True
                except ValueError:
                    return False

            _line = line.replace(A_TAG, '')
            if not isInt(_line):
                if _line in PRE_DEFINED_SYMBOLS.keys():
                    _line = PRE_DEFINED_SYMBOLS[_line]
                elif _line in self.labelDict.keys():
                    _line = self.labelDict[_line]
                else:
                    self.labelDict[_line] = str(self.memCnt)
                    _line = self.memCnt
                    self.memCnt += 1
            num = int(_line)
            if MIN_INT <= num <= MAX_INT:
                return A_START + bin(num)[2:].zfill(15)
            else:
                raise ValueError(
                    f"{line} can't be represented with 15-bit two's complement"
                )

        def cInstruction(line: str) -> str:
            def strSplit(line: str):
                if ';' in line and '=' in line:
                    matchStr = re.match(PATTERN_BOTH, line)
                    dest, comp, jump = matchStr.groups()
                elif ';' in line:
                    matchStr = re.match(PATTERN_SEM, line)
                    comp, jump = matchStr.groups()
                    dest = ""
                elif '=' in line:
                    matchStr = re.match(PATTERN_EQ, line)
                    dest, comp = matchStr.groups()
                    jump = ""
                else:
                    comp = line
                    dest = jump = ""
                return dest, comp, jump

            dest, comp, jump = strSplit(line)
            try:
                dest = DEST_DIC[dest]
                comp = COMP_DIC[comp]
                jump = JUMP_DIC[jump]
            except KeyError:
                raise ValueError(f'{line} is ungrammatical')
            return C_START + comp + dest + jump

        if not self.lines:
            raise Exception("Cleaned lines are not ready to transe.")
        result = []
        for line in self.lines:
            line: str
            if line.startswith('@'):
                result.append(aInstruction(line))
            else:
                result.append(cInstruction(line))
        self.result = result

    def saveResult(self):
        if not self.savePath:
            raise Exception("Save path is not ready to save.")
        if not self.result:
            raise Exception("Result is not ready to save.")
        try:
            with open(self.savePath, 'w', encoding='utf-8') as file:
                for item in self.result:
                    file.write(item+'\n')
        except FileNotFoundError:
            raise f"File '{self.savePath}' does not exist." from None

    @staticmethod
    def getAssembler():
        def getPath() -> tuple[Path, Path]:
            arguments = sys.argv
            if len(arguments) < 2:
                raise IndexError("Please provide target file_path argument")
            if len(arguments) > 3:
                raise Exception("Too Many arguments")

            fpath = Path(arguments[1])
            if not fpath.exists():
                raise FileNotFoundError(f"File '{fpath}' does not exist.")
            savePath = Path(f'{fpath.parent}/{fpath.stem}.hack')
            if len(arguments) == 3:
                savePath = Path(arguments[2])
            return fpath, savePath

        fpath, savePath = getPath()
        return Assembler(fpath, savePath)


if __name__ == '__main__':
    Assembler.getAssembler().runAssembler()

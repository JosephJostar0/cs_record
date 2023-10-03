import sys
from pathlib import Path
import re
from const import *


class VMTranslator:
    def __init__(self):
        self.fileName = None
        self.filePath = None
        self.savePath = None
        self.lines = None
        self.result = []

    def __init__(self, fpath: Path, savePath: Path):
        self.fileName = fpath.stem
        self.filePath = fpath
        self.savePath = savePath
        self.lines = None
        self.result = []

    def setAll(self, fpath: Path, savePath: Path):
        self.fileName = fpath.stem
        self.filePath = fpath
        self.savePath = savePath
        self.lines = None
        self.result = []

    def readAndCleanLines(self):
        def cleanLines(content: str) -> list:
            cleanedLines = []
            for line in content.split('\n'):
                cline = re.sub(r'//.*', '', line.strip())
                if len(cline) == 0:
                    continue
                cleanedLines.append(cline)
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

        def transPush(line: str):
            command, segment, index = parseCommand(line)
            if command != 'push' or segment not in PUSH_SEGMENT or not isInt(index):
                raise ValueError(f'{line} is ungrammatical')

            if segment in SEGMENT_BASIC:
                # addr=@segment+index; D=*addr; *sp=D; sp++
                self.result.extend(genSegIns(segment, index))  # addr=seg+i
                self.result.extend(SET_MADDR2D)  # D=*addr
                self.result.extend(SET_D2STACK)  # D=*sp
                self.result.extend(PUSH_INSTRUCTIONS)  # sp++
            elif segment in SEGMENT_CONSTANT:
                # D=index; *sp=D; sp++
                self.result.extend([f'@{index}', 'D=A'])  # D=index
                self.result.extend(SET_D2STACK)  # *sp=D
                self.result.extend(PUSH_INSTRUCTIONS)  # sp++
            elif segment in SEGMENT_STATIC:
                pass

        def transPop(line: str):
            command, segment, index = parseCommand(line)
            if command != 'pop' or segment not in POP_SEGMENT or not isInt(index):
                raise ValueError(f'{line} is ungrammatical')

            if segment in SEGMENT_BASIC:
                # sp--; addr=@segment+index; D=*sp; *addr=D
                self.result.extend(POP_INSTRUCTIONS)  # sp--
                self.result.extend(genSegIns(segment, index))  # addr=seg+i
                self.result.extend(SET_STACK2D)  # D=*sp
                self.result.extend(SET_D2MADDR)  # *addr=D
            elif segment in SEGMENT_STATIC:
                pass

        def parseOthers(line: str):
            if line not in ARI_LOGI_COMMANDS:
                raise ValueError(f'{line} is ungrammatical')

        if not self.lines:
            raise Exception("Lines is not ready to translate.")
        for line in self.lines:
            line: str
            if line.startswith('push'):
                transPush(line)
            elif line.startswith('pop'):
                transPop(line)
            else:
                parseOthers(line)

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
            savePath = Path(f'{fpath.parent}/{fpath.stem}.hack')
            if len(arguments) == 3:
                savePath = Path(arguments[2])
            return fpath, savePath

        fpath, savePath = getPath()
        return VMTranslator(fpath, savePath)


if __name__ == '__main__':
    VMTranslator.getVMTranslator().runVMTranslator()

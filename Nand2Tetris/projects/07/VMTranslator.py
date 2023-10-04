import sys
from pathlib import Path
import re
from const import *


class VMTranslator:
    def __init__(self, fpath: Path, savePath: Path):
        self.setAll(fpath, savePath)

    def setAll(self, fpath: Path, savePath: Path):
        self.fileName = fpath.stem
        self.filePath = fpath
        self.savePath = savePath
        self.cnt = 0
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

        def transPush(line: str) -> list[str]:
            command, segment, index = parseCommand(line)
            if command != 'push' or segment not in PUSH_SEGMENT or not isInt(index):
                raise ValueError(f'{line} is ungrammatical')

            result = []
            return result

        def transPop(line: str) -> list[str]:
            command, segment, index = parseCommand(line)
            if command != 'pop' or segment not in POP_SEGMENT or not isInt(index):
                raise ValueError(f'{line} is ungrammatical')

            result = []
            return result

        def parseOthers(line: str) -> list[str]:
            if line not in ARI_LOGI_COMMANDS:
                raise ValueError(f'{line} is ungrammatical')

            result = []
            return result

        if not self.lines:
            raise Exception("Lines is not ready to translate.")
        for line in self.lines:
            line: str
            if line.startswith('push'):
                self.result.extend(transPush(line))
            elif line.startswith('pop'):
                self.result.extend(transPop(line))
            else:
                self.result.extend(parseOthers(line))

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

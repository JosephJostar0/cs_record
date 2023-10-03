import sys
from pathlib import Path
import re


class VMTranslator:
    def __init__(self):
        self.filePath = None
        self.savePath = None

    def __init__(self, fpath: Path, savePath: Path):
        self.filePath = fpath
        self.savePath = savePath

    def clear(self):
        self.filePath = None
        self.savePath = None

    def setAll(self, fpath: Path, savePath: Path):
        self.filePath = fpath
        self.savePath = savePath

    def setCleanedLines(self):
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
        if not fpath.exists():
            raise FileNotFoundError(f"File '{fpath}' does not exist.")

        try:
            with fpath.open('r', encoding='utf-8') as file:
                self.lines = cleanLines(file.read())
        except UnicodeDecodeError:
            raise f"File '{fpath}' is not a valid text file." from None

    def runVMTranslator(self):
        self.setCleanedLines()

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

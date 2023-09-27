import sys
from pathlib import Path
import re


def getPath():
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


def getFileCleanedLines(fpath: Path) -> list:
    if not fpath.exists():
        raise FileNotFoundError(f"File '{fpath}' does not exist.")

    def cleanLines(content: str) -> list:
        cleanedLines = []
        for line in content.split('\n'):
            line: str
            cline = line.strip()
            if cline and not cline.startswith("//"):
                cleanedLines.append(cline)
        return cleanedLines

    try:
        with fpath.open('r', encoding='utf-8') as file:
            content = file.read()
    except UnicodeDecodeError:
        print(f"File '{fpath}' is not a valid text file.")
        raise Exception(f"File '{fpath}' is not a valid text file.") from None

    return cleanLines(re.sub(r'/\*.*?\*/', '', content))


def getClearLines() -> list:
    pass


def aInstruction():
    pass


def cInstruction():
    pass


if __name__ == '__main__':
    filePath, savePath = getPath()
    lines = getFileCleanedLines(filePath)
    print(lines)

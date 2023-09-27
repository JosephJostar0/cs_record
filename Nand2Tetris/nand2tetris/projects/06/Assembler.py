import sys
from pathlib import Path


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


def getFileCleanedLines(fpath: Path) -> list[str]:
    if not fpath.exists():
        raise FileNotFoundError(f"File '{fpath}' does not exist.")

    def cleanLines(content: str) -> list:
        cleanedLines = []
        for line in content.split('\n'):
            cline = line.strip()
            if cline and not cline.startswith("//"):
                cleanedLines.append(cline.replace(" ", ""))
        return cleanedLines

    try:
        with fpath.open('r', encoding='utf-8') as file:
            return cleanLines(file.read())
    except UnicodeDecodeError:
        raise Exception(f"File '{fpath}' is not a valid text file.") from None


def aInstruction(line: str) -> str:
    pass


def cInstruction(line: str) -> str:
    pass


def transeInstruction(lines: list) -> list:
    result = []
    return result


def saveResult(savePath: Path, result: list[str]):
    with open(savePath, 'w', encoding='utf-8') as file:
        for item in result:
            file.write(item+'\n')


if __name__ == '__main__':
    filePath, savePath = getPath()
    lines = getFileCleanedLines(filePath)
    result = transeInstruction(lines)
    saveResult(savePath, result)

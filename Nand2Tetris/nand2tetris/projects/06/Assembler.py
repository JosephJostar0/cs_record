import sys
from pathlib import Path
import re

from const import *


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
    def isInt(line: str) -> bool:
        try:
            int(line)
            return True
        except ValueError:
            return False

    temp = line.replace(A_TAG, '')
    if isInt(temp):
        num = int(temp)
        if MIN_INT <= num <= MAX_INT:
            if num < 0:
                num += 2**A_INT_BIT
            return A_START + bin(num)[2:].zfill(15)
        else:
            raise ValueError(
                f"{line} can't be represented with 15-bit two's complement"
            )
    else:
        return ''


def cInstruction(line: str) -> str:
    def strSplit(line: str):
        matchStr = re.match(PATTERN, line)
        if matchStr:
            part1, part2, part3 = matchStr.groups()
            return part1, part2 if part2 else "", part3 if part3 else ""
        else:
            return line, "", ""

    dest, comp, jump = strSplit(line)
    try:
        dest = DEST_DIC[dest]
        comp = COMP_DIC[comp]
        jump = JUMP_DIC[jump]
    except KeyError:
        raise ValueError(f'{line} is ungrammatical') from None
    return C_START + comp + dest + jump


def transeInstruction(lines: list[str]) -> list:
    result = []
    for line in lines:
        if line.startswith('@'):
            result.append(aInstruction(line))
        else:
            result.append(cInstruction(line))
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

import sys
from pathlib import Path
import re

from const import *

labelDict = {}
memCnt = 16


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
        cnt = 0
        for line in content.split('\n'):
            cline = line.strip()
            if cline and not cline.startswith("//"):
                if not cline.startswith('('):
                    cline = re.sub(r'//.*', '', cline)
                    cleanedLines.append(cline.replace(" ", ""))
                    cnt += 1
                elif cline.startswith('(') and cline.endswith(')'):
                    label = re.findall(r'\((.*?)\)', cline)
                    if len(label) != 1:
                        raise ValueError(f'{line} is ungrammatical')
                    if cnt > MAX_INT:
                        raise ValueError(
                            f'program is too long to run in memery')
                    labelDict[label[0]] = cnt
                else:
                    raise ValueError(f'{line} is ungrammatical')
        return cleanedLines

    try:
        with fpath.open('r', encoding='utf-8') as file:
            return cleanLines(file.read())
    except UnicodeDecodeError:
        raise Exception(f"File '{fpath}' is not a valid text file.") from None


def aInstruction(line: str) -> str:
    global memCnt, labelDict

    def isInt(line: str) -> bool:
        try:
            int(line)
            return True
        except ValueError:
            return False

    temp = line.replace(A_TAG, '')

    if not isInt(temp):
        if temp in PRE_DEFINED_SYMBOLS.keys():
            temp = PRE_DEFINED_SYMBOLS[temp]
        elif temp in labelDict.keys():
            temp = labelDict[temp]
        else:
            labelDict[temp] = str(memCnt)
            temp = memCnt
            memCnt += 1

    num = int(temp)
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
        print(dest)
        print(comp)
        print(jump)
        raise ValueError(f'{line} is ungrammatical')
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

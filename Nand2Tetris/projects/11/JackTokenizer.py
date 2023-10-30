from pathlib import Path
from queue import Queue
import re

from CompilerTools import *


class JackTokenizer:
    def __init__(self, inPath: Path) -> None:
        self.setAll(inPath)

    def setAll(self, inPath: Path, outPath: Path = None):
        if inPath is None or not inPath.exists():
            raise FileExistsError(f'{inPath} is not a valid file/dir')
        self.inPath = inPath
        if outPath is None:
            if inPath.is_file():
                outPath = Path(f'{inPath.parent}/{inPath.stem}T_.xml')
            elif inPath.is_dir():
                raise FileExistsError(f"{inPath} isn't a file")
            else:
                raise FileNotFoundError(f"File/Dir '{inPath}' does not exist.")
        self.outPath = outPath
        self.lines = Queue()
        self.results = []
        self.current = ''

    def hasMoreTokens(self) -> bool:
        '''
        Are there more tokens in the input?
        '''
        return not self.lines.empty()

    def advance(self):
        '''
        Gets the next token from the input, and makes it the current token.
        This method should be called only if hasMoreTokens is true.
        Initially there is no current token.
        '''
        self.current = self.lines.get()

    def tokenType(self):
        '''
        Returns the type of the current token, as a constant.
        '''
        token = self.current

        def isKey():
            return token in KEYWORD_LIST

        def isSymbol():
            return token in SYMBOL_DICT.keys()

        def isIdentifier():
            return bool(re.match(MATCH_IDENTIFIER, token))

        def isIntConst():
            def isInt():
                try:
                    return INT_MIN <= int(token) <= INT_MAX
                except:
                    return False
            return isInt()

        def isString():
            return bool(re.match(MATCH_STRING, token))

        if isKey():
            return KEYWORD
        elif isSymbol():
            return SYMBOL
        elif isIdentifier():
            return IDENTIFIER
        elif isIntConst():
            return INTEGER
        elif isString():
            return STRING
        else:
            raise ValueError(f'{token} is not valid')

    def readAndGetToken(self):
        def getToken(line: str) -> list:
            def handleNoStr(content: str):
                result = []
                fragments = re.split(MATCH_TOKEN, content)
                fragments = [it for it in fragments if it != '']
                for item in fragments:
                    item = item.strip()
                    if item.startswith('"') and item.endswith('"'):
                        result.append(item)
                    else:
                        for it in item.split(' '):
                            it = it.strip()
                            if len(it) > 0:
                                result.append(it)
                return result

            result = []
            strCut = re.match(MATCH_TOKEN_STR, line)
            if strCut is not None:
                preStr, string, postStr = strCut.groups()
                result += handleNoStr(preStr)
                if len(string) > 0:
                    result.append(string)
                result += handleNoStr(postStr)
            else:
                return handleNoStr(line)
            return result

        def cleanLines(content: str):
            content = re.sub(MATCH_COMMENT0, '', content).strip()
            content = re.sub(MATCH_COMMENT1, '', content, flags=re.DOTALL)
            for line in content.strip().split('\n'):
                if len(line) > 0:
                    for item in getToken(line):
                        self.lines.put(item)

        inPath = self.inPath
        if not inPath:
            raise Exception("File path is not ready to read.")
        if inPath.is_file():
            with inPath.open('r', encoding=ENCODE) as file:
                cleanLines(file.read())
        elif inPath.is_dir():
            raise TypeError(f"class VMTranslator_ does not accept a dir.")

    def saveResult(self):
        with open(self.outPath, 'w', encoding=ENCODE) as file:
            file.write('<tokens>\n')
            for token in self.results:
                file.write(str(token) + '\n')
            file.write('</tokens>\n')

    def tokenize(self):
        while self.hasMoreTokens():
            self.advance()
            tType = self.tokenType()
            token = self.current.replace('\"', '')
            self.results.append(Token(token, tType))

    def runTokenizer(self, isSave: bool = False):
        self.readAndGetToken()
        self.tokenize()
        if isSave:
            self.saveResult()

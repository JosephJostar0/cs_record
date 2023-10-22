import sys
from pathlib import Path
import re
from queue import Queue
import xml.etree.ElementTree as ET

from ConstAnalyzer import *


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
        self.results = ['<tokens>']
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

        def isKeyWord():
            return token in KEYWORD

        def isSymbol():
            return token in SYMBOL.keys()

        def isIdentifier():
            return bool(re.match(MATCH_IDENTIFYER, token))

        def isInt():
            def isInt():
                try:
                    int(token)
                    return True
                except:
                    return False
            return isInt() and INT_MIN <= int(token) <= INT_MAX

        def isString():
            return bool(re.match(MATCH_STRING, token))

        if isKeyWord():
            return 'keyword'
        elif isSymbol():
            return 'symbol'
        elif isIdentifier():
            return 'identifier'
        elif isInt():
            return 'integerConstant'
        elif isString():
            return 'stringConstant'
        else:
            raise ValueError(f'{token} is not valid')

    def keyWord(self):
        '''
        Returns the keyword which is the current token, as a constant.
        This method should be called only if the tokenType is KEYWORD.
        '''
        pass

    def symbol(self) -> str:
        '''
        Returns the character which is the current token.
        Should be called only if tokenType is SYMBOL.
        '''
        pass

    def identifier(self) -> str:
        '''
        Returns the identifier which is the current token.
        Should be called only if tokenType is IDENTIFIER.
        '''
        pass

    def intVal(self) -> int:
        '''
        Returns the integer value of the current token.
        Should be called only if tokenType is INT_CONST
        '''
        pass

    def stringVal(self) -> str:
        '''
        Returns the string value of the current token, without the two enclosing double quotes.
        Should be called only if tokenType is STRING_CONST
        '''
        pass

    def readAndGetToken(self):
        def getToken(content: str) -> list:
            fragments = re.split(MATCH_TOKEN, content)
            fragments = [it for it in fragments if it != '']
            result = []
            for item in fragments:
                item = item.strip()
                if item.startswith('"') and item.endswith('"'):
                    result.append(item)
                else:
                    for it in item.split(' '):
                        it = it.strip()
                        if len(it) > 0:
                            result.append(it)

            # 打开文件以追加写入，如果文件不存在则创建它
            with open('my_file.txt', 'a') as file:
                for it in result:
                    file.write(it+'| ')
                file.write('\n\n------------------------\n\n')

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
        self.results.append('</tokens>')
        with open(self.outPath, 'w', encoding=ENCODE) as file:
            for line in self.results:
                file.write(line + '\n')

    def tokenize(self):
        while self.hasMoreTokens():
            self.advance()
            tType = self.tokenType()
            token = self.current.replace('\"', '')
            if token in SYMBOL.keys():
                token = SYMBOL[token]
            result = f'<{tType}> {token} </{tType}>'
            self.results.append(result)

    def runTokenizer(self):
        self.readAndGetToken()
        self.tokenize()
        self.saveResult()


class CompilationEngine:
    def __init__(self, inPath: Path):
        pass

    def compileLet():
        '''
        Compiles a let statement.
        '''

    def compileIf():
        '''
        Compiles an if statement, possibly with a trailing else clause.
        '''

    def compileWhile():
        '''
        Compiles a while statement.
        '''

    def compileDo():
        '''
        Compiles a do statement.
        '''

    def compileReturn():
        '''
        Compiles a return statement.
        '''

    def compileExpression():
        '''
        Compiles an expression.
        '''

    def compileTerm():
        '''
        Compiles a term.
        If the current token is an identifier, the routine must distinguish between a variable, an array entry, or a subroutine call.
        A single look-ahead token, which may be one of "[", "(", or ".", suffices to distinguish between the possibilities.
        Any other token is not part of this term and should not be advanced over.
        '''

    def compileExpressionList():
        '''
        Compiles a (possibly empty) comma-separated list of expressions.
        '''


class JackAnalyzer:
    def __init__(self, inPath: Path, outPath: Path = None):
        self.setAll(inPath, outPath)

    def setAll(self, inPath: Path, outPath: Path = None):
        if inPath is None or not inPath.exists():
            raise FileExistsError(f'{inPath} is not a valid file/dir')
        self.inPath = inPath
        if outPath is None:
            if inPath.is_file():
                outPath = Path(f'{inPath.parent}/{inPath.stem}.xml')
            elif inPath.is_dir():
                outPath = inPath / f'{inPath.name}.xml'
            else:
                raise FileNotFoundError(f"File/Dir '{inPath}' does not exist.")
        self.outPath = outPath

    def runJackAnalyzer(self):
        if self.inPath.is_file():
            JackTokenizer(self.inPath).runTokenizer()
        elif self.inPath.is_dir():
            for item in self.inPath.iterdir():
                if item.is_file() and item.suffix == '.jack':
                    JackTokenizer(item).runTokenizer()
        else:
            raise ValueError(f'{self.inPath} is invalid.')

    @staticmethod
    def getJackAnalyzer():
        def getPaths() -> tuple[Path, Path]:
            arguments = sys.argv

            if len(arguments) < 2:
                raise IndexError("Please provide target file_path argument")
            if len(arguments) > 2:
                raise Exception("Too Many arguments")

            inPath = Path(arguments[1])
            if not inPath.exists():
                raise FileNotFoundError(f"File/Dir '{inPath}' does not exist.")
            return inPath

        return JackAnalyzer(getPaths())


if __name__ == '__main__':
    JackAnalyzer.getJackAnalyzer().runJackAnalyzer()

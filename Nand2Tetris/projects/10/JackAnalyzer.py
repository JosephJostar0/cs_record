import sys
from pathlib import Path


class JackTokenizer:
    def __init__(self) -> None:
        pass

    def hasMoreTokens(self) -> bool:
        '''
        Are there more tokens in the input?
        '''
        pass

    def advance(self):
        '''
        Gets the next token from the input, and makes it the current token.
        This method should be called only if hasMoreTokens is true.
        Initially there is no current token.
        '''
        pass

    def tokenType(self):
        '''
        Returns the type of the current token, as a constant.
        '''
        pass

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

    @staticmethod
    def getJackTokenizer():
        '''
        Opens the input .jack file and gets ready to tokenize it.
        '''
        pass


class CompilationEngine:
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

    @staticmethod
    def getJackAnalyzer():
        def getPaths() -> tuple[Path, Path]:
            arguments = sys.argv

            if len(arguments) < 2:
                raise IndexError("Please provide target file_path argument")
            if len(arguments) > 3:
                raise Exception("Too Many arguments")

            inPath = Path(arguments[1])
            if not inPath.exists():
                raise FileNotFoundError(f"File/Dir '{inPath}' does not exist.")
            if inPath.is_file():
                outPath = Path(f'{inPath.parent}/{inPath.stem}.asm')
                if len(arguments) == 3:
                    outPath = Path(arguments[2])
            elif inPath.is_dir():
                outPath = inPath / f'{inPath.name}.asm'
            else:
                raise FileExistsError(f"File/Dir '{inPath}' does not exist.")
            return inPath, outPath

        inPath, outPath = getPaths()
        return JackAnalyzer(inPath, outPath)


if __name__ == '__main__':
    JackAnalyzer.getJackAnalyzer()

import sys
from pathlib import Path
import re
from queue import Queue
import threading
from time import sleep

from ConstAnalyzer import *


class Token:
    def __init__(self, content: str, tType: str):
        self.content = content
        self.tType = tType

    def __str__(self) -> str:
        token = self.content if self.tType != SYMBOL else SYMBOL_DICT[self.content]
        return f'<{self.tType}> {token} </{self.tType}>'


class WriteElement:
    def __init__(self, content, level: int):
        self.content = content
        self.level = level

    def __str__(self) -> str:
        return '  ' * self.level + str(self.content)


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

        def isKeyWord():
            return token in KEYWORD_LIST

        def isSymbol():
            return token in SYMBOL_DICT.keys()

        def isIdentifier():
            return bool(re.match(MATCH_IDENTIFIER, token))

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
            return KEYWORD
        elif isSymbol():
            return SYMBOL
        elif isIdentifier():
            return IDENTIFIER
        elif isInt():
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

    def runTokenizer(self):
        self.readAndGetToken()
        self.tokenize()
        self.saveResult()


class CompilationEngine:
    def __init__(self, inPath: Path, tokenList: list[Token] = []):
        self.setAll(inPath, tokenList)

    def setAll(self, inPath: Path, tokenList: list[Token] = []):
        self.inPath = inPath
        self.tokenList = tokenList
        self.total = len(tokenList)
        self.results = Queue()
        self.end = False
        if inPath.is_file():
            self.outPath = Path(f'{inPath.parent}/{inPath.stem}_.xml')
        elif inPath.is_dir():
            raise FileExistsError(f"{inPath} isn't a file")
        else:
            raise FileNotFoundError(f"File/Dir '{inPath}' does not exist.")

    def writeResult(self):
        with open(self.outPath, 'w') as file:
            pass  # clear file
        while not (self.end and self.results.empty()):
            element: WriteElement = self.results.get()
            with open(self.outPath, 'a') as file:
                file.write(str(element) + '\n')

    def compileLet(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a let statement.
        '''

    def compileIf(self, head: int, tail: int, level: int = 0):
        '''
        Compiles an if statement, possibly with a trailing else clause.
        '''

    def compileWhile(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a while statement.
        '''

    def compileDo(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a do statement.
        '''

    def compileReturn(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a return statement.
        '''

    def compileExpression(self, head: int, tail: int, level: int = 0):
        '''
        Compiles an expression.
        '''

    def compileTerm(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a term.
        If the current token is an identifier, the routine must distinguish between a variable, an array entry, or a subroutine call.
        A single look-ahead token, which may be one of "[", "(", or ".", suffices to distinguish between the possibilities.
        Any other token is not part of this term and should not be advanced over.
        '''

    def compileExpressionList(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a (possibly empty) comma-separated list of expressions.
        '''

    def compilesStatements(self, head: int, tail: int, level: int = 0):  # TODO
        '''
        Compiles a sequence of statements.
        Does not handle the enclosing "{}".
        '''

    def compileVarDec(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a var declaration.
        '''
        self.results.put(WriteElement('<varDec>', level))

        if head != tail:
            if tail-head < 4:
                raise ValueError('varDec is too short.')
            varKWD = self.tokenList[head]
            varType = self.tokenList[head + 1]
            varSemicolon = self.tokenList[tail - 1]
            if varKWD.content != 'var' or varKWD.tType != KEYWORD:
                raise ValueError(f'{varKWD} must be "var".')
            if not isType(varType):
                raise ValueError(f'{varType} must be TYPE.')
            if not isSemicolon(varSemicolon):
                raise ValueError(f'{varSemicolon} must be ";".')

            self.results.put(WriteElement(varKWD, level + 1))
            self.results.put(WriteElement(varType, level + 1))
            for offset in range(0, tail - head - 3):
                current = self.tokenList[head + 2 + offset]
                if offset % 2 == 0 and current.tType != IDENTIFIER:
                    raise ValueError(f'{current} must be an {IDENTIFIER}.')
                if offset % 2 == 1 and not isComma(current):
                    raise ValueError(f'{current} must be a ",".')
                self.results.put(WriteElement(current, level + 1))
            self.results.put(WriteElement(varSemicolon, level + 1))
        self.results.put(WriteElement('</varDec>', level))

    def compileSubroutineBody(self, head: int, tail: int, level):
        '''
        Compiles a subroutine's body.
        '''
        def followedVarDec(head: int, tail: int) -> int:
            offset = 0
            while head + offset < tail:
                current = self.tokenList[head + offset]
                if current.content != 'var' or current.tType != KEYWORD:
                    break
                index = 0
                while head + offset + index < tail:
                    token = self.tokenList[head + offset + index]
                    if isSemicolon(token):
                        self.compileVarDec(
                            head + offset, head + offset + index + 1, level + 1
                        )
                        offset += index + 1
                        break
                    index += 1
                if head + offset + index == tail:
                    raise Exception(f'missed ";"')
            return head + offset

        openBrace = self.tokenList[head]
        closeBrace = self.tokenList[tail - 1]
        if not isOpenBrace(openBrace) or not isCloseBrace(closeBrace):
            raise ValueError(
                f'{openBrace} and {closeBrace} must be'+' "{ and }"'
            )

        self.results.put(WriteElement('<subroutineBody>', level))
        self.results.put(WriteElement(openBrace, level + 1))
        nextId = followedVarDec(head + 1, tail - 1)
        self.compilesStatements(nextId, tail - 1, level + 1)
        self.results.put(WriteElement(closeBrace, level + 1))
        self.results.put(WriteElement('</subroutineBody>', level))

    def compileParameterList(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a (possibly empty) parameter list.
        Does not handle the enclosing "()".
        '''
        self.results.put(WriteElement('<parameterList>', level))
        if head != tail:
            if tail - head < 2:
                raise ValueError('parameter is invalid.')
            offset = 0
            while head + offset < tail:
                current = self.tokenList[head + offset]
                if offset % 3 == 0 and not isType(current):
                    raise ValueError(
                        f'{current} is invalid. It should be a TYPE.')
                if offset % 3 == 1 and not current.tType == IDENTIFIER:
                    raise ValueError(
                        f'{current} is invalid. It should be an "{IDENTIFIER}".'
                    )
                if offset % 2 == 2 and not isComma(current):
                    raise ValueError(
                        f'{current} is invalid. It should be a ",".'
                    )
                self.results.put(WriteElement(current, level + 1))
                offset += 1
        self.results.put(WriteElement('</parameterList>', level))

    def compileSubroutineDec(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a complete method, function, or constructor.
        '''
        def followedParamList(head: int, tail: int) -> int:
            offset = 0
            while head + offset < tail:
                current = self.tokenList[head + offset]
                if isCloseParenthesis(current):
                    break
                offset += 1
            return head + offset

        subKWD = self.tokenList[head]
        subType = self.tokenList[head + 1]
        subName = self.tokenList[head + 2]
        openParenthesis = self.tokenList[head + 3]
        nextId = followedParamList(head + 4, tail)
        closeParenthesis = self.tokenList[nextId]
        if not (isType(subType) or (subType.content == 'void' and subType.tType == KEYWORD)):
            raise ValueError(
                f'{subType} is invalid. It should be a TYPE/"void".'
            )
        if not subName.tType == IDENTIFIER:
            raise ValueError(
                f'{subName} is invalid. It should be an {IDENTIFIER}.'
            )
        if not isOpenParenthesis(openParenthesis):
            raise ValueError(
                f'{openParenthesis} is invalid. It should be a "(".'
            )
        if not isCloseParenthesis(closeParenthesis):
            raise ValueError(
                f'{closeParenthesis} is invalid. It should be a "(".'
            )

        self.results.put(WriteElement('<subroutineDec>', level))
        self.results.put(WriteElement(subKWD, level + 1))
        self.results.put(WriteElement(subType, level + 1))
        self.results.put(WriteElement(subName, level + 1))
        self.results.put(WriteElement(openParenthesis, level + 1))
        self.compileParameterList(head + 4, nextId, level + 1)
        self.results.put(WriteElement(closeParenthesis, level + 1))
        self.compileSubroutineBody(nextId + 1, tail, level + 1)
        self.results.put(WriteElement('</subroutineDec>', level))

    def compileClassVarDec(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a static variable declaration, or a field declaration.
        '''
        def getVarNames(head: int, tail: int) -> list[Token]:
            cnt = 0
            result = []
            while head + cnt < tail:
                current = self.tokenList[head + cnt]
                if cnt % 2 == 0 and current.tType != IDENTIFIER:
                    raise ValueError(
                        f"{current} is invalid. It should be an {IDENTIFIER}."
                    )
                elif cnt % 2 == 1 and not isComma(current):
                    raise ValueError(
                        f"{current} is invalid. It should be a ','."
                    )
                result.append(current)
                cnt += 1
            return result

        varKWD = self.tokenList[head]
        varType = self.tokenList[head + 1]
        varNames = getVarNames(head + 2, tail - 1)
        semicolon = self.tokenList[tail - 1]
        if not isType(varType):
            raise ValueError(f'{varType} is invalid. It should be a TYPE.')

        self.results.put(WriteElement('<classVarDec>', level))
        self.results.put(WriteElement(varKWD, level + 1))
        self.results.put(WriteElement(varType, level + 1))
        for token in varNames:
            self.results.put(WriteElement(token, level + 1))
        self.results.put(WriteElement(semicolon, level + 1))
        self.results.put(WriteElement('</classVarDec>', level))

    def compileClass(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a complete class
        '''
        def followedClassVar(head: int, tail: int) -> int:
            offset = 0
            while head + offset < tail:
                current = self.tokenList[head + offset]
                if current.content not in ['static', 'field'] or current.tType != KEYWORD:
                    break
                index = 0
                while head + offset + index < tail:
                    token = self.tokenList[head + offset + index]
                    if isSemicolon(token):
                        self.compileClassVarDec(
                            head + offset, head + offset + index + 1, level + 1
                        )
                        offset += index + 1
                        break
                    index += 1
                if head + offset + index == tail:
                    raise Exception(f'missed ";"')
            return head + offset

        def followedSubroutineDec(head: int, tail: int) -> int:
            offset = 0
            while head + offset < tail:
                current = self.tokenList[head + offset]
                if current.content not in ['constructor', 'function', 'method'] or current.tType != KEYWORD:
                    break
                index = 0
                while head + offset + index < tail:
                    token = self.tokenList[head + offset + index]
                    if isCloseBrace(token):
                        self.compileSubroutineDec(
                            head + offset, head + offset + index + 1, level + 1
                        )
                        offset += index + 1
                        break
                    index += 1
                if head + offset + index == tail:
                    raise Exception(f'missed ";"')
            return head + offset

        classKWD = self.tokenList[head]
        className = self.tokenList[head + 1]
        openBrace = self.tokenList[head + 2]
        closeBrace = self.tokenList[tail - 1]
        if classKWD.content != 'class' or classKWD.tType != KEYWORD:
            raise ValueError(f'{classKWD} is invalid')
        if className.tType != IDENTIFIER:
            raise ValueError(f'{className} is invalid')
        if openBrace.content != '{' or openBrace.tType != SYMBOL:
            raise ValueError(f'{openBrace} is invalid')
        if closeBrace.content != '}' or closeBrace.tType != SYMBOL:
            raise ValueError(f'{closeBrace} is invalid')

        self.results.put(WriteElement('<class>', level))
        self.results.put(WriteElement(classKWD, level + 1))
        self.results.put(WriteElement(className, level + 1))
        self.results.put(WriteElement(openBrace, level + 1))
        nextId = followedClassVar(head + 3, tail - 1)
        followedSubroutineDec(nextId, tail - 1)
        self.results.put(WriteElement(closeBrace, level + 1))
        self.results.put(WriteElement('</class>', level))

    def runCompilationEngine(self):
        writer = threading.Thread(target=self.writeResult)
        writer.start()
        try:
            self.compileClass(0, self.total)
        except Exception as e:
            print(e)
        self.end = True
        # writer.join()


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
        def runBoth(inPath: Path):
            tokenizer = JackTokenizer(inPath)
            tokenizer.runTokenizer()
            compilationEngine = CompilationEngine(inPath, tokenizer.results)
            compilationEngine.runCompilationEngine()

        if self.inPath.is_file():
            runBoth(self.inPath)
        elif self.inPath.is_dir():
            for item in self.inPath.iterdir():
                if item.is_file() and item.suffix == '.jack':
                    runBoth(item)
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

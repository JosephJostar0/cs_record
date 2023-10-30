from pathlib import Path
from queue import Queue
import threading

from CompilerTools import *


class WriteElement:
    def __init__(self, content, level: int):
        self.content = content
        self.level = level

    def __str__(self) -> str:
        return '  ' * self.level + str(self.content)


class CompilationEngine:
    def __init__(self, inPath: Path, tokenList: list[Token] = [], isSave: bool = False):
        self.setAll(inPath, tokenList, isSave)

    def setAll(self, inPath: Path, tokenList: list[Token] = [], isSave: bool = False):
        self.inPath = inPath
        self.tokenList = tokenList
        self.total = len(tokenList)
        self.results = Queue()
        self.end = False
        self.isSave = isSave
        if inPath.is_file():
            self.outPath = Path(f'{inPath.parent}/{inPath.stem}_.xml')
        elif inPath.is_dir():
            raise FileExistsError(f"{inPath} isn't a file")
        else:
            raise FileNotFoundError(f"File/Dir '{inPath}' does not exist.")

    def writeResult(self):
        try:
            file = open(self.outPath, 'w')
            while not (self.end and self.results.empty()):
                element: WriteElement = self.results.get()
                file.write(str(element) + '\n')
            file.close()
        except Exception as e:
            print(e)

    def compileTerm(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a term.
        If the current token is an identifier, the routine must distinguish between a variable, an array entry, or a subroutine call.
        A single look-ahead token, which may be one of "[", "(", or ".", suffices to distinguish between the possibilities.
        Any other token is not part of this term and should not be advanced over.
        '''
        self.results.put(WriteElement('<term>', level))

        first = self.tokenList[head]
        if isInteger(first) or isString(first) or isKeywordConst(first):
            self.results.put(WriteElement(first, level + 1))
        elif isUnaryOp(first):
            self.results.put(WriteElement(first, level + 1))
            self.compileTerm(head + 1, tail, level + 1)
        elif isOpenParenthesis(first):
            closeParen = self.tokenList[tail - 1]
            if not isCloseParenthesis(closeParen):
                raise ValueError(f'{closeParen} should be ")".')
            self.results.put(WriteElement(first, level + 1))
            self.compileExpression(head + 1, tail - 1, level + 1)
            self.results.put(WriteElement(closeParen, level + 1))
        elif first.tType == IDENTIFIER:
            if tail - head == 1:
                self.results.put(WriteElement(first, level + 1))
            else:
                whether = self.tokenList[head + 1]
                if isOpenSquare(whether):
                    closeSquare = self.tokenList[tail - 1]
                    if not isCloseSquare(closeSquare):
                        raise ValueError(f'{closeSquare} should be "]".')
                    self.results.put(WriteElement(first, level + 1))
                    self.results.put(WriteElement(whether, level + 1))
                    self.compileExpression(head + 2, tail - 1, level + 1)
                    self.results.put(WriteElement(closeSquare, level + 1))
                elif isPoint(whether):
                    subName = self.tokenList[head + 2]
                    openParen = self.tokenList[head + 3]
                    closeParen = self.tokenList[tail - 1]
                    if not subName.tType == IDENTIFIER:
                        raise ValueError(
                            f'{subName} should be an {IDENTIFIER}.'
                        )
                    if not isOpenParenthesis(openParen):
                        raise ValueError(f'{openParen} should be "(".')
                    if not isCloseParenthesis(closeParen):
                        raise ValueError(f'{openParen} should be ")".')
                    self.results.put(WriteElement(first, level + 1))
                    self.results.put(WriteElement(whether, level + 1))
                    self.results.put(WriteElement(subName, level + 1))
                    self.results.put(WriteElement(openParen, level + 1))
                    self.compileExpressionList(head + 4, tail - 1, level + 1)
                    self.results.put(WriteElement(closeParen, level + 1))
                elif isOpenBrace(whether):
                    closeParen = self.tokenList[tail - 1]
                    if not isCloseParenthesis(closeParen):
                        raise ValueError(f'{openParen} should be ")".')
                    self.results.put(WriteElement(first, level + 1))
                    self.results.put(WriteElement(whether, level + 1))
                    self.compileExpressionList(head + 2, tail - 1, level + 1)
                    self.results.put(WriteElement(closeParen, level + 1))
                else:
                    raise ValueError('invalid term.')
        else:
            raise ValueError('invalid term.')

        self.results.put(WriteElement('</term>', level))

    def compileExpression(self, head: int, tail: int, level: int = 0):
        '''
        Compiles an expression.
        '''
        self.results.put(WriteElement('<expression>', level))

        offset = 0
        while head + offset < tail:
            length = 0
            current = None
            matchCnt = 0
            while head + offset + length < tail:
                current = self.tokenList[head + offset + length]
                if isOpenParenthesis(current):
                    matchCnt += 1
                elif isCloseParenthesis(current):
                    matchCnt -= 1
                elif isOp(current) and matchCnt == 0 and length != 0:
                    break
                length += 1
            self.compileTerm(
                head + offset, head + offset + length, level + 1
            )
            if not head + offset + length == tail:
                self.results.put(WriteElement(current, level + 1))
            offset += length + 1

        self.results.put(WriteElement('</expression>', level))

    def compileExpressionList(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a (possibly empty) comma-separated list of expressions.
        '''
        self.results.put(WriteElement('<expressionList>', level))

        offset = 0
        while head + offset < tail:
            length = 0
            current = None
            while head + offset + length < tail:
                current = self.tokenList[head + offset + length]
                if isComma(current):
                    break
                length += 1
            self.compileExpression(
                head + offset, head + offset+length, level + 1
            )
            if not head+offset+length == tail:
                self.results.put(WriteElement(current, level + 1))
            offset += length + 1

        self.results.put(WriteElement('</expressionList>', level))

    def compileReturn(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a return statement.
        '''
        returnKWD = self.tokenList[head]
        semicolon = self.tokenList[tail - 1]
        if not isSemicolon(semicolon):
            raise ValueError(f'{semicolon} must be ";".')

        self.results.put(WriteElement('<returnStatement>', level))
        self.results.put(WriteElement(returnKWD, level + 1))
        if tail - head != 2:
            self.compileExpression(head + 1, tail - 1, level + 1)
        self.results.put(WriteElement(semicolon, level + 1))
        self.results.put(WriteElement('</returnStatement>', level))

    def compileDo(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a do statement.
        '''
        def handleSubroutineCall(head: int, tail: int):
            def handleCallList(head, tail) -> int:
                matchCnt = 1
                for i in range(head, tail):
                    current = self.tokenList[i]
                    if isOpenParenthesis(current):
                        matchCnt += 1
                    elif isCloseParenthesis(current):
                        matchCnt -= 1
                        if matchCnt == 0:
                            return i
                raise ValueError('invalid callList.')

            name = self.tokenList[head]
            whether = self.tokenList[head + 1]
            if isPoint(whether):
                subName = self.tokenList[head + 2]
                openParen = self.tokenList[head + 3]
                if not isOpenParenthesis(openParen):
                    raise ValueError(f'{openParen} should be "("')
                nexId = handleCallList(head + 4, tail)
                closeParen = self.tokenList[nexId]
                if not isCloseParenthesis(closeParen):
                    raise ValueError(f'{closeParen} shoule be ")"')
                self.results.put(WriteElement(name, level + 1))
                self.results.put(WriteElement(whether, level + 1))
                self.results.put(WriteElement(subName, level + 1))
                self.results.put(WriteElement(openParen, level + 1))
                self.compileExpressionList(head + 4, nexId, level + 1)
                self.results.put(WriteElement(closeParen, level + 1))
                return
            nextId = handleCallList(head + 2, tail)
            closeParen = self.tokenList[nextId]
            self.results.put(WriteElement(name, level + 1))
            self.results.put(WriteElement(whether, level + 1))
            self.compileExpressionList(head + 2, nextId, level + 1)
            self.results.put(WriteElement(closeParen, level + 1))

        doKWD = self.tokenList[head]
        semicolon = self.tokenList[tail - 1]
        if not isSemicolon(semicolon):
            raise ValueError(f'{semicolon} should be ";"')

        self.results.put(WriteElement('<doStatement>', level))
        self.results.put(WriteElement(doKWD, level + 1))
        handleSubroutineCall(head + 1, tail - 1)
        self.results.put(WriteElement(semicolon, level + 1))
        self.results.put(WriteElement('</doStatement>', level))

    def compileWhile(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a while statement.
        '''
        def handleWhileExpression(head: int, tail: int) -> int:
            offset = 0
            matchCnt = 1
            while head + offset < tail:
                current = self.tokenList[head + offset]
                if isOpenParenthesis(current):
                    matchCnt += 1
                elif isCloseParenthesis(current):
                    matchCnt -= 1
                    if matchCnt == 0:
                        break
                offset += 1
            if head + offset == tail:
                raise ValueError('invalid whileExpression.')
            return head + offset

        whileKWD = self.tokenList[head]
        openParen = self.tokenList[head + 1]
        nextId = handleWhileExpression(head + 2, tail)
        closeParen = self.tokenList[nextId]
        openBrace = self.tokenList[nextId + 1]
        closeBrace = self.tokenList[tail - 1]
        if not isOpenParenthesis(openParen):
            raise ValueError(f'{openParen} should be' + ' "{"')
        if not isCloseParenthesis(closeParen):
            raise ValueError(f'{closeParen} should be' + ' "}"')
        if not isOpenBrace(openBrace):
            raise ValueError(f'{openBrace} should be "("')
        if not isCloseBrace(closeBrace):
            raise ValueError(f'{closeBrace} should be ")"')

        self.results.put(WriteElement('<whileStatement>', level))
        self.results.put(WriteElement(whileKWD, level + 1))
        self.results.put(WriteElement(openParen, level + 1))
        self.compileExpression(head + 2, nextId, level + 1)
        self.results.put(WriteElement(closeParen, level + 1))
        self.results.put(WriteElement(openBrace, level + 1))
        self.compileStatements(nextId + 2, tail - 1, level + 1)
        self.results.put(WriteElement(closeBrace, level + 1))
        self.results.put(WriteElement('</whileStatement>', level))

    def compileIf(self, head: int, tail: int, level: int = 0):
        '''
        Compiles an if statement, possibly with a trailing else clause.
        '''
        def handleIfExpression(head: int, tail: int) -> int:
            offset = 0
            matchCnt = 1
            while head + offset < tail:
                current = self.tokenList[head + offset]
                if isOpenParenthesis(current):
                    matchCnt += 1
                elif isCloseParenthesis(current):
                    matchCnt -= 1
                    if matchCnt == 0:
                        break
                offset += 1
            if head + offset == tail:
                raise ValueError('invalid ifExpression.')
            return head + offset

        def handleIfStatements(head: int, tail: int) -> int:
            offset = 0
            matchCnt = 1
            while head + offset < tail:
                current = self.tokenList[head + offset]
                if isOpenBrace(current):
                    matchCnt += 1
                if isCloseBrace(current):
                    matchCnt -= 1
                    if matchCnt == 0:
                        return head + offset
                offset += 1
            raise ValueError('invalid ifStatements.')

        def handleElse(head: int, tail: int):
            elseKWD = self.tokenList[head]
            openBrace = self.tokenList[head + 1]
            closeBrace = self.tokenList[tail - 1]
            if not isElse(elseKWD):
                raise ValueError(f'{elseKWD} should be "else".')
            if not isOpenBrace(openBrace):
                raise ValueError(f'{openBrace} should be "(".')
            if not isCloseBrace(closeBrace):
                raise ValueError(f'{closeBrace} should be ")".')

            self.results.put(WriteElement(elseKWD, level + 1))
            self.results.put(WriteElement(openBrace, level + 1))
            self.compileStatements(head + 2, tail - 1, level + 1)
            self.results.put(WriteElement(closeBrace, level + 1))

        ifKWD = self.tokenList[head]
        openParen = self.tokenList[head + 1]
        nextId0 = handleIfExpression(head + 2, tail)
        closeParen = self.tokenList[nextId0]
        openBrace = self.tokenList[nextId0 + 1]
        nextId1 = handleIfStatements(nextId0 + 2, tail)
        closeBrace = self.tokenList[nextId1]
        if not isOpenParenthesis(openParen):
            raise ValueError(f'{openParen} should be ' + '"{".')
        if not isCloseParenthesis(closeParen):
            raise ValueError(f'{openParen} should be ' + '"}".')
        if not isOpenBrace(openBrace):
            raise ValueError(f'{openBrace} should be "(".')
        if not isCloseBrace(closeBrace):
            raise ValueError(f'{closeBrace} should be ")".')

        self.results.put(WriteElement('<ifStatement>', level))
        self.results.put(WriteElement(ifKWD, level + 1))
        self.results.put(WriteElement(openParen, level + 1))
        self.compileExpression(head + 2, nextId0, level + 1)
        self.results.put(WriteElement(closeParen, level + 1))
        self.results.put(WriteElement(openBrace, level + 1))
        self.compileStatements(nextId0 + 2, nextId1, level + 1)
        self.results.put(WriteElement(closeBrace, level + 1))
        if nextId1 < tail - 1:
            handleElse(nextId1 + 1, tail)
        self.results.put(WriteElement('</ifStatement>', level))

    def compileLet(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a let statement.
        '''
        def handleLetExpression(head: int, tail: int) -> int:
            openSquare = self.tokenList[head]
            if not isOpenSquare(openSquare):
                return head
            offset = 1
            matchCnt = 1
            while head + offset < tail:
                current = self.tokenList[head + offset]
                if isOpenSquare(current):
                    matchCnt += 1
                if isCloseSquare(current):
                    matchCnt -= 1
                    if matchCnt == 0:
                        break
                offset += 1
            if head + offset == tail:
                raise ValueError('invalid letExpression.')
            self.results.put(WriteElement(openSquare, level + 1))
            self.compileExpression(head + 1, head + offset, level + 1)
            self.results.put(WriteElement(current, level + 1))
            return head + offset + 1

        letKWD = self.tokenList[head]
        varName = self.tokenList[head + 1]
        semicolon = self.tokenList[tail - 1]
        if not varName.tType == IDENTIFIER:
            raise ValueError(f'{varName} should be an {IDENTIFIER}.')
        if not isSemicolon(semicolon):
            raise ValueError(f'{semicolon} should be a ";".')

        self.results.put(WriteElement('<letStatement>', level))
        self.results.put(WriteElement(letKWD, level + 1))
        self.results.put(WriteElement(varName, level + 1))
        nextId = handleLetExpression(head + 2, tail)
        equal = self.tokenList[nextId]
        if not isEqual(equal):
            raise ValueError(f'{equal} should be a "=".')
        self.results.put(WriteElement(equal, level + 1))
        self.compileExpression(nextId + 1, tail - 1, level + 1)
        self.results.put(WriteElement(semicolon, level + 1))
        self.results.put(WriteElement('</letStatement>', level))

    def compileStatements(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a sequence of statements.
        Does not handle the enclosing "{}".
        '''
        def handleStatement(content: str, head: int, tail: int):
            if content == 'let':
                self.compileLet(head, tail, level + 1)
            elif content == 'if':
                self.compileIf(head, tail, level + 1)
            elif content == 'while':
                self.compileWhile(head, tail, level + 1)
            elif content == 'do':
                self.compileDo(head, tail, level + 1)
            elif content == 'return':
                self.compileReturn(head, tail, level + 1)
            else:
                raise ValueError(f'{content} should be a statementKey')

        self.results.put(WriteElement('<statements>', level))

        offset = 0
        while head + offset < tail:
            current = self.tokenList[head + offset]
            if not isStatementKey(current):
                raise ValueError(f'{current} should be a statementKey')
            length = 1
            matchCnt = 0  # matching parentheses
            while head + offset + length < tail:
                temp = self.tokenList[head + offset + length]
                if isOpenBrace(temp) or isOpenParenthesis(temp) or isOpenSquare(temp):
                    matchCnt += 1
                if isCloseBrace(temp) or isCloseParenthesis(temp) or isCloseSquare(temp):
                    matchCnt -= 1
                if isStatementKey(temp) and matchCnt == 0:
                    break
                length += 1
            handleStatement(
                current.content, head + offset, head + offset + length
            )
            offset += length
        self.results.put(WriteElement('</statements>', level))

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

    def compileSubroutineBody(self, head: int, tail: int, level: int = 0):
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
        self.compileStatements(nextId, tail - 1, level + 1)
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
                if not isSubDecKWD(current):
                    raise ValueError(f'{current} should be an SubDecKWD.')
                index = 1
                while head + offset + index < tail:
                    temp = self.tokenList[head + offset + index]
                    if isSubDecKWD(temp):
                        break
                    index += 1
                self.compileSubroutineDec(
                    head + offset, head + offset + index, level + 1
                )
                offset += index
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
        if self.isSave:
            writer = threading.Thread(target=self.writeResult)
            writer.start()
        # self.compileClass(0, self.total)
        try:
            self.compileClass(0, self.total)
        except Exception as e:
            print(self.inPath.name + ': ' + str(e))
        self.end = True
        # writer.join()

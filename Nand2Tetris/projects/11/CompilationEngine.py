from pathlib import Path
from queue import Queue
import threading

from CompilerTools import *
from SymbolTable import SymbolTable
from VMWriter import VMWriter


class WriteElement:
    def __init__(self, content, level: int):
        self.content = content
        self.level = level

    def __str__(self) -> str:
        return '  ' * self.level + str(self.content)
        # return ''


class CompilationEngine:
    def __init__(self, inPath: Path, tokenList: list[Token] = [], isSave: bool = False):
        self.setAll(inPath, tokenList, isSave)

    def setAll(self, inPath: Path, tokenList: list[Token] = [], isSave: bool = False):
        self.inPath = inPath
        self.tokenList: list[Token] = tokenList
        self.total = len(tokenList)
        self.results = Queue()
        self.end = False
        self.isSave = isSave
        self.cName = ''
        self.cField = 0
        self.index = 0
        self.symbalTable = SymbolTable()
        self.methodList = []
        if inPath.is_file():
            self.outPath = Path(f'{inPath.parent}/{inPath.stem}.vm')
        elif inPath.is_dir():
            raise FileExistsError(f"{inPath} isn't a file")
        else:
            raise FileNotFoundError(f"File/Dir '{inPath}' does not exist.")

    def writeResult(self):
        open(self.outPath, 'w', encoding=ENCODE).close()
        while not (self.end and self.results.empty()):
            element: WriteElement = self.results.get()
            with open(self.outPath, 'a', encoding=ENCODE) as file:
                file.write(str(element) + '\n')

    def getIndex(self):
        self.index += 1
        return self.index - 1

    def compileTerm(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a term.
        If the current token is an identifier, the routine must distinguish between a variable, an array entry, or a subroutine call.
        A single look-ahead token, which may be one of "[", "(", or ".", suffices to distinguish between the possibilities.
        Any other token is not part of this term and should not be advanced over.
        '''
        # print('\n----------term---------------')
        # for i in range(head, tail):
        #     print(self.tokenList[i])

        def handlePoint(first: Token):
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
            if not self.symbalTable.kindOf(first.content) is None:
                kind = self.symbalTable.kindOf(first.content)
                index = self.symbalTable.indexOf(first.content)
                self.writer.writePush(kind, index)
            nArgs = self.compileExpressionList(
                head + 4, tail - 1, level + 1)
            funName = f'{first.content}.{subName.content}'
            if not self.symbalTable.kindOf(first.content) is None:
                nArgs += 1
                vType = self.symbalTable.typeOf(first.content)
                funName = f'{vType}.{subName.content}'
            self.writer.writeCall(funName, nArgs)

        def handleSquare(first: Token):
            name = first.content
            kind = self.symbalTable.kindOf(name)
            if kind is None:
                raise ValueError(f'invalid var {name}.')
            index = self.symbalTable.indexOf(name)
            closeSquare = self.tokenList[tail - 1]
            if not isCloseSquare(closeSquare):
                raise ValueError(f'{closeSquare} should be "]".')
            self.writer.writePush(kind, index)
            self.compileExpression(head + 2, tail - 1, level + 1)
            self.writer.writeArithmetic('add')
            # stack.top() = RAM address of arr[expression]
            self.writer.writePop('pointer', 1)
            self.writer.writePush('that', 0)

        def handleParen():
            closeParen = self.tokenList[tail - 1]
            if not isCloseParenthesis(closeParen):
                raise ValueError(f'{closeParen} should be ")".')
            self.compileExpressionList(head + 2, tail - 1, level + 1)

        def handleKWDConst(first: Token):
            content = first.content
            if content == 'true':
                self.writer.writePush('constant', 0)
                self.writer.writeArithmetic('not')
            elif content == 'false':
                self.writer.writePush('constant', 0)
            elif content == 'null':
                self.writer.writePush('constant', 0)
            else:  # this
                self.writer.writePush('pointer', 0)

        def handleString(first: Token):
            content = first.content
            self.writer.writePush('constant', len(content))
            self.writer.writeCall('String.new', 1)
            for char in content:
                self.writer.writePush('constant', ord(char))
                self.writer.writeCall('String.appendChar', 2)

        first = self.tokenList[head]
        if isInteger(first):
            self.writer.writePush('constant', first.content)
        elif isString(first):
            handleString(first)
        elif isKeywordConst(first):  # 'true', 'false', 'null', 'this'
            handleKWDConst(first)
        elif isUnaryOp(first):  # - or ~
            self.compileTerm(head + 1, tail, level + 1)
            self.writer.writeArithmetic(UNARY_DICT[first.content])
        elif isOpenParenthesis(first):  # (
            closeParen = self.tokenList[tail - 1]
            if not isCloseParenthesis(closeParen):
                raise ValueError(f'{closeParen} should be ")".')
            self.compileExpression(head + 1, tail - 1, level + 1)
        elif first.tType == IDENTIFIER:
            if tail - head == 1:
                name = first.content
                kind = self.symbalTable.kindOf(name)
                if kind is None:
                    raise ValueError(f'{name} should be an IDENTIFIER.')
                index = self.symbalTable.indexOf(name)
                self.writer.writePush(kind, index)
            else:
                whether = self.tokenList[head + 1]
                if isOpenSquare(whether):  # [
                    handleSquare(first)
                elif isPoint(whether):  # .
                    handlePoint(first)
                elif isOpenParenthesis(whether):  # (
                    handleParen(first)
                else:
                    raise ValueError('invalid term.')
        else:
            raise ValueError('invalid term.')

    def compileExpression(self, head: int, tail: int, level: int = 0):
        '''
        Compiles an expression.
        '''
        # print(f'\n-------expression------------')
        # for i in range(head, tail):
        #     print(self.tokenList[i])

        def writeAri(ari: str):
            if ari in ARI_DICT.keys():
                self.writer.writeArithmetic(ARI_DICT[ari])
            elif ari == '*':
                self.writer.writeCall('Math.multiply', 2)
            elif ari == '/':
                self.writer.writeCall('Math.divide', 2)
            else:
                raise ValueError(f'{ari} should be an ari.')

        offset = 0
        stack = []
        while head + offset < tail:
            length = 0
            current = None
            matchCnt = 0
            while head + offset + length < tail:
                current = self.tokenList[head + offset + length]
                if isOpenParenthesis(current) or isOpenSquare(current):
                    matchCnt += 1
                    stack.append(current.content)
                elif isCloseParenthesis(current) or isCloseSquare(current):
                    matchCnt -= 1
                    stack.append(current.content)
                elif isOp(current) and matchCnt == 0 and length != 0:
                    break
                length += 1
            self.compileTerm(
                head + offset, head + offset + length, level + 1
            )
            if len(stack) > 1 and stack[-1] in [')', ']']:
                stack.pop()
                num = 1
                while num != 0 and len(stack) != 0:
                    temp = stack.pop()
                    if temp in ['(', '[']:
                        num -= 1
                    elif temp == [')', ']']:
                        num += 1
            if not head + offset + length == tail:
                stack.append(current.content)
            offset += length + 1
        while len(stack) != 0:
            temp = stack.pop()
            writeAri(temp)

    def compileExpressionList(self, head: int, tail: int, level: int = 0) -> int:
        '''
        Compiles a (possibly empty) comma-separated list of expressions.
        '''
        cnt = 0
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
            cnt += 1
        return cnt

    def compileReturn(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a return statement.
        '''
        returnKWD = self.tokenList[head]
        semicolon = self.tokenList[tail - 1]
        if not isSemicolon(semicolon):
            raise ValueError(f'{semicolon} must be ";".')

        if tail - head != 2:
            self.compileExpression(head + 1, tail - 1, level + 1)
        else:
            self.writer.writePush('constant', 0)
        self.writer.writeReturn()

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

            name = self.tokenList[head].content
            whether = self.tokenList[head + 1]
            if isPoint(whether):
                subName = self.tokenList[head + 2].content
                openParen = self.tokenList[head + 3]
                if not isOpenParenthesis(openParen):
                    raise ValueError(f'{openParen} should be "("')
                nexId = handleCallList(head + 4, tail)
                closeParen = self.tokenList[nexId]
                if not isCloseParenthesis(closeParen):
                    raise ValueError(f'{closeParen} shoule be ")"')
                if not self.symbalTable.kindOf(name) is None:
                    kind = self.symbalTable.kindOf(name)
                    index = self.symbalTable.indexOf(name)
                    self.writer.writePush(kind, index)
                nArgs = self.compileExpressionList(head + 4, nexId, level + 1)
                funName = f'{name}.{subName}'
                if not self.symbalTable.kindOf(name) is None:
                    vType = self.symbalTable.typeOf(name)
                    funName = f'{vType}.{subName}'
                    nArgs += 1
                self.writer.writeCall(funName, nArgs)
            elif isOpenParenthesis(whether):
                nextId = handleCallList(head + 2, tail)
                closeParen = self.tokenList[nextId]
                if not isCloseParenthesis(closeParen):
                    raise ValueError(f'{closeParen} shoule be ")"')
                if name in self.methodList:
                    self.writer.writePush('pointer', 0)
                nArgs = self.compileExpressionList(head + 2, nextId, level + 1)
                funName = f'{self.cName}.{name}'
                if name in self.methodList:
                    nArgs += 1
                self.writer.writeCall(funName, nArgs)
            else:
                raise ValueError(f'{whether} should be "("')

        doKWD = self.tokenList[head]
        semicolon = self.tokenList[tail - 1]
        if not isSemicolon(semicolon):
            raise ValueError(f'{semicolon} should be ";"')

        handleSubroutineCall(head + 1, tail - 1)
        self.writer.writePop('temp', 0)

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

        label0 = f'while{self.getIndex()}'
        label1 = f'endWhile{self.getIndex()}'
        self.writer.writeLabel(label0)
        self.compileExpression(head + 2, nextId, level + 1)
        self.writer.writeArithmetic('not')
        self.writer.writeIf(label1)
        self.compileStatements(nextId + 2, tail - 1, level + 1)
        self.writer.writeGoto(label0)
        self.writer.writeLabel(label1)

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

            self.compileStatements(head + 2, tail - 1, level + 1)

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

        label0 = f'endIf{self.getIndex()}'
        label1 = f'endElse{self.getIndex()}'
        self.compileExpression(head + 2, nextId0, level + 1)
        self.writer.writeArithmetic('not')
        self.writer.writeIf(label0)
        self.compileStatements(nextId0 + 2, nextId1, level + 1)
        self.writer.writeGoto(label1)
        self.writer.writeLabel(label0)
        if nextId1 < tail - 1:
            handleElse(nextId1 + 1, tail)
        self.writer.writeLabel(label1)

    def compileLet(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a let statement.
        '''
        def handleLetExpression(head: int, tail: int, var: Token) -> int:
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
            vName = var.content
            kind = self.symbalTable.kindOf(vName)
            if kind is None:
                raise ValueError(f'invalid var "{kind}"')
            index = self.symbalTable.indexOf(vName)
            self.writer.writePush(kind, index)
            self.compileExpression(head + 1, head + offset, level + 1)
            self.writer.writeArithmetic('add')
            return head + offset + 1

        letKWD = self.tokenList[head]
        varName = self.tokenList[head + 1]
        semicolon = self.tokenList[tail - 1]
        if not varName.tType == IDENTIFIER:
            raise ValueError(f'{varName} should be an {IDENTIFIER}.')
        if not isSemicolon(semicolon):
            raise ValueError(f'{semicolon} should be a ";".')
        nextId = handleLetExpression(head + 2, tail, varName)
        equal = self.tokenList[nextId]
        if not isEqual(equal):
            raise ValueError(f'{equal} should be a "=".')

        name = varName.content
        kind = self.symbalTable.kindOf(name)
        index = self.symbalTable.indexOf(name)
        self.compileExpression(nextId + 1, tail - 1, level + 1)
        if nextId == head + 2:
            self.writer.writePop(kind, index)
        else:  # handle array
            self.writer.writePop('temp', 0)
            self.writer.writePop('pointer', 1)
            self.writer.writePush('temp', 0)
            self.writer.writePop('that', 0)

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

    def compileVarDec(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a var declaration.
        '''
        if head != tail:
            if tail - head < 4:
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

            for offset in range(0, tail - head - 3):
                current = self.tokenList[head + 2 + offset]
                if offset % 2 == 0:
                    if current.tType != IDENTIFIER:
                        raise ValueError(f'{current} must be an {IDENTIFIER}.')
                    self.symbalTable.define(
                        current.content, varType.content, 'local'
                    )
                if offset % 2 == 1 and not isComma(current):
                    raise ValueError(f'{current} must be a ",".')

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

        nextId = followedVarDec(head + 1, tail - 1)
        self.compileStatements(nextId, tail - 1, level + 1)

    def compileParameterList(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a (possibly empty) parameter list.
        Does not handle the enclosing "()".
        '''
        if head != tail:
            if tail - head < 2:
                raise ValueError('parameter is invalid.')
            offset = 0
            segType = ''
            segName = ''
            while head + offset < tail:
                current: Token = self.tokenList[head + offset]
                if offset % 3 == 0:
                    if not isType(current):
                        raise ValueError(
                            f'{current} is invalid. It should be a TYPE.')
                    segType = current.content
                if offset % 3 == 1:
                    if not current.tType == IDENTIFIER:
                        raise ValueError(
                            f'{current} is invalid. It should be an "{IDENTIFIER}".'
                        )
                    segName = current.content
                if offset % 3 == 2:
                    if not isComma(current):
                        raise ValueError(
                            f'{current} is invalid. It should be a ",".'
                        )
                    self.symbalTable.define(segName, segType, 'argument')
                offset += 1
            self.symbalTable.define(segName, segType, 'argument')

    def compileSubroutineDec(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a complete method, function, or constructor.
        '''
        def handleParamList(head: int, tail: int) -> int:
            offset = 0
            while head + offset < tail:
                current = self.tokenList[head + offset]
                if isCloseParenthesis(current):
                    break
                offset += 1
            return head + offset

        def cntArgs(head: int, tail: int) -> int:
            offset = 1
            cnt = 0
            while head + offset < tail:
                current = self.tokenList[head + offset]
                if current.content != 'var' or current.tType != KEYWORD:
                    break
                length = 2
                while head + offset + length < tail:
                    current = self.tokenList[head + offset + length]
                    if current.tType == IDENTIFIER:
                        cnt += 1
                    if isSemicolon(current):
                        break
                    length += 1
                offset += length + 1
            return cnt

        subKWD = self.tokenList[head]
        subType = self.tokenList[head + 1]
        subName = self.tokenList[head + 2]
        openParenthesis = self.tokenList[head + 3]
        nextId = handleParamList(head + 4, tail)
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

        self.symbalTable.startSubroutine()
        fname = f'{self.cName}.{subName.content}'
        cnt = cntArgs(nextId + 1, tail)
        fKind = subKWD.content
        self.writer.writeFunction(fname, cnt)
        if fKind == 'method':
            self.symbalTable.define('this', self.cName, 'argument')
            self.writer.writePush('argument', 0)
            self.writer.writePop('pointer', 0)
        elif fKind == 'constructor':
            self.writer.writePush('constant', self.cField)
            self.writer.writeCall('Memory.alloc', 1)
            self.writer.writePop('pointer', 0)
        self.compileParameterList(head + 4, nextId, level + 1)
        self.compileSubroutineBody(nextId + 1, tail, level + 1)

    def compileClassVarDec(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a static variable declaration, or a field declaration.
        '''
        def getVarNames(head: int, tail: int) -> list[Token]:
            cnt = 0
            names = []
            while head + cnt < tail:
                current = self.tokenList[head + cnt]
                if cnt % 2 == 0:
                    if current.tType != IDENTIFIER:
                        raise ValueError(
                            f"{current} is invalid. It should be an {IDENTIFIER}."
                        )
                    names.append(current)
                elif cnt % 2 == 1 and not isComma(current):
                    raise ValueError(
                        f"{current} is invalid. It should be a ','."
                    )
                cnt += 1
            return names

        varKWD = self.tokenList[head]
        varType = self.tokenList[head + 1]
        varNames = getVarNames(head + 2, tail - 1)
        semicolon = self.tokenList[tail - 1]
        if not isType(varType):
            raise ValueError(f'{varType} is invalid. It should be a TYPE.')
        if not isSemicolon(semicolon):
            raise ValueError(f'{varType} is invalid. It should be ";".')

        if varKWD.content == 'field':
            self.cField += len(varNames)
            varKWD.content = 'this'
        for token in varNames:
            self.symbalTable.define(
                token.content, varType.content, varKWD.content
            )

    def compileClass(self, head: int, tail: int, level: int = 0):
        '''
        Compiles a complete class
        '''
        def handleClassVar(head: int, tail: int) -> int:
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

        def handleSubroutineDec(head: int, tail: int) -> int:
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

        def getMethods():
            i = head
            while i < tail:
                current = self.tokenList[i]
                if isSubDecKWD(current) and current.content == 'method':
                    if i + 2 >= tail:
                        raise ValueError('invalid method.')
                    temp = self.tokenList[i + 2]
                    self.methodList.append(temp.content)
                i += 1

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

        self.cName = className.content
        getMethods()
        nextId = handleClassVar(head + 3, tail - 1)
        handleSubroutineDec(nextId, tail - 1)

    def runCompilationEngine(self):
        # self.compileClass(0, self.total)
        try:
            self.writer = VMWriter(self.outPath)
            self.compileClass(0, self.total)
            self.writer.close()
        except Exception as e:
            print(self.inPath.name + ': ' + str(e))
        self.end = True

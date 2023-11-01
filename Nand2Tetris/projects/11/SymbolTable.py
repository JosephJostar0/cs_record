class SymbolNode:
    def __init__(self, name: str, sType: str, kind: str, index: int):
        self.name = name
        self.sType = sType
        self.kind = kind
        self.index = index

    def __str__(self) -> str:
        return f'{self.name} {self.sType} {self.kind} {self.index}'


class SymbolTable:
    def __init__(self):
        self.whole: dict[str, SymbolNode] = dict()
        self.subroutine: dict[str, SymbolNode] = dict()

    def startSubroutine(self):
        '''
        Starts a new subroutine scope (i.e., resets the subroutine's symbol table.)
        '''
        self.subroutine.clear()

    def define(self, name: str, sType: str, kind: str):
        '''
        Defines a new identifier of the given name, type, and kind, and assigns it a running index.
        STATIC and FIELD identifiers have a class scope, while ARG and VAR identifiers have a subroutine scope.
        '''
        num = self.varCount(kind)
        node = SymbolNode(name, sType, kind, num)
        if kind in ['static', 'this']:
            self.whole[name] = node
        else:
            self.subroutine[name] = node

    def varCount(self, kind: str) -> int:
        '''
        Returns the number of variables of the given kind already defined in the current scope.
        '''
        cnt = 0
        for value in self.whole.values():
            if value.kind == kind:
                cnt += 1
        for value in self.subroutine.values():
            if value.kind == kind:
                cnt += 1
        return cnt

    def kindOf(self, name: str) -> str:
        '''
        Returns the kind of the named identifier in the current scope.
        If the identifier is unknown in the current scope, returns NONE.
        '''
        if name in self.subroutine.keys():
            return self.subroutine[name].kind
        if name in self.whole.keys():
            return self.whole[name].kind
        return None

    def typeOf(self, name: str) -> str:
        '''
        Returns the type of the named identifier in the current scope.
        '''
        if name in self.subroutine.keys():
            return self.subroutine[name].sType
        if name in self.whole.keys():
            return self.whole[name].sType
        return None

    def indexOf(self, name: str) -> int:
        '''
        Returns the index assigned to the named identifier.
        '''
        if name in self.subroutine.keys():
            return self.subroutine[name].index
        if name in self.whole.keys():
            return self.whole[name].index
        return None

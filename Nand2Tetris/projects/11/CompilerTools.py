ENCODE = 'utf-8'
MATCH_COMMENT0 = r'//.*'
MATCH_COMMENT1 = r'/\*.*?\*/'
MATCH_STRING = r'^".*"$'
MATCH_IDENTIFIER = r"^(?!^\d)\w+$"
MATCH_TOKEN = r'([{},\[\].,;+\-*/&|<>=~\(\)])'
MATCH_TOKEN_STR = r'(.*)(".*")(.*)'
INT_MIN = 0
INT_MAX = 32767

# Token Type
SYMBOL = 'symbol'
KEYWORD = 'keyword'
IDENTIFIER = 'identifier'
INTEGER = 'integerConstant'
STRING = 'stringConstant'

# JackTokenizer
KEYWORD_LIST = [
    'class', 'constructor', 'function', 'method',
    'field', 'static', 'var', 'int', 'char',
    'boolean', 'void', 'true', 'false', 'null',
    'this', 'let', 'do', 'if', 'else', 'while', 'return'
]
SYMBOL_DICT = {
    '{': '{', '}': '}', '(': '(', ')': ')', '[': '[', ']': ']',
    '.': '.', ',': ',', ';': ';', '+': '+', '-': '-', '*': '*',
    '/': '/', '&': '&amp;', '|': '|', '<': '&lt;', '>': '&gt;',
    '=': '=', '~': '~',
}


class Token:
    def __init__(self, content: str, tType: str):
        self.content = content
        self.tType = tType

    def __str__(self) -> str:
        token = self.content if self.tType != SYMBOL else SYMBOL_DICT[self.content]
        return f'<{self.tType}> {token} </{self.tType}>'


# CompilationEngine
ARI_DICT = {
    '+': 'add', '-': 'sub', '&': 'and', '|': 'or',
    '>': 'gt', '<': 'lt', '=': 'eq'
}
UNARY_DICT = {'-': 'neg', '~': 'not'}


def isSemicolon(token: Token) -> bool:
    return token.content == ';' and token.tType == SYMBOL


def isType(token: Token) -> bool:
    if token.tType == IDENTIFIER:
        return True
    return token.content in ['int', 'char', 'boolean'] and token.tType == KEYWORD


def isOpenBrace(token: Token) -> bool:
    return token.content == '{' and token.tType == SYMBOL


def isCloseBrace(token: Token) -> bool:
    return token.content == '}' and token.tType == SYMBOL


def isComma(token: Token) -> bool:
    return token.content == ',' and token.tType == SYMBOL


def isOpenParenthesis(token: Token) -> bool:
    return token.content == '(' and token.tType == SYMBOL


def isCloseParenthesis(token: Token) -> bool:
    return token.content == ')' and token.tType == SYMBOL


def isStatementKey(token: Token) -> bool:
    return token.tType == KEYWORD and token.content in ['let', 'if', 'while', 'do', 'return']


def isEqual(token: Token) -> bool:
    return token.tType == SYMBOL and token.content == '='


def isOpenSquare(token: Token) -> bool:
    return token.tType == SYMBOL and token.content == '['


def isCloseSquare(token: Token) -> bool:
    return token.tType == SYMBOL and token.content == ']'


def isElse(token: Token) -> bool:
    return token.tType == KEYWORD and token.content == 'else'


def isWhile(token: Token) -> bool:
    return token.tType == KEYWORD and token.content == 'while'


def isReturn(token: Token) -> bool:
    return token.tType == KEYWORD and token.content == 'return'


def isSubDecKWD(token: Token) -> bool:
    return token.tType == KEYWORD and token.content in ['constructor', 'function', 'method']


def isPoint(token: Token) -> bool:
    return token.tType == SYMBOL and token.content == '.'


def isOp(token: Token) -> bool:
    return token.tType == SYMBOL and token.content in ['+', '-', '*', '/', '&', '|', '<', '>', '=']


def isUnaryOp(token: Token) -> bool:
    return token.tType == SYMBOL and token.content in ['-', '~']


def isKeywordConst(token: Token) -> bool:
    return token.tType == KEYWORD and token.content in ['true', 'false', 'null', 'this']


def isInteger(token: Token) -> bool:
    return token.tType == INTEGER


def isString(token: Token) -> bool:
    return token.tType == STRING

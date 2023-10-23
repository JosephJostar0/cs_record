from JackAnalyzer import Token

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


# CompilationEngine
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

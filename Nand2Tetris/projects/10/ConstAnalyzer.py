ENCODE = 'utf-8'
MATCH_COMMENT0 = r'//.*'
MATCH_COMMENT1 = r'/\*.*?\*/'
MATCH_STRING = r'^".*"$'
MATCH_IDENTIFYER = r"^(?!^\d)\w+$"
MATCH_TOKEN = r'([{},\[\].,;+\-*/&|<>=~\(\)])'
MATCH_TOKEN_STR = r'(.*)(".*")(.*)'
INT_MIN = 0
INT_MAX = 32767

# JackTokenizer
KEYWORD = [
    'class', 'constructor', 'function', 'method',
    'field', 'static', 'var', 'int', 'char',
    'boolean', 'void', 'true', 'false', 'null',
    'this', 'let', 'do', 'if', 'else', 'while', 'return'
]
SYMBOL = {
    '{': '{', '}': '}', '(': '(', ')': ')', '[': '[', ']': ']',
    '.': '.', ',': ',', ';': ';', '+': '+', '-': '-', '*': '*',
    '/': '/', '&': '&amp;', '|': '|', '<': '&lt;', '>': '&gt;',
    '=': '=', '~': '~',
}

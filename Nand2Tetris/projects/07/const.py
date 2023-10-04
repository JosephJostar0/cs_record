ENCODE = 'utf-8'
CUTOFF = r'//.*'

TEMP = 5
ADDR = '@R15'
INDEX_MAX = 7

PUSH_SEGMENT = [
    'local', 'arguement', 'this', 'that',
    'constant', 'static', 'pointer', 'temp',
]
PUSH_COMMON = ['@sp', 'M=M+1', 'A=M-1', 'M=D']

POP_SEGMENT = [
    'local', 'arguement', 'this', 'that',
    'static', 'pointer', 'temp',
]

SEG_CONST = ['constant']
SEG_BASIC = ['local', 'argument', 'this', 'that']
BASIC_ALTER = {
    'local': '@LCL',
    'arguement': '@ARG',
    'this': '@THIS',
    'that': '@THAT',
}
SEG_STATIC = ['static']
SEG_TEMP = ['temp']
SEG_POINT = ['pointer']

# A=sp-1
_ARI1COMMON = ['@sp', 'A=M-1']
ARI1 = {
    'neg': _ARI1COMMON + ['M=-M'],
    'not': _ARI1COMMON + ['M=!M']
}

# D=M[--sp], A=sp-1
_ARI2COMMON = ['@sp', 'AM=M-1', 'D=M', '@sp', 'A=M-1']
ARI2 = {
    'add': _ARI2COMMON + ['M=D+M'],
    'sub': _ARI2COMMON + ['M=M-D'],
    'and': _ARI2COMMON + ['M=D&M'],
    'or': _ARI2COMMON + ['M=D|M'],
}

# D=M[sp-1], sp--, D=M[sp-1]-D, M[sp-1]=1,
LOGI_PRE = ['@sp', 'AM=M-1', 'D=M', '@sp', 'A=M-1', 'D=M-D', 'M=1']
LOGI_POST = ['@sp', 'A=M-1', 'M=0']
LOGI = {
    'eq': ['D;JEQ'],
    'gt': ['D;JGT'],
    'lt': ['D;JLT'],
}

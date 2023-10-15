ENCODE = 'utf-8'
MATCH_COMMENT = r'//.*'
MATCH_GOTO = r'(goto|if-goto) (\w+)'
MATCH_LABEL = r'(label) (\w+)'
MATCH_FUNC = r'function (.+) (\d+)'
MATCH_CALL = r'call (.+) (\d+)'
SUFFIX = '.vm'
SYSVM = 'Sys.vm'

TEMP = 5
ADDR = '@R15'
ENDFRAME = '@R14'
RETADDR = '@R13'
INDEX_MAX = 7

PUSH_SEGMENT = [
    'local', 'argument', 'this', 'that',
    'constant', 'static', 'pointer', 'temp',
]
PUSH_COMMON = ['@SP', 'M=M+1', 'A=M-1', 'M=D']

POP_SEGMENT = [
    'local', 'argument', 'this', 'that',
    'static', 'pointer', 'temp',
]
POP_COMMON = ['@SP', 'AM=M-1', 'D=M']  # D=M[--sp]

SEG_CONST = ['constant']
SEG_BASIC = ['local', 'argument', 'this', 'that']
BASIC_ALTER = {
    'local': '@LCL',
    'argument': '@ARG',
    'this': '@THIS',
    'that': '@THAT',
}
SEG_STATIC = ['static']
SEG_TEMP = ['temp']
SEG_POINT = ['pointer']

# A=sp-1
_ARI1COMMON = ['@SP', 'A=M-1']
ARI1 = {
    'neg': _ARI1COMMON + ['M=-M'],
    'not': _ARI1COMMON + ['M=!M']
}

# D=M[--sp], A=sp-1
_ARI2COMMON = POP_COMMON + ['A=A-1']
ARI2 = {
    'add': _ARI2COMMON + ['M=D+M'],
    'sub': _ARI2COMMON + ['M=M-D'],
    'and': _ARI2COMMON + ['M=D&M'],
    'or': _ARI2COMMON + ['M=D|M'],
}

# D=M[--sp], D=M[sp-1]-D, M[sp-1]=1,
LOGI_PRE = POP_COMMON + ['A=A-1', 'D=M-D', 'M=-1']
LOGI_POST = ['@SP', 'A=M-1', 'M=0']
LOGI = {
    'eq': ['D;JEQ'],
    'gt': ['D;JGT'],
    'lt': ['D;JLT'],
}

IFGOTO_CODE = POP_COMMON

ENDFRAME_COMMON = [ENDFRAME, 'AM=M-1', 'D=M']  # D=*(--endFrame)
RETURN_CODE = [
    '@LCL',
    'D=M',
    ENDFRAME,
    'M=D',  # endFrame = LCL
    '@5',
    'A=D-A',
    'D=M',
    RETADDR,
    'M=D',  # retAddr = *(endFrame - 5)
] + POP_COMMON + [
    '@ARG',
    'A=M',
    'M=D',  # *ARG = pop()
    'D=A+1',
    '@SP',
    'M=D',  # sp = ARG + 1
] + ENDFRAME_COMMON + [
    '@THAT',
    'M=D',  # THAT = *(--endFrame) = *(LCL - 1)
] + ENDFRAME_COMMON + [
    '@THIS',
    'M=D',  # THIS = *(--endFrame) = *(LCL - 2)
] + ENDFRAME_COMMON + [
    '@ARG',
    'M=D',  # ARG = *(--endFrame) = *(LCL - 3)
] + ENDFRAME_COMMON + [
    '@LCL',
    'M=D',  # LCL = *(--endFrame) = *(LCL - 4)
    RETADDR,
    'A=M',
    'D;JMP',  # goto retAddr
]

CALL_CODE1 = [
    'D=A',
] + PUSH_COMMON + [
    '@LCL',
    'D=M',
] + PUSH_COMMON + [
    '@ARG',
    'D=M',
] + PUSH_COMMON + [
    '@THIS',
    'D=M',
] + PUSH_COMMON + [
    '@THAT',
    'D=M',
] + PUSH_COMMON

CALL_CODE2 = [
    'D=A',
    '@SP',
    'D=M-D',
    '@ARG',
    'M=D',  # ARG = SP - 5 - nArgs
    '@SP',
    'D=M',
    '@LCL',
    'M=D',  # LCL = SP
]

INIT_CODE = [
    '@256',
    'D=A',
    '@SP',
    'M=D',
]

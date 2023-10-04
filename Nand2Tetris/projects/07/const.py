STACK_BASE = 256
PUSH_SEGMENT = [
    'local', 'arguement', 'this', 'that',
    'constant', 'static', 'pointer', 'temp',
]
POP_SEGMENT = [
    'local', 'arguement', 'this', 'that',
    'static', 'pointer', 'temp',
]
ARI_LOGI_COMMANDS = [
    'add', 'sub', 'neg',
    'eq', 'gt', 'lt',
    'and', 'or', 'not',
]
SEGMENT_CONSTANT = [
    'constant',
]
SEGMENT_BASIC = [
    'local', 'argument', 'this', 'that',
]
SEGMENT_STATIC = [
    'static',
]
SEGMENT_TEMP = [
    'temp',
]

SET_D2STACK = [
    '@sp',
    'M=D'
]
SET_STACK2D = [
    '@sp',
    'D=M'
]

SET_MADDR2D = [
    '@addr',
    'D=M',
]
SET_D2MADDR = [
    '@addr',
    'M=D',
]

PUSH_INSTRUCTIONS = [
    '@sp',
    'M=M+1',
]
POP_INSTRUCTIONS = [
    '@sp',
    'M=M-1'
]

AL_DICT = {
    'add': [

    ], 'sub': [

    ], 'neg': [

    ], 'eq': [

    ], 'gt': [

    ], 'lt': [

    ], 'and': [

    ], 'or': [

    ], 'not': [

    ],
}

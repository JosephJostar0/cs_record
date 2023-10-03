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
        '@sp',
        'A=M',
        'D=M',
        '@sp',
        'M=M-1',
        'A=M',
        'M=D+M'
    ], 'sub': [
        '@sp',
        'A=M',
        'D=M',
        '@sp',
        'M=M-1',
        'A=M',
        'M=M-D'
    ], 'neg': [
        '@sp',
        'A=M'
        'M=-M'
    ], 'eq': [
        '@sp',
        'A=M',
        'D=M',
        '@sp',
        'M=M-1',
        'A=M',
        'D=D-M',
        '@__Equal',
        'D;JEQ',
        'D=0',
        '@__EqEnd__',
        '1;JMP',
        '(__Equal)',
        'D=1',
        '(__EqEnd__)',
        '@sp',
        'A=M',
        'M=D'
    ], 'gt': [
        '@sp',
        'A=M',
        'D=M',
        '@sp',
        'M=M-1',
        'A=M',
        'D=D-M',
        '@__Greater',
        '-D;JGT',
        'D=0',
        '@__GtEnd__',
        '1;JMP',
        '(__Greater)',
        'D=1',
        '(__GtEnd__)',
        '@sp',
        'A=M',
        'M=D'
    ], 'lt': [
        '@sp',
        'A=M',
        'D=M',
        '@sp',
        'M=M-1',
        'A=M',
        'D=D-M',
        '@__Lesser',
        '-D;JLT',
        'D=0',
        '@__GtEnd__',
        '1;JMP',
        '(__Greater)',
        'D=1',
        '(__GtEnd__)',
        '@sp',
        'A=M',
        'M=D'
    ], 'and': [

    ], 'or': [

    ], 'not': [

    ],
}


def genSegIns(segment: str, index: str, fileName: str = '') -> list[str]:
    if segment in SEGMENT_BASIC:
        return [  # addr = @segment + i
            f'@{index}',
            'D=A',
            f'@{segment}',
            'D=D+M',
            '@addr',
            'M=D'
        ]
    if segment in SEGMENT_CONSTANT:
        return [  # D = i
            f'@{index}',
            'D=A'
        ]
    if segment in SEGMENT_STATIC:
        return [  # M[fileName.i] = D
            f'@{fileName}.{index}',
            'M=D'
        ]
    if segment in SEGMENT_TEMP:
        if int(index) > 7:
            raise ValueError(f'{segment} {index} is ungrammatical')
        return [  # addr = 5 + i
            f'@{(int(index)+5)}',
            'D=A',
            '@addr',
            'M=D'
        ]
    raise ValueError(f'{segment} {index} is ungrammatical')

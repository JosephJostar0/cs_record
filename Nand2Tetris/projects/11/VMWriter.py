from pathlib import Path

from CompilerTools import *


class VMWriter:
    def __init__(self, outPath: Path):
        self.outPath = outPath
        self.file = open(self.outPath, 'w')

    def close(self):
        # Close the output file.
        self.file.close()

    def writePush(self, segment: str, index: int):
        # Writes a VM push command.
        self.file.write(f'push {segment} {index}\n')

    def writePop(self, segment: str, index: int):
        # Writes a VM pop command.
        self.file.write(f'pop {segment} {index}\n')

    def writeArithmetic(self, command: str):
        # Writes a VM arithmetic-logical command.
        self.file.write(command + '\n')

    def writeLabel(self, label: str):
        # Writes a VM label command.
        self.file.write(label + '\n')

    def writeGoto(self, label: str):
        # Writes a VM goto command.
        self.file.write(f"goto {label}\n")

    def writeIf(self, label: str):
        # Writes a VM if-goto command.
        self.file.write(f"if-goto {label}\n")

    def writeCall(self, name: str, nArgs: int):
        # Writes a VM call command.
        self.file.write(f"call {name} {nArgs}\n")

    def writeFunction(self, name: str, nLocals: int):
        # Writes a VM function command.
        self.file.write(f'function {name} {nLocals}\n')

    def writeReturn(self):
        # Writes a VM return command.
        self.file.write('return\n')

import sys
from pathlib import Path

from CompilerTools import *
from JackTokenizer import JackTokenizer
from CompilationEngine import CompilationEngine


class JackCompiler:
    def __init__(self, inPath: Path):
        self.setAll(inPath)

    def setAll(self, inPath: Path):
        if inPath is None or not inPath.exists():
            raise FileExistsError(f'{inPath} is not a valid file/dir')
        self.inPath = inPath

    def runJackAnalyzer(self, isSave: bool = False):
        def runBoth(inPath: Path):
            tokenizer = JackTokenizer(inPath)
            tokenizer.runTokenizer()
            compilationEngine = CompilationEngine(
                inPath, tokenizer.results, isSave)
            compilationEngine.runCompilationEngine()

        if self.inPath.is_file():
            runBoth(self.inPath)
        elif self.inPath.is_dir():
            for item in self.inPath.iterdir():
                if item.is_file() and item.suffix == '.jack':
                    runBoth(item)
        else:
            raise ValueError(f'{self.inPath} is invalid.')


def getJackAnalyzer():
    def getPaths() -> tuple[Path, Path]:
        arguments = sys.argv

        if len(arguments) < 2:
            raise IndexError("Please provide target file_path argument")
        if len(arguments) > 2:
            raise Exception("Too Many arguments")

        inPath = Path(arguments[1])
        if not inPath.exists():
            raise FileNotFoundError(f"File/Dir '{inPath}' does not exist.")
        return inPath

    return JackCompiler(getPaths())


if __name__ == '__main__':
    getJackAnalyzer().runJackAnalyzer(True)

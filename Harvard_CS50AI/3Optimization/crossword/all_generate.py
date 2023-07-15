import sys
from crossword import Variable, Crossword
from time import time

ans = list()


class CrosswordCreator():

    def __init__(self, crossword):
        """
        Create new CSP crossword generate.
        """
        self.crossword = crossword
        self.domains = {
            var: self.crossword.words.copy()
            for var in self.crossword.variables
        }

    def letter_grid(self, assignment):
        """
        Return 2D array representing a given assignment.
        """
        letters = [
            [None for _ in range(self.crossword.width)]
            for _ in range(self.crossword.height)
        ]
        for variable, word in assignment.items():
            direction = variable.direction
            for k in range(len(word)):
                i = variable.i + (k if direction == Variable.DOWN else 0)
                j = variable.j + (k if direction == Variable.ACROSS else 0)
                letters[i][j] = word[k]
        return letters

    def print(self, assignment):
        """
        Print crossword assignment to the terminal.
        """
        letters = self.letter_grid(assignment)
        for i in range(self.crossword.height):
            for j in range(self.crossword.width):
                if self.crossword.structure[i][j]:
                    print(letters[i][j] or " ", end="")
                else:
                    print("█", end="")
            print()

    def save(self, assignment, filename):
        """
        Save crossword assignment to an image file.
        """
        from PIL import Image, ImageDraw, ImageFont
        cell_size = 100
        cell_border = 2
        interior_size = cell_size - 2 * cell_border
        letters = self.letter_grid(assignment)

        # Create a blank canvas
        img = Image.new(
            "RGBA",
            (self.crossword.width * cell_size,
             self.crossword.height * cell_size),
            "black"
        )
        font = ImageFont.truetype("assets/fonts/OpenSans-Regular.ttf", 80)
        draw = ImageDraw.Draw(img)

        for i in range(self.crossword.height):
            for j in range(self.crossword.width):

                rect = [
                    (j * cell_size + cell_border,
                     i * cell_size + cell_border),
                    ((j + 1) * cell_size - cell_border,
                     (i + 1) * cell_size - cell_border)
                ]
                if self.crossword.structure[i][j]:
                    draw.rectangle(rect, fill="white")
                    if letters[i][j]:
                        _, _, w, h = draw.textbbox(
                            (0, 0), letters[i][j], font=font)
                        draw.text(
                            (rect[0][0] + ((interior_size - w) / 2),
                             rect[0][1] + ((interior_size - h) / 2) - 10),
                            letters[i][j], fill="black", font=font
                        )

        img.save(filename)

    def solve(self):
        """
        Enforce node and arc consistency, and then solve the CSP.
        """
        self.enforce_node_consistency()
        self.ac3()
        self.backtrack(dict())

    def enforce_node_consistency(self):
        """
        Update `self.domains` such that each variable is node-consistent.
        (Remove any values that are inconsistent with a variable's unary
         constraints; in this case, the length of the word.)
        """
        for var in self.domains.keys():
            copy = self.domains[var].copy()
            for val in copy:
                if len(val) != var.length:
                    self.domains[var].remove(val)

    def revise(self, x: Variable, y: Variable) -> bool:
        """
        Make variable `x` arc consistent with variable `y`.
        To do so, remove values from `self.domains[x]` for which there is no possible corresponding value for `y` in `self.domains[y]`.

        Return True if a revision was made to the domain of `x`; return
        False if no revision was made.
        """
        idx, idy = self.crossword.overlaps[x, y]
        is_revision = False
        copy = self.domains[x].copy()
        for valx in copy:
            is_confict = True
            for valy in self.domains[y]:
                if valx[idx] == valy[idy]:
                    is_confict = False
                    break
            if is_confict:
                is_revision = True
                self.domains[x].remove(valx)
        return is_revision

    def ac3(self, arcs: list = None) -> bool:
        """
        Update `self.domains` such that each variable is arc consistent.
        If `arcs` is None, begin with initial list of all arcs in the problem.
        Otherwise, use `arcs` as the initial list of arcs to make consistent.

        Return True if arc consistency is enforced and no domains are empty;
        return False if one or more domains end up empty.
        """
        if arcs is None:
            arcs = list()
            for varx in self.crossword.variables:
                neighbors = self.crossword.neighbors(varx)
                for vary in neighbors:
                    arcs.append((varx, vary))
        while len(arcs) != 0:
            varx, vary = arcs.pop()
            if self.revise(varx, vary):
                if len(self.domains[varx]) == 0:
                    return False
                for it in self.crossword.neighbors(varx):
                    if (it, varx) not in arcs:
                        arcs.append((it, varx))
        return True

    def assignment_complete(self, assignment: dict) -> bool:
        """
        Return True if `assignment` is complete (i.e., assigns a value to each
        crossword variable); return False otherwise.
        """
        return len(self.domains) == len(assignment)

    def consistent(self, assignment: dict) -> bool:
        """
        Return True if `assignment` is consistent (i.e., words fit in crossword puzzle without conflicting characters); return False otherwise.
        """
        crossword = self.crossword
        for var, value in assignment.items():
            # check distinct value
            if len(assignment) != len(set(assignment.values())):
                return False

            # check conflicting characters
            for var_y in crossword.neighbors(var):
                idx, idy = crossword.overlaps[var, var_y]
                if var_y in assignment.keys():
                    val_y = assignment[var_y]
                    if value[idx] != val_y[idy]:
                        return False
        return True

    def order_domain_values(self, var: Variable, assignment: dict) -> list:
        """
        Return a list of values in the domain of `var`, in order by
        the number of values they rule out for neighboring variables.
        The first value in the list, for example, should be the one
        that rules out the fewest values among the neighbors of `var`.
        """
        return list(self.domains[var])

    def select_unassigned_variable(self, assignment: dict) -> Variable:
        """
        Return an unassigned variable not already part of `assignment`.
        Choose the variable with the minimum number of remaining values
        in its domain. If there is a tie, choose the variable with the highest degree. If there is a tie, any of the tied variables are acceptable return values.
        """
        unassigned = set(self.domains.keys()) - set(assignment.keys())
        return list(unassigned)[0]

    def backtrack(self, assignment: dict):
        """
        Using Backtracking Search, take as input a partial assignment for the crossword and return a complete assignment if possible to do so.

        `assignment` is a mapping from variables (keys) to words (values).

        If no assignment is possible, return None.
        """
        if self.assignment_complete(assignment):
            ans.append(assignment)
            return
        var = self.select_unassigned_variable(assignment)
        vals = self.order_domain_values(var, assignment)
        for val in vals:
            assignment[var] = val
            if self.consistent(assignment):
                self.backtrack(assignment.copy())


def main():

    # Check usage
    if len(sys.argv) not in [3, 4]:
        sys.exit("Usage: python generate.py structure words [output]")

    # Parse command-line arguments
    structure = sys.argv[1]
    words = sys.argv[2]
    output = sys.argv[3] if len(sys.argv) == 4 else None

    # Generate crossword
    crossword = Crossword(structure, words)
    creator = CrosswordCreator(crossword)
    creator.solve()

    # Print result
    if len(ans) == 0:
        print("No solution.")
    else:
        cnt = 0
        for assignment in ans:
            creator.print(assignment)
            print()
            if output:
                name = output.split('.')[0]
                creator.save(assignment, name+f'_{cnt}.png')
                cnt += 1
        print(f'\ntotal = {cnt}')


if __name__ == "__main__":
    main()

"""
Tic Tac Toe Player
"""

import math

X = "X"
O = "O"
EMPTY = None

next_step = dict()
point = dict()


def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY], [EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY]]


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    cnt_x = 0
    cnt_o = 0
    for it in board:
        for it2 in it:
            if it2 != EMPTY:
                if it2 == X:
                    cnt_x += 1
                else:
                    cnt_o += 1
    return X if cnt_x == cnt_o else O


def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """
    actions = set()
    for i in range(len(board)):
        for j in range(len(board[i])):
            if board[i][j] == EMPTY:
                actions.add((i, j))
    return actions


def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """
    copy = list()
    for it in board:
        copy.append(it.copy())
    copy[action[0]][action[1]] = player(board)
    return copy


def winner(board):
    """
    Returns the winner of the game, if there is one.
    """
    lines = [
        [(0, 0), (0, 1), (0, 2)],
        [(1, 0), (1, 1), (1, 2)],
        [(2, 0), (2, 1), (2, 2)],
        [(0, 0), (1, 0), (2, 0)],
        [(0, 1), (1, 1), (2, 1)],
        [(0, 2), (1, 2), (2, 2)],
        [(0, 0), (1, 1), (2, 2)],
        [(0, 2), (1, 1), (2, 0)],
    ]
    for l in lines:
        if board[l[0][0]][l[0][1]] == board[l[1][0]][l[1][1]]:
            if board[l[0][0]][l[0][1]] == board[l[2][0]][l[2][1]]:
                if board[l[0][0]][l[0][1]] is not EMPTY:
                    return board[l[0][0]][l[0][1]]
    return None


def terminal(board):
    """
    Returns True if game is over, False otherwise.
    """
    if winner(board) is not None:
        return True
    for it in board:
        if EMPTY in it:
            return False
    return True


def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """
    win_player = winner(board)
    if win_player is None:
        return 0
    return 1 if win_player == X else -1


def minimax(board):
    """
    Returns the optimal action for the current player on the board.
    """
    if terminal(board):
        return None

    key = get_key(board)
    if key in next_step.keys():
        return next_step[key]

    margin = -math.inf if player(board) == X else math.inf
    get_score(board, margin)    
    return next_step[key]


def get_key(board):
    return tuple(map(tuple, board))


def is_acceptable(score, margin, my_role):
    return score > margin if my_role == X else score < margin


def get_score(board, pre):
    if terminal(board):
        return utility(board)
    key = get_key(board)
    if key in point.keys():
        return point[key]

    my_role = player(board)
    margin = -math.inf if my_role == X else math.inf
    optimal = None
    for action in actions(board):
        new_board = result(board, action)
        score = get_score(new_board, margin)
        if is_acceptable(score, margin, my_role):
            margin = score
            optimal = action
    point[key] = margin
    next_step[key] = optimal
    return margin

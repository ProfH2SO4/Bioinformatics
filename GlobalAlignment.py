"""
Subject: DSIB01 Introduction to Bioinformatics
Task: Coding Dynamic Algorithm (Global Align)
"""


class Seq:
    def __init__(self):
        print("Please Enter sequence one:")
        self.seq1 = input()
        print("Please Enter second sequence:")
        self.seq2 = input()


def board_matrix():
    matrix = []
    for nk1 in range(len(seq.seq2) + 1):
        matrix_row = []
        for nk2 in range(len(seq.seq1) + 1):
            matrix_row.append('  ')
        matrix.append(matrix_row)
    for i in range(len(matrix[0])):
        matrix[0][i] = -i
    for j in range(len(matrix)):
        matrix[j][0] = -j
    return matrix


def vis_matrix(matrix):
    print('    ', end='  ')
    for nk1 in seq.seq1:
        print('  ', end='')
        print(nk1, end='  ')
    print()
    for i in range(len(matrix)):
        for dash in range(len(matrix[0])):
            print('  --', end=' ')
        print()
        if i == 0: print(' ', end='')  # first row
        if i != 0:
            print(seq.seq2[i - 1], end='')
        for j in range(len(matrix[0])):
            if type(matrix[i][j]) == int:  # for better visual alignment(cuz -1 and 1 diff spaces)
                if matrix[i][j] >= 0:
                    print('| ', matrix[i][j], end=' ')
                else:
                    print('|', matrix[i][j], end=' ')
            else:
                print('|', matrix[i][j], end=' ')
        print()
    print('  ---' * len(matrix[0]), end=' ')
    print()
    print("--" * len(seq.seq1) * len(seq.seq1), end='')
    print()
    return matrix


def print_score(matrix):
    if matrix[len(seq.seq2)][len(seq.seq1)] < matrix[len(seq.seq2)][len(seq.seq1) - 1]:
        print("Matrix score:", matrix[len(seq.seq2)][len(seq.seq1) - 1])
    else:
        print("Matrix score:", matrix[len(seq.seq2)][len(seq.seq1)])


def find_highest(num1, num2, num3):
    return sorted([num1, num2, num3])


def solve_matrix():
    matrix = vis_matrix(board_matrix())
    for row in range(1, len(seq.seq2) + 1):
        for col in range(1, len(seq.seq1) + 1):
            highest = find_highest(matrix[row - 1][col - 1], matrix[row][col - 1], matrix[row - 1][col])[2]
            if highest == matrix[row - 1][col - 1] and seq.seq2[row - 1] == seq.seq1[col - 1]:
                matrix[row][col] = highest + 1
            elif highest == matrix[row][col - 1]:
                matrix[row][col] = highest - 1
            else:
                matrix[row][col] = highest - 1
    vis_matrix(matrix)
    return matrix


def back_propagation(matrix):
    print_score(matrix)
    col_move = 0
    row_move = 0
    for row in range(len(seq.seq2) - row_move, 1, -1):
        for col in range(len(seq.seq1) - col_move, 1, -1):
            highest = find_highest(matrix[row][col - 1], matrix[row - 1][col], matrix[row - 1][col - 1])[2]
            if matrix[row - 1][col - 1] == highest:  # diagonal priority
                pass
            elif matrix[row][col - 1] == highest:  # check left
                p1_fin_seq2 = seq.seq2[:row]
                p2_fin_seq2 = seq.seq2[row:]
                seq.seq2 = p1_fin_seq2 + '_' + p2_fin_seq2
                col_move += 1
            elif matrix[row - 1][col] == highest:  # check up
                p1_fin_seq1 = seq.seq1[:col]
                p2_fin_seq1 = seq.seq1[col:]
                seq.seq1 = p1_fin_seq1 + '_' + p2_fin_seq1
                row_move += 1
            col_move += 1
            break
    if len(seq.seq1) < len(seq.seq2):
        seq.seq1 = '_' + seq.seq1
    elif len(seq.seq1) > len(seq.seq2):
        seq.seq2 = '_' + seq.seq2
    print("First sequence:")
    print(seq.seq1)
    print("Second sequence:")
    print(seq.seq2)


if __name__ == "__main__":
    seq = Seq()
    back_propagation(solve_matrix())

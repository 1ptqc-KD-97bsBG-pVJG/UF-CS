# create board using two dimensional list
def initialize_board(num_cols, num_rows):
    board = []
    for i in range(1, num_rows + 1):
        inner = []
        for j in range(1, num_cols + 1):
            inner.append("-")
        board.append(inner)
    return board

# print two dimensional list in for of a board
def print_board(board):
    for i in board:
        for j in i:
            print(j, end = ' ')
        print('')

# insert chip to bottom-most empty row of user specified column
def insert_chip(board = ['zybooks'], col = 1, chip_type = 'x'):
    for i in range(len(board) - 1, -1, -1):
        if board[i][col] == '-':
            board[i][col] = chip_type
            # return selected number for use in check_if_winner function
            return i

def check_if_winner(board, col, row, chip_type):
# create two strings of the row and column which the chip was inserted into
    horizontal, vertical = "", ""
    for i in board[row]:
            horizontal += i
    for i in range(0, len(board)):
        vertical += board[i][col]
    # check if there are four consecutive chips in either row or column
    if (chip_type * 4) in (vertical + " " + horizontal):
        return True

def main():
    # start game
    board = []
    board_height, board_width = 0, 0
    board_height = int(input('What would you like the height of the board to be? '))
    board_width = int(input('What would you like the length of the board to be? '))
    board = initialize_board(board_width, board_height)
    print_board(board)
    print('\nPlayer 1: x')
    print('Player 2: o\n')
    
    # main game loop
    for i in range(0, (board_width * board_height) // 2):
        # player 1's turn
        col = int(input('\nPlayer 1: Which column would you like to choose? '))
        # insert chip and check if there is a winner
        if not check_if_winner(board, col, insert_chip(board, col, 'x'), 'x'):
            print_board(board)
        else:
            print_board(board)
            print("Player 1 won the game!")
            quit()
        # player 2's turn
        col = int(input('\nPlayer 2: Which column would you like to choose? '))
        # insert chip and check if there is a winner
        if not check_if_winner(board, col, insert_chip(board, col, 'o'), 'o'):
            print_board(board)
        else:
            print_board(board)
            print("Player 2 won the game!")
            quit()
    # if loop ends without a winner, print tie message
    print("Draw. Nobody wins.")
    quit()

if __name__ == '__main__':
    main()
def main():

    def initialize_board(num_cols, num_rows):
        for i in range(1, num_rows + 1):
            inner = []
            for j in range(1, num_cols + 1):
                inner.append("-")
            board.append(inner)

    def print_board(board):
        for i in board:
            for j in i:
                print(j, end = ' ')
            print('')

    def insert_chip(board, col, chip_type = 'x'):
        for i in range(len(board) - 1, -1, -1):
            if board[i][col] == '-':
                board[i][col] = chip_type
                return i

    def check_if_winner(board, col, row, chip_type = 'x'):
        horizontal, vertical = "", ""
        for i in board[row]:
                horizontal += i
        for i in range(0, board_height):
            vertical += board[i][col]
        # if (chip_type * 4) in vertical or (chip_type * 4) in horizontal:
        if (chip_type * 4) in (vertical + " " + horizontal):
            print('Winner!')
        else:
            print('No winner!')
        


    board = []
    board_height = int(input('What would you like the height of the board to be? '))
    board_width = int(input('What would you like the width of the board to be? '))
    initialize_board(board_width, board_height)
    print_board(board)
    print('Player 1: x')
    print('Player 2: o')
    # print(board)
    
    
    
    col = int(input('Player 1: Which column would you like to choose? ')) - 1
    check_if_winner(board, col, insert_chip(board, col))
    print_board(board)

    col = int(input('Player 1: Which column would you like to choose? ')) - 1
    check_if_winner(board, col, insert_chip(board, col))
    print_board(board)

    col = int(input('Player 1: Which column would you like to choose? ')) - 1
    check_if_winner(board, col, insert_chip(board, col))
    print_board(board)

    col = int(input('Player 1: Which column would you like to choose? ')) - 1
    check_if_winner(board, col, insert_chip(board, col))
    print_board(board)

    col = int(input('Player 1: Which column would you like to choose? ')) - 1
    check_if_winner(board, col, insert_chip(board, col))
    print_board(board)
    




if __name__ == '__main__':
    main()



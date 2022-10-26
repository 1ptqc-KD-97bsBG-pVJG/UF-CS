def main():

    def print_board(num_rows, num_cols):
        inner = []
        outer = []
        for i in range(1, num_cols):
            for j in range(1, num_rows):
                inner.append("-")
            outer.append(inner)
        print(outer)




    board_height = int(input('What would you like the height of the board to be? '))
    board_width = int(input('What would you like the width of the board to be? '))
    print_board(board_width, board_height)




if __name__ == '__main__':
    main()



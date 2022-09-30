from console_gfx import ConsoleGfx 

#menu:
# 0. Exit
# 1. Load File
# 2. Load Test Image
# 3. Read RLE String
# 4. Read RLE Hex String
# 5. Read Data Hex String
# 6. Display Image
# 7. Display RLE String
# 8. Display Hex RLE Data
# 9. Display Hex Flat Data

# Select a Menu Option:

def main():
    def menu_print():
        print('RLE Menu')
        print('-' * 8)
        print('0. Exit')
        print('1. Load File')
        print('2. Load Test Image')
        print('3. Read RLE String')
        print('4. Read RLE Hex String')
        print('5. Read Data Hex String')
        print('6. Display Image')
        print('7. Display RLE String')
        print('8. Display Hex RLE Data')
        print('9. Display Hex Flat Data')
        menu_select()

    def menu_select():
        selection = input('Select a Menu Option: ')
    
    
    
    print('Welcome to the RLE image encoder!')
    ConsoleGfx.display_image(ConsoleGfx.test_rainbow)
    menu_print()
    


if __name__ == '__main__':
    main()
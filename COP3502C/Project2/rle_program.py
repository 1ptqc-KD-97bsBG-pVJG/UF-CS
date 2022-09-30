from console_gfx import ConsoleGfx 
import os

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
    global image_data
    image_data = []
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
        if selection in ('0', 'exit'):
            print('THIS IS A TEMPORARY EXIT MESSAGE')
            quit()
        elif selection in ('1', 'load file'):
            user_file = input('Enter the name of the file: ')
            # print(user_file)
            global image_data
            image_data = ConsoleGfx.load_file(str(user_file))
            print(image_data)
            # ConsoleGfx.load_file('testfiles/uga.gfx')
            menu_print()
        elif selection in ('2', 'load test image'):
            ConsoleGfx.display_image(ConsoleGfx.test_image)
        
        elif selection in ('6', 'display image'):
            ConsoleGfx.display_image(image_data)
    
    
    
    print('Welcome to the RLE image encoder!')
    ConsoleGfx.display_image(ConsoleGfx.test_rainbow)
    menu_print()
    


if __name__ == '__main__':
    main()
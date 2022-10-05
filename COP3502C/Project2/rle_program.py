from console_gfx import ConsoleGfx 
import os

def main():
    # set initial conditions
    global image_data
    image_data = None
    
    # print menu function
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

    # prompt user for input and perform appropriate action
    def menu_select():
        selection = input('Select a Menu Option: ')
        if selection in ('0', 'exit'):
            print('THIS IS A TEMPORARY EXIT MESSAGE')
            quit()
        elif selection in ('1', 'load file'):
            user_file = input('Enter the name of the file: ')
            global image_data
            image_data = ConsoleGfx.load_file(user_file)
            menu_print()
        elif selection in ('2', 'load test image'):
            ConsoleGfx.display_image(ConsoleGfx.test_image)
        elif selection in ('6', 'display image'):
            ConsoleGfx.display_image(image_data)
    
    # run the program
    print('Welcome to the RLE image encoder!')
    ConsoleGfx.display_image(ConsoleGfx.test_rainbow)
    menu_print()
    
if __name__ == '__main__':
    main()
# Example:

# Decoding Menu 
# ------------- 
# 1. Decode hexadecimal 
# 2. Decode binary 
# 3. Convert binary to hexadecimal 
# 4. Quit 

# Please enter an option: 1 
# Please enter the numeric string to convert: 0x4321 
# Result: 17185 

def main():

    def menu():
        print('Decoding Menu')
        print('-------------')
        print('1. Decode hexadecimal')
        print('2. Decode binary')
        print('3. Convert binary to hexadecimal')
        print('4. Quit')
        selection = input('Please enter an option: ')
        numeric_input = input('Please enter the numeric string to convert: ')
        
        # remove prefix
        if numeric_input[1] in ('x', 'b'):
            numeric_input = numeric_input[2:]

        if selection.lower() in ('1', 'decode hexadecimal'):
            print(hex_char_decode(numeric_input))
        elif selection.lower() in ('2', 'decode binary'):
            print(hex_string_decode(numeric_input))
        elif selection.lower() in ('3', 'convert binary to hexadecimal'):
            print(binary_string_decode(numeric_input))
        elif selection.lower() in ('4', 'quit'):
            quit()
    
    def hex_char_decode(digit):
        print('temp')

    def hex_string_decode(hex):
        print('temp')

    def binary_string_decode(binary):
        print('temp')

    def binary_to_hex(binary):
        print('temp')



if __name__ == '__main__':
    main()
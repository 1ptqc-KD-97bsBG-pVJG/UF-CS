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
        numeric_input = input('Please enter the numeric string to convert: ').lower()
        
        # remove prefix
        if numeric_input[1] in ('x', 'b'):
            numeric_input = numeric_input[2:]
        
        # convert to list
        input_list = list(map(str, numeric_input))
        
        # convert hex letters to numbers
        formatted_list = []
        for num in input_list:
            try:
                key = ['a', 'b', 'c', 'd', 'e', 'f']
                formatted_list.append(key.index(num) + 10)
            except:
                formatted_list.append(num)
        
        formatted_list = list(map(int, formatted_list))

       # call the correct function for conversion
        if selection.lower() in ('1', 'decode hexadecimal'):
            print(hex_string_decode(formatted_list))
        elif selection.lower() in ('2', 'decode binary'):
            print(binary_string_decode(formatted_list))
        elif selection.lower() in ('3', 'convert binary to hexadecimal'):
            print(binary_to_hex(formatted_list))
        elif selection.lower() in ('4', 'quit'):
            quit()
    
    def hex_string_decode(digit):
        result = 0
        for i in range(0, len(digit)):
            result += digit[i] * 16 ** (len(digit) - 1 - i)
        return result

    def binary_string_decode(binary):
        print('temp')

    def binary_to_hex(binary):
        print('temp')

    menu()



if __name__ == '__main__':
    main()
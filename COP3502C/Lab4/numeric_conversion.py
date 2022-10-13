def main():

    def menu():
        print('Decoding Menu')
        print('-------------')
        print('1. Decode hexadecimal')
        print('2. Decode binary')
        print('3. Convert binary to hexadecimal')
        print('4. Quit')
        print()
        selection = input('Please enter an option: ')
        
        if selection.lower() in ('4', 'quit'):
            print('Goodbye!')
            quit()
        
        numeric_input = input('Please enter the numeric string to convert: ').lower()
        
        # format input into a list using format_input() function
        formatted_list = format_input(numeric_input)

       # call the correct function for conversion
        if selection.lower() in ('1', 'decode hexadecimal'):
            print(f'Result: {hex_string_decode(formatted_list)}')
        elif selection.lower() in ('2', 'decode binary'):
            print(f'Result: {binary_string_decode(formatted_list)}')
        elif selection.lower() in ('3', 'convert binary to hexadecimal'):
            print(f'Result: {binary_to_hex(formatted_list)}')
        
        # call menu() function again
        menu()

    # inital call to menu
    menu()

# function for formatting input so the program can easily use it
def format_input(input_string):
    # remove prefix
    if input_string[1] in ('x', 'b'):
        input_string = input_string[2:]
    
    # convert to list
    input_list = list(map(str, input_string))
    
    # convert hex letters to numbers
    formatted_list = []
    for num in input_list:
        try:
            key = ['a', 'b', 'c', 'd', 'e', 'f']
            formatted_list.append(key.index(num.lower()) + 10)
        except:
            formatted_list.append(num)
    
    # convert list back into list of ints
    formatted_list = list(map(int, formatted_list))
    return formatted_list

def hex_char_decode(digit):
    result = 0
    try:
        str(digit)
        key = ['a', 'b', 'c', 'd', 'e', 'f']
        result = key.index(digit) + 10
    except:
        result = digit
    return int(result)

def hex_string_decode(digit):
    digit = format_input(digit)
    result = 0
    # iterate over list and convert each element to decimal using powers of 16
    for i in range(0, len(digit)):
        result += digit[i] * 16 ** (len(digit) - 1 - i)
    return result

# iterate over list and convert each element to decimal using powers of 2
def binary_string_decode(binary):
    # zybooks sucks so much, format_input() should be done before calling the function but nooooo
    binary = format_input(binary)
    result = 0
    for i in range(0, len(binary)):
        result += binary[i] * 2 ** (len(binary) - 1 - i)
    return result

# convert to decimal, then convert to hex
def binary_to_hex(binary):
    decimal_input = binary_string_decode(format_input(binary))
    current_val = decimal_input
    result = []
    # convert decimal to hex
    # any loop would do but this eliminates possiblity of infinite loop
    for i in range(0, decimal_input):
        current_mod = current_val % 16
        # convert hex numbers to letters
        if current_mod > 9:
            key = ['a', 'b', 'c', 'd', 'e', 'f']
            result.insert(0, key[current_mod - 10].capitalize())
            current_val = current_val // 16
        elif 0 < current_mod < 10: 
            current_val = current_val // 16
            result.insert(0, current_mod)
        else:
            break
    # convert list to string
    return ''.join(map(str, result))

if __name__ == '__main__':
    main()
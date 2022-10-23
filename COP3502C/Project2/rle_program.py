from console_gfx import ConsoleGfx 
import os

# Translates data (RLE or raw) a hexadecimal string (without delimiters).
def to_hex_string(data):
    result = []
    for i in data:
        if i > 9:
            key = ['a', 'b', 'c', 'd', 'e', 'f']
            result.append(key[i - 10])
        else:
            result.append(i)
    return ''.join(str(e) for e in result)

# Returns number of runs of data in an image data set; double this result for length of encoded (RLE) list.
def count_runs(flat_data):
    runs = 1
    num = 0
    for i in range(len(flat_data) - 1):
        if flat_data[i] != flat_data[i + 1]:
            runs += 1
        else:
            num += 1
        if num == 15:
            runs += 1
            num = 0
    return runs

# Returns encoding (in RLE) of the raw data passed in; used to generate RLE representation of a data.
def encode_rle(flat_data):
    amount = 1
    integer = 0
    result = []
    for i in range(0, len(flat_data) - 1):
        if (flat_data[i] == flat_data[i + 1]) and amount != 15:
            integer = flat_data[i]
            amount += 1
        else:
            integer = flat_data[i]
            result.extend([amount, integer])
            amount = 1
    integer = flat_data[len(flat_data) - 1]
    result.extend([amount, integer])
    return result

# Returns decompressed size RLE data; used to generate flat data from RLE encoding. 
def get_decoded_length(rle_data):
    result = 0
    for i in range(0, len(rle_data) - 1, 2):
        result += rle_data[i]
    return result

# Returns the decoded data set from RLE encoded data. This decompresses RLE data for use.
def decode_rle(rle_data):
    result = []
    for i in range(0, len(rle_data) - 1, 2):
        for j in range(0, rle_data[i]):
            result.append(rle_data[i + 1])
    return result

# Translates a string in hexadecimal format into byte data
def string_to_data(data_string):
    result = []
    for i in data_string:
        try:
            result.append(int(i))
        except:
            # convert from letter to number
            key = ['a', 'b', 'c', 'd', 'e', 'f']
            result.append(key.index(i.lower()) + 10)
    return result

# Translates RLE data into human-readable representation.
def to_rle_string(rle_data):
    result = ""
    for i in range(0, len(rle_data) - 1, 2):
        result += str(rle_data[i])
        if rle_data[i + 1] > 9:
            try:
                # convert from number to letter
                key = ['a', 'b', 'c', 'd', 'e', 'f']
                result += str(key[(rle_data[i + 1]) - 10])
            except:
                result += str(rle_data[i + 1])
        else:
            result += str(rle_data[i + 1])
        try:
            if rle_data[i + 2]:
                result += ":"
        except:
            continue
    return result

def string_to_rle(rle_string):
    result = []
    raw_list = rle_string.split(":")
    for i in raw_list:
        result.append(int(i[0:(len(i) - 1)]))
        try:
            # convert from letter to number
            key = ['a', 'b', 'c', 'd', 'e', 'f']
            result.append(key.index(i[-1].lower()) + 10)
        except:
            result.append(int(i[-1]))
    return result

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
        selection = input('Select a Menu Option: ').lower()
        if selection in ('0', 'exit'):
            print('THIS IS A TEMPORARY EXIT MESSAGE')
            quit()
        elif selection in ('1', 'load file'):
            user_file = input('Enter the name of the file: ')
            global image_data
            image_data = ConsoleGfx.load_file(user_file)
            print(image_data)
        elif selection in ('2', 'load test image'):
            ConsoleGfx.display_image(ConsoleGfx.test_image)
        elif selection in ('3', 'read rle string'):
            user_input = input('Enter an RLE string to be decoded: ')
            # translate to RLE format, then decode
            image_data = decode_rle(string_to_rle(user_input))
        elif selection in ('4', 'read rle hex string'):
            user_input = input('Enter the hex string holding RLE data: ')
            # translate from hex string to RLE, then decode
            image_data = decode_rle(string_to_data(user_input))
        elif selection in ('5', 'read data hex string'):
            user_input = input('Enter the hex string holding flat data: ')
            image_data = string_to_data(user_input)
        elif selection in ('6', 'display image'):
            ConsoleGfx.display_image(image_data)
            quit()
        elif selection in ('7', 'display rle string'):
            # encode image data to RLE, then convert to human-readable RLE format
            print(f'RLE hex values: {to_rle_string(encode_rle(image_data))}')
        elif selection in ('8', 'display hex rle data'):
            # encode image data to RLE, then convert to hex
            print(f'RLE hex values: {to_hex_string(encode_rle(image_data))}')
        elif selection in ('9', 'display hex flat data'):
            # convert full image data to hex to produce flat hex
            print(f'Flat hex values: {to_hex_string(image_data)}')
        menu_print()
    
    # run the program
    print('Welcome to the RLE image encoder!')
    ConsoleGfx.display_image(ConsoleGfx.test_rainbow)
    menu_print()
    
if __name__ == '__main__':
    main()
import math

def main():
    # set inital conditions
    global continue_game 
    continue_game = True
    results = []
    result = 0.0
    print(f'Current Result: {result}')

    # menu function
    def menu(skip_menu=False):
        # allow skipping of printing menu
        if not skip_menu:
            print("Calculator Menu")
            print("---------------")
            print("0. Exit Program")
            print("1. Addition")
            print("2. Subtraction")
            print("3. Multiplication")
            print("4. Division")
            print("5. Exponentiation")
            print("6. Logarithm")
            print("7. Display Average")

        # prompt for menu choice
        operation = input("Enter Menu Selection: ")

        # there is definitely a better way to do the following, but this works for now

        # exit program
        if operation in ('0', 'exit'):
            global continue_game
            continue_game = False
            print('Thanks for using this calculator. Goodbye!')

        # display average option
        elif operation in ('7', 'display average'):
            # check if averaging would make sense
            if len(results) > 0:
                print(f'Sum of calculations: {sum(results)}')
                print(f'Number of calculations: {len(results)}')
                print(f'Average of calculations: {round((sum(results)) / len(results), 2)}')
                menu(True)
            else:
                print('Error: No calculations yet to average!')
                menu(True)
        else:
            # I don't like how I did this but it works
            try:
                if int(operation) in range(1,7):
                    # prompt for operand
                    first_op = input('Enter first operand: ')
                    second_op = input('Enter second operand: ')

                    # allow user to use previous result in calculation
                    if first_op.lower() == 'result':
                        first_op = results[-1]
                    elif second_op.lower() == 'result':
                        second_op = results[-1]
                    
                    # format operands
                    first_op = float(first_op)
                    second_op = float(second_op)
                    
                    calculate(operation, first_op, second_op)
                else:
                    print("Error: Invalid selection!")
                    menu(True)
            except ValueError:
                print("Error: Invalid selection!")
                menu(True)

    # function for performing calculations
    def calculate(operation, first_op, second_op):
        if operation in ('1', 'addition'):
            result = first_op + second_op
        elif operation in ('2', 'subtraction'):
            result = first_op - second_op
        elif operation in ('3', 'multiplication'):
            result = first_op * second_op
        elif operation in ('4', 'division'):
            result = first_op / second_op
        elif operation in ('5', 'exponentiation'):
            result = first_op ** second_op
        elif operation in ('6', 'logarithm'):
            result = math.log(second_op, first_op)
        
        print(f'Current Result: {result}')
        results.append(result)
        menu()

    # inital menu call
    menu()

if __name__ == '__main__':
    main()
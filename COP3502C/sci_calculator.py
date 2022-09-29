import math

def main():
    global continue_game 
    continue_game = True

    def menu(skip_menu=False):
        # print calculator menu
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
        operation = int(input("Enter Menu Selection: "))
        

        if operation != 0:
            # prompt for operand
            first_op = float(input("Enter first operand: "))
            second_op = float(input("Enter second operand: "))
            calculate(operation, first_op, second_op)
        else:
            global continue_game
            continue_game = False
    
    def calculate(operation, first_op, second_op):
        # perform operation 
        if operation == 1:
            result = first_op + second_op
        elif operation == 2:
            result = first_op - second_op
        elif operation == 3:
            result = first_op * second_op
        elif operation == 4:
            result = first_op / second_op
        elif operation == 5:
            result = first_op ** second_op
        else:
            print("Error: Invalid selection! Terminating program.")
        
        print(result)
        menu()

    #main loop
    while continue_game:
        menu()
    





if __name__ == '__main__':
    main()
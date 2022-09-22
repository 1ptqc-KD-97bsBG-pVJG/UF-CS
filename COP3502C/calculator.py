# prompt for operand
first_op = float(input("Enter first operand: "))
second_op = float(input("Enter second operand: "))

# print calculator menu
print("Calculator Menu")
print("---------------")
print("1. Addition")
print("2. Subtraction")
print("3. Multiplication")
print("4. Division")

# prompt for menu choice
operation = int(input("Which operation do you want to perform? "))

# perform operation with match case
# match operation:
#     case 1:
#         print(f"The result of the operation is {first_op + second_op}. Goodbye!")
#     case 2:
#         print(f"The result of the operation is {first_op - second_op}")
#     case 3:
#         print(f"The result of the operation is {first_op * second_op}. Goodbye!")
#     case 4:
#         print(f"The result of the operation is {first_op / second_op}. Goodbye!")
#     case _:
#         print("Error: Invalid selection! Terminating program.")

# perform operation with if/elif/else because zybooks isn't on python 3.10 yet
if operation == 1:
    print(f"The result of the operation is {first_op + second_op}. Goodbye!")
elif operation == 2:
    print(f"The result of the operation is {first_op - second_op}. Goodbye!")
elif operation == 3:
    print(f"The result of the operation is {first_op * second_op}. Goodbye!")
elif operation == 4:
    print(f"The result of the operation is {first_op / second_op}. Goodbye!")
else:
    print("Error: Invalid selection! Terminating program.")
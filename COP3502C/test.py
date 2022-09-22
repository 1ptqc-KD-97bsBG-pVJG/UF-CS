#Example:
#input: 5553332222
#output:
#Country  Phone Number
#-------  ------------
#U.S.     555-333-2222

a = input("Enter a phone number: ")
area_code, prefix, line_num = a.split()

area_code = int(area_code)
prefix = int(prefix)
line_num = int(line_num)

print("Country     Phone Number")
print("-------     ------------")
print(f"U.S.        +1({area_code})-{prefix}-{line_num}")
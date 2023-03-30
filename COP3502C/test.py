#Example:
#input: 5553332222
#output:
#Country  Phone Number
#-------  ------------
#U.S.     555-333-2222

# a = input("Enter a phone number: ")
# area_code, prefix, line_num = a.split()

# area_code = int(area_code)
# prefix = int(prefix)
# line_num = int(line_num)

# print("Country     Phone Number")
# print("-------     ------------")
# print(f"U.S.        +1({area_code})-{prefix}-{line_num}")
  
class Student: 
    def __init__(self, grade): 
        self.grade = grade 
 
    @staticmethod 
    def increase_grade(grades, student, grade): 
        grades[0] += 25 
        student.grade = 100 
        grade = 101 
 
grades = [85, 80, 90] 
bob = Student(grades[1]) 
grade = grades[-1] 
Student.increase_grade(grades, bob, grade) 
print(grades[0] + bob.grade + grade)
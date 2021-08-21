from cs50 import get_string

number = "0"

while (len(number) < 13):
    number = get_string("Number: ")

number, digits = int(number), len(number)

while (number > 0):
    
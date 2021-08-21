from cs50 import get_string
import sys

# Ask for a valid input
number = '0'
while (len(number) < 10):
    number = get_string("Number: ")

digits = len(number)
sum1 = 0

# Sum all digits
for i in range(0, digits, 2):
    if ((int(number[i]) * 2) > 2):
        b = int(number[i]) * 2
        sum1 += b % 10
        sum1 += int(b / 10)
    else:
        sum1 += int(number[i]) * 2

# Sum other digits
for i in range(1, digits, 2):
    sum1 += int(number[i])

# Check if isn't invalid
if(sum1 % 2 != 0):
    sys.exit("INVALID")

# Check if its Amex, Mastercard, Visa or don't suffice any of then
if((number[0] == "3") and (number[1] == '4' or number[1] == '7') and digits == 15):
    print("AMEX")
elif((number[0] == "5") and (int(number[1]) > 0 and int(number[1]) < 6) and digits == 16):
    print("MASTERCARD")
elif(number[0] == "4" and digits == 13 or digits == 16):
    print("VISA")
else:
    print("INVALID")

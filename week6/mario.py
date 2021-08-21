from cs50 import get_int 

# Ask for the height
n = 0
while (n < 1 or n > 8):
    n = get_int("Height: ")

# Declare variables
j = 1
y = n-1

# Print the pyramid
for i in range(1, n+1):
    print(" "*y, end="")
    print("#"*i, end="")
    print("  ", end="")
    print("#"*i, end="")
    y -= 1 
    print()
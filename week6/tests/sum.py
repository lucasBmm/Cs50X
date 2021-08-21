import sys
n = int(input("N: "))
if (n < 1 or n > 8):
    sys.exit()
for i in range(0, n):
    for j in range(0, i+1):
        print("#", end="")
    print()

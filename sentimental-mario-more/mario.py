from cs50 import get_int

# initialise variable for user input
n = 0

# Get user input - if not between 1 - 8, reprompt
while n < 1 or n > 8:
    n = get_int("Height: \n")

# Draws a pyramid of height n
for i in range(n):
    for j in range(n - (i + 1)):
        print(" ", end="")

    print("#" * (i + 1), end="")

    print("  ", end="")

    print("#" * (i + 1), end="")

    print()
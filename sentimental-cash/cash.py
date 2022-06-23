from cs50 import get_float


def main():

    dollars = get_dollars()

    cents = int(dollars * 100)

    quarters = calculate_quarters(cents)
    cents = cents - (quarters * 25)

    dimes = calculate_dimes(cents)
    cents = cents - (dimes * 10)

    nickels = calculate_nickels(cents)
    cents = cents - (nickels * 5)

    coins = int(quarters + dimes + nickels + cents)

    print(f"{coins}")


def get_dollars():
    while True:
        n = get_float("Change owed: ")
        if n > 0:
            break
    return n


def calculate_quarters(n):
    quarters = n // 25
    return quarters


def calculate_dimes(n):
    dimes = n // 10
    return dimes


def calculate_nickels(n):
    nickels = n // 5
    return nickels


def calculate_pennies(n):
    return n


if __name__ == "__main__":
    main()
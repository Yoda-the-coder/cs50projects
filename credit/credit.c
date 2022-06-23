#include <stdio.h>
#include <cs50.h>

int get_counter(long);
void print_invalid(void);
bool checksum(long, int);
void cardtype(long, int);

int main(void)
{
    // Prompt for Credit Card Number.
    long number = get_long("Number: ");

    // Count number of digits.
    int counter = get_counter(number);

    // Check length of number.
    if (counter == 13 || counter == 15 || counter == 16)
    {
        // Checks number against Luhn's algorithm.
        bool check_status = checksum(number, counter);

        // If number passes Luhn's algorithm the cardtype is worked out (ie AMEX, Visa etc...).
        if (check_status == true)
        {
            cardtype(number, counter);
        }
        else
        {
            print_invalid();
        }
    }
    // If number doesn't pass length check - invalid is returned.
    else
    {
        print_invalid();
    }
}

int get_counter(long number)    // cdFunction to count length of number.
{
    int counter = 0;
    while (number > 0)
    {
        number /= 10;
        counter++;
    }
    return counter;
}

void print_invalid(void)    // Function prints "INVALID".
{
    printf("INVALID\n");
}

bool checksum(long number, int counter)     // Function to check number against Luhn's algorithm.
{
    int total_1 = 0;
    int total_2 = 0;
    int digits = 0;

    for (int i = counter; i > 0; i--)
    {
        total_1 += number % 10;
        number /= 10;
        i--;
        digits = number % 10 * 2;
        if (digits > 9)     // Adds the digits of double digit numbers together.
        {
            while (digits > 0)
            {
                total_2 += digits % 10;
                digits /= 10;
            }
        }
        else
        {
            total_2 += digits;
        }
        number /= 10;
    }
    total_1 += total_2;
    if (total_1 % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void cardtype(long number, int counter)
{
    for (int i = 0; i < counter - 2; i++)
    {
        number /= 10;
    }
    int x = 0;
    if (number == 34 || number == 37)
    {
        x = 1;
    }
    else if (number > 50 && number < 56)
    {
        x = 2;
    }
    else
    {
        number /= 10;
        if (number == 4)
        {
            x = 3;
        }
        else
        {
            print_invalid();
        }
    }
    switch (x)
    {
        case 1:
            printf("AMEX\n");
            break;
        case 2:
            printf("MASTERCARD\n");
            break;
        case 3:
            printf("VISA\n");
            break;
    }
}
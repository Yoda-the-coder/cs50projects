#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>

bool only_digits(string key);
char rotate(char k, int key);

int main(int argc, string argv[])
{
    if (argc != 2)  // If anything other than 1 command line argument - returns 1.
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    if (only_digits(argv[1]) == false)   // Calls function to check digits - passes over last array in argv[] as a string.
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        int key = atoi(argv[1]);
        string plain_text = get_string("plaintext:  ");
        string cipher_text = plain_text;
        int j = strlen(plain_text);

        for (int i = 0; i < j; i++) // Iterates through the plain text, encrypting each char.
        {
            cipher_text[i] = rotate(plain_text[i], key);
        }

        printf("ciphertext: %s\n", cipher_text);    // Prints ciphertext.
        return 0;
    }
}

bool only_digits(string key)    // Function to check string characters for digits.
{
    int j = strlen(key);    // Sets variable J to length of key.
    for (int i = 0; i < j; i++) // For loop iterates over each character of key, checking whether digit.
    {
        if (isdigit(key[i]) == 0)
        {
            return false;
        }
    }
    return true;
}

char rotate(char k, int key)
{
    char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    if (isalpha(k))
    {
        if (islower(k)) //If lower, char is between 97 (a) - 122 (z)
        {
            k -= 97;
            k = (k + key) % 26;
            k = tolower(alphabet[(int) k]);
        }
        else
        {
            k -= 65;
            k = (k + key) % 26;
            k = toupper(alphabet[(int) k]);
        }
    }
    return k;
}
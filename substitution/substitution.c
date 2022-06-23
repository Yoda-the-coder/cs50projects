#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int string_check(int argc, string argv[]);
string cipher(string argv, string plaintext);

int main(int argc, string argv[])
{
    if (string_check(argc, argv) == 1)  // Calls function to check command line argument.
    {
        return 1;
    }

    string plaintext = get_string("plaintext: ");   // Prompts user for plaintext.

    string ciphertext = cipher(argv[1], plaintext); // Calls function to encrypt plain text with cipher.

    printf("ciphertext: %s\n", ciphertext); // Prints encrypted text to screen.

    return 0;   // Function returns 0;
}

int string_check(int argc, string argv[])   // Function to check command line argument.
{
    if (argc != 2)  // If anymore than one command line arguments are inputted, function prints error message and returns 1.
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (strlen(argv[1]) != 26)  // If key is not 26 characters error message and returns 1.
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    char a; // Char data type initialised - this will store one char to compare against rest of string.

    for (int i = 0; i < 26; i++)    // For loop cycles variable a through each char of the key.
    {
        a = argv[1][i]; // Variable a = ith char of argv

        for (int j = i; j < 25; j++)    // Cycles from current a to the end of the key - checking for duplicates.
        {
            if (a == argv[1][j + 1])
            {
                printf("Key must not contain duplicate characters.\n");
                return 1;
            }
        }
        if (isalpha(argv[1][i]) == false)   // Final check, if all others are passed, this makes sure the key only contains letters.
        {
            printf("Key must only contain alphabetical characters.\n");
            return 1;
        }
    }
    return 0;   // If all criteria are passed, function returns 0;
}

string cipher(string argv, string plaintext)    // Function to take key and plaintext and returns ciphertext.
{
    int plength = strlen(plaintext);    // Declares an int that is the length of plain text.
    for (int i = 0; i < plength; i++)   // Cycles through each individual character of plaintext.
    {
        if (isalpha(plaintext[i]))  //If character is a letter, it is then encrypted. If not alpha, cycles to next character.
        {
            if (isupper(plaintext[i]))  //If character is uppercase, cipher char will also be uppercase.
            {
                argv[plaintext[i] - 65] = toupper(argv[plaintext[i] - 65]); // Changes the letter in the key to uppercase.
                plaintext[i] = argv[plaintext[i] - 65]; // Changes letter in the plaintext to letter from the key (using ASCII).
            }
            else
            {
                argv[plaintext[i] - 97] = tolower(argv[plaintext[i] - 97]); // Changes the letter in the key to lowercase.
                plaintext[i] = argv[plaintext[i] - 97]; // Changes letter in the plaintext to letter from the key (using ASCII).
            }
        }
    }
    return plaintext;   // Function returns the encrypted text.
}
#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>


string convertPlainText(string plainText, string key);
int validateKey(int argc, string key);

int main(int argc, string argv[])
{
    string key = argv[1];
    //check if key is valid
    if (validateKey(argc, key))
    {
        return 1;
    }

    //get input
    string plainText = get_string("plaintext: ");

    //convert the user input
    string cipherText = convertPlainText(plainText, key);

    //print everything
    printf("ciphertext: %s\n", cipherText);
    return 0;

}
//-------------------------------------------------------------------------------------------
int validateKey(int argc, string key)
{
    //check if 2nd argument exists
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //check if 2nd argument is 26 char long
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    //validate for duplicate characters and non valid characters
    for (int i = 0; i < strlen(key); i++)
    {
        //check if current char is alphabetic
        if (!(isalpha(key[i])))
        {
            printf("Key must contain only alphabetic characters.\n");
            return 1;
        }
        //check for repeated characters
        for (int j = 1; j < strlen(key); j++)
        {
            if (i == j)
            {
                continue;
            }
            if (key[i] == key[j])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }
    return 0;
}


//-------------------------------------------------------------------------------------------
string convertPlainText(string plainText, string key)
{
    //iterate thorugh the user given string
    for (int i = 0; i < strlen(plainText); i++)
    {
        //check if it's a letter
        if (isalpha(plainText[i]))
        {
            //check whether the letter is upper or lower case then substitute
            if (islower(plainText[i]))
            {
                plainText[i] = tolower(key[plainText[i] - 96 - 1]);
                continue;
            }
            plainText[i] = toupper(key[plainText[i] - 64 - 1]);
        }
    }
    return plainText;
}
#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>


int countLetters(string text);
int countWords(string text);
int countSentences(string text);
float getAverage100(int value1, int value2);
void printGrade(int index);

int main(void)
{
    //get text from user input
    string text = get_string("Text: ");

    //calculate values
    int numberLetters = countLetters(text);
    int numberWords = countWords(text);
    int numberSentences = countSentences(text);

    //get Averages
    float L = getAverage100(numberLetters, numberWords);
    float S = getAverage100(numberSentences, numberWords);

    //calculate formula
    float index = 0.0588 * L - 0.296 * S - 15.8;

    //printf("%i     %i     %i\n%f     %f    %f\n", numberLetters, numberWords, numberSentences, L, S, index);

    //print result
    printGrade(round(index));
}
//-------------------------------------------------------------------------------------------
int countLetters(string text)
{
    int counter = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isupper(text[i]))
        {
            counter++;
        }
        if (islower(text[i]))
        {
            counter++;
        }
    }
    return counter;
}
//-------------------------------------------------------------------------------------------
int countWords(string text)
{
    int counter = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            counter++;
        }
    }
    return counter;
}
//-------------------------------------------------------------------------------------------
int countSentences(string text)
{
    int counter = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.')
        {
            counter++;
        }
        if (text[i] == '!')
        {
            counter++;
        }
        if (text[i] == '?')
        {
            counter++;
        }
    }
    return counter;
}
//-------------------------------------------------------------------------------------------
float getAverage100(int value1, int value2)
{
    return (float) value1 / value2 * 100.0;
}
//-------------------------------------------------------------------------------------------
void printGrade(int index)
{
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index < 16 && index > 0)
    {
        printf("Grade %i\n", index);
    }
    else
    {
        printf("Grade 16+\n");
    }
}
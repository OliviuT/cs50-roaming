#include <cs50.h>
#include <stdio.h>


// AMEX - 15 digits starting with 34 or 37
// Mastercard 16 digits start with 51-55
// Vista 13 or 16 - start with 4

#define TEN 10


long getCardNumber(void);
int checkEvenSum(long long cardNumber);
int checkOddSum(long long cardNumber);
void checkCompany(long long cardNumber);

int main(void)
{
    int evenSum, oddSum;
    long long cardNumber;

    //ask for user card number
    cardNumber = getCardNumber();
    evenSum = checkEvenSum(cardNumber);
    oddSum = checkOddSum(cardNumber);
    //check if total sum has the last number == to zero, else INVALID
    if (((evenSum + oddSum) % TEN))
    {
        printf("INVALID\n");
        return 0;
    }
    checkCompany(cardNumber);
}
//------------------------------------------------------------------------------------------------
long getCardNumber(void)
{
    return get_long_long("Number: ");
}
//------------------------------------------------------------------------------------------------
int checkEvenSum(long long cardNumber)
{
    int evenSum = 0;
    while (cardNumber)
    {
        cardNumber /= TEN;
        //check if we reached the end
        if (!cardNumber)
        {
            break;
        }
        //multiply the even number by 2 and check if it's value is greater than ten, if yes divide and add its products
        int evenDigit = (cardNumber % TEN) * 2;
        if (evenDigit >= TEN)
        {
            int evenDigit2 = evenDigit % TEN;
            evenDigit /= TEN;
            evenSum = evenSum + evenDigit2 + evenDigit;
        }
        else
        {
            evenSum += evenDigit;
        }
        cardNumber /= TEN;
    }
    return evenSum;
}
//------------------------------------------------------------------------------------------------
int checkOddSum(long long cardNumber)
{
    int oddSum = 0;
    while (cardNumber)
    {
        int oddDigit = cardNumber % TEN;
        oddSum += oddDigit;
        cardNumber /= 100;
    }
    return oddSum;
}
//------------------------------------------------------------------------------------------------
void checkCompany(long long cardNumber)
{
    if (((340000000000000 <= cardNumber) && (cardNumber <= 349999999999999)) ||
        ((370000000000000 <= cardNumber) && (cardNumber <= 379999999999999)))
    {
        printf("AMEX\n");
    }
    else if (5100000000000000 <= cardNumber && cardNumber <= 5599999999999999)
    {
        printf("MASTERCARD\n");
    }
    else if (((4000000000000 <= cardNumber) && (cardNumber <= 4999999999999)) ||
             ((4000000000000000 <= cardNumber) && (cardNumber <= 4999999999999999)))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
#include <stdio.h>

void SizeOfVariables()
{
    char c;
    short s;
    int i;
    unsigned int ui;
    unsigned long int ul;
    float f;
    double d;
    long double ld;
    void *ptr;

    printf("Char c has size: %d\n", sizeof(c));                    //Print statements to read off all the sizes of the different variable types in bytes.
    printf("Short s has size: %d\n", sizeof(s));
    printf("Int i has size: %d\n", sizeof(i));
    printf("Unsigned int ui has size: %d\n", sizeof(ui));
    printf("Unsigned long int ul has size: %d\n", sizeof(ul));
    printf("Float f has size: %d\n", sizeof(f));
    printf("Double d has size: %d\n", sizeof(d));
    printf("Long double ld has size: %d\n", sizeof(ld));
    printf("Pointer ptr has size: %d\n", sizeof(ptr));
}

int IsLeapYear(int aYear)
{
    //Conditionals to check for the conditions of a leap year.
    if(aYear < 1752 && aYear > 0)
    {
        printf("The year entered is %d and it is not a leap year.\n", aYear);
        return 0;
    }
    else if(aYear % 400 == 0)
    {
        printf("The year entered is %d and it is a leap year.\n", aYear);
        return 1;
    }
    else if(aYear % 100 == 0)
    {
        printf("The year entered is %d and it is a not a leap year.\n", aYear);
        return 0;
    }
    else if(aYear % 4 == 0)
    {
        printf("The year entered is %d and it is a leap year.\n", aYear);
        return 1;
    }
    else
    {
        printf("The year entered is %d and it is not a leap year.\n", aYear);
        return 0;
    }
}

int IsVowel(char aLetter)
{
    //Use the fact that ASCII can be represented as numbers to selectively eliminate non-alphabetic characters.
    if ((aLetter >= 0 && aLetter <= 64) || (aLetter >= 91 && aLetter <= 96) || (aLetter >= 123))
    {
        printf("Error: Non-alphabetic character\n");
        return 0;
    }
    
    if(aLetter == 'a' || aLetter == 'e' || aLetter == 'i' || aLetter == 'o' || aLetter == 'u' || aLetter == 'A' || aLetter == 'I' || aLetter == 'E' || aLetter == 'O' || aLetter == 'U')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void ReverseNumber(long aNumber)
{
    short isNegative = 0;
    long aNumberCopy = aNumber;
    long reversed_number = 0;
    if (aNumber < 0)
    {
        isNegative = 1;
        aNumber = -aNumber;
    }
    
    while(aNumber != 0)
    {
        reversed_number *= 10;              //These 2 lines of code put the unit's place digit from the original and shift it left in the reversed number.
        reversed_number += aNumber % 10;
        aNumber /= 10; //This line removes the unit's place digit we just added onto our reversed number.
    }

    switch (isNegative)
    {
    case 1:
        printf("Number: %ld\tReversed: %ld\n", aNumberCopy, -reversed_number);
        break;
    
    default:
        printf("Number: %ld\tReversed: %ld\n", aNumberCopy, reversed_number);
        break;
    }
}

int main()
{    
    char character;
    SizeOfVariables();
    int listOfYears[] = {1750, 1800, 1900, 2000, 1904, 1908, 1996, 2018, 2020, 2024};   //Array of years to test.

    for(int i = 0; i < 10; i++)
    {
        IsLeapYear(listOfYears[i]);
    }

    char *testString = "aibIOqE23$%"; //Array of characters (string) to test the output of the function.
    for (int i = 0; i < 11; i++)
    {
        printf("%d\n", IsVowel(testString[i])); //Print statement to check whether the character was a vowel or not.
    }

    long testNumbers[] = {-234, -103, 0, 1234, 34, 234234, 729572};     //Array to test numbers for the reverse number function.
    for (int i = 0; i < 7; i++)
    {
        ReverseNumber(testNumbers[i]);
    }
    
    

    printf("Press Enter to quit");
    scanf("%c",&character);
    return 0;
}
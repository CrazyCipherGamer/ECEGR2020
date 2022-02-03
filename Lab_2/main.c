#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long Factorial(long num);
int IsPalindrome(long value);
int HighestBitSet(int value);
void ReverseIt(void);
void ReverseItAgain(void);
void Pyramid(int lines);

int main(void)
{
    //Test for Factorial function by user input
    for(int i = 0; i < 5; i++)
    {
        long userInput = 0;
        printf("Enter number to find the factorial of: ");
        scanf("%ld", &userInput);
        getchar(); //Throws away everything that is not a number.

        printf("You entered the number %ld and its factorial is %ld.\n", userInput, Factorial(userInput));
    }

    //Test for IsPalindrome function by user input
    for(int i = 0; i < 5; i++)
    {
        long value = 0;
        printf("Enter number to find whether it is a palindrome or not: ");
        scanf("%ld", &value);
        getchar(); //Throws away everything that is not a number.

        switch (IsPalindrome(value))
        {
        case 1:
            printf("The input number was %ld and it was a palindrome.\n", value);
            break;
        
        default:
            printf("The input number was %ld and it was NOT a palindrome.\n", value);
            break;
        }
    }

    //Test of HighestBitSet with user input
    for(int i = 0; i < 5; i++)
    {
        int userInput = 0;
        printf("Enter number to find the highest bit of: ");
        scanf("%d", &userInput);
        getchar(); //Throws away everything that is not a number.

        char buffer[8 * sizeof(int)] = "";

        itoa(userInput, buffer, 2);
        //Converts the user input into a string where the number is represented with base 2 intead of base 10 

        printf("Value: %d  Binary: %s  Highest bit set: %d.\n", userInput, buffer, HighestBitSet(userInput));
    }

    ReverseIt();
    ReverseItAgain();

    int userInput = 0;
    printf("Enter the number of lines of the pyramid you want: ");
    scanf("%d", &userInput);
    getchar(); //Throws away everything that is not a number.
    
    Pyramid(userInput);

    return 0;   
}

long Factorial(long num)
{
    long facNum = 1;

    while(num > 0)
    {
        facNum *= num;
        num--;
    }
    return facNum;
}

int IsPalindrome(long value)
{
    long originalNum = value;               //Copy the input into new variable for later comparison.
    long reversed_number = 0;

    while(value != 0)
    {
        reversed_number *= 10;              //These 2 lines of code put the unit's place digit from the original and shift it left in the reversed number.
        reversed_number += value % 10;
        value /= 10;                        //This line removes the unit's place digit we just added onto our reversed number.
    }

    if(reversed_number == originalNum)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

int HighestBitSet(int value)
{
    int bitIndex = 8 * sizeof(value) - 1;
    //Take care of error at value = 0
    switch (value)
    {
    case 0:
        return 0;
        break;
    
    default:

        while((value & (1 << bitIndex)) >> bitIndex != 1) //Continue loop as long as we don't hit the highest bit set to 1.
        {
            bitIndex--;
        }

        return bitIndex;
        break;
    }
}

void ReverseIt(void)
{
    //Create file to store the numbers into
    FILE *myfile = fopen("output.txt", "w");

    float floatArray[] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    //Loop to retrieve and put floats in reverse order in the array for printing and writing to file.
    for(int i = 4; i >= 0; i--)
    {
        float userInput = 0.0f;
        printf("Enter float to put in reverse order: ");
        scanf("%f", &userInput);
        getchar(); //Throws away everything that is not a number.
        floatArray[i] = userInput;
        fprintf(myfile, "%f\n", userInput);
    }

    for(int i = 0; i < 5; i++)
    {
        printf("The floats entered are as follows in reverse: %f\n", floatArray[i]);
        fprintf(myfile, "%f\n", floatArray[i]);
    }

    fclose(myfile);
}

void ReverseItAgain(void)
{
    float floatFromFile = 0.0f;
    FILE *myfile = fopen("output.txt", "r");
    if (myfile == NULL)
    {
        printf("Error: file is not there anymore.\n");
        return;
    }

    printf("\n\nThe following are the numbers stored in the file.\n");

    while(!feof(myfile))
    {
        fscanf(myfile, "%f", &floatFromFile);
        printf("%f\n", floatFromFile);
    }
}

void Pyramid(int lines)
{
    FILE *file = fopen("pyramid.txt", "w");
    char lineToPrint[64] = "";
    for(int i = 0; i < lines; i++)
    {
        for (int j = i; j < lines - 1; j++)
        {
            strcat(lineToPrint, " ");
        }
        for(int k = 0; k < 2*i+1; k++)
        {
            strcat(lineToPrint, "*");
        }
        strcat(lineToPrint, "\n");
        printf(lineToPrint);

        //Cycle through all the characters and put them into the file.        
        for(int n = 0; n < strlen(lineToPrint) + 1; n++)
        {   
            if(lineToPrint[n] == '\0')
            {
                break;
            }     
            fprintf(file, "%c", lineToPrint[n]);          
        }
        strcpy(lineToPrint, "");
    }
    fclose(file);
}
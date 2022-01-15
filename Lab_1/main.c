#include<stdio.h>

int main()
{
    int num1, num2;  
    float fraction;     
    char character;
    char str[50];   // char array of size 50

    printf("Enter two numbers\n");
    
    // Taking integer as input from user
    scanf(" %d%i", &num1, &num2);
    printf("\n\nThe two numbers You have entered are %d and %i\n\n", num1, num2);

    // Taking float or fraction as input from the user
    printf("\n\nEnter a Decimal number\n");
    scanf(" %f", &fraction); 
    printf("\n\nThe float or fraction that you have entered is %f", fraction);

    // Taking Character as input from the user
    printf("\n\nEnter a Character\n");
    scanf(" %c",&character);
    printf("\n\nThe character that you have entered is %c and the ASCII number is %d", character, character);
    getchar();

    printf("\n\nEnter your complete name:\n\n\n");

    gets(str);
    printf("\n\nWelcome to ECEGR 2020  %s\n\n\n", str);

    printf("\n\n\t\t\tCoding is Fun !\n\n\n");
    
    printf("Press Enter to quit");
    scanf("%c",&character);
    return 0;
}
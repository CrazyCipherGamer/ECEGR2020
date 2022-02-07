#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char userInput[100];

int isVowel(char aLetter);
int isConsonant(char aLetter);
void printMenu(void);

int main(void)
{
    printf("Enter a string please: ");
    fgets(userInput, 100, stdin);
    userInput[strlen(userInput)-1] = '\0'; //Replace erroneous newline character with the null terminator.

    printMenu();

    while(1)
    {

        char userChoice;
        scanf("%c", &userChoice);
        getchar();


        //Define variables used in switch case statments. Needed as compiler throws errors otherwise.
        int numVowels = 0;
        int numConsonants = 0;
        char *token = (char *)malloc(30);
        char tempWord[30];
        char outputString[100] = "";
        const char delimiter[2] = " ";

        //Use switch case for faster decision making. Reduces clock cycles required.
        switch (userChoice)
        {
            case 'a':
            case 'A':

                for(int i = 0; i < strlen(userInput); i++)
                {
                    numVowels += isVowel(userInput[i]);
                }

                printf("\n\nThere were %d vowels in the string.\n\n", numVowels);
                break;

            case 'b':
            case 'B':
                

                for(int i = 0; i < strlen(userInput); i++)
                {
                    numConsonants += isConsonant(userInput[i]);
                }

                printf("\n\nThere were %d consonants in the string.\n\n", numConsonants);
                break;

            case 'c':
            case 'C':
                for (int i = 0; i < strlen(userInput); i++)
                {
                    userInput[i] = toupper(userInput[i]);
                }
                break;
            
            case 'd':
            case 'D':
                for (int i = 0; i < strlen(userInput); i++)
                {
                    userInput[i] = tolower(userInput[i]);
                }
                break;

            case 'e':
            case 'E':
                printf("\nThe current string is: %s\n", userInput);
                break;
            
            case 'f':
            case 'F':
                printf("Enter a new string please: ");
                fgets(userInput, 100, stdin);
                userInput[strlen(userInput)-1] = '\0'; //Replace erroneous newline character with the null terminator.
                break;

            case 'r':
            case 'R':
                
                token = strtok(userInput, delimiter);   //Get the first token
                while(token != NULL)
                {
					/*Copy the token into a temporary string as we don't want to 
					manipulate the token as it is a pointer to the original string that will change otherwise.*/
                    strcpy(tempWord, token);
                    for(int i = 0; i < strlen(tempWord)/2; i++)		//Only need to go upto half of the word to swap all characters.
                    {
                        char tempChar = tempWord[i];
                        tempWord[i] = tempWord[strlen(tempWord)-i-1];
                        tempWord[strlen(tempWord)-i-1] = tempChar;
                    }
                    strcat(outputString, tempWord);			//Concatenate the reversed word into another string to build up for the output.
                    strcat(outputString, " ");				//Concatenate the space to separate the words.
                    token = strtok(NULL, delimiter);
                }
                outputString[strlen(outputString)-1] = '\0';	//Removes the last space we added for the final output as it is an extra.
                strcpy(userInput, outputString);				//Update the original string which is used for all other functions.
                break;

            case 'm':
            case 'M':
                printMenu();
                break;
            
            default:
                break;
        }

        if(userChoice == 'x' || userChoice == 'X')
        {
            break;
        }
        
    }

    return 0;
}

int isVowel(char aLetter)
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

int isConsonant(char aLetter)
{
    //Use the fact that ASCII can be represented as numbers to selectively eliminate non-alphabetic characters.
    if ((aLetter >= 0 && aLetter <= 64) || (aLetter >= 91 && aLetter <= 96) || (aLetter >= 123))
    {
        printf("Error: Non-alphabetic character\n");
        return 0;
    }
    
    if(aLetter == 'a' || aLetter == 'e' || aLetter == 'i' || aLetter == 'o' || aLetter == 'u' || aLetter == 'A' || aLetter == 'I' || aLetter == 'E' || aLetter == 'O' || aLetter == 'U')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void printMenu(void)
{
    printf("A) Count the number of vowels in the string\n");
    printf("B) Count the number of consonants in the string\n");
    printf("C) Convert the string to uppercase\n");
    printf("D) Convert the string to lowercase\n");
    printf("E) Display the current string\n");
    printf("F) Enter another string\n");
    printf("R) Reverse words in string\n");
    printf("\nM) Display this menu again\n");
    printf("X) Exit the Program\n\n\n");
}
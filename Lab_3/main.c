#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int theArray[10] = {1,2,3,4,5,6,7,8,9,10};

typedef struct student
{
    int ID;
    char firstName[30];
    char lastName[30];
    float GPA;
} Student;

void ReverseArray(void);
Student* NewStudent(void);                          //Function to allocate and get user input for a new student.
void SortByGPA(Student** array, int num);           //Sorts students by GPA in descending order.
void SaveStudentData(Student** array, int num);     //Function that writes out all data in heap to a file.
Student** ImportStudentData(void);

int main(void)
{
    int numStudents = 0;

    ReverseArray();
    for(int i = 0; i < 10; i++)
    {
        printf("%d\n", theArray[i]);
    }
    
    printf("How many students do you want to enter into the records? ");
    scanf("%d", &numStudents);
    Student **arrayOfStudents = (Student**)malloc(numStudents * sizeof(Student*));

    for(int i = 0; i < numStudents; i++)
    {
        arrayOfStudents[i] = NewStudent();
    }

    SortByGPA(arrayOfStudents, numStudents);
    SaveStudentData(arrayOfStudents, numStudents);
    free(arrayOfStudents);


    Student **newArray = ImportStudentData();
    free(newArray);
    return 0;
}

void ReverseArray(void)
{
    int tempArray[10] = {0};
    for(int i = 0; i < 10; i++)
    {
        tempArray[i] = theArray[9-i];   
    }
    for (int i = 0; i < 10; i++)
    {
        theArray[i] = tempArray[i];
    }
    
}

Student* NewStudent(void)
{
    Student* student = (Student*) malloc(sizeof(Student));
    int ID = 0;
    char firstName[30] = "";
    char lastName[30] = "";
    float GPA = 0.0f;

    printf("\nEnter ID of student: ");
    scanf("%d", &ID);
    student->ID = ID;
    printf("Enter first name of student: ");
    scanf("%s", firstName);
    strcpy(student->firstName, firstName);
    printf("Enter last name of student: ");
    scanf("%s", lastName);
    strcpy(student->lastName, lastName);
    printf("Enter GPA of student: ");
    scanf("%f", &GPA);
    student->GPA = GPA;

    return student;
}

void SortByGPA(Student** array, int num)
{
    for (int i = 0; i < num; i++)
    {
      for (int j = i + 1; j < num; j++)
      {
        if (array[i]->GPA < array[j]->GPA)
        {
            Student *tempStudent = array[i];
            array[i] = array[j];
            array[j] = tempStudent;
        }
      }
   }
}

void SaveStudentData(Student** array, int num)
{
    FILE *myfile = fopen("output.txt", "w");

    fprintf(myfile, "%d\n", num);

    for(int i = 0; i < num; ++i)
    {
        fprintf(myfile, "%d\n", array[i]->ID);
        fprintf(myfile, "%s\n", array[i]->firstName);
        fprintf(myfile, "%s\n", array[i]->lastName);
        fprintf(myfile, "%f\n", array[i]->GPA);
    }

    fclose(myfile);
}

Student** ImportStudentData(void)
{
    FILE *studentFile = fopen("output.txt", "r");
    if(studentFile == NULL)
    {
        printf("File does not exist anymore.\n");
        return NULL;
    }
    int numStudents;
    fscanf(studentFile, "%d", &numStudents);
    fgetchar();

    Student **studentArray = (Student **)malloc(numStudents * sizeof(Student*));

    float averageGPA = 0.0f;
    
    for(int i = 0; i < numStudents; ++i)
    {
        studentArray[i] = (Student*)malloc(sizeof(Student));

        fscanf(studentFile, "%d", &(studentArray[i]->ID));
        fscanf(studentFile, "%s", studentArray[i]->firstName);
        fscanf(studentFile, "%s", studentArray[i]->lastName);
        fscanf(studentFile, "%f", &(studentArray[i]->GPA));

        printf("ID of student %d is: %d\n", i+1, studentArray[i]->ID);
        printf("First name of student %d is: %s\n", i+1, studentArray[i]->firstName);
        printf("Last name of student %d is: %s\n", i+1, studentArray[i]->lastName);
        printf("GPA of student %d is: %f\n", i+1, studentArray[i]->GPA);

        averageGPA += studentArray[i]->GPA;
    }
    averageGPA /= numStudents;
    printf("\nThere were %d students in the class and the average GPA was %f\n", numStudents, averageGPA);
    return studentArray;
}
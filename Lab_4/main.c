#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
    int ID;
    char firstName[30];
    char lastName[30];
    float GPA;
    struct student *next;
} Student;

int numStudents;

Student *head = NULL;

void ImportStudentData(void);                                                               //Function to read and create the linked list
void SaveStudentData(void);                                                                 //Function that writes out all data in linked list to the originial file.
void LinkedMenu(void);                                                                       //Function to utilise the menu
Student* NewStudent(int ID, char firstName[30], char lastName[30], float GPA);              //Function to allocate and get user input for a new student node.
void AddStudent(Student* studentNode);                                                      //Function to add student node to the linked list at the end
void RemoveByID(int ID);                                                                    //Function to remove a student by searching for their ID in the linked list.
void UpdateByID(int ID);                                                                    //Function to find student by ID to update.
void InsertByGPA(Student* insertedStudent);                                                 //Inserts student by GPA in descending order in linked list. This avoids us having to resort the list as we enter the student right where they need to be.
void PrintStudents(void);                                                                   //Prints all students in order of descending GPA as put in the linked list
void DeleteList(void);                                                                      //Ensures all elements of the linked list are freed individually.

int main(void)
{
    ImportStudentData();
    LinkedMenu();
    DeleteList();
    return 0;
}

void ImportStudentData(void)
{
    FILE *studentFile = fopen("output.txt", "r");
    if(studentFile == NULL)
    {
        printf("File does not exist anymore.\n");
        return;
    }
    fscanf(studentFile, "%d", &numStudents);

    
    for(int i = 0; i < numStudents; ++i)
    {   
        int ID;
        char firstName[30];
        char lastName[30];
        float GPA;

        fscanf(studentFile, "%d", &ID);
        fscanf(studentFile, "%s", firstName);
        fscanf(studentFile, "%s", lastName);
        fscanf(studentFile, "%f", &GPA);

        Student *fileStudent = NewStudent(ID, firstName, lastName, GPA);

        if(fileStudent != NULL)
        {
            AddStudent(fileStudent);
        }
    }
}

void SaveStudentData()
{
    FILE *myfile = fopen("output.txt", "w");

    fprintf(myfile, "%d\n", numStudents);

    //Wow, much cool checking and declaration
    for( Student *currentStudent = head; currentStudent != NULL; currentStudent = currentStudent->next)
    {
        fprintf(myfile, "%d\n", currentStudent->ID);
        fprintf(myfile, "%s\n", currentStudent->firstName);
        fprintf(myfile, "%s\n", currentStudent->lastName);
        fprintf(myfile, "%f\n", currentStudent->GPA);
    }

    fclose(myfile);
}

void LinkedMenu()
{
    int option = 0;
    while(option != 5)
    {
        printf("1) List all Students\n");
        printf("2) Add Student\n");              //Student is inserted into the linked list in descending order of GPA. This avoids a full sort of the linked list entirely.
        printf("3) Remove Student (by ID)\n");   //Assuming that we remove student by their unique ID, a reasonable and realistic assumption.
        printf("4) Update Student (by ID)\n");   //Again, by using a sensible approach of ID.
        printf("5) Save and Quit\n\n\n");

        scanf("%d", &option);

        int ID;
        char firstName[30];
        char lastName[30];
        float GPA;

        switch (option)
        {
        case 1:
            PrintStudents();
            break;
        
        case 2:
            printf("Enter ID of new student: ");
            scanf("%d", &ID);
            printf("Enter the first name of new student: ");
            scanf("%s", firstName);
            printf("Enter the last name of new student: ");
            scanf("%s", lastName);
            printf("Enter the GPA of new student: ");
            scanf("%f", &GPA);
            printf("\n\n");
            
            Student *insertStudent = NewStudent(ID, firstName, lastName, GPA);

            InsertByGPA(insertStudent);
            break;
        
        case 3:
            printf("Enter ID of student to remove: ");
            scanf("%d", &ID);
            RemoveByID(ID);
            break;
        
        case 4:
            printf("Enter ID of student to update: ");
            scanf("%d", &ID);
            UpdateByID(ID);
            break;
        case 5:
            SaveStudentData();
            DeleteList();
            break;
        default:
            break;
        }
    }
    
}

Student* NewStudent(int ID, char firstName[30], char lastName[30], float GPA)
{
    //Create Student node
    Student* student = (Student*) malloc(sizeof(Student));
    
    if(student != NULL)
    {
        student->ID = ID;
        strcpy(student->firstName, firstName);
        strcpy(student->lastName, lastName);
        student->GPA = GPA;
        student->next = NULL;
    }
    
    return student;
}

void AddStudent(Student* studentNode)
{
    Student* currentStudent = head;
    
    //If list is empty, then make the input student as the head node.
    if(head == NULL)
    {
        head = studentNode;
        return;
    }

    //Traverse list until the end and add the studentNode there if list had stuff.
    while(currentStudent->next != NULL)
    {
        currentStudent = currentStudent->next;
    }
    currentStudent->next = studentNode;
}

void RemoveByID(int ID)
{
    Student *prevStudent = head;
    Student *currentStudent = NULL;
    if(prevStudent == NULL)
    {
        printf("Error! Linked list empty!\n\n");
        return;
    }
    currentStudent = prevStudent->next;

    if(currentStudent == NULL && prevStudent->ID == ID)
    {
        free(prevStudent);
        printf("List Cleared!\n");
        numStudents--;
        return;
    }

    while(currentStudent != NULL)
    {
        //Case when the student to be removed is the first student
        if(prevStudent->ID == ID)
        {
            head = prevStudent->next;
            free(prevStudent);
            break;
        }
        //Case when the student to be removed is in the middle
        else if(currentStudent->ID == ID)
        {
            prevStudent->next = currentStudent->next;
            free(currentStudent);
            break;
        }
        //Case when the student to be removed is at the end
        if(currentStudent->ID == ID && currentStudent->next == NULL)
        {
            prevStudent->next = NULL;
            free(currentStudent);
            break;
        }
        prevStudent = currentStudent;
        currentStudent = currentStudent->next;
    }
    numStudents--;
}

//We find the student in the list and then update their info, connect the linked list as it should be and then just put the Student * for that student into InsertByGPA to put them in correctly in the list to never worry about resorting the entire linked list.
void UpdateByID(int ID)
{
    Student *currentStudent = head;
    Student *nextStudent = NULL;
    if(currentStudent == NULL)
    {
        printf("List empty!");
        return;
    }
    nextStudent = currentStudent->next;

    while(nextStudent != NULL)
    {
        //Case when the first student is the student we need to update
        if(currentStudent->ID == ID)
        {
            printf("Enter new ID: ");
            scanf("%d", &(currentStudent->ID));
            printf("Enter new first name: ");
            scanf("%s", currentStudent->firstName);
            printf("Enter new last name: ");
            scanf("%s", currentStudent->lastName);
            printf("Enter new GPA: ");
            scanf("%f", &(currentStudent->GPA));

            //Remove the student node temporarily while connecting the linked list back up.
            head = nextStudent;
            currentStudent->next = NULL;

            //Reinsert the student node
            InsertByGPA(currentStudent);
            break;
        }
        //Case when the student to be updated is in the middle. Note: currentStudent and nextStudent now refer to prevStudent and currentStudent here to ensure that all pointers are connected correctly.
        else if(nextStudent->ID == ID && nextStudent->next != NULL)
        {
            printf("Enter new ID: ");
            scanf("%d", &(nextStudent->ID));
            printf("Enter new first name: ");
            scanf("%s", nextStudent->firstName);
            printf("Enter new last name: ");
            scanf("%s", nextStudent->lastName);
            printf("Enter new GPA: ");
            scanf("%f", &(nextStudent->GPA));

            //Remove the student node temporarily while connecting the linked list back up
            currentStudent->next = nextStudent->next;
            nextStudent->next = NULL;

            //Reinsert the student node
            InsertByGPA(nextStudent);
        }
        //Case for student at the end
        if(nextStudent->ID == ID && nextStudent->next == NULL)
        {
            printf("Enter new ID: ");
            scanf("%d", &(nextStudent->ID));
            printf("Enter new first name: ");
            scanf("%s", nextStudent->firstName);
            printf("Enter new last name: ");
            scanf("%s", nextStudent->lastName);
            printf("Enter new GPA: ");
            scanf("%f", &(nextStudent->GPA));

            //Momentary disconnect
            currentStudent->next = NULL;

            //Reinsert
            InsertByGPA(nextStudent);
            break;
        }
        currentStudent = nextStudent;
        nextStudent = nextStudent->next;
    }
    
}


//This function adds the student node at the correct point in the linked list by comparing GPAs ahead and behind in a loop
//This check ensures that the student is entered at the correct spot to ensure GPA is in descending order
//This method totally avoids the need to resort as long as the original data read in from the external file was in descending order.
void InsertByGPA(Student* insertedStudent)
{
    Student *currentStudent = head;
    Student *nextStudent = NULL;
    if(currentStudent == NULL)
    {
        printf("Error! Linked list empty!\n\n");
        return;
    }
    nextStudent = currentStudent->next;

    while(nextStudent != NULL)
    {
        //Insertion at the beginning
        if(currentStudent->GPA < insertedStudent->GPA)
        {
            insertedStudent->next = currentStudent;
            head = insertedStudent;
            break;
        }
        //Insertion at the middle
        else if(currentStudent->GPA > insertedStudent->GPA && nextStudent->GPA < insertedStudent->GPA)
        {
            currentStudent->next = insertedStudent;
            insertedStudent->next = nextStudent;
        }
        //Insertion at the end
        if(nextStudent->GPA > insertedStudent->GPA)
        {
            nextStudent->next = insertedStudent;
            break;
        }
        currentStudent = nextStudent;
        nextStudent = nextStudent->next;
    }
    numStudents++;
}

void PrintStudents(void)
{
    Student *currentStudent = head;

    if(numStudents == 0)
    {
        printf("List is empty!\n");
        return;
    }

    for (int pos = 0; currentStudent != NULL; ++pos)
    {
        printf("The ID of student %d is: %d\n", pos + 1, currentStudent->ID);
        printf("The first name of student %d is: %s\n", pos + 1, currentStudent->firstName);
        printf("The last name of student %d is: %s\n", pos + 1, currentStudent->lastName);
        printf("The GPA of student %d is: %f\n\n\n", pos + 1, currentStudent->GPA);

        if(currentStudent->next != NULL)
        {
            currentStudent = currentStudent->next;
            continue;
        }
        break;
    }
}

void DeleteList(void)
{
    Student *prev = head;
    //This loop essentially cycles the nodes backwards to free them from memory.
    while(head)
    {
        head = head->next;
        free(prev);
        prev = head;
    }
}
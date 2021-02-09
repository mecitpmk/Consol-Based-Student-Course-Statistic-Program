
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#pragma warning(disable : 4996)


typedef struct
{
    char studentName[50];
    int studentID;
    float midtermGrade;
    float FinalGrade;
    float courseGradE;
    bool passed;
}Student;

typedef struct
{
    int passed_numbers;
    int failed_numbers;
    float avarage_grades;
}COURSESTATISTIC;
COURSESTATISTIC Statistic;



Student* createdStudents[1000];
int counter = 0;


void CreateStudent(char *stdName,int *std_id, float *midtermGrade,float * finalGrade);
int findStudents(int *givenID);
void calculateStatistic();

int main()
{
    while (1)
    {
        char input_char;
        char stdNm[50];
        int stdID;
        float midtermG;
        float finalG;
        int willFinded;
        printf("\nAdd a new record for 'A'\nFind Record for 'F' \nShow Statistic for 'S' \nQuit for 'Q'\nYour Answers:");
        scanf(" %c",&input_char);
        

        switch (toupper(input_char))
        {
        case 'A':
            printf("Add entry Selected");
            printf("\nEnter Student Name:");
            scanf("%s",stdNm);
            printf("\nEnter Student ID:");
            scanf("%d",&stdID);
            printf("\nEnter Student Midterm Grade:");
            scanf("%f",&midtermG);
            printf("\nEnter Student Final Grade:");
            scanf("%f",&finalG);
            printf("\nStudent Created Succesfully\n");
            CreateStudent(stdNm,&stdID,&midtermG,&finalG);
            break;
        case 'S':
            calculateStatistic();
            printf("\nNumber of Student = %d\nFailed Students Number = %d \nPassed Students Number = %d\nCourse Avarage = %.2f\n",counter,Statistic.failed_numbers,Statistic.passed_numbers,Statistic.avarage_grades);
            break;
        case 'F':
            printf("\nEnter Student id to Search:");
            scanf("%d",&willFinded);
            int result = findStudents(&willFinded);
            if (result != -1)
            {
                printf("\n Record founded\n");
                printf("\nStudent Name :%s",createdStudents[result]->studentName);
                printf("\nStudent ID:%d",createdStudents[result]->studentID);
                printf("\nStudent Midterm Grade :%.2f",createdStudents[result]->midtermGrade);
                printf("\nStudent Final Grade:%.2f",createdStudents[result]->FinalGrade);
                printf("\nStudent Course Grade:%.2f",createdStudents[result]->courseGradE);
                printf("\nFail Status : %s\n",createdStudents[result]->passed ? "Passed" : "Failed");
            }
            else
            {
                printf("No record is founded");
            }
            
            break;
        case 'Q':
            exit(1);
        default:
            printf("\nINCOMPLETE KEYWORD TRY AGAIN.\n");
            break;
        break;
        }
    }
    

    
}


void CreateStudent(char *stdName,int *std_id, float *midtermGrade,float * finalGrade)
{   
    Student *std_object  = (Student*)malloc(sizeof(Student));
    // memcpy(std_object->studentName,stdName,sizeof(stdName));
    strcpy(std_object->studentName,stdName);
    std_object->studentID = *std_id;
    std_object->midtermGrade = *midtermGrade;
    std_object->FinalGrade = *finalGrade;
    std_object->passed = false;
    std_object->courseGradE  = (float)(*finalGrade*0.6+*midtermGrade*0.4);
    if (std_object->courseGradE > 60)
    {
        std_object->passed = true;
    }
    createdStudents[counter] = std_object;
    counter++;
}

int findStudents(int *givenID)
{
    // If fonuded return index in the array   else return -1; 
    
    int index;
    for (index = 0; index<counter; index++)
    {
        if (createdStudents[index]->studentID == *givenID)
        {
            return index;
        }
    }
    return -1;

}


void calculateStatistic()
{
    int passed_numbers = 0;
    int failed_numbers = 0;
    float avarage_grades = 0;
    if (counter > 0 )
    {
        for (int i = 0 ; i<counter ; i++)
        {
            avarage_grades += createdStudents[i]->courseGradE;
            if (createdStudents[i]->passed)
            {
                passed_numbers++;
            }
            else
            {
                failed_numbers++;
            }
        }
        avarage_grades = avarage_grades/counter;
    }
    Statistic.avarage_grades = avarage_grades;
    Statistic.passed_numbers = passed_numbers;
    Statistic.failed_numbers = failed_numbers;
}
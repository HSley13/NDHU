#include <stdio.h>

#define SIZE 20

typedef struct 
{
    char studentID[20];
    int programming, programmingLab, calculus;
} Student;

void take_record(Student *list, int n)
{
    for (int i = 0; i < n; i++)
    {
        scanf("%s\n", list[i].studentID);
        scanf("%d\n", &list[i].programming);
        scanf("%d\n", &list[i].programmingLab);
        scanf("%d\n", &list[i].calculus);
    }
}

double average(Student *list)
{
    double sum = list->programming + list->programmingLab + list->calculus;

    return sum / 3;
}     

void put_in_order(Student *list, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (average(&list[i]) < average(&list[j]))
            {
                Student temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
}

void top_3(Student *list, int n)
{   
    int max_student = (n >= 3) ? 3 : n;

    for (int i = 0; i < max_student; i++) printf ("%s\n", list[i].studentID);
}

int main(void)
{
    int n;
    scanf("%d", &n);

    Student list[SIZE];
    take_record(list, n);

    put_in_order(list, n);
    top_3(list, n);
}
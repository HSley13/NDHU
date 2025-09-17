#include <stdio.h>

#define SIZE 100

typedef struct COURSES
{
    int sid, student_ID, course_ID;
    
}COURSES;

typedef struct SCORES
{
    int sid, score, sid_n_score;
}SCORES;

int init_courses(COURSES *arr, int n_courses)
{
    int num_student = 0;
    for (int i = 0; i < n_courses; i++) 
    {
        scanf("%d %d %d", &arr[i].sid, &arr[i].student_ID, &arr[i].course_ID);
        num_student++;

        for (int j = 0; j < i - 1; j++)
        {
            if (arr[i].student_ID == arr[j].student_ID)
            {
                num_student--;
                break;
            }
        }
    }

    return num_student;
}

void init_scores(SCORES *arr, int n_scores)
{
    for (int i = 0; i < n_scores; i++)
    {
        arr[i].sid_n_score = 0;
        
        scanf("%d %d", &arr[i].sid, &arr[i].score);
        arr[i].sid_n_score++;
    }
}

int num_failed (SCORES *arr, int n_scores)
{
    int failed = 0;

    for (int i = 0; i < n_scores; i++) 
    {
       int sum = arr[i].score;
       
       for (int j = i + 1; j < n_scores; j++)
       {
            if (arr[i].sid == arr[j].sid) sum += arr[j].score;
       }

        int  avg = sum / arr[i].sid_n_score;
        failed = (avg < 60) ? failed + 1 : failed;
    }

    return failed;
}


int main(void)
{
    int n_courses, n_scores;
    scanf("%d %d", &n_courses, &n_scores);

    COURSES arr1[SIZE] = {0};
    SCORES arr2[SIZE] = {0};

    int student_num = init_courses(arr1, n_courses);
    init_scores(arr2, n_scores);

    int failed = num_failed(arr2, n_scores);

    printf("%d %d",student_num, failed);
}
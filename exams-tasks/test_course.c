#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
{
    char name[51];
    char date[11];
    int lekcii;
    float price;
}Course;


void Sale (Course *courses, int n, int idx)
{
    if (idx<0 || idx>=n) exit(-3);
    courses[idx].price -= 0.1 * Course[idx].price;
    printf("%.2f---- %50[^\n] ------%s", courses[idx].price, courses[idx].name, courses[idx].date);
}



int Count (Course *courses, int n, float min, float max)
{
    count = 0;
    FILE *fp = fopen("offer.txt", "w");
    if (fp==NULL) exit(-4);
    for (int i = 0; i<n; i++)
    {
        if (courses[i].price>min && courses[i]<max)
        {
            fprintf(fp, "%50[^\n] ----- %s ------ %.2f", courses[i].name, courses[i].date, courses[i].price);
            count++;
        }
    }

    fclose(fp);
    return count;
}

Course *removeCourse (Course *courses, int n, char *name, char *date)
{
    int skipIdx = -1;
    for (int i = 0; i<n; i++)
    {
        if(strcmp(courses[i].name, name) == 0 && strcmp(courses[i].date, date) == 0)
        {
            skipIdx = i;
            break;
        }
    }
    if (skipIdx == -1)
    {
        printf("Kursa ne e nameren");
        return NULL;
    }
    int newSize = n-1;
    Course *result = malloc(newSize *sizeof(Course));

    if (result ==NULL) exit(-5);
    int idx = 0;
    
    for (int j = 0; j<n - 1; j++)
    {
        if (j != skipIdx)
        {
            result[idx] = courses[j];
            idx++;
        }
    }
    return result;
}


int main()
{
    FILE *fp = fopen("courses.bin", "rb");
    if (fp ==NULL) exit(-1);


    fseek(fp, 0, SEEK_END);
    int fileSize = ftell(fp);
    rewind(fp);

    int numCourses = fileSize / sizeof(Course);

    Course *courses = malloc(numCourses * sizeof(Course));
    if (courses ==NULL) exit(-2);

    fread (courses, sizeof(Course), numCourses, fp);

    free(courses);
    fclose(fp);
    return 0;
}

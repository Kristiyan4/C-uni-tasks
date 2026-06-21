#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
{
    int id;
    char date [11];
    char name [31];
    char diagnose [51];
} Treatment;


int count_treatment(Treatment *history, int n, char *name, char *diagnose)
{
    int count = 0;
    for (int i = 0; i<n; i++)
    {
        if (strcmp(history[i].name, name)==0 && strcmp(history[i].diagnose, diagnose)==0)
        {
            count++;
        }
    }
    return count; 
}


Treatment *add_new_treatment(Treatment *history, int n)
{
    Treatment new;
    scanf("%d", &new.id);
    getchar();
    fgets(new.date, 11, stdin);
    new.date[strcspn(new.date, "\n")] = "\0";
    fgets(new.name, 31, stdin);
    new.name[strcspn(new.name, "\n")] = "\0";
    fgets(new.diagnose, 51, stdin);
    new.diagnose[strcspn(new.diagnose, "\n")]= "\0";

    Treatment *newMasiv = realloc(history, (n+1) * sizeof(Treatment));
    if (newMasiv==NULL) exit (-3);
    newMasiv[n] = new;

    return newMasiv;
}

int write_text_file(Treatment *history, int n, char *diagnose)
{
    FILE *fp = fopen("illnes.txt", "w");
    if (fp ==NULL) exit (-4);
    int count = 0;

    for (int i = 0; i<n; i++)
    {
        if (history[i].diagnose == diagnose)
        {
            fprintf(fp, "%d --- %s --- %30 [^\n] ----- %50[^\n ----]", history[i].id, history[i].date, history[i].name, history[i].diagnose);
            count++;
        }
    }
    return count;
}


int main ()
{
    FILE *fp = fopen("history.bin", "rb");
    if(fp==NULL) exit (-1);

    fseek(fp, 0, SEEK_END);
    int fileSize = ftell(fp);
    rewind(fp);
    if (fileSize<sizeof(Treatment)) exit(-2);

    int n = fileSize/sizeof(Treatment);
    Treatment *history = malloc(n * sizeof(Treatment));
    if (history == NULL) exit (-3);

    fread(history, sizeof(Treatment), n, fp);

    free(history);
    fclose(fp);
    return 0;
}
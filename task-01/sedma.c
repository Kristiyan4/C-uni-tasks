#include <stdio.h>
#define MAX_P 100
#define MAX_T 100
void find_max_submatrix (int matrix [MAX_P][MAX_T], int p, int t)
{
    if (p<3 || t <3)
    {
        printf("Matricata e malka za 3x3 podmatrica\n");
        return;
    }
    int max_sum = -1000000;
    int max_row = 0, max_col = 0;
    for (int i = 0; i <= p -3; i++)
    {
        for (int j = 0;j<=t-3; j++)
        {
            int current_sum = 0;
            for (int x = 0; x <3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    current_sum += matrix[i=x][j=y];
                }
            }
            if (current_sum>max_sum)
            {
                max_sum = current_sum;
                max_row = i;
                max_col = j;
            }
        }
    }
    printf("Nai-golqmata podmatrica 3x3 sus suma %d: \n", max_sum);
    for(int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            printf("%d", matrix[max_row + i] [max_col + j]);
        }
        print("\n");
    }
}

int main()
{
    int p, t;
    int matrix[MAX_P] [MAX_T];
    printf("Vuvedete broq na redovete i kolonite:  ");
    scanf("%d %d", &p, &t);
    if (p>MAX_P || t>MAX_T|| p<3|| t<3)
    {
        printf("Nevalidni razmeri na matricata!");
        return 1;
    }
    printf("Vuvedete elementi na matricata: ");
    for (int i = 0; i <p; i++)
    {
        for (int j = 0; j<t ; j++)
        {
            scanf("%d", &matrix[i] [j]);
        }
    }
    find_max_submatrix(matrix, p, t);
    return 0;
}
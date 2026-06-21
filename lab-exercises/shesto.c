#include <stdio.h>
//============================================== 1
int main() 
{
    int arr[20];  
    for (int i = 0; i < 20; i++) 
    {
        arr[i] = i * 5;
    }
    printf("Елементите на масива са:\n");
    for (int i = 0; i < 20; i++) 
    {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    return 0;
}
//==================================================== 2
#include <stdio.h>
#include <string.h>

int main() 
{
    char text[21];
    int count[256] = {0};
    printf("Въведете текст до 20 символа: ");
    fgets(text, 21, stdin);
    text[strcspn(text, "\n")] = 0;
    for (int i = 0; text[i] != '\0'; i++) 
    {
        count[(unsigned char)text[i]]++;
    }
    printf("Брой на срещанията на всеки символ:\n");
    for (int i = 0; i < 256; i++) 
    {
        if (count[i] > 0) 
        {
            printf("%c - %d\n", i, count[i]);
        }
    }
    return 0;
}
//================================================== 3
#include <stdio.h>
#include <stdbool.h>

int main() 
{
    int N;
    printf("Въведете колко прости числа искате да видите: ");
    scanf("%d", &N);
    if (N <= 0) 
    {
        printf("Моля, въведете положително число!\n");
        return 1;
    }

    int limit = N * 20;  
    bool is_prime[limit];

    for (int i = 0; i < limit; i++) 
    {
        is_prime[i] = true;
    }
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i < limit; i++) 
    {
        if (is_prime[i]) 
        {
            for (int j = i * i; j < limit; j += i) 
            {
                is_prime[j] = false;
            }
        }
    }

    printf("Първите %d прости числа са:\n", N);
    int count = 0;
    for (int i = 2; i < limit && count < N; i++) 
    {
        if (is_prime[i]) 
        {
            printf("%d ", i);
            count++;
        }
    }

    printf("\n");
    return 0;
}

//================================================== 4
#include <stdio.h>

#define SIZE 20

int main() 
{
    int arr[SIZE];
    int maxLength = 1, currentLength = 1;
    int maxElement;

    printf("Въведете %d цели числа:\n", SIZE);
    for (int i = 0; i < SIZE; i++) 
    {
        scanf("%d", &arr[i]);
    }

    for (int i = 1; i < SIZE; i++) 
    {
        if (arr[i] == arr[i - 1]) 
        {
            currentLength++;
        } 
        else 
        {
            currentLength = 1;
        }

        if (currentLength > maxLength) 
        {
            maxLength = currentLength;
            maxElement = arr[i];
        }
    }

    printf("Най-дългата редица от еднакви елементи е: {");
    for (int i = 0; i < maxLength; i++) 
    {
        printf("%d", maxElement);
        if (i < maxLength - 1) 
        {
            printf(", ");
        }
    }
    printf("}\n");

    return 0;
}

//============================================== 5
#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 32
#define MAX_NAME_LENGTH 128
void search_students(char students[MAX_STUDENTS][MAX_NAME_LENGTH], int student_count, char *substring) 
{
    int found = 0;
    printf("Резултат от търсенето:\n");
    for (int i = 0; i < student_count; i++) 
    {
        if (strstr(students[i], substring) != NULL) 
        {  
            printf("- %s\n", students[i]);
            found = 1;
        }
    }
    if (!found) 
    {
        printf("Няма намерени студенти с тази част от име.\n");
    }
}
int main() 
{
    char students[MAX_STUDENTS][MAX_NAME_LENGTH];
    int student_count;
    printf("Въведете броя на присъстващите студенти (максимум %d): ", MAX_STUDENTS);
    scanf("%d", &student_count);
    if (student_count > MAX_STUDENTS || student_count <= 0) 
    {
        printf("Броят на студентите трябва да е между 1 и %d.\n", MAX_STUDENTS);
        return 1;
    }
    printf("Въведете имената на студентите:\n");
    for (int i = 0; i < student_count; i++) 
    {
        printf("Студент %d: ", i + 1);
        scanf(" %[^\n]", students[i]);
    }
    char search_query[MAX_NAME_LENGTH];
    printf("Въведете част от име за търсене: ");
    scanf(" %[^\n]", search_query);
    search_students(students, student_count, search_query);
    return 0;
}

//================================================== 6
#include <stdio.h>

int main() 
{
    int N, K;

    printf("Въведете N: ");
    scanf("%d", &N);

    printf("Въведете K: ");
    scanf("%d", &K);

    int array[N];

    printf("Въведете масив от %d елемента: ", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &array[i]);
    }

    for (int i = 0; i < N - 1; i++) 
    {
        for (int j = i + 1; j < N; j++) 
        {
            if (array[i] < array[j]) 
            {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }

    int max_sum = 0;
    printf("Тези %d елемента с максимална сума са: ", K);
    for (int i = 0; i < K; i++) 
    {
        printf("%d ", array[i]);
        max_sum += array[i];
    }

    printf("\nМаксималната сума е: %d\n", max_sum);

    return 0;
}

//===================================================== 7

#include <stdio.h>

#define MAX 100

int matrix[MAX][MAX];
int visited[MAX][MAX];
int n, m;

int dRow[] = {0, 1, 0, -1};
int dCol[] = {1, 0, -1, 0};

//proverqvame dali sa pravilno uvedeni kletkite
int isValid(int row, int col, int value) 
{
    return (row >= 0 && row < n && col >= 0 && col < m && !visited[row][col] && matrix[row][col] == value);
}

//obhojdame vseki edin element
int findRegionSize(int row, int col, int value) 
{
    visited[row][col] = 1;
    int size = 1;
    for (int i = 0; i < 4; i++) 
    {
        int newRow = row + dRow[i];
        int newCol = col + dCol[i];
        if (isValid(newRow, newCol, value)) 
        {
            size += findRegionSize(newRow, newCol, value);
        }
    }

    return size;
}

int main() 
{
    printf("Въведете размерите на матрицата (редове и колони): ");
    scanf("%d %d", &n, &m);

    printf("Въведете елементите на матрицата:\n");
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            scanf("%d", &matrix[i][j]);
            visited[i][j] = 0;
        }
    }

    int maxRegionSize = 0;
    int maxRegionValue = 0;

//onaglejdava se matricata
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            if (!visited[i][j]) 
            {
                int currentSize = findRegionSize(i, j, matrix[i][j]);
                if (currentSize > maxRegionSize) 
                {
                    maxRegionSize = currentSize;
                    maxRegionValue = matrix[i][j];
                }
            }
        }
    }
    printf("Най-голямата област е съставена от числото %d и има размер %d.\n", maxRegionValue, maxRegionSize);
    return 0;
}

//==================================================== 8
#include <stdio.h>

#define MAX_SIZE 10

int main() 
{
    int array[MAX_SIZE];
    int n;

    printf("Въведете броя на елементите (до %d): ", MAX_SIZE);
    scanf("%d", &n);

    if (n > MAX_SIZE || n <= 0) 
    {
        printf("Грешка: Броят на елементите трябва да е между 1 и %d.\n", MAX_SIZE);
        return 1;
    }

    printf("Въведете %d цели числа:\n", n);
    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &array[i]);
    }

    int max_count = 0;
    int most_frequent;

    for (int i = 0; i < n; i++) 
    {
        int count = 0;

        for (int j = 0; j < n; j++) 
        {
            if (array[i] == array[j]) 
            {
                count++;
            }
        }

        if (count > max_count) 
        {
            max_count = count;
            most_frequent = array[i];
        }
    }

    printf("Най-често срещаният елемент е: %d (%d пъти).\n", most_frequent, max_count);

    return 0;
}
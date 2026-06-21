//ednomeren masiv s celi chisla broika el opredelqme nie /celi chisla/ da se suzdade vtori ednomeren masiv na bazata na purviq, toi ima za purviq masiv maksimalniq na stoinost el na purviq masiv, posledniq el na vtoriq masiv e broq na nechetnite po stoinost el na purviq masiv ostanalite sa otricatelnite el na purviq masiv]

#include ‹stdio.h›
#include ‹stdlib.h>
int
main (){
int n;
printf("Въведете размер на првия масив:
scanf ("%d", &n);
int aln];
printf ("Въведете елементите на първия
Ma
for (int i =0; i‹n;
i++) {
scanf ("%d", &alil);
｝
int max = al0];
int countodd = 0;
int countNeg = 0;
/І намираме максимум, брой нечетни и отр
for (int i
=0; i < n; i++) {
if (ali] > max)
max = ali]; if (ali]% 2 != 0)
countodd++;
if (alil < 0)
countNeg++;
}
// размер на втория масив = отрицателни
int sizeB = countNeg + 2;
int *b = (int*) malloc(sizeB * sizeof(ir
if (b == NULL) {
printf( "Грешка при заделяне на памет");
return 1;
+
｝
b[0] = max;
// първи елемен
b[sizeB - 1] = countodd; // последен еле

int j = 1;
for(int = 0; i <n && sizeB; i++ )
{
    printf("\n");
}



// двумерен масив с цели числа, да се създаде едномерен масив на базата на първия по следния начин в елемент на едномерен масив представляват елемент на двата диагонала на ДВУМЕРНИЯ МАСИВ НО НЕ ВС, а само тези които са по големи от 10


#include <stdio.h>

int main() {
    int arr[4][4] = {
        {5,  11,  3,  8},
        {2,  15, 12,  6},
        {9,  14, 13,  7},
        {16,  4, 18, 10}
    };

    int n = 4;
    int temp[8];
    int count = 0;
    int i;

    for (i = 0; i < n; i++) {
        if (arr[i][i] > 10) {
            temp[count] = arr[i][i];
            count++;
        }

        if (arr[i][n - 1 - i] > 10 && i != n - 1 - i) {
            temp[count] = arr[i][n - 1 - i];
            count++;
        }
    }

    printf("Dvumeren masiv:\n");
    for (i = 0; i < n; i++) {
        int j;
        for (j = 0; j < n; j++) {
            printf("%4d", arr[i][j]);
        }
        printf("\n");
    }

    printf("\nEdnomenen masiv (diag. elementi > 10): ");
    for (i = 0; i < count; i++) {
        printf("%d ", temp[i]);
    }
    printf("\n");

    return 0;
}
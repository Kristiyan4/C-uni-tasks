#include <stdio.h>

void findMaxSequence(int arr[], int n) 
{
    if (n == 0) return;
    int maxStart = 0, maxLength = 1;
    int currentStart = 0, currentLength = 1;
    for (int i = 1; i < n; i++) 
    {
        if (arr[i] == arr[i - 1]) 
        {
            currentLength++;
        } 
        else 
        {
            if (currentLength > maxLength) 
            {
                maxLength = currentLength;
                maxStart = currentStart;
            }
            currentStart = i;
            currentLength = 1;
        }
    }
    if (currentLength > maxLength) 
    {
        maxLength = currentLength;
        maxStart = currentStart;
    }
    printf("Най-дългата поредица от еднакви елементи е: ");
    for (int i = maxStart; i < maxStart + maxLength; i++) 
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
int main() 
{
    int arr[20];
    int n = 0;
    printf("Въведете елементите на масива (въведете 0 за край):\n");
    while (1) 
    {
        int num;
        scanf("%d", &num);
        
        if (num == 0) 
        {
            break;
        }
        if (n < 20) 
        {
            arr[n++] = num;
        } 
        else 
        {
            printf("Масивът е пълен! Няма място за повече елементи.\n");
            break;
        }
    }
    findMaxSequence(arr, n);
    return 0;
}
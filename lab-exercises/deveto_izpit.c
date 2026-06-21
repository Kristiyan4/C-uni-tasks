#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct 
{
    char code[4];      
    char name[21];
    int weightKg;
    float pricePerKg;
} IceCream;


float calculateTotalPriceByLetter(IceCream* arr, int count, char letter) 
{
    float total = 0.0;
    letter = tolower(letter);

    for (int i = 0; i < count; i++) 
    {
        if (tolower(arr[i].name[0]) == letter) 
        {
            total += arr[i].weightKg * arr[i].pricePerKg;
        }
    }

    return total;
}

// Задача 3 – Запис във текстов файл
int saveIceCreamsToFile(IceCream* arr, int count, float maxPrice, int minWeight) {
    FILE* file = fopen("info.txt", "w");
    if (file == NULL) {
        printf("Грешка при отваряне на файла.\n");
        return 0;
    }

    int writtenCount = 0;

    for (int i = 0; i < count; i++) 
    {
        if (arr[i].pricePerKg < maxPrice && arr[i].weightKg > minWeight) 
        {
            fprintf(file, "%s;%s;%d;%.2fleva\n",
                    arr[i].code,
                    arr[i].name,
                    arr[i].weightKg,
                    arr[i].pricePerKg);
            writtenCount++;
        }
    }

    fclose(file);
    return writtenCount;
}
void readIceCreamFromBinaryByCode(const char* searchCode) 
{
    FILE* file = fopen("icecream.bin", "rb");
    if (file == NULL) 
    {
        printf("Грешка при отваряне на бинарния файл.\n");
        return;
    }

    while (!feof(file)) 
    {
        char code[4];
        int nameLen;
        char name[21];
        int weight;
        float price;

        if (fread(code, sizeof(char), 3, file) != 3) break;
        code[3] = '\0';

        if (fread(&nameLen, sizeof(int), 1, file) != 1) break;
        if (nameLen >= 20) nameLen = 20;

        if (fread(name, sizeof(char), nameLen, file) != nameLen) break;
        name[nameLen] = '\0';

        if (fread(&weight, sizeof(int), 1, file) != 1) break;
        if (fread(&price, sizeof(float), 1, file) != 1) break;

        if (strcmp(code, searchCode) == 0) 
        {
            printf("====================\n");
            printf("IceCream - %s\n", name);
            printf("Price - %.2f BGN\n", price);
            printf("====================\n");
            fclose(file);
            return;
        }
    }

    printf("Сладолед с код '%s' не е открит.\n", searchCode);
    fclose(file);
}
void saveToBinaryFile(IceCream* arr, int count) 
{
    FILE* file = fopen("icecream.bin", "wb");
    if (file == NULL) 
    {
        printf("Грешка при създаване на бинарен файл.\n");
        return;
    }

    for (int i = 0; i < count; i++) 
    {
        fwrite(arr[i].code, sizeof(char), 3, file);
        int nameLen = strlen(arr[i].name);
        fwrite(&nameLen, sizeof(int), 1, file);
        fwrite(arr[i].name, sizeof(char), nameLen, file);
        fwrite(&arr[i].weightKg, sizeof(int), 1, file);
        fwrite(&arr[i].pricePerKg, sizeof(float), 1, file);
    }

    fclose(file);
    printf("Данните бяха записани в icecream.bin\n");
}

int main() 
{
    int n;
    printf("Въведи брой сладоледи (между 6 и 14): ");
    scanf("%d", &n);

    if (n <= 5 || n >= 15) 
    {
        printf("Невалиден брой. Трябва да е между 6 и 14.\n");
        return 1;
    }

    IceCream* iceCreams = (IceCream*) malloc(n * sizeof(IceCream));
    if (iceCreams == NULL) 
    {
        printf("Грешка при заделяне на памет.\n");
        return 1;
    }

    // Въвеждане на сладоледи
    for (int i = 0; i < n; i++) 
    {
        printf("\nСладолед #%d:\n", i + 1);
        printf("Код (напр. A2): ");
        scanf("%s", iceCreams[i].code);
        printf("Име (до 20 символа): ");
        scanf(" %20s", iceCreams[i].name);
        printf("Тегло (в кг): ");
        scanf("%d", &iceCreams[i].weightKg);
        printf("Цена на кг (0.00): ");
        scanf("%f", &iceCreams[i].pricePerKg);
    }

    char letter;
    printf("\nВъведи буква за търсене: ");
    scanf(" %c", &letter);

    float total = calculateTotalPriceByLetter(iceCreams, n, letter);
    if (total > 0)
        printf("Обща цена на сладоледи с %c*: %.2f лв\n", letter, total);
    else
        printf("Няма съвпадения със сладоледи започващи с '%c'\n", letter);

    float maxPrice;
    int minWeight;

    printf("\nВъведи максимална цена (напр. 4.00): ");
    scanf("%f", &maxPrice);
    printf("Въведи минимално тегло (напр. 30): ");
    scanf("%d", &minWeight);

    int saved = saveIceCreamsToFile(iceCreams, n, maxPrice, minWeight);
    if (saved > 0)
        printf("Записани са %d сладоледа във файл info.txt\n", saved);
    else
        printf("Няма сладоледи отговарящи на зададените критерии.\n");

    saveToBinaryFile(iceCreams, n);

    char searchCode[4];
    printf("\nВъведи код за търсене в бинарния файл: ");
    scanf("%s", searchCode);

    readIceCreamFromBinaryByCode(searchCode);

    free(iceCreams);
    return 0;
}
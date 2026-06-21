#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char id[3];
    char name[21];
    int weight;
    float price;
}IceCream;

float returnPrice (IceCream*sladoled, int n, char s){
float totalPrice=0.0;
for (int i = 0; i<n; i++)
{
    if(sladoled[i].name[0]==s)
    {
        price += sladoled[i].price*sladoled[i].weight;
    }
}
return totalPrice;
}

int Count (IceCream*sladoled,int n, float price, int weight)
{
    FILE*fp = fopen("info.txt","w");
    if(fp==NULL)
    {
        exit(-3);
    }
    int count = 0;
    for (int i = 0; i<n; i++)
    {
        if(sladoled[i].price<price && sladoled[i].weight>weight)
        {
            fprintf(fp,"%s - %20[^\n]- %d - %.2f" ,sladoled[i].id, sladoled[i].name, sladoled[i].weight, sladoled[i].price);
            count++;
        }
    }
    return count;
}

void Print (char*code)
{
    FILE*fp=fopen("icecream.bin", "rb");
    if (fp==NULL)
    {
        exit(-4);
    }
    char readCode[3];
    char *name;
    int nameLen; 
    float price;
    int weight;
    int found = 0;


    while (fread(readCode, sizeof(char), 2, fp) == 2)
    {
        readCode[2] = '\0';
        if(fread(&nameLen, sizeof(int), 1, fp) != 1) exit(-4);

        name = malloc(nameLen + 1);
        if (name == NULL ){
            fclose(fp);
            exit(-5);
        }

        if(fread(name, sizeof(char), nameLen, fp) != nameLen){
            free(name);
            fclose(fp);
            exit(-6);

        }

        name[nameLen] = '\0';
        if (fread(&weight, sizeof(int), 1, fp) != 1 ||
            fread(&price, sizeof(float), 1, fp) != 1) {
            free(name);
            fclose(fp);
            exit(-7);

        }

        if (strcmp(code, readCode) == 0) {
            printf("Намерен сладолед:\n");
            printf("Код: %s\n", readCode);
            printf("Име: %s\n", name);
            printf("Тегло: %d kg\n", weight);
            printf("Цена: %.2f лв/кг\n", price);
            found = 1;
            free(name);
            break;
        }

        

        free(name);
    

    }
    if(!found) exit(-9);
    fclose(fp);
    
}





int main()
{
    int n;
    scanf("%d", &n);
    if (n<5 || n>15)
    {
        exit(-1);
    }
    IceCream *sladoled = malloc(n*sizeOf(IceCream));
    if(sladoled ==NULL)
    {
        exit(-2);
    }
    for (int i = 0; i<n; i++)
    {
        scanf("%s", &sladoled[i].id);
        scanf("%20[^\n]", &sladoled[i].name);
        scanf("%d", &sladoled[i].weight);
        scanf("%.2f", &sladoled[i].price);
    }
    free(sladoled);
    return 0;
}


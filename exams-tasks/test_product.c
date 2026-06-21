#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char name [21];
    int id;
    char date [11];
    float price;
}Product;


float avrg_by_price(Product *producti, int n, float price)
{
    int count;
    int cena;
    int found;
    float average;
    for (int i = 0; i<n;i++)
    {
        if (producti[i].price<price)
        {
            count++;
            cena += producti[i].price;
            found++;
        }
    }
    if (found != 0)
    {
    average = cena/count;
    }
    else 
    {
        average = 0;
    }
    return average;
}

int write_text_file(Product *producti, int n, char *date, float price)
{
    FILE *fp = fopen("product.txt", "w");
    if (fp==NULL) exit (-3);
    int count;
    for (int i = 0; i<n;i++)
    {
        if(strcmp(producti[i].date, date)==0 && (producti[i].price>price))
        {
            fprintf("%20 [^\n] - %d - %s - %.2f", producti[i].name, producti[i].id, producti[i].date, producti[i].price);
            count++;
        }
    }
    return count;
}

void print_info(char *target_name, int target_id)
{
    FILE *fp = fopen("product.bin", "rb");
    if (fp==NULL) exit (-5);

    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    rewind(fp);

    int currentPos = 0;
    int found = 0;

    while(currentPos<size)
    {
        int nameLen;
        fread(&nameLen, sizeof(int), 1, fp);
        currentPos += sizeof(int);

        char *name = malloc(n +1);
        if (name == NULL) exit (-7);
        fread(&name, sizeof(char), nameLen, fp);
        name[nameLen] = '\0';
        currentPos += nameLen;

        int code;
        fread(&code, sizeof(int), 1, fp);
        currentPos += sizeof(int);

        char date[11];
        fread(&date, sizeof(char), 10, fp);
        currentPos += 10;

        float price;
        fread(&price, sizeof(float), 1, fp);
        currentPos +=sizeof(float);

        if (strcspn(name, target_id) == 0 && (strcspn(id, target_name)==0))
        {
            printf("Danni na product:  <%20 [^\n]> izpolzvai predi <%s> - cena <%.2f> leva", name, date, price);
            found =1;
        }
    }
    if (found != 0)
    {
        printf("Nqma takiva elementi!");
    }
}


int main()
{
    int n;
    scanf("%d", &n);
    getchar();
    if (n<10||n>30)
    {
        exit (-1);
    }
    Product *producti = malloc(n * sizeof(Product));
    if (producti ==NULL) exit (-2);

    for (int i = 0; i<n;i++)
    {
        fgets(producti[i].name, 21, stdin);
        producti[i].name[strcspn(producti[i].name, '\n')] = '\0';
        scanf("%d", &producti[i].id);
        getchar();
        if (producti[i].id <100 || producti[i].id>999) exit (-6);
        scanf("%s", &producti[i].date);
        getchar();
        scanf("%.2f", &producti[i].price);
        getchar();
    }
free(producti);
return 0;
}

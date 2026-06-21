#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char name [31];
    char date [8];
    long long id;
    float price;
    int kolichestvo;
}Medicine;

void convertDate(char *date, char *result)
{
    char *result[8];
    result[0] = date[3];
    result[1] = date[4];
    result[2] = date[5];
    result[3] = date[6];

    result[4] = date[2];

    result[5] = date[0];
    result[6] = date[1];

    result[7] = '\0';

    return result;
}
Medicine *returnMedicine(Medicine*medicines, int n, char data)
{
    int count = 0; // kolko lekarstva shte ima
    char convertedDate [8]; // novata data za sravnqvaneto
    convertDate(data, convertedDate); // vikame funkciqta da oburnem vtorata data
    for (int i =0; i<n; i++)
    {
        char temp[8];  
        convertDate(medicines[i].date, temp); // tuka prevrushtame datata na lekarstvoto v pravilniq format
        if(strcmp(convertedDate, temp) <0) // funkciqta strcmp ni sravnqva (ako purvoto e po malko izkarva minus) tuk otbroqvame kolko godni lekarstva ima
        {
            count++;
        }
    }
    Medicine *result = malloc(count * sizeof(Medicine)); // tuk si pravim masiva
    int idx = 0; // tova e za da moje da pochva da se pulni masiva ot samoto nachalo, bez nego shte se pulnqt po pozicii (2=2, ne ot 0)
    if (result==NULL) exit(-4);
    for (int i = 0; i<n; i++)
    {
        if (strcmp(convertDate, temp)<0) 
        {
            result[idx] = medicines[i]; // sushtiq cikul, no tuk vmesto da otbroqvame mestoto, go pulnim s danni
            idx++;
        }
    }
return result;
}



int countEl (Medicine *medicines, int n, float min, float max)
{
    FILE *fp = fopen("offer.txt", "w");
    if (fp ==NULL) exit(-5);
    int count = 0;
    for (int i = 0; i<n; i++)
    {
        if(medicines[i].price>min && medicines[i].price<max)
        {
            count++;
            fprintf("<%30[^\n]>\n  <%s>   <%lld>     <%.2f>   " , medicines[i].name, medicines[i].date, medicines[i].id, medicines[i].price);
        }
    }
    return count;
}





void deleteEl (Medicine *medicines, int n, char *name, char *date)
{
    int newSize =n;
    int found = 0;
    for (int i = 0; i<n; i++)
    {
        if (strcmp(medicines[i].name, name) == 0 && strcmp(medicines[i].date, date) ==0) //sravnqvame imeto i datata
        {
            found = 1; // promenqme bull shtoto sme namerili takova lekarstvo, trqbva ni za suobshtenieto nakraq
            for (int j = i; i<n-1; j++) // cikul v cikul, shtoto namerenoto trqbva da go izbutame naj nakraq
            {
                Medicine *temp = *medicines[j]; // nova promenliva za da zapazim namerenoto
                *medicines[j] = *medicines[j+1]; // premestvame tova koeto ne e namereno napred na mqstoto na tova koeto e namereno
                *temp = *medicines[j+1]; // zapisvame namerenoto na mqstoto na nenamerenoto(edna poziciq nazad)
            }
            newSize--;
            *medicines = realloc(medicines, newSize * sizeof(Medicine)); // purvoto e masiva koito shte mu promenqme razmera, vtoroto e s koko shte mu promenqme ramera
            break;
        }

    }
    if (found == 0)
    {
        printf("Nqma takova lekarstvo")
    }
}


int main()
{
    FILE*fp = fopen("medicines.bin", "rb");
    if (fp ==NULL)
    {
        exit(-1);
    }
    int Count = 0;

    fseek (fp, 0, SEEK_END);
    long fileSize = ftell(fp);  // namirame celiq fail kolko elementa ima, ftell broi kolko simvola ima ot nachaloto do kursora
    rewind(fp); //vrushtame kursora v nachaloto

    Count = fileSize/sizeof(Medicine); //celiq fail go delim na struktorata da vidim kolko struktori shte ima

    Medicine *medicines = malloc(count * sizeof(Medicine)); // broq na struktori po struktora
    if (medicines ==NULL) exit(-2);

    fread(medicines, sizeof(Medicine), count, fp); // fread -> kude da se zapishe, goleminata na struktorite, samata struktora, faila
    free(medicines);
    fclose(fp);
    return 0;

}
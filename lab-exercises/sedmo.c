#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FLIGHT_NUM 10
#define MAX_PASSENGER_NAME 50
#define MIN_FLIGHTS 10
#define AVG_FLIGHTS 20
#define MAX_FLIGHTS 50
#define MIN_PASSENGERS 5
#define AVG_PASSENGERS 100
#define MAX_PASSENGERS 256

typedef struct 
{
    char flightNumber[MAX_FLIGHT_NUM];
    char status[20]; 
} Flight;

typedef struct 
{
    char name[MAX_PASSENGER_NAME];
    char status[20];  
} Passenger;

Flight *flights = NULL;
int flightCount = 0;
Passenger **passengers = NULL; 

void showHelp() 
{
    printf("\n==================== ПОМОЩ ====================\n");
    printf("0 - Помощ\n");
    printf("1 - Въвеждане на полети\n");
    printf("2 - Задаване на полет като Активен\n");
    printf("3 - Задаване на полет като Приключил\n");
    printf("4 - Добавяне на полет\n");
    printf("5 - Изтриване на полет\n");
    printf("6 - Редактиране на полет\n");
    printf("7 - Отпечатване на справка за полети\n");
    printf("8 - Добавяне на пътник\n");
    printf("9 - Добавяне на пътник към полет\n");
    printf("10 - Промяна на статус на пътник\n");
    printf("11 - Справка за пътници в полет\n");
    printf("12 - Изход\n");
    printf("==============================================\n");
}

void enterFlights() 
{
    printf("\nВъведете броя на полетите: ");
    scanf("%d", &flightCount);
    if (flightCount < MIN_FLIGHTS || flightCount > MAX_FLIGHTS) 
    {
        printf("Грешка: Броят на полетите трябва да е между %d и %d.\n", MIN_FLIGHTS, MAX_FLIGHTS);
        return;
    }

    if (flights) free(flights);
    flights = (Flight *)malloc(flightCount * sizeof(Flight));

    if (passengers) 
    {
        for (int i = 0; i < flightCount; i++) 
        {
            free(passengers[i]);
        }
        free(passengers);
    }
    passengers = (Passenger **)malloc(flightCount * sizeof(Passenger *));

    for (int i = 0; i < flightCount; i++) 
    {
        printf("Въведете номер на полет %d: ", i + 1);
        scanf("%s", flights[i].flightNumber);
        strcpy(flights[i].status, "Неактивен");
        passengers[i] = (Passenger *)malloc(AVG_PASSENGERS * sizeof(Passenger));
    }
}

void setFlightStatus(int isActive) 
{
    char flightNum[MAX_FLIGHT_NUM];
    printf("Въведете номер на полет: ");
    scanf("%s", flightNum);

    for (int i = 0; i < flightCount; i++) 
    {
        if (strcmp(flights[i].flightNumber, flightNum) == 0) 
        {
            strcpy(flights[i].status, isActive ? "Активен" : "Приключил");
            printf("Статусът на полет %s е променен на %s\n", flights[i].flightNumber, flights[i].status);
            return;
        }
    }
    printf("Грешка: Полет с този номер не е намерен!\n");
}

void printFlights() 
{
    printf("\n================ СПРАВКА ЗА ПОЛЕТИ ================\n");
    printf("№  | Номер на полет | Статус\n");
    printf("-----------------------------------\n");
    for (int i = 0; i < flightCount; i++) 
    {
        printf("%-3d| %-14s | %-10s\n", i + 1, flights[i].flightNumber, flights[i].status);
    }
    printf("===================================================\n");
}

int main() 
{
    int choice;

    printf("==============================================\n");
    printf("        ЛЕТИЩНА СИСТЕМА - УПРАВЛЕНИЕ НА ПЪТНИЦИ И ПОЛЕТИ         \n");
    printf("==============================================\n");

    do 
    {
        printf("\nМеню:\n");
        printf("0 - Помощ\n");
        printf("1 - Въвеждане на полети\n");
        printf("2 - Задаване на полет като Активен\n");
        printf("3 - Задаване на полет като Приключил\n");
        printf("7 - Отпечатване на справка за полети\n");
        printf("12 - Изход\n");
        printf("Изберете опция: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 0: showHelp(); break;
            case 1: enterFlights(); break;
            case 2: setFlightStatus(1); break;
            case 3: setFlightStatus(0); break;
            case 7: printFlights(); break;
            case 12: printf("Изход от програмата...\n"); break;
            default: printf("Невалиден избор! Опитайте отново.\n");
        }
    } 
    while (choice != 12);

    free(flights);
    if (passengers) 
    {
        for (int i = 0; i < flightCount; i++) 
        {
            free(passengers[i]);
        }
        free(passengers);
    }

    printf("\n==============================================\n");
    printf("Автор: Кристиян Йорданов\n");
    printf("Версия: 1.0.0\n");
    printf("==============================================\n");

    return 0;
}
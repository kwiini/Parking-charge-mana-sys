#ifndef PARKMANAGE_H
#define PARKMANAGE_H

#include "dataStructure.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ParkVehs(InVehs head) {
    InVehs p;
    InVehs rear;
    time_t In_time; // 停车时间
    char plateNum[20]; // 车牌号
    int VehsType; // 车型
    int select;
    int count;
    while (1) {
        system("cls");
        count = 0;
        printf("Please enter the license plate number: ");
        scanf("%s", plateNum);
        putchar(10);
        rear = head;
        while (rear->next) {
            if (strcmp(rear->next->plateNum, plateNum) == 0) {
                printf("The car is in the garage! \n");
                count++;
                break;
            }
            rear = rear->next;
        }
        if (count != 0) {
            break;
        }
        printf("***********************************\n");
        printf("** 1. Landaulet         **\n");
        printf("** 2. Large             **\n");
        printf("***********************************\n");
        printf("Please choose: ");
        scanf("%d", &select);
        if (select == 1 || select == 2) {
            p = (InVehs)malloc(sizeof(InVehsNode));
            strcpy(p->plateNum, plateNum);
            p->VehsType = select;
            time(&In_time);
            p->In_time = In_time;
            p->next = NULL;
            rear->next = p;
            printf("Stop successfully! \n");
            break;
        } else {
            printf("Input error, please re-select! \n");
            system("pause");
        }
    }
} 

void WriteFile_InVehs(InVehs head) {
    InVehs p = head->next;
    FILE *fp;
    if ((fp = fopen("InParkingLot.txt", "w")) == NULL) {
        printf("File opening failure! \n");
        return;
    }
    while (p) {
        fprintf(fp, "%s\t%d\t%d\n", p->plateNum, p->VehsType, p->In_time);
        p = p->next;
    }
    fclose(fp);
}

#endif
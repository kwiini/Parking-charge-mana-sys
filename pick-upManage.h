#ifndef PICKUPMANAGE_H
#define PICKUPMANAGE_H

#include "dataStructure.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void TakeVehs(InVehs head, OutVehs first, double mon, double mon1) {
    InVehs p = head, re = head->next;
    OutVehs q, rear = first;
    time_t Out_time;
    char plateNum[20];
    int count;
    double money; // 花费
    printf("Please enter the license plate number: ");
    scanf("%s", plateNum);
    while (re) {
        if (strcmp(re->plateNum, plateNum) == 0) {
            count++;
            p->next = re->next;
            break;
        }
        re = re->next;
        p = p->next;
    }
    if (count == 0) {
        printf("There is no car in the garage! \n");
        return;
    }
    while (rear->next) {
        rear = rear->next;
    }
    q = (OutVehs)malloc(sizeof(OutVehsNode));
    strcpy(q->plateNum, plateNum);
    q->VehsType = re->VehsType;
    time(&Out_time);
    q->In_time = re->In_time;
    q->Out_time = Out_time;
    if (q->VehsType == 1) {
        money = (q->Out_time - q->In_time) * mon / 60.0;
    } else {
        money = (q->Out_time - q->In_time) * mon1 / 60.0;
    }
    q->money = money;
    q->next = NULL;
    rear->next = q;
    free(re);
    printf("Pickup success! \n");
    printf("The parking costs %f yuan! \n", money);
} 

void WriteFile_OutVehs(OutVehs head) {
    OutVehs p = head->next;
    FILE *fp;
    if ((fp = fopen("OutParkingLot.txt", "w")) == NULL) {
        printf("File opening failure! \n");
        return;
    }
    while (p) {
        fprintf(fp, "%s\t%ld\t%ld\t%ld\t%f\n", p->plateNum, p->VehsType, p->In_time, p->Out_time, p->money);
        p = p->next;
    }
    fclose(fp);
}

#endif
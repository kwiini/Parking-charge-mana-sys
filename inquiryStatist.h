#ifndef INQUIRYSTATIST_H
#define INQUIRYSTATIST_H

#include "dataStructure.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void viewInVehs(InVehs head) {
    InVehs p = head->next;
    struct tm *timein;
    char VehsType[15];
    printf("Vehicle information in the garage\n");
    printf("***********************************\n");
    if (p == NULL) {
        printf("There are no cars in the garage! \n");
        return;
    }
    printf("license plate number\tvehicle model\tstopping time\n");
    while(p) {
        if (p->VehsType == 1) {
            strcpy(VehsType, "Small");
        } else {
            strcpy(VehsType, "Large");
        }
        timein = localtime(&p->In_time);
        printf("%s\t%s\t%d/%d/%d %d:%d\n", p->plateNum, VehsType, timein->tm_year + 1900, timein->tm_mon + 1, timein->tm_mday, timein->tm_hour, timein->tm_min);
        p = p->next;
    }
}

void viewOutVehs(OutVehs head) {
    OutVehs p = head->next;
    struct tm *timein;
    struct tm *timeout;
    char VehsType[5];
    printf("Vehicle toll records are as follows: \n");
    printf("**********************************************************************\n");
    if (p == NULL) {
        printf("No charge record! \n");
        return;
    }
    printf("license plate number\tvehicle model\tstopping time\tpick-up time\ttoll\n");
    while(p) {
        if (p->VehsType == 1) {
            strcpy(VehsType, "Small");
        } else {
            strcpy(VehsType, "Large");
        }
        timein = localtime(&p->In_time);
        timeout = localtime(&p->Out_time);
        printf("%s\t%s\t%d/%d/%d %d:%d\t%d/%d/%d %d:%d\t%f\n", p->plateNum, VehsType, timein->tm_year + 1900, timein->tm_mon + 1, timein->tm_mday, timein->tm_hour, timein->tm_min, timeout->tm_year + 1900, timeout->tm_mon + 1, timeout->tm_mday, timeout->tm_hour, timeout->tm_min, p->money);
        p = p->next;
    }
}

void FindPlateNum(InVehs head, OutVehs first) { // 按照车牌号查找车辆
    InVehs p = head->next;
    OutVehs q = first->next;
    struct tm *timein;
    struct tm *timeout;
    char VehsType[15];
    char state[7] = "";
    char plateNum[20];
    int count = 0;
    printf("Please enter the license plate number: ");
    scanf("%s", plateNum);
    while (q) {
        if (strcmp(q->plateNum, plateNum) == 0) {
            count++;
            printf("license plate number\tvehicle model\tstopping time\tpick-up time\ttoll\tstate\n");
            strcpy(state, "Removed");
            if (q->VehsType == 1) {
                strcpy(VehsType, "Small");
            } else {
                strcpy(VehsType, "Large");
            }
            timein = localtime(&q->In_time);
            timeout = localtime(&q->Out_time);
            printf("%s\t%s\t%d/%d/%d %d:%d\t%d/%d/%d %d:%d\t%f\t%s\n", q->plateNum, VehsType, timein->tm_year + 1900, timein->tm_mon + 1, timein->tm_mday, timein->tm_hour, timein->tm_min, timeout->tm_year + 1900, timeout->tm_mon + 1, timeout->tm_mday, timeout->tm_hour, timeout->tm_min, q->money, state);
        }
        q = q->next;
    }
    while (p) {
        if (strcmp(p->plateNum, plateNum) == 0) {
            if (count == 0) {
                printf("license plate number\tvehicle model\tstopping time\tpick-up time\ttoll\n");
            }
            count++;
            strcpy(state, "Parking");
            if (p->VehsType == 1) {
                strcpy(VehsType, "Small");
            } else {
                strcpy(VehsType, "Large");
            }
            timein = localtime(&(p->In_time));
            printf("%s\t%s\t%d/%d/%d %d:%d\t\t\t%s\n", p->plateNum, VehsType, timein->tm_year + 1900, timein->tm_mon + 1, timein->tm_mday, timein->tm_hour, timein->tm_min, state);
            break;
        }
        p = p->next;
    }
    if (count == 0) {
        printf("There's no record of the license plate! \n");
    }
}

void FindParkingDate(InVehs head, OutVehs first) { // 按照日期查找车辆
    InVehs p = head->next;
    OutVehs q = first->next;
    int year, month, day;
    struct tm *timein;
    struct tm *timeout;
    char VehsType[15]; // 车型
    char state[7] = ""; // 状态
    int count = 0;
    printf("Please enter the year, month and day: ");
    scanf("%d %d %d", &year, &month, &day);
    year -= 1900; // 转为 struct rm 结构中的时间值
    while (q) {
        timein = localtime(&q->In_time);
        timeout = localtime(&q->Out_time);
        if ((timein->tm_year == year && timein->tm_mon == month && timein->tm_mday == day) || (timeout->tm_year == year && timeout->tm_mon == month && timeout->tm_mday == day)) {
            count++;
            printf("license plate number\tvehicle model\tstopping time\tpick-up time\ttoll\tstate\n");
            strcpy(state, "Removed");
            if (q->VehsType == 1) {
                strcpy(VehsType, "Small");
            } else {
                strcpy(VehsType, "Large");
            }
            printf("%s\t%s\t%d/%d/%d %d:%d\t%d/%d/%d %d:%d\t%f\t%s\n", q->plateNum, VehsType, timein->tm_year + 1900, timein->tm_mon + 1, timein->tm_mday, timein->tm_hour, timein->tm_min, timeout->tm_year + 1900, timeout->tm_mon + 1, timeout->tm_mday, timeout->tm_hour, timeout->tm_min, q->money, state);
        }
        q = q->next;
    }
    while (p) {
        timein = localtime(&(p->In_time));
        if (timein->tm_year == year && timein->tm_mon == month && timein->tm_mday == day) {
            if (count == 0) {
                printf("license plate number\tvehicle model\tstopping time\tpick-up time\ttoll\tstate\n");
            }
            count++;
            strcpy(state, "Parking");
            if (p->VehsType == 1) {
                strcpy(VehsType, "Small");
            } else {
                strcpy(VehsType, "Large");
            }
            timein = localtime(&(p->In_time));
            printf("%s\t%s\t%d/%d/%d %d:%d\t\t\t%s\n", p->plateNum, VehsType, timein->tm_year + 1900, timein->tm_mon + 1, timein->tm_mday, timein->tm_hour, timein->tm_min, state);
        }
        p = p->next;
    }
    if (count == 0) {
        printf("There's no record of the license plate! \n");
    }
}

void FindVehsInfo(InVehs head, OutVehs first) {
    int select;
    while (1) {
        system("cls");
        printf("***********************************\n");
        printf("** 1. Search by license plate    **\n");
        printf("** 2. Query by date              **\n");
        printf("** 2. Return                     **\n");
        printf("***********************************\n\n");
        printf("Please choose: ");
        scanf("%d", &select);
        switch (select) {
            case 1:
            FindPlateNum(head, first);
            break;
            case 2:
            FindParkingDate(head, first);
            break;
            case 3:
            return;
            default:
            printf("Input error, please re-select! \n");
        }
        system("pause");
    }
}

#endif
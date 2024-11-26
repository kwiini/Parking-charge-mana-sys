#ifndef CHARGESTANDARDMANAGE_H
#define CHARGESTANDARDMANAGE_H

#include "dataStructure.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void viewFreeStandard(double mon, double mon1) {
    printf("Charge standard management\n");
    printf("***********************************\n");
    printf("** 1. Landaulet: %f （元/分钟）\n", mon);
    printf("** 2. Large: %f （元/分钟）\n", mon1);
    printf("***********************************\n");
}

void ManaFreeStandard(double *mon, double *mon1) { // 收费标准管理
    int n;
    while (1) {
        viewFreeStandard(*mon, *mon1);
        printf("\n\n");
        printf("***********************************\n");
        printf("** 1. Revision of charges   **\n");
        printf("** 2. Return                **\n");
        printf("*********************************\n\n");
        printf("Please choose: ");
        scanf("%d", &n);
        if (n == 1) {
            printf("Please enter small car fee (Yuan/min): ");
            scanf("%lf", mon);
            printf("Please enter large car fee (Yuan/min): ");
            scanf("%lf", mon1);
            printf("save successfully! \n");
            break;
        } else if (n == 2) {
            return;
        } else {
            printf("Input error, please re-select! \n");
        }
    }
}

#endif
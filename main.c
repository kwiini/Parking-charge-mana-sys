#include "dataStructure.h"
#include "parkManage.h"
#include "pick-upManage.h"
#include "chargeStandardManage.h"
#include "inquiryStatist.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void CreateInVehsList(InVehs head);
void CreateOutVehsList(OutVehs head);

void menu() {
    printf(" Parking charge management system\n\n");
    printf("***********************************\n");
    printf("** 1. Park");
    printf("** 2. Pick up");
    printf("** 3. View vehicle information in the garage");
    printf("** 4. View charge history");
    printf("** 5. View fees");
    printf("** 6. Query vehicle information");
    printf("** 7. Management charge standard");
    printf("** 0. Exit");
    printf("***********************************\n\n");
    printf("Please choose: ");
}

int main() {
    InVehs head;
    OutVehs first;
    int num;
    double mon = 0.1, mon1 = 0.2;
    head = (InVehs)malloc(sizeof(InVehsNode));
    head->next = NULL;
    first = (OutVehs)malloc(sizeof(OutVehsNode));
    first->next = NULL;
    CreateInVehsList(head); // 创建并初始化车库中车辆信息
    CreateOutVehsList(first); // 创建并初始化收费记录信息
    while (1) {
        system("cls");
        menu();
        scanf("%d", &num);
        system("cls");
        printf(" Parking charge management system\n\n");
        switch (num) {
            case 1:
            ParkVehs(head); // 停车登记函数
            WriteFile_InVehs(head); // 将车库中车辆信息存入文件
            break;
            case 2:
            TakeVehs(head, first, mon, mon1); // 取车登记函数
            WriteFile_InVehs(head); // 将车库中车辆信息存入文件
            WriteFile_OutVehs(first); // 将收费记录存入文件
            break;
            case 3:
            viewInVehs(head); // 查看车库中车辆信息
            break;
            case 4:
            viewOutVehs(first); // 查看收费记录
            break;
            case 5:
            viewFreeStandard(mon, mon1); // 查看收费记录
            break;
            case 6:
            FindVehsInfo(head, first); // 查找车库中车辆信息
            break;
            case 7:
            ManaFreeStandard(&mon, &mon1); // 管理收费标准
            break;
            case 0:
            WriteFile_InVehs(head); // 将车库中车辆信息存入文件
            WriteFile_OutVehs(first); // 将收费记录存入文件
            exit(0);
            default:
            printf("Input error, please re-select! \n");
        }
        system("pause");
    }
    return 0;
}

void CreateInVehsList(InVehs head) {
    InVehs p, rear = head;
    char plateNum[20];
    FILE *fp;
    time_t In_time;
    time_t VehsType;
    if ((fp = fopen("InParkingLot.txt", "r")) == NULL) {
        fp = fopen("InParkingLot.txt", "w");
        return;
    }
    while (fscanf(fp, "%s\t%ld\t%ld", plateNum, &VehsType, &In_time) != EOF) {
        p = (InVehs)malloc(sizeof(InVehsNode));
        strcpy(p->plateNum, plateNum);
        p->VehsType = VehsType;
        p->In_time = In_time;
        rear->next = p;
        rear = p;
    }
    rear->next = NULL;
    fclose(fp);
}

void CreateOutVehsList(OutVehs head) {
    OutVehs p, rear = head;
    time_t In_time, Out_time;
    char plateNum[20];
    double money;
    FILE *fp;
    int VehsType;
    if ((fp = fopen("OutParkingLot.txt", "r")) == NULL) {
        fp = fopen("OutParkingLot.txt", "w");
        fclose(fp);
        return;
    }
    while (fscanf(fp, "%s\t%ld\t%ld\t%ld\t%lf", plateNum, &VehsType, &In_time, &Out_time, &money) != EOF) {
        p = (OutVehs)malloc(sizeof(OutVehsNode));
        strcpy(p->plateNum, plateNum);
        p->VehsType = VehsType;
        p->In_time = In_time;
        p->Out_time = Out_time;
        rear->next = p;
        rear = p;
    }
    rear->next = NULL;
    fclose(fp);
}
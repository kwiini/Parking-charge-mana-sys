#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <time.h>

typedef struct InVehicles {
    char plateNum[20]; // 车牌号
    int VehsType; // 车型（小型，大型）
    time_t In_time; // 车辆进入时间
    struct InVehicles *next;
} InVehsNode, *InVehs;

typedef struct OutVehicles {
    char plateNum[20]; // 车牌号
    int VehsType; // 车型（小型，大型）
    time_t In_time; // 车辆进入时间
    time_t Out_time; // 车辆离开时间
    double money; // 所收费用
    struct OutVehicles *next;
} OutVehsNode, *OutVehs;

#endif

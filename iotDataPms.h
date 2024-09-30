#ifndef __IOTDATAOMS_H__
#define __IOTDATAOMS_H__
#include <Arduino.h>


class iotDataPms{
    public:
        String max_range_0_3um;
        String max_range_0_5um;
        String max_range_1_0um;
        String max_range_2_5um;
        String max_range_5_0um;
        String max_range_10_0um;
        String um_total;//V1.10

        iotDataPms();
};
#endif
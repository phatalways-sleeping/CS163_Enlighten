#pragma once
#include <time.h>

double getTime(auto start, auto end){
    double time = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    return time;
}

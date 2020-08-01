#include "../includes/misc.h"

#include <sys/time.h>
#include <stdlib.h>
#include <math.h>

int digits(double num)
{
    if (num <= 0.0) return 1;
    else return log10(num) + 1;
}

void clamp(double* val, double min, double max)
{
    *val = (*val > min) ? ((*val < max) ? *val : max) : min;
}

double min(double a, double b)
{
    return (a < b) ? a : b;
}

double max(double a, double b)
{
    return (a > b) ? a : b;
}

// Time
double time_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000.0 + tv.tv_usec * 0.001;
}

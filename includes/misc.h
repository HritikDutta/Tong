#ifndef MISC_H
#define MISC_H

int digits(double num);
void clamp(double* val, double min, double max);
double min(double a, double b);
double max(double a, double b);

double time_ms();

#endif // MISC_H
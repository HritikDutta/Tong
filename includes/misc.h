#ifndef MISC_H
#define MISC_H

// Maths
int digits(double num);
void clamp(double* val, double min, double max);
double min(double a, double b);
double max(double a, double b);

// Time
double time_ms();

// Random
void init_random();
double i_random();    // Returns a random double between 0 and 1

#endif // MISC_H
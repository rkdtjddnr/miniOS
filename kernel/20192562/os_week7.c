#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int check_in_circle(const double* x, const double* y)
{
	double dis = sqrt(pow(*x, 2) + pow(*y, 2));
	//printf("dis %lf\n", dis);
	if(dis > 1.0) return 0;
	else return 1;
}

void cal_pi(double* result, const int* circle, const int total)
{
	*result = 4 * ((double)(*circle) / (double)(total)); 
}

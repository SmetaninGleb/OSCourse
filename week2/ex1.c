#include <limits.h>
#include <stdio.h>
#include <float.h>

int main() {
	int integer = INT_MAX;
	float fl = FLT_MAX;
	double d = DBL_MAX;
	printf ("%d\n%f\n%f\n", integer, fl, d);
	printf ("%d\n%d\n%d", sizeof(integer), sizeof(fl), sizeof(d));
	return 0;
}

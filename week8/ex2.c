#include <stdlib.h>

int main() {
    int *ptr;
    for (int i = 1; i <= 10; i++) {
        ptr = malloc(1024 * 1024 * 10);
        memset(ptr, 0, sizeof(ptr));
        sleep(1);
    }
}

/*
Exercise 2:

 
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 0  0 480508 1375668      0      0    4    4     0     5    6    1 16 12 72  0  0
 0  0 480508 1373388      0      0   64    0     1     0 10724 21837 16 19 65  0  0
 0  0 480508 1367376      0      0 22528    0   352     0 14150 29748 28 18 54  0  0
 0  0 480472 1352984      0      0 5952    0    93     0 15960 31029 21 22 57  0  0
 0  0 480468 1351148      0      0 2752    0    43     0 12380 25098 16 14 70  0  0
 0  0 480400 1357600      0      0    0    0     0     0 10552 19647 15 10 76  0  0
 0  0 480400 1359732      0      0    0    0     0     0 10064 19754 10  7 82  0  0
 0  0 480400 1359868      0      0    0    0     0     0 10088 20945  8 11 81  0  0
 0  0 480400 1362660      0      0    0    0     0     0 10261 19727  7  8 85  0  0
 0  0 480396 1362704      0      0   64    0     1     0 9837 19339  8  7 85  0  0
 0  0 480396 1363160      0      0    0    0     0     0 10130 19690 10  6 84  0  0
 0  0 480396 1363152      0      0    0    0     0     0 10308 20454  8  6 86  0  0
 0  0 480396 1363184      0      0    0    0     0     0 9852 19296  9  5 86  0  0
 0  0 480396 1363180      0      0    0    0     0     0 9978 19757 12  6 82  0  0
 0  0 480396 1363180      0      0    0    0     0     0 9186 18956 14 16 69  0  0
 0  0 480396 1363240      0      0    0    0     0     0 9630 18875  5 13 82  0  0
 0  0 480396 1363332      0      0    0    0     0     0 10236 21050 10 12 78  0  0
 0  0 480396 1363916      0      0 1024    0    16     0 9032 17806 11  9 79  0  0
 0  0 480396 1363976      0      0    0    0     0     0 8017 17948 15 22 64  0  0
 0  0 480396 1363972      0      0    0    0     0     0 8784 17716  8  6 86  0  0

It means that the computer allocates virtual memory when physical memory is not enough.
*/

/*
Exercise 3:

The process of this program is in the top list, then it allocate a lot of resources of the computer.
*/
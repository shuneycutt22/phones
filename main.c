#include <stdio.h>
#include <stdlib.h>
#include "phones.h"

#define LIMIT 100

int main() {
    char * nums[LIMIT];
    char filename[25];
    int n = 0;
    int i;

    printf("Enter file name: ");
    scanf("%s", filename);
    /* initialize array */
    for (i=0; i<100; i++) nums[i] = NULL;  /* NULL pointer = no string */
    n = findPhoneNumbers(filename, nums, LIMIT);
    sortPhoneNumbers(nums, n);
    printPhoneNumbers(nums, n);

    return EXIT_SUCCESS;
}

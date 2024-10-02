/*
-Project: Binary Counter
-Description: To count the number of 1's in the binary equivalent of a number
-Version: 1.0
-File: binarycount.c
-Author: Gowri A Sankar
-Date: 02-10-24
*/

#include <stdio.h>

void main()
{
    int num, count = 0;
    printf("Enter a number:");
    scanf("%d", &num); // number taken from user
    while (num > 0)
    {
        if (num & 1) // Checks LSB is 1
        {
            count++; // count increased by 1
        }
        num = num >> 1; // number is right shifted to check the next bit
    }
    printf("number of 1's:%d", count);
}
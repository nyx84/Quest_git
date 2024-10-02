/*
-Project: Quadratic Equation Slover
-Description: To evuluate the roots of a quadratic equation;capture coeffecient values from user
-Version: 1.0
-File: QuadraticEqSlove.c 
-Author: Gowri A Sankar
-Date: 02-10-24
*/

#include <stdio.h>
#include <math.h>

void slove(float,float,float);

void main()
{
    float a,b,c;
    printf("Enter the value for the first coefficent:");
    scanf("%f",&a); //coefficent a value taken from user
    printf("Enter the value for the second coefficent:");
    scanf("%f",&b); //coefficent b value taken from user
    printf("Enter the value for the third coefficent:");
    scanf("%f",&c); //coefficent c value taken from user
    slove(a,b,c);
}

void slove(float a, float b, float c)
{
    float discriminant, root1, root2, realPart, imaginaryPart;
    discriminant=(b*b)-(4*a*c);

    if (discriminant > 0) //Discriminant value positive: two real distinct roots
    {
        root1 = (-b + sqrt(discriminant)) / (2 * a);
        root2 = (-b - sqrt(discriminant)) / (2 * a);
        printf("The roots are real and different\n");
        printf("Root 1: %f\n", root1);
        printf("Root 2: %f\n", root2);
    }

    else if (discriminant == 0) //Discriminant value zero: one real repeated root
    {
        root1 = -b / (2 * a);
        printf("The roots are real and the same.\n");
        printf("Root 1:%f\n", root1);
        printf("Root 2:%f\n", root1);
    }

    else //Discriminant value negative: Two complex roots
    {
        realPart = -b / (2 * a);
        imaginaryPart = sqrt(-discriminant) / (2 * a);
        printf("The roots are complex and different.\n");
        printf("Root 1: %f + %fi\n", realPart, imaginaryPart);
        printf("Root 2: %f - %fi\n", realPart, imaginaryPart);
    }
}

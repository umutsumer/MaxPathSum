#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int isPrime(int num);
int maxSum(int *arr, int len);
int *toArray(int *arr, FILE *fp, int *len);

int main()
{

    int *arr = (int *)malloc(sizeof(int)); 
    int max;
    int len = 0;

    FILE *fp = fopen("pyramid.txt", "r");
    arr = toArray(arr, fp, &len);
    max = maxSum(arr, len);
    printf("%d", max);

    return 0;
}

int isPrime(int num)
{
    int i;

    if ((num > 2 && num % 2 == 0) || num < 2)
    {
        return 0;
    }
    for (i = 3; i <= sqrt(num); i += 2)
    {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

int maxSum(int *arr, int len) 
{
    int i = 0; // Index of array
    int j = 1; // Number of steps.
    int max = arr[0];

    while (i + j < len) // Walking over the array until index+step number passes the maximum length.
    {
        if (isPrime(arr[i + j]) && isPrime(arr[i + j + 1])) 
        {
            return max;
        }

        if (!isPrime(arr[i + j]) && !isPrime(arr[i + j + 1])) 
        {
            if (arr[i + j] > arr[i + j + 1])
            { 
                max += arr[i + j];
                i = i + j;
            }
            else
            {
                max += arr[i + j + 1];
                i = i + j + 1;
            }
        }
        else if (!isPrime(arr[i + j]))
        {
            max += arr[i + j];
            i = i + j;
        }
        else
        {
            max += arr[i + j + 1];
            i = i + j + 1;
        }
        j++;
    }
    return max;
}

int *toArray(int *arr, FILE *fp, int *len) // Converting input text to an integer array.
{ 

    fscanf(fp, "%d", &arr[(*len)++]);
    while (!feof(fp))
    {
        arr = (int *)realloc(arr, ((*len) + 1) * sizeof(int)); // Expanding the array as we scan values.
        fscanf(fp, "%d", &arr[(*len)++]);
    }
    return arr;
}



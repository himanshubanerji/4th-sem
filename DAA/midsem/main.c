// Program: Given an array[] having repetitive elements find GCD of the lowest and highest frequency elements

#include <stdio.h>

int findGcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }

    return findGcd(b, a % b);
}

int main()
{

    int arr[10] = {35, 35, 35, 5, 10, 7, 5, 7, 8, 8};

    int bucket_array[45] = {0};
    for (int i = 0; i < 10; i++)
    {
        bucket_array[arr[i]]++;
    }

    int max_fq_index, min_fq_index;
    max_fq_index = min_fq_index = arr[0];
    for (int i = 0; i < 40; i++)
    {
        min_fq_index = ((bucket_array[i] < bucket_array[min_fq_index]) && (bucket_array[i] != 0)) ? i : min_fq_index;
        max_fq_index = ((bucket_array[i] > bucket_array[max_fq_index]) && (bucket_array[i] != 0)) ? i : max_fq_index;
    }

    printf("The GCD of %d and %d is: %d\n", max_fq_index, min_fq_index, findGcd(max_fq_index, min_fq_index));

    return 0;
}
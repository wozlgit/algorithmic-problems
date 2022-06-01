// This is an answer to the Leetcode problem '1480. Running Sum of 1d Array'

#include <malloc.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* runningSum(int* nums, int numsSize, int* returnSize){
    int runningSum, i;
    int *sums = (int*) malloc(sizeof(int) * numsSize);

    runningSum = 0;

    for(i = 0; i < numsSize; i++) {
        runningSum += nums[i];
        sums[i] = runningSum;
    }
    *returnSize = numsSize;
    return sums;
}

int main() {
    int nums[] = {1, 2, 3, 4};
    int returnSize;
    int *sums = runningSum(nums, 4, &returnSize);
    printf("%d\n", returnSize);
    for(int i = 0; i < returnSize; i++) {
        printf("sums[%d]: %d\n", i, sums[i]); 
    }
    return 0;
}
// This is an answer to the Leetcode problem '867. Transpose Matrix'

#include <malloc.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** transpose(int** matrix, int matrixSize, int* matrixColSize, int* returnSize, int** returnColumnSizes){
    // Each column of the matrix has the same size... so why is matrixColSize an array!?
    int **transposedMatrix = malloc(sizeof(int*) * matrixColSize[0]);
    *returnColumnSizes = malloc(sizeof(int) * matrixColSize[0]);
    *returnSize = matrixColSize[0];

    for(int i = 0; i < matrixColSize[0]; i++) transposedMatrix[i] = NULL;
    for(int i = 0; i < matrixSize; i++) {
        for(int j = 0; j < matrixColSize[i]; j++) {
            if(transposedMatrix[j] == NULL) {
                transposedMatrix[j] = malloc(sizeof(int) * matrixSize);
            }
            transposedMatrix[j][i] = matrix[i][j];
            (*returnColumnSizes)[j] = matrixSize;
        }
    }
    return transposedMatrix;
}

int main() {
    int col1[3] = {1, 2, 3};
    int col2[3] = {4, 5, 6};
    int col3[3] = {7, 8, 9};
    int *matrix[3] = {col1, col2, col3};
    const int matrixColumnCount = 3;
    int matrixRowCounts[matrixColumnCount];
    for(int i = 0; i < matrixColumnCount; i++) matrixRowCounts[i] = 3;
    int transposedColumnCount;
    int *transposedRowCounts;
    int **transposedMatrix = transpose(matrix, matrixColumnCount, matrixRowCounts, &transposedColumnCount, &transposedRowCounts);
    printf("[");
    for(int i = 0; i < transposedColumnCount; i++) {
        if(i != 0) printf(", ");
        printf("[");
        for(int j = 0; j < transposedRowCounts[i]; j++) {
            if(j != 0) printf(", ");
            printf("%d", transposedMatrix[i][j]);
        }
        printf("]");
    }
    printf("]\n");
    return 0;
}
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool hasAllCodes(char * s, int k) {
    if(s == NULL) return false;
    const uint32_t requiredBinaryCodeCount = 1U << k;

    uint8_t binaryCodesFound[requiredBinaryCodeCount];
    uint32_t binaryCodesFoundCount, binaryNumber, multiplier;
    
    for(uint32_t i = 0; i < requiredBinaryCodeCount; i++) binaryCodesFound[i] = 0;

    // Get the initial binary number
    multiplier = 1;
    binaryNumber = 0;
    for(uint32_t i = 0; i < k; i++) {
        if(s[i] == '\0') return false;
        s[i] = s[i] - '0';
        binaryNumber += s[i] * multiplier;
        multiplier *= 2;
    }
    binaryCodesFound[binaryNumber] = 1;
    binaryCodesFoundCount = 1;
    //multiplier was multiplied by 2 one extra time, so we have to undo that such
    //that we can use multiplier later on.
    multiplier /= 2;
    // Get all the other numbers
    for(uint32_t i = k; s[i] != '\0'; i++) {
        // Convert s[i] from a character to a digit
        s[i] = s[i] - '0';
        // Perform a right bit-shift by 1 on the previous number (divide it by 2):
        // this will remove the first digit in the number and shift the multipliers of
        // all other digits by one. Then add the last digit of this number in.
        binaryNumber = (binaryNumber >> 1) + s[i] * multiplier;

        // If the current binary number has already been found 
        // (if binaryCodesFound[binaryNumber] is 1), then dont increment binaryCodesFoundCount
        binaryCodesFoundCount += 1 - binaryCodesFound[binaryNumber];
        if(binaryCodesFoundCount >= requiredBinaryCodeCount) return true;
        
        binaryCodesFound[binaryNumber] = 1;
    }
    return false;
}

int main() {
    char s[] = "00110110\0";
    printf("%d\n", hasAllCodes(s, 2));
    return 0;
}
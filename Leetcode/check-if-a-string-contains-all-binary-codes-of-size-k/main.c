#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool hasAllCodes(char * s, int k) {
    if(s == NULL) return false;
    const uint32_t requiredBinaryCodeCount = 1U << k;

    uint8_t binaryCodesFound[requiredBinaryCodeCount];
    uint32_t binaryCodesFoundCount, binaryNumber;
    
    memset(binaryCodesFound, 0, sizeof(binaryCodesFound));

    binaryNumber = 0;
    binaryCodesFoundCount = 0;
    for(uint32_t i = 0; s[i] != '\0'; i++) {
        // Convert s[i] from a character to a digit
        s[i] = s[i] - '0';
        if(i < k) {
            // Get the initial number
            binaryNumber += (s[i] << i);
        }
        else {
            // If the previous binary number has already been found
            // (if binaryCodesFound[binaryNumber] is 1), then dont increment binaryCodesFoundCount
            binaryCodesFoundCount += 1 - binaryCodesFound[binaryNumber];
            if(binaryCodesFoundCount >= requiredBinaryCodeCount) return true;
            
            binaryCodesFound[binaryNumber] = 1;

            // Perform a right bit-shift by 1 on the previous number (divide it by 2):
            // this will remove the first digit in the number and shift the multipliers of
            // all other digits by one. Then add the last digit of this number in (the last
            // digit is bit-shifted to the left by k - 1 because it is the last digit in the
            // binary number of size k and thus the multiplier is 2^(k -1)).
            binaryNumber = (binaryNumber >> 1) + (s[i] << (k - 1));
        }
    }
    binaryCodesFoundCount += 1 - binaryCodesFound[binaryNumber];
    if(binaryCodesFoundCount >= requiredBinaryCodeCount) return true;
    return false;
}

int main() {
    char s[] = "00110110\0";
    printf("%d\n", hasAllCodes(s, 2));
    return 0;
}
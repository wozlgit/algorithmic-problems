#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool hasAllCodes(char * s, int k) {
    uint64_t *binaryCodesFound;
    uint32_t binaryCodesFoundCount;
    bool alreadyFound;
    uint32_t strLength;

    const uint32_t requiredBinaryCodeCount = 1U << k;
    
    for(strLength = 0; s[strLength] != '\0'; strLength++);
    // s.length - k + 1 will be the number of distinct binary numbers of size k
    // that can fit in a string of length strLength.
    if(strLength - k + 1 < requiredBinaryCodeCount) return false;
    
    binaryCodesFound = (uint64_t *) malloc(sizeof(uint64_t) * requiredBinaryCodeCount);
    
    // Get the initial binary number
    uint64_t multiplier = 1;
    binaryCodesFound[0] = 0;
    for(uint32_t i = 0; i < k; i++) {
        s[i] = s[i] - '0';
        binaryCodesFound[0] += s[i] * multiplier;
        multiplier *= 2;
    }
    //multiplier was multiplied by 2 one extra time, so we have to undo that such
    //that we can use multiplier later on.
    multiplier /= 2;
    binaryCodesFoundCount = 1;
    // Get all the other numbers
    for(uint32_t i = k; i < strLength; i++) {
        // Convert s[i] from a character to a digit
        s[i] = s[i] - '0';
        // Perform a right bit-shift by 1 on the previous number (divide it by 2):
        // this will remove the first digit in the number and shift the multipliers of
        // all other digits by one. Then add the last digit of this number in.
        binaryCodesFound[binaryCodesFoundCount] = (binaryCodesFound[binaryCodesFoundCount - 1] >> 1)
                                                + s[i] * multiplier;
        
        alreadyFound = false;
        // Check if this binary number has already been found, in which case set
        // alreadyFound to true, to signal that this binary number had already been found.
        for(uint32_t j = 0; j < binaryCodesFoundCount; j++) {
            if(binaryCodesFound[j] == binaryCodesFound[binaryCodesFoundCount]) {
                alreadyFound = true;
                break;
            }
        }
        if(!alreadyFound) binaryCodesFoundCount++;
    }
    free(binaryCodesFound);
    if(binaryCodesFoundCount >= requiredBinaryCodeCount) return true;
    else return false;
}

int main() {
    char *s = (char *) malloc(sizeof(char) * 8);
    s[0] = '0';
    s[1] = '0';
    s[2] = '1';
    s[3] = '1';
    s[4] = '0';
    s[5] = '1';
    s[6] = '1';
    s[7] = '0';
    printf("%d\n", hasAllCodes(s, 2));
    free(s);
    return 0;
}
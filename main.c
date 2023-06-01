#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void ft_swap(char** s1, char** s2) {
    char* strTemp;

    strTemp = *s1;
    *s1 = *s2;
    *s2 = strTemp;
}

char* addStrings(char* s1, char* s2) {
    int sign1 = 0;
    int sign2 = 0;
    if (s1 != NULL && s2 != NULL) {
        if (s1[0] == '-') {
            sign1 = 1;
        }
        if (s2[0] == '-') {
            sign2 = 1;
        }
    }

    // s2 length has to be  larger if we want to loop less:
    char* addS1= &s1[sign1];
    char* addS2 = &s2[sign2];
    if (strlen(addS1) > strlen(addS2)) {
        ft_swap(&addS1, &addS2);
    }

    s1 = addS1;
    s2 = addS2;

    // Calculate length of both char*
    size_t len1 = strlen(addS1);
    size_t len2 = strlen(addS2);

    int sign = 0;
    if ((sign1 && sign2) || sign1) {
        sign++;
    }
    int resultLength = len1 + len2 + sign;
    int resultLengthTmp = len1 + len2 + sign;
    char* result = (char*)malloc(sizeof(char) * (len1 + len2 + 1 + sign));
    memset(result, '0', resultLength);
    result[resultLength] = '\0';
    resultLength--;

    int carry = 0;
    int len22 = len2 - 1;
    for (int i = len1 - 1; i >= 0 ; i--) {
        // Do school mathematics, compute sum of current digits and carry
        int sum = 0;
        if ((sign1 && sign2) || (!sign1 && !sign2)) {
            sum = ((s1[i] - '0') + (s2[len22] - '0') + carry);
        } else {
            sum = ((s1[i] + '0') - (s2[len22] + '0') + carry);
            sum = sum * (-1);
        }
        len22--;
        if (len22 == 0) {
            break;
        }
        result[resultLength] = (sum % 10) + '0';
        resultLength--;
        // Calculate carry for next step
        carry = sum / 10;
    }

    // Add remaining digits of larger number
    for (int i = len22; i >= 0; i--) {
        int sum = ((s2[i] - '0') + carry);
        result[resultLength] = (sum % 10) + '0';
        resultLength--;
        carry = sum / 10;
    }

    // Add remaining carry
    if (carry) {
        result[resultLength] = (carry + '0');
        resultLength--;
    }

    // Remove leading zeros
    int leadingZeros = 0;
    while (result[leadingZeros] == '0') {
        leadingZeros++;
    }
    if (leadingZeros == resultLengthTmp) {
        leadingZeros--;
    }

    char* finalResult = (char*)malloc(sizeof(char) * (resultLengthTmp - leadingZeros + 1 + sign));
    if (sign) {
        finalResult[0] = '-';
    }
    memcpy(finalResult + sign, result + leadingZeros, sizeof(char) * (resultLengthTmp - leadingZeros + sign));
    finalResult[resultLengthTmp - leadingZeros + sign] = '\0';

    free(result);
    return finalResult;
}

char* multiplyStrings(char* s1, char* s2) {
    int sign1 = 0;
    int sign2 = 0;
    if (s1 != NULL && s2 != NULL) {
        if (s1[0] == '-') {
            sign1 = 1;
        }
        if (s2[0] == '-') {
            sign2 = 1;
        }
    }

    // s2 length has to be  larger if we want to loop less:
    char* addS1= &s1[sign1];
    char* addS2 = &s2[sign2];
    if (strlen(addS1) > strlen(addS2)) {
        ft_swap(&addS1, &addS2);
    }

    s1 = addS1;
    s2 = addS2;

    size_t len1 = strlen(addS1);
    size_t len2 = strlen(addS2);

    int sign = 0;
    if ((sign1 || sign2) && (!sign1 || !sign2)) {
        sign++;
    }
    // Result can be at most len1 + len2 digits long
    int resultLength = len1 + len2;
    char* result = (char*)malloc(sizeof(char) * (resultLength + 1 + sign));
    memset(result, '0', resultLength);
    result[resultLength] = '\0';

    for (int i = len1 - 1; i >= 0; i--) {
        int carry = 0;
        int digit1 = s1[i] - '0';

        for (int j = len2 - 1; j >= 0; j--) {
            int digit2 = s2[j] - '0';

            int temp = (result[i + j + 1] - '0') + (digit1 * digit2) + carry;
            result[i + j + 1] = (temp % 10) + '0';
            carry = temp / 10;
        }
        result[i] += carry;
    }

    // Remove leading zeros
    int leadingZeros = 0;
    while (result[leadingZeros] == '0') {
        leadingZeros++;
    }
    if (leadingZeros == resultLength) {
        leadingZeros--;
    }

    char* finalResult = (char*)malloc(sizeof(char) * (resultLength - leadingZeros + 1 + sign));
    if (sign) {
        finalResult[0] = '-';
    }
    memcpy(finalResult + sign, result + leadingZeros, sizeof(char) * (resultLength - leadingZeros + sign));
    finalResult[resultLength - leadingZeros + sign] = '\0';

    free(result);
    return finalResult;
}

int main() {
    char s1[] = "198234";
    char s2[] = "12";
    char s1neg[] = "-198234";
    char s2neg[] = "-12";

    // addition DONE
//    "198234";
//   +"    12";
//     198246
    char* a = addStrings(s1, s2);
    printf("Addition result (++=+): %s\n", a);
    free(a);

    // addition + (-sign) DONE
//    "-198234";
//   +"-    12";
//     -198246
    char* b = addStrings(s1neg, s2neg);
    printf("Addition result (--=-): %s\n", b);
    free(b);

    // subtraction DONE
//    " 198234";
//   +"-    12";
//      198222
    char* c = addStrings(s1, s2neg);
    printf("Addition result (+-=+): %s\n", c);
    free(c);

    // subtraction + (-sign) DONE
//    "-198234";
//   +"     12";
//     -198222
    char* d = addStrings(s1neg, s2);
    printf("Addition result (-+=-): %s\n", d);
    free(d);

    // --------------------------------------------------------------------------------------------

    // positive result
//     "198234";
//    *"    12";
//     " 396468"
//   + "198234 "   -> SHIFT
//      2378808
    char* aa = multiplyStrings(s1, s2);
    printf("Multiplication result (++=+): %s\n", aa);
    free(aa);

    // positive result
//     "-198234";
//    *"-    12";
//     " 396468"
//   + "198234 "     -> SHIFT
//      2378808
    char* bb = multiplyStrings(s1neg, s2neg);
    printf("Multiplication result (--=+): %s\n", bb);
    free(bb);

    // negative result
//     " 198234";
//    *"-    12";
//     " 396468"
//  + "-198234 "    -> SHIFT
//     -2378808
    char* cc = multiplyStrings(s1, s2neg);
    printf("Multiplication result (+-=-): %s\n", cc);
    free(cc);

    // negative result
//     "-198234";
//    *"     12";
//     " 396468"
//  + "-198234 "    -> SHIFT
//     -2378808
    char* dd = multiplyStrings(s1neg, s2);
    printf("Multiplication result (-+=-): %s\n", dd);
    free(dd);
    return 0;
}
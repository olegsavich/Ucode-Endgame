#include "../inc/header.h"

char *mx_intToChar(int n) {
    char *arr = (char *)malloc(55);
    long num = n;
    int i = 0;

    if (num == 0)
        arr[i] = '0';

    while (num != 0) {
        arr[i] = (num % 10) + '0';
        num /= 10;
        i++;
    }

    i--;
    for (int j = 0; j < i; j++, i--) {
            char temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
    }    
    return arr;
}

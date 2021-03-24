#include <stdio.h>
#include <locale.h>

#define SIZE 11
#define ZERO_CHAR 48
#define P_CHAR 94
#define END "end"

int arrayFirst[SIZE] = {};
int arraySecond[SIZE] = {};


int* arrayAdd(int* arrayF, int* arrayS);
int* arraySub(int* arrayF, int* arrayS);
int* arrayMul(int* arrayF, int* arrayS);

void inputArrays();
void printArrayFirst();
void printArraySecond();


int main() {
    setlocale(LC_ALL, "Russian");
    inputArrays();
    printArrayFirst();
    printArraySecond();
    arrayAdd(arrayFirst, arraySecond);
    arraySub(arrayFirst, arraySecond);
    arrayMul(arrayFirst, arraySecond);
    return 0;
}

/*
 *
 */

int* arrayAdd(int* arrayF, int* arrayS){
    int arrayRes[SIZE] = {};
    for (int i = 0; i < SIZE; ++i) {
        arrayRes[i] = arrayF[i] + arrayS[i];
    }
    for (int i = SIZE - 1; i >= 0; --i) {
        if(arrayRes[i] != 0)
            printf("%dx%c%d ", arrayRes[i], P_CHAR, i);
    }
    printf("\n");
}

/*
 *
 */
int* arraySub(int* arrayF, int* arrayS){
    int arrayRes[SIZE] = {};
    for (int i = 0; i < SIZE; ++i) {
        arrayRes[i] = arrayF[i] - arrayS[i];
    }
    for (int i = SIZE - 1; i >= 0; --i) {
        if(arrayRes[i] != 0)
            printf("%dx%c%d ", arrayRes[i], P_CHAR, i);
    }
    printf("\n");
}

/*
 *
 */
int* arrayMul(int* arrayF, int* arrayS){
    int arrayRes[SIZE * 2] = {};
    for (int i = 0; i < SIZE; ++i) {
        for(int j = 0; j < SIZE; ++j){
            arrayRes[i + j] += arrayF[i] * arrayS[j];
        }
    }
    for (int i = (SIZE - 1) * 2; i >= 0; --i) {
        if(arrayRes[i] != 0)
            printf("%dx%c%d ", arrayRes[i], P_CHAR, i);
    }
    printf("\n");
}

/*
 *
 */
void inputArrays(){
    for(int i = 0; i < SIZE; ++i){
        printf("Type coefficient for extent %d\nFor end of input, type '%s'\n ", i, END);
        char inputNumber[SIZE] = {};
        scanf("%s", inputNumber);
        printf("%s\n", inputNumber);
        printf("%d\n", (int)inputNumber[i]);
        if(inputNumber[0] == 'e' && inputNumber[1] == 'n' && inputNumber[2] == 'd'){
            break;
        }
        else{
            int resInputNumber = 0;
            int multiplier = 1;
            for(int j = SIZE - 1; j >= 0; --j){
                if((int)inputNumber[j] == 0){
                    continue;
                } else {
                    resInputNumber += ((int)inputNumber[j] - ZERO_CHAR) * multiplier;
                    multiplier *= 10;
                }
            }
            arrayFirst[i] =  resInputNumber;
        }
    }

    for(int i = 0; i < SIZE; ++i){
        printf("Type coefficient for extent %d\nFor end of input, type '%s'\n ", i, END);
        char inputNumber[SIZE] = {};
        scanf("%s", inputNumber);
        printf("%s\n", inputNumber);
        printf("%d\n", (int)inputNumber[i]);
        if(inputNumber[0] == 'e' && inputNumber[1] == 'n' && inputNumber[2] == 'd'){
            break;
        }
        else{
            int resInputNumber = 0;
            int multiplier = 1;
            for(int j = SIZE - 1; j >= 0; --j){
                if((int)inputNumber[j] == 0){
                    continue;
                } else {
                    resInputNumber += ((int)inputNumber[j] - ZERO_CHAR) * multiplier;
                    multiplier *= 10;
                }
            }
            arraySecond[i] =  resInputNumber;
        }
    }
}

/*
 *
 */
void printArrayFirst(){
    for (int i = SIZE - 1; i >= 0; --i) {
        if(arrayFirst[i] != 0)
            printf("%dx%c%d ", arrayFirst[i], P_CHAR, i);
    }
    printf("\n");
}

/*
 *
 */
void printArraySecond(){
    for (int i = SIZE - 1; i >= 0; --i) {
        if(arraySecond[i] != 0)
            printf("%dx%c%d ", arraySecond[i], P_CHAR, i);
    }
    printf("\n");
}
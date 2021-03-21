#include <stdio.h>
#include <locale.h>
#include <unistd.h>

#define SIZE 11
#define P_CHAR 94
#define END 404

int arrayFirst[SIZE] = {};
int arraySecond[SIZE] = {};

void printHello();
unsigned int sleep (unsigned int sec);

int* arrayAdd(int* arrayF, int* arrayS);
int* arraySub(int* arrayF, int* arrayS);
int* arrayMul(int* arrayF, int* arrayS);

void inputArrays();
void printArrayFirst();
void printArraySecond();


int main() {
    setlocale(LC_ALL, "Russian");
    printHello();
    inputArrays();
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
        printf("Type coefficient for extent %d\nFor end of input, type %d\n ", i, END);
        int inputNumber;
        scanf("%d", &inputNumber);
        if(inputNumber == END)
            break;
        else
            arrayFirst[i] =  inputNumber;
    }

    for(int i = 0; i < SIZE; ++i){
        printf("Type coefficient for extent %d\nFor end of input, type %d\n ", i, END);
        int inputNumber;
        scanf("%d", &inputNumber);
        if(inputNumber == END)
            break;
        else
            arraySecond[i] =  inputNumber;
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
}

/*
 *
 */
void printArraySecond(){
    for (int i = SIZE - 1; i >= 0; --i) {
        if(arraySecond[i] != 0)
            printf("%dx%c%d ", arraySecond[i], P_CHAR, i);
    }
}

void printHello(){
    printf("%s","𝕎𝕖𝕝𝕔𝕠𝕞𝕖 𝕥𝕠 𝕡𝕠𝕝𝕪𝕟𝕠𝕞 𝕒𝕕𝕕𝕚𝕟𝕘 𝕒𝕟𝕕 𝕠𝕥𝕙𝕖𝕣 𝕤𝕥𝕦𝕗𝕗 𝕡𝕣𝕠𝕘𝕣𝕒𝕞");
}
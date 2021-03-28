#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define SIZE 11
#define P_CHAR 94
#define END 404

int arrayFirst[SIZE] = {};
int arraySecond[SIZE] = {};

int* arrayAdd(int* arrayF, int* arrayS);
int* arraySub(int* arrayF, int* arrayS);
int* arrayMul(int* arrayF, int* arrayS);
float* arrayDiv(int* arrayF, int extent, int coefficient);

void inputArrays();
float* initArrayFloat();
int* initArrayInt();
void printArrayInt(int *array);
void printArrayFloat(float *array);

int main() {
    setlocale(LC_ALL, "Russian");
    inputArrays();
    arrayAdd(arrayFirst, arraySecond);
    arraySub(arrayFirst, arraySecond);
    arrayMul(arrayFirst, arraySecond);
    int coefficient, extent;
    printf("Type coefficient of monom for division: \n");
    scanf("%d", &coefficient);
    printf("Type extent of monom for division: \n");
    scanf("%d", &extent);
    float *res = arrayDiv(arrayFirst, extent, coefficient);
    printArrayFloat(res);
    return 0;
}


int* initArrayInt(){
    int* res = (int*) malloc(sizeof(int) * SIZE);
    for (int i = 0; i < SIZE; i++){
        res[i] = 0;
    }
    return res;
}

float* initArrayFloat(){
    float* res = (float*) malloc(sizeof(float) * SIZE);
    for (int i = 0; i < SIZE; i++){
        res[i] = 0;
    }
    return res;
}

void printArrayInt(int *array){
    int flag = 0;
    for (int i = SIZE - 1; i >= 0; --i) {
        if(array[i] != 0)
            printf("%s%dx%c%d ", (array[i] > 0 && flag++ != 0) ? "+" : "", array[i], P_CHAR, i);
    }
}

void printArrayFloat(float *array){
    int flag = 0;
    printf("The result of polynom division:  \n");
    for (int i = SIZE - 1; i >= 0; --i) {
        if((array[i] > 0.000001) || (array[i] < -0.000001))
            printf("%s%.2fx%c%d ", (array[i] > 0 && flag++ != 0) ? "+" : "", array[i], P_CHAR, i);
    }
}

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

int* arrayAdd(int* arrayF, int* arrayS){
    int arrayRes[SIZE] = {};
    for (int i = 0; i < SIZE; ++i) {
        arrayRes[i] = arrayF[i] + arrayS[i];
    }
    printf("The result of polynom addition:  \n");
    printArrayInt(arrayRes);
    printf("\n");
}

int* arraySub(int* arrayF, int* arrayS){
    int arrayRes[SIZE] = {};
    for (int i = 0; i < SIZE; ++i) {
        arrayRes[i] = arrayF[i] - arrayS[i];
    }
    printf("The result of polynom subtraction:  \n");
    printArrayInt(arrayRes);
    printf("\n");
}

int* arrayMul(int* arrayF, int* arrayS){
    int arrayRes[SIZE * 2] = {};
    for (int i = 0; i < SIZE; ++i) {
        for(int j = 0; j < SIZE; ++j){
            arrayRes[i + j] += arrayF[i] * arrayS[j];
        }
    }
    printf("The result of polynom multiplication:  \n");
    printArrayInt(arrayRes);
    printf("\n");
}

float* arrayDiv(int* arrayF, int extent, int coefficient){
    int maxPower = 0;
    float* res = initArrayFloat();
    for (int i = SIZE-1; i > 0; i--){
        if (i < extent)
            break;
        if(arrayF[i] != 0){
            res[i - extent] = (float)arrayF[i] / (float)coefficient;
        }
    }
    return res;
}
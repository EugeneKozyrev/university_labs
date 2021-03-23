#include <stdio.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>

#define SIZE 11
#define P_CHAR 94
#define END "end"

int arrayFirst[SIZE] = {};
int arraySecond[SIZE] = {};

void printHello();
unsigned int sleep (unsigned int sec);

//int* polynomDiv(int* arrayF, int*  arrayS);

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
int* polynomDiv(int* arrayF, int*  arrayS){
    printHello();
}

int* arrayDiv(int* arrayF, int* arrayS){
    int arrayRes[SIZE] = {};
    int flagF = 0;
    int flagS = 0;
    for(int i = 0; i < SIZE; ++i){
        if(arrayF[i] != 0)
            flagF++;
    }
    for(int i = 0; i < SIZE; ++i){
        if(arrayS[i] != 0)
            flagS++;
    }
    if(flagS == 0){
        perror("ERROR: DIVISION BY ZERO");
        return 0;
    } else if (flagF == 0 && flagS == 0){
        printf("%d", 0);
    } else if (flagS > flagF){
        perror("ERROR: THE POWER OF THE DIVISOR MUST BE LESS THAN OR EQUAL TO THE POWER OF THE DIVIDEND!");
        return 0;
    } else {
        polynomDiv(arrayF, arrayS);
    }


}
*/
/*
 *
 */
void inputArrays(){
    for(int i = 0; i < SIZE; ++i){
        char inputNumber[20];
        printf("Type coefficient for extent %d\nFor end of input, type '%s'\n ", i, END);
        scanf("%s", inputNumber);
        if(inputNumber[0] == 'e' && inputNumber[1] == 'n' && inputNumber[2] == 'd')
            break;
        else{
            int resInputNumber = 0;
            int multiplier = 1;
            for(int i = 0; i < 1; ++i, multiplier *= 10){
                if((int)inputNumber[i] == 48){
                    resInputNumber += 0 * multiplier;
                } else if ((int)inputNumber[i] == 49){
                    resInputNumber += 1 * multiplier;
                } else if ((int)inputNumber[i] == 50){
                    resInputNumber += 2 * multiplier;
                } else if ((int)inputNumber[i] == 51){
                    resInputNumber += 3 * multiplier;
                } else if ((int)inputNumber[i] == 52) {
                    resInputNumber += 4 * multiplier;
                } else if ((int)inputNumber[i] == 53){
                    resInputNumber += 5 * multiplier;
                } else if ((int)inputNumber[i] == 54){
                    resInputNumber += 6 * multiplier;
                } else if ((int)inputNumber[i] == 55){
                    resInputNumber += 7 * multiplier;
                } else if ((int)inputNumber[i] == 56) {
                    resInputNumber += 8 * multiplier;
                } else if ((int)inputNumber[i] == 57) {
                    resInputNumber += 9 * multiplier;
                } else {
                    perror("ERROR");
                    //i--;
                    continue;
                }
            }
            arrayFirst[i] =  resInputNumber;
        }
    }

    for(int i = 0; i < SIZE; ++i){
        char inputNumber[20];
        printf("Type coefficient for extent %d\nFor end of input, type '%s'\n ", i, END);
        scanf("%s", inputNumber);
        if(inputNumber[0] == 'e' && inputNumber[1] == 'n' && inputNumber[2] == 'd')
            break;
        else{
            int resInputNumber = 0;
            int multiplier = 1;
            for(int i = 0; i < 1; ++i, multiplier *= 10){
                if((int)inputNumber[i] == 48){
                    resInputNumber += 0 * multiplier;
                } else if ((int)inputNumber[i] == 49){
                    resInputNumber += 1 * multiplier;
                } else if ((int)inputNumber[i] == 50){
                    resInputNumber += 2 * multiplier;
                } else if ((int)inputNumber[i] == 51){
                    resInputNumber += 3 * multiplier;
                } else if ((int)inputNumber[i] == 52) {
                    resInputNumber += 4 * multiplier;
                } else if ((int)inputNumber[i] == 53){
                    resInputNumber += 5 * multiplier;
                } else if ((int)inputNumber[i] == 54){
                    resInputNumber += 6 * multiplier;
                } else if ((int)inputNumber[i] == 55){
                    resInputNumber += 7 * multiplier;
                } else if ((int)inputNumber[i] == 56) {
                    resInputNumber += 8 * multiplier;
                } else if ((int)inputNumber[i] == 57) {
                    resInputNumber += 9 * multiplier;
                } else {
                    perror("ERROR");
                    //i--;
                    continue;
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
    printf("%s\n","Hello");
}
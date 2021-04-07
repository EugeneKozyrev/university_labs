#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

#define END 404
#define P_CHAR 94

int* arrayFirst;
int* arraySecond;

int arrayMaxExtentChoice();
int* initArrayInt(int maxExtent);
float* initArrayFloat(int maxExtent);
void inputArrays(int maxExtent);
void inputArray(int maxExtent);
void printArrayInt(int *array, int maxExtent);
void printArrayFloat(float *array, int maxExtent);


int* arrayAdd(int* arrayF, int* arrayS, int maxExtent);
int* arraySub(int* arrayF, int* arrayS, int maxExtent);
int* arrayMul(int* arrayF, int* arrayS, int maxExtent);
float* arrayDiv(int* arrayF, int extent, int coefficient, int maxExtent);
int* arrayDiff(int* arrayF, int maxExtent);
int differentiationRes(int* arrayF, int maxExtent);
float certainIntegral(int* arrayF, float* arrayRes, int maxExtent, int lowerLimit, int upperLimit);


int main() {
    setlocale(LC_ALL, "Russian");
    while(1){
    int userChoice;
    printf("Введите желаемое действие над полиномами: \n");
    printf("1: Сложение полиномов \n");
    printf("2: Вычитание полиномов \n");
    printf("3: Умножение полиномов \n");
    printf("4: Деление полинома на моном \n");
    printf("5: Нахождение производной \n");
    printf("6: Нахождение интеграла \n");
    scanf("%d", &userChoice);
        if(userChoice == 1){
            int maxExtent = arrayMaxExtentChoice();
            arrayFirst = initArrayInt(maxExtent);
            arraySecond = initArrayInt(maxExtent);
            inputArrays(maxExtent);
            int* addResult = arrayAdd(arrayFirst, arraySecond, maxExtent);
            printf("Результат сложения полинома и полинома:  \n");
            printArrayInt(addResult, maxExtent);
            free(arrayFirst);
            free(arraySecond);
            free(addResult);
            break;
        } else if (userChoice == 2){
            int maxExtent = arrayMaxExtentChoice();
            arrayFirst = initArrayInt(maxExtent);
            arraySecond = initArrayInt(maxExtent);
            inputArrays(maxExtent);
            int* subResult = arraySub(arrayFirst, arraySecond, maxExtent);
            printf("Результат вычитания полинома из полинома:  \n");
            printArrayInt(subResult, maxExtent);
            free(arrayFirst);
            free(arraySecond);
            free(subResult);
            break;
        } else if (userChoice == 3){
            int maxExtent = arrayMaxExtentChoice();
            arrayFirst = initArrayInt(maxExtent);
            arraySecond = initArrayInt(maxExtent);
            inputArrays(maxExtent);
            int* mulResult = arrayMul(arrayFirst, arraySecond, maxExtent);
            printf("Результат умножения полинома на полином:  \n");
            printArrayInt(mulResult, maxExtent);
            free(arrayFirst);
            free(arraySecond);
            free(mulResult);
            break;
        } else if (userChoice == 4){
            int maxExtent = arrayMaxExtentChoice();
            arrayFirst = initArrayInt(maxExtent);
            inputArray(maxExtent);
            int coefficient, extent;
            printf("Введите коэфициент монома: \n");
            scanf("%d", &coefficient);
            printf("Введите степень монома: \n");
            scanf("%d", &extent);
            float* divResult = arrayDiv(arrayFirst, extent, coefficient, maxExtent);
            printf("Результат деления полинома на моном:  \n");
            printArrayFloat(divResult, maxExtent);
            free(arrayFirst);
            free(arraySecond);
            free(divResult);
            break;
        } else if (userChoice == 5){
            int maxExtent = arrayMaxExtentChoice();
            arrayFirst = initArrayInt(maxExtent);
            inputArray(maxExtent);
            int* diffResult = arrayDiff(arrayFirst, maxExtent);
            int res = differentiationRes(diffResult, maxExtent);
            printf("Результат дифференцирования полинома в точке x0: %d\n", res);
            free(arrayFirst);
            free(diffResult);
            break;
        } else if (userChoice == 6){
            int upperLimit, lowerLimit;
            printf("Введите верхний предел: \n");
            scanf("%d", &upperLimit);
            printf("Введите нижний предел: \n");
            scanf("%d", &lowerLimit);
            int maxExtent = arrayMaxExtentChoice();
            arrayFirst = initArrayInt(maxExtent);
            inputArray(maxExtent);
            float* temp;
            float result = certainIntegral(arrayFirst, temp, maxExtent, lowerLimit, upperLimit);
            printf("Результат: %.2f \n", result);
            free(arrayFirst);
            free(temp);
            break;
        } else {
            printf("Выберите одно из доступных действий \n");
            fflush(stdout);
        }
    }
    return 0;
}

int arrayMaxExtentChoice(){
    int userMaxExtent;
    printf("Введите максимальную степень полиномов: \n");
    scanf("%d", &userMaxExtent);
    return ++userMaxExtent;
}

int* initArrayInt(int maxExtent){
    int* arrayRes = (int*) malloc(sizeof(int) * maxExtent);
    for (int i = 0; i < maxExtent; i++){
        arrayRes[i] = 0;
    }
    return arrayRes;
}

float* initArrayFloat(int maxExtent){
    float* arrayRes = (float*) malloc(sizeof(float) * maxExtent);
    for (int i = 0; i < maxExtent; i++){
        arrayRes[i] = 0;
    }
    return arrayRes;
}

void inputArrays(int maxExtent){
    for(int i = 0; i < maxExtent; ++i){
        printf("Введите коэффицент для степени %d\nДля окончания ввода введите %d\n ", i, END);
        int inputNumber;
        scanf("%d", &inputNumber);
        if(inputNumber == END)
            break;
        else
            arrayFirst[i] =  inputNumber;
    }

    for(int i = 0; i < maxExtent; ++i){
        printf("Введите коэффицент для степени %d\nДля окончания ввода введите %d\n ", i, END);
        int inputNumber;
        scanf("%d", &inputNumber);
        if(inputNumber == END)
            break;
        else
            arraySecond[i] =  inputNumber;
    }
}

void inputArray(int maxExtent){
    for(int i = 0; i < maxExtent; ++i){
        printf("Введите коэффицент для степени %d\nДля окончания ввода введите %d\n ", i, END);
        int inputNumber;
        scanf("%d", &inputNumber);
        if(inputNumber == END)
            break;
        else
            arrayFirst[i] =  inputNumber;
    }
}

void printArrayInt(int *array, int maxExtent){
    int flag = 0;
    for (int i = maxExtent - 1; i >= 0; --i) {
        if(array[i] != 0)
            printf("%s%dx%c%d ", (array[i] > 0 && flag++ != 0) ? "+" : "", array[i], P_CHAR, i);
    }
    printf("\n");
}

void printArrayFloat(float *array, int maxExtent){
    int flag = 0;
    for (int i = maxExtent - 1; i >= 0; --i) {
        if((array[i] > 0.000001) || (array[i] < -0.000001))
            printf("%s%.2fx%c%d ", (array[i] > 0 && flag++ != 0) ? "+" : "", array[i], P_CHAR, i);
    }
    printf("\n");
}

int* arrayAdd(int* arrayF, int* arrayS, int maxExtent){
    int* arrayRes = initArrayInt(maxExtent);
    for (int i = 0; i < maxExtent; ++i) {
        arrayRes[i] = arrayF[i] + arrayS[i];
    }
    return arrayRes;
}

int* arraySub(int* arrayF, int* arrayS, int maxExtent){
    int* arrayRes = initArrayInt(maxExtent);
    for (int i = 0; i < maxExtent; ++i) {
        arrayRes[i] = arrayF[i] - arrayS[i];
    }
    return arrayRes;
}

int* arrayMul(int* arrayF, int* arrayS, int maxExtent){
    int* arrayRes = initArrayInt(maxExtent * 2);
    for (int i = 0; i < maxExtent; ++i) {
        for(int j = 0; j < maxExtent; ++j){
            arrayRes[i + j] += arrayF[i] * arrayS[j];
        }
    }
    return arrayRes;
}

float* arrayDiv(int* arrayF, int extent, int coefficient, int maxExtent){
    float* res = initArrayFloat(maxExtent);
    for (int i = maxExtent - 1; i > 0; i--){
        if (i < extent)
            break;
        if(arrayF[i] != 0){
            res[i - extent] = (float)arrayF[i] / (float)coefficient;
        }
    }
    return res;
}

int* arrayDiff(int* arrayF, int maxExtent){
    int* arrayRes = initArrayInt(maxExtent);
    for(int i = 1; i < maxExtent; ++i){
        arrayRes[i - 1] = arrayF[i] * i;
    }
    return arrayRes;
}

int differentiationRes(int* arrayF, int maxExtent){
    int result = 0;
    int x;
    printf("Введите точку: \n");
    scanf("%d", &x);
    for(int i = 0; i < maxExtent; ++i){
        result += arrayF[i] * pow(x, i);
    }
    return result;
}

float certainIntegral(int* arrayF, float* arrayRes, int maxExtent, int lowerLim, int upperLim){
    arrayRes = (float*)initArrayFloat(maxExtent);
    for(int i = 0; i < maxExtent; ++i){
        arrayRes[i + 1] = (float)arrayF[i] / (float)(i + 1);
    }
    float sumUpperLim = 0;
    float sumLowerLim = 0;
    for(int i = 0; i < maxExtent; ++i){
        sumUpperLim += (float)pow(upperLim, i) * arrayRes[i];
        sumLowerLim += (float)pow(lowerLim, i) * arrayRes[i];
    }
    float result = sumUpperLim - sumLowerLim;
    return result;
}
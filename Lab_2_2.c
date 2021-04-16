#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
//#include <locale.h>

#define RANGE 2147483646
#define TRY 100
#define P_CHAR 94

double* arrayFirst;
double* arraySecond;

int arrayMaxExtentChoice(char* name);
double* initArray(int maxExtent);
void inputArray(double* array, int maxExtent);
void printArray(double *array, int maxExtent);
double* arrayAdd(double* arrayLarger, double* arraySmaller, int maxExtentLarger, int maxExtentSmaller);
double* arraySub(double* arrayLarger, double* arraySmaller, int maxExtentLarger, int maxExtentSmaller);
double* arrayMul(double* arrayLarger, double* arraySmaller, int maxExtentLarger, int maxExtentSmaller);
double* arrayDiv(double* array, int extent, double coefficient, int maxExtent);
double* arrayDiff(double* array, int maxExtent);
double differentiationRes(double* array, int maxExtent);
double certainIntegral(double* array, double* arrayRes, int maxExtent, int lowerLim, int upperLim);

int main() {
    SetConsoleOutputCP(CP_UTF8);
    //setlocale(LC_ALL, "Russian");
    int idx = 0;
    while (idx++ < TRY) {
        int userChoice = RANGE;
        printf("Введите желаемое действие над полиномами: \n");
        printf("1: Сложение полиномов \n");
        printf("2: Вычитание полиномов \n");
        printf("3: Умножение полиномов \n");
        printf("4: Деление полинома на моном \n");
        printf("5: Нахождение производной \n");
        printf("6: Нахождение интеграла \n");
        scanf("%d", &userChoice);
        if (userChoice == RANGE) break;
        else if (userChoice == 1) {
            int maxExtent1 = arrayMaxExtentChoice("первого");
            int maxExtent2 = arrayMaxExtentChoice("второго");
            arrayFirst = initArray(maxExtent1);
            arraySecond = initArray(maxExtent2);
            inputArray(arrayFirst, maxExtent1);
            inputArray(arraySecond, maxExtent2);
            double *addResult;
            int maxExtentToFunc;
            if (maxExtent1 > maxExtent2) {
                maxExtentToFunc = maxExtent1;
                addResult = arrayAdd(arrayFirst, arraySecond, maxExtent1, maxExtent2);
            } else {
                maxExtentToFunc = maxExtent2;
                addResult = arrayAdd(arraySecond, arrayFirst, maxExtent2, maxExtent1);
            }
            printf("Результат сложения полиномов:  \n");
            printArray(addResult, maxExtentToFunc);
            free(arrayFirst);
            free(arraySecond);
            free(addResult);
            break;
        } else if (userChoice == 2) {
            int maxExtent1 = arrayMaxExtentChoice("первого");
            int maxExtent2 = arrayMaxExtentChoice("второго");
            arrayFirst = initArray(maxExtent1);
            arraySecond = initArray(maxExtent2);
            inputArray(arrayFirst, maxExtent1);
            inputArray(arraySecond, maxExtent2);
            double *addResult;
            int maxExtentToFunc;
            if (maxExtent1 > maxExtent2) {
                maxExtentToFunc = maxExtent1;
                addResult = arraySub(arrayFirst, arraySecond, maxExtent1, maxExtent2);
            } else {
                maxExtentToFunc = maxExtent2;
                addResult = arraySub(arraySecond, arrayFirst, maxExtent2, maxExtent1);
            }
            printf("Результат вычитания полиномов:  \n");
            printArray(addResult, maxExtentToFunc);
            free(arrayFirst);
            free(arraySecond);
            free(addResult);
            break;
        } else if (userChoice == 3) {
            int maxExtent1 = arrayMaxExtentChoice("первого");
            int maxExtent2 = arrayMaxExtentChoice("второго");
            arrayFirst = initArray(maxExtent1);
            arraySecond = initArray(maxExtent2);
            inputArray(arrayFirst, maxExtent1);
            inputArray(arraySecond, maxExtent2);
            double *addResult;
            int maxExtentToFunc;
            if (maxExtent1 > maxExtent2) {
                maxExtentToFunc = maxExtent1;
                addResult = arrayMul(arrayFirst, arraySecond, maxExtent1, maxExtent2);
            } else {
                maxExtentToFunc = maxExtent2;
                addResult = arrayMul(arraySecond, arrayFirst, maxExtent2, maxExtent1);
            }
            printf("Результат умножения полиномов:  \n");
            printArray(addResult, maxExtent1 + maxExtent2);
            free(arrayFirst);
            free(arraySecond);
            free(addResult);
            break;
        } else if (userChoice == 4) {
            int maxExtent1 = arrayMaxExtentChoice("");
            arrayFirst = initArray(maxExtent1);
            inputArray(arrayFirst, maxExtent1);
            int extent;
            double coefficient;
            printf("Введите коэфициент монома: \n");
            scanf("%lf", &coefficient);
            printf("Введите степень монома: \n");
            scanf("%d", &extent);
            double *addResult = arrayDiv(arrayFirst, extent, coefficient, maxExtent1);
            free(arrayFirst);
            free(arraySecond);
            free(addResult);
            break;
        } else if (userChoice == 5) {
            int maxExtent = arrayMaxExtentChoice("");
            arrayFirst = initArray(maxExtent);
            inputArray(arrayFirst, maxExtent);
            double *diffResult = arrayDiff(arrayFirst, maxExtent);
            double res = differentiationRes(diffResult, maxExtent);
            printf("Результат дифференцирования полинома в точке x0: %lf\n", res);
            free(arrayFirst);
            free(diffResult);
            break;
        } else if (userChoice == 6) {
            int upperLimit, lowerLimit;
            printf("Введите верхний предел: \n");
            scanf("%d", &upperLimit);
            printf("Введите нижний предел: \n");
            scanf("%d", &lowerLimit);
            int maxExtent = arrayMaxExtentChoice("");
            arrayFirst = initArray(maxExtent);
            inputArray(arrayFirst, maxExtent);
            double *temp;
            double result = certainIntegral(arrayFirst, temp, maxExtent, lowerLimit, upperLimit);
            printf("Результат: %lf\n", result);
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

int arrayMaxExtentChoice(char* name){
    int userMaxExtent;
    printf("Введите максимальную степень %s полиномов: \n", name);
    scanf("%d", &userMaxExtent);
    return ++userMaxExtent;
}

double* initArray(int maxExtent){
    double* arrayRes = (double*) malloc(sizeof(double) * maxExtent);
    for (int i = 0; i < maxExtent; i++){
        arrayRes[i] = 0;
    }
    return arrayRes;
}

void inputArray(double* array, int maxExtent){
    for(int i = 0; i < maxExtent; ++i){
        printf("Введите коэффицент для степени %d\n ", i);
        double inputNumber;
        scanf("%lf", &inputNumber);
        array[i] =  inputNumber;
    }
}

void printArray(double *array, int maxExtent){
    int flag = 0;
    for (int i = maxExtent - 1; i >= 0; --i) {
        if(array[i] != 0)
            printf("%s%.2lfx%c%d ", (array[i] > 0 && flag++ != 0) ? "+" : "", array[i], P_CHAR, i);
    }
    printf("\n");
}

double* arrayAdd(double* arrayLarger, double* arraySmaller, int maxExtentLarger, int maxExtentSmaller){
    double* arrayRes = initArray(maxExtentLarger);
    for (int i = 0; i < maxExtentLarger; ++i) {
        arrayRes[i] = arrayLarger[i];
    }
    for (int i = 0; i < maxExtentSmaller; ++i) {
        arrayRes[i] += arraySmaller[i];
    }
    return arrayRes;
}


double* arraySub(double* arrayLarger, double* arraySmaller, int maxExtentLarger, int maxExtentSmaller){
    double* arrayRes = initArray(maxExtentLarger);
    for (int i = 0; i < maxExtentLarger; ++i) {
        arrayRes[i] = arrayLarger[i];
    }
    for (int i = 0; i < maxExtentSmaller; ++i) {
        arrayRes[i] -= arraySmaller[i];
    }
    return arrayRes;
}

double* arrayMul(double* arrayLarger, double* arraySmaller, int maxExtentLarger, int maxExtentSmaller){
    double* arrayRes = initArray(maxExtentLarger + maxExtentSmaller);
    for (int i = 0; i < maxExtentLarger; ++i) {
        for(int j = 0; j < maxExtentSmaller; ++j){
            arrayRes[i + j] += arrayLarger[i] * arraySmaller[j];
        }
    }
    return arrayRes;
}

double* arrayDiv(double* array, int extent, double coefficient, int maxExtent){
    double* res = initArray(maxExtent - extent);
    for (int i = extent; i < maxExtent; ++i) {
        if (array[i] != 0)
            res[i - extent] = array[i] / coefficient;
    }
    printf("\nРезультат деления: ");
    printArray(res, maxExtent - extent);
    printf("\nОстаток: ");
    printArray(array, extent);
    return res;
}

double* arrayDiff(double* array, int maxExtent){
    double* arrayRes = initArray(maxExtent);
    for(int i = 1; i < maxExtent; ++i){
        arrayRes[i - 1] = array[i] * i;
    }
    return arrayRes;
}

double differentiationRes(double* array, int maxExtent){
    double result = 0;
    int x;
    printf("Введите точку: \n");
    scanf("%d", &x);
    for(int i = 0; i < maxExtent; ++i){
        result += array[i] * pow(x, i);
    }
    return result;
}

double certainIntegral(double* array, double* arrayRes, int maxExtent, int lowerLim, int upperLim){
    arrayRes = (double*)initArray(maxExtent);
    for(int i = 0; i < maxExtent; ++i){
        arrayRes[i + 1] = (double)array[i] / (double)(i + 1);
    }
    double sumUpperLim = 0;
    double sumLowerLim = 0;
    for(int i = 0; i < maxExtent + 1; ++i){
        sumUpperLim += (double)pow(upperLim, i) * arrayRes[i];
        sumLowerLim += (double)pow(lowerLim, i) * arrayRes[i];
    }
    return sumUpperLim - sumLowerLim;
}
#include <stdio.h>
#define SIZE 4

int count = 0;

void rotate(int* array, int size, int n) {
    int i;
    int pos = size - n;
    int temp = array[pos];
    for (i = pos + 1; i < size; ++i) {
        array[i - 1] = array[i];
    }
    array[i - 1] = temp;
}

void display(int* array, int size) {
    if ((float)(array[0] + array[1])/2.0 > ((float)(array[2] * array[3])/2.0))
    {
      printf("%d%d%d%d", array[0], array[1], array[2], array[3]);
      count++;
      printf("\n");
    }
}

void getCombination(int* array, int size, int n) {
    if (n == 1) 
        return;
    for (int i = 0; i < n; ++i) {
        getCombination(array, size, n - 1);
        if (n == 2)
            display(array, size);
        rotate(array, size, n);
    }
}


int main(){
    int number1, number2, number3, number4;
    scanf("%d %d %d %d", &number1, &number2, &number3, &number4);

    int array[SIZE] = {number1, number2, number3, number4};

    getCombination(array, 4, 4); // 1234
    printf("Count is: %d\n", count);
}

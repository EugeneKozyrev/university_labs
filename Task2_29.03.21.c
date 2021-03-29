#include <stdio.h>
#define SIZE 30


int main()
{
    int array[SIZE];
    for (int i = 0; i < SIZE; ++i){
        array[i] = rand() % 7;
        printf("%d ", array[i]);
    }
    printf("\n");
    int counter = 0;
    for (int i = 0; i < SIZE; i++)
    {
        if (array[i] == 0)
        {
            counter++;
            continue;
        }
        else
        {
            int temp = array[i - counter];
            array[i - counter] = array[i];
            array[i] = temp;
        }
    }
    for (int i = 0; i < SIZE; ++i){
        printf("%d ", array[i]);
    }
    return 0;
}

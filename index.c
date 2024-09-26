#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Troca(int array[], int n)
{
    int i, j, temp;

    // Ira ler termo por termo
    for (i = 0; i < n; i++)
    {
        // Ira comparar termo por termo
        for (j = 0; j < n - 1; j++)
        {
            // Troca os elementos
            if (array[j] > array[j + 1])
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int main(void)
{
    system("cls");

    int array[10] = { 1 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 20, 12};

    Troca(array, 10);

	for (int i = 0; i < 10; i++){
    printf("%i ", array[i]);
    }

    printf("\n\n");
    return 0;
}

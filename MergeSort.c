#include <stdio.h>
#include <stdlib.h>

int main()
{
    void merge(int *a, int left, int half, int right){
        int i, j, k, *aux;
        int n1 = half - left + 1, n2 = right - half;
        int aux1[n1], aux2[n2];

        for(i = 0; i < n1; i++)
            aux1[i] = a[left + i];

        for(j = 0; j < n2; j++)
            aux2[j] = a[half + 1 + j];

        i = 0;
        j = 0;
        k = left;

        while(i < n1 && j < n2){
            if(aux1[i] <= aux2[j]){
                a[k] = aux1[i];
                i++;
            }else{
                a[k] = aux2[j];
                j++;
            }
            k++;
        }

        while(i < n1){
            a[k] = aux1[i];
            i++;
            k++;
        }

        while(j < n2){
            a[k] = aux2[j];
            j++;
            k++;
        }
    }

    int ordena(int *v, int *aux, int left, int right){
        if(left >= right) return;

        int half = (left + right)/2;
        ordena(aux, v, left, half);
        ordena(aux, v, half + 1, right);
        if(v[half] <= v[half + 1]) return;
        merge(v, left, half, right);
    }

    void insertionSort(int *v, int ini, int fim){
        int i, j, temp;
        for(i = ini; i < fim; i++){
            temp = v[i];
            j = i - 1;

            while(j >= 0 && temp <= v[j]){
                v[j+1] = v[j];
                j = j-1;
            }

            v[j+1] = temp;
        }
    }

    int mergeSort(int *v, int n){
        if(n < 4) insertionSort(v, 0, n-1);
        else{
            int *aux = v;
            ordena(v, aux, 0, n-1);
            return 1;
        }
    }

    int arr[5] = {2, 0, 1, 3, 4};

    for(int i = 0; i < 5; i++)
        printf("%d\t", arr[i]);
        printf("\n");

    if(mergeSort(arr, 5))
        for(int i = 0; i < 5; i++)
            printf("%d\t", arr[i]);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int max(int n1, int n2){
    if (n1 >= n2)
    {
        return n1;
    }
    else return n2;
}

int main() {
    int input, size, result;
    printf("n 값 입력 : ");
    scanf("%d", &input);
    size = input + 1;

    int** arr = (int**)malloc(sizeof(int*) * size);
    for (int i = 0; i < size; i++) { 
        arr[i] = (int*)malloc(sizeof(int) * size); 
    }

    for (int i = 1; i < size; i++) {
        printf("%d행 입력 : ", i);
        for (int j = 1; j < size; j++) {
            int n;
            scanf("%d", &n);
            arr[i][j] = n;
        }
    }

    for (int i = 0; i < size; i++) {
        arr[i][0] = 0;
    }
    for (int j = 1; j < size; j++) {
        arr[0][j] = 0;
    }

    for (int i = 1; i < size; i++) {
        for (int j = 1; j < size; j++) {
            arr[i][j] = arr[i][j] + max(arr[i-1][j], arr[i][j-1]);
        }
    }

    result = arr[size-1][size-1];
    printf("결과 : %d\n", result);

    int tmp_arr[size][2];
    int w = 0;
    int i = size - 1;
    int j = size - 1;

    while (i > 0 && j > 0) {
        tmp_arr[w][0] = i;
        tmp_arr[w][1] = j;
        w++;

        if (arr[i-1][j] > arr[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("경로 : ");
    for (int k = w - 1; k > 0; k--) {
        printf("(%d, %d) -> ", tmp_arr[k][0], tmp_arr[k][1]);
    }
    printf("(%d, %d)", input, input);

    return 0;
}

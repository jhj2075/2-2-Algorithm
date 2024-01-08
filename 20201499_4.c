#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int NUM = 10000;
int COUNT = 1;

// 교재의 partition 함수
int partition (int A[], int p, int r){
    int x = A[r];
    int i = p-1;

    for (int j = p; j <= r-1; j++)
    {
        if (A[j] <= x)
        {
            i++;
            int tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
        }
    }
    int tmp = A[i+1];
    A[i+1] = A[r];
    A[r] = tmp;

    return i+1;
}
// 교재의 select 함수
int select (int A[], int p, int r, int i){
    if (p == r)
    {
        return A[p];
    }

    int q = partition(A, p, r);
    int k = q - p;

    if (i < k)
    {
        return select(A, p, q-1, i);
    }
    else if (i == k)
    {
        return A[q];
    }
    else return select(A, q+1, r, i-k);    
}
// 교재의 heapify 함수
void heapify(int A[], int k, int n){
    int left = (k+1)*2 - 1;
    int right = (k+1)*2;
    int smaller;

    if (right <= n-1)
    {
        if (A[left] < A[right])
        {
            smaller = left;
        }
        else smaller = right;
    }
    else if (left <= n)
    {
        smaller = left;
    }
    else return;

    if (A[smaller] < A[k])
    {
        int tmp = A[k];
        A[k] = A[smaller];
        A[smaller] = tmp;
        heapify(A, smaller, n);
    }    
}
// 교재의 buildHeap 함수
void buildHeap(int A[], int n){
    for (int i = n/2; i >= 0; i--)
    {
        heapify(A, i, n);
    }
    
}
// 교재의 heapSort 함수
void heapSort(int A[], int n){
    buildHeap(A, n);
    for (int i = n-1; i > 0; i--)
    {
        int tmp = A[0];
        A[0] = A[i];
        A[i] = tmp;
        heapify(A, 0, i-1);
    }
}
int linearSelect(int A[], int p, int r, int i){
    // 명세의 2-1번
    if (r < 4)
    {
        select(A, p, r, i);
    }
    int arrNum = r - p + 1;
    // 명세의 2-2번
    if (arrNum <= arrNum)
    {
        heapSort(A + p, arrNum);
        return A[p + i];
    }

    int div = (arrNum+4) / 5;
    int midArr[div];

    for (int j = 0; j < div; j++) {
        int groupP = p + j * 5;
        int groupR = groupP + 4;
        if (groupR > r) {
            groupR = r;
        }
        midArr[j] = linearSelect(A, groupP, groupR, 3);
    }

    int x = linearSelect(midArr, 0, div - 1, div / 2);

    // 명세의 2-3번
    int q = partition(A, p, r);
    int k = q - p + 1;

    if (i == k) {
        return A[q];
    } else if (i < k) {
        return linearSelect(A, p, q - 1, i);
    } else {
        return linearSelect(A, q + 1, r, i - k);
    }
}

int main(){
    clock_t start = clock();

    srand(time(NULL));
    int TIME = 0;
    int input;
    
    int selected;
    int randArr[NUM];
    int k = NUM / 2 - 1;
    int tmp[NUM / 2];
    int n = 0;

    printf("평균 0, 최악 1 입력 : ");
    scanf("%d", &input);

    for (int i = 0; i < COUNT; i++)
    {
            for (int i = 0; i < NUM; i++)
        {
            int randNum = rand() % NUM + 1;
            randArr[i] = randNum;
        }
        if (input == 0)
        {
            for (int i = 0; i < (NUM / 2); i++)
            {
                selected = select(randArr, 0, NUM - 1, i);
                printf("%d ", selected);
            }
        }
        else if (input == 1)
        {
            for (int i = NUM / 2; i < NUM; i++)
            {
                if (n < NUM / 2)
                {
                    tmp[n] = linearSelect(randArr, 0, NUM - 1, i);
                    n++;
                }
            }
            for (int k = NUM / 2 - 1; k >= 0; k--)
            {
                printf("%d ", tmp[k]);
            }
            
        }
    }

    TIME += ((int)clock() - start) / (CLOCKS_PER_SEC / 1000);
    printf("\nTIME : %d ms\n", TIME);
    
    return 0;
}
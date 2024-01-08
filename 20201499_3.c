#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node
{
    int data;
    struct Node *next;
} node;

void print_list(node *head)
{
    node *current = head;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 난수를 받아 동적 메모리를 할당 받고 노드로 만들어주는 함수
node *create_node(int data) 
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void radix_sort(node **head)
{
    // 3) 각 연결리스트의 헤드를 저장하는 크기가 10인 포인터 배열을 생성
    node *headPointers[10] = {NULL};
    // 4) 각 연결리스트의 테일을 저장하는 크기가 10인 포인터 배열을 생성
    node *tailPointers[10] = {NULL};

    for (int digit = 1; digit <= 10000; digit *= 10)
    {
        for (int i = 0; i < 10; i++)
        {
            headPointers[i] = NULL;
            tailPointers[i] = NULL;
        }

        node *current = *head;
        // 2) 0 ~ 9 자릿수에 해당하는 연결리스트를 create_node에서 동적 메모리 할당을 통해 노드를 생성한 후 연결해 만드는 반복문
        while (current != NULL)
        {
            int num = current->data;
            int digit_data = (num / digit) % 10;

            if (headPointers[digit_data] == NULL)
            {
                headPointers[digit_data] = create_node(num);
                tailPointers[digit_data] = headPointers[digit_data];
            }
            else
            {
                tailPointers[digit_data]->next = create_node(num);
                tailPointers[digit_data] = tailPointers[digit_data]->next;
            }
            current = current->next;
        }

        *head = NULL;
        for (int i = 0; i < 10; i++)
        {
            if (headPointers[i] != NULL)
            {
                if (*head == NULL)
                {
                    *head = headPointers[i];
                }
                else
                {
                    node *temp = *head;
                    while (temp->next != NULL)
                    {
                        temp = temp->next;
                    }
                    temp->next = headPointers[i];
                }
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    int n, m;

    printf("정렬할 4자리 정수 갯수 입력 : ");
    scanf("%d", &n);
    printf("실행 횟수 입력 : ");
    scanf("%d", &m);

    node *head = NULL;
    node *current = NULL;
    for (int i = 0; i < m; i++)
    {
        // 1) 난수를 생성하고 생성된 난수를 반복문이 실행될 때마다 create_node 함수를 이용해 동적 메모리를 할당 받아 노드로 생성, 노드를 연결하는 반복문
        for (int j = 0; j < n; j++)
        {
            int randNum = rand() % 10000; 
            node *newNode = create_node(randNum); 

            if (head == NULL)
            {
                head = newNode;
                current = newNode;
            }
            else
            {
                current->next = newNode;
                current = newNode;
            }
        }

        printf("정렬 전 값 출력 : ");
        print_list(head);

        radix_sort(&head);
        printf("정렬된 값 출력 : ");
        print_list(head);
        printf("\n");

        current = head;
        while (current != NULL)
        {
            node *temp = current;
            current = current->next;
            free(temp);
        }
        head = NULL;
    }

    return 0;
}

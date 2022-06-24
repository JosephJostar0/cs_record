#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode Next;
};
typedef PtrToNode List;

List Read(){};        /* 细节在此不表 */
void Print(List L){}; /* 细节在此不表；空链表将输出NULL */

List Merge(List L1, List L2);

int main() {
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

/* 你的代码将被嵌在这里 */
List Merge(List L1, List L2) {
    List L3 = (List)malloc(sizeof(List)), L4, L5;
    L4 = L1, L1 = L1->Next, L4->Next = NULL;
    L4 = L2, L2 = L2->Next, L4->Next = NULL;
    L4 = L3;
    while (L1 && L2) {
        if (L1->Data < L2->Data)
            L3->Next = L1, L5 = L1, L1 = L1->Next;
        else
            L3->Next = L2, L5 = L2, L2 = L2->Next;
        L3 = L3->Next;
    }
    while (L1)
        L3->Next = L1, L1 = L1->Next, L3 = L3->Next;
    while (L2)
        L3->Next = L2, L2 = L2->Next, L3 = L3->Next;
    return L4;
}
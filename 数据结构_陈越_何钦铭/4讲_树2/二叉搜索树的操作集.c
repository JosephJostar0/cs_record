#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode {
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal(BinTree BT) {
    if (!BT)
        return;
    printf("%d ", BT->Data);
    PreorderTraversal(BT->Left);
    PreorderTraversal(BT->Right);
}
void InorderTraversal(BinTree BT) {
    if (!BT)
        return;
    InorderTraversal(BT->Left);
    printf("%d ", BT->Data);
    InorderTraversal(BT->Right);
}

BinTree Insert(BinTree BST, ElementType X);
BinTree Delete(BinTree BST, ElementType X);
Position Find(BinTree BST, ElementType X);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);

int main() {
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }

    printf("Preorder:");
    PreorderTraversal(BST);
    printf("\n");
    printf("Inorder:");
    InorderTraversal(BST);
    printf("\n");

    MinP = FindMin(BST);
    MaxP = FindMax(BST);

    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL)
            printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp == MinP)
                printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp == MaxP)
                printf("%d is the largest key\n", Tmp->Data);
        }
    }

    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }

    printf("Preorder:");
    PreorderTraversal(BST);
    printf("\n");
    printf("Inorder:");
    InorderTraversal(BST);
    printf("\n");

    return 0;
}
/* 你的代码将被嵌在这里 */
BinTree Insert(BinTree BST, ElementType X) {
    if (!BST) {
        BST = (BinTree)malloc(sizeof(BinTree));
        BST->Data = X;
        BST->Left = BST->Right = NULL;
        return BST;
    }
    if (BST->Data < X)
        BST->Right = Insert(BST->Right, X);
    else
        BST->Left = Insert(BST->Left, X);
    return BST;
}

BinTree Delete(BinTree BST, ElementType X) {
    if (!BST) {
        printf("Not Found\n");
        return NULL;
    }
    BinTree temp;
    if (BST->Data < X)
        BST->Right = Delete(BST->Right, X);
    else if (BST->Data > X)
        BST->Left = Delete(BST->Left, X);
    else {
        if (BST->Left && BST->Right) {
            temp = FindMin(BST->Right);
            BST->Data = temp->Data;
            BST->Right = Delete(BST->Right, temp->Data);
        } else {
            temp = BST;
            if (!BST->Left)
                BST = BST->Right;
            else
                BST = BST->Left;
            free(temp);
        }
    }
    return BST;
}

Position Find(BinTree BST, ElementType X) {
    if (!BST)
        return NULL;
    if (BST->Data == X)
        return BST;
    else if (X > BST->Data)
        return Find(BST->Right, X);
    else
        return Find(BST->Left, X);
}

Position FindMin(BinTree BST) {
    if (!BST)
        return BST;
    BinTree temp = BST;
    while (temp->Left)
        temp = temp->Left;
    return temp;
}

Position FindMax(BinTree BST) {
    if (!BST)
        return BST;
    BinTree temp = BST;
    while (temp->Right)
        temp = temp->Right;
    return temp;
}

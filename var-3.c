#include <stdio.h>
#include <stdlib.h>
#define LENGTH 10

typedef struct {
    int *elemPtr;
    int count;
    int max;
} List;

List initialize(List L) {
    L.elemPtr = (int*)malloc(sizeof(int)*LENGTH);
    if (L.elemPtr==NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    L.count=0;
    L.max=LENGTH;
    return L;
}

List resize(List L) {
    L.max*=2;
    int *newElem=(int*)realloc(L.elemPtr, sizeof(int)*L.max);
    if (newElem==NULL) {
        printf("Reallocation failed.\n");
        exit(1);
    }
    L.elemPtr=newElem;
    return L;
}

List insertPos(List L, int data, int pos) {
    if (pos<0 || pos>L.count) {
        printf("Invalid position.\n");
        return L;
    }
    if (L.count==L.max) {
        L=resize(L);
    }
    for (int i=L.count;i>pos;i--) {
        L.elemPtr[i]=L.elemPtr[i-1];
    }
    L.elemPtr[pos]=data;
    L.count++;
    return L;
}

List deletePos(List L, int pos) {
    if (pos<0 || pos>=L.count) {
        printf("Invalid position.\n");
        return L;
    }
    for (int i=pos;i<L.count-1;i++) {
        L.elemPtr[i]=L.elemPtr[i+1];
    }
    L.count--;
    return L;
}

int locate(List L, int data) {
    for (int i=0;i<L.count;i++) {
        if (L.elemPtr[i]==data) {
            return i;
        }
    }
    return -1;
}

List insertSorted(List L, int data) {
    if (L.count==L.max) {
        L=resize(L);
    }
    for (int i=0;i<L.count-1;i++) {
        for (int j=i+1;j<L.count; j++) {
            if (L.elemPtr[i]>L.elemPtr[j]) {
                int temp=L.elemPtr[i];
                L.elemPtr[i]=L.elemPtr[j];
                L.elemPtr[j]=temp;
            }
        }
    }
    int i;
    for (i=L.count-1;i>=0 &&L.elemPtr[i]>data;i--) {
        L.elemPtr[i+1]=L.elemPtr[i];
    }
    L.elemPtr[i+1]=data;
    L.count++;
    return L;
}

void display(List L) {
    for (int i=0;i<L.count;i++) {
        printf("%d ", L.elemPtr[i]);
    }
    printf("\n");
}

void makeNULL(List *L) {
    if (L->elemPtr!=NULL) {
        free(L->elemPtr);
        L->elemPtr=NULL;
    }
    L->count=0;
    L->max=0;
}

int main() {
    List L;
    L = initialize(L);

    int selected, val, pos;

    printf("Enter size of array: ");
    scanf("%d", &L.count);
    if (L.count > L.max) {
        printf("Invalid size.\n");
        free(L.elemPtr);
        return 1;
    }

    printf("Enter values: ");
    for (int i = 0; i < L.count; i++) {
        scanf("%d", &L.elemPtr[i]);
    }

    printf("\n1. Insert Position\n");
    printf("2. Delete Position\n");
    printf("3. Locate\n");
    printf("4. Insert Sorted\n");
    printf("5. Display\n");
    printf("\nEnter operation: ");
    scanf("%d", &selected);

    switch (selected) {
        case 1: {
            printf("Enter position to insert: ");
            scanf("%d", &pos);
            printf("Enter value: ");
            scanf("%d", &val);
            L = insertPos(L, val, pos);
            display(L);
            break;
        }
        case 2: {
            printf("Enter position to delete: ");
            scanf("%d", &pos);
            L = deletePos(L, pos);
            display(L);
            break;
        }
        case 3: {
            printf("Enter value to locate: ");
            scanf("%d", &val);
            pos = locate(L, val);
            if (pos == -1) {
                printf("Value not found.\n");
            } else {
                printf("Value %d is at position %d.\n", val, pos);
            }
            break;
        }
        case 4: {
            printf("Enter value to insert sorted: ");
            scanf("%d", &val);
            L = insertSorted(L, val);
            display(L);
            break;
        }
        case 5: {
            display(L);
            break;
        }
        default: {
            printf("Invalid choice.\n");
        }
    }

    makeNULL(&L);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#define LENGTH 10

typedef struct {
    int *elemPtr;
    int count;
    int max;
} List;

void initialize(List *L) {
    L->elemPtr=(int*)malloc(sizeof(int)*LENGTH);
    if (L->elemPtr==NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    L->count=0;
    L->max=LENGTH;
}

void resize(List *L) {
    L->max*=2;
    int *newPtr=(int*)realloc(L->elemPtr,sizeof(int)*L->max);
    if (newPtr == NULL) {
        printf("Reallocation failed.\n");
        exit(1);
    }
    L->elemPtr=newPtr;
}

void insertPos(List *L, int data, int position) {
    if (position<0 || position>L->count) {
        printf("Invalid position.\n");
        return;
    }
    if (L->count==L->max) {
        resize(L);
    }
    for (int i=L->count;i>position;i--) {
        L->elemPtr[i]=L->elemPtr[i-1];
    }
    L->elemPtr[position]=data;
    L->count++;
}

void deletePos(List *L, int position) {
    if (position<0 || position>=L->count) {
        printf("Invalid position.\n");
        return;
    }
    for (int i=position;i<L->count-1;i++) {
        L->elemPtr[i]=L->elemPtr[i+1];
    }
    L->count--;
}

int locate(List *L, int data) {
    for (int i=0;i<L->count;i++) {
        if (L->elemPtr[i]==data) {
            return i;
        }
    }
    return -1;
}

int retrieve(List *L, int position) {
    if (position>=0 && position<L->count) {
        return L->elemPtr[position];
    } else {
        printf("Invalid position.\n");
        return -1;
    }
}

void insertSorted(List *L, int data) {
    if (L->count==L->max) {
        resize(L);
    }
    int i;
    for (i=L->count-1;i>=0 && L->elemPtr[i]>data;i--) {
        L->elemPtr[i+1]=L->elemPtr[i];
    }
    L->elemPtr[i+1]=data;
    L->count++;
}

void display(List *L) {
    for (int i=0;i<L->count;i++) {
        printf("%d ", L->elemPtr[i]);
    }
    printf("\n");
}

void makeNULL(List *L) {
    free(L->elemPtr);
    L->elemPtr=NULL;
    L->count=0;
    L->max=0;
}

int main() {
    List L;
    initialize(&L);

    int selected, val, pos;

    printf("Enter size of array: ");
    scanf("%d", &L.count);
    if (L.count > L.max) {
        printf("Invalid size.\n");
        makeNULL(&L);
        return 1;
    }

    printf("Enter values: ");
    for (int i = 0; i < L.count; i++) {
        scanf("%d", &L.elemPtr[i]);
    }

    printf("\n1. Insert Position\n");
    printf("2. Delete Position\n");
    printf("3. Locate\n");
    printf("4. Retrieve\n");
    printf("5. Insert Sorted\n");
    printf("\nEnter operation: ");
    scanf("%d", &selected);

    switch (selected) {
        case 1:
            printf("Enter position to insert: ");
            scanf("%d", &pos);
            printf("Enter value: ");
            scanf("%d", &val);
            insertPos(&L, val, pos);
            display(&L);
            break;

        case 2:
            printf("Enter position to delete: ");
            scanf("%d", &pos);
            deletePos(&L, pos);
            display(&L);
            break;

        case 3:
            printf("Enter value to locate: ");
            scanf("%d", &val);
            pos = locate(&L, val);
            if (pos == -1) {
                printf("Value not found.\n");
            } else {
                printf("Value %d is at position %d.\n", val, pos);
            }
            break;

        case 4:
            printf("Enter position to retrieve: ");
            scanf("%d", &pos);
            val = retrieve(&L, pos);
            if (val != -1) {
                printf("Element at position %d is %d\n", pos, val);
            }
            break;

        case 5:
            printf("Enter value to insert sorted: ");
            scanf("%d", &val);
            insertSorted(&L, val);
            display(&L);
            break;

        default:
            printf("Invalid choice.\n");
    }

    makeNULL(&L);
    return 0;
}

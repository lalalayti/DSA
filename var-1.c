#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct {
    int elem[MAX];
    int count;
} List;

List initialize(List L) {
    L.count = 0;
    return L;
}

List insertPos(List L, int data, int position) {
    if (position<0 || position>L.count) {
        printf("Invalid position.\n");
        exit(1);
    }
    if (L.count==MAX) {
        printf("Array is full.\n");
        exit(1);
    }
    for (int i=L.count;i>position;i--) {
        L.elem[i]=L.elem[i-1];
    }
    L.elem[position]=data;
    L.count++;
    return L;
}

List deletePos(List L, int position) {
    if (position<0 || position>=L.count) {
        printf("Invalid position.\n");
        exit(1);
    }
    for (int i=position;i<L.count-1;i++) {
        L.elem[i]=L.elem[i+1];
    }
    L.count--;
    return L;
}

int locate(List L, int data) {
    for (int i=0;i<L.count;i++) {
        if (L.elem[i]==data) {
            return i;
        }
    }
    return -1;
}

List insertSorted(List L, int data) {
    int i=0;
    if (L.count==MAX) {
        printf("Array is full.\n");
        exit(1);
    }
    for (i=L.count-1;i>=0 && L.elem[i]>data;i--) {
        L.elem[i+1]=L.elem[i];
    }
    L.elem[i+1]=data;
    L.count++;
    return L;
}


void display(List L) {
    for (int i=0;i<L.count;i++) {
        printf("%d ", L.elem[i]);
    }
    printf("\n");
}

int main() {
    List L;
    L = initialize(L);

    int selected, val, pos;

    printf("Enter size of array: ");
    scanf("%d", &L.count);
    if (L.count > MAX) {
        printf("Invalid size.\n");
        return 1;
    }
    printf("Enter values: ");
    for (int i=0;i<L.count;i++) {
        scanf("%d", &L.elem[i]);
    }

    printf("\n1. Insert Position\n");
    printf("2. Delete Position\n");
    printf("3. Locate\n");
    printf("4. Insert Sorted\n");
    printf("5. Display\n");
    printf("\nEnter operation: ");
    scanf("%d", &selected);

    switch (selected) {
        case 1:
            printf("Enter position to insert: ");
            scanf("%d", &pos);
            printf("Enter value: ");
            scanf("%d", &val);
            L = insertPos(L, val, pos);
            display(L);
            break;

        case 2:
            printf("Enter position to delete: ");
            scanf("%d", &pos);
            L = deletePos(L, pos);
            display(L);
            break;

        case 3:
            printf("Enter value to locate: ");
            scanf("%d", &val);
            pos = locate(L, val);
            if (pos == -1) {
                printf("Value not found.\n");
            } else {
                printf("Value %d is at position %d.\n", val, pos);
            }
            break;

        case 4:
            printf("Enter value to insert sorted: ");
            scanf("%d", &val);
            L = insertSorted(L, val);
            display(L);
            break;

        case 5:
            display(L);
            break;

        default:
            printf("Invalid choice.\n");
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct {
    int elem[MAX];
    int count;
} List;

List initialize(List L){
    L.count = 0;
    return L;
}

List insertPos(List L, int data, int position){
    if(position > L.count || position == L.count){
        printf("Invalid position.");
        exit(1);
    }
    if(L.count==MAX){
        printf("Array is full.");
        exit(1);
    }

    for(int i=L.count;i>position;i--){
        L.elem[i]=L.elem[i-1];
    }
    L.elem[position]=data;
    L.count++;
    return L;
}

List deletePos(List L, int position){
    if(position > L.count || position == L.count){
        printf("Invalid position.");
        exit(1);
    }
    for(int i=position;i<L.count-1;i++){
        L.elem[i]=L.elem[i-1];
    }
    L.count--;
    return L;
}

int locate(List L, int data){
    for(int i=0;i<L.count;i++){
        if(L.elem[i]==data){
            return i;
        } else {
            return -1;
        }
    }
}

int main(){
    List L;
    List init = initialize(L);
    int selected;
    int val;
    int pos;

    printf("Enter size of array: ");
    scanf("%d", &L.count);
    printf("Enter values: ");
    for(int i=0;i<L.count;i++){
        scanf("%d", &L.elem[i]);
    }

    printf("\n1. Insert Position\n");
    printf("2. Delete Position\n");
    printf("3. Locate\n");
    printf("4. Insert Sorted\n");
    printf("5. Display\n");
    printf("\nEnter operation: ");
    scanf("%d", &selected);

    List newArr;

    switch(selected){
        case 1:
        printf("Enter position to insert: ");
        scanf("%d", &pos);
        printf("Enter value: ");
        scanf("%d", &val);
        newArr = insertPos(L, val, pos);
        printf("Updated array: ");
        for(int i=0;i<newArr.count;i++){
            printf("%d ", newArr.elem[i]);
        }
        break;
        
        case 2:
        printf("Enter position to delete: ");
        scanf("%d", &pos);
        newArr = deletePos(L, pos);
        printf("Updated array: ");
        for(int i=0;i<newArr.count;i++){
            printf("%d ", newArr.elem[i]);
        }
        break;
        case 3:
        printf("Enter value to locate: ");
        scanf("%d", &val);
        int returned = locate(L, val);
        if(returned == -1){
            printf("Value can't be found.");
        } else {
            printf("Value %d is at position %d.", val, returned);
        }
        

    }
    return 0;
}

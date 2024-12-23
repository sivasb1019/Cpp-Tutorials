#include <stdio.h>
#include <stdlib.h>


struct lNode{
    int data;
    struct lNode *next;
};

typedef struct lNode node;
node* head = NULL;

void insertAtBeginning(int val){
    node* newNode = malloc(sizeof(node*));
    if(newNode == NULL){
        printf("Out of memory");
        return;
    }
    newNode -> data = val;
    newNode -> next = head;
    head = newNode;

    printf("Inserted %d at the beginning.\n", val);
}

void displayList(){
    if(head==NULL){
        printf("List is empty!!!");
    }
    node* temp = head;
    while(temp!=NULL){
        printf("%d ", temp->data);
        temp = temp -> next;
    }
}

void insertAtPosition(int pos, int val){
    if(pos==0){
        insertAtBeginning(val);
        return;
    }
    node* newNode = malloc(sizeof(node*));
    if(newNode == NULL){
        printf("Out of memory");
        return;
    }
    node* tempHead = head;
    int i;
    /*while(tempPos < pos){
        printf("data :%d | position: %d | address: %u\n", tempHead->data, tempPos+1, tempHead->next);

        if(pos == tempPos+2){
            newNode -> data = val;
            newNode -> next = tempHead -> next;
            tempHead -> next = newNode;
            break;
        }
        if(tempHead == NULL){return}
        tempHead = tempHead -> next;
        tempPos++;
    }
    */
    for(i=1;i<pos;i++){
        tempHead = tempHead -> next;
        if(tempHead == NULL){
            printf("Position out of range");
            return;
        }
    }
    newNode -> data = val;
    newNode -> next = tempHead -> next;
    tempHead -> next = newNode;
    printf("Inserted %d at the position %d.\n", val, pos);
}

void deleteAtPosition(int pos){
    if(head == NULL){
        printf("List is empty!!!");
        return;
    }
    node *prev, *tempHead = head;
    if(pos==0){
        head = head -> next;
        free(tempHead);
        return;
    }
    int i;
    for(i=1;i<=pos;i++){
        prev = tempHead;
        tempHead = tempHead -> next;
        if(tempHead == NULL){
            printf("Position out of range");
            return;
        }
    }
    int val = tempHead -> data;
    prev -> next = tempHead -> next;
    free(tempHead);
    printf("Deleted %d at the position %d.\n", val, pos);
}
int main(){
    int choice, val, pos;
    while(1){
        printf("\n-------------Listing menu------------\n");
        printf("1. Insert at a beginning\n");
        printf("2. Display list\n");
        printf("3. Insert at specific position\n");
        printf("4. Delete at specific position\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        printf("---------------------------------------\n\n");

        switch(choice){
        case 1:
            printf("Enter the data to insert: ");
            scanf("%d", &val);
            insertAtBeginning(val);
            break;
        case 2:
            displayList();
            break;
        case 3:
            printf("Enter the position \(starts at 0\): ");
            scanf("%d", &pos);
            if(pos<0){
                printf("Invalid position");
                break;
            }
            printf("Enter the data to insert: ");
            scanf("%d", &val);
            insertAtPosition(pos, val);
            break;
        case 4:
            printf("Enter the position to delete\(starts at 0\): ");
            scanf("%d", &pos);
            deleteAtPosition(pos);
            break;
        case 5:
            exit(0);
        default:
            printf("Wrong choice..\n");
            break;
        }
    }
    return 0;
}

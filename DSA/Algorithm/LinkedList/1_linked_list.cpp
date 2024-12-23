#include <iostream>
using namespace std;


struct Node{
    int data;
    Node* next = nullptr;
};

class LinkedList{
    Node* head;

public:
    LinkedList():head(NULL){}

    void displayList(){
        if(!head){
            cout << "List is empty." <<endl;
            return;
        }

        Node* tempHead = head;

        while(tempHead){
            cout << tempHead -> data << " ";
            tempHead = tempHead -> next;
        }
    }

    void reverseList(){
        if(!head){
            cout << "List is empty." <<endl;
            return;
        }
        Node *currentNode = head, *prevNode = nullptr, *nextNode;

        while(currentNode){
            //prev = head;

            nextNode = currentNode -> next;
            currentNode -> next = prevNode;

            prevNode = currentNode;
            currentNode = nextNode;

       }
        head = prevNode;
        displayList();
    }

    void insertAtBeginning(int val){
        Node* newNode = new Node();
        newNode -> data = val;
        newNode -> next = head;
        head = newNode;

        cout << val << " inserted at the beginning." << endl;
    }

    void insertAtPosition(int pos, int val){
        if(pos==0){
            insertAtBeginning(val);
            return;
        }
        if(!head){
            cout << "List is empty. Index out of range" << endl;
            return;
        }
        Node* newNode = new Node();
        Node* tempHead = head;

        for(int i=1; i<pos; i++){
            tempHead = tempHead -> next;
            if(tempHead == nullptr){
                cout << "Given position " <<pos << " out of range." << endl;
                return;
            }
        }
        newNode -> data = val;
        newNode -> next = tempHead -> next;
        tempHead -> next = newNode;

        cout << val << " inserted at the position " << pos << endl;
    }

    void deleteAtBeginning(){
        if(!head){
            cout << "List is empty." << endl;
            return;
        }

        Node* tempHead = head;
        int val = tempHead -> data;
        head = head -> next;
        delete tempHead;

        cout << "Value " << val << " deleted at the beginning." << endl;
    }

    void deleteAtPosition(int pos){
        if(pos==0){
            deleteAtBeginning();
            return;
        }
        if(!head){
            cout << "List is empty. Index out of range" << endl;
            return;
        }

        Node* tempHead = head;
        Node* prev = nullptr;

        for(int i=1; i<=pos; i++){
            prev = tempHead;
            tempHead = tempHead -> next;
            if(tempHead == nullptr){
                cout << "Given position " <<pos << " out of range." << endl;
                return;
            }
        }
        prev -> next = tempHead -> next;
        int val = tempHead -> data;
        delete tempHead;

        cout << "Value " << val << " deleted from the position " << pos << endl;
    }


};

int main(){
    int choice, val, pos;
    LinkedList l;
    while(true){
        cout << "\n-------------Listing menu------------" << endl;
        cout << "1. Insert at a beginning" << endl;
        cout << "2. Display list" << endl;
        cout << "3. Insert at specific position" << endl;
        cout << "4. Delete at a beginning" << endl;
        cout << "5. Delete at specific position" << endl;
        cout << "6. Reverse a list" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cout << "---------------------------------------" << endl;

        switch(choice){
        case 1:
            cout << "Enter the data to insert: ";
            cin >> val;
            l.insertAtBeginning(val);
            break;
        case 2:
            l.displayList();
            break;
        case 3:
            cout << "Enter the position (starts at 0): ";
            cin >> pos;
            if(pos<0){
                cout << "Invalid position" << endl;
                break;
            }
            cout << "Enter the data to insert: ";
            cin >> val;
            l.insertAtPosition(pos, val);
            break;
        case 4:
            l.deleteAtBeginning();
            break;
        case 5:
            cout << "Enter the position to delete (starts at 0): ";
            cin >> pos;
            if(pos<0){
                cout << "Invalid position" << endl;
                break;
            }
            l.deleteAtPosition(pos);
            break;
        case 6:
            l.reverseList();
            break;
        case 7:
            return 0;
        default:
            cout << "Wrong choice.." << endl;
            break;
        }
    }
    return 0;
}

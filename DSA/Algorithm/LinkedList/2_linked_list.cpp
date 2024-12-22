#include <iostream>
#include <string>
using namespace std;


class Node{
public:
    string data;
    Node *prev, *next;

    Node():prev(nullptr), next(nullptr){}

    Node(string data){
        this -> data = data;
        this -> prev = nullptr;
        this -> next = nullptr;
    }
};

class LinkedList{
    Node *head, *tail;
public:
    LinkedList():head(nullptr), tail(nullptr){}

    void displayList(){
        if(!head){
            cout << "List is empty." << endl;
        }

        Node* tempHead = head;

        while(tempHead){
            cout << tempHead -> data << " ";
            tempHead = tempHead -> next;
        }
    }

    void displayReverseList(){
        if(!tail){
            cout << "List is empty." << endl;
        }

        Node* tempTail = tail;

        while(tempTail){
            cout << tempTail -> data << " ";
            tempTail = tempTail -> prev;
        }
    }

    void insertAtBeginning(string val){
        Node* newNode = new Node(val);
        if(!head){
            head = tail = newNode;
        }
        else{
            newNode -> next = head;
            head -> prev = newNode;
            head = newNode;
        }
        cout << val << " inserted at the beginning." << endl;

    }

    void insertAtPosition(int pos, string val){
        if(pos==0){
            insertAtBeginning(val);
            return;
        }

        if(!head){
            cout << "List is empty. Index out of range" << endl;
            return;
        }

        Node* newNode = new Node(val);
        Node *tempHead = head;

        for(int i=1;i<pos;i++){
            tempHead = tempHead -> next;
            if(!tempHead){
                cout << "Index out of range" <<endl;
                return;
            }
        }
        newNode -> prev = tempHead;
        newNode -> next = tempHead -> next;
        tempHead -> next = newNode;
        if(newNode->prev == tail){tail = newNode;}
        cout << val << " inserted at the position " << pos << endl;
    }

    void deleteAtBeginning(){
        int val = 0;
        cout << val << " deleted at the beginning." << endl;
    }

    void deleteAtPosition(int pos){
        int val = 0;
        cout << val << " deleted at the position " << pos << endl;
    }
};


int main(){
    int choice, pos;
    string val;
    LinkedList l;
    while(true){
        cout << "\n-------------Listing menu------------" << endl;
        cout << "1. Display list" << endl;
        cout << "2. Display reverse list" << endl;
        cout << "3. Insert at a beginning" << endl;
        cout << "4. Insert at specific position" << endl;
        cout << "5. Delete at a beginning" << endl;
        cout << "6. Delete at specific position" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cout << "---------------------------------------" << endl;

        switch(choice){
        case 1:
            l.displayList();
            break;
        case 2:
            l.displayReverseList();
            break;
        case 3:
            cout << "Enter the data to insert: ";
            cin >> val;
            l.insertAtBeginning(val);
            break;
        case 4:
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
        case 5:
            l.deleteAtBeginning();
            break;
        case 6:
            cout << "Enter the position to delete (starts at 0): ";
            cin >> pos;
            if(pos<0){
                cout << "Invalid position" << endl;
                break;
            }
            l.deleteAtPosition(pos);
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

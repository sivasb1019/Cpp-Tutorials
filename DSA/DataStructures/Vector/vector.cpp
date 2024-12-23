#include <iostream>
#include <vector>
using namespace std;

void display(vector<int> v){
    cout << "\nDisplay function" << endl;
    /*vector<int> it;
    for(it = v.begin(); it != v.end(); i++){
        cout << *it << " ";
    }*/
    for(auto val: v){
        cout << val << " ";
    }
    cout << "\nSize of vector: " << v.size() <<endl;
}

int main(){
    vector<int> a;
    a = {1, 2, 3, 4};
    cout << "Normal for loop" << endl;
    for(int i=0; i<a.size(); i++){
        cout << a[i] << " ";
    }
    cout << "\nSize of a: " << a.size() <<endl;
    cout << "Capacity of a: " << a.capacity() <<endl;
    a.push_back(5);
    a.push_back(6);
    display(a);
    //a.pop_back;
}

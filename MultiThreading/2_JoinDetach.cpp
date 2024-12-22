#include <iostream>
#include <thread>
#include <chrono>
#include <string>

using namespace std;

void fun(int n, string content){
    while(n --> 0){
        cout << content << endl;
    }
    this_thread::sleep_for(chrono::seconds(3));
    cout << content << " finished working" << endl;
}

void joinThread(){

    thread tj1(fun, 10, "Join Thread 1");
    //thread t2(fun, 10, "Thread 2");
    tj1.join();
    //tj2.join();
    //tj1.join(); // again calling ti.join() terminates the program. we can use joinable for this scenerio.
    if(tj1.joinable()){tj1.join();}
}

void detachThread(){

    thread td1(fun, 10, " Detach Thread 1");
    thread td2(fun, 10, " Detach Thread 2");
    td1.detach();
    td2.detach();
}


int main(){
    cout << "Thread started working" << endl;

    //joinThread();
    detachThread();
    this_thread::sleep_for(chrono::seconds(2));

    cout << "exiting" << endl;
    return 0;
}

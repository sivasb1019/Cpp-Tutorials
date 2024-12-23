#include <iostream>
#include <thread>

using namespace std;
typedef unsigned long long ull;

ull evenCount = 0, oddCount = 0, evenSum = 0, oddSum = 0;

void findEven(ull start, ull end_){
    for(ull i=start; i<=end_; i++){
        if(i%2==0){
            //cout << "evenSum: " << evenSum << endl;
            evenSum += i;
            evenCount++;
        }
    }
}

void findOdd(ull start, ull end_){
    for(ull i=start; i<=end_; i++){
        if(i%2!=0){
            //cout << "oddSum: " << oddSum << endl;
            oddSum += i;
            oddCount++;
        }
    }
}

int main()
{
    ull start = 0, end_ = 190000000;
    thread t1(findEven,start, end_);
    thread t2(findOdd,start, end_);

    t1.join();
    t2.join();

    cout << "Sum of even numbers     : " << evenSum << endl;
    cout << "Total even number count : " << evenCount << endl;
    cout << "Sum of odd numbers      : " << oddSum << endl;
    cout << "Total odd number count  : " << oddCount << endl;
    return 0;
}

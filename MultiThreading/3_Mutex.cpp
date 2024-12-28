#include <iostream>
#include <thread>
#include <mutex>
#include <string>

using namespace std;

int money = 0;
mutex mtx;

void addMoney(string t) {
    mtx.lock();
    money++;
    cout << t << " Money: " << money << endl;
    mtx.unlock();
}
void addMoneyBy1Lakh(string t) {
    for (int i = 0; i < 100; i++) {
        if (mtx.try_lock()) {
            //this_thread::sleep_for(chrono::seconds(1));
            cout << t << " locked rthe mutex = " << i << endl;
            money++; //critical section

            mtx.unlock();
        }
        else {
            cout << t << " can't able to lock when i = " << i << endl;
        }
    }
    cout << t << " Money: " << money << endl;
}

int main() {
    thread t1(addMoneyBy1Lakh, "Thread 1");
    thread t2(addMoneyBy1Lakh, "Thread 2");

    t1.join();
    t2.join();

    cout << "Total Money: " << money << endl;

    return 0;

}

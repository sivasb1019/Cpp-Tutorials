#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

int addMoney = 0;
timed_mutex mtx;
chrono::seconds sec(1);

void increment(int i) {
	// try_lock_untill
	auto now = chrono::steady_clock::now();
	if (mtx.try_lock_until(now + sec)){
	// if (mtx.try_lock_for(sec)){ //try_lock_for
		++addMoney;
		this_thread::sleep_for(sec * 1);
		cout << "Thread " << i << " Entered" << endl;
		mtx.unlock();
	}
	else {
		cout << "Thread " << i << " Not Entered" << endl;
	}
}

int main(){
	thread t1(increment, 1);
	thread t2(increment, 2);

	t1.join();
	t2.join();

	cout << "Money: " << addMoney << endl;

	return 0;
}
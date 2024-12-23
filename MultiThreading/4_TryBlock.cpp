#include <iostream>
#include <thread>
#include<chrono>
#include <mutex>

using namespace std;

int x = 0, y = 0;
mutex m1, m2;


void waitingSeconds(int sec) { this_thread::sleep_for(chrono::seconds(sec)); }

void incrementXorY(int& XorY, mutex& m, const char* desc) {
	for (int i = 0; i < 5; i++) {
		m.lock();
		++XorY;
		cout << desc << XorY << "\n";
		m.unlock();
		waitingSeconds(1);
	}
}

void consumeXY() {
	int useCount = 5;
	int XplusY = 0;
	while (1) {
		//int lockResult = try_lock(m1, m2);
		if (try_lock(m1, m2)) {
			if (x != 0 && y != 0) {
				--useCount;
				XplusY += x + y;
				x = 0;
				y = 0;

				cout << "x + y: " << XplusY << endl;
			}
			m1.unlock();
			m2.unlock();
			if (useCount == 0) { break; }
		}
	}

}

int main() {
	thread t1(incrementXorY, ref(x), ref(m1), "X");
	thread t2(incrementXorY, ref(y), ref(m2), "Y");


	thread consumer(consumeXY);

	t1.join();
	t2.join();

	consumer.join();

	return 0;
}
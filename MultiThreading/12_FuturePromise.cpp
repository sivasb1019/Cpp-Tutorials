#include <iostream>
#include <future>
#include <thread>

using namespace std;

void compute(promise<int> resultPromise) {
    try {
        cout << "Waiting inside compute function..." << endl;
        this_thread::sleep_for(chrono::seconds(2)); // Simulate a delay
        cout << "Waiting completed..." << endl;
        int result = 10; // Compute some result
        resultPromise.set_value(result); // Set the value for the promise
    } catch (...) {
        resultPromise.set_exception(current_exception()); // Set an exception
    }
}

int main() {
    promise<int> resultPromise;
    future<int> resultFuture = resultPromise.get_future();

    thread t(compute, move(resultPromise));

    cout << "Waiting for result...\n";

    // Wait for the result
    int value = resultFuture.get();
    cout << "The result is: " << value << "\n";

    t.join();

    return 0;
}
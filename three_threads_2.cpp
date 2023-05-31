#include <atomic>
#include <thread>
#include <iostream>

using namespace std;

atomic<int> current(1);

void print(int id) {
    for (int i = 0; i < 5; ++i) {
        // Spin until it's this thread's turn
        while (current != id) {
            this_thread::yield(); // Yield to other threads
        }

        cout << id << endl;

        // Update the current ID, wraps back to 1 after 3
        current = id % 3 + 1;
    }
}

int main() {
    thread t1(print, 1);
    thread t2(print, 2);
    thread t3(print, 3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}

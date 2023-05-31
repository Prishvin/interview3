#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;
mutex m;
condition_variable cv;
int current = 0;

void print_id(int id, int max_prints) {
    for (int i = 0; i < max_prints; ++i) {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [id] { return id == current; });
        cout << id+1 << endl; // Adding 1 to match your desired output (1, 2, 3)
        current = (current + 1) % 3;
        lock.unlock();
        cv.notify_all();
    }
}

int main() {
    int max_prints = 3; // number of times each thread should print

    thread t1(print_id, 0, max_prints);
    thread t2(print_id, 1, max_prints);
    thread t3(print_id, 2, max_prints);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}

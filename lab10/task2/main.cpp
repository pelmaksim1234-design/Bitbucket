#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

int counter = 0;

void unsafeIncrement(int threadId) {
    for (int step = 0; step < 5; ++step) {
        const int snapshot = counter;
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        counter = snapshot + threadId;

        std::cout
            << "thread " << threadId
            << ", step " << (step + 1)
            << ", counter = " << counter
            << std::endl;
    }
}

int main() {
    std::vector<std::thread> threads;

    for (int threadId = 1; threadId <= 3; ++threadId) {
        threads.emplace_back(unsafeIncrement, threadId);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "\nFinal counter value: " << counter << std::endl;
    std::cout << "This result is unreliable because the shared counter is modified without synchronization." << std::endl;

    return 0;
}

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

int counter = 0;
std::mutex counterMutex;

void safeIncrement(int threadId) {
    for (int step = 0; step < 5; ++step) {
        std::lock_guard<std::mutex> lock(counterMutex);
        counter += threadId;

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
        threads.emplace_back(safeIncrement, threadId);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "\nFinal counter value: " << counter << std::endl;
    std::cout << "Synchronization with std::mutex removes the data race." << std::endl;

    return 0;
}

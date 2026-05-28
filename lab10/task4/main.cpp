#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

std::timed_mutex firstMutex;
std::timed_mutex secondMutex;

void workerOne() {
    std::lock_guard<std::timed_mutex> firstLock(firstMutex);
    std::cout << "Worker 1 locked first mutex." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::cout << "Worker 1 tries to lock second mutex..." << std::endl;
    if (!secondMutex.try_lock_for(std::chrono::milliseconds(300))) {
        std::cout << "Worker 1 cannot lock second mutex. Deadlock risk detected." << std::endl;
        return;
    }

    std::lock_guard<std::timed_mutex> secondLock(secondMutex, std::adopt_lock);
    std::cout << "Worker 1 locked both mutexes." << std::endl;
}

void workerTwo() {
    std::lock_guard<std::timed_mutex> secondLock(secondMutex);
    std::cout << "Worker 2 locked second mutex." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::cout << "Worker 2 tries to lock first mutex..." << std::endl;
    if (!firstMutex.try_lock_for(std::chrono::milliseconds(300))) {
        std::cout << "Worker 2 cannot lock first mutex. Deadlock risk detected." << std::endl;
        return;
    }

    std::lock_guard<std::timed_mutex> firstLock(firstMutex, std::adopt_lock);
    std::cout << "Worker 2 locked both mutexes." << std::endl;
}

int main() {
    std::thread first(workerOne);
    std::thread second(workerTwo);

    first.join();
    second.join();

    std::cout << "\nDeadlock appears when threads lock the same mutexes in different order." << std::endl;
    std::cout << "Prevention: use one lock order everywhere or std::lock/scoped_lock." << std::endl;

    return 0;
}

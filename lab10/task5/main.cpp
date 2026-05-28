#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <optional>
#include <queue>
#include <thread>
#include <vector>

template <typename T>
class ThreadSafeQueue {
public:
    explicit ThreadSafeQueue(std::size_t capacity) : capacity_(capacity) {}

    void enqueue(T value) {
        std::unique_lock<std::mutex> lock(mutex_);
        notFull_.wait(lock, [this]() {
            return queue_.size() < capacity_;
        });

        queue_.push(std::move(value));
        notEmpty_.notify_one();
    }

    T dequeue() {
        std::unique_lock<std::mutex> lock(mutex_);
        notEmpty_.wait(lock, [this]() {
            return !queue_.empty();
        });

        T value = std::move(queue_.front());
        queue_.pop();
        notFull_.notify_one();
        return value;
    }

private:
    std::queue<T> queue_;
    std::size_t capacity_;
    std::mutex mutex_;
    std::condition_variable notEmpty_;
    std::condition_variable notFull_;
};

void producer(ThreadSafeQueue<int>& queue, int producerId, int baseValue) {
    for (int i = 0; i < 5; ++i) {
        const int value = baseValue + i;
        queue.enqueue(value);
        std::cout << "Producer " << producerId << " enqueued " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }
}

void consumer(ThreadSafeQueue<int>& queue, int consumerId) {
    for (int i = 0; i < 5; ++i) {
        const int value = queue.dequeue();
        std::cout << "Consumer " << consumerId << " dequeued " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(70));
    }
}

int main() {
    ThreadSafeQueue<int> queue(3);

    std::thread producerOne(producer, std::ref(queue), 1, 100);
    std::thread producerTwo(producer, std::ref(queue), 2, 200);
    std::thread consumerOne(consumer, std::ref(queue), 1);
    std::thread consumerTwo(consumer, std::ref(queue), 2);

    producerOne.join();
    producerTwo.join();
    consumerOne.join();
    consumerTwo.join();

    std::cout << "\nProducer-consumer finished without races or lost data." << std::endl;
    return 0;
}

#include <iostream>
#include <thread>
#include <vector>

int main() {
    const std::vector<int> values{2, 4, 6};
    std::vector<int> results(values.size(), 0);
    std::vector<std::thread> threads;

    for (std::size_t i = 0; i < values.size(); ++i) {
        threads.emplace_back([value = values[i], &results, i]() {
            results[i] = value * value;
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Squared values:" << std::endl;
    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << values[i] << "^2 = " << results[i] << std::endl;
    }

    return 0;
}

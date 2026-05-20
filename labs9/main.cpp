#include <algorithm>
#include <array>
#include <cctype>
#include <deque>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <random>
#include <set>
#include <string>
#include <vector>

bool isOdd(int value) {
    return value % 2 != 0;
}

bool compareNameLength(const std::string& left, const std::string& right) {
    return left.size() < right.size();
}

class TaxApplier {
public:
    explicit TaxApplier(double rate) : rate_(rate) {}

    double operator()(double price) const {
        return price + price * rate_;
    }

private:
    double rate_;
};

class WithinRange {
public:
    WithinRange(int minValue, int maxValue)
        : minValue_(minValue), maxValue_(maxValue) {}

    bool operator()(int value) const {
        return value >= minValue_ && value <= maxValue_;
    }

private:
    int minValue_;
    int maxValue_;
};

template <typename Container>
void printContainer(const Container& values) {
    std::cout << "[";
    for (auto it = values.begin(); it != values.end(); ++it) {
        std::cout << *it;
        if (std::next(it) != values.end()) {
            std::cout << ", ";
        }
    }
    std::cout << "]";
}

template <typename Key, typename Value>
void printMap(const std::map<Key, Value>& values) {
    std::cout << "{";
    for (auto it = values.begin(); it != values.end(); ++it) {
        std::cout << it->first << ": " << it->second;
        if (std::next(it) != values.end()) {
            std::cout << ", ";
        }
    }
    std::cout << "}";
}

void printTitle(int number, const std::string& title) {
    std::cout << "\nTask " << number << ". " << title << std::endl;
}

void task1RemoveOddNumbers() {
    printTitle(1, "std::list<int> and std::remove_if");

    std::list<int> numbers;
    std::mt19937 generator(42);
    std::uniform_int_distribution<int> distribution(1, 99);

    std::generate_n(std::back_inserter(numbers), 20, [&]() {
        return distribution(generator);
    });

    std::cout << "Before: ";
    printContainer(numbers);
    std::cout << std::endl;

    numbers.erase(std::remove_if(numbers.begin(), numbers.end(), isOdd), numbers.end());

    std::cout << "After removing odd numbers: ";
    printContainer(numbers);
    std::cout << std::endl;
}

void task2SortNamesByLength() {
    printTitle(2, "std::array<string> sorted by name length");

    std::array<std::string, 8> names{
        "Olena", "Ihor", "Anastasiia", "Maksym", "Eva", "Volodymyr", "Sofia", "Artem"
    };

    std::cout << "Before: ";
    printContainer(names);
    std::cout << std::endl;

    std::sort(names.begin(), names.end(), compareNameLength);

    std::cout << "After: ";
    printContainer(names);
    std::cout << std::endl;
}

void task3ApplyTax() {
    printTitle(3, "std::deque<double> and TaxApplier functor");

    std::deque<double> prices{120.0, 49.99, 310.5, 85.75, 15.2};
    std::deque<double> pricesWithTax(prices.size());

    std::transform(prices.begin(), prices.end(), pricesWithTax.begin(), TaxApplier(0.2));

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Before: ";
    printContainer(prices);
    std::cout << std::endl;
    std::cout << "With 20% tax: ";
    printContainer(pricesWithTax);
    std::cout << std::endl;
    std::cout << std::defaultfloat << std::setprecision(6);
}

void task4CountWithinRange() {
    printTitle(4, "std::set<int> and std::count_if");

    std::set<int> numbers{3, 8, 12, 19, 21, 34, 45, 57, 63, 80};
    const int minValue = 20;
    const int maxValue = 60;
    const auto count = std::count_if(numbers.begin(), numbers.end(), WithinRange(minValue, maxValue));

    std::cout << "Numbers: ";
    printContainer(numbers);
    std::cout << std::endl;
    std::cout << "In range [" << minValue << ", " << maxValue << "]: " << count << std::endl;
}

void task5ShowLargeStockItems() {
    printTitle(5, "std::map<string, int> stock items greater than 100");

    std::map<std::string, int> stock{
        {"keyboard", 45},
        {"mouse", 135},
        {"monitor", 24},
        {"usb cable", 250},
        {"webcam", 118},
        {"headphones", 73}
    };

    std::cout << "Stock: ";
    printMap(stock);
    std::cout << std::endl;

    std::cout << "Items with amount greater than 100: ";
    bool first = true;
    std::for_each(stock.begin(), stock.end(), [&first](const auto& item) {
        if (item.second > 100) {
            if (!first) {
                std::cout << ", ";
            }
            std::cout << item.first << " (" << item.second << ")";
            first = false;
        }
    });
    std::cout << std::endl;
}

void task6ReplaceNegativeNumbers() {
    printTitle(6, "std::vector<int> and replacing negative values with zero");

    std::vector<int> numbers{12, -4, 0, 18, -7, 25, -1, 9};

    std::cout << "Before: ";
    printContainer(numbers);
    std::cout << std::endl;

    std::replace_if(numbers.begin(), numbers.end(), [](int value) {
        return value < 0;
    }, 0);

    std::cout << "After: ";
    printContainer(numbers);
    std::cout << std::endl;
}

void task7SumAndAverage() {
    printTitle(7, "std::vector<int> sum and average without std::accumulate");

    std::vector<int> numbers{7, 12, 5, 21, 16, 4};
    int sum = 0;

    std::for_each(numbers.begin(), numbers.end(), [&sum](int value) {
        sum += value;
    });

    const double average = numbers.empty()
        ? 0.0
        : static_cast<double>(sum) / static_cast<double>(numbers.size());

    std::cout << "Numbers: ";
    printContainer(numbers);
    std::cout << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Average: " << average << std::endl;
}

void task8CountVowels() {
    printTitle(8, "Count vowels in a text string");

    const std::string text = "Standard Template Library algorithms make code shorter.";
    const std::string vowels = "aeiouy";

    const auto count = std::count_if(text.begin(), text.end(), [&vowels](unsigned char symbol) {
        const char lower = static_cast<char>(std::tolower(symbol));
        return vowels.find(lower) != std::string::npos;
    });

    std::cout << "Text: " << text << std::endl;
    std::cout << "Vowels: " << count << std::endl;
}

int main() {
    task1RemoveOddNumbers();
    task2SortNamesByLength();
    task3ApplyTax();
    task4CountWithinRange();
    task5ShowLargeStockItems();
    task6ReplaceNegativeNumbers();
    task7SumAndAverage();
    task8CountVowels();

    return 0;
}

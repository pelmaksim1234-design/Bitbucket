#include <iostream>
#include <string>
#include <utility>
#include <vector>

template <typename T, typename IsEven>
std::pair<std::vector<T>, std::vector<T>> split_by_parity(
    const std::vector<T>& values,
    IsEven isEven
) {
    std::vector<T> evenValues;
    std::vector<T> oddValues;

    for (auto it = values.begin(); it != values.end(); ++it) {
        if (isEven(*it)) {
            evenValues.push_back(*it);
        } else {
            oddValues.push_back(*it);
        }
    }

    return {evenValues, oddValues};
}

class NumberBox {
public:
    NumberBox() = default;
    explicit NumberBox(int value) : value_(value) {}

    int value() const {
        return value_;
    }

    friend std::ostream& operator<<(std::ostream& out, const NumberBox& number) {
        out << "box(" << number.value_ << ")";
        return out;
    }

private:
    int value_ = 0;
};

template <typename T>
void print_vector(const std::vector<T>& values) {
    std::cout << "[";
    for (auto it = values.begin(); it != values.end(); ++it) {
        std::cout << *it;
        if (it + 1 != values.end()) {
            std::cout << ", ";
        }
    }
    std::cout << "]";
}

template <typename T>
void print_result(const std::pair<std::vector<T>, std::vector<T>>& result) {
    std::cout << "Even: ";
    print_vector(result.first);
    std::cout << std::endl;

    std::cout << "Odd: ";
    print_vector(result.second);
    std::cout << std::endl;
}

int main() {
    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7};
    print_result(split_by_parity(numbers, [](int value) {
        return value % 2 == 0;
    }));

    std::cout << std::endl;

    std::vector<NumberBox> boxes{NumberBox(10), NumberBox(15), NumberBox(22), NumberBox(31)};
    print_result(split_by_parity(boxes, [](const NumberBox& box) {
        return box.value() % 2 == 0;
    }));

    return 0;
}


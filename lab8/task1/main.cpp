#include <array>
#include <iostream>
#include <string>

template <typename T, std::size_t FirstSize, std::size_t SecondSize>
std::array<T, FirstSize + SecondSize> merge_sorted_arrays(
    const std::array<T, FirstSize>& first,
    const std::array<T, SecondSize>& second
) {
    std::array<T, FirstSize + SecondSize> result{};
    auto firstIt = first.begin();
    auto secondIt = second.begin();
    auto resultIt = result.begin();

    while (firstIt != first.end() && secondIt != second.end()) {
        if (*secondIt < *firstIt) {
            *resultIt = *secondIt;
            ++secondIt;
        } else {
            *resultIt = *firstIt;
            ++firstIt;
        }
        ++resultIt;
    }

    while (firstIt != first.end()) {
        *resultIt = *firstIt;
        ++firstIt;
        ++resultIt;
    }

    while (secondIt != second.end()) {
        *resultIt = *secondIt;
        ++secondIt;
        ++resultIt;
    }

    return result;
}

class Student {
public:
    Student() = default;
    Student(std::string name, int mark) : name_(name), mark_(mark) {}

    bool operator<(const Student& other) const {
        return mark_ < other.mark_;
    }

    friend std::ostream& operator<<(std::ostream& out, const Student& student) {
        out << student.name_ << "(" << student.mark_ << ")";
        return out;
    }

private:
    std::string name_;
    int mark_ = 0;
};

template <typename T, std::size_t Size>
void print_array(const std::array<T, Size>& values) {
    std::cout << "[";
    for (auto it = values.begin(); it != values.end(); ++it) {
        std::cout << *it;
        if (it + 1 != values.end()) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

int main() {
    std::array<int, 4> firstNumbers{1, 4, 7, 10};
    std::array<int, 3> secondNumbers{2, 3, 8};
    print_array(merge_sorted_arrays(firstNumbers, secondNumbers));

    std::array<std::string, 3> firstWords{"apple", "cat", "home"};
    std::array<std::string, 3> secondWords{"book", "dog", "zoo"};
    print_array(merge_sorted_arrays(firstWords, secondWords));

    std::array<Student, 2> firstStudents{Student("Ira", 75), Student("Oleh", 90)};
    std::array<Student, 2> secondStudents{Student("Nazar", 68), Student("Anna", 82)};
    print_array(merge_sorted_arrays(firstStudents, secondStudents));

    return 0;
}


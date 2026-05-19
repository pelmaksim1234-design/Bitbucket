#include <deque>
#include <iostream>
#include <string>

template <typename T>
bool is_palindrome(const std::deque<T>& values) {
    if (values.empty()) {
        return true;
    }

    auto left = values.begin();
    auto right = values.end();
    --right;

    while (left < right) {
        if (!(*left == *right)) {
            return false;
        }

        ++left;
        --right;
    }

    return true;
}

class Word {
public:
    Word() = default;
    explicit Word(std::string text) : text_(text) {}

    bool operator==(const Word& other) const {
        return text_ == other.text_;
    }

    friend std::ostream& operator<<(std::ostream& out, const Word& word) {
        out << word.text_;
        return out;
    }

private:
    std::string text_;
};

template <typename T>
void print_check(const std::deque<T>& values) {
    std::cout << "[";
    for (auto it = values.begin(); it != values.end(); ++it) {
        std::cout << *it;
        if (it + 1 != values.end()) {
            std::cout << ", ";
        }
    }
    std::cout << "] -> ";

    if (is_palindrome(values)) {
        std::cout << "palindrome";
    } else {
        std::cout << "not palindrome";
    }

    std::cout << std::endl;
}

int main() {
    std::deque<int> numbers{1, 2, 3, 2, 1};
    print_check(numbers);

    std::deque<char> letters{'r', 'a', 'c', 'e'};
    print_check(letters);

    std::deque<Word> words{Word("one"), Word("two"), Word("one")};
    print_check(words);

    return 0;
}


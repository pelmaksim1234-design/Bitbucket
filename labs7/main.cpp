#include <exception>
#include <iostream>
#include <string>

#include "Lists.hpp"

int main() {
    try {
        SinglyLinkedList<int> numbers;
        numbers.push_back(10);
        numbers.push_back(20);
        numbers.push_front(5);
        numbers.insert(2, 15);

        std::cout << "Singly linked list: ";
        numbers.print();
        std::cout << "Element with index 2: " << numbers.at(2) << std::endl;
        std::cout << "Index of 20: " << numbers.find(20) << std::endl;
        std::cout << "Removed first: " << numbers.pop_front() << std::endl;
        std::cout << "Removed last: " << numbers.pop_back() << std::endl;
        std::cout << "Size: " << numbers.size() << std::endl;
        std::cout << "Is empty: " << std::boolalpha << numbers.empty() << std::endl;
        numbers.print();

        std::cout << std::endl;

        DoublyLinkedList<std::string> words;
        words.push_back("one");
        words.push_back("three");
        words.push_front("zero");
        words.insert(2, "two");

        std::cout << "Doubly linked list: ";
        words.print();
        std::cout << "Element with index 1: " << words.at(1) << std::endl;
        std::cout << "Index of two: " << words.find("two") << std::endl;
        std::cout << "Removed with index 2: " << words.remove(2) << std::endl;
        std::cout << "Removed first: " << words.pop_front() << std::endl;
        std::cout << "Removed last: " << words.pop_back() << std::endl;
        std::cout << "Size: " << words.size() << std::endl;
        std::cout << "Is empty: " << words.empty() << std::endl;
        words.print();
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        return 1;
    }

    return 0;
}


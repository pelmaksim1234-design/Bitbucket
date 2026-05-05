#include <exception>
#include <iostream>
#include <string>

#include "Lists.hpp"

int main() {
    try {
        // Приклад роботи з однозв'язним списком цілих чисел.
        SinglyLinkedList<int> singly;
        singly.push_back(10);
        singly.push_back(20);
        singly.push_front(5);
        singly.insert(2, 15);

        std::cout << "Singly linked list: ";
        singly.print();
        std::cout << "Element at index 2: " << singly.at(2) << std::endl;
        std::cout << "Index of 20: " << singly.find(20) << std::endl;
        std::cout << "Removed first: " << singly.pop_front() << std::endl;
        std::cout << "Removed last: " << singly.pop_back() << std::endl;
        std::cout << "Size: " << singly.size() << std::endl;
        std::cout << "Is empty: " << std::boolalpha << singly.empty() << std::endl;
        singly.print();

        std::cout << std::endl;

        // Приклад роботи з двозв'язним списком рядків.
        DoublyLinkedList<std::string> doubly;
        doubly.push_back("one");
        doubly.push_back("three");
        doubly.push_front("zero");
        doubly.insert(2, "two");

        std::cout << "Doubly linked list: ";
        doubly.print();
        std::cout << "Element at index 1: " << doubly.at(1) << std::endl;
        std::cout << "Index of two: " << doubly.find("two") << std::endl;
        std::cout << "Removed at index 2: " << doubly.remove(2) << std::endl;
        std::cout << "Removed first: " << doubly.pop_front() << std::endl;
        std::cout << "Removed last: " << doubly.pop_back() << std::endl;
        std::cout << "Size: " << doubly.size() << std::endl;
        std::cout << "Is empty: " << doubly.empty() << std::endl;
        doubly.print();
    } catch (const std::exception& error) {
        // Обробка помилок, які виникають під час неправильного доступу до списку.
        std::cerr << "Error: " << error.what() << std::endl;
        return 1;
    }

    return 0;
}

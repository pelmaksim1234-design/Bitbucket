#ifndef LISTS_HPP
#define LISTS_HPP

#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T>
struct Node {
    // Вузол списку зберігає значення, посилання на наступний вузол і попередній вузол.
    T data;
    std::shared_ptr<Node<T>> next;
    std::weak_ptr<Node<T>> previous;

    explicit Node(const T& value) : data(value), next(nullptr), previous() {}
};

template <typename T>
class SinglyLinkedList {
public:
    // Додає елемент на початок однозв'язного списку.
    void push_front(const T& value) {
        auto node = std::make_shared<Node<T>>(value);
        node->next = head_;
        head_ = node;

        if (!tail_) {
            tail_ = head_;
        }

        ++size_;
    }

    // Додає елемент у кінець однозв'язного списку.
    void push_back(const T& value) {
        auto node = std::make_shared<Node<T>>(value);

        if (empty()) {
            head_ = tail_ = node;
        } else {
            tail_->next = node;
            tail_ = node;
        }

        ++size_;
    }

    // Видаляє перший елемент і повертає його значення.
    T pop_front() {
        ensure_not_empty();

        T value = head_->data;
        head_ = head_->next;
        --size_;

        if (empty()) {
            tail_.reset();
        }

        return value;
    }

    // Видаляє останній елемент і повертає його значення.
    T pop_back() {
        ensure_not_empty();

        if (size_ == 1) {
            return pop_front();
        }

        auto current = head_;
        while (current->next != tail_) {
            current = current->next;
        }

        T value = tail_->data;
        current->next.reset();
        tail_ = current;
        --size_;
        return value;
    }

    // Повертає елемент за індексом з перевіркою меж.
    T& at(std::size_t index) {
        return node_at(index)->data;
    }

    const T& at(std::size_t index) const {
        return node_at(index)->data;
    }

    // Вставляє новий елемент у вказану позицію.
    void insert(std::size_t index, const T& value) {
        if (index > size_) {
            throw std::out_of_range("Insert index is out of range");
        }

        if (index == 0) {
            push_front(value);
            return;
        }

        if (index == size_) {
            push_back(value);
            return;
        }

        auto previous = node_at(index - 1);
        auto node = std::make_shared<Node<T>>(value);
        node->next = previous->next;
        previous->next = node;
        ++size_;
    }

    // Видаляє елемент за індексом і повертає його значення.
    T remove(std::size_t index) {
        if (index == 0) {
            return pop_front();
        }

        auto previous = node_at(index - 1);
        auto current = previous->next;

        if (!current) {
            throw std::out_of_range("Remove index is out of range");
        }

        T value = current->data;
        previous->next = current->next;

        if (current == tail_) {
            tail_ = previous;
        }

        --size_;
        return value;
    }

    // Повертає кількість елементів у списку.
    std::size_t size() const {
        return size_;
    }

    // Перевіряє, чи список порожній.
    bool empty() const {
        return size_ == 0;
    }

    // Шукає елемент у списку. Якщо елемент не знайдено, повертає -1.
    int find(const T& value) const {
        auto current = head_;
        int index = 0;

        while (current) {
            if (current->data == value) {
                return index;
            }

            current = current->next;
            ++index;
        }

        return -1;
    }

    // Виводить список на екран за допомогою cout.
    void print() const {
        auto current = head_;
        std::cout << "[";

        while (current) {
            std::cout << current->data;
            current = current->next;

            if (current) {
                std::cout << ", ";
            }
        }

        std::cout << "]" << std::endl;
    }

private:
    // Вказівники на початок, кінець і поточний розмір списку.
    std::shared_ptr<Node<T>> head_;
    std::shared_ptr<Node<T>> tail_;
    std::size_t size_ = 0;

    // Генерує виняток, якщо список порожній.
    void ensure_not_empty() const {
        if (empty()) {
            throw std::underflow_error("List is empty");
        }
    }

    // Повертає вузол за індексом.
    std::shared_ptr<Node<T>> node_at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index is out of range");
        }

        auto current = head_;
        for (std::size_t i = 0; i < index; ++i) {
            current = current->next;
        }

        return current;
    }
};

template <typename T>
class DoublyLinkedList {
public:
    // Додає елемент на початок двозв'язного списку.
    void push_front(const T& value) {
        auto node = std::make_shared<Node<T>>(value);
        node->next = head_;

        if (head_) {
            head_->previous = node;
        }

        head_ = node;

        if (!tail_) {
            tail_ = head_;
        }

        ++size_;
    }

    // Додає елемент у кінець двозв'язного списку.
    void push_back(const T& value) {
        auto node = std::make_shared<Node<T>>(value);
        node->previous = tail_;

        if (tail_) {
            tail_->next = node;
        }

        tail_ = node;

        if (!head_) {
            head_ = tail_;
        }

        ++size_;
    }

    // Видаляє перший елемент і повертає його значення.
    T pop_front() {
        ensure_not_empty();

        T value = head_->data;
        head_ = head_->next;

        if (head_) {
            head_->previous.reset();
        } else {
            tail_.reset();
        }

        --size_;
        return value;
    }

    // Видаляє останній елемент і повертає його значення.
    T pop_back() {
        ensure_not_empty();

        T value = tail_->data;
        auto previous = tail_->previous.lock();
        tail_ = previous;

        if (tail_) {
            tail_->next.reset();
        } else {
            head_.reset();
        }

        --size_;
        return value;
    }

    // Повертає елемент за індексом з перевіркою меж.
    T& at(std::size_t index) {
        return node_at(index)->data;
    }

    const T& at(std::size_t index) const {
        return node_at(index)->data;
    }

    // Вставляє новий елемент у вказану позицію.
    void insert(std::size_t index, const T& value) {
        if (index > size_) {
            throw std::out_of_range("Insert index is out of range");
        }

        if (index == 0) {
            push_front(value);
            return;
        }

        if (index == size_) {
            push_back(value);
            return;
        }

        auto current = node_at(index);
        auto previous = current->previous.lock();
        auto node = std::make_shared<Node<T>>(value);

        node->previous = previous;
        node->next = current;
        previous->next = node;
        current->previous = node;
        ++size_;
    }

    // Видаляє елемент за індексом і повертає його значення.
    T remove(std::size_t index) {
        if (index == 0) {
            return pop_front();
        }

        if (index + 1 == size_) {
            return pop_back();
        }

        auto current = node_at(index);
        auto previous = current->previous.lock();
        auto next = current->next;
        T value = current->data;

        previous->next = next;
        next->previous = previous;
        --size_;
        return value;
    }

    // Повертає кількість елементів у списку.
    std::size_t size() const {
        return size_;
    }

    // Перевіряє, чи список порожній.
    bool empty() const {
        return size_ == 0;
    }

    // Шукає елемент у списку. Якщо елемент не знайдено, повертає -1.
    int find(const T& value) const {
        auto current = head_;
        int index = 0;

        while (current) {
            if (current->data == value) {
                return index;
            }

            current = current->next;
            ++index;
        }

        return -1;
    }

    // Виводить список на екран за допомогою cout.
    void print() const {
        auto current = head_;
        std::cout << "[";

        while (current) {
            std::cout << current->data;
            current = current->next;

            if (current) {
                std::cout << ", ";
            }
        }

        std::cout << "]" << std::endl;
    }

private:
    // Вказівники на початок, кінець і поточний розмір списку.
    std::shared_ptr<Node<T>> head_;
    std::shared_ptr<Node<T>> tail_;
    std::size_t size_ = 0;

    // Генерує виняток, якщо список порожній.
    void ensure_not_empty() const {
        if (empty()) {
            throw std::underflow_error("List is empty");
        }
    }

    // Повертає вузол за індексом. Пошук починається з ближчого краю списку.
    std::shared_ptr<Node<T>> node_at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index is out of range");
        }

        if (index < size_ / 2) {
            auto current = head_;
            for (std::size_t i = 0; i < index; ++i) {
                current = current->next;
            }

            return current;
        }

        auto current = tail_;
        for (std::size_t i = size_ - 1; i > index; --i) {
            current = current->previous.lock();
        }

        return current;
    }
};

#endif

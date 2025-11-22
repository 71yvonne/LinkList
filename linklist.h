#ifndef LINKLIST_LINKLIST_H
#define LINKLIST_LINKLIST_H

#include <cstddef>
#include <iostream>

template<typename T>
class LinkList;

// Linked list node
template<typename T>
class node {
    friend class LinkList<T>;

public:
    T data; // Data field
    node<T> *pre; // Previous pointer
    node<T> *next; // Next pointer

    explicit node(const T &data) : data(data), pre(nullptr), next(nullptr) {
    }
};

// Doubly circular linked list
template<typename T>
class LinkList {
public:
    node<T> *head; // Head pointer points to head node

    // constructor
    LinkList() {
        head = new node<T>(T{});
        head->pre = head;
        head->next = head;
        _size = 0;
    }

    // destructor
    ~LinkList() {
        _clear();
        delete head;
        head = nullptr;
    }

    // Copy constructor
    LinkList(const LinkList &other) {
        head = new node<T>(T{});
        head->pre = head;
        head->next = head;
        _size = 0;

        // Deep copy all elements from other
        node<T> *cur = other.head->next;
        while (cur != other.head) {
            insertBack(cur->data);
            cur = cur->next;
        }
    }

    // Copy assignment operator
    LinkList &operator=(const LinkList &other) {
        if (this != &other) {
            // Clear current list
            _clear();

            // Deep copy all elements from other
            node<T> *cur = other.head->next;
            while (cur != other.head) {
                insertBack(cur->data);
                cur = cur->next;
            }
        }
        return *this;
    }

    // Move constructor
    LinkList(LinkList &&other) noexcept : head(other.head), _size(other._size) {
        // Prevent other's destructor from deleting nodes we now own
        other.head = nullptr;
        other._size = 0;
    }

    // Move assignment operator
    LinkList &operator=(LinkList &&other) noexcept {
        if (this != &other) {
            // Clear current list
            _clear();
            delete head;

            // Take resources from other
            head = other.head;
            _size = other._size;

            // Prevent other's destructor from deleting nodes we now own
            other.head = nullptr;
            other._size = 0;
        }
        return *this;
    }

    // Get list length
    std::size_t size() const {
        return _size;
    }

    // Insert element at specified position
    bool insert(std::size_t pos, const T &data) {
        if (pos > _size) return false; // Invalid position

        // Find the previous node at the insertion position
        node<T> *cur = head;
        for (std::size_t i = 0; i < pos; ++i) {
            cur = cur->next;
        }

        // Create new node
        node<T> *newnode = new node<T>(data);

        // Insert node
        newnode->next = cur->next;
        newnode->pre = cur;
        cur->next->pre = newnode;
        cur->next = newnode;

        _size++;
        return true;
    }

    // Insert element at the beginning
    bool insertFront(const T &data) {
        return insert(0, data);
    }

    // Insert element at the end
    bool insertBack(const T &data) {
        return insert(_size, data);
    }

    // Delete element at specified position
    bool erase(std::size_t pos) {
        if (pos >= _size || _size == 0) return false; // Invalid position or empty list

        // Find the previous node of the one to be deleted
        node<T> *cur = head;
        for (std::size_t i = 0; i < pos; ++i) {
            cur = cur->next;
        }

        // Get the node to be deleted
        node<T> *delNode = cur->next;

        // Reconnect pointers
        cur->next = delNode->next;
        delNode->next->pre = cur;

        // Delete node
        delete delNode;

        _size--;
        return true;
    }

    // Delete element at the beginning
    bool eraseFront() {
        return erase(0);
    }

    // Delete element at the end
    bool eraseBack() {
        return erase(_size - 1);
    }

    // Find element by position
    T *findByPos(std::size_t pos) {
        if (pos >= _size) return nullptr; // Invalid position

        node<T> *cur = head->next;
        for (std::size_t i = 0; i < pos; ++i) {
            cur = cur->next;
        }

        return &(cur->data);
    }

    // Find position by element value
    std::size_t findByValue(const T &data) {
        node<T> *cur = head->next;
        for (std::size_t i = 0; i < _size; ++i) {
            if (cur->data == data) {
                return i;
            }
            cur = cur->next;
        }

        return _size; // Not found, return list length to indicate not found
    }

    // Check if element exists
    bool contains(const T &data) {
        return findByValue(data) != _size;
    }

    // Locate node at specific position
    node<T> *locate(std::size_t pos) {
        if (pos > _size) return nullptr; // Invalid position (can locate head node)

        node<T> *cur = head;
        for (std::size_t i = 0; i < pos; ++i) {
            cur = cur->next;
        }

        return cur;
    }

    // Get first node
    node<T> *first() {
        return _size > 0 ? head->next : nullptr;
    }

    // Get last node
    node<T> *last() {
        return _size > 0 ? head->pre : nullptr;
    }

    // Traverse and output list elements
    void display() const {
        if (_size == 0) {
            std::cout << "List is empty" << std::endl;
            return;
        }

        std::cout << "List contents: ";
        node<T> *cur = head->next;
        for (std::size_t i = 0; i < _size; ++i) {
            std::cout << cur->data;
            if (i < _size - 1) {
                std::cout << " -> ";
            }
            cur = cur->next;
        }
        std::cout << std::endl;
    }

    // Reverse traverse and output list elements
    void displayReverse() const {
        if (_size == 0) {
            std::cout << "List is empty" << std::endl;
            return;
        }

        std::cout << "List contents (reverse): ";
        node<T> *cur = head->pre;
        for (std::size_t i = 0; i < _size; ++i) {
            std::cout << cur->data;
            if (i < _size - 1) {
                std::cout << " <- ";
            }
            cur = cur->pre;
        }
        std::cout << std::endl;
    }

private:
    std::size_t _size; // Record list length

    // Destroy list
    void _clear() {
        while (head->next != head) {
            node<T> *tmp = head->next;
            head->next = tmp->next;
            tmp->next->pre = head;
            delete tmp;
        }
    }
};

#endif // LINKLIST_LINKLIST_H

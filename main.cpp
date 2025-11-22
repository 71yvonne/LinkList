#include <iostream>
#include <string>
#include "linklist.h"

int main() {
    std::cout << "===== Doubly Circular Linked List Test =====" << std::endl;

    // Create an integer linked list
    LinkList<int> list;

    // Test initial state
    std::cout << "1. Test initial state:" << std::endl;
    std::cout << "List length: " << list.size() << std::endl;
    list.display();

    // Test insertion operations
    std::cout << "\n2. Test insertion operations:" << std::endl;
    std::cout << "Insert element 10 at the end" << std::endl;
    list.insertBack(10);
    list.display();

    std::cout << "Insert element 5 at the beginning" << std::endl;
    list.insertFront(5);
    list.display();

    std::cout << "Insert element 15 at the end" << std::endl;
    list.insertBack(15);
    list.display();

    std::cout << "Insert element 12 at position 2" << std::endl;
    list.insert(2, 12);
    list.display();

    std::cout << "Insert element 7 at position 1" << std::endl;
    list.insert(1, 7);
    list.display();

    std::cout << "Current list length: " << list.size() << std::endl;

    // Test search operations
    std::cout << "\n3. Test search operations:" << std::endl;
    std::cout << "Find element at position 3: " << (list.findByPos(3) ? std::to_string(*list.findByPos(3)) : "Invalid position") << std::endl;
    std::cout << "Find position of element 12: " << list.findByValue(12) << std::endl;
    std::cout << "Find position of element 99: " << list.findByValue(99) << std::endl;
    std::cout << "Does the list contain element 15: " << (list.contains(15) ? "Yes" : "No") << std::endl;
    std::cout << "Does the list contain element 20: " << (list.contains(20) ? "Yes" : "No") << std::endl;

    // Test positioning operations
    std::cout << "\n4. Test positioning operations:" << std::endl;
    std::cout << "Value of first node: " << (list.first() ? std::to_string(list.first()->data) : "List is empty") << std::endl;
    std::cout << "Value of last node: " << (list.last() ? std::to_string(list.last()->data) : "List is empty") << std::endl;

    // Test reverse traversal
    std::cout << "\n5. Test reverse traversal:" << std::endl;
    list.displayReverse();

    // Test deletion operations
    std::cout << "\n6. Test deletion operations:" << std::endl;
    std::cout << "Delete element at position 2" << std::endl;
    list.erase(2);
    list.display();

    std::cout << "Delete element at the beginning" << std::endl;
    list.eraseFront();
    list.display();

    std::cout << "Delete element at the end" << std::endl;
    list.eraseBack();
    list.display();

    std::cout << "Current list length: " << list.size() << std::endl;

    // Test clearing the list
    std::cout << "\n7. Test clearing the list:" << std::endl;
    while (list.size() > 0) {
        list.eraseFront();
        std::cout << "After deleting head element, list length: " << list.size() << std::endl;
        list.display();
    }

    // Test edge cases
    std::cout << "\n8. Test edge cases:" << std::endl;
    std::cout << "Attempt to delete from empty list: " << (list.eraseFront() ? "Success" : "Failed") << std::endl;
    std::cout << "Attempt to find element in empty list: " << (list.findByPos(0) ? "Success" : "Failed") << std::endl;

    // Test string type linked list
    std::cout << "\n9. Test string type linked list:" << std::endl;
    LinkList<std::string> strList;
    std::cout << "Insert element \"Hello\" at the end" << std::endl;
    strList.insertBack("Hello");
    std::cout << "Insert element \"World\" at the end" << std::endl;
    strList.insertBack("World");
    std::cout << "Insert element \"C++\" at the beginning" << std::endl;
    strList.insertFront("C++");
    strList.display();
    std::cout << "String list length: " << strList.size() << std::endl;

    std::cout << "\n===== Test Completed =====" << std::endl;

    return 0;
}

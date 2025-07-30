#include <iostream>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <unordered_set>

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        std::shared_ptr<Node> next;
        Node(const T& value) : data(value), next(nullptr) {}
    };
    
    std::shared_ptr<Node> head;
    size_t size;

    class EmptyListException : public std::runtime_error {
    public:
        EmptyListException() : std::runtime_error("Operation failed: List is empty") {}
    };

public:
    LinkedList() : head(nullptr), size(0) {}
    
    void push_front(const T& value) {
        auto newNode = std::make_shared<Node>(value);
        newNode->next = head;
        head = newNode;
        size++;
    }
    
    void push_back(const T& value) {
        auto newNode = std::make_shared<Node>(value);
        if (!head) {
            head = newNode;
        } else {
            auto current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }
    
    void reverse() {
        if (!head || !head->next) return;
        
        std::shared_ptr<Node> prev = nullptr;
        auto current = head;
        std::shared_ptr<Node> next = nullptr;
        
        while (current) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }
    
    bool hasCycle() {
        if (!head) return false;
        
        auto slow = head;
        auto fast = head;
        
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }
    
    void sort() {
        if (!head || !head->next) return;
        
        std::vector<T> values;
        auto current = head;
        while (current) {
            values.push_back(current->data);
            current = current->next;
        }
        
        std::sort(values.begin(), values.end());
        
        current = head;
        for (const auto& value : values) {
            current->data = value;
            current = current->next;
        }
    }
    
    T& front() {
        if (!head) throw EmptyListException();
        return head->data;
    }
    
    void remove(const T& value) {
        if (!head) return;
        
        if (head->data == value) {
            head = head->next;
            size--;
            return;
        }
        
        auto current = head;
        while (current->next && current->next->data != value) {
            current = current->next;
        }
        
        if (current->next) {
            current->next = current->next->next;
            size--;
        }
    }
    
    size_t getSize() const { return size; }
    
    void display() const {
        auto current = head;
        while (current) {
            std::cout << current->data;
            if (current->next) std::cout << " -> ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    try {
        LinkedList<int> list;
        
        // Adding elements
        list.push_back(11);
        list.push_back(22);
        list.push_back(33);
        list.push_front(44);
        list.push_back(55);
        
        std::cout << "Original list: ";
        list.display();
        
        // Reverse the list
        list.reverse();
        std::cout << "Reversed list: ";
        list.display();
        
        // Sort the list
        list.sort();
        std::cout << "Sorted list: ";
        list.display();
        
        // Remove an element
        list.remove(33);
        std::cout << "After removing 33: ";
        list.display();
        
        // Check for cycle
        std::cout << "Has cycle: " << (list.hasCycle() ? "Yes" : "No") << std::endl;
        
        // Get front element
        std::cout << "Front element: " << list.front() << std::endl;
        
        // Get size
        std::cout << "List size: " << list.getSize() << std::endl;
        
        // Test with different data type
        LinkedList<std::string> strList;
        strList.push_back("Hello");
        strList.push_back("World");
        strList.push_back("C++");
        std::cout << "\nString list: ";
        strList.display();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}
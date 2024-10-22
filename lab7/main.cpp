#include <iostream>
#include <stdexcept>

/// @class Node
/// @brief A template class for nodes in a doubly linked list.
/// @tparam T The type of the data stored in the node.
template <typename T>
class Node {
public:
    T data;          ///< The value stored in the node.
    Node* next;      ///< Pointer to the next node.
    Node* prev;      ///< Pointer to the previous node.

    /// @brief Constructor to initialize a node with a given value.
    /// @param value The value to initialize the node with.
    Node(T value) : data(value), next(nullptr), prev(nullptr) {}
};

/// @class DoublyLinkedList
/// @brief A template class for a doubly linked list.
/// @tparam T The type of the data stored in the list.
template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;   ///< Pointer to the first node in the list.
    Node<T>* tail;   ///< Pointer to the last node in the list.
    size_t size;     ///< The current size of the list.

public:
    /// @brief Constructor to create an empty list.
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    /// @brief Destructor to clean up the list.
    ~DoublyLinkedList() {
        while (!isEmpty()) {
            removeFront();
        }
    }

    /// @brief Checks if the list is empty.
    /// @return True if the list is empty, false otherwise.
    bool isEmpty() const {
        return size == 0;
    }

    /// @brief Gets the size of the list.
    /// @return The number of elements in the list.
    size_t getSize() const {
        return size;
    }

    /// @brief Adds an element to the front of the list.
    /// @param value The value to add to the front.
    void addFront(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    /// @brief Adds an element to the end of the list.
    /// @param value The value to add to the end.
    void addBack(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    /// @brief Gets the element from the front of the list.
    /// @return The value stored in the first node.
    /// @throws std::out_of_range if the list is empty.
    T getFront() const {
        if (isEmpty()) {
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }

    /// @brief Gets the element from the end of the list.
    /// @return The value stored in the last node.
    /// @throws std::out_of_range if the list is empty.
    T getBack() const {
        if (isEmpty()) {
            throw std::out_of_range("List is empty");
        }
        return tail->data;
    }

    /// @brief Removes the element from the front of the list.
    /// @throws std::out_of_range if the list is empty.
    void removeFront() {
        if (isEmpty()) {
            throw std::out_of_range("List is empty");
        }
        Node<T>* temp = head;
        if (head == tail) { // only one element
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
        size--;
    }

    /// @brief Removes the element from the end of the list.
    /// @throws std::out_of_range if the list is empty.
    void removeBack() {
        if (isEmpty()) {
            throw std::out_of_range("List is empty");
        }
        Node<T>* temp = tail;
        if (head == tail) { // only one element
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        size--;
    }

    /// @class Iterator
    /// @brief An iterator class to allow range-based iteration over the list.
    class Iterator {
    private:
        Node<T>* current;

    public:
        /// @brief Constructor to initialize the iterator with a node.
        Iterator(Node<T>* node) : current(node) {}

        /// @brief Dereferences the iterator to get the current element.
        /// @return The value stored in the current node.
        T& operator*() const {
            return current->data;
        }

        /// @brief Advances the iterator to the next node.
        /// @return Reference to the current iterator after increment.
        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        /// @brief Compares two iterators for equality.
        /// @param other The other iterator to compare with.
        /// @return True if both iterators point to the same node, false otherwise.
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    /// @brief Gets an iterator to the first element of the list.
    /// @return An iterator pointing to the first node.
    Iterator begin() const {
        return Iterator(head);
    }

    /// @brief Gets an iterator to the past-the-end element of the list.
    /// @return An iterator pointing to null (end).
    Iterator end() const {
        return Iterator(nullptr);
    }
};

int main() {
    DoublyLinkedList<int> list;

    std::cout << "List size: " << list.getSize() << std::endl;

    // Adding elements to the list
    list.addFront(10);
    list.addBack(20);
    list.addFront(5);
    list.addBack(30);

    std::cout << "List elements: ";
    for (auto el : list) {
        std::cout << el << " ";
    }
    std::cout << std::endl;

    std::cout << "Front element: " << list.getFront() << std::endl;
    std::cout << "Back element: " << list.getBack() << std::endl;

    // Removing elements
    list.removeFront();
    list.removeBack();

    std::cout << "List after removing front and back: ";
    for (auto el : list) {
        std::cout << el << " ";
    }
    std::cout << std::endl;

    return 0;
}

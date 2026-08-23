#include <bits/stdc++.h>
using namespace std;

template <typename T>
class List
{   
    struct Node{
        T data;
        Node* next;
        Node* prev; 
        Node(const T& val) : data(val), next(nullptr), prev(nullptr) {}
    };

    Node *head;
    Node *tail;
    int sz;


    public:

    class Iterator {
        Node* current;
        public:
        Iterator(Node* node) : current(node) {}
        Node *getCurrent() const { return current; }
        T& operator*() { return current->data; }
        T* operator->() { return &(current->data); }
        Iterator& operator++() { current = current->next; return *this; }
        Iterator operator++(int) { Iterator temp = *this; current = current->next; return temp; }
        Iterator& operator--() { current = current->prev; return *this; }
        Iterator operator--(int) { Iterator temp = *this; current = current->prev; return temp; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
        bool operator==(const Iterator& other) const { return current == other.current; }
    };

    List() : head(nullptr), tail(nullptr), sz(0) {}
    
    ~List () {
        clear();
    }

    // copt ctor
    List(const List& other) : head(nullptr), tail(nullptr), sz(0)
    {
        for (Node* curr = other.head; curr != nullptr; curr = curr->next) {
            push_back(curr->data);
        }
    }

    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            for (Node* curr = other.head; curr != nullptr; curr = curr->next) {
                push_back(curr->data);
            }
        }
        return *this;
    }

    // mode ctor
    List(List&& other) noexcept : head(other.head), tail(other.tail), sz(other.sz) {
        other.head = nullptr;
        other.tail = nullptr;
        other.sz = 0;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            sz = other.sz;
            other.head = nullptr;
            other.tail = nullptr;
            other.sz = 0;
        }
        return *this;
    }

    void push_back(const T& val) {
        Node *newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        ++sz;
    }

    void push_front(const T& val) {
        Node *newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        ++sz;
    }

    void pop_back() {
        if (head == nullptr) return;
        Node* temp = tail;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        --sz;
    }

    void pop_front() {
        if (head == nullptr) return;
        Node* temp = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
        --sz;
    }

    T& front() {
        if(empty()) throw std::out_of_range("List is empty");
        return head->data;
    }

    T& back() {
        if(empty()) throw std::out_of_range("List is empty");
        return tail->data;
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
        sz = 0;
    }

    Iterator insert(Iterator pos, const T& val)
    {
        Node* newNode = new Node(val);
        Node* currentNode = pos.getCurrent();

        if (currentNode == nullptr) { // Insert at the end
            push_back(val);
            return Iterator(tail);
        } else if (currentNode == head) { // Insert at the front
            push_front(val);
            return Iterator(head);
        } else {
            newNode->next = currentNode;
            newNode->prev = currentNode->prev;
            currentNode->prev->next = newNode;
            currentNode->prev = newNode;
            ++sz;
            return Iterator(newNode);
        }
    }

    Iterator erase(Iterator pos)
    {
        Node* currentNode = pos.getCurrent();
        if (currentNode == nullptr) {
            throw std::out_of_range("Cannot erase end iterator");
        }

        Iterator nextIter(currentNode->next);

        if (currentNode == head) {
            pop_front();
        } else if (currentNode == tail) {
            pop_back();
        } else {
            currentNode->prev->next = currentNode->next;
            currentNode->next->prev = currentNode->prev;
            delete currentNode;
            --sz;
        }

        return nextIter;
    }

    int size() const {
        return sz;
    }

    bool empty() const {
        return sz == 0;
    }

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};

int main() 
{
    List<int> l;

    l.push_back(10);
    l.push_back(20);
    l.push_back(30);

    l.push_front(5);

    cout << "List: ";

    for (auto it = l.begin(); it != l.end(); ++it) {
        cout << *it << " ";
    }

    cout << "\n";

    cout << "Front: " << l.front() << "\n";
    cout << "Back: " << l.back() << "\n";
    cout << "Size: " << l.size() << "\n";

    // Insert 15 before 20
    auto it = l.begin();

    while (it != l.end() && *it != 20)
        ++it;

    l.insert(it, 15);

    cout << "After insert: ";

    for (auto x : l)
        cout << x << " ";

    cout << "\n";

    // Erase 20
    it = l.begin();

    while (it != l.end() && *it != 20)
        ++it;

    l.erase(it);

    cout << "After erase: ";

    for (auto x : l)
        cout << x << " ";

    cout << "\n";

    l.pop_front();
    l.pop_back();

    cout << "After pop: ";

    for (auto x : l)
        cout << x << " ";

    cout << "\n";

    return 0;
}

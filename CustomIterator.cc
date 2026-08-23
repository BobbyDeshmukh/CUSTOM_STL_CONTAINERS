#include <iostream>
using namespace std;

template <typename T>
class MyContainer {
private:
    T* arr;
    int sz;

public:
    MyContainer(int n) : sz(n) {
        arr = new T[sz];
    }

    ~MyContainer() {
        delete[] arr;
    }

    // Simple Iterator
    class Iterator {
    private:
        T* ptr;

    public:
        Iterator(T* p) : ptr(p) {}

        // Dereference operator
        T& operator*() {
            return *ptr;
        }

        // Prefix increment
        Iterator& operator++() {
            ++ptr;
            return *this;
        }

        // Postfix increment
        Iterator operator++(int) {
          Iterator temp = *this;
          ++ptr;
          return temp;
        }

        // Compare two iterators
        bool operator!=(const Iterator& other) const {
            return ptr != other.ptr;
        }
    };

    // Required for iteration
    Iterator begin() {
        return Iterator(arr);
    }

    Iterator end() {
        return Iterator(arr + sz);
    }

    T& operator[](int index) {
        return arr[index];
    }
};


int main() {
    MyContainer<int> obj(5);

    for (int i = 0; i < 5; i++) {
        obj[i] = (i + 1) * 10;
    }

    // Normal iterator usage
    for (auto it = obj.begin(); it != obj.end(); ++it) {
        cout << *it << " ";
    }

    cout << endl;

    // Range-based for loop
    for (auto x : obj) {
        cout << x << " ";
    }
}

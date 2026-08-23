#include <bits/stdc++.h>
using namespace std;

template <typename T>
class SharedPtr {
private:
    T* ptr;
    int* count;

    void release() {
        if (count && --(*count) == 0) {
            delete ptr;
            delete count;
        }
    }

public:
    explicit SharedPtr(T* p = nullptr)
        : ptr(p), count(new int(1)) {}

    // Destructor
    ~SharedPtr() {
        release();
    }

    // Copy constructor
    SharedPtr(const SharedPtr& other)
        : ptr(other.ptr), count(other.count) {
        ++(*count);
    }

    // Copy assignment
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();

            ptr = other.ptr;
            count = other.count;

            ++(*count);
        }

        return *this;
    }

    // Move constructor
    SharedPtr(SharedPtr&& other) noexcept
        : ptr(other.ptr), count(other.count) {

        other.ptr = nullptr;
        other.count = nullptr;
    }

    // Move assignment
    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();

            ptr = other.ptr;
            count = other.count;

            other.ptr = nullptr;
            other.count = nullptr;
        }

        return *this;
    }

    int use_count() const {
        return count ? *count : 0;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    T* get() const {
        return ptr;
    }
};

int main() {
    SharedPtr<int> sp1(new int(10));

    cout << sp1.use_count() << endl;  // 1

    SharedPtr<int> sp2 = sp1;

    cout << sp1.use_count() << endl;  // 2
    cout << sp2.use_count() << endl;  // 2

    SharedPtr<int> sp3(std::move(sp1));

    cout << sp1.use_count() << endl;  // 0
    cout << sp2.use_count() << endl;  // 2
    cout << sp3.use_count() << endl;  // 2

    sp2 = std::move(sp3);

    cout << sp1.use_count() << endl;  // 0
    cout << sp2.use_count() << endl;  // 2
    cout << sp3.use_count() << endl;  // 0
}

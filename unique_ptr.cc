#include <bits/stdc++.h>
using namespace std;

template <typename T>
class UniquePtr{

    private:
    T *ptr;

    public:
    // UniquePtr() : ptr(nullptr) {}
    explicit UniquePtr(T *p = nullptr) : ptr(p) {}

    ~UniquePtr() {
        cout << "Destructor called for UniquePtr" << endl;
        delete ptr;
    }

    // copy not allowed with unique pointer
    UniquePtr(const UniquePtr &other) = delete;
    UniquePtr& operator=(const UniquePtr &other) = delete;


    // move ctor and assignment.
    UniquePtr(UniquePtr&& other) noexcept {
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T& operator*() {
        return *ptr;
    }

    T* operator->() {
        return ptr;
    }

    // give raw pointer to the caller and release ownership from unique_ptr
    T *release() {
        T *temp = ptr;
        ptr = nullptr;
        return temp;
    }

    // reset the unique_ptr to a new pointer, deleting the old one
    void reset(T *p = nullptr) {
        delete ptr;
        ptr = p;
    }

    operator bool() const {
        return ptr != nullptr;
    }
};


int main()
{
    UniquePtr<int> p1(new int(10));

    if (p1) {
        cout << "p1 is not null" << endl;
    } else {
        cout << "p1 is null" << endl;
    }

    UniquePtr<int> p2 = std::move(p1);

    if (p2) {
        cout << "p2 is not null" << endl;
    } else {
        cout << "p2 is null" << endl;
    }

    if (p1) {
        cout << "p1 is not null" << endl;
    } else {
        cout << "p1 is null" << endl;
    }

    UniquePtr<int> p3(new int(20));
    p3.reset(new int(30));
    int *rawPtr = p3.release();
    cout << "Raw pointer value: " << *rawPtr << endl;
    delete rawPtr;

    return 0;
}

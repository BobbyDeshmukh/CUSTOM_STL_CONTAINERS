#include <iostream>
#include <stdexcept>
#include <utility>

using namespace std;

template <typename T>
class Vector
{
private:
    T* arr = nullptr;
    int sz = 0;
    int cap = 0;

    void resize()
    {
        int newCapacity = (cap == 0) ? 1 : cap * 2;

        T* temp = new T[newCapacity];

        for (int i = 0; i < sz; i++)
        {
            temp[i] = arr[i];
        }

        delete[] arr;

        arr = temp;
        cap = newCapacity;
    }

public:

    // Default constructor
    Vector() = default;

    // Constructor with size
    Vector(int size) : sz(size), cap(size * 2)
    {
        if (cap == 0)
            cap = 1;

        arr = new T[cap];
    }

    // Constructor with size and initial value
    Vector(int size, const T& initVal) : Vector(size)
    {
        for (int i = 0; i < sz; i++)
        {
            arr[i] = initVal;
        }
    }

    // Copy constructor
    Vector(const Vector& other)
        : sz(other.sz), cap(other.cap)
    {
        arr = new T[cap];

        for (int i = 0; i < sz; i++)
        {
            arr[i] = other.arr[i];
        }
    }

    // Copy assignment
    Vector& operator=(const Vector& other)
    {
        if (this != &other)
        {
            T* temp = new T[other.cap];

            for (int i = 0; i < other.sz; i++)
            {
                temp[i] = other.arr[i];
            }

            delete[] arr;

            arr = temp;
            sz = other.sz;
            cap = other.cap;
        }

        return *this;
    }

    // Move constructor
    Vector(Vector&& other) noexcept
        : arr(other.arr),
          sz(other.sz),
          cap(other.cap)
    {
        other.arr = nullptr;
        other.sz = 0;
        other.cap = 0;
    }

    // Move assignment
    Vector& operator=(Vector&& other) noexcept
    {
        if (this != &other)
        {
            delete[] arr;

            arr = other.arr;
            sz = other.sz;
            cap = other.cap;

            other.arr = nullptr;
            other.sz = 0;
            other.cap = 0;
        }

        return *this;
    }

    // Destructor
    ~Vector()
    {
        delete[] arr;
    }

    void push_back(const T& val)
    {
        if (sz == cap)
        {
            resize();
        }

        arr[sz++] = val;
    }

    void pop_back()
    {
        if (sz != 0)
        {
            --sz;
        }
    }

    int size() const
    {
        return sz;
    }

    int capacity() const
    {
        return cap;
    }

    T& operator[](int index)
    {
        if (index < 0 || index >= sz)
        {
            throw runtime_error("index out of bounds");
        }

        return arr[index];
    }

    const T& operator[](int index) const
    {
        if (index < 0 || index >= sz)
        {
            throw runtime_error("index out of bounds");
        }

        return arr[index];
    }

    // custom iterator
    class Iterator
    {
    private:
        T* ptr;
    public:
        Iterator(T* p) : ptr(p) {}

        T& operator*() { return *ptr; }
        Iterator& operator++()
        {
            ++ptr;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++ptr;
            return temp;
        }
        bool operator!=(const Iterator& other) const
        {
            return ptr != other.ptr;
        }
    };

    Iterator begin() { return Iterator(arr); }
    Iterator end() { return Iterator(arr + sz); }
};

int main()
{
    Vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    cout << "Size: " << v.size() << endl;
    cout << "Capacity: " << v.capacity() << endl;

    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }

    cout << endl;

    Vector<int> v2 = v;       // Copy constructor

    Vector<int> v3 = move(v); // Move constructor

    cout << "v size:" << v.size() << endl;
    cout << "v2 size:" << v2.size() << endl;
    cout << "v3 size:" << v3.size() << endl;


    for(Vector<int>::Iterator it = v3.begin(); it != v3.end(); ++it)
    {
        cout << *it << " ";
    }

    cout<<endl;

    for(auto it = v2.begin(); it != v2.end(); it++)
    {
        cout << *it << " ";
    }
    cout<<endl;

    for (auto it : v3)
    {
        cout << it << " ";
    }
    cout<<endl;

    return 0;
}

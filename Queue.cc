#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Queue
{
private:
    T* arr = nullptr;

    int frontIndex = 0;
    int rearIndex = 0;

    int count = 0;
    int capacity = 0;

public:

    // Default constructor
    Queue() : Queue(10)
    {
    }

    // Parameterized constructor
    Queue(int size) : capacity(size)
    {
        if (size <= 0)
        {
            throw invalid_argument("Queue size must be positive");
        }

        arr = new T[capacity];
    }

    // Destructor
    ~Queue()
    {
        delete[] arr;
    }

    void push(const T& val)
    {
        if (count == capacity)
        {
            throw runtime_error("Queue full");
        }

        arr[rearIndex] = val;

        rearIndex = (rearIndex + 1) % capacity;

        ++count;
    }

    void pop()
    {
        if (count == 0)
        {
            throw runtime_error("Queue empty");
        }

        frontIndex = (frontIndex + 1) % capacity;

        --count;
    }

    T& front()
    {
        if (count == 0)
        {
            throw runtime_error("Queue empty");
        }

        return arr[frontIndex];
    }

    const T& front() const
    {
        if (count == 0)
        {
            throw runtime_error("Queue empty");
        }

        return arr[frontIndex];
    }

    T& back()
    {
        if (count == 0)
        {
            throw runtime_error("Queue empty");
        }

        int index = (rearIndex - 1 + capacity) % capacity;

        return arr[index];
    }

    const T& back() const
    {
        if (count == 0)
        {
            throw runtime_error("Queue empty");
        }

        int index = (rearIndex - 1 + capacity) % capacity;

        return arr[index];
    }

    bool empty() const
    {
        return count == 0;
    }

    bool full() const
    {
        return count == capacity;
    }

    int size() const
    {
        return count;
    }
};

int main()
{
    Queue<int> q(4);

    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);

    cout << "Size: " << q.size() << endl;
    cout << "Front: " << q.front() << endl;
    cout << "Back: " << q.back() << endl;

    q.pop();
    q.pop();

    q.push(50);
    q.push(60);

    cout << "Size: " << q.size() << endl;
    cout << "Front: " << q.front() << endl;
    cout << "Back: " << q.back() << endl;

    return 0;
}

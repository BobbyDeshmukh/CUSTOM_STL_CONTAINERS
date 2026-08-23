#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Stack
{
private:
    T* arr = nullptr;
    int cap = 0;
    int tp = -1;

public:

    // Default constructor
    Stack() : Stack(10)
    {
    }

    // Parameterized constructor
    Stack(int size) : cap(size), tp(-1)
    {
        if (size <= 0)
            throw invalid_argument("Stack size must be positive");

        arr = new T[cap];
    }

    // Destructor
    ~Stack()
    {
        delete[] arr;
    }

    void push(const T& val)
    {
        if (tp + 1 >= cap)
        {
            throw runtime_error("Stack overflow");
        }

        arr[++tp] = val;
    }

    void pop()
    {
        if (tp == -1)
        {
            throw runtime_error("Stack underflow");
        }

        --tp;
    }

    T& top()
    {
        if (tp == -1)
        {
            throw runtime_error("Stack is empty");
        }

        return arr[tp];
    }

    const T& top() const
    {
        if (tp == -1)
        {
            throw runtime_error("Stack is empty");
        }

        return arr[tp];
    }

    int size() const
    {
        return tp + 1;
    }

    bool empty() const
    {
        return tp == -1;
    }

    int capacity() const
    {
        return cap;
    }
};

int main()
{
    Stack<int> st(4);

    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);

    // st.push(6);   // Stack overflow

    cout << "Size: " << st.size() << endl;
    cout << "Top: " << st.top() << endl;

    st.pop();

    cout << "Size: " << st.size() << endl;
    cout << "Top: " << st.top() << endl;

    return 0;
}

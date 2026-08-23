#include <iostream>
#include <vector>
#include <functional>
using namespace std;

template <typename T,
          typename Container = vector<T>,
          typename Compare = less<T>>
class PriorityQueue
{
private:
    Container arr;
    Compare comp;

    // Returns true if 'a' should come before 'b'
    bool higherPriority(const T& a, const T& b)
    {
        return comp(a, b);
    }

    void heapifyUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;

            if (higherPriority(arr[parent], arr[index]))
                break;

            swap(arr[parent], arr[index]);

            index = parent;
        }
    }

    void heapifyDown(int index)
    {
        int n = arr.size();

        while (true)
        {
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            int best = index;

            if (left < n &&
                higherPriority(arr[left], arr[best]))
            {
                best = left;
            }

            if (right < n &&
                higherPriority(arr[right], arr[best]))
            {
                best = right;
            }

            if (best == index)
                break;

            swap(arr[index], arr[best]);

            index = best;
        }
    }

public:

    PriorityQueue() = default;

    bool empty() const
    {
        return arr.empty();
    }

    size_t size() const
    {
        return arr.size();
    }

    const T& top() const
    {
        if (arr.empty())
            throw runtime_error("PriorityQueue is empty");

        return arr[0];
    }

    void push(const T& value)
    {
        arr.push_back(value);

        heapifyUp(arr.size() - 1);
    }

    void pop()
    {
        if (arr.empty())
            throw runtime_error("PriorityQueue is empty");

        arr[0] = arr.back();
        arr.pop_back();

        if (!arr.empty())
            heapifyDown(0);
    }
};

int main()
{
    PriorityQueue<int> pq;

    pq.push(10);
    pq.push(5);
    pq.push(20);
    pq.push(15);

    // cout << pq.top() << endl;


    PriorityQueue<int, vector<int>, greater<int>> pq1;

    pq1.push(10);
    pq1.push(5);
    pq1.push(20);
    pq1.push(15);

    pq1.pop();
    pq1.pop();
    pq1.pop();
    // pq1.pop();

    cout << pq1.top() << endl;

    return 0;
}

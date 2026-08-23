#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
using namespace std;

template <typename T>
class UnorderedSet
{
private:
    struct Node
    {
        T key;
        Node* next;

        Node(const T& k) : key(k), next(nullptr) {}
    };

    vector<Node*> buckets;
    size_t sz;
    float maxLoadFactor = 0.75f;

    size_t getBucketIndex(const T& key) const
    {
        return std::hash<T>{}(key) % buckets.size();
    }

    void rehash(size_t newBucketCount)
    {
        vector<Node*> newBuckets(newBucketCount, nullptr);

        for (size_t i = 0; i < buckets.size(); i++)
        {
            Node* curr = buckets[i];

            while (curr)
            {
                Node* next = curr->next;

                size_t newIndex =
                    std::hash<T>{}(curr->key) % newBucketCount;

                curr->next = newBuckets[newIndex];
                newBuckets[newIndex] = curr;

                curr = next;
            }
        }

        buckets.swap(newBuckets);
    }

    void checkRehash()
    {
        if ((float)(sz + 1) / buckets.size() > maxLoadFactor)
        {
            rehash(buckets.size() * 2);
        }
    }

public:

    // =========================
    // Iterator
    // =========================

    class Iterator
    {
    private:
        UnorderedSet* set;
        size_t bucketIndex;
        Node* current;

        void moveToNextBucket()
        {
            while (current == nullptr &&
                   bucketIndex + 1 < set->buckets.size())
            {
                bucketIndex++;
                current = set->buckets[bucketIndex];
            }
        }

    public:

        Iterator(UnorderedSet* s,
                 size_t index,
                 Node* node)
            : set(s),
              bucketIndex(index),
              current(node)
        {
        }

        T& operator*()
        {
            return current->key;
        }

        T* operator->()
        {
            return &(current->key);
        }

        Iterator& operator++()
        {
            if (current)
                current = current->next;

            moveToNextBucket();

            return *this;
        }

        bool operator==(const Iterator& other) const
        {
            return current == other.current &&
                   bucketIndex == other.bucketIndex;
        }

        bool operator!=(const Iterator& other) const
        {
            return !(*this == other);
        }
    };

    // =========================
    // Constructor
    // =========================

    UnorderedSet(size_t bucketCount = 8)
        : buckets(bucketCount, nullptr),
          sz(0)
    {
    }

    // =========================
    // Destructor
    // =========================

    ~UnorderedSet()
    {
        clear();
    }

    // =========================
    // Insert
    // =========================

    bool insert(const T& key)
    {
        checkRehash();

        size_t index = getBucketIndex(key);

        Node* curr = buckets[index];

        // Check duplicate
        while (curr)
        {
            if (curr->key == key)
                return false;

            curr = curr->next;
        }

        Node* newNode = new Node(key);

        newNode->next = buckets[index];
        buckets[index] = newNode;

        sz++;

        return true;
    }

    // =========================
    // Find
    // =========================

    Iterator find(const T& key)
    {
        size_t index = getBucketIndex(key);

        Node* curr = buckets[index];

        while (curr)
        {
            if (curr->key == key)
            {
                return Iterator(this, index, curr);
            }

            curr = curr->next;
        }

        return end();
    }

    // =========================
    // Erase
    // =========================

    bool erase(const T& key)
    {
        size_t index = getBucketIndex(key);

        Node* curr = buckets[index];
        Node* prev = nullptr;

        while (curr)
        {
            if (curr->key == key)
            {
                if (prev)
                    prev->next = curr->next;
                else
                    buckets[index] = curr->next;

                delete curr;
                sz--;

                return true;
            }

            prev = curr;
            curr = curr->next;
        }

        return false;
    }

    // =========================
    // Size
    // =========================

    size_t size() const
    {
        return sz;
    }

    // =========================
    // Empty
    // =========================

    bool empty() const
    {
        return sz == 0;
    }

    // =========================
    // Clear
    // =========================

    void clear()
    {
        for (size_t i = 0; i < buckets.size(); i++)
        {
            Node* curr = buckets[i];

            while (curr)
            {
                Node* next = curr->next;
                delete curr;
                curr = next;
            }

            buckets[i] = nullptr;
        }

        sz = 0;
    }

    // =========================
    // Begin
    // =========================

    Iterator begin()
    {
        for (size_t i = 0; i < buckets.size(); i++)
        {
            if (buckets[i])
            {
                return Iterator(this, i, buckets[i]);
            }
        }

        return end();
    }

    // =========================
    // End
    // =========================

    Iterator end()
    {
        return Iterator(this,
                        buckets.size() - 1,
                        nullptr);
    }
};

int main()
{
    UnorderedSet<int> s;

    s.insert(10);
    s.insert(20);
    s.insert(30);
    s.insert(40);

    // Duplicate
    s.insert(20);

    cout << "Elements:\n";

    for (auto it = s.begin(); it != s.end(); ++it)
    {
        cout << *it << " ";
    }

    cout << "\n";

    auto it = s.find(20);

    if (it != s.end())
    {
        cout << "Found: " << *it << endl;
    }

    s.erase(20);

    cout << "Size: " << s.size() << endl;
}

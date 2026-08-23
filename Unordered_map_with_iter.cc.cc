#include <iostream>
#include <vector>
#include <functional>
#include <utility>

using namespace std;

template <typename K, typename V>
class UnorderedMap {

private:

    struct Node {
        K key;
        V value;
        Node* next;

        Node(const K& k, const V& v)
            : key(k), value(v), next(nullptr) {}
    };

    vector<Node*> buckets;

    size_t sz;
    size_t bucketCount;

    size_t getBucketIndex(const K& key) const {
        return hash<K>{}(key) % bucketCount;
    }


public:

    // ==================================================
    // Iterator
    // ==================================================

    class Iterator {

    private:

        Node* current;
        UnorderedMap* map;
        size_t bucketIndex;

        Iterator(Node* node,
                 UnorderedMap* m,
                 size_t index)
            : current(node),
              map(m),
              bucketIndex(index) {}

        friend class UnorderedMap;


    public:

        // ------------------------------
        // Dereference
        // ------------------------------

        pair<const K&, V&> operator*() const {
            return {current->key, current->value};
        }


        // ------------------------------
        // Arrow operator
        // ------------------------------

        Node* operator->() const {
            return current;
        }


        // ------------------------------
        // Pre-increment
        // ------------------------------

        Iterator& operator++() {

            // Case 1:
            // There is another node in
            // the same bucket

            if (current->next != nullptr) {

                current = current->next;

                return *this;
            }


            // Case 2:
            // Current bucket is finished.
            // Find next non-empty bucket.

            bucketIndex++;

            while (bucketIndex < map->bucketCount &&
                   map->buckets[bucketIndex] == nullptr) {

                bucketIndex++;
            }


            // Found next bucket

            if (bucketIndex < map->bucketCount) {

                current = map->buckets[bucketIndex];
            }
            else {

                // End iterator

                current = nullptr;
            }

            return *this;
        }


        // ------------------------------
        // Post-increment
        // ------------------------------

        Iterator operator++(int) {

            Iterator temp = *this;

            ++(*this);

            return temp;
        }


        // ------------------------------
        // Comparison
        // ------------------------------

        bool operator==(const Iterator& other) const {

            return current == other.current;
        }


        bool operator!=(const Iterator& other) const {

            return !(*this == other);
        }
    };


    // ==================================================
    // Constructor
    // ==================================================

    UnorderedMap(size_t bucketsCount = 8)
        : buckets(bucketsCount, nullptr),
          sz(0),
          bucketCount(bucketsCount) {}


    // ==================================================
    // Destructor
    // ==================================================

    ~UnorderedMap() {
        clear();
    }


    // ==================================================
    // Insert
    // ==================================================

    void insert(const K& key, const V& value) {

        size_t index = getBucketIndex(key);

        Node* curr = buckets[index];

        // Check duplicate key

        while (curr != nullptr) {

            if (curr->key == key) {

                curr->value = value;

                return;
            }

            curr = curr->next;
        }


        // Create new node

        Node* newNode =
            new Node(key, value);


        // Insert at beginning

        newNode->next = buckets[index];

        buckets[index] = newNode;

        sz++;
    }


    // ==================================================
    // operator[]
    // ==================================================

    V& operator[](const K& key) {

        size_t index = getBucketIndex(key);

        Node* curr = buckets[index];

        while (curr != nullptr) {

            if (curr->key == key) {

                return curr->value;
            }

            curr = curr->next;
        }


        // Key doesn't exist

        Node* newNode =
            new Node(key, V{});

        newNode->next = buckets[index];

        buckets[index] = newNode;

        sz++;

        return newNode->value;
    }


    // ==================================================
    // find
    // ==================================================

    Iterator find(const K& key) {

        size_t index = getBucketIndex(key);

        Node* curr = buckets[index];

        while (curr != nullptr) {

            if (curr->key == key) {

                return Iterator(
                    curr,
                    this,
                    index
                );
            }

            curr = curr->next;
        }

        return end();
    }


    // ==================================================
    // erase
    // ==================================================

    bool erase(const K& key) {

        size_t index = getBucketIndex(key);

        Node* curr = buckets[index];
        Node* prev = nullptr;

        while (curr != nullptr) {

            if (curr->key == key) {

                if (prev == nullptr) {

                    buckets[index] =
                        curr->next;
                }
                else {

                    prev->next =
                        curr->next;
                }

                delete curr;

                sz--;

                return true;
            }

            prev = curr;
            curr = curr->next;
        }

        return false;
    }


    // ==================================================
    // begin()
    // ==================================================

    Iterator begin() {

        for (size_t i = 0;
             i < bucketCount;
             i++) {

            if (buckets[i] != nullptr) {

                return Iterator(
                    buckets[i],
                    this,
                    i
                );
            }
        }

        return end();
    }


    // ==================================================
    // end()
    // ==================================================

    Iterator end() {

        return Iterator(
            nullptr,
            this,
            bucketCount
        );
    }


    // ==================================================
    // size
    // ==================================================

    size_t size() const {
        return sz;
    }


    // ==================================================
    // clear
    // ==================================================

    void clear() {

        for (size_t i = 0;
             i < bucketCount;
             i++) {

            Node* curr = buckets[i];

            while (curr != nullptr) {

                Node* next = curr->next;

                delete curr;

                curr = next;
            }

            buckets[i] = nullptr;
        }

        sz = 0;
    }
};


int main() {

    UnorderedMap<string, int> mp;

    mp["apple"] = 10;
    mp["banana"] = 20;
    mp["orange"] = 30;
    mp["mango"] = 40;


    // =========================================
    // Iterator
    // =========================================

    cout << "Using iterator:\n";

    for (auto it = mp.begin();
         it != mp.end();
         ++it) {

        cout << it->key
             << " "
             << it->value
             << endl;
    }


    // =========================================
    // Range based for
    // =========================================

    cout << "\nRange based loop:\n";

    for (auto it = mp.begin();
         it != mp.end();
         ++it) {

        auto [key, value] = *it;

        cout << key
             << " "
             << value
             << endl;
    }


    // =========================================
    // find()
    // =========================================

    auto it = mp.find("banana");

    if (it != mp.end()) {

        cout << "\nFound: "
             << it->key
             << " = "
             << it->value
             << endl;
    }
}

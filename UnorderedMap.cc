#include <iostream>
#include <vector>
#include <functional>
#include <utility>
#include <stdexcept>

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

    float maxLoadFactor = 0.75f;

    // -------------------------
    // Hash function
    // -------------------------
    size_t getBucketIndex(const K& key) const {
        return std::hash<K>{}(key) % bucketCount;
    }

    // -------------------------
    // Rehash
    // -------------------------
    void rehash(size_t newBucketCount) {

        vector<Node*> newBuckets(newBucketCount, nullptr);

        for (size_t i = 0; i < bucketCount; i++) {

            Node* curr = buckets[i];

            while (curr != nullptr) {

                Node* next = curr->next;

                size_t index =
                    std::hash<K>{}(curr->key) % newBucketCount;

                curr->next = newBuckets[index];

                newBuckets[index] = curr;

                curr = next;
            }
        }

        buckets = std::move(newBuckets);

        bucketCount = newBucketCount;
    }


public:

    // =========================
    // Constructor
    // =========================

    UnorderedMap(size_t initialBuckets = 8)
        : buckets(initialBuckets, nullptr),
          sz(0),
          bucketCount(initialBuckets) {}


    // =========================
    // Destructor
    // =========================

    ~UnorderedMap() {
        clear();
    }


    // =========================
    // Insert
    // =========================

    pair<bool, V*> insert(const K& key, const V& value) {

        size_t index = getBucketIndex(key);

        Node* curr = buckets[index];

        // Check if key already exists
        while (curr != nullptr) {

            if (curr->key == key) {
                return {false, &curr->value};
            }

            curr = curr->next;
        }

        // Create new node
        Node* newNode = new Node(key, value);

        // Insert at beginning of bucket
        newNode->next = buckets[index];

        buckets[index] = newNode;

        sz++;

        // Check load factor
        if (loadFactor() > maxLoadFactor) {
            rehash(bucketCount * 2);
        }

        return {true, &newNode->value};
    }


    // =========================
    // operator[]
    // =========================

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
        // Insert default value

        Node* newNode = new Node(key, V{});

        newNode->next = buckets[index];

        buckets[index] = newNode;

        sz++;

        if (loadFactor() > maxLoadFactor) {
            rehash(bucketCount * 2);

            // Find again because bucket index may have changed
            index = getBucketIndex(key);

            curr = buckets[index];

            while (curr != nullptr) {

                if (curr->key == key)
                    return curr->value;

                curr = curr->next;
            }
        }

        return newNode->value;
    }


    // =========================
    // find
    // =========================

    V* find(const K& key) {

        size_t index = getBucketIndex(key);

        Node* curr = buckets[index];

        while (curr != nullptr) {

            if (curr->key == key) {
                return &curr->value;
            }

            curr = curr->next;
        }

        return nullptr;
    }


    // =========================
    // contains
    // =========================

    bool contains(const K& key) const {

        size_t index = getBucketIndex(key);

        Node* curr = buckets[index];

        while (curr != nullptr) {

            if (curr->key == key)
                return true;

            curr = curr->next;
        }

        return false;
    }


    // =========================
    // erase
    // =========================

    bool erase(const K& key) {

        size_t index = getBucketIndex(key);

        Node* curr = buckets[index];
        Node* prev = nullptr;

        while (curr != nullptr) {

            if (curr->key == key) {

                if (prev == nullptr) {
                    // First node
                    buckets[index] = curr->next;
                }
                else {
                    prev->next = curr->next;
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


    // =========================
    // size
    // =========================

    size_t size() const {
        return sz;
    }


    // =========================
    // empty
    // =========================

    bool empty() const {
        return sz == 0;
    }


    // =========================
    // load factor
    // =========================

    float loadFactor() const {

        return static_cast<float>(sz) /
               static_cast<float>(bucketCount);
    }


    // =========================
    // bucket count
    // =========================

    size_t getBucketCount() const {
        return bucketCount;
    }


    // =========================
    // clear
    // =========================

    void clear() {

        for (size_t i = 0; i < bucketCount; i++) {

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


    // =========================
    // Debug
    // =========================

    void print() const {

        for (size_t i = 0; i < bucketCount; i++) {

            cout << i << " : ";

            Node* curr = buckets[i];

            while (curr != nullptr) {

                cout << "[" << curr->key
                     << "," << curr->value << "] -> ";

                curr = curr->next;
            }

            cout << "NULL\n";
        }
    }
};


int main() {

    UnorderedMap<string, int> mp;

    mp["apple"] = 10;
    mp["banana"] = 20;
    mp["orange"] = 30;

    // Update existing key
    mp["apple"] = 100;

    // for(auto it = mp.begin(); it != mp.end(); ++it) {
    //     cout << it->first << " = " << it->second << endl;
    // }

    // for (auto i : mp) {
    //     cout << i.first << " = " << i.second << endl;
    // }

    // Insert
    mp.insert("mango", 40);

    cout << "apple = "
         << mp["apple"] << endl;

    cout << "banana = "
         << mp["banana"] << endl;

    cout << "mango = "
         << mp["mango"] << endl;

    // find
    auto result = mp.find("orange");

    if (result != nullptr) {
        cout << "orange = "
             << *result << endl;
    }

    // contains
    if (mp.contains("banana")) {
        cout << "banana exists\n";
    }

    // erase
    mp.erase("banana");

    cout << "After erase:\n";

    mp.print();

    cout << "Size = "
         << mp.size() << endl;

    cout << "Load factor = "
         << mp.loadFactor() << endl;





    return 0;
}

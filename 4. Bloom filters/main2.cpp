#include <iostream>
#include <vector>
#include <functional>
#include <string>

using namespace std;

class CountingBloomFilter {
private:
    int m; // size of counter array
    int k; // number of hash functions
    vector<int> counters;

    int hash(const std::string& data, int seed) const {
        std::hash<std::string> hasher;
        return hasher(data + std::to_string(seed)) % m;
    }

public:
    CountingBloomFilter(int size, int numHashes) : m(size), k(numHashes) {
        counters.resize(m, 0);
    }

    void insert(const string& item) {
        for (int i = 0; i < k; ++i) {
            int idx = hash(item, i);
            counters[idx]++;
        }
    }

    bool possiblyContains(const string& item) const {
        for (int i = 0; i < k; ++i) {
            int idx = hash(item, i);
            if (counters[idx] == 0) return false;
        }
        return true;
    }

    void remove(const string& item) {
        if (!possiblyContains(item)) return; // avoid underflow
        for (int i = 0; i < k; ++i) {
            int idx = hash(item, i);
            if (counters[idx] > 0) counters[idx]--;
        }
    }

    void debugPrint() const {
        cout << "Counters:\n";
        for (int i = 0; i < m; ++i) {
            cout << counters[i] << " ";
        }
        cout << "\n";
    }
};


int main() {
    CountingBloomFilter cbf(1000, 5); // 1000 counters, 5 hash functions

    cbf.insert("apple");
    cbf.insert("banana");
    cbf.insert("cherry");

    cout << "Before removal:\n";
    cout << "apple: " << cbf.possiblyContains("apple") << "\n";
    cout << "grape: " << cbf.possiblyContains("grape") << "\n";

    cbf.remove("apple");

    cout << "\nAfter removing apple:\n";
    cout << "apple: " << cbf.possiblyContains("apple") << "\n";

    cbf.debugPrint();

    return 0;
}

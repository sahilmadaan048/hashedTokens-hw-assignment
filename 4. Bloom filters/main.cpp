#include <iostream>
#include <vector>
#include <functional>
#include <string>
using namespace std;

class BloomFilter {
private:
    int m; // size of bit array
    int k; // number of hash functions
    vector<bool> bitArray;

    // Simulates multiple hash functions using std::hash with salt
    int hash(const std::string& data, int seed) const {
        std::hash<std::string> hasher;
        return hasher(data + std::to_string(seed)) % m;
    }


public:
    BloomFilter(int size, int numHashes) : m(size), k(numHashes) {
        bitArray.resize(m, false);
    }

    void insert(const string& item) {
        for (int i = 0; i < k; ++i) {
            int idx = hash(item, i);
            bitArray[idx] = true;
        }
    }

    bool possiblyContains(const string& item) const {
        for (int i = 0; i < k; ++i) {
            int idx = hash(item, i);
            if (!bitArray[idx]) return false;
        }
        return true; // Possibly present
    }
};

int main() {
    BloomFilter bf(1000, 5); // 1000 bits, 5 hash functions

    bf.insert("apple");
    bf.insert("banana");
    bf.insert("cherry");

    cout << "Checking elements:\n";
    cout << "apple: " << bf.possiblyContains("apple") << "\n";   // Likely true
    cout << "banana: " << bf.possiblyContains("banana") << "\n"; // Likely true
    cout << "grape: " << bf.possiblyContains("grape") << "\n";   // Likely false

    return 0;
}

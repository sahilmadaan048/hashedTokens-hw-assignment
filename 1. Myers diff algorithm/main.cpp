#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Line {
    int number;
    string text;
};

vector<Line> lines(const vector<string>& document) {
    vector<Line> result;
    for (size_t i = 0; i < document.size(); ++i) {
        result.push_back({static_cast<int>(i) + 1, document[i]});
    }
    return result;
}

class Myers {
public:
    Myers(const vector<Line>& a, const vector<Line>& b) : a(a), b(b) {}

    int shortest_edit() {
        int n = a.size();
        int m = b.size();
        int max = n + m;
        vector<int> v(2 * max + 1, 0);
        v[max + 1] = 0; 

        for (int d = 0; d <= max; ++d) {
            for (int k = -d; k <= d; k += 2) {
                int k_index = max + k;
                int x;
                if (k == -d || (k != d && v[k_index - 1] < v[k_index + 1])) {
                    x = v[k_index + 1];
                } else {
                    x = v[k_index - 1] + 1;
                }
                int y = x - k;
                while (x < n && y < m && a[x].text == b[y].text) {
                    ++x;
                    ++y;
                }
                v[k_index] = x;
                if (x >= n && y >= m) {
                    return d;
                }
            }
        }

        return -1; 
    }

private:
    const vector<Line>& a;
    const vector<Line>& b;
};


int main() {
    vector<string> doc1 = {"line one", "line two", "line three"};
    vector<string> doc2 = {"line one", "line two", "line three"};

    auto a = lines(doc1);
    auto b = lines(doc2);

    Myers diff(a, b);
    cout << "Shortest edit distance: " << diff.shortest_edit() << endl;

    return 0;
}

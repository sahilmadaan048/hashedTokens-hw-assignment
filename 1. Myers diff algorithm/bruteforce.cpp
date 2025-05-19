#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Line {
    size_t number;
    string text;

    Line(size_t n, const string& t) : number(n), text(t) {}
};

vector<Line> lines(const vector<string>& document) {
    vector<Line> result;
    for (size_t i = 0; i < document.size(); ++i) {
        result.emplace_back(i + 1, document[i]);
    }
    return result;
}

class Myers {
public:
    Myers(const vector<Line>& a, const vector<Line>& b)
        : a(a), b(b), min_edits(SIZE_MAX) {}

    size_t shortest_edit_bruteforce() {
        dfs(0, 0, 0);
        return min_edits;
    }

private:
    const vector<Line>& a;
    const vector<Line>& b;
    size_t min_edits;

    void dfs(size_t i, size_t j, size_t edits) {
        if (i == a.size() && j == b.size()) {
            min_edits = min(min_edits, edits);
            return;
        }

        if (edits >= min_edits) return;

        if (i < a.size() && j < b.size() && a[i].text == b[j].text) {
            dfs(i + 1, j + 1, edits);
        } else {
            if (i < a.size()) dfs(i + 1, j, edits + 1);
            if (j < b.size()) dfs(i, j + 1, edits + 1);
        }
    }
};

int main() {
    vector<string> doc1 = {
        "line one",
        "line two",
        "line three"
    };
    vector<string> doc2 = {
        "line one",
        "line 2",
        "line three"
    };

    vector<Line> a = lines(doc1);
    vector<Line> b = lines(doc2);

    Myers myers(a, b);
    size_t distance = myers.shortest_edit_bruteforce();
    cout << "Shortest edit distance (brute-force DFS): " << distance << endl;

    return 0;
}

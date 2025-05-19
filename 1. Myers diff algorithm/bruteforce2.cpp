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

struct EditOp {
    string op;
    size_t a_index;
    size_t b_index;
    string a_text;
    string b_text;
};

class Myers {
public:
    Myers(const vector<Line>& a, const vector<Line>& b)
        : a(a), b(b), min_edits(SIZE_MAX) {}

    size_t shortest_edit_bruteforce() {
        vector<EditOp> current_path;
        dfs(0, 0, 0, current_path);
        return min_edits;
    }

    void print_edit_path() {
        for (const auto& op : best_path) {
            if (op.op == "match") {
                cout << "  " << op.a_text << endl;
            } else if (op.op == "delete") {
                cout << "- " << op.a_text << endl;
            } else if (op.op == "insert") {
                cout << "+ " << op.b_text << endl;
            }
        }
    }

private:
    const vector<Line>& a;
    const vector<Line>& b;
    size_t min_edits;
    vector<EditOp> best_path;

    void dfs(size_t i, size_t j, size_t edits, vector<EditOp>& path) {
        if (i == a.size() && j == b.size()) {
            if (edits < min_edits) {
                min_edits = edits;
                best_path = path;
            }
            return;
        }

        if (edits >= min_edits) return;

        if (i < a.size() && j < b.size() && a[i].text == b[j].text) {
            path.push_back({"match", i, j, a[i].text, b[j].text});
            dfs(i + 1, j + 1, edits, path);
            path.pop_back();
        } else {
            if (i < a.size()) {
                path.push_back({"delete", i, j, a[i].text, ""});
                dfs(i + 1, j, edits + 1, path);
                path.pop_back();
            }
            if (j < b.size()) {
                path.push_back({"insert", i, j, "", b[j].text});
                dfs(i, j + 1, edits + 1, path);
                path.pop_back();
            }
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
    cout << "Edit path:\n";
    myers.print_edit_path();

    return 0;
}

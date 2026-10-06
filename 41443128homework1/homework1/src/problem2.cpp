#include <iostream>
#include <string>

using namespace std;

void powerset(const string& set, int index, string& current) {
    if (index == static_cast<int>(set.size())) {
        cout << "{";

        for (int i = 0; i < static_cast<int>(current.size()); ++i) {
            if (i > 0) {
                cout << ",";
            }

            cout << current[i];
        }

        cout << "}" << '\n';
        return;
    }

    powerset(set, index + 1, current);

    current += set[index];
    powerset(set, index + 1, current);
    current.pop_back();
}

int main() {
    string set = "abc";
    string current = "";

    powerset(set, 0, current);

    return 0;
}

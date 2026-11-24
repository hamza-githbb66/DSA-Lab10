#include <iostream>
#include <vector>
#include <string>
using namespace std;

int target, K, Mmax;
vector<string> opStack;   // operation stack
int found = 0;

// apply operation; returns false if not allowed
bool apply(int val, int op, int& result) {
    if (op == 0) result = val + 3;
    else if (op == 1) result = val * 2;
    else if (op == 2) result = val - 5;
    else result = val / 2;
    if (result < 0 || result > Mmax) return false;   // prune
    return true;
}

string names[4] = {"+3", "*2", "-5", "/2"};

void solve(int val, int steps) {
    if (val == target && steps > 0) {
        found++;
        cout << "Sequence " << found << ": ";
        for (int i = 0; i < (int)opStack.size(); i++) cout << opStack[i] << " ";
        cout << endl;
    }
    if (steps == K) return;

    for (int op = 0; op < 4; op++) {
        int next;
        if (!apply(val, op, next)) continue;

        opStack.push_back(names[op]);   // push
        solve(next, steps + 1);
        opStack.pop_back();             // pop (undo)
    }
}

int main() {
    int start;
    cout << "Enter start: ";   cin >> start;
    cout << "Enter target: ";  cin >> target;
    cout << "Enter max operations K: "; cin >> K;
    cout << "Enter overflow bound Mmax: "; cin >> Mmax;

    solve(start, 0);
    if (found == 0) cout << "No sequence found." << endl;
    return 0;
}
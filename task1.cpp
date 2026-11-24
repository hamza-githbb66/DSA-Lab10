#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    int id, weight;
    Node* next;
    Node(int i, int w) { id = i; weight = w; next = NULL; }
};

int W;                          // capacity of each truck
int numTrucks;
vector<int> remaining;          // remaining capacity of each truck
vector<vector<int> > loads;     // container ids in each truck

bool solve(Node* cur, int remainingWeight, int totalCap) {
    if (cur == NULL) return true;                 // all containers loaded

    // pruning: remaining weight more than remaining capacity of all trucks
    if (remainingWeight > totalCap) return false;

    for (int t = 0; t < numTrucks; t++) {
        // pruning: container doesn't fit in this truck
        if (cur->weight > remaining[t]) continue;

        remaining[t] -= cur->weight;              // choose
        loads[t].push_back(cur->id);

        if (solve(cur->next, remainingWeight - cur->weight, totalCap - cur->weight))
            return true;

        remaining[t] += cur->weight;              // backtrack
        loads[t].pop_back();
    }
    return false;
}

int main() {
    int n;
    cout << "Enter number of containers: ";
    cin >> n;

    Node* head = NULL;
    Node* tail = NULL;
    int totalWeight = 0;
    for (int i = 0; i < n; i++) {
        int id, w;
        cout << "Container " << i + 1 << " (id weight): ";
        cin >> id >> w;
        Node* nn = new Node(id, w);
        if (head == NULL) head = tail = nn;
        else { tail->next = nn; tail = nn; }
        totalWeight += w;
    }

    cout << "Enter number of trucks: ";
    cin >> numTrucks;
    cout << "Enter truck capacity W: ";
    cin >> W;

    // trucks arrive in a queue
    queue<int> trucks;
    for (int i = 1; i <= numTrucks; i++) trucks.push(i);

    while (!trucks.empty()) {
        remaining.push_back(W);
        loads.push_back(vector<int>());
        trucks.pop();
    }

    if (solve(head, totalWeight, numTrucks * W)) {
        for (int t = 0; t < numTrucks; t++) {
            cout << "Truck " << t + 1 << ": ";
            for (int j = 0; j < (int)loads[t].size(); j++) cout << loads[t][j] << " ";
            cout << endl;
        }
    } else {
        cout << "Insufficient truck capacity." << endl;
    }
    return 0;
}
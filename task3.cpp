#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int id, cost;
    Node* left;
    Node* right;
    Node(int i, int c) { id = i; cost = c; left = right = NULL; }
};

Node* insert(Node* root, int id, int cost) {
    if (root == NULL) return new Node(id, cost);
    if (cost < root->cost) root->left = insert(root->left, id, cost);
    else root->right = insert(root->right, id, cost);
    return root;
}

int B;

// ---------- Part A: downward paths ----------
vector<Node*> path;

void findPaths(Node* node, int sum) {
    if (node == NULL) return;
    path.push_back(node);                 // push
    sum += node->cost;

    if (sum == B) {
        cout << "Path: ";
        for (int i = 0; i < (int)path.size(); i++)
            cout << path[i]->id << "(" << path[i]->cost << ") ";
        cout << endl;
    }
    findPaths(node->left, sum);
    findPaths(node->right, sum);
    path.pop_back();                      // pop (backtrack)
}

// try every node as the starting point of a path
void startFromEveryNode(Node* node) {
    if (node == NULL) return;
    findPaths(node, 0);
    startFromEveryNode(node->left);
    startFromEveryNode(node->right);
}

// ---------- Part B: subsets ----------
vector<Node*> sorted;    // inorder = ascending costs
vector<Node*> subset;
int subsetCount = 0;

void inorder(Node* node) {
    if (node == NULL) return;
    inorder(node->left);
    sorted.push_back(node);
    inorder(node->right);
}

void findSubsets(int index, int sum) {
    if (sum == B && !subset.empty()) {
        subsetCount++;
        cout << "Subset: ";
        for (int i = 0; i < (int)subset.size(); i++)
            cout << subset[i]->id << "(" << subset[i]->cost << ") ";
        cout << endl;
    }
    for (int i = index; i < (int)sorted.size(); i++) {
        // pruning: this and all bigger nodes to the right exceed B
        if (sum + sorted[i]->cost > B) break;

        subset.push_back(sorted[i]);
        findSubsets(i + 1, sum + sorted[i]->cost);
        subset.pop_back();
    }
}

int main() {
    Node* root = NULL;
    int n;
    cout << "Enter number of services: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        int id, cost;
        cout << "Service " << i + 1 << " (id cost): ";
        cin >> id >> cost;
        root = insert(root, id, cost);
    }
    cout << "Enter target budget B: ";
    cin >> B;

    cout << "\nPart A - Downward paths with sum B:" << endl;
    startFromEveryNode(root);

    cout << "\nPart B - Subsets with sum B:" << endl;
    inorder(root);
    findSubsets(0, 0);
    if (subsetCount == 0) cout << "No subset found." << endl;
    return 0;
}
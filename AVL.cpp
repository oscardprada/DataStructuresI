#include <iostream>
using std::cin;
using std::cout;

const int mod = 1000000000;

struct Node {
    int key, height;
    Node *left, *right;

    Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

int getHeight(Node* node) {
    return node ? node->height : 0;
}

void updtHeight(Node* node) {
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int getBalance(Node* node) {
    return getHeight(node->left) - getHeight(node->right);
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    updtHeight(y);
    updtHeight(x);
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    updtHeight(x);
    updtHeight(y);
    return y;
}

Node* insert(Node* root, int key) {
    if (!root) return new Node(key);

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    } else {
        return root;
    }

    updtHeight(root);

    int balance = getBalance(root);
    if (balance > 1) {
        if (key < root->left->key)
            return rotateRight(root);
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1) {
        if (key > root->right->key)
            return rotateLeft(root);
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

int lowerBound(Node* root, int key) {
    int result = -1;
    while (root) {
        if (root->key >= key) {
            result = root->key;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return result;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    Node* root = nullptr;
    int lastAnswer = 0;
    bool lastOpWasQuery = false;

    while (n--) {
        char op;
        int x;
        cin >> op >> x;

        if (op == '+') {
            int value = lastOpWasQuery ? (x + lastAnswer) % mod : x;
            root = insert(root, value);
            lastOpWasQuery = false;
        } else if (op == '?') {
            lastAnswer = lowerBound(root, x);
            cout << lastAnswer << '\n';
            lastOpWasQuery = true;
        }
    }

    return 0;
}
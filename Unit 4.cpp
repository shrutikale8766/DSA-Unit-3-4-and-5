
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int orderID, height;
    Node *left, *right;

    Node(int id) {
        orderID = id;
        height = 1;
        left = right = nullptr;
    }
};

int height(Node* n) {
    return n ? n->height : 0;
}

int balanceFactor(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* t = x->right;

    x->right = y;
    y->left = t;

    y->height = 1 + max(height(y->left),
                        height(y->right));
    x->height = 1 + max(height(x->left),
                        height(x->right));

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* t = y->left;

    y->left = x;
    x->right = t;

    x->height = 1 + max(height(x->left),
                        height(x->right));
    y->height = 1 + max(height(y->left),
                        height(y->right));

    return y;
}

Node* insert(Node* root, int id) {
    if (root == nullptr)
        return new Node(id);

    if (id < root->orderID)
        root->left = insert(root->left, id);
    else if (id > root->orderID)
        root->right = insert(root->right, id);
    else {
        cout << "Duplicate Order ID!\n";
        return root;
    }

    root->height = 1 + max(height(root->left),
                           height(root->right));

    int bf = balanceFactor(root);

    // LL Case
    if (bf > 1 && id < root->left->orderID)
        return rightRotate(root);

    // RR Case
    if (bf < -1 && id > root->right->orderID)
        return leftRotate(root);

    // LR Case
    if (bf > 1 && id > root->left->orderID) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL Case
    if (bf < -1 && id < root->right->orderID) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void display(Node* root) {
    if (!root)
        return;

    display(root->left);

    cout << "Order ID: " << root->orderID
         << " | Height: " << root->height
         << " | Balance Factor: "
         << balanceFactor(root) << endl;

    display(root->right);
}

bool verifyAVL(Node* root) {
    if (!root)
        return true;

    int bf = balanceFactor(root);

    if (bf < -1 || bf > 1)
        return false;

    return verifyAVL(root->left) &&
           verifyAVL(root->right);
}

bool search(Node* root, int id) {
    if (!root)
        return false;

    if (root->orderID == id)
        return true;

    if (id < root->orderID)
        return search(root->left, id);

    return search(root->right, id);
}

void countOrders(Node* root, int &count) {
    if (!root)
        return;

    count++;
    countOrders(root->left, count);
    countOrders(root->right, count);
}

void showTotalOrders(Node* root) {
    int count = 0;
    countOrders(root, count);
    cout << "Total Orders: " << count << endl;
}

int main() {
    Node* root = nullptr;
    int choice, id;

    do {
        cout << "\n===== ORDER MANAGEMENT =====\n";
        cout << "1. Insert Order ID\n";
        cout << "2. Display Orders\n";
        cout << "3. Verify AVL Properties\n";
        cout << "4. Search Order ID\n";
        cout << "5. Count Total Orders\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Order ID: ";
            cin >> id;
            root = insert(root, id);
            break;

        case 2:
            if (root == nullptr)
                cout << "No orders available!\n";
            else
                display(root);
            break;

        case 3:
            if (verifyAVL(root))
                cout << "Tree satisfies AVL properties.\n";
            else
                cout << "Tree violates AVL properties.\n";
            break;

        case 4:
            cout << "Enter Order ID to search: ";
            cin >> id;

            if (search(root, id))
                cout << "Order ID found!\n";
            else
                cout << "Order ID not found!\n";
            break;

        case 5:
            showTotalOrders(root);
            break;

        case 6:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}
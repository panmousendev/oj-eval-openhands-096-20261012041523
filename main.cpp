#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Build tree from preorder traversal with -1 as null
TreeNode* buildTree(vector<int>& preorder, int& index) {
    if (index >= preorder.size() || preorder[index] == -1) {
        index++;
        return nullptr;
    }
    
    TreeNode* node = new TreeNode(preorder[index++]);
    node->left = buildTree(preorder, index);
    node->right = buildTree(preorder, index);
    return node;
}

// Find depth and parent of a node
bool findNode(TreeNode* root, int target, int depth, int& nodeDepth, int& parentNode) {
    if (!root) return false;
    
    if ((root->left && root->left->val == target) || 
        (root->right && root->right->val == target)) {
        nodeDepth = depth + 1;
        parentNode = root->val;
        return true;
    }
    
    // Search in left subtree
    if (root->left && findNode(root->left, target, depth + 1, nodeDepth, parentNode)) {
        return true;
    }
    
    // Search in right subtree
    return root->right && findNode(root->right, target, depth + 1, nodeDepth, parentNode);
}

// Check if two nodes are cousins
bool areCousins(TreeNode* root, int x, int y) {
    if (x == y) return false;
    
    int depthX = -1, depthY = -1;
    int parentX = -1, parentY = -1;
    
    findNode(root, x, 0, depthX, parentX);
    findNode(root, y, 0, depthY, parentY);
    
    // Nodes are cousins if they have same depth but different parents
    return (depthX == depthY) && (parentX != parentY);
}

// Clean up memory
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    int q;
    cin >> q;
    
    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].first >> queries[i].second;
    }
    
    // Read the preorder traversal
    string line;
    cin.ignore(); // Ignore newline after last query
    getline(cin, line);
    
    stringstream ss(line);
    vector<int> preorder;
    int val;
    while (ss >> val) {
        preorder.push_back(val);
    }
    
    // Build the tree
    int index = 0;
    TreeNode* root = buildTree(preorder, index);
    
    // Process queries
    for (int i = 0; i < q; i++) {
        int x = queries[i].first;
        int y = queries[i].second;
        cout << (areCousins(root, x, y) ? 1 : 0) << endl;
    }
    
    // Clean up
    deleteTree(root);
    
    return 0;
}
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char character, int frequency) {
        ch = character;
        freq = frequency;
        left = right = nullptr;
    }
};

// Comparator for Min-Heap Priority Queue
struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// Traverse tree to generate codes and calculate Weighted Path Length (WPL)
void generateCodes(Node* root, string code, unordered_map<char, string>& huffmanCodes, int depth, int& totalWPL) {
    if (!root) return;

    // Leaf node check
    if (!root->left && !root->right) {
        huffmanCodes[root->ch] = code;
        totalWPL += (root->freq * depth);
        return;
    }

    generateCodes(root->left, code + "0", huffmanCodes, depth + 1, totalWPL);
    generateCodes(root->right, code + "1", huffmanCodes, depth + 1, totalWPL);
}

void buildHuffmanTree(const vector<char>& chars, const vector<int>& freqs) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    // Create leaf nodes and insert into min heap
    for (size_t i = 0; i < chars.size(); ++i) {
        minHeap.push(new Node(chars[i], freqs[i]));
    }

    // Build Huffman Tree
    while (minHeap.size() > 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();

        // '$' is placeholder for internal nodes
        Node* parent = new Node('$', left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        minHeap.push(parent);
    }

    Node* root = minHeap.top();

    unordered_map<char, string> huffmanCodes;
    int totalWPL = 0;

    generateCodes(root, "", huffmanCodes, 0, totalWPL);

    cout << "=== Huffman Codes ===" << endl;
    cout << "Char\tFreq\tCode" << endl;
    cout << "--------------------" << endl;
    for (size_t i = 0; i < chars.size(); ++i) {
        cout << chars[i] << "\t" << freqs[i] << "\t" << huffmanCodes[chars[i]] << endl;
    }

    cout << "\nWeighted Path Length (WPL): " << totalWPL << " bits" << endl;
}

int main() {
    vector<char> chars = {'A', 'B', 'C', 'D', 'E', 'F'};
    vector<int> freqs = {45, 13, 12, 16, 9, 5};

    buildHuffmanTree(chars, freqs);

    return 0;
}

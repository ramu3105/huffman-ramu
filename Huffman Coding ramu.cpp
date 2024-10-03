#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// A Tree Node for the Huffman Tree
struct MinHeapNode {
    char data; // Character
    int freq;  // Frequency of the character
    MinHeapNode *left, *right; // Left and right children

    // Constructor
    MinHeapNode(char data, int freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

// Compare class to order the priority queue (min-heap)
struct compare {
    bool operator()(MinHeapNode* left, MinHeapNode* right) {
        return (left->freq > right->freq);
    }
};

// Function to print Huffman codes using preorder traversal of the Huffman Tree
void printCodes(MinHeapNode* root, string code) {
    if (!root)
        return;

    // If it's a leaf node, print the character and its code
    if (root->data != '$')
        cout << root->data << ": " << code << endl;

    // Recursively go to the left and right subtree
    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

// Function to build the Huffman Tree and print codes
void HuffmanCodes(char data[], int freq[], int size) {
    MinHeapNode *left, *right, *top;

    // Create a priority queue (min-heap) to store nodes of the Huffman Tree
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

    // Create a leaf node for each character and add it to the priority queue
    for (int i = 0; i < size; ++i)
        minHeap.push(new MinHeapNode(data[i], freq[i]));

    // Iterate while the size of the queue becomes 1
    while (minHeap.size() != 1) {
        // Extract the two nodes with the smallest frequency
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with a frequency equal to the sum of the two nodes' frequencies
        top = new MinHeapNode('$', left->freq + right->freq);

        // Set the extracted nodes as children of this new node
        top->left = left;
        top->right = right;

        // Add this node to the priority queue
        minHeap.push(top);
    }

    // Print the Huffman codes by traversing the tree in preorder
    printCodes(minHeap.top(), "");
}

// Driver program to test above functions
int main() {
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };

    int size = sizeof(arr) / sizeof(arr[0]);

    // Build Huffman Tree and print codes
    HuffmanCodes(arr, freq, size);

    return 0;
}

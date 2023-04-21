#include <iostream>
using namespace std;
struct Node
{
    int value;
    Node* next;
};

Node* makeNodeList(int totalNodes)
{
    Node* startNode;
    Node* newNode;
    Node* bufferNode;

    startNode = new Node;
    // Get start node value
    int startNodeValue;
    cin >> startNodeValue;
    startNode->value = startNodeValue;
    startNode->next = NULL;

    bufferNode = startNode;
    for (int nodeCnt = 2; nodeCnt <= totalNodes; nodeCnt++)
    {
        newNode = new Node;
        // Assign new node value
        int newNodeValue;
        cin >> newNodeValue;
        newNode->value = newNodeValue;
        newNode->next = NULL;
        bufferNode->next = newNode;
        bufferNode = newNode;
    }
    return startNode;
}

int main() {
    int nodeCnt;
    cin >> nodeCnt;
    Node* headNode = makeNodeList(nodeCnt);
    Node* currentNode = headNode;
    for (int i = 0; i < nodeCnt; i++)
    {
        cout << currentNode->value << " ";
        currentNode = currentNode->next;
    }
    return 0;
}
#include <iostream>
using namespace std;
struct Node 
{
    int value;
    Node* next;
};

Node* createNodeList(int totalNodeCnt)
{
    struct Node* newNode;
    struct Node* nodeBuffer;
    // Create the starting node
    struct Node* startingNode = new Node;
    // Get the starting node value
    int startingNodeValue;
    cin >> startingNodeValue;
    startingNode->value = startingNodeValue;
    startingNode->next = NULL;
    nodeBuffer = startingNode;

    for (int nodeCnt = 2; nodeCnt <= totalNodeCnt; nodeCnt++)
    {
        newNode = new Node;
        // Get new node value;
        int newNodeValue;
        cin >> newNodeValue;
        newNode->value = newNodeValue;
        newNode->next = NULL;
        nodeBuffer->next = newNode;
        nodeBuffer = nodeBuffer->next;
    }    
    return startingNode;
}

Node* swapAfter(Node* head, int x)
{
    Node* startingNode = head; // For returning
    Node* currentNode = startingNode;
    Node* nextNode;
    while (currentNode->next != NULL) 
    {
        if (currentNode->value == x)
        {
            nextNode = currentNode->next;   
            int temp = currentNode->value;
            currentNode->value = nextNode->value;
            nextNode->value = temp;
            currentNode = currentNode->next;
        }
        if (currentNode->next != NULL)
        {
            currentNode = currentNode->next;
        }
    } 
    return startingNode;
}

struct LinkedList {
    Node *head, *tail;
    void sortedInsert(int value)
    {

    }
};



int main() {
    int node_cnt;
    cin >> node_cnt;
    Node* headNode = createNodeList(node_cnt);
    int x;
    cin >> x;
    headNode = swapAfter(headNode, x);
    while (headNode != NULL)
    {
        cout << headNode->value << " ";
        headNode = headNode->next;
    }
    return 0;
}
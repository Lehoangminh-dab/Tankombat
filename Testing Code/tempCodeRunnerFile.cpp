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
        currentNode = currentNode->next;
    } 
    return startingNode;
}
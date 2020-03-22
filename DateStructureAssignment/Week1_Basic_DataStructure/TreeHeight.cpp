#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif
//Input 1. Number of nodes n
//      2. Node List : 0 ... n
//         Parent is   ...(-1 is the root) ...
//Output is the height of tree
class Node;

class Node
{
public:
    int key;
    Node *parent;
    std::vector<Node *> children;//Children are pointers (pointing at Nodes)

    Node()
    {
        this->parent = NULL;
    }

    void setParent(Node *theParent)
    {
        parent = theParent;
        parent->children.push_back(this);//the parent pointer should be the parent of children pointer.
    }
};


int main_with_large_stack_space()
{
    std::ios_base::sync_with_stdio(0);
    int n;
    std::cin >> n;//First input: number of nodes.

    std::vector<Node> nodes;
    nodes.resize(n);
    //Construct the tree
    for (int child_index = 0; child_index < n; child_index++)
    {
        int parent_index;
        std::cin >> parent_index;//Second input: Parent Index
        if (parent_index >= 0)// -1 means root while positive number corresponding to parent
            nodes[child_index].setParent(&nodes[parent_index]);
        nodes[child_index].key = child_index;
    }

    // Replace this code with a faster implementation
    int maxHeight = 0;
    int root = -1;
    std::queue<Node> q_node;
    for (int leaf_index = 0; leaf_index < n; leaf_index++)
    {
        if(nodes[leaf_index].parent == NULL)
        {
            root = leaf_index;// It is the ROOT.
            break;
        }
    }
    if(root != -1)
    {
        q_node.push(nodes[root]);
        maxHeight += 1;
    }
    else
    {
        std::cout << "There is no root in the tree." << std::endl;
        return 0;
    }
    Node curr_node;
    while(!q_node.empty())
    {
        curr_node = q_node.front();
        q_node.pop();
        if(!curr_node.children.empty())
        {
            maxHeight += 1;
            //Add children into the queue.
            for (int i=0; i < curr_node.children.size(); i++)
            {
                q_node.push(*curr_node.children[i]);
            }
        }
    }


    std::cout << maxHeight << std::endl;
    return 0;
}

int main (int argc, char **argv)
{
    return main_with_large_stack_space();
}

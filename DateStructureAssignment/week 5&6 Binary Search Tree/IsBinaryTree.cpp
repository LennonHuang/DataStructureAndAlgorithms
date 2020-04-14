/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node
{
    int key;
    int left;
    int right;

    Node() : key(0), left(-1), right(-1) {}
    Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};
bool IsBinarySearchTreeRecursive(const vector<Node>& tree,int root,const int* min_for_left,const int* max_for_right)
{
    if (root == -1)
    {
        return true;
    }
    if (tree[root].left != -1)
    {
        if((tree[tree[root].left].key > tree[root].key)
            || (tree[tree[root].left].key < *min_for_left))
        {
            return false;
        }
    }
    if(tree[root].right != -1)
    {
        if((tree[tree[root].right].key > *max_for_right) || (tree[tree[root].right].key < tree[root].key))
    {
        return false;
    }
}
return (IsBinarySearchTreeRecursive(tree,tree[root].left, min_for_left, &tree[root].key)
           && IsBinarySearchTreeRecursive(tree,tree[root].right, &tree[root].key, max_for_right));
}

bool IsBinarySearchTree(const vector<Node>& tree)
{
    // Implement correct algorithm here
    const int INT_MIN = std::numeric_limits<int>::min();
    const int INT_MAX = std::numeric_limits<int>::max();
    const int* ini_left_min = &INT_MIN;
    const int* ini_right_max = &INT_MAX;
    if(tree.size() == 0){
        return true;
    }
    return IsBinarySearchTreeRecursive(tree,0,ini_left_min,ini_right_max);//Assume index 0 is the root
}
int main()
{
    int nodes;
    cin >> nodes;
    vector<Node> tree;
    for (int i = 0; i < nodes; ++i)
    {
        int key, left, right;
        cin >> key >> left >> right;
        tree.push_back(Node(key, left, right));
    }
    if (IsBinarySearchTree(tree))
{
    cout << "CORRECT" << endl;
}
else
{
    cout << "INCORRECT" << endl;
}
return 0;
}



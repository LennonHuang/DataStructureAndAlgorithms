#include <cstdio>
#include <iostream>
// Splay tree implementation

// Vertex of a splay tree
struct Vertex
{
    int key;
    // Sum of all the keys in the subtree - remember to update
    // it after each operation that changes the tree.
    long long sum;//sum of its left and right sub-tree and its key.
    Vertex* left;
    Vertex* right;
    Vertex* parent;

    Vertex(int key, long long sum, Vertex* left, Vertex* right, Vertex* parent)
        : key(key), sum(sum), left(left), right(right), parent(parent) {}
};

void update(Vertex* v)  //when left/right node changed, the sum needed to be changed.
{
    if (v == NULL)
        return;
    v->sum = v->key + (v->left != NULL ? v->left->sum : 0ll) + (v->right != NULL ? v->right->sum : 0ll);
    if (v->left != NULL)
    {
        v->left->parent = v;
    }
    if (v->right != NULL)
    {
        v->right->parent = v;
    }
}

void small_rotation(Vertex* v)
{
    Vertex* parent = v->parent;
    if (parent == NULL)
    {
        return;
    }
    Vertex* grandparent = v->parent->parent;
    if (parent->left == v)
    {
        Vertex* m = v->right;
        v->right = parent;
        parent->left = m;
    }
    else
    {
        Vertex* m = v->left;
        v->left = parent;
        parent->right = m;
    }
    update(parent);
    update(v);
    v->parent = grandparent;
    if (grandparent != NULL)
    {
        if (grandparent->left == parent)
        {
            grandparent->left = v;
        }
        else
        {
            grandparent->right = v;
        }
    }
}

void big_rotation(Vertex* v)
{
    if (v->parent->left == v && v->parent->parent->left == v->parent)
    {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    }
    else if (v->parent->right == v && v->parent->parent->right == v->parent)
    {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    }
    else
    {
        // Zig-zag
        small_rotation(v);
        small_rotation(v);
    }
}

// Makes splay of the given vertex and makes
// it the new root.
void splay(Vertex*& root, Vertex* v)
{
    if (v == NULL)
        return;
    while (v->parent != NULL)
    {
        if (v->parent->parent == NULL)
        {
            small_rotation(v);
            break;
        }
        big_rotation(v);
    }
    root = v;
}

// Searches for the given key in the tree with the given root
// and calls splay for the deepest visited node after that.
// If found, returns a pointer to the node with the given key.
// Otherwise, returns a pointer to the node with the smallest
// bigger key (next value in the order).
// If the key is bigger than all keys in the tree,
// returns NULL.
Vertex* find(Vertex*& root, int key)
{
    Vertex* v = root;
    Vertex* last = root;
    Vertex* next = NULL;
    while (v != NULL)
    {
        if (v->key >= key && (next == NULL || v->key < next->key))  //
        {
            next = v;//smallest bigger --> next pointer
        }
        last = v;
        if (v->key == key)  //find the pos
        {
            break;
        }
        if (v->key < key)
        {
            v = v->right;
        }
        else
        {
            v = v->left;
        }
    }
    splay(root, last);//splay the found node
    return next;
}

void split(Vertex* root, int key, Vertex*& left, Vertex*& right)
{
    right = find(root, key);
    splay(root, right);
    if (right == NULL)
    {
        left = root;
        return;
    }
    left = right->left;
    right->left = NULL;
    if (left != NULL)
    {
        left->parent = NULL;
    }
    update(left);
    update(right);
}

Vertex* merge(Vertex* left, Vertex* right)
{
    if (left == NULL)
        return right;
    if (right == NULL)
        return left;
    Vertex* min_right = right;//smallest at right sub-tree
    while (min_right->left != NULL)
    {
        min_right = min_right->left;
    }
    splay(right, min_right);
    right->left = left;
    update(right);
    return right;
}

// Code that uses splay tree to solve the problem

Vertex* root = NULL;

void insert(int x)
{
    Vertex* left = NULL;
    Vertex* right = NULL;
    Vertex* new_vertex = NULL;
    split(root, x, left, right);
    if (right == NULL || right->key != x)  //x does not exist
    {
        new_vertex = new Vertex(x, x, NULL, NULL, NULL);
    }
    root = merge(merge(left, new_vertex), right);
}

void erase(int x)
{
    // Implement erase yourself
    Vertex* left = NULL;
    Vertex* right = NULL;
    Vertex* middle = NULL;
    split(root,x,left,right);//right tree >= x, need to eliminate x from right
    split(right,x+1,middle,right);//Now right tree >=x+1 >x
    root = merge(left,right);
}

bool find(int x)
{
    // Implement find yourself
    if(find(root,x) != nullptr)
    {
        if(x == find(root,x)->key)
        {
            return true;//found x
        }
    }
    return false;
}

long long sum(int from, int to)
{
    Vertex* left = NULL;
    Vertex* middle = NULL;
    Vertex* right = NULL;
    split(root, from, left, middle);//middle >= from
    split(middle, to + 1, middle, right);// now middle <=t
    long long ans = 0;
    // Complete the implementation of sum
    if(middle != NULL)
    {
        ans = middle->sum;//sum is calculated during update in split
        root = merge(merge(left,middle),right);//Get back the tree
    }
    else
    {
        ans = 0;
        root = merge(left,right);
    }

    return ans;
}

const int MODULO = 1000000001;

int main()
{
    int n;
    scanf("%d", &n);
    int last_sum_result = 0;
    for (int i = 0; i < n; i++)
    {
        char buffer[10];
        scanf("%s", buffer);
        char type = buffer[0];
        switch (type)
        {
        case '+' :
        {
            int x;
            scanf("%d", &x);
            insert((x + last_sum_result) % MODULO);
        }
        break;
        case '-' :
        {
            int x;
            scanf("%d", &x);
            erase((x + last_sum_result) % MODULO);
        }
        break;
        case '?' :
        {
            int x;
            scanf("%d", &x);
            int q = (x + last_sum_result) % MODULO ;
            printf( (find(q)) ? "Found\n" : "Not found\n");
        }
        break;
        case 's' :
        {
            int l, r;
            scanf("%d %d", &l, &r);
            long long res = sum((l + last_sum_result) % MODULO, (r + last_sum_result) % MODULO);
            printf("%lld\n", res);
            last_sum_result = int(res % MODULO);
        }
        }
    }
    return 0;
}

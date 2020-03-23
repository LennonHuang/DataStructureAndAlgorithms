#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct DisjointSetsElement
{
    int size, parent, rank;

    DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
        size(size), parent(parent), rank(rank) {}
};

struct DisjointSets
{
    int size;
    int max_table_size;
    vector <DisjointSetsElement> sets;

    DisjointSets(int size): size(size), max_table_size(0), sets(size)
    {
        for (int i = 0; i < size; i++)
            sets[i].parent = i;//Parent itself
    }

    int getParent(int table)
    {
        // find parent and compress path
        vector<int> table_list_same_parent;//Record list of table nodes that has the same parent for compressing path
        //Find parent
        int parent = table;
        while(parent != sets[parent].parent) //when it is not the root
        {
            parent = sets[parent].parent;
            table_list_same_parent.push_back(parent);//Put into the list
        }
        //cout << "The parent is: " << parent << std::endl;
        //Compress Path
        for (int i = 0; i < table_list_same_parent.size(); ++i)
        {
            sets[table_list_same_parent[i]].parent = parent;
        }
        return parent;
    }

    void merge(int destination, int source)
    {
        int realDestination = getParent(destination);
        int realSource = getParent(source);
        if (realDestination != realSource)
        {
            // merge two components
            // use union by rank heuristic
            //Rank heuristic
            /*if(sets[realDestination].rank > sets[realSource].rank){
                sets[realSource].parent = sets[realDestination].parent;
                sets[realDestination].size += sets[realSource].size;
                sets[realSource].size = 0;

                max_table_size = max(max_table_size,sets[realDestination].size);// update max_table_size
            }
            else{
                sets[realDestination].parent = sets[realSource].parent;
                sets[realSource].size += sets[realDestination].size;
                sets[realDestination].size = 0;

                max_table_size = max(max_table_size,sets[realSource].size);
                if(sets[realDestination].rank == sets[realSource].rank){
                    sets[realSource].rank += 1;//Same rank, Parent tree rank +1
                }
            }*/
            //Not rank heuristic but according to command --- source linked to desitination
            sets[realSource].parent = sets[realDestination].parent;
            sets[realDestination].size += sets[realSource].size;
            sets[realSource].size = 0;

            max_table_size = max(max_table_size,sets[realDestination].size);// update max_table_size
            cout << "The parent of " << source + 1 << " is " << getParent(source) +1<< std::endl;
        }
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    DisjointSets tables(n);
    for (auto &table : tables.sets)
    {
        cin >> table.size;
        tables.max_table_size = max(tables.max_table_size, table.size);
    }

    for (int i = 0; i < m; i++)
    {
        int destination, source;
        cin >> destination >> source;
        --destination;
        --source;

        tables.merge(destination, source);
        cout << "The maximum of row is: " << tables.max_table_size << endl;
    }

    return 0;
}

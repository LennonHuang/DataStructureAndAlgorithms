#include <iostream>
#include <vector>
#include <deque>

using std::cin;
using std::cout;
using std::vector;
using std::max;

void max_sliding_window(vector<int> const & A, int w)
{
    int window_max = 0;
    std::deque<int> dq;//deque for record useful index. Useful index means index of candidates for being maximum.
    //Construc the first window
    for (int j = 0; j < w; ++j)
    {
        while(!dq.size() == 0 && A.at(j) >= A.at(dq.back()))
        {
            dq.pop_back();//pop useless index
        }
        dq.push_back(j);
        window_max = A.at(dq.front());
    }
    cout << window_max << " ";
    /*for(int i = 0; i<dq.size(); ++i)
    {
        std::cout << A.at(dq[i]) << " ";
    }
    std::cout << " " << std::endl;*/
    //Go throu each window
    for (size_t i = 1; i < A.size() - w + 1; ++i)
    {
        while(i > dq.front())
        {
            dq.pop_front();// index is not within the window
        }
        while(!dq.size() == 0 && A.at(i+w-1) >= A.at(dq.back()))//Comparing new coming from the right with the elements from deque index
        {
            dq.pop_back();//pop useless index
        }
        dq.push_back(i+w-1);
        window_max = A.at(dq.front());

        cout << window_max << " ";
    }

    return;
}



int main()
{
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window(A, w);

    return 0;
}

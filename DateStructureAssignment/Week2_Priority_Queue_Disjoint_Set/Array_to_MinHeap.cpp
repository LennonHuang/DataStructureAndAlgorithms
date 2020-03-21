#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;
using std::max;

class HeapBuilder {
private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << "Swap times: "<<swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
    //for(int i = 0; i < n; ++i)
        //cout << data_[i] << std::endl;
  }
  void PrintData(){
    for(int i = 0; i < data_.size(); ++i)
        cout << data_[i] << " ";

  }

    //Heapify the a tree. And if there is a swap (subtree got affected), heapify its subtree.
    void heapify(vector<int> arr, int n, int root)
    {
        int smallest_idx = root;
        int r_idx = root*2 +2;
        int l_idx = root*2 +1;

        if(r_idx < n && data_[r_idx] <data_[root])
        {
            smallest_idx = r_idx;
        }
        if(l_idx < n && data_[l_idx] <data_[smallest_idx])
        {
            smallest_idx = l_idx;
        }

        if(smallest_idx != root){//there is a swap
            swap(data_[smallest_idx], data_[root]);
        cout << smallest_idx << std::endl;
        swaps_.push_back(make_pair(smallest_idx, root));
        if(smallest_idx*2+1 < n )
        {
            heapify(arr,n,smallest_idx);//Heapify its subtree
        }
        }
    }

  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap,
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    for(int i = data_.size()/2 -1; i >= 0;--i ){
        heapify(data_,data_.size(),i);
    }
  }
public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
    PrintData();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}

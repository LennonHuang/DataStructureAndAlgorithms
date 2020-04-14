#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

using std::vector;
using std::cin;
using std::cout;

typedef std::pair<long long, int> worker;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " "<< start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    //Use a prioty queue pair<release time, worker index>. Then when the next job comes, we can simply find the top element from
    //this priority queue (the one that is released first).
    std::priority_queue<worker, std::vector<worker>, std::greater<worker> > next_free_time;// std::great<type> from <functional> gives us min_heap
    for(int i = 0; i < num_workers_; ++i){
        next_free_time.push(std::make_pair(0,i));
    }

    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_worker = 0;
      next_worker = next_free_time.top().second;//The earliest worker that is available

      assigned_workers_[i] = next_worker;
      start_times_[i] = next_free_time.top().first;//Record the assignement
      //cout << "The duration of this job is:" << duration << std::endl;
      //cout << "Next worker Id: " << next_worker << " AND starting time is: " << next_free_time.top().first << std::endl;
      next_free_time.pop();//Since prority queue cannot be modified. We first pop and then UPDATE the release time of the worker (push).
      next_free_time.push(std::make_pair(start_times_[i] + duration,next_worker));//Update the release time of the assigned worker
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}

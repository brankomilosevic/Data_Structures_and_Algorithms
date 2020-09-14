#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

/*
Problem Description
Task. You have a program which is parallelized and uses 𝑛 independent threads to process the given list of 𝑚
jobs. Threads take jobs in the order they are given in the input. If there is a free thread, it immediately
takes the next job from the list. If a thread has started processing a job, it doesn’t interrupt or stop
until it finishes processing the job. If several threads try to take jobs from the list simultaneously, the
thread with smaller index takes the job. For each job you know exactly how long will it take any thread
to process this job, and this time is the same for all the threads. You need to determine for each job
which thread will process it and when will it start processing.
Input Format. The first line of the input contains integers 𝑛 and 𝑚.
The second line contains 𝑚 integers 𝑡𝑖 — the times in seconds it takes any thread to process 𝑖-th job.
The times are given in the same order as they are in the list from which threads take jobs.
Threads are indexed starting from 0.
Constraints. 1 ≤ 𝑛 ≤ 105; 1 ≤ 𝑚 ≤ 105; 0 ≤ 𝑡𝑖 ≤ 109.
Output Format. Output exactly 𝑚 lines. 𝑖-th line (0-based index is used) should contain two spaceseparated
integers — the 0-based index of the thread which will process the 𝑖-th job and the time
in seconds when it will start processing that job.
*/

// Branko Milosevic 2020-09-07
// Coursera Data Structures wk03-02

using std::vector;
using std::cin;
using std::cout;
using std::priority_queue;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  struct thread
  {
    int id;
    long long next_free_time;

    thread(int id, long long t = 0) : id(id), next_free_time(t){};

    void addtime(long long t)
    {
        next_free_time += t;
    }

    friend bool operator<(const thread &b, const thread &a)
    {
      if (b.next_free_time != a.next_free_time)
        return b.next_free_time > a.next_free_time;
      else
        return b.id > a.id;
    }
  };

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
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
/*
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_worker = 0;
      for (int j = 0; j < num_workers_; ++j) {
        if (next_free_time[j] < next_free_time[next_worker])
          next_worker = j;
      }
      assigned_workers_[i] = next_worker;
      start_times_[i] = next_free_time[next_worker];
      next_free_time[next_worker] += duration;
    }
*/

    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());

    priority_queue<thread, vector<thread>> q;

    for (int i = 0; i < num_workers_; i++)
      q.push(thread(i));

    for (int i = 0; i < jobs_.size(); ++i)
    {
      int duration = jobs_[i];
      thread td = q.top();
      q.pop();
      assigned_workers_[i] = td.id;
      start_times_[i] = td.next_free_time;
      td.next_free_time += duration;
      q.push(td);
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

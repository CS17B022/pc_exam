// pthread (POSIX)
/*
 * CS5105: Parallel Computing
 * Compute array sum (data size is a multiple of number of threads)
 * To compile: g++ -std=c++11 -pthread thread.cc
 */

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>

using namespace std::chrono;


const int nthreads = 1024;
const int64_t ndata = 1600000;
std::mutex mtx;

int total_sum = 0;
int sum[nthreads] = { 0 };

void compute_sum(int tid, std::vector<int>& d)
{
  int st = (ndata / nthreads) * tid;
  int en = (ndata / nthreads) * (tid + 1);
  // the above local_sum is "shared" by all threads

  // you are calculating and dividing up the work 
  // suppose ndata is not a multiple of nthreads
  // st and en calculation is not straightforward
  //
  // all threads are executing (might) in parallel this below for loop
  // BUT they are reading different data elements d[]
  // why? because variable st, and en are different for different threads
  for (int i = st; i < en; i++) {

    // using the below statement, I am computing the sum locally
    // which means that all threads are locally updating the sum
    // NO need for lock in this case
    // sum[0], sum[1], .....
    //sum[tid] += d[i];

    
    sum[tid] += d[i];
    
    // when I do a lock if thread 0 enters line 44, there is no way that thread 1 can enter line 51!
    // total_sum is shared among the threads
    //
    // t0: read d[0] and computed total_sum
    // what do i mean by this?
    // 
    
    // thread 0
    // load d[0]
    // load total_sum (0)
    // add d[0] + total_sum
    // store result in total_sum
    // total_sum (1) <- time = 8
    
    // thread 1
    // load d[100]
    // load total_sum (0) [" The store from thread 0 has not happened! "]
    // add d[100] + total_sum
    // store result in total_sum
    // total_sum (99) <- time = 7
    //
    // so what happened in time = 7 is lost! which means the value of d[100] is not computed into total_sum
  }
}

int main(int argc, char ** arg)
{
  std::vector<std::thread> threads;
  
  std::vector<int> data; // it is shared among threads
  for (int i = 0; i < ndata; i++) {
    data.push_back(i);
  }

  auto start = high_resolution_clock::now();
  for (int i = 0; i < nthreads; i++) {
    threads.push_back(std::thread(compute_sum, i, std::ref(data)));
  }
  
  for (auto &th : threads) {
    th.join();
  }

  // there is only one thread because I have joined
  int tsum = 0;
  for (int i = 0; i < nthreads; i++) {
    tsum += sum[i];
    // compute total sum using local sums
  }
  auto stop = high_resolution_clock::now();

  //std::cout << "Array sum is: " << tsum << std::endl;
  //std::cout << "Array sum is: " << total_sum << std::endl;
  auto duration = duration_cast<microseconds>(stop - start);
  std::cout << duration.count() << std::endl;

  return 0;
}



/*

func (std::vector<int> & x) 
{
  // blash blah on x
  x[3] = 9;
}


f (int & y)
{
  y = 8;
}
main()
{
  std::vector<int> y(100);
  // initialize y
  y[3] = 8;
  func(y.data());
  // print y[3]
  //
  x = 10;
  f(x);

}
*/

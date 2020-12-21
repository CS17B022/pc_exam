// pthread (POSIX)
/*
 * CS5105: Parallel Computing
 * Compute array sum (data size is a multiple of number of threads)
 * To compile: g++ -std=c++11 -pthread thread.cc
 */

#include <iostream>
#include <thread>
#include <vector>

const int nthreads = 4;
const int ndata = 8;

int sum[nthreads] = { 0 };

void compute_sum(int tid, std::vector<int>& d)
{
  int st = (ndata / nthreads) * tid;
  int en = (ndata / nthreads) * (tid + 1);

  for (int i = st; i < en; i++) {
    sum[tid] += d[i];
  }
}

int main(int argc, char ** arg)
{
  std::vector<std::thread> threads;
  
  std::vector<int> data;
  for (int i = 0; i < ndata; i++) {
    data.push_back(i);
  }

  for (int i = 0; i < nthreads; i++) {
    threads.push_back(std::thread(compute_sum, i, std::ref(data)));
  }
  
  for (auto &th : threads) {
    th.join();
  }

  int tsum = 0;
  for (int i = 0; i < nthreads; i++) {
    tsum += sum[i];
  }

  std::cout << "Array sum is: " << tsum << std::endl;

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

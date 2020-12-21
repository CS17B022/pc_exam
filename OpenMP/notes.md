* Using lock the performance of the parallel code is bad. In our experiment, it is 17X slower when compared to using local sum.

* In the code that uses lock, we reduce the number of threads.
  * What happens?
  * If we reduce the number of threads, performance increases!!!, and it is best if I don't have any parallelism!
  * Locks are bad!! -- it does not mean that you should not use locks

* In the code that does not use lock, we reduce the number of threads.
  * 

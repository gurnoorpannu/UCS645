## Inference

In this problem, two different approaches were used to compute the sum of the first N natural numbers using CUDA threads. The iterative method computes the sum using a loop, which takes linear time, whereas the formula-based method computes the result in constant time. Both methods produced the same output, verifying correctness. This demonstrates that while parallel execution is possible, algorithmic efficiency (O(N) vs O(1)) plays a crucial role in performance.

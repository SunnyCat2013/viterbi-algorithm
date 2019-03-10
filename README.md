Demo for learning viterbi algorithm

# usage

``` shell
$ cmake . && make && ./viterbi

-- Configuring done
-- Generating done
-- Build files have been written to: /Users/didi/CLionProjects/viterbi
[100%] Built target viterbi
T: 3
output should be:
0.1 0.16    0.28
init delta[0][i]
0.1 0.16    0.28

Time: 1 delta: 0.028    Choose box: 2
Time: 1 delta: 0.0504   Choose box: 2
Time: 1 delta: 0.042    Choose box: 2

Time: 2 delta: 0.00756  Choose box: 1
Time: 2 delta: 0.01008  Choose box: 1
Time: 2 delta: 0.0147   Choose box: 2

The best path: begin -> 2 -> 2 -> 2 -> end
```

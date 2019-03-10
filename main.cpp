#include <iostream>
#include <string>
#include <list>
using namespace std;
int main(){
    // 本例来自《统计学习方法》P186，例 10.3。可参考 P173 例 10.1 理解本题
    // 有三个状态（比如，有三个装球的盒子）
    double pi[3] = { 0.2, 0.4, 0.4 }; // 初始概率分布（每个盒子被选中的概率）
    int q = 0;
    for (auto _: pi) q++;

    double A[3][3] = { 0.5, 0.2, 0.3, 0.3, 0.5, 0.2, 0.2, 0.3, 0.5 }; // 转移概率（A[i][j] 表示从状态 i 到状态 j 转移的概率）
    double B[3][2] = { 0.5, 0.5, 0.4, 0.6, 0.7, 0.3 }; // 观测概率分布（每个盒子中，白球、红球被选中的概率）

//    int output[] = { 0, 1, 0 , 1}; // 观测序列：红、白、红、白
    int output[] = { 0, 1, 0}; // 观测序列：红、白、红
    int T = 0;

    // 获取观测序列长度
    for (auto o: output) T++;
    cout << "T: " << T << endl;

    double **delta = new double *[T]; // 状态表，delta[i][j] 表示时间 i 时，到达状态 j 的最大概率值。
    for (int i; i < T; i++) {
        delta[i] = new double[q];
    }
    int psi[T][q];


    // 初始化时间为 1 时的 delta 值
    int color = output[0];
    cout << "output should be: \n" << "0.1\t0.16\t0.28" << endl;
    cout << "init delta[0][i]" << endl;
    for (int i = 0; i < q; i ++) {
        delta[0][i] = pi[i] * B[i][color];
        cout << delta[0][i] << "\t";
    }
    cout << endl;
    cout << endl;

    for (int i = 1; i < T; i++) { // 遍历剩余 T - 1 个时间状态
        color = output[i];
        for (int j = 0; j < q; j++) { // 处理每个时间点中，每个状态的情况
            double i_j_pro[q]; // 时间为 i，状态为 j 的结点，从时间为 i - 1 的 q 个状态到达当前位置的概率
            for (int k = 0; k < q; k++) {
//                i_j_pro[k] = delta[i - 1][k] * A[k][j];
                i_j_pro[k] = delta[i - 1][k] * A[k][j] * B[j][color]; // 不要忘记 B（选择当前状态的哪个颜色的概率）
            }

            // 获得 i_j_pro 的最大值和最大值下标
            int idx = 0;
            double imax = i_j_pro[idx];
            for (int k = 1; k < q; k++) {
                if (i_j_pro[k] > imax) {
                    imax = i_j_pro[k];
                    idx = k;
                }
            }

            delta[i][j] = imax;
            psi[i][j] = idx;
            cout << "Time: " << i << "\t" << "delta: " << delta[i][j] << "\t" << "Choose box: " << psi[i][j] << endl;

        }
        cout << endl;
    }

    // 反向 decode
    //// 最后一个输出是 j = argmax(delta[i][j])
    int path[T];
    int i = T - 1;
    int idx = 0;
    double imax = delta[i][idx];
    for (int k = 1; k < q; k++) {
        if (delta[i][k] > imax) {
            imax = delta[i][k];
            idx = k;
        }
    }
    path[i] = idx;

    // 再往前的输出，保存在 psi[i + 1][下一个最优状态处]
    for (int i = T - 2; i >= 0; i--) {
        path[i] = psi[i + 1][path[i + 1]];
    }

    // 输出最优路径，如果 output 是 {0, 1, 0} 的话，输出应该是：The best path: begin -> 2 -> 2 -> 2 -> end
    cout << "The best path: begin -> ";
    for (auto p: path) {
        cout << p << " -> ";
    }
    cout << "end" << endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <cstdlib>
#include <queue>
#include <set>
#include <map>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <iomanip>
#include <chrono>
#include <bitset>
#include <list>
#include <functional>
#include <numeric>
#include <cassert>

#define LL long long
#define ULL unsigned long long
#define endl '\n'

using namespace std;



int n, k;
const int N = (int)2e5 + 10;
multiset<int, greater<>> jump_gains;
vector<int> children[N];
int depth[N], max_depth[N];


int sort_tree_by_max_depth(int node, int now_depth) {
    depth[node] = now_depth;
    if (children[node].empty()) {
        max_depth[node] = now_depth;
        return now_depth;
    }
    int ret = now_depth;
    for (auto &child: children[node]) {
        ret = max(ret, sort_tree_by_max_depth(child, now_depth + 1));
    }
    sort(children[node].begin(), children[node].end(), [](const int a, const int b) {
        return max_depth[a] < max_depth[b];
    });
    return max_depth[node] = ret;
}

int dfs(int node, int prev_path_len) {
    if (children[node].empty()) {
        jump_gains.insert(max(0, prev_path_len - depth[node]));
        return 0;
    }
    for (auto &child: children[node]) {
        prev_path_len = dfs(child, prev_path_len + 1) + 1;
    }
    return prev_path_len;
}


void solve() {
    cin >> n >> k;

    for (int i = 2; i <= n; ++i) {
        int pa;
        cin >> pa;
        children[pa].push_back(i);
    }

    int acc = (n - 1) * 2;

    sort_tree_by_max_depth(1, 0);
    dfs(1, 0);

    auto end = jump_gains.end();
    if (k < jump_gains.size()) {
        end = jump_gains.begin();
        std::advance(end, k);
    }

    cout << acc - std::reduce(jump_gains.begin(), end) - max_depth[1] << endl;
}




int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    auto start = chrono::steady_clock::now();
#endif
    cin.sync_with_stdio(false);
    cin.tie(nullptr);

    solve();



#ifdef LOCAL
    auto end = chrono::steady_clock::now();
    chrono::duration<double> diff = end - start;
    cout.setf(ios::fixed, ios::floatfield);
    std::cout << endl;
    std::cout << "use " << std::setprecision(9) << diff.count() << " s";
#endif

    return 0;
}

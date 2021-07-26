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

#define LOCAL

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int value): val(value), left(nullptr), right(nullptr) {}
};



void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

TreeNode* stringToTreeNode(string input) {
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    if (!input.size()) {
        return nullptr;
    }

    string item;
    stringstream ss;
    ss.str(input);

    getline(ss, item, ',');
    TreeNode* root = new TreeNode(stoi(item));
    queue<TreeNode*> nodeQueue;
    nodeQueue.push(root);

    while (true) {
        TreeNode* node = nodeQueue.front();
        nodeQueue.pop();

        if (!getline(ss, item, ',')) {
            break;
        }

        trimLeftTrailingSpaces(item);
        if (item != "null") {
            int leftNumber = stoi(item);
            node->left = new TreeNode(leftNumber);
            nodeQueue.push(node->left);
        }

        if (!getline(ss, item, ',')) {
            break;
        }

        trimLeftTrailingSpaces(item);
        if (item != "null") {
            int rightNumber = stoi(item);
            node->right = new TreeNode(rightNumber);
            nodeQueue.push(node->right);
        }
    }
    return root;
}

vector<int> stringToIntegerVector(string input) {
    vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}


int maxSubArr(vector<int> arr) {
    int ans = -9999999;
    int now = 0;
    for (int i = 0; i < arr.size(); ++i) {
        now += arr[i];
        if (now > ans) {
            ans = now;
        }
        if (now < 0) {
            now = 0;
        }
    }
    return ans;
}


int randInt(int a, int b) {
    static random_device rd;  //Will be used to obtain a seed for the random number engine
    static mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    static uniform_int_distribution<> distrib(a, b);
    return distrib(gen);
}

#define SHIFT 5
#define MASK 0x1F
#define N 10000000
#define BITSPERINT 32

int a[1 + N / BITSPERINT];
int randArr[N];

void cov(int i) {
    a[i >> SHIFT] |= (1 << (i & MASK));
}

void clr(int i) {
    a[i >> SHIFT] &= ~(1 << (i & MASK));
}

bool test(int i) {
    return a[i >> SHIFT] & (1 << (i & MASK));
}

void geneRandoms(int k, int n) {
    for (int i = 0; i < n; ++i) {
        randArr[i] = i;
    }
    for (int i = 0; i < k; ++i) {
        swap(randArr[i], randArr[randInt(i, n - 1)]);
        cout << randArr[i] << endl;
    }
}


// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    int minOperations(vector<int>& tar, vector<int>& arr) {
        unordered_set<int> arrset(arr.begin(), arr.end());
        vector<int> target;
        for (auto &e : tar) {
            if (arrset.count(e)) {
                target.push_back(e);
            }
        }
        vector<vector<int>> dp(tar.size(), vector<int>(arr.size(), 0));
        for (int i = 0; i < tar.size(); ++i) {
            dp[i][0] = max((int)(tar[i] == arr[0]), dp[i - 1 > 0 ? i - 1 : 0][0]);
        }
        for (int i = 0; i < arr.size(); ++i) {
			dp[0][i] = max((int)(tar[0] == arr[i]), dp[0][i - 1 > 0 ? i - 1 : 0]);
        }
        for (int i = 1; i < dp.size(); ++i) {
            for (int j = 1; j < dp[0].size(); ++j) {
                dp[i][j] = max(dp[i - 1][j - 1] + (tar[i] == arr[j]),
                               max(dp[i - 1][j], dp[i][j - 1]));
            }
        }
        return tar.size() - dp.back().back();
    }
};

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
//    cin.sync_with_stdio(false);
//    cin.tie(nullptr);

    /* 处理输入 */

    Solution solu;

    auto start = chrono::steady_clock::now();

    string t, a;
    cin >> t >> a;

    vector<int> target = stringToIntegerVector(t);
    vector<int> arr = stringToIntegerVector(a);

    cout << solu.minOperations(target, arr);

    auto end = chrono::steady_clock::now();
    chrono::duration<double> diff = end - start;
    cout.setf(ios::fixed, ios::floatfield);
    std::cout << endl;
    std::cout << "use " << std::setprecision(9) << diff.count() << " s";

}
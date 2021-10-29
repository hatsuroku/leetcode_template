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

#define LOCAL

using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
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

ListNode* stringToListNode(string input) {
    // Generate list from the input
    vector<int> list = stringToIntegerVector(input);

    // Now convert that list into linked list
    ListNode* dummyRoot = new ListNode(0);
    ListNode* ptr = dummyRoot;
    for(int item : list) {
        ptr->next = new ListNode(item);
        ptr = ptr->next;
    }
    ptr = dummyRoot->next;
    delete dummyRoot;
    return ptr;
}

void prettyPrintTree(TreeNode* node, string prefix = "", bool isLeft = true) {
    if (node == nullptr) {
        cout << "Empty tree";
        return;
    }

    if(node->right) {
        prettyPrintTree(node->right, prefix + (isLeft ? "│   " : "    "), false);
    }

    cout << prefix + (isLeft ? "└── " : "┌── ") + to_string(node->val) + "\n";

    if (node->left) {
        prettyPrintTree(node->left, prefix + (isLeft ? "    " : "│   "), true);
    }
}

void prettyPrintLinkedList(ListNode* node) {
    while (node && node->next) {
        cout << node->val << "->";
        node = node->next;
    }

    if (node) {
        cout << node->val << endl;
    } else {
        cout << "Empty LinkedList" << endl;
    }
}

template<typename T>
void prettyPrintVector(vector<T> vec) {
    cout << '[';
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i != vec.size() - 1) {
            cout << ",";
        }
    }
    cout << "]";
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

vector<char> stringToCharVector(string s) {
    vector<char> ret(s.size());
    for (int i = 0; i < s.size(); ++i) {
        ret[i] = s[i];
    }
    return ret;
}


class Solution {
public:
    vector<vector<int>> ans;
    vector<int> *num;

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        num = &nums;
        per(0);
        return ans;
    }

    void per(int first) {
        vector<int> &v = *num;
        int n = num->size();
        bool visited[21] = { false };
        if (first == n) {
            ans.push_back(v);
        }
        for (int i = first; i < n; ++i) {
            if (visited[v[i] + 10]) continue;
            visited[v[i] + 10] = true;
            swap(v[first], v[i]);
            per(first + 1);
            swap(v[first], v[i]);
        }
    }
};

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin.sync_with_stdio(false);
    cin.tie(nullptr);

    /* 处理输入 */

    Solution solu;

    string s;
    string s2;
    cin >> s;
//    int n;
//    cin >> n;
//    int t;
//    cin >> t;

    auto v = stringToIntegerVector(s);
//    auto l = stringToListNode(s);
//    auto tree = stringToTreeNode(s);
//    vector<vector<int>> g;
//    vector<vector<char>> gg;
//    for (int i = 0; i < n; ++i) {
//        string s;
//        cin >> s;
//        gg.emplace_back(stringToCharVector(s));
//    }


//    while (cin >> s) {
//        auto v = stringToCharVector(s);
//        gg.push_back(v);
//    }

//    vector<string> vs;
//    string tmps;
//    while (cin >> tmps) {
//        vs.push_back(tmps);
//    }

    auto start = chrono::steady_clock::now();

//    cout << solu.licenseKeyFormatting(s, n) << endl;
    auto ret = solu.permuteUnique(v);
    for (auto &e : ret) {
        prettyPrintVector(e);
    }

    auto end = chrono::steady_clock::now();
    chrono::duration<double> diff = end - start;
    cout.setf(ios::fixed, ios::floatfield);
    std::cout << endl;
    std::cout << "use " << std::setprecision(9) << diff.count() << " s";
}


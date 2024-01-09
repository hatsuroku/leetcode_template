from typing import List
from functools import cache
from math import inf
from typing import List, Optional
from sortedcontainers import SortedList
import heapq


import sys
import math
import time
import functools
from bisect import bisect_left, bisect_right
from collections import deque, defaultdict



class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def minExtraChar(self, s: str, dictionary: List[str]) -> int:
        dic = set(dictionary)
        f = [inf for _ in range(len(s) + 1)]
        # f[i] 是 s[0,i) 分割后剩下的最小字符数
        f[0] = 0
        
        for i in range(1, len(s) + 1):
            f[i] = f[i - 1] + 1
            for j in range(i, 0, -1):
                sub = s[j-1:i]
                if sub in dic:
                    f[i] = min(f[i], f[j - 1])
        
        return f[-1]
                
         
        


if __name__ == '__main__':
    # input_file = open('input.txt', 'r', encoding='utf-8')
    # output_file = open('output.txt', 'w', encoding='utf-8')
    # sys.stdin = input_file
    # sys.stdout = output_file

    solu = Solution()

    t1 = time.time()

    ret = solu.minDistance("horse", "ros")
    print(ret)
    
    t2 = time.time()
    print(t2 - t1)


    # input_file.close()
    # output_file.close()

from typing import List
from functools import cache
from math import inf
from typing import List, Optional
from sortedcontainers import SortedList
import heapq

import re
import sys
import math
import time
import functools
from itertools import pairwise
from bisect import bisect_left, bisect_right
from collections import deque, defaultdict, Counter

import requests



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
    def distinctDifferenceArray(self, nums: List[int]) -> List[int]:
        st = set()
        n = len(nums)
        prefix = [0] * n
        suffix = [0] * n
        ans = [0] * n
        for i, x in enumerate(nums):
            st.add(x)
            prefix[i] = len(st)
        
        st.clear()
        for i in range(n - 1, -1, -1):
            st.add(nums[i])
            suffix[i] = len(st)
        
        for i in range(n):
            ans[i] = prefix[i] - (suffix[i + 1] if i + 1 < n else 0)
        
        return ans
            
        

def wow(ran):
    r = list(ran)
    s = [sum(ran[:i+1]) for i, x in enumerate(ran)]
    ss = [sum(s[:i+1]) for i, x in enumerate(ran)]
    calc_ss = []
    
    for i in range(len(r)):
        acc = 0
        for j in range(i+1):
            acc += (i + 1 - j) * r[j]
        calc_ss.append(acc)
    
    print(calc_ss)
    print(ss)
    print()
            
        

if __name__ == '__main__':
    # input_file = open('input.txt', 'r', encoding='utf-8')
    # output_file = open('output.txt', 'w', encoding='utf-8')
    # sys.stdin = input_file
    # sys.stdout = output_file

    solu = Solution()
    wow(range(6))
    wow(range(5, -1, -1))

    t1 = time.time()

    # ret = solu.distinctDifferenceArray()
    
    
    
    t2 = time.time()
    print(t2 - t1)


    # input_file.close()
    # output_file.close()

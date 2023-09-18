from typing import List
from functools import cache
from math import inf
from typing import List, Optional

import sys
import time



class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        pass


if __name__ == '__main__':
    input_file = open('input.txt', 'r', encoding='utf-8')
    output_file = open('output.txt', 'w', encoding='utf-8')
    sys.stdin = input_file
    sys.stdout = output_file

    solu = Solution()

    t1 = time.time()

    l = [1 for _ in range(10 ** 7)]
    print(l[0])
    for i in range(1, 10 ** 7):
        l[i] += l[i - 1]
        print(l[i])

    t2 = time.time()
    print(f'use {t2 - t1} seconds')

    input_file.close()
    output_file.close()

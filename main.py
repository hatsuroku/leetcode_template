from typing import List
from functools import cache
from math import inf
import sys


class Solution:
    def findTargetSumWays(self, nums: List[int], target: int) -> int:
        s = sum(nums) + target
        if s < 0 or s % 2 != 0:
            return 0
        p = s // 2


if __name__ == '__main__':
    input_file = open('input.txt', 'r', encoding='utf-8')
    output_file = open('output.txt', 'w', encoding='utf-8')
    sys.stdin = input_file
    sys.stdout = output_file

    solu = Solution()

    input_file.close()
    output_file.close()

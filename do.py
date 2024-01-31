import sys
import time


def int_input():
    return map(int, input().split())

def local_main():
    input_file = open('input.txt', 'r', encoding='utf-8')
    output_file = open('output.txt', 'w', encoding='utf-8')
    sys.stdin = input_file
    sys.stdout = output_file
    
    t1 = time.time()
    
    main()
    
    t2 = time.time()
    print(f'\n\nused {t2 - t1} seconds')
    
    input_file.close()
    output_file.close()



def main():
    n, m, x = int_input()
    asphalt = list(int_input())
    to = [[] for _ in range(n)]
    ans = [0] * (n - 1)
    
    
    for i in range(m):
        a, b = int_input()
        a -= 1
        b -= 1
        to[a].append((b, i + 1))
        to[b].append((a, i + 1))
    
    if sum(asphalt) < x * (n - 1):
        print('NO')
        return
    
    left, right = 0, n - 2
    
    visited = [False] * n
    
    def dfs(node: int):
        nonlocal left, right
        
        visited[node] = True
        for child, i in to[node]:
            if visited[child]: continue
            dfs(child)
            if asphalt[node] + asphalt[child] >= x:
                asphalt[node] += asphalt[child] - x
                ans[left] = i
                left += 1
            else:
                ans[right] = i
                right -= 1
    
    dfs(0)
    print('YES')
    for a in ans:
        print(a)




if __name__ == '__main__':
    main()
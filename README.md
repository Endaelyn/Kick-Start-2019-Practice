# Kick-Start-2019-Practice
personal practice

#### A2 Parcels
在BFS后使用二分法求解，可以作为一种普遍思路：  
若问题的最优解S是某种数值（最短时间，etc），可以将“给定数值K，判断S是否<=K”作为子问题，用二分搜索对K进行迭代，最终得到K=S。若子问题求解时间复杂度为O(N)，则二分搜索时间复杂度为O(NlogM)，其中M为在最坏情况下K的迭代范围。

#### A3 Contention
难度太高，性价比低，暂时不做。

#### B1 Building Palindromes
前缀和(prefix sum)，某元素及其之前所有元素之和。  
对于需要反复查询数组元素出现频率的场合，前缀和是有用的工具，空间换时间。

# 每日一题复盘：P1177 排序（归并排序实现）

## 题目简介
给定一个正整数 `N` 和 `N` 个正整数 `a_i`，要求将这些数从小到大排序并输出，数字之间用空格分隔，行末无多余空格。

- 数据范围：`1 ≤ N ≤ 1e5`，`1 ≤ a_i ≤ 1e9`
- 关键点：`N` 最大到 `1e5`，需要使用 **O(n log n)** 的排序算法，否则会超时。

---

## 最初思路与问题
一开始写的是类似选择排序的做法：每轮从区间中找最小值交换到前面。

- 选择排序复杂度：**O(n²)**
- 当 `N=1e5` 时，`n²=1e10` 级别，必然 TLE（超时）。

另外还踩到过两个典型 bug（在选择排序版本中）：
1. `min` 没有在每轮循环重置，导致比较逻辑错误；
2. `p` 可能未被赋值就使用（未初始化变量），产生未定义行为。

因此决定更换算法。

---

## 最终选择：归并排序（Merge Sort）

### 为什么选归并排序？
- 时间复杂度稳定：**最坏也是 O(n log n)**，不怕被卡数据
- 思路清晰：分治 + 合并
- 相比快排更少边界坑（尤其是重复元素、最坏情况退化）
- 相比堆排更容易理解和调试

---

## 算法思路
归并排序核心是“分治”：

1. 将区间 `[l, r]` 平分成 `[l, mid]` 和 `[mid+1, r]`
2. 递归排序左右两段
3. 将两段有序数组**合并**成一个有序区间

合并过程用一个辅助数组 `tmp`：
- 用两个指针分别扫左右部分，把较小的元素依次放入 `tmp`
- 最后再把 `tmp[l..r]` 拷回原数组

---

## 复杂度分析
- 时间复杂度：**O(n log n)**
- 空间复杂度：**O(n)**（需要一个辅助数组 `tmp`）

在 `N ≤ 1e5` 下完全可过。

---

## 关键实现细节
- 按题目要求使用 `cin/cout`
- 不使用 `sort`（不调用 STL 排序）
- 输出格式严格控制：数字之间空格分隔，**行末无多余空格**
- 使用快速 IO 提升稳定性：
  - `ios::sync_with_stdio(false);`
  - `cin.tie(nullptr);`

---

## 参考代码（归并排序）
```cpp
#include <iostream>
using namespace std;

void mergeSort(int a[], int tmp[], int l, int r) {
    if (l >= r) return;
    int m = (l + r) >> 1;
    mergeSort(a, tmp, l, m);
    mergeSort(a, tmp, m + 1, r);

    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) tmp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
    while (i <= m) tmp[k++] = a[i++];
    while (j <= r) tmp[k++] = a[j++];

    for (int t = l; t <= r; t++) a[t] = tmp[t];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int *a = new int[n];
    int *tmp = new int[n];

    for (int i = 0; i < n; i++) cin >> a[i];

    mergeSort(a, tmp, 0, n - 1);

    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << a[i];
    }

    delete[] a;
    delete[] tmp;
    return 0;
}

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

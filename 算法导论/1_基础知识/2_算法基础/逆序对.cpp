#include <iostream>
#include <vector>
int cnt = 0;
void merge(int arr[], int l, int r) {
    int mid = (l + r) / 2, left = l, right = mid + 1, temp;
    std::vector<int> v;
    while (left <= mid && right <= r) {
        if (arr[left] <= arr[right])
            v.push_back(arr[left]), left++;
        else
            v.push_back(arr[right]), right++, cnt += mid - left + 1;
    }
    while (left <= mid)
        v.push_back(arr[left++]);
    while (right <= r)
        v.push_back(arr[right++]);
    for (temp = 0; temp < v.size(); temp++)
        arr[l + temp] = v[temp];
}

void mergeSort(int arr[], int l, int r) {
    if (r > l) {
        int mid = (l + r) / 2;
        mergeSort(arr, l, mid);
        mergeSort(arr, mid + 1, r);
        merge(arr, l, r);
    }
}

int main() {
    int arr[] = {2, 3, 8, 6, 1};
    mergeSort(arr, 0, 4);
    for (int i = 0; i < 5; i++)
        printf("%d ", arr[i]);
    printf("\ncnt:%d", cnt);
    return 0;
}

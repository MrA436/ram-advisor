// Utils.h
// TCS307 Unit 5: Function templates (clamp<T>, average<T>)
// TCS302 Unit 4: Sorting (quick sort) and searching (binary search)
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <numeric>
#include <functional>

// ---- Generic clamp<T>() ----
template <typename T>
T clampValue(T value, T lo, T hi) {
    if (value < lo) return lo;
    if (value > hi) return hi;
    return value;
}

// ---- Generic average<T>() over any container of numeric readings ----
template <typename T>
double averageValue(const std::vector<T>& values) {
    if (values.empty()) return 0.0;
    double sum = 0.0;
    for (const auto& v : values) sum += static_cast<double>(v);
    return sum / values.size();
}

// ---- Quick sort (TCS302 Unit 4), generic via a comparator ----
template <typename T, typename Compare>
void quickSort(std::vector<T>& arr, int low, int high, Compare cmp) {
    if (low < high) {
        T pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (cmp(arr[j], pivot)) {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        int p = i + 1;
        quickSort(arr, low, p - 1, cmp);
        quickSort(arr, p + 1, high, cmp);
    }
}

template <typename T, typename Compare>
void quickSort(std::vector<T>& arr, Compare cmp) {
    if (!arr.empty()) quickSort(arr, 0, static_cast<int>(arr.size()) - 1, cmp);
}

// ---- Binary search (TCS302 Unit 4) over a sorted vector, by a key extractor ----
template <typename T, typename KeyType, typename KeyFn>
int binarySearchByKey(const std::vector<T>& sortedArr, KeyType key, KeyFn keyOf) {
    int lo = 0, hi = static_cast<int>(sortedArr.size()) - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        auto midKey = keyOf(sortedArr[mid]);
        if (midKey == key) return mid;
        if (midKey < key) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;   // not found
}

#endif

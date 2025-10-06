#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include <locale>


void print_vector(const std::vector<int>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i + 1 < vec.size()) std::cout << ", ";
    }
    std::cout << "]";
}

void merge(std::vector<int>& arr, std::vector<int>& temp, int left, int mid, int right) {
    int i = left;
    int j = mid;
    int k = left;

    while (i < mid && j < right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i < mid) temp[k++] = arr[i++];
    while (j < right) temp[k++] = arr[j++];

    for (int x = left; x < right; ++x) {
        arr[x] = temp[x];
    }
}

void merge_sort(std::vector<int>& arr, std::vector<int>& temp, int left, int right) {
    if (right - left <= 1) return;
    int mid = left + (right - left) / 2;
    merge_sort(arr, temp, left, mid);
    merge_sort(arr, temp, mid, right);
    merge(arr, temp, left, mid, right);
}

std::vector<int> generate_random_data(int size) {
    std::vector<int> data(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100000);

    for (int i = 0; i < size; ++i) {
        data[i] = dis(gen);
    }
    return data;
}

void benchmark_merge_sort(int size) {
    std::vector<int> data = generate_random_data(size);
    std::vector<int> temp(size);

    auto start = std::chrono::high_resolution_clock::now();
    merge_sort(data, temp, 0, data.size());
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double milliseconds = duration.count() / 1000.0;

    std::cout << std::fixed << std::setprecision(2);
    std::cout.imbue(std::locale("")); // enable comma grouping

    std::cout << "C++ - Array size: " << size << std::endl;
    std::cout << "C++ - Execution time: " << milliseconds << " ms" << std::endl;
    std::cout << "C++ - Elements per second: " 
              << std::fixed << std::setprecision(0) 
              << (size / (milliseconds / 1000.0)) << std::endl;
    std::cout << std::endl;
}

int main() {
    std::vector<int> numbers = {64, 34, 25, 12, 22, 11, 90};
    std::vector<int> temp(numbers.size());

    std::cout << "Small example: ";
    print_vector(numbers);
    std::cout << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    merge_sort(numbers, temp, 0, numbers.size());
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Sorted: ";
    print_vector(numbers);
    std::cout << std::endl;

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Time: " << (duration.count() / 1000.0) << " ms" << std::endl;
    std::cout << std::endl;

    std::cout << "=== C++ MERGE SORT BENCHMARKS ===" << std::endl;
    std::vector<int> test_sizes = {1000, 10000, 100000};
    for (int size : test_sizes) {
        benchmark_merge_sort(size);
    }

    return 0;
}

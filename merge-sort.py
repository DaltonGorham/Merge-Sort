import time
import random

def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    
    # Divide
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])
    
    # Conquer
    return merge(left, right)

def merge(left, right):
    result = []
    i = j = 0
    
    # Compare elements and merge
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    
    # Add remaining elements
    result.extend(left[i:])
    result.extend(right[j:])
    
    return result

def benchmark_merge_sort(size):
    """
    Benchmark merge sort with different array sizes.
    """
    # Generate random data
    data = [random.randint(1, 100000) for _ in range(size)]
    
    # Time the sorting
    start_time = time.perf_counter()
    sorted_data = merge_sort(data.copy())
    end_time = time.perf_counter()
    
    execution_time = (end_time - start_time) * 1000  # Convert to milliseconds
    
    print(f"Python - Array size: {size:,}")
    print(f"Python - Execution time: {execution_time:.2f} ms")
    print(f"Python - Elements per second: {size / (execution_time / 1000):,.0f}")
    print()
    
    return execution_time

# Usage examples
if __name__ == "__main__":
    # Small example
    numbers = [64, 34, 25, 12, 22, 11, 90]
    print(f"Small example: {numbers}")
    
    start = time.perf_counter()
    sorted_numbers = merge_sort(numbers)
    end = time.perf_counter()
    
    print(f"Sorted: {sorted_numbers}")
    print(f"Time: {(end - start) * 1000:.3f} ms")
    print()
    
    # Benchmarks with different sizes
    test_sizes = [1000, 10000, 100000]
    
    print("=== PYTHON MERGE SORT BENCHMARKS ===")
    for size in test_sizes:
        benchmark_merge_sort(size)
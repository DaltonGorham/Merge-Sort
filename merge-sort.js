// JavaScript Merge Sort 

// Merge two sorted subarrays in place
function merge(mainArray, leftArray, rightArray, startIndex) {
    let leftIndex = 0;
    let rightIndex = 0;
    let mainIndex = startIndex;

    while (leftIndex < leftArray.length && rightIndex < rightArray.length) {
        mainArray[mainIndex++] =
            leftArray[leftIndex] <= rightArray[rightIndex]
                ? leftArray[leftIndex++]
                : rightArray[rightIndex++];
    }

    while (leftIndex < leftArray.length) mainArray[mainIndex++] = leftArray[leftIndex++];
    while (rightIndex < rightArray.length) mainArray[mainIndex++] = rightArray[rightIndex++];
}


// Recursive merge sort
function mergeSort(arr, start = 0, end = arr.length) {
    if (end - start <= 1) return;

    const mid = Math.floor((start + end) / 2);
    mergeSort(arr, start, mid);
    mergeSort(arr, mid, end);

    const leftArr = arr.slice(start, mid);
    const rightArr = arr.slice(mid, end);

    merge(arr, leftArr, rightArr, start);
}

// Generate random array
function generateRandomArray(size) {
    return Array.from({ length: size }, () => Math.floor(Math.random() * 100000) + 1);
}

// Benchmark function 
function benchmarkMergeSort(size) {
    const arr = generateRandomArray(size);

    const start = performance.now();
    mergeSort(arr);
    const end = performance.now();

    const executionTime = end - start; // ms
    const elementsPerSecond = size / (executionTime / 1000);

    console.log(`JavaScript - Array size: ${size.toLocaleString()}`);
    console.log(`JavaScript - Execution time: ${executionTime.toFixed(2)} ms`);
    console.log(`JavaScript - Elements per second: ${Math.round(elementsPerSecond).toLocaleString()}\n`);
}

// Example run
(function main() {
    const numbers = [64, 34, 25, 12, 22, 11, 90];
    console.log("Small example:");
    console.log(numbers);

    mergeSort(numbers);
    console.log("Sorted:");
    console.log(numbers);
    console.log();

    console.log("=== JAVASCRIPT MERGE SORT BENCHMARKS ===");
    [1000, 10000, 100000].forEach(size => benchmarkMergeSort(size));
})();

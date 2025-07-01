#include <bits/stdc++.h>
#include <chrono>

using namespace std;

vector<int> randomize(int size, int min, int max) {
    vector<int> result;
    result.reserve(size);
    for (int i = 0; i < size; ++i) {
        // Generate a random number in the range [min, max]
        result.push_back(rand() % (max - min + 1) + min);
    }
    return result;
}

// Function that prints out the elements
void printVector(const vector<int>& a, int limit) {
    for (int i = 0; i < a.size() && i < limit; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
}


// Bubble Sort in Descending Order
void bubbleSort(vector<int>& a) {
    
    bool swapped_in_pass;
    for (int i = 0; i < a.size() - 1; i++) {
        swapped_in_pass = false;
        // In each pass, the largest element of the unsorted part "bubbles up" to its correct position.
        for (int j = a.size() - 1; j > i; j--) {
            if (a.at(j) > a.at(j - 1)) {
                swap(a.at(j), a.at(j - 1));
                swapped_in_pass = true;
            }
        }
        // If no swaps occurred in a pass, the array is already sorted.
        if (!swapped_in_pass) {
            break;
        }
    }
    
}

// Selection Sort in Descending Order
void selectionSort(vector<int>& a) {
    
    for (int i = 0; i < a.size() - 1; i++) {
        int max_index = i;
        // Find the index of the maximum element in the unsorted part.
        for (int j = i + 1; j < a.size(); j++) {
            if (a.at(j) > a.at(max_index)) {
                max_index = j;
            }
        }
        // Swap the found maximum element with the current element.
        if (max_index != i) {
            swap(a.at(i), a.at(max_index));
        }
    }
    
}

// Merge Sort in Descending Order
// Helper function: merges two sorted subarrays
void merge(vector<int>& a, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary vectors to store the left and right halves
    vector<int> Left(n1), Right(n2);

    for (int i = 0; i < n1; i++)
        Left[i] = a[left + i];
    for (int j = 0; j < n2; j++)
        Right[j] = a[mid + 1 + j];

    // Merge the temporary vectors back into the original vector a[left..right]
    // Initial index of the first, second, merged subarray
    int i = 0; 
    int j = 0; 
    int k = left;

    while (i < n1 && j < n2) {
        // Descending order
        if (Left[i] >= Right[j]) { 
            a[k] = Left[i];
            i++;
        } else {
            a[k] = Right[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of Left or Right, if any
    while (i < n1) {
        a[k] = Left[i];
        i++;
        k++;
    }
    while (j < n2) {
        a[k] = Right[j];
        j++;
        k++;
    }
}

// Main Merge Sort function
void mergeSort(vector<int>& a, int left, int right) {
    
    if (left >= right) {
        // Base case reached
        return; 
    }
    // Find the mid
    int mid = left + (right - left) / 2;
    mergeSort(a, left, mid);
    mergeSort(a, mid + 1, right);
    merge(a, left, mid, right);
    
}

// Quick Sort in Descending Order
// Helper function: partitions the array
int partition(vector<int>& a, int low, int high) {
    // Choose the last element as the pivot
    int pivot = a[high]; 
    // Index of the boundary of the larger element area
    int i = (low - 1);   

    for (int j = low; j <= high - 1; j++) {
        // If the current element is greater than or equal to the pivot (for descending sort)
        if (a[j] >= pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[high]);
    return (i + 1);
}

// Main Quick Sort function
void quickSort(vector<int>& a, int low, int high) {
    
    if (low < high) {
        // pi is the partitioning index, a[pi] is now at the right place
        int pi = partition(a, low, high);

        // Recursively sort elements before and after the partition
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
    
}


int main() {
    // Initialize random seed, should only be called once.
    srand(time(0));
    // Define the color used
    const std::string RESET = "\033[0m";
	const std::string RED = "\033[31m";

    vector<int> a = randomize(10000, 3, 32000);
    vector<int> b = a;
    vector<int> c = a;
    vector<int> d = a;
    // Define the start and finish time used
    std::chrono::time_point<std::chrono::high_resolution_clock> start1, start2, start3, start4, stop1, stop2, stop3, stop4;
    
    cout << "Original array (first 100 elements):" << endl;
    printVector(a, 100);
    cout << "----------------------------------" << endl;

    // --- Using Bubble Sort ---
    cout << "Bubble Sort (descending)..." << endl;
    // Use start and stop to count the duration
    start1 = std::chrono::high_resolution_clock::now();
    bubbleSort(a);
    stop1 = std::chrono::high_resolution_clock::now();
    // Calculate the time used by stop-start
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1).count();
    cout << "Sorted array (first 100 elements):" << endl;
    printVector(a, 100);
    cout << "Time used: " << RED << duration1/1000000.0 << "s" << RESET;
    cout << "----------------------------------" << endl;

    // --- Using Selection Sort ---
    cout << "Selection Sort (descending)..." << endl;
    start2 = std::chrono::high_resolution_clock::now();
    selectionSort(b);
    stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2).count();
    cout << "Sorted array (first 100 elements):" << endl;
    printVector(b, 100);
    cout << "Time used: " << RED << duration2/1000000.0 << "s" << RESET;
    cout << "----------------------------------" << endl;

    // --- Using Merge Sort ---
    cout << "Merge Sort (descending)..." << endl;
    start3 = std::chrono::high_resolution_clock::now();
    mergeSort(c, 0, c.size() - 1);
    stop3 = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(stop3 - start3).count();
    cout << "Sorted array (first 100 elements):" << endl;
    printVector(c, 100);
    cout << "Time used: " << RED << duration3/1000000.0 << "s" <<RESET;
    cout << "----------------------------------" << endl;

    // --- Using Quick Sort ---
    cout << "Quick Sort (descending)..." << endl;
    start4 = std::chrono::high_resolution_clock::now();
    quickSort(d, 0, d.size() - 1);
    stop4 = std::chrono::high_resolution_clock::now();
    auto duration4 = std::chrono::duration_cast<std::chrono::microseconds>(stop4 - start4).count();
    cout << "Sorted array (first 100 elements):" << endl;
    printVector(d, 100);
    cout << "Time used: " << RED << duration4/1000000.0 << "s" << RESET;
    cout << "----------------------------------" << endl;
}

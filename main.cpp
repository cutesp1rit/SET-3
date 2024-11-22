#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <chrono>
#include <map>

class ArrayGenerator {
public:
    ArrayGenerator(int size = 10000, int minValue = 0, int maxValue = 6000) : size(size), minValue(minValue), maxValue(maxValue) {
        std::srand(std::time(nullptr));
    }

    std::vector<int> randomArray() {
        std::vector<int> array(size);
        for (int& element : array) {
            element = randomInt(minValue, maxValue);
        }
        return array;
    }

    std::vector<int> reverseSortedArray() {
        std::vector<int> array = randomArray();
        std::sort(array.begin(), array.end(), std::greater<int>());
        return array;
    }

    std::vector<int> SortedArrayButSomeSwaps() {
        int swapCount = size / 10;
        std::vector<int> array = randomArray();
        std::sort(array.begin(), array.end()); // сортируем, чтобы потом свапнуть 1/10 массива
        for (int i = 0; i < swapCount; ++i) {
            int ind1 = randomInt(0, size - 1);
            int ind2 = randomInt(0, size - 1);
            std::swap(array[ind1], array[ind2]);
        }
        return array;
    }

private:
    int size;
    int minValue;
    int maxValue;

    // генерация случайного числа в заданном диапазоне
    int randomInt(int min, int max) {
        return std::rand() % (max - min + 1);
    }
};

void insertionSort(std::vector<int> &arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int main = arr[i];
        int j = i;
        while (j > left && arr[j - 1] > main) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = main;
    }
}

void merge(std::vector<int> &arr, int left, int mid, int right) {
    std::vector<int> tmp_vect;

    int first_ptr = left;
    int second_ptr = mid + 1;

    while (first_ptr <= mid || second_ptr <= right) {
        if (first_ptr > mid) {  // left часть закончилась
            tmp_vect.push_back(arr[second_ptr]);
            second_ptr++;
            continue;
        }

        if (second_ptr > right) {  // right часть закончилась
            tmp_vect.push_back(arr[first_ptr]);
            first_ptr++;
            continue;
        }

        if (arr[first_ptr] <= arr[second_ptr]) {
            tmp_vect.push_back(arr[first_ptr]);
            first_ptr++;
        } else {
            tmp_vect.push_back(arr[second_ptr]);
            second_ptr++;
        }
    }

    for (int i = 0; i < tmp_vect.size(); ++i) {
        arr[left + i] = tmp_vect[i];
    }
}

void updateSort(std::vector<int> &arr, int left, int right) {
    if (right - left + 1 <= 15) {
        insertionSort(arr, left, right);
    } else {
        int mid = left + (right - left) / 2;
        updateSort(arr, left, mid);
        updateSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSort(std::vector<int> &arr, int left, int right) {
    if (right - left + 1 <= 1) {
        return;
    } else {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

class SortTester {
public:
    // для merge sort
    long long HowMuchTime_MS(std::vector<int> & array) {
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(array, 0, array.size() - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    }

    // для update sort
    long long HowMuchTime_US(std::vector<int> & array) {
        auto start = std::chrono::high_resolution_clock::now();
        updateSort(array, 0, array.size() - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    }
};

int main() {
    ArrayGenerator generator = ArrayGenerator();
    SortTester test = SortTester();
    std::vector<int> tmp_arr;
    std::map<int, std::vector<int>> results_MS_RA;
    std::map<int, std::vector<int>> results_MS_RSA;
    std::map<int, std::vector<int>> results_MS_ASA;
    std::map<int, std::vector<int>> results_US_RA;
    std::map<int, std::vector<int>> results_US_RSA;
    std::map<int, std::vector<int>> results_US_ASA;

    int ind;

    // 20 замеров для усреднения результатов
    for (int j = 0; j < 20; j++) {
        std::vector<int> randomArray = generator.randomArray();

        for (int i = 0; i < 500; i++) {
            tmp_arr.push_back(randomArray[i]);
        }

        ind = 500;
        for (int n = 500; n <= 10000; n += 100) {
            while (tmp_arr.size() < n) {
                tmp_arr.push_back(randomArray[ind]);
                ind++;
            }

            results_MS_RA[n].push_back(test.HowMuchTime_MS(tmp_arr));
            results_US_RA[n].push_back(test.HowMuchTime_US(tmp_arr));
        }

        tmp_arr.clear();

        std::vector<int> reverseSortedArray = generator.reverseSortedArray();

        for (int i = 0; i < 500; i++) {
            tmp_arr.push_back(randomArray[i]);
        }

        ind = 500;
        for (int n = 500; n <= 10000; n += 100) {
            while (tmp_arr.size() < n) {
                tmp_arr.push_back(randomArray[ind]);
                ind++;
            }

            results_MS_RSA[n].push_back(test.HowMuchTime_MS(tmp_arr));
            results_US_RSA[n].push_back(test.HowMuchTime_US(tmp_arr));
        }

        tmp_arr.clear();

        std::vector<int> almostSortedArray = generator.SortedArrayButSomeSwaps();

        for (int i = 0; i < 500; i++) {
            tmp_arr.push_back(randomArray[i]);
        }

        ind = 500;
        for (int n = 500; n <= 10000; n += 100) {
            while (tmp_arr.size() < n) {
                tmp_arr.push_back(randomArray[ind]);
                ind++;
            }

            results_MS_ASA[n].push_back(test.HowMuchTime_MS(tmp_arr));
            results_US_ASA[n].push_back(test.HowMuchTime_US(tmp_arr));
        }

        tmp_arr.clear();
    }

    for (int n = 500; n <= 10000; n += 100) {
        std::vector<int> curr_vect = results_MS_RA[n];
        long long sum = 0;
        for (int i = 0; i < 20; i++) {
            sum += curr_vect[i];
        }
        std::cout << (double)sum/20 << " ";

        curr_vect = results_MS_RSA[n];
        sum = 0;
        for (int i = 0; i < 20; i++) {
            sum += curr_vect[i];
        }
        std::cout << (double)sum/20 << " ";

        curr_vect = results_MS_ASA[n];
        sum = 0;
        for (int i = 0; i < 20; i++) {
            sum += curr_vect[i];
        }
        std::cout << (double)sum/20 << " ";

        curr_vect = results_US_RA[n];
        sum = 0;
        for (int i = 0; i < 20; i++) {
            sum += curr_vect[i];
        }
        std::cout << (double)sum/20 << " ";

        curr_vect = results_US_RSA[n];
        sum = 0;
        for (int i = 0; i < 20; i++) {
            sum += curr_vect[i];
        }
        std::cout << (double)sum/20 << " ";

        curr_vect = results_US_ASA[n];
        sum = 0;
        for (int i = 0; i < 20; i++) {
            sum += curr_vect[i];
        }
        std::cout << (double)sum/20 << "\n";
    }

    return 0;
}

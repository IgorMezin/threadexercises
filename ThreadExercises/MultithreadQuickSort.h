#ifndef MULTITHREADQUICKSORT_H
#define MULTITHREADQUICKSORT_H
#include <iterator>
#include <vector>
#include <mutex>
#include <queue>
template <typename T>
class QuickSort {
private:
    typename std::vector<T>::iterator partition(std::vector<T>& vec, typename std::vector<T>::iterator start, typename std::vector<T>::iterator stop);
public:
    void quickSort(std::vector<T>& vec, typename std::vector<T>::iterator start, typename std::vector<T>::iterator stop);
};

template <typename T>
class MultithreadQuickSort {
public:
    MultithreadQuickSort() = delete;
    MultithreadQuickSort(int numThreads);
    ~MultithreadQuickSort();
    void quickSort(std::vector<T>& vec);

private:
    struct Task {
        std::vector<T>& vec; 
        typename std::vector<T>::iterator start;
        typename std::vector<T>::iterator stop;
    };
    
    void worker();
    typename std::vector<T>::iterator partition(std::vector<T>& vec, typename std::vector<T>::iterator start, typename std::vector<T>::iterator stop);
    void quickSortHelper(std::vector<T>& vec, typename std::vector<T>::iterator start, typename std::vector<T>::iterator stop);

    std::queue<Task> taskQueue;
    std::vector<std::thread> workers;
    mutable std::mutex queueMtx;
    std::condition_variable cv;
    bool done;



};
extern template class QuickSort<int>;
extern template class MultithreadQuickSort<int>;
#endif // MULTITHREADQUICKSORT_H

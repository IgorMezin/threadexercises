#include "MultithreadQuickSort.h"
#include <iterator>
#include <algorithm>
#include <vector>
#include <mutex>
#include <thread>


template <typename T>
typename std::vector<T>::iterator QuickSort<T>::partition(std::vector<T>& vec, typename std::vector<T>::iterator start, typename std::vector<T>::iterator stop) {
    auto pivot = stop - 1;
    auto it = start; 

    while (it != pivot) {
        if (*it <= *pivot) {
            ++it;
        }
        else {
            std::iter_swap(it, pivot - 1);
            std::iter_swap(pivot - 1, pivot);
            --pivot;
        }
    }
    return pivot;
}
template <typename T>
void QuickSort<T>::quickSort(std::vector<T>& vec, typename std::vector<T>::iterator start, typename std::vector<T>::iterator stop) {
    if (start < stop) {
        auto pivot = partition(vec, start, stop);
        quickSort(vec, start, pivot);
        quickSort(vec, pivot + 1, stop);
    }
}


template <typename T>
MultithreadQuickSort<T>::MultithreadQuickSort(int numThreads) : done(false)
{
    for (int i = 0; i < numThreads; ++i) {
        workers.emplace_back(&MultithreadQuickSort<T>::worker, this);
    }
}

template<typename T>
MultithreadQuickSort<T>::~MultithreadQuickSort()
{
    {
        std::unique_lock<std::mutex> ulock(queueMtx);
        done = true;
        cv.notify_all();
    }
    for (auto& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

template <typename T>
void MultithreadQuickSort<T>::quickSort(std::vector<T>& vec) {
    {
        std::unique_lock<std::mutex> lock(queueMtx);
        taskQueue.push({ vec, vec.begin(), vec.end() });
    }
    cv.notify_all();

    // Wait for all tasks to complete
    {
        std::unique_lock<std::mutex> lock(queueMtx);
        cv.wait(lock, [this] { return taskQueue.empty(); });
    }
}

template <typename T>
typename std::vector<T>::iterator MultithreadQuickSort<T>::partition(std::vector<T>& vec, typename std::vector<T>::iterator start, typename std::vector<T>::iterator stop)
{
    auto pivot = stop - 1;
    auto it = start;

    while (it != pivot) {
        if (*it <= *pivot) {
            ++it;
        }
        else {
            std::iter_swap(it, pivot - 1);
            std::iter_swap(pivot - 1, pivot);
            --pivot;
        }
    }
    return pivot;
}

template<typename T>
void MultithreadQuickSort<T>::quickSortHelper(std::vector<T>& vec, typename std::vector<T>::iterator start, typename std::vector<T>::iterator stop)
{
    if (start < stop) {
        auto pivot = partition(vec, start, stop);

        taskQueue.push({ vec, start, pivot });
        taskQueue.push({ vec, pivot + 1, stop });
    }
    cv.notify_all();
}


template <typename T>
void MultithreadQuickSort<T>::worker()
{
    while (true) {
        std::unique_lock<std::mutex> ulock(queueMtx);
        cv.wait(ulock, [this]() { return !taskQueue.empty() || done; });

        if (done || taskQueue.empty()) {
            return;
        }

        Task task = taskQueue.front();
        taskQueue.pop();
        ulock.unlock();

        quickSortHelper(task.vec, task.start, task.stop);

        ulock.lock();
        if (taskQueue.empty()) {
            cv.notify_one();
        }
    }
}

template class QuickSort<int>;
template class MultithreadQuickSort<int>;
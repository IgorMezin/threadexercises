#include "ThreadSafeVector.h"
#include <iostream>
#include <vector>
template<typename T>
 void ThreadSafeVector<T>::push_back(const T& value)
{
     std::lock_guard<std::mutex> lock(mtx);
     vec.push_back(value);

}

template<typename T>
void ThreadSafeVector<T>::erase(size_t index)
{
    std::lock_guard<std::mutex> lock(mtx);
    if (index >= vec.size()) {
        throw std::out_of_range("Index out of range");
    }
    vec.erase(vec.begin() + index);
}

template<typename T>
size_t ThreadSafeVector<T>::size() const
{
    std::lock_guard<std::mutex> lock(mtx);
    return vec.size();
}

template<typename T>
T ThreadSafeVector<T>::at(size_t index) const
{
    std::lock_guard<std::mutex> lock(mtx);
    if (index >= vec.size()) {
        throw std::out_of_range("Index out of range");
    }
    return vec.at(index);
}

template<typename T>
T ThreadSafeVector<T>::operator[](size_t index) const
{
    std::lock_guard<std::mutex> lock(mtx);
    return vec[index];
}

template<typename T>
void ThreadSafeVector<T>::clear()
{
    std::lock_guard<std::mutex> lock(mtx);
    vec.clear();
}

template class ThreadSafeVector<int>;

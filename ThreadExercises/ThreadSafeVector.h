#ifndef THREADSAFEVECTOR_H
#define THREADSAFEVECTOR_H
#include <vector>
#include <mutex>
#include <stdexcept>

template <typename T>
class ThreadSafeVector
{
private:
    std::vector<T> vec;
    mutable std::mutex mtx;
public:
    ThreadSafeVector() = default;

    void push_back(const T& value);
    size_t size() const;
    T at(size_t index) const;
    T operator[](size_t index) const;
    void erase(size_t index);
    void clear();
};

extern template class ThreadSafeVector<int>;

#endif // THREADSAFEVECTOR_H

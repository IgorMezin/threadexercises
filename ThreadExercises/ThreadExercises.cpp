#include <iostream>
#include <thread>
#include "ThreadSafeVector.h"

int main()
{
    ThreadSafeVector<int> ts_vec;
    std::vector<int> vec;

    auto add_el = [&ts_vec]() {
        for (int i = 0; i < 1000; ++i) {
            ts_vec.push_back(i);
        }
    };

    std::thread t1(add_el);
    std::thread t2(add_el);

    t1.join();
    t2.join();

    for (size_t i = 0; i < ts_vec.size(); ++i) {
        std::cout << ts_vec[i] << " ";
    }
    std::cout << std::endl;
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}
#include <iostream>
#include <thread>
#include <vector>
#include <iterator>
#include <random>
#include <ctime>
#include <memory>
#include "ThreadSafeVector.h"
#include "MultithreadQuickSort.h"

void programs(int number) {
    switch (number) {
    case 1:
    {
        std::vector<int> v = { 1,2,3 };
        auto iter = v.end();
        iter--;
        std::cout << *iter;
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
        break;
    }
    case 2:{
        std::vector<int> vec = { 1,5,8,3,2, 1, 4, 3, 3, 6 , 0 , 1, 3};
        std::unique_ptr<MultithreadQuickSort<int>> m_q_s = std::make_unique<MultithreadQuickSort<int>>(2);
        m_q_s->quickSort(vec);
        for (const auto& el : vec) {
            std::cout << el << " ";
        }
        std::cout << std::endl;
        break;
    }
    default:
        std::cout << "not implemented" << std::endl; 
    }
}

int main()
{
    //std::srand(std::time((time_t*)nullptr)); // use current time for rng seed
    int num;

    std::vector<int> s = { 1,2,3 };
    std::cout << "Номер символа: " << std::distance(s.begin(), s.end()) << std::endl;

    std::cout << "choose the number of program:\n";
    std::cout << "1. threadSafeVector\n";
    std::cout << "2. multi thread quickSort\n";
    std::cin >> num;
    programs(num);

}
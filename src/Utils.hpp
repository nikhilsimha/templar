#pragma once
#include <iostream>

namespace utils {
    template<class T>
    void printList(const T& t){
        for(auto  elem: t) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}
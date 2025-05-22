#include <iostream>
#include <ctime>
#include <limits>
#include <cstdint>

uint32_t xorshift32_state = static_cast<uint32_t>(std::time(nullptr));

uint32_t xorshift32_next() {
    xorshift32_state ^= xorshift32_state << 13;
    xorshift32_state ^= xorshift32_state >> 17;
    xorshift32_state ^= xorshift32_state << 5;
    return xorshift32_state;
}

// Генерация числа в заданном диапазоне [min, max]
int xorshift32_next_int(int min, int max) {
    return min + (xorshift32_next() % (max - min + 1));
}

int main() {
    std::cout << "10 случайных 32-битных чисел:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << xorshift32_next() << std::endl;
    }

    std::cout << "\n10 случайных чисел в диапазоне [1, 100]:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << xorshift32_next_int(1, 100) << std::endl;
    }
    
    return 0;
}
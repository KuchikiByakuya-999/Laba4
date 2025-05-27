#include <iostream>
#include <vector>
#include <chrono>

uint32_t init_xorshift_state(uint32_t seed = 0) {
    if (seed == 0) {
        seed = static_cast<uint32_t>(
            std::chrono::system_clock::now().time_since_epoch().count());
    }
    return seed;
}

uint32_t xorshift_next(uint32_t* state) {
    *state ^= *state << 13;
    *state ^= *state >> 17;
    *state ^= *state << 5;
    return *state;
}

void xorshift_generate_sequence(uint32_t seed, size_t count, std::vector<uint32_t>& sequence) {
    sequence.clear();
    sequence.reserve(count);
    
    uint32_t state = init_xorshift_state(seed);
    
    for (size_t i = 0; i < count; ++i) {
        sequence.push_back(xorshift_next(&state));
    }
}

int main() {
    const uint32_t seed = 123456789;
    const size_t count = 10;
    
    std::vector<uint32_t> sequence;
    xorshift_generate_sequence(seed, count, sequence);
    
    std::cout << "Сгенерированная последовательность (" << count << " чисел):\n";
    for (uint32_t num : sequence) {
        std::cout << num << std::endl;
    }
    
    return 0;
}
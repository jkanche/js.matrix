#include <emscripten/bind.h>

using namespace emscripten;

// EMSCRIPTEN_KEEPALIVE
double printSumFloat64 (uintptr_t values, int size) {
    double* buffer = reinterpret_cast<double*>(values);
    double sum = 0;

    // printf("%d\n", size);

    for (int i = 0; i < size; ++i) {
        sum += buffer[i];
    }

    return sum;
}

// EMSCRIPTEN_KEEPALIVE
void getAtPosition(int position, uintptr_t val_orig, uintptr_t values) {
    double* buffer_orig = reinterpret_cast<double*>(val_orig);
    double* buffer = reinterpret_cast<double*>(values);

    std::copy(buffer_orig + (position-1), buffer_orig + position, buffer);

    return;
    // return val(typed_memory_view(ptr->nrow(), buffer));
}

EMSCRIPTEN_BINDINGS(my_module) {
    function("printSumFloat64", &printSumFloat64, allow_raw_pointers());
    function("getAtPosition", &getAtPosition, allow_raw_pointers());
}
#include <random>
#include <vector>
#include <chrono>
#include <iostream>
#include <algorithm>
#include "tatami/tatami.h"

int main () {
    // Generating a random matrix of 10000 x 10000 random unifs.
    std::mt19937_64 generator;
    std::uniform_real_distribution<double> distribution(0.0,1.0);

    size_t m = 10000, n = 10000;
    std::vector<double> source(m*n);
    for (size_t i = 0; i < m*n; ++i) {
        source[i] = distribution(generator);
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::shared_ptr<tatami::numeric_matrix> ptr(new tatami::DenseColumnMatrix<double>(m, n, std::move(source)));
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Construction:" << "\t" << duration.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();
    auto routput = tatami::column_sums<double>(ptr.get());
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "COLSUM: " << std::accumulate(routput.begin(), routput.end(), 0.0) << "\t" << duration.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();
    auto coutput = tatami::row_sums(ptr.get());
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "ROWSUM:" << std::accumulate(coutput.begin(), coutput.end(), 0.0) << "\t" << duration.count() << std::endl;

    return 0;
}

#include <emscripten/bind.h>
#include <emscripten/val.h>
#include "tatami/base/DenseMatrix.hpp"
#include <iostream>
#include "scran/qc/PerCellQCMetrics.hpp"

template<typename T>
class JSVector {
public:
    JSVector(const T* p, size_t n) : ptr(p), num(n) {}
    size_t size() const { return num; }
    const T* data() const { return ptr; }
    const T* begin() const { return ptr; }
    const T* end() const { return ptr + num; }
    const T* ptr;
    size_t num;
};

struct NumericMatrix {
    NumericMatrix(int nr, int nc) : nrows(nr), ncols(nc) {
        valbuffer.resize(nr * nc);
        return;
    }

    emscripten::val buffer() const {
        return emscripten::val(emscripten::typed_memory_view(valbuffer.size(), valbuffer.data()));
    }

    void construct() {
        ptr = std::shared_ptr<tatami::numeric_matrix>(new tatami::DenseRowMatrix<double, int>(nrows, ncols, std::move(valbuffer)));
        return;
    }

    int nrow() const {
        return ptr->nrow();
    }

    int ncol() const {
        return ptr->ncol();
    }

    int row(int r) {
        rowbuffer.resize(ptr->ncol());
        auto x = ptr->row(r, rowbuffer.data());
        if (x != rowbuffer.data()) {
            std::copy(x, x + rowbuffer.size(), rowbuffer.data());
        }
        return ptr->nrow();
    }

    int column(int c) {
        colbuffer.resize(ptr->nrow());
        auto x = ptr->row(c, colbuffer.data());
        if (x != rowbuffer.data()) {
            std::copy(x, x + colbuffer.size(), colbuffer.data());
        }
        return ptr->nrow();
    }

    size_t nrows, ncols;
    std::vector<double> valbuffer;
    std::vector<double> rowbuffer, colbuffer;
    std::shared_ptr<tatami::numeric_matrix> ptr;
};

struct PerCellQCMetrics {
    void compute(const NumericMatrix& mat) {
        std::vector<double> buffer(mat.ptr->nrow());
        auto ptr = mat.ptr->column(0, buffer.data());
        std::cout << ptr[0] << std::endl;
        QC.compute_metrics(mat.ptr.get());
        const auto& sums = QC.get_detected();
        return;
    }

    emscripten::val sums() const {
        const auto& sums = QC.get_sums();
        return emscripten::val(emscripten::typed_memory_view(sums.size(), sums.data()));
    }

    scran::PerCellQCMetrics<int> QC;
};

EMSCRIPTEN_BINDINGS(my_class_example) {
    emscripten::class_<NumericMatrix>("NumericMatrix")
        .constructor<int, int>()
        .function("buffer", &NumericMatrix::buffer)
        .function("construct", &NumericMatrix::construct)
        .function("nrow", &NumericMatrix::nrow)
        .function("ncol", &NumericMatrix::ncol)
        .function("row", &NumericMatrix::row)
        .function("column", &NumericMatrix::column)
        ;

    emscripten::class_<PerCellQCMetrics>("PerCellQCMetrics")
        .constructor<>()
        .function("compute", &PerCellQCMetrics::compute)
        .function("sums", &PerCellQCMetrics::sums)
        ;
}

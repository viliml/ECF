#ifndef Root_h
#define Root_h

#include <cmath>
#include "Primitive.h"

namespace Tree {
namespace Primitives {

/**
* \ingroup tree genotypes primitives
* \brief Mul function primitive (Tree genotype)
*/
template<class T>
class RootT : public Primitive {
public:
    RootT(void);
    void execute(void *result, Tree &tree);
    ~RootT(void);
};
typedef RootT<double> Root;



template<class T>
RootT<T>::RootT(void) {
    nArguments_ = 2;
    name_ = "root";
    complementName_ = "pow";
}


template<class T>
RootT<T>::~RootT(void) {}


template<class T>
void RootT<T>::execute(void *result, Tree &tree) {
    T first, second, one = 1;
    T &root = *(T *) result;
    getNextArgument(&first, tree);
    getNextArgument(&second, tree);
    if (second == -3) {
        root = one / std::cbrt(first);
    } else if (second == -2) {
        root = one / std::sqrt(first);
    } else if (second == -1) {
        root = one / first;
    } else if (second == 0) {
        root = 0;
    } else if (second == 1) {
        root = first;
    } else if (second == 2) {
        root = std::sqrt(first);
    } else if (second == 3) {
        root = std::cbrt(first);
    } else {
        root = std::pow(first, one / second);
        if (!std::isfinite(root)) {
            root = 0;
        }
    }
}

}
}

#endif

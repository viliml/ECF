#ifndef Pow_h
#define Pow_h
#include <cmath>
#include "Primitive.h"

namespace Tree {
namespace Primitives {

/**
 * \ingroup tree genotypes primitives
 * \brief Mul function primitive (Tree genotype)
 */
template <class T>
class PowT : public Primitive
{
public:
    PowT(void);
	void execute(void* result, Tree& tree);
	~PowT(void);
};
typedef PowT<double> Pow;


template <class T>
PowT<T>::PowT(void)
{
	nArguments_ = 2;
	name_ = "pow";
	complementName_ = "root";
}


template <class T>
PowT<T>::~PowT(void)
{	}


template <class T>
void PowT<T>::execute(void* result, Tree &tree)
{
	T first, second;
	T& pow = *(T*)result;
    getNextArgument(&first, tree);
    getNextArgument(&second, tree);
    if (second == 0 || first == 1) {
        pow = 1;
    } else if (first == 0) {
        pow = 0;
    } else {
        pow = std::pow(first, second);
        if (!std::isfinite(pow)) {
            pow = 0;
        }
    }
}

}
}

#endif

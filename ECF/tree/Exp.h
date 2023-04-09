#ifndef Exp_h
#define Exp_h
#include "Primitive.h"

namespace Tree {
namespace Primitives {

/**
 * \ingroup tree genotypes primitives
 * \brief Cos function primitive (Tree genotype)
 */
class Exp : public Primitive
{
public:
    Exp(void);
	void execute(void* result, Tree& tree);
	~Exp(void);
};

}
}

#endif 
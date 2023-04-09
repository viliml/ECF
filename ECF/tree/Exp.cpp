#include "../ECF_base.h"
#include "Exp.h"
#include <cmath>

namespace Tree {
namespace Primitives {

Exp::Exp(void)
{
	nArguments_ = 1;
	name_ = "exp";
	complementName_ = "log";
}


Exp::~Exp(void)
{	}


void Exp::execute(void* result, Tree &tree)
{
	double& arg = *(double*)result;
    getNextArgument(&arg, tree);
    arg = exp(arg);
}

}
}
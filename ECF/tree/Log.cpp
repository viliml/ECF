#include "../ECF_base.h"
#include "Log.h"
#include <cmath>

namespace Tree {
namespace Primitives {

const double MIN = 0.000000001; // protected logarithm parameter

Log::Log(void)
{
	nArguments_ = 1;
	name_ = "log";
	complementName_ = "exp";
}


Log::~Log(void)
{	}


void Log::execute(void* result, Tree &tree)
{
	double& arg = *(double*)result;
    getNextArgument(&arg, tree);
    arg = fabs(arg) > MIN ? log(fabs(arg)) : 1.;
}

}
}
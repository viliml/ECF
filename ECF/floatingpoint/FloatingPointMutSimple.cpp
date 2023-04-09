#include "../ECF_base.h"
#include "FloatingPoint.h"
#include <cmath>


namespace FloatingPoint
{

void FloatingPointMutSimple::registerParameters(StateP state)
{
	myGenotype_->registerParameter(state, "mut.simple", (voidP) new double(0), ECF::DOUBLE);
}

bool FloatingPointMutSimple::initialize(StateP state)
{
	voidP sptr = myGenotype_->getParameterValue(state, "mut.simple");
	probability_ = *((double*)sptr.get());

	return true;
}

bool FloatingPointMutSimple::mutate(GenotypeP gene)
{
	FloatingPointP FP = std::static_pointer_cast<FloatingPoint>(gene);

	uint dimension = state_->getRandomizer()->getRandomInteger((uint) FP->realValue.size());
	FP->realValue[dimension] = state_->getRandomizer()->getRandomDouble() * (FP->getUBound() - FP->getLBound()) + FP->getLBound();

	return true;
}

}
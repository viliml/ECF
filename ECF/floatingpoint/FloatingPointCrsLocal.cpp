#include "../ECF_base.h"
#include "FloatingPoint.h"

namespace FloatingPoint
{

void FloatingPointCrsLocal::registerParameters(StateP state)
{
	myGenotype_->registerParameter(state, "crx.local", (voidP) new double(0), ECF::DOUBLE);
}


bool FloatingPointCrsLocal::initialize(StateP state)
{
	voidP sptr = myGenotype_->getParameterValue(state, "crx.local");
	probability_ = *((double*)sptr.get());
	return true;
}


bool FloatingPointCrsLocal::mate(GenotypeP gen1, GenotypeP gen2, GenotypeP child)
{
	FloatingPointP p1 = std::static_pointer_cast<FloatingPoint>(gen1);
	FloatingPointP p2 = std::static_pointer_cast<FloatingPoint>(gen2);
	FloatingPointP ch = std::static_pointer_cast<FloatingPoint>(child);

	double a;

	switch (state_->getRandomizer()->getRandomInteger(0, 1)) {
		case 0: for (uint i = 0; i < p1->realValue.size(); i++) {
					a = state_->getRandomizer()->getRandomDouble();
					ch->realValue[i] = a * (p1->realValue[i]) + (1 - a) * (p2->realValue[i]);
				}
				break;
		case 1: for (uint i = 0; i < p1->realValue.size(); i++) {
					a = state_->getRandomizer()->getRandomDouble();
					ch->realValue[i] = a * (p2->realValue[i]) + (1 - a) * (p1->realValue[i]);
				}
	}

	return true;
}

}
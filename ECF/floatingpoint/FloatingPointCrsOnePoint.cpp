#include "../ECF_base.h"
#include "FloatingPoint.h"


namespace FloatingPoint
{

void FloatingPointCrsOnePoint::registerParameters(StateP state)
{
	myGenotype_->registerParameter(state, "crx.onepoint", (voidP) new double(0), ECF::DOUBLE);
}


bool FloatingPointCrsOnePoint::initialize(StateP state)
{
	voidP sptr = myGenotype_->getParameterValue(state, "crx.onepoint");
	probability_ = *((double*)sptr.get());
	return true;
}


bool FloatingPointCrsOnePoint::mate(GenotypeP gen1, GenotypeP gen2, GenotypeP child)
{
	FloatingPointP p1 = std::static_pointer_cast<FloatingPoint>(gen1);
	FloatingPointP p2 = std::static_pointer_cast<FloatingPoint>(gen2);
	FloatingPointP ch = std::static_pointer_cast<FloatingPoint>(child);

	uint dimensionCrs = state_->getRandomizer()->getRandomInteger((int) p1->realValue.size());
	switch (state_->getRandomizer()->getRandomInteger(0, 1)) {
		case 0: for (uint i = 0; i < dimensionCrs; i++) {
					ch->realValue[i] = p1->realValue[i];
				}
				for (uint i = dimensionCrs; i < p2->realValue.size(); i++) {
					ch->realValue[i] = p2->realValue[i];
				}
				break;
		case 1: for (uint i = 0; i < dimensionCrs; i++) {
					ch->realValue[i] = p2->realValue[i];
				}
				for (uint i = dimensionCrs; i < p1->realValue.size(); i++) {
					ch->realValue[i] = p1->realValue[i];
				}
	}

	return true;
}

}
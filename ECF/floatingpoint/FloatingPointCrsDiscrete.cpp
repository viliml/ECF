#include "../ECF_base.h"
#include "FloatingPoint.h"


namespace FloatingPoint
{

void FloatingPointCrsDiscrete::registerParameters(StateP state)
{
	myGenotype_->registerParameter(state, "crx.discrete", (voidP) new double(0), ECF::DOUBLE);
}


bool FloatingPointCrsDiscrete::initialize(StateP state)
{
	voidP sptr = myGenotype_->getParameterValue(state, "crx.discrete");
	probability_ = *((double*)sptr.get());
	return true;
}


bool FloatingPointCrsDiscrete::mate(GenotypeP gen1, GenotypeP gen2, GenotypeP child)
{
	FloatingPointP p1 = std::static_pointer_cast<FloatingPoint>(gen1);
	FloatingPointP p2 = std::static_pointer_cast<FloatingPoint>(gen2);
	FloatingPointP ch = std::static_pointer_cast<FloatingPoint>(child);
	int a;

	switch (state_->getRandomizer()->getRandomInteger(0, 1)) {
		case 0: for (uint i = 0; i < p1->realValue.size(); i++) {
					a = state_->getRandomizer()->getRandomInteger(0, 1);
					if (a == 0)
						ch->realValue[i] = p1->realValue[i];
					else
						ch->realValue[i] = p2->realValue[i];
				}
				break;
		case 1: for (uint i = 0; i < p1->realValue.size(); i++) {
					a = state_->getRandomizer()->getRandomInteger(0, 1);
					if (a == 0)
						ch->realValue[i] = p2->realValue[i];
					else
						ch->realValue[i] = p1->realValue[i];
				}
	}
	
	return true;
}

}
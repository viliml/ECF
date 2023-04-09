#include "../ECF_base.h"
#include "BitString.h"

namespace BitString
{

void BitStringCrsUniform::registerParameters(StateP state)
{
	myGenotype_->registerParameter(state, "crx.uniform", (voidP) new double(0), ECF::DOUBLE);
}


bool BitStringCrsUniform::initialize(StateP state)
{
	voidP sptr = myGenotype_->getParameterValue(state, "crx.uniform");
	probability_ = *((double*)sptr.get());
	return true;
}


bool BitStringCrsUniform::mate(GenotypeP gen1, GenotypeP gen2, GenotypeP child)
{
    BitStringP p1 = std::static_pointer_cast<BitString>(gen1);
	BitStringP p2 = std::static_pointer_cast<BitString>(gen2);
	BitStringP ch = std::static_pointer_cast<BitString>(child);

	for(uint i = 0; i < p1->bits.size(); i++){
		if (p1->bits[i] == p2->bits[i]) 
			ch->bits[i] = p1->bits[i];
		else
			ch->bits[i] = state_->getRandomizer()->getRandomInteger(2) ? true:false;
	}

	return true;
}
}
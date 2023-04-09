#include "../ECF_base.h"
#include "Permutation.h"
#include <map>


namespace Permutation
{

void PermutationCrsPBX::registerParameters(StateP state)
{
	myGenotype_->registerParameter(state, "crx.PBX", (voidP) new double(0), ECF::DOUBLE);
}


bool PermutationCrsPBX::initialize(StateP state)
{
	voidP sptr = myGenotype_->getParameterValue(state, "crx.PBX");
	probability_ = *((double*)sptr.get());
	return true;
}

	
bool PermutationCrsPBX::mate(GenotypeP gen1, GenotypeP gen2, GenotypeP child)
{
	PermutationP p1 = std::static_pointer_cast<Permutation>(gen1);
	PermutationP p2 = std::static_pointer_cast<Permutation>(gen2);
	PermutationP ch = std::static_pointer_cast<Permutation>(child);

	// storage of elements copied into child (true ==> copied)
	std::vector<bool> taged;
	taged.resize(p1->getSize());

	int count=0;
	for(uint i = 0; i < ch->getSize(); i++) {
		if(state_->getRandomizer()->getRandomInteger(2) == 0) {
			ch->variables[i] = p1->variables[i];
			taged[p1->variables[i]] = 1;
			count++;
		}
		else {
			ch->variables[i] = -1;
		}
	}

	int indCh = 0;
	count = (int) ch->getSize() - count;
	for(uint i = 0; i < ch->getSize() && count > 0; i++) {
			//trazimo prazno mjesto u djetetu
			while(ch->variables[indCh] != -1)
				indCh++;
			//ako element iz drugog roditelja nije vec u djetetu onda ga kopiramo
			if(taged[p2->variables[i]] != 1) {
				ch->variables[indCh] = p2->variables[i];
				count--;
			}
	}
	return true;
}

}
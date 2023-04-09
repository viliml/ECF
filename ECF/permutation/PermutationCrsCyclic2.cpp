#include "../ECF_base.h"
#include "Permutation.h"
#include <map>


namespace Permutation
{

void PermutationCrsCyclic2::registerParameters(StateP state)
{
	myGenotype_->registerParameter(state, "crx.cyclic2", (voidP) new double(0), ECF::DOUBLE);
}


bool PermutationCrsCyclic2::initialize(StateP state)
{
	voidP sptr = myGenotype_->getParameterValue(state, "crx.cyclic2");
	probability_ = *((double*)sptr.get());
	return true;
}


bool PermutationCrsCyclic2::mate(GenotypeP gen1, GenotypeP gen2, GenotypeP child)
{
	PermutationP p1 = std::static_pointer_cast<Permutation>(gen1);
	PermutationP p2 = std::static_pointer_cast<Permutation>(gen2);
	PermutationP ch = std::static_pointer_cast<Permutation>(child);


	std::map<int, int>  index;
	int j, num;

	j = (int) state_->getRandomizer()->getRandomInteger(p1->getSize());

	while (!index[j]) { //da li je ovo OK?
		ch->variables[j] = p1->variables[j];
		num = p2->variables[j];
		index[j] = 1;

		j = 0;
		while ((j < (int) p1->getSize()) && (p1->variables[j] != num)) {
		  j++;
		}
	}

	  for (int i = 0; i < (int) p1->getSize(); i++) {
		if (!index[i]) {
			ch->variables[i] = p2->variables[i];
		}
	  }

	return true;
}

}
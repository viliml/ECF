#include "../ECF_base.h"
#include "Permutation.h"
#include <map>


namespace Permutation
{

void PermutationCrsCyclic::registerParameters(StateP state)
{
	myGenotype_->registerParameter(state, "crx.cyclic", (voidP) new double(0), ECF::DOUBLE);
}


bool PermutationCrsCyclic::initialize(StateP state)
{
	voidP sptr = myGenotype_->getParameterValue(state, "crx.cyclic");
	probability_ = *((double*)sptr.get());
	return true;
}


bool PermutationCrsCyclic::mate(GenotypeP gen1, GenotypeP gen2, GenotypeP child)
{
	PermutationP p1 = std::static_pointer_cast<Permutation>(gen1);
	PermutationP p2 = std::static_pointer_cast<Permutation>(gen2);
	PermutationP ch = std::static_pointer_cast<Permutation>(child);

	std::map<int, int> invP1, invP2, index;

	//radim inverzno mapiranje (broj -> index)

	for (int i = 0; i < (int) p1->getSize(); i++) {
	  invP1[p1->variables[i]] = i;
	  invP2[p2->variables[i]] = i;
	}

	//slučajnim odabirom odabrati da li se kopiranje počima od roditelja 1 ili 2
	int rand = state_->getRandomizer()->getRandomInteger(0,1);

	int j = 0;
	do {
		do {
		  if (rand) {
			ch->variables[j] = p1->variables[j];
			index[j] = 1;
			j = invP2[ch->variables[j]]; // postavi poziciju j na poziciju kopiranog broja u p2
		  } else {
			ch->variables[j] = p2->variables[j];
			index[j] = 1;
			j = invP1[ch->variables[j]]; // postavi poziciju j na poziciju kopiranog broja u p1
		  }
		} while (!index[j]);
		rand = !rand;
		j = 0;
		while (j < (int) p1->getSize() && index[j])
			j++;
	} while (j < (int) p1->getSize());

	return true;
}

}
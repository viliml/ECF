#include "../ECF_base.h"
#include "Permutation.h"
#include <map>


namespace Permutation
{

void PermutationCrsOX2::registerParameters(StateP state)
{
	myGenotype_->registerParameter(state, "crx.OX2", (voidP) new double(0), ECF::DOUBLE);
}


bool PermutationCrsOX2::initialize(StateP state)
{
	voidP sptr = myGenotype_->getParameterValue(state, "crx.OX2");
	probability_ = *((double*)sptr.get());
	return true;
}


bool PermutationCrsOX2::mate(GenotypeP gen1, GenotypeP gen2, GenotypeP child)
{
	PermutationP p1 = std::static_pointer_cast<Permutation>(gen1);
	PermutationP p2 = std::static_pointer_cast<Permutation>(gen2);
	PermutationP ch = std::static_pointer_cast<Permutation>(child);

	int start = state_->getRandomizer()->getRandomInteger(p1->getSize());
	int end = state_->getRandomizer()->getRandomInteger(start, (int) p1->getSize() - 1);

	std::map<int, int> subSet;

	int ind1 = state_->getRandomizer()->getRandomInteger(p1->getSize() - 1);
	int ind2 = state_->getRandomizer()->getRandomInteger(ind1, (int) p1->getSize() - 1);

	// copy subvector into child
	for(int i = ind1; i <= ind2; i++) {
		ch->variables[i] = p1->variables[i];
		subSet[p1->variables[i]] = 1; //bilo je 0
	}
	int indexChild = (ind2 + 1) % p1->getSize();
	std::map<int, int>::iterator iter = subSet.begin();

	// krecemo od pocetka

	int index = 0;
  	for (int i = 0; i < (int) p1->getSize(); i++) {  // copy remaining part of second permutation
		if (index == ind1) {  // skip already copied part
			index = ind2 + 1;
		}
		if (!subSet[p2->variables[i]]) {
			ch->variables[index] = p2->variables[i];
			index++;
		}
	}

	return true;
}

}
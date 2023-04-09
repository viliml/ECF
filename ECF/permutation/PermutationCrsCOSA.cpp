#include "../ECF_base.h"
#include "Permutation.h"
#include <map>


namespace Permutation
{

void PermutationCrsCOSA::registerParameters(StateP state)
{
	myGenotype_->registerParameter(state, "crx.COSA", (voidP) new double(0), ECF::DOUBLE);
}


bool PermutationCrsCOSA::initialize(StateP state)
{
	voidP sptr = myGenotype_->getParameterValue(state, "crx.COSA");
	probability_ = *((double*)sptr.get());
	return true;
}


bool PermutationCrsCOSA::mate(GenotypeP gen1, GenotypeP gen2, GenotypeP child)
{
	PermutationP p1 = std::static_pointer_cast<Permutation>(gen1);
	PermutationP p2 = std::static_pointer_cast<Permutation>(gen2);
	PermutationP ch = std::static_pointer_cast<Permutation>(child);

	int indexChild, start, end;

	indexChild = (int) state_->getRandomizer()->getRandomInteger(p1->getSize());
    start = (indexChild + 1) % p1->getSize();

	int i = 0;
	while ((i < (int) p2->getSize()) && (p2->variables[i] != p1->variables[indexChild])) {
		i++;
	}
	int crx = p2->variables[(i + 1) % p2->getSize()];
	end = 0;
	while ((end < (int) p1->getSize()) && (p1->variables[end] != crx)) {
		end++;
	}

	if (start <= end) {
		for (i = 0; i < (int) p1->getSize(); i++) {
			if (i >= start && i <= end) {
				ch->variables[i] = p1->variables[end - i + start];
			} else {
				ch->variables[i] = p1->variables[i];
			}
		}
	} else {
		for (i = 0; i < (int) p1->getSize(); i++) {
			if (i >= start || i <= end) {
				ch->variables[i] = p1->variables[(end - i + start + p1->getSize()) % p1->getSize()];
			} else {
				ch->variables[i] = p1->variables[i];
			}
		}
	}
	return true;
}

}
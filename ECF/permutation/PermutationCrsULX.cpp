#include "../ECF_base.h"
#include "Permutation.h"
#include <map>


namespace Permutation
{

void PermutationCrsULX::registerParameters(StateP state)
{
	myGenotype_->registerParameter(state, "crx.ULX", (voidP) new double(0), ECF::DOUBLE);
}


bool PermutationCrsULX::initialize(StateP state)
{
	voidP sptr = myGenotype_->getParameterValue(state, "crx.ULX");
	probability_ = *((double*)sptr.get());
	return true;
}


bool PermutationCrsULX::mate(GenotypeP gen1, GenotypeP gen2, GenotypeP child)
{
	PermutationP p1 = std::static_pointer_cast<Permutation>(gen1);
	PermutationP p2 = std::static_pointer_cast<Permutation>(gen2);
	PermutationP ch = std::static_pointer_cast<Permutation>(child);

	std::map<int, int> numCopied;
	std::vector<int> free;

	for (int i = 0; i < (int) p1->getSize(); i++) {
		bool copied = true;
		if (p1->variables[i] == p2->variables[i]) {
		  ch->variables[i] = p1->variables[i];
		} else if (!numCopied[p1->variables[i]] && !numCopied[p2->variables[i]]) {
		  ch->variables[i] = state_->getRandomizer()->getRandomInteger(0, 1) ? p1->variables[i] : p2->variables[i];
		} else if (!numCopied[p1->variables[i]]) {
		  ch->variables[i] = p1->variables[i];
		} else if (!numCopied[p2->variables[i]]) {
		  ch->variables[i] = p2->variables[i];
		} else {
		  copied = false;
		  free.push_back(i);
		}
		if (copied)
			numCopied[ch->variables[i]] = 1;
	}

	if (free.size() > 0) {
		for (int i = 0; i < (int) p1->getSize(); i++) {
			if (!numCopied[i]) {
				int r = state_->getRandomizer()->getRandomInteger((int) free.size());

				ch->variables[free[r]] = i;
				free.erase(free.begin() + r);
			}
			if (free.size() == 0) break;
		}
	}

	return true;
}

}
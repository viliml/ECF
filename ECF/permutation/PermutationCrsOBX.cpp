#include "../ECF_base.h"
#include "Permutation.h"
#include <map>


namespace Permutation
{

void PermutationCrsOBX::registerParameters(StateP state)
{
	myGenotype_->registerParameter(state, "crx.OBX", (voidP) new double(0), ECF::DOUBLE);
}


bool PermutationCrsOBX::initialize(StateP state)
{
	voidP sptr = myGenotype_->getParameterValue(state, "crx.OBX");
	probability_ = *((double*)sptr.get());
	return true;
}


bool PermutationCrsOBX::mate(GenotypeP gen1, GenotypeP gen2, GenotypeP child)
{
	PermutationP p1 = std::static_pointer_cast<Permutation>(gen1);
	PermutationP p2 = std::static_pointer_cast<Permutation>(gen2);
	PermutationP ch = std::static_pointer_cast<Permutation>(child);

	std::vector<int> selectedNum;
	std::map<int, int> numSelected;

	int index, selectedIndex, currentIndex;

	int rand = state_->getRandomizer()->getRandomInteger(p1->getSize()+1);

	selectedNum.resize(rand);

	for (int i = 0; i < (int) selectedNum.size(); i++) {  // izaberi brojeve za polje
		index = 0;
		while (numSelected[p1->variables[index]]) {  // na�i prvi ispravni index
		  index++;
	}

	selectedIndex = state_->getRandomizer()->getRandomInteger(p1->getSize()- i);
	currentIndex = 0;
	while ((index <  (int) p1->getSize()) && (currentIndex != selectedIndex)) {  // na�i izabrani broj
	  index++;
	  if (!numSelected[p1->variables[index]]) {
		currentIndex++;
	  }
	}
	numSelected[p1->variables[index]] = 1;
	}

	index = 0;
	for (int i = 0; i < (int) p1->getSize(); i++) {  // kopiraj selektirane brojeve u polje
		if (numSelected[p1->variables[i]]) {
		  selectedNum[index] = p1->variables[i];
		  index++;
		}
	}

	index = 0;
	for (int i = 0; i < (int) p1->getSize(); i++) {  // kopiraj ostatak druge permutacije i selektiranih brojeva u poretku prve permutacije
		if (numSelected[p2->variables[i]]) {
		  ch->variables[i] = selectedNum[index];
		  index++;
		} else {
			 ch->variables[i] = p2->variables[i];
		}
	}

	return true;
}

}
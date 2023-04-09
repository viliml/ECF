#include "../ECF_base.h"
#include <cmath>
#include "IntGenotype.h"

namespace IntGenotype
{
	
		bool IntGenotypeCrxOp::mate(GenotypeP gen1, GenotypeP gen2, GenotypeP child) {

			IntGenotypeP p1 = std::static_pointer_cast<IntGenotype>(gen1);
			IntGenotypeP p2 = std::static_pointer_cast<IntGenotype>(gen2);
			IntGenotypeP ch = std::static_pointer_cast<IntGenotype>(child);

			uint dimensionCrs = state_->getRandomizer()->getRandomInteger((int)p1->intValues.size());
			switch (state_->getRandomizer()->getRandomInteger(0, 1)) {
			case 0: for (uint i = 0; i < dimensionCrs; i++) {
						ch->intValues[i] = p1->intValues[i];
			}
					for (uint i = dimensionCrs; i < p2->intValues.size(); i++) {
						ch->intValues[i] = p2->intValues[i];
					}
					break;
			case 1: for (uint i = 0; i < dimensionCrs; i++) {
						ch->intValues[i] = p2->intValues[i];
			}
					for (uint i = dimensionCrs; i < p1->intValues.size(); i++) {
						ch->intValues[i] = p1->intValues[i];
					}
			}

			return true;
		}
	
}
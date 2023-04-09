#include "../ECF_base.h"
#include <cmath>
#include "IntGenotype.h"

namespace IntGenotype
{
	
		bool IntGenotypeCrxAverage::mate(GenotypeP gen1, GenotypeP gen2, GenotypeP child) {

			IntGenotypeP p1 = std::static_pointer_cast<IntGenotype>(gen1);
			IntGenotypeP p2 = std::static_pointer_cast<IntGenotype>(gen2);
			IntGenotypeP ch = std::static_pointer_cast<IntGenotype>(child);

			for (uint i = 0; i < p1->intValues.size(); i++) {
				ch->intValues[i] = (int) (0.5 * (p1->intValues[i]) + 0.5 * (p2->intValues[i]));
			}

			
			return true;
		}
	
}
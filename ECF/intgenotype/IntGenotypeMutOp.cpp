#include "../ECF_base.h"
#include <cmath>
#include "IntGenotype.h"

namespace IntGenotype
{
	
		bool IntGenotypeMutOp::mutate(GenotypeP gene)
		{
			IntGenotypeP gen = std::static_pointer_cast<IntGenotype>(gene);

			int a = state_->getRandomizer()->getRandomInteger(gen->intValues.size());
			gen->intValues[a] = state_->getRandomizer()->getRandomInteger(gen->getLBound(), gen->getUBound());

			return true;
		}
	
}
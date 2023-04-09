#include "../ECF_base.h"
#include "Binary.h"

namespace Binary
{

void BinaryCrsSegmented::registerParameters(StateP state)
{
	myGenotype_->registerParameter(state, "crx.segmented", (voidP) new double(0), ECF::DOUBLE);
}


bool BinaryCrsSegmented::initialize(StateP state)
{
	voidP sptr = myGenotype_->getParameterValue(state, "crx.segmented");
	probability_ = *((double*)sptr.get());
	return true;
}


bool BinaryCrsSegmented::mate(GenotypeP gen1, GenotypeP gen2, GenotypeP child)
{
	BinaryP p1 = std::static_pointer_cast<Binary>(gen1);
	BinaryP p2 = std::static_pointer_cast<Binary>(gen2);
	BinaryP ch = std::static_pointer_cast<Binary>(child);

	double s=0.2;

	for (uint dimension = 0; dimension < p1->variables.size(); dimension++)
	{
		uint parent = state_->getRandomizer()->getRandomInteger(0, 1);
		for (uint i = 0; i < p1->getNumBits(); i++)
		{
			// Uzmi bit iz trenutno odabranog roditelja
			if (parent==0)
			{
				ch->variables[dimension][i] = p1->variables[dimension][i];
			} else {
				ch->variables[dimension][i] = p2->variables[dimension][i];
			}

			// Sa 's' posto vjerojatnosti promjeni roditelja za sljedeći bit;
			// Sa (1-s) tekući roditelj ostaje nepromijenjen.
			double q = state_->getRandomizer()->getRandomDouble();
			if(q < s)
			{
				parent = 1 - parent;
			}
		}
	}

	ch->update();

	return true;
}

}

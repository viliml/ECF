#include <cmath>
#include <ECF/ECF.h>
#include "SymbRegEvalOp.h"


// called only once, before the evolution alg generates training data
bool SymbRegEvalOp::initialize(StateP state)
{
	nSamples = 10;
	double x = -10;
	for(uint i = 0; i < nSamples; i++) {
		domain.push_back(x);
		codomain.push_back(x + sin(x));
		x += 2;
	}

	useAPGenotype = false;
	GenotypeP activeGenotype = state->getGenotypes()[0];
	if(activeGenotype->getName() == "APGenotype")
		useAPGenotype = true;

	return true;
}


FitnessP SymbRegEvalOp::evaluate(IndividualP individual)
{
	// we try to minimize the function value, so we use FitnessMin fitness (for minimization problems)
	FitnessP fitness (new FitnessMin);

	// get the genotype we defined in the configuration file
	APGenotypeP apg = std::static_pointer_cast<Tree::APGenotype>(individual->getGenotype());

	TreeP tree;
	if (useAPGenotype)
		tree = apg->convertToPhenotype();
	else
		tree = std::static_pointer_cast<Tree::Tree>(individual->getGenotype());

	double value = 0;
	for(uint i = 0; i < nSamples; i++) {
		// for each test data instance, the x value (domain) must be set
		if(useAPGenotype)
			apg->setTerminalValue("X", &domain[i]);
		else
			tree->setTerminalValue("X", &domain[i]);
		// get the y value of the current tree
		double result;
		tree->execute(&result);
		// add the difference
		value += fabs(codomain[i] - result);
	}
	fitness->setValue(value);

	return fitness;
}

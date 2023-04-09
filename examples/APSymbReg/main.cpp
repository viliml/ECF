#include <ECF/ECF.h>
#include "SymbRegEvalOpAP.h"


int main(int argc, char **argv)
{
	StateP state (new State);

	// set the evaluation operator
	state->setEvalOp(new SymbRegEvalOpAP(0));

	state->initialize(argc, argv);
	state->run();

	// after the evolution: show best solution in Tree form
	std::vector<IndividualP> hof = state->getHoF()->getBest();
	IndividualP ind = hof[0];
	TreeP tree = static_pointer_cast<Tree::APGenotype>(ind->getGenotype())->convertToPhenotype();
	std::cout << tree->toString();

	return 0;
}

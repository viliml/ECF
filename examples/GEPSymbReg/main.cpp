#include <ECF/ECF.h>
#include "SymbRegEvalOpGEP.h"


int main(int argc, char **argv)
{
	StateP state (new State);

	// set the evaluation operator
	state->setEvalOp(new SymbRegEvalOpGEP(0));

	// initialize & run
	state->initialize(argc, argv);

	//XMLNode xInd = XMLNode::parseFile("./ind.xml", "Individual");
	//IndividualP ind = (IndividualP) new Individual(state);
	//ind->read(xInd);
	//ECF_LOG(state, 3, "TEST XML READ OUTPUT:\n"+ind->toString());

	state->run();
	return 0;
}

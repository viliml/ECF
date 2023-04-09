#include <ECF/ECF.h>
#include "SymbRegEvalOpTree.h"

int main(int argc, char **argv)
{
	StateP state (new State);

	// set the evaluation operator
	state->setEvalOp(new SymbRegEvalOpTree(0));

	state->initialize(argc, argv);
	state->run();

	return 0;
}

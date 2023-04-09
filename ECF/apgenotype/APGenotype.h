#ifndef APGENOTYPE_H_
#define APGENOTYPE_H_

#include "../ECF_base.h"

#include "../tree/Tree.h"
#include "../tree/PrimitiveSet.h"
#include "../tree/Primitive.h"

#include "../RealValueGenotype.h"
#include "../floatingpoint/FloatingPointMutSimple.h"
#include "../floatingpoint/FloatingPointCrsOnePoint.h"
#include "../floatingpoint/FloatingPointCrsArithmetic.h"
#include "../floatingpoint/FloatingPointCrsDiscrete.h"
#include "../floatingpoint/FloatingPointCrsArithmeticSimple.h"
#include "../floatingpoint/FloatingPointCrsArithmeticSingle.h"
#include "../floatingpoint/FloatingPointCrsAverage.h"
#include "../floatingpoint/FloatingPointCrsFlat.h"
#include "../floatingpoint/FloatingPointCrsBlx.h"
#include "../floatingpoint/FloatingPointCrsHeuristic.h"
#include "../floatingpoint/FloatingPointCrsRandom.h"
#include "../floatingpoint/FloatingPointCrsSbx.h"
#include "../floatingpoint/FloatingPointCrsBga.h"
#include "../floatingpoint/FloatingPointCrsLocal.h"
#include "../floatingpoint/FloatingPointCrsBlxAlpha.h"
#include "../floatingpoint/FloatingPointCrsBlxAlphaBeta.h"

#include "PrimitiveSetAP.h"
#include <vector>


namespace Tree {

/**
 * \defgroup apgenotype APGenotype
 * \ingroup genotypes
 */

/**
 * \ingroup genotypes apgenotype
 * \brief Analytical Programing genotype class - implements genotype as a vector of floating point values that translates to Tree genotype
 *
 * AP genotype parameters are:
 * - lbound: lower bound of represented real value (inherited from RealValueGenoptype)
 * - ubound: upper bound of represented real value (inherited from RealValueGenoptype)
 * - dimension: number of distinct real values (inherited from RealValueGenoptype)
 * - terminalset: set of variables (inherited from Tree)
 * - functionset: set of functions (inherited from Tree)
 */
class APGenotype : public RealValueGenotype {

public:

	PrimitiveSetAPP primitiveSet;
	std::vector<PrimitiveP> userFunctions_;
	std::vector<PrimitiveP> userTerminals_;

	StateP state_;

	std::vector<NodeP> nodes;

	uint toEnd;

	APGenotype()
	{
		name_ = "APGenotype";
	}

	void registerParameters(StateP);

	bool initialize(StateP state);
	virtual void initializeFirst(APGenotype* persistent);

	bool addFunction(PrimitiveP);
	bool addTerminal(PrimitiveP);

	void buildTree(std::vector<uint> indices, uint current, uint depth);

	std::vector<uint> getDiscreteIndices();
	TreeP convertToPhenotype();

	/// return lower bound of the defined interval
	double getLBound()
	{
		return minValue_;
	}

	/// return upper bound of the defined interval
	double getUBound()
	{
		return maxValue_;
	}

	GenotypeP copy()
	{
		return std::make_shared<APGenotype>(*this);
	}

	/// return usable crx operators
	std::vector<CrossoverOpP> getCrossoverOp()
	{
		std::vector<CrossoverOpP> crx;
		crx.push_back(std::make_shared<FloatingPoint::FloatingPointCrsOnePoint>());
		crx.push_back(std::make_shared<FloatingPoint::FloatingPointCrsArithmetic>());
		crx.push_back(std::make_shared<FloatingPoint::FloatingPointCrsDiscrete>());
		crx.push_back(std::make_shared<FloatingPoint::FloatingPointCrsArithmeticSimple>());
		crx.push_back(std::make_shared<FloatingPoint::FloatingPointCrsArithmeticSingle>());
		crx.push_back(std::make_shared<FloatingPoint::FloatingPointCrsAverage>());
		crx.push_back(std::make_shared<FloatingPoint::FloatingPointCrsFlat>());
		crx.push_back(std::make_shared<FloatingPoint::FloatingPointCrsHeuristic>());
		crx.push_back(std::make_shared<FloatingPoint::FloatingPointCrsSbx>());
		crx.push_back(std::make_shared<FloatingPoint::FloatingPointCrsBga>());
		crx.push_back(std::make_shared<FloatingPoint::FloatingPointCrsLocal>());
		crx.push_back(std::make_shared<FloatingPoint::FloatingPointCrsBlxAlpha>());
		crx.push_back(std::make_shared<FloatingPoint::FloatingPointCrsBlxAlphaBeta>());
		// control operator - not to be used in optimization
		//crx.push_back(std::make_shared<FloatingPointCrsRandom>());
		return crx;
	}

	/// return usable mut operators
	std::vector<MutationOpP> getMutationOp() override
	{
		std::vector<MutationOpP> mut;
		mut.push_back(std::make_shared<FloatingPoint::FloatingPointMutSimple>());
		return mut;
	}

    void setTerminalValue(const std::string &name, void* value);
    void setTerminalValue(uint name, void* value);
    uint getTerminalIndex(const std::string &name);

	void write(XMLNode& xFloatingPoint);
	void read(XMLNode& xFloatingPoint);
};

}

typedef std::shared_ptr<Tree::APGenotype> APGenotypeP;
#endif

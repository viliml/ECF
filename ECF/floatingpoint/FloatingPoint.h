#ifndef FLOATINGPOINT_H_
#define FLOATINGPOINT_H_

#include "../RealValueGenotype.h"
#include "FloatingPointMutSimple.h"
#include "FloatingPointCrsOnePoint.h"
#include "FloatingPointCrsArithmetic.h"
#include "FloatingPointCrsDiscrete.h"
#include "FloatingPointCrsArithmeticSimple.h"
#include "FloatingPointCrsArithmeticSingle.h"
#include "FloatingPointCrsAverage.h"
#include "FloatingPointCrsFlat.h"
#include "FloatingPointCrsBlx.h"
#include "FloatingPointCrsHeuristic.h"
#include "FloatingPointCrsRandom.h"
#include "FloatingPointCrsSbx.h"
#include "FloatingPointCrsBga.h"
#include "FloatingPointCrsLocal.h"
#include "FloatingPointCrsBlxAlpha.h"
#include "FloatingPointCrsBlxAlphaBeta.h"

namespace FloatingPoint
{

/**
 * \defgroup flpoint FloatingPoint
 * \ingroup genotypes
 */

/**
 * \ingroup genotypes flpoint
 * \brief FloatingPoint class - implements genotype as a vector of floating point values
 *
 * FloatingPoint genotype parameters are (inherited from RealValueGenoptype):
 * - lbound: lower bound of represented real value
 * - ubound: upper bound of represented real value
 * - dimension: number of distinct real values
 */
class FloatingPoint: public RealValueGenotype {

public:

	FloatingPoint ()
	{	name_="FloatingPoint";	}

	bool initialize (StateP state);

	void registerParameters(StateP state);

	/// return lower bound of the defined interval
	double getLBound ()
	{	return minValue_;	}

	/// return upper bound of the defined interval
	double getUBound ()
	{	return maxValue_;	}

	GenotypeP copy() override
	{
		return std::make_shared<FloatingPoint>(*this);
	}

	/// return usable crx operators
	std::vector<CrossoverOpP> getCrossoverOp()
	{
		std::vector<CrossoverOpP> crx;
		crx.push_back(std::make_shared<FloatingPointCrsOnePoint>());
		crx.push_back(std::make_shared<FloatingPointCrsArithmetic>());
		crx.push_back(std::make_shared<FloatingPointCrsDiscrete>());
		crx.push_back(std::make_shared<FloatingPointCrsArithmeticSimple>());
		crx.push_back(std::make_shared<FloatingPointCrsArithmeticSingle>());
		crx.push_back(std::make_shared<FloatingPointCrsAverage>());
		crx.push_back(std::make_shared<FloatingPointCrsFlat>());
		crx.push_back(std::make_shared<FloatingPointCrsHeuristic>());
		crx.push_back(std::make_shared<FloatingPointCrsSbx>());
		crx.push_back(std::make_shared<FloatingPointCrsBga>());
		crx.push_back(std::make_shared<FloatingPointCrsLocal>());
		crx.push_back(std::make_shared<FloatingPointCrsBlxAlpha>());
		crx.push_back(std::make_shared<FloatingPointCrsBlxAlphaBeta>());
		// control operator - not to be used in optimization
		//crx.push_back(std::make_shared<FloatingPointCrsRandom>());
		return crx;
	}

	std::vector<MutationOpP> getMutationOp()
	{
		std::vector<MutationOpP> mut;
		mut.push_back(std::make_shared<FloatingPointMutSimple>());
		return mut;
	}

	void write(XMLNode& xFloatingPoint);
	void read(XMLNode& xFloatingPoint);
};
}

typedef std::shared_ptr<FloatingPoint::FloatingPoint> FloatingPointP;
#endif
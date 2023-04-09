#ifndef PERMUTATION_H_
#define PERMUTATION_H_

#include "PermutationCrsPMX.h"
#include "PermutationMutToggle.h"
#include "PermutationMutIns.h"
#include "PermutationMutInv.h"
#include "PermutationCrsPBX.h"
#include "PermutationCrsOX.h"
#include "PermutationCrsCOSA.h"
#include "PermutationCrsCyclic.h"
#include "PermutationCrsCyclic2.h"
#include "PermutationCrsOBX.h"
#include "PermutationCrsULX.h"
#include "PermutationCrsOX2.h"
#include "PermutationCrsOPX.h"
#include "PermutationCrsSPX.h"
#include "PermutationCrsDPX.h"
#include "PermutationCrsUPMX.h"


#include "../Genotype.h"


namespace Permutation
{

/**
 * \defgroup permutation Permutation
 * \ingroup genotypes
 */

/**
 * \ingroup genotypes permutation
 * \brief Permutation class - implements genotype as a vector of indices 0..(n-1) (permutation of indices)
 */
class Permutation: public Genotype {
protected:
	uint size_;	//!< permutation vector size
public:
	typedef std::vector<int> var;
	var variables;

	Permutation () {name_ = "Permutation";}

	uint getSize()	//!< return size of indices vector
	{	return size_;	}

	bool initialize (StateP state);

	void registerParameters(StateP state);

	GenotypeP copy()
	{
		return std::make_shared<Permutation>(*this);
	}

	std::vector<CrossoverOpP> getCrossoverOp()
	{
		std::vector<CrossoverOpP> crx;
		crx.push_back(std::make_shared<PermutationCrsPMX>());
		crx.push_back(std::make_shared<PermutationCrsPBX>());
		crx.push_back(std::make_shared<PermutationCrsOX>());
		crx.push_back(std::make_shared<PermutationCrsCOSA>());
		crx.push_back(std::make_shared<PermutationCrsCyclic>());
		crx.push_back(std::make_shared<PermutationCrsCyclic2>());
		crx.push_back(std::make_shared<PermutationCrsOBX>());
		crx.push_back(std::make_shared<PermutationCrsULX>());
		crx.push_back(std::make_shared<PermutationCrsOX2>());
		crx.push_back(std::make_shared<PermutationCrsOPX>());
		crx.push_back(std::make_shared<PermutationCrsSPX>());
		crx.push_back(std::make_shared<PermutationCrsDPX>());
		crx.push_back(std::make_shared<PermutationCrsUPMX>());
		return crx;
	}

	std::vector<MutationOpP> getMutationOp()
	{
		std::vector<MutationOpP> mut;
		mut.push_back(std::make_shared<PermutationMutToggle>());
		mut.push_back(std::make_shared<PermutationMutIns>());
		mut.push_back(std::make_shared<PermutationMutInv>());
		return mut;

	}

	void write(XMLNode&);
	void read(XMLNode&);
};
}

typedef std::shared_ptr<Permutation::Permutation> PermutationP;
#endif

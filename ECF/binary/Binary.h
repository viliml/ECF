#ifndef BINARY_H_
#define BINARY_H_

#include "BinaryCrsOnePoint.h"
#include "BinaryCrsTwoPoint.h"
#include "BinaryMutSimple.h"
#include "BinaryMutMix.h"
#include "BinaryCrsUniform.h"
#include "BinaryCrsHalfUniform.h"
#include "BinaryCrsReducedSurrogate.h"
#include "BinaryCrsSegmented.h"
#include "BinaryCrsShuffle.h"
#include "BinaryCrsNonGeometric.h"
#include "BinaryCrsRandomRespectful.h"
#include "BinaryCrsMasked.h"

#include "../RealValueGenotype.h"

namespace Binary
{

/**
 * \defgroup binary Binary
 * \ingroup genotypes
 */

/**
 * \ingroup genotypes binary
 * \brief Binary class - implements genotype as a vector of binary coded real values with variable interval and precision
 *
 * Binary genotype parameters are (the first 3 are inherited from RealValueGenoptype):
 * - lbound: lower bound of represented real value
 * - ubound: upper bound of represented real value
 * - dimension: number of distinct real values, each coded with previous 3 parameters
 * - precision: desired number of digits (after the decimal point) to be represented
 * - rounding: whether the represented real value is rounded to 'precision' digits (false by default)
 */
class Binary: public RealValueGenotype {
	friend class BinaryMutSimple;	// za potrebe ad-hoc lokalnog operatora!
protected:
	uint nDecimal_;                   //!< number of digits after the decimal point
	uint nBits_;                      //!< number of bits for a single dimension
	long potention_;
	bool bRounding_;                  //!< use rounding with 'precision' digits on real values in the chromosome
	typedef std::vector<bool> v_bool;
	v_bool vBool_;                    //!< temporary bool vector 

	double logbase(double a, double base);
	double round(double, int);

public:
	std::vector<long int> decValue;    //!< integer values of bit representation
	std::vector<v_bool> variables;     //!< vector of bit vectors

	Binary ()
	{	name_ = "Binary";	}

	/// Return number of bits used in a single dimension in real domain.
	uint getNumBits()
	{	return nBits_;	}

	bool initialize (StateP state) override;

	void registerParameters(StateP state) override;

	/// Update genotype after genetic material change via genetic operators.
	bool update () override;

	GenotypeP copy() override
	{
		return std::make_shared<Binary>(*this);
	}

	std::vector<CrossoverOpP> getCrossoverOp() override
	{
		std::vector<CrossoverOpP> crx;
		crx.push_back(std::make_shared<BinaryCrsOnePoint>());
		crx.push_back(std::make_shared<BinaryCrsTwoPoint>());
		crx.push_back(std::make_shared<BinaryCrsUniform>());
		crx.push_back(std::make_shared<BinaryCrsHalfUniform>());
		crx.push_back(std::make_shared<BinaryCrsReducedSurrogate>());
		crx.push_back(std::make_shared<BinaryCrsSegmented>());
		crx.push_back(std::make_shared<BinaryCrsShuffle>());
		crx.push_back(std::make_shared<BinaryCrsNonGeometric>());
		crx.push_back(std::make_shared<BinaryCrsRandomRespectful>());
		// TODO: reimplement
		//crx.push_back(std::make_shared<BinaryCrsMasked>());
		return crx;
	}

	std::vector<MutationOpP> getMutationOp() override
	{	
		std::vector<MutationOpP> mut;
        mut.push_back(std::make_shared<BinaryMutSimple>());
        mut.push_back(std::make_shared<BinaryMutMix>());
		return mut;
	}

	void write(XMLNode& xBinary) override;

	void read(XMLNode& xBinary) override;
};

}
typedef std::shared_ptr<Binary::Binary> BinaryP;
#endif

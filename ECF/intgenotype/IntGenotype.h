#include "../Genotype.h"
#include <cmath>
#include <sstream>

#include "IntGenotypeCrxOp.h"
#include "IntGenotypeCrxTwoPoint.h"
#include "IntGenotypeCrxAverage.h"
#include "IntGenotypeMutOp.h"

namespace IntGenotype
{

	/**
	 * \defgroup intgenotype IntGenotype
	 * \ingroup genotypes
	 */

	 /**
	  * \ingroup intgenotype genotypes
	  * \brief IntGenotype class - implements genotype as a vector of int values
	  */
	class IntGenotype : public Genotype
	{
	public:
		int minValue_, maxValue_;
		uint nSize_;
		std::vector<int> intValues;

		IntGenotype()
		{
			name_ = "IntGenotype";
		}

		GenotypeP copy()
		{
			return std::make_shared<IntGenotype>(*this);
		}

		/// return lower bound of the defined interval
		int getLBound()
		{
			return minValue_;
		}

		/// return upper bound of the defined interval
		int getUBound()
		{
			return maxValue_;
		}
		std::vector<CrossoverOpP> getCrossoverOp()
		{
			std::vector<CrossoverOpP> crx;
			crx.push_back(std::make_shared<IntGenotypeCrxOp>());
			crx.push_back(std::make_shared<IntGenotypeCrxTwoPoint>());
			crx.push_back(std::make_shared<IntGenotypeCrxAverage>());
			return crx;
		}

		std::vector<MutationOpP> getMutationOp()
		{
			std::vector<MutationOpP> mut;
			mut.push_back(std::make_shared<IntGenotypeMutOp>());
			return mut;
		}

		void registerParameters(StateP state);

		bool initialize(StateP state);

		void write(XMLNode &xIntGenotype);

		// mandatory if running parallel ECF or reading population from a milestone file
		void read(XMLNode& xIntGenotype);
	};
}

typedef std::shared_ptr<IntGenotype::IntGenotype> IntGenotypeP;

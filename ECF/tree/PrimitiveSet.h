#ifndef PrimitiveSet_h
#define PrimitiveSet_h
#include <vector>
#include <unordered_map>
#include "Primitive.h"


namespace Tree
{

/**
 * \ingroup genotypes tree
 * \brief Primitive set class: collects all Tree Primitives.
 *
 * Each Tree genotype (if there are more Trees in the Individual) has a unique PrimitiveSet. 
 * Each unique instance is linked to the appropriate Tree object in State (the 'hometree' variable name).
 */
class PrimitiveSet
{
	friend class Tree;
public:
	PrimitiveSet();
	virtual ~PrimitiveSet();

	bool initialize(StateP state);

	//void addFunction(PrimitiveP functionPrimitive);
	bool addFunction(const std::string& name);
	void addTerminal(const PrimitiveP& terminalPrimitive);

	PrimitiveP getRandomTerminal();
	PrimitiveP getRandomFunction();
	PrimitiveP getRandomPrimitive();

    PrimitiveP getTerminalByName(const std::string& name);
    PrimitiveP getFunctionByName(const std::string& name);
    PrimitiveP getPrimitiveByName(const std::string& name);

    int getTerminalIndex(const std::string& name);
    int getFunctionIndex(const std::string& name);
    int getPrimitiveIndex(const std::string& name);

    PrimitiveP getTerminalByIndex(uint index);
    PrimitiveP getFunctionByIndex(uint index);
    PrimitiveP getPrimitiveByIndex(uint index);
	
	uint getFunctionSetSize();
	uint getTerminalSetSize();
	uint getPrimitivesSize();

	std::unordered_map <std::string, PrimitiveP> mAllPrimitives_;                 //!< map of all registered primitive functions
	std::unordered_map <std::string, Primitives::terminal_type> mTypeNames_;

protected:
	StateP state_;

	std::vector<PrimitiveP> terminalSet_;                               //!< vector of active (actual used) terminals
    std::unordered_map <std::string, PrimitiveP> mTerminalSet_;         //!< map of active (actual used) terminals
    std::unordered_map <std::string, uint> iTerminalSet_;               //!< map of active (actual used) terminal indices
	std::vector<PrimitiveP> functionSet_;                               //!< vector of active (actual used) functions
	std::unordered_map <std::string, PrimitiveP> mFunctionSet_;         //!< map of active (actual used) functions
    std::unordered_map <std::string, uint> iFunctionSet_;               //!< map of active (actual used) function indices
	std::vector<PrimitiveP> primitives_;                                //!< vector of active (actual used) primitives
	std::unordered_map <std::string, PrimitiveP> mPrimitiveSet_;        //!< map of active (actual used) primitives
    std::unordered_map <std::string, uint> iPrimitiveSet_;              //!< map of active (actual used) primitive indices
};
typedef std::shared_ptr<PrimitiveSet> PrimitiveSetP;

}
#endif

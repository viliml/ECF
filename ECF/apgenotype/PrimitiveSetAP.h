#ifndef PrimitiveSetAP_h
#define PrimitiveSetAP_h
#include <vector>
#include <unordered_map>
#include "../ECF_base.h"
#include "../tree/Primitive.h"


namespace Tree
{

	/**
	 * \ingroup genotypes tree
	 * \brief Primitive set class for APGenotype: collects all Tree Primitives.
	 *
	 * Each Tree genotype (if there are more Trees in the Individual) has a unique PrimitiveSet.
	 * Each unique instance is linked to the appropriate Tree object in State (the 'hometree' variable name).
	 */
	class PrimitiveSetAP
	{
		
	public:
		PrimitiveSetAP();
		virtual ~PrimitiveSetAP();

		bool initialize(StateP state);

		//void addFunction(PrimitiveP functionPrimitive);
		bool addFunction(const std::string& name);
		void addTerminal(const PrimitiveP& terminalPrimitive);

        PrimitiveP getTerminalByName(const std::string &name);
        PrimitiveP getGFSOneByName(const std::string &name);
        PrimitiveP getGFSTwoByName(const std::string &name);
        PrimitiveP getPrimitiveByName(const std::string &name);

        int getTerminalIndex(const std::string &name);
        int getGFSOneIndex(const std::string &name);
        int getGFSTwoIndex(const std::string &name);
        int getPrimitiveIndex(const std::string &name);

		PrimitiveP getTerminalByIndex(uint index);
		PrimitiveP getGFSOneByIndex(uint index);
		PrimitiveP getGFSTwoByIndex(uint index);
		PrimitiveP getPrimitiveByIndex(uint index);

		uint getGFSOneSetSize();
		uint getGFSTwoSetSize();
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
		std::vector<PrimitiveP> GFSOneSet_;                                 //!< vector of active (actual used) functions
		std::unordered_map <std::string, PrimitiveP> mGFSOneSet_;           //!< map of active (actual used) functions
        std::unordered_map <std::string, uint> iGFSOneSet_;                 //!< map of active (actual used) function indices
		std::vector<PrimitiveP> GFSTwoSet_;                                 //!< vector of active (actual used) functions
		std::unordered_map <std::string, PrimitiveP> mGFSTwoSet_;           //!< map of active (actual used) functions
        std::unordered_map <std::string, uint> iGFSTwoSet_;                 //!< map of active (actual used) function indices
		std::vector<PrimitiveP> primitives_;                                //!< vector of active (actual used) primitives
		std::unordered_map <std::string, PrimitiveP> mPrimitiveSet_;        //!< map of active (actual used) primitives
        std::unordered_map <std::string, uint> iPrimitiveSet_;              //!< map of active (actual used) primitive indices
	};
	typedef std::shared_ptr<PrimitiveSetAP> PrimitiveSetAPP;

}
#endif
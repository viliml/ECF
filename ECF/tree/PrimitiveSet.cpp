#include "../ECF_base.h"
#include "Tree.h"


namespace Tree {

PrimitiveSet::PrimitiveSet() {}


PrimitiveSet::~PrimitiveSet() {}


bool PrimitiveSet::initialize(StateP state) {
    state_ = state;

    // register existing primitives
    PrimitiveP prim = (PrimitiveP) (new Primitives::Add);
    mAllPrimitives_[prim->getName()] = prim;
    prim = (PrimitiveP) (new Primitives::Sub);
    mAllPrimitives_[prim->getName()] = prim;
    prim = (PrimitiveP) (new Primitives::Mul);
    mAllPrimitives_[prim->getName()] = prim;
    prim = (PrimitiveP) (new Primitives::Div);
    mAllPrimitives_[prim->getName()] = prim;
    prim = (PrimitiveP) (new Primitives::Sin);
    mAllPrimitives_[prim->getName()] = prim;
    prim = (PrimitiveP) (new Primitives::Cos);
    mAllPrimitives_[prim->getName()] = prim;
    prim = (PrimitiveP) (new Primitives::Pos);
    mAllPrimitives_[prim->getName()] = prim;
    prim = (PrimitiveP) (new Primitives::Neg);
    mAllPrimitives_[prim->getName()] = prim;
    prim = (PrimitiveP) (new Primitives::Max);
    mAllPrimitives_[prim->getName()] = prim;
    prim = (PrimitiveP) (new Primitives::Min);
    mAllPrimitives_[prim->getName()] = prim;
    prim = (PrimitiveP) (new Primitives::Pow);
    mAllPrimitives_[prim->getName()] = prim;
    prim = (PrimitiveP) (new Primitives::Root);
    mAllPrimitives_[prim->getName()] = prim;
    prim = (PrimitiveP) (new Primitives::Exp);
    mAllPrimitives_[prim->getName()] = prim;
    prim = (PrimitiveP) (new Primitives::Log);
    mAllPrimitives_[prim->getName()] = prim;

    for (auto& primIter: mAllPrimitives_)
        primIter.second->initialize(state);

    // register terminal types
    mTypeNames_.insert(std::pair<std::string, Primitives::terminal_type>("DOUBLE", Primitives::Double));
    mTypeNames_.insert(std::pair<std::string, Primitives::terminal_type>("INT", Primitives::Int));
    mTypeNames_.insert(std::pair<std::string, Primitives::terminal_type>("BOOL", Primitives::Bool));
    mTypeNames_.insert(std::pair<std::string, Primitives::terminal_type>("CHAR", Primitives::Char));
    mTypeNames_.insert(std::pair<std::string, Primitives::terminal_type>("STRING", Primitives::String));

    return true;
}


/// Get random function from the set of active functions.
PrimitiveP PrimitiveSet::getRandomFunction() {
    return functionSet_[state_->getRandomizer()->getRandomInteger((int) functionSet_.size())];
}


/// Get random terminal from the set of active terminals.
PrimitiveP PrimitiveSet::getRandomTerminal() {
    return terminalSet_[state_->getRandomizer()->getRandomInteger((int) terminalSet_.size())];
}


/// Get random primitive (function or terminal) from the set of active primitives.
PrimitiveP PrimitiveSet::getRandomPrimitive() {
    return primitives_[state_->getRandomizer()->getRandomInteger((int) primitives_.size())];
}


/// Access function by name (active functions only).
PrimitiveP PrimitiveSet::getFunctionByName(const std::string &name) {
    auto iter = mFunctionSet_.find(name);
    if (iter == mFunctionSet_.end())
        return PrimitiveP();

    return iter->second;
}


/// Access terminal by name (active terminals only).
PrimitiveP PrimitiveSet::getTerminalByName(const std::string &name) {
    auto iter = mTerminalSet_.find(name);
    if (iter == mTerminalSet_.end())
        return PrimitiveP();

    return iter->second;
}


/// Find primitive by name (active functions or terminals only).
PrimitiveP PrimitiveSet::getPrimitiveByName(const std::string &name) {
    auto iter = mPrimitiveSet_.find(name);
    if (iter == mPrimitiveSet_.end())
        return PrimitiveP();

    return iter->second;
}


/// Index function by name (active functions only).
int PrimitiveSet::getFunctionIndex(const std::string &name) {
    auto iter = iFunctionSet_.find(name);
    if (iter == iFunctionSet_.end())
        return -1;

    return iter->second;
}


/// Index terminal by name (active terminals only).
int PrimitiveSet::getTerminalIndex(const std::string &name) {
    auto iter = iTerminalSet_.find(name);
    if (iter == iTerminalSet_.end())
        return -1;

    return iter->second;
}


/// Index primitive by name (active functions or terminals only).
int PrimitiveSet::getPrimitiveIndex(const std::string &name) {
    auto iter = iPrimitiveSet_.find(name);
    if (iter == iPrimitiveSet_.end())
        return -1;

    return iter->second;
}


/// Access function by name (active functions only).
PrimitiveP PrimitiveSet::getFunctionByIndex(uint index) {
    return functionSet_[index % functionSet_.size()];
}


/// Access terminal by name (active terminals only).
PrimitiveP PrimitiveSet::getTerminalByIndex(uint index) {
    return terminalSet_[index % terminalSet_.size()];
}


/// Find primitive by name (active functions or terminals only).
PrimitiveP PrimitiveSet::getPrimitiveByIndex(uint index) {
    return primitives_[index % primitives_.size()];
}


//void PrimitiveSet::addFunction(PrimitiveP functionPrimitive)
//{
//	if(functionPrimitive->getNumberOfArguments() == 0) {
//		terminalSet_.push_back(functionPrimitive);
//		mTerminalSet_[functionPrimitive->getName()] = functionPrimitive;
//	}
//	else {
//		functionSet_.push_back(functionPrimitive);
//		mFunctionSet_[functionPrimitive->getName()] = functionPrimitive;
//	}
//
//	primitives_.push_back(functionPrimitive);
//	mPrimitives_[functionPrimitive->getName()] = functionPrimitive;
//}


/**
 * \brief	Add a function primitive to the set of active primitives - if found by name in collection of all primitives.
 * If a function takes 0 arguments, it is added to the terminal set.
 */
bool PrimitiveSet::addFunction(const std::string& name) {
    auto iter = mAllPrimitives_.find(name);
    if (iter == mAllPrimitives_.end())
        return false;

    if (iter->second->getNumberOfArguments() == 0) {
        iTerminalSet_[iter->first] = terminalSet_.size();
        terminalSet_.push_back(iter->second);
        mTerminalSet_[iter->first] = iter->second;
    } else {
        iFunctionSet_[iter->first] = functionSet_.size();
        functionSet_.push_back(iter->second);
        mFunctionSet_[iter->first] = iter->second;
    }

    iPrimitiveSet_[iter->first] = primitives_.size();
    primitives_.push_back(iter->second);
    mPrimitiveSet_[iter->first] = iter->second;

    return true;
}


/**
 * \brief	Add a terminal primitive to the set of active primitives.
 */
void PrimitiveSet::addTerminal(const PrimitiveP& terminalPrimitive) {
    iTerminalSet_[terminalPrimitive->getName()] = terminalSet_.size();
    terminalSet_.push_back(terminalPrimitive);
    mTerminalSet_[terminalPrimitive->getName()] = terminalPrimitive;

    iPrimitiveSet_[terminalPrimitive->getName()] = primitives_.size();
    primitives_.push_back(terminalPrimitive);
    mPrimitiveSet_[terminalPrimitive->getName()] = terminalPrimitive;
}


/// Get the number of active functions.
uint PrimitiveSet::getFunctionSetSize() {
    return (uint) functionSet_.size();
}


/// Get the number of active terminals.
uint PrimitiveSet::getTerminalSetSize() {
    return (uint) terminalSet_.size();
}


/// Get the number of active primitives (functions and terminals).
uint PrimitiveSet::getPrimitivesSize() {
    return (uint) primitives_.size();
}

}
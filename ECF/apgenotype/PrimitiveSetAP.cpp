#include "PrimitiveSetAP.h"
#include "../tree/Tree.h"
#include "../tree/Primitive.h"


namespace Tree {

    PrimitiveSetAP::PrimitiveSetAP() {}


    PrimitiveSetAP::~PrimitiveSetAP() {}


    bool PrimitiveSetAP::initialize(StateP state) {
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

        for (auto &primIter: mAllPrimitives_)
            primIter.second->initialize(state);

        // register terminal types
        mTypeNames_.insert(std::pair<std::string, Primitives::terminal_type>("DOUBLE", Primitives::Double));
        mTypeNames_.insert(std::pair<std::string, Primitives::terminal_type>("INT", Primitives::Int));
        mTypeNames_.insert(std::pair<std::string, Primitives::terminal_type>("BOOL", Primitives::Bool));
        mTypeNames_.insert(std::pair<std::string, Primitives::terminal_type>("CHAR", Primitives::Char));
        mTypeNames_.insert(std::pair<std::string, Primitives::terminal_type>("STRING", Primitives::String));

        return true;
    }


    /// Access function by name (active functions only).
    PrimitiveP PrimitiveSetAP::getGFSOneByName(const std::string &name) {
        auto iter = mGFSOneSet_.find(name);
        if (iter == mGFSOneSet_.end())
            return PrimitiveP();

        return iter->second;
    }

    /// Access function by name (active functions only).
    PrimitiveP PrimitiveSetAP::getGFSTwoByName(const std::string &name) {
        auto iter = mGFSTwoSet_.find(name);
        if (iter == mGFSTwoSet_.end())
            return PrimitiveP();

        return iter->second;
    }


    /// Access terminal by name (active terminals only).
    PrimitiveP PrimitiveSetAP::getTerminalByName(const std::string &name) {
        auto iter = mTerminalSet_.find(name);
        if (iter == mTerminalSet_.end())
            return PrimitiveP();

        return iter->second;
    }


    /// Access primitive by name (active functions or terminals only).
    PrimitiveP PrimitiveSetAP::getPrimitiveByName(const std::string &name) {
        auto iter = mPrimitiveSet_.find(name);
        if (iter == mPrimitiveSet_.end())
            return PrimitiveP();

        return iter->second;
    }


    /// Index function by name (active functions only).
    int PrimitiveSetAP::getGFSOneIndex(const std::string &name) {
        auto iter = iGFSOneSet_.find(name);
        if (iter == iGFSOneSet_.end())
            return -1;

        return iter->second;
    }

    /// Index function by name (active functions only).
    int PrimitiveSetAP::getGFSTwoIndex(const std::string &name) {
        auto iter = iGFSTwoSet_.find(name);
        if (iter == iGFSTwoSet_.end())
            return -1;

        return iter->second;
    }


    /// Index terminal by name (active terminals only).
    int PrimitiveSetAP::getTerminalIndex(const std::string &name) {
        auto iter = iTerminalSet_.find(name);
        if (iter == iTerminalSet_.end())
            return -1;

        return iter->second;
    }


    /// Index primitive by name (active functions or terminals only).
    int PrimitiveSetAP::getPrimitiveIndex(const std::string &name) {
        auto iter = iPrimitiveSet_.find(name);
        if (iter == iPrimitiveSet_.end())
            return -1;

        return iter->second;
    }

    PrimitiveP PrimitiveSetAP::getTerminalByIndex(uint index) {
        return terminalSet_[index % terminalSet_.size()];
    }

    PrimitiveP PrimitiveSetAP::getGFSOneByIndex(uint index) {
        return GFSOneSet_[index % GFSOneSet_.size()];
    }

    PrimitiveP PrimitiveSetAP::getGFSTwoByIndex(uint index) {
        return GFSTwoSet_[index % GFSTwoSet_.size()];
    }

    PrimitiveP PrimitiveSetAP::getPrimitiveByIndex(uint index) {
        return primitives_[index % primitives_.size()];
    }


    /**
     * \brief	Add a function primitive to the set of active primitives - if found by name in collection of all primitives.
     * If a function takes 0 arguments, it is added to the terminal set.
     */
    bool PrimitiveSetAP::addFunction(const std::string& name) {
        auto iter = mAllPrimitives_.find(name);
        if (iter == mAllPrimitives_.end())
            return false;

        int argNum = iter->second->getNumberOfArguments();

        if (argNum == 0) {
            iTerminalSet_[iter->first] = terminalSet_.size();
            terminalSet_.push_back(iter->second);
            mTerminalSet_[iter->first] = iter->second;
        } else if (argNum == 1) {
            iGFSOneSet_[iter->first] = GFSOneSet_.size();
            GFSOneSet_.push_back(iter->second);
            mGFSOneSet_[iter->first] = iter->second;
        } else if (argNum == 2) {
            iGFSTwoSet_[iter->first] = GFSTwoSet_.size();
            GFSTwoSet_.push_back(iter->second);
            mGFSTwoSet_[iter->first] = iter->second;
        }

        iPrimitiveSet_[iter->first] = primitives_.size();
        primitives_.push_back(iter->second);
        mPrimitiveSet_[iter->first] = iter->second;

        return true;
    }


    /**
     * \brief	Add a terminal primitive to the set of active primitives.
     */
    void PrimitiveSetAP::addTerminal(const PrimitiveP& terminalPrimitive) {
        iTerminalSet_[terminalPrimitive->getName()] = terminalSet_.size();
        terminalSet_.push_back(terminalPrimitive);
        mTerminalSet_[terminalPrimitive->getName()] = terminalPrimitive;

        iPrimitiveSet_[terminalPrimitive->getName()] = primitives_.size();
        primitives_.push_back(terminalPrimitive);
        mPrimitiveSet_[terminalPrimitive->getName()] = terminalPrimitive;
    }


    uint PrimitiveSetAP::getFunctionSetSize() {
        return getGFSOneSetSize() + getGFSTwoSetSize();
    }

    uint PrimitiveSetAP::getGFSOneSetSize() {
        return (uint) GFSOneSet_.size();
    }

    uint PrimitiveSetAP::getGFSTwoSetSize() {
        return (uint) GFSTwoSet_.size();
    }

    /// Get the number of active terminals.
    uint PrimitiveSetAP::getTerminalSetSize() {
        return (uint) terminalSet_.size();
    }

    /// Get the number of active primitives (functions and terminals).
    uint PrimitiveSetAP::getPrimitivesSize() {
        return (uint) primitives_.size();
    }

}
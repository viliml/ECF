#ifndef SEMINAR_SYMBREGEVALOPGEP_H
#define SEMINAR_SYMBREGEVALOPGEP_H
#include "ECF/ECF.h"
#include "utility/expression_evaluation.h"
#include "utility/measures.h"
#include "utility/fileparser.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
class SymbRegEvalOpGEP : public EvaluateOp
{
private:
    int index;
    std::vector<std::vector<double>> inputs;
    std::vector<double> output;
    std::vector<double> kappaOutput;
    std::vector<double> thetaOutput;
    std::string equation;
    double softTargetBeta;
    double softTargetGamma;
    bool softTarget = false;
    void addConstants(uint nConstants);
public:
    explicit SymbRegEvalOpGEP(int index): index(index) {}
    void registerParameters(StateP stateP);
    bool initialize(StateP stateP);
    FitnessP evaluate(IndividualP individual);
};
#endif //SEMINAR_SYMBREGEVALOPGEP_H

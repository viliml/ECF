#include "SymbRegEvalOpTree.h"
#include "utility/utilityrng.h"
#include <iostream>

void SymbRegEvalOpTree::addConstants(uint nConstants) {
    std::uniform_real_distribution<double> distribution(-10.0, 10.0);
    for (auto &elem: inputs) {
        for (uint i = 0; i < nConstants; i++) {
            elem.push_back(rng::get_uniform_random_double(distribution));
        }
    }
}

void SymbRegEvalOpTree::registerParameters(StateP stateP) {
    stateP->getRegistry()->registerEntry("training.infile", (voidP)
    new (std::string), ECF::STRING);
    stateP->getRegistry()->registerEntry("expression.infile", (voidP)
    new(std::string), ECF::STRING);
    stateP->getRegistry()->registerEntry("softtarget", (voidP)
    new(std::string), ECF::STRING);
    stateP->getRegistry()->registerEntry("softtarget.gamma", (voidP)
    new(std::string), ECF::STRING);
    stateP->getRegistry()->registerEntry("softtarget.beta", (voidP)
    new(std::string), ECF::STRING);
}

bool SymbRegEvalOpTree::initialize(StateP stateP) {
    if (!stateP->getRegistry()->isModified("expression.infile")) {
        ECF_LOG_ERROR(stateP,
                      "Expression is not registered as a parameter. Register a path to a expression in parameters.txt file.");
        return false;
    }
    voidP vp1 = stateP->getRegistry()->getEntry("expression.infile");
    std::string path1 = *((std::string *) vp1.get());
    std::ifstream in_file(path1);
    if (!in_file) {
        std::cerr << "Parser could not load a expression file: " << path1 << '\n';
        exit(-1);
    }
    std::string line;
    getline(in_file, line);
    in_file.close();
    this->equation = line;
    if (!stateP->getRegistry()->isModified("training.infile")) {
        ECF_LOG_ERROR(stateP, "Error: no input file defined for arguments and function values.");
        return false;
    }
    vp1 = stateP->getRegistry()->getEntry("training.infile");
    path1 = *((std::string *) vp1.get());
    std::ifstream in_file2(path1);
    if (!in_file2) {
        std::cerr << "Could not load a file which defines arguments / function values for given function.\n";
        exit(-1);
    }
    for (std::string line2; getline(in_file2, line2);) {
        auto result = utility::parseArgumentsAndFunctionValues(line2);
        this->inputs.push_back(std::move(result.first));
        this->output.push_back(result.second);
    }
    if (stateP->getRegistry()->isModified("softtarget")) {
        voidP vpS = stateP->getRegistry()->getEntry("softtarget");
        std::string sa = *((std::string *) vpS.get());
        if (sa == "1" || sa == "yes" || sa == "Yes" || sa == "true") {
            softTarget = true;
            ECF_LOG(stateP, 0, "Soft target regularization is used.");
            if (!stateP->getRegistry()->isModified("softtarget.beta")) {
                ECF_LOG_ERROR(stateP,
                              "Could not find beta factor for softtarget. Define softtarget.beta entry in registry.\n");
                exit(-1);
            } else {
                voidP vpSBeta = stateP->getRegistry()->getEntry("softtarget.beta");
                std::string vbeta = *((std::string *) vpSBeta.get());
                try {
                    softTargetBeta = std::stod(vbeta);
                } catch (std::exception &ex) {
                    ECF_LOG_ERROR(stateP, "Soft target beta is not a number convertible to double.\n");
                    exit(-1);
                }
            }
            if (!stateP->getRegistry()->isModified("softtarget.gamma")) {
                ECF_LOG_ERROR(stateP,
                              "Could not find gamma factor for softtarget. Define softtarget.gamma entry in registry.\n");
                exit(-1);
            } else {
                voidP vpSGamma = stateP->getRegistry()->getEntry("softtarget.gamma");
                std::string vgamma = *((std::string *) vpSGamma.get());
                try {
                    softTargetGamma = std::stod(vgamma);
                } catch (std::exception &ex) {
                    ECF_LOG_ERROR(stateP, "Soft target gamma is not a number convertible to double.\n");
                    exit(-1);
                }
            }
        }
    }
    return true;
}


FitnessP SymbRegEvalOpTree::evaluate(IndividualP individual) {
    FitnessP fitness(new FitnessMin);
    auto tree = (Tree::Tree *) individual->getGenotype(index).get();

    std::vector<uint> terminal_indices;
    std::string var = "X";
    for (uint i = 0; i < inputs[0].size(); ++i) {
        terminal_indices.push_back(tree->getTerminalIndex(var));
        var[0] += 1;
    }

    double value = 0.0;
    std::vector<double> calculatedOutputs;
    for (auto &input: inputs) {
        double result = 0.0;
        for (uint i = 0; i < input.size(); ++i) {
            tree->setTerminalValue(terminal_indices[i], &input[i]);
        }
        tree->execute(&result);
//        cout<<"tree got result "<<result<<endl;
        calculatedOutputs.push_back(result);
    }
    fitness->setValue(utility::rootMeanSquareError(output, calculatedOutputs));
    return fitness;
}
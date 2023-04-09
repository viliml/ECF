#include "ECF_base.h"
#include "FitnessMin.h"
#include<sstream>


bool FitnessMin::isBetterThan(FitnessP other){
	//za min fitness, bolji je onaj koji ima MANJU vrijednost
	return value_ < other->getValue();
}


FitnessP FitnessMin::copy()
{
    return std::make_shared<FitnessMin>(*this);
}


void FitnessMin::write(XMLNode &xFitness)
{
	xFitness = XMLNode::createXMLTopNode("FitnessMin");
	std::stringstream sValue;
	sValue << value_;
	xFitness.addAttribute("value", sValue.str().c_str());
}

#include "ECF_base.h"
#include "FitnessMax.h"
#include<sstream>


bool FitnessMax::isBetterThan(FitnessP other)
{
	return value_ > other->getValue();
}


FitnessP FitnessMax::copy()
{
	return std::make_shared<FitnessMax>(*this);
}


void FitnessMax::write(XMLNode &xFitness)
{
	xFitness = XMLNode::createXMLTopNode("FitnessMax");
	std::stringstream sValue;
	sValue << value_;
	xFitness.addAttribute("value", sValue.str().c_str());
}

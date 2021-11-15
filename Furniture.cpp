#pragma once
#include <iostream>
#include <string>
#include "tinyxml2.h"

#include "Product.cpp"
#include "Size.cpp"

using namespace std;
using namespace tinyxml2;

class Furniture : public Product
{
public:
	Furniture()
	{
		weight = 0;
		size = Size{ 0, 0, 0 };
	}

	Furniture(string title, string description, double price, 
		double weight, Size size)
		: Product(title, description, price)
	{
		this->weight = weight;
		this->size = size;
	}

protected:
	double weight;
	Size size;

	virtual void ToXML(XMLDocument& xmlDoc, XMLElement* rootElement) override
	{
		Product::ToXML(xmlDoc, rootElement);

		auto* element = xmlDoc.NewElement("Weight");
		element->SetText(weight);
		rootElement->InsertEndChild(element);

		auto* eSize = xmlDoc.NewElement("Size");
		rootElement->InsertEndChild(eSize);

		element = xmlDoc.NewElement("Lenght");
		element->SetText(size.length);
		eSize->InsertEndChild(element);

		element = xmlDoc.NewElement("Width");
		element->SetText(size.width);
		eSize->InsertEndChild(element);

		element = xmlDoc.NewElement("Height");
		element->SetText(size.height);
		eSize->InsertEndChild(element);
	}

	virtual bool TryParseXml(XMLElement* inElement) override
	{
		if (!Product::TryParseXml(inElement)) return false;

		auto* element = inElement->FirstChildElement("Weight");
		if (element == nullptr) return false;
		XMLError result = element->QueryDoubleText(&weight);
		if (result != XMLError::XML_SUCCESS) return false;

		auto* eSize = inElement->FirstChildElement("Size");
		if (element == nullptr) return false;

		double* sizeFields[3] = { &size.length, &size.width, &size.height };
		element = eSize->FirstChildElement();

		for (int i = 0; i < 3; i++) {
			if (element == nullptr) return false;
			XMLError result = element->QueryDoubleText(sizeFields[i]);
			if (result != XMLError::XML_SUCCESS) return false;

			element = element->NextSiblingElement();
		}

		return true;
	}
};
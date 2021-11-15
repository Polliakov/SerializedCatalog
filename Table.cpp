#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "tinyxml2.h"

#include "Furniture.cpp"
#include "IPrintable.cpp"

using namespace std;
using namespace tinyxml2;

class Table : public Furniture, public IPrintable
{
private:
	bool isFolding;

public:
	Table()
	{
		isFolding = false;
	}

	Table(string title, string description, double price,
		double weight, Size size,
		bool isFolding)
		: Furniture(title, description, price, weight, size)
	{
		this->isFolding = isFolding;
	}

	void Print() override
	{
		cout.setf(ios::fixed);
		cout << "Title: " << title << endl 
			 << "Description: " << description << endl 
			 << "Folding: " << BoolToString(isFolding) << endl 
			 << "Price: " << setprecision(2) << price << endl 
			 << "Size: " << endl 
			 << "  Length: " << setprecision(2) << size.length << endl
			 << "  Width: " << setprecision(2) << size.width << endl
			 << "  Height: " << setprecision(2) << size.height << endl
			 << "Weigth: " << setprecision(2) << weight << endl;
		cout.unsetf(ios::fixed);
	}

	void ToXML(XMLDocument& xmlDoc, XMLElement* rootElement) override
	{
		Furniture::ToXML(xmlDoc, rootElement);

		auto* element = xmlDoc.NewElement("IsFolding");
		element->SetText(isFolding);
		rootElement->InsertEndChild(element);
	}

	bool TryParseXml(XMLElement* inElement) override
	{
		if (!Furniture::TryParseXml(inElement)) return false;

		auto* element = inElement->FirstChildElement("IsFolding");
		if (element == nullptr) return false;
		XMLError result = element->QueryBoolText(&isFolding);
		if (result != XMLError::XML_SUCCESS) return false;

		return true;
	}

private:
	string BoolToString(bool value)
	{
		return value ? "Yes" : "No";
	}
};
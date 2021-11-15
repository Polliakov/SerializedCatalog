#pragma once
#include <iostream>
#include <string>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class Product
{
public:
	Product()
	{
		title = "No Title";
		description = "No Description";
		price = 0;
	}

	Product(string title, string description, double price)
	{
		this->title = title;
		this->description = description;
		this->price = price;
	}

protected:
	string title;
	string description;
	double price;

	virtual void ToXML(XMLDocument& xmlDoc, XMLElement* rootElement)
	{
		auto* element = xmlDoc.NewElement("Title");
		element->SetText(title.c_str());
		rootElement->InsertEndChild(element);

		element = xmlDoc.NewElement("Description");
		element->SetText(description.c_str());
		rootElement->InsertEndChild(element);

		element = xmlDoc.NewElement("Price");
		element->SetText(price);
		rootElement->InsertEndChild(element);
	}

	virtual bool TryParseXml(XMLElement* inElement)
	{
		auto* element = inElement->FirstChildElement("Title");
		if (element == nullptr) return false;
		title = element->GetText();

		element = inElement->FirstChildElement("Description");
		if (element == nullptr) return false;
		description = element->GetText();

		element = inElement->FirstChildElement("Price");
		if (element == nullptr) return false;
		XMLError result = element->QueryDoubleText(&price);
		if (result != XMLError::XML_SUCCESS) return false;

		return true;
	}
};
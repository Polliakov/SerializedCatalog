#pragma once
#include <iostream>
#include <vector>
#include "tinyxml2.h"

#include "Table.cpp"

using namespace std;
using namespace tinyxml2;

class Catalog
{
private:
	vector<Table> notes;

public:
	string title;

	Catalog()
	{
		title = "No Title";
	}

	Catalog(string title)
	{
		this->title = title;
	}

	void Print()
	{
		cout << title << endl << endl;

		for (int i = 0; i < notes.size(); i++) {
			cout << "Note¹" << i << endl;
			notes[i].Print();
			cout << endl;
		}
	}

	bool Update(int index, Table& item)
	{
		if (index < 0 || index >= notes.size()) return false;
		notes[index] = item;
	}

	void Add(Table& item)
	{
		notes.push_back(item);
	}

	bool Delete(int index)
	{
		if (index < 0 || index >= notes.size()) return false;
		notes.erase(notes.cbegin() + index);
		return true;
	}

	bool TrySave(string path)
	{
		XMLDocument xmlDoc;
		auto* declaration = xmlDoc.NewDeclaration();
		xmlDoc.InsertFirstChild(declaration);

		auto* eCatalog = xmlDoc.NewElement("Catalog");
		eCatalog->SetAttribute("title", title.c_str());
		xmlDoc.InsertEndChild(eCatalog);

		for (int i = 0; i < notes.size(); i++) {
			auto* eNote = xmlDoc.NewElement("Note");
			eCatalog->InsertEndChild(eNote);

			notes[i].ToXML(xmlDoc, eNote);
		}

		XMLError result = xmlDoc.SaveFile(path.c_str());
		return result == XMLError::XML_SUCCESS ? true : false;
	}

	static bool TryLoad(string path, Catalog& outCatalog)
	{
		XMLDocument xmlDoc;
		XMLError result = xmlDoc.LoadFile(path.c_str());
		if (result != XMLError::XML_SUCCESS) return false;

		auto* eCatalog = xmlDoc.FirstChildElement("Catalog");
		if (eCatalog == nullptr) return false;

		const char* title;
		result = eCatalog->QueryAttribute("title", &title);
		if (result != XMLError::XML_SUCCESS) return false;
		outCatalog.title = title;

		auto* eNote = eCatalog->FirstChildElement("Note");
		while (eNote != nullptr) {
			Table note;
			if (!note.TryParseXml(eNote)) return false;
			outCatalog.Add(note);

			eNote = eNote->NextSiblingElement();
		}

		return true;
	}

	~Catalog()
	{
		notes.clear();
	}
};
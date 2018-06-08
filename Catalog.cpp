#include	<fstream>
#include	<iostream>
#include	<string>
#include 	<map> // inluding STL library map
#include 	<cstdint>
#include 	<utility>

#include	"Catalog.h"

using namespace std;


// Given a category number and name, add it to the catalog. It will have an empty product list. Return false if the category number already exists in the catalog, true otherwise.
bool Catalog::AddCategory(uint64_t categoryNumber, const string& name) 
{
	if (UPCCatalogMap.find(categoryNumber) != UPCCatalogMap.end()) {
		return false;
	}
	map<uint64_t, string> productMap;
	pair<string, map<uint64_t, string> > temp = make_pair(name, productMap); //make_pair will create a pair with the type of elements that were passed into it, no need to to tell it what data types.
	UPCCatalogMap[categoryNumber] = temp;
	return true;
}

//Given a category number, a product number, and a product name, add the product to the catalog. Return false if the category number doesn’t exist in the catalog or if the product number already exists within the category, true otherwise.
bool Catalog::AddProduct(uint64_t categoryNumber, uint64_t productNumber, const string& name)
{
	if (UPCCatalogMap.find(categoryNumber) == UPCCatalogMap.end()) {
		return false;
	}
	if (UPCCatalogMap[categoryNumber].second.find(productNumber) != UPCCatalogMap[categoryNumber].second.end()) {
		return false;
	}
	UPCCatalogMap[categoryNumber].second[productNumber] = name;
	return true;
}

//Return the number of categories in the catalog.
uint64_t Catalog::GetCategoryCount()
{
	return UPCCatalogMap.size();
}

//Given a category number, return the number of products in the category; return -1 if the category doesn’t exist.
int64_t	Catalog::GetProductCount(uint64_t categoryNumber)
{
	if (UPCCatalogMap.find(categoryNumber) == UPCCatalogMap.end()) {
		return -1;
	}
	return UPCCatalogMap[categoryNumber].second.size();
}

//Load the catalog from a file, given the file’s name. Return false if the catalog can’t be loaded, either because the file doesn’t exist or isn’t in the correct format.
bool Catalog::Load(const string& fileName) 
{
	ifstream infile;
	infile.open(fileName.c_str());
	if (!infile) {//if file does not open return false
		return false;
	}

	string line;
	uint64_t categoryNumber = 0;
	while (getline(infile, line)) {
		if (line.size() < 3) {//Product count for jewelry
			continue;
		}
		if (line.size()>8 && line.substr(0, 8) == "Category") {//load catalog
			int location = line.find("\t", 9);
			string number = line.substr(9, location - 9);
			uint64_t answer = 0;
			for (int i = 0; i<number.size(); i++) {
				answer *= 10;
				answer += number[i] - '0';
			}
			string name = line.substr(location + 1);
			AddCategory(answer, name); //78292 Books
			categoryNumber = answer;
		}
		else {
			int location = line.find("\t");
			string number = line.substr(0, location);
			uint64_t answer = 0;
			for (int i = 0; i<number.size(); i++) {
				answer *= 10;
				answer += number[i] - '0';
			}
			string name = line.substr(location + 1);
			AddProduct(categoryNumber, answer, name);//Adds product such as Catagory number(78292), answer(5931), name(gone with the wind)
		}
	}
	infile.close(); //close file after its read
	return true;
}

//****************************************************************************************
//
//	Show... methods
//
//	The stream argument allows thess functions to write its output to any output stream,
//	such as cout or a file, that the caller passes. The argument's name "stream" should
//	be used just as you would use "cout":
//
//		stream << "X = " << x << endl;
//
//	The output will go where the caller intended without special action by this function.
//
//****************************************************************************************

//Given a category number and a product number, show the product number and name separated by a tab.Return false if the category number doesn’t exist in the catalog or if the product number doesn’t exist within the category.
bool Catalog::ShowProduct(ostream& stream, uint64_t categoryNumber, uint64_t productNumber)
{
	if (UPCCatalogMap.find(categoryNumber) == UPCCatalogMap.end()) {
		return false;
	}
	if (UPCCatalogMap[categoryNumber].second.find(productNumber) == UPCCatalogMap[categoryNumber].second.end()) {
		return false;
	}
	stream << productNumber << "\t" << UPCCatalogMap[categoryNumber].second[productNumber] << "\n";
	return true;
}

// Given a category number, show only its products in order by product number. Return false if the category number doesn’t exist in the catalog. Use the same format as the text file in Load.
bool Catalog::ShowCategory(ostream& stream, uint64_t categoryNumber)
{
	if (UPCCatalogMap.find(categoryNumber) == UPCCatalogMap.end()) {
		return false;
	}
	stream << "Category\t" << categoryNumber << "\t" << UPCCatalogMap[categoryNumber].first << "\n";
	map<uint64_t, string> temp = UPCCatalogMap[categoryNumber].second;
	map<uint64_t, string>::iterator it;
	for (it = temp.begin(); it != temp.end(); it++) {
		ShowProduct(stream, categoryNumber, it->first);
	}
	return true;
}

//Show the entire catalog, category by category, in order by category number. Under each category, show its products in order by product number. Use the same format as the text file in Load
bool Catalog::ShowAll(ostream& stream)
{
	if (UPCCatalogMap.size() == 0) {
		return false;
	}
	map<uint64_t, pair<string, map<uint64_t, string> > >::iterator it;
	for (it = UPCCatalogMap.begin(); it != UPCCatalogMap.end(); it++) {
		ShowCategory(stream, it->first);
	}
	return true;
}


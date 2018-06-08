#ifndef	Catalog_h
#define	Catalog_h

//****************************************************************************************
//
//	INCLUDE FILES
//
//****************************************************************************************
#include	<iostream>
#include	<string>
#include 	<map> // inluding STL library map
#include 	<cstdint>
#include 	<utility>

using namespace std;

//****************************************************************************************
//
//	CONSTANT DEFINITIONS
//
//****************************************************************************************

//****************************************************************************************
//
//	CLASSES, TYPEDEFS AND STRUCTURES
//
//****************************************************************************************


class	Catalog
{
	public:
		//Given a category number and name, add it to the catalog. It will have an empty product list. 
		//Return false if the category number already exists in the catalog, true otherwise.
		bool		AddCategory(uint64_t categoryNumber, const string& name);
	
		//Return the number of categories in the catalog
		uint64_t	GetCategoryCount();

		//Given a category number, a product number, and a product name, add the product to the catalog.
		//Return false if the category number doesn’t exist in the catalog or if the product number already exists within the category, true otherwise.
		bool		AddProduct(uint64_t categoryNumber, uint64_t productNumber, const string& name);
	
		//Given a category number, return the number of products in the category; return -1 if the category doesn’t exist.
		int64_t		GetProductCount(uint64_t categoryNumber);
	
		//Load the catalog from a file, given the file’s name.
		//Return false if the catalog can’t be loaded, either because the file doesn’t exist or isn’t in the correct format.
		bool		Load(const string& fileName);
		
		//Given a category number and a product number, show the product number and name separated by a tab.
		//Return false if the category number doesn’t exist in the catalog or if the product number doesn’t exist within the category.
		bool		ShowProduct(ostream& stream, uint64_t categoryNumber, uint64_t productNumber);

		//Given a category number, show only its products in order by product number.
		//Return false if the category number doesn’t exist in the catalog.Use the same format as the text file in Load.
		bool		ShowCategory(ostream& stream, uint64_t categoryNumber);

		//Show the entire catalog, category by category, in order by category number.Under each category, show its products in order by product number.Use the same format as the text file in Load.
		bool		ShowAll(ostream& stream);

	private:
	
		map<uint64_t, pair<string, map<uint64_t, string> > > UPCCatalogMap;// declaring catalog map wih spaces inbetween to avoid compiler read error
};

//****************************************************************************************
//
//	FUNCTION PROTOTYPES
//
//****************************************************************************************

#endif

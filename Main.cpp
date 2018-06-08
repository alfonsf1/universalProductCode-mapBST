//****************************************************************************************
//
//	INCLUDE FILES
//
//****************************************************************************************
#include	<fstream>
#include	<iostream>
#include	<sstream>
#include	<vector>

#include	"Catalog.h"
#include	"GetLine.h"

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

//****************************************************************************************
//
//	PUBLIC DATA
//
//****************************************************************************************

//****************************************************************************************
//
//	PRIVATE DATA
//
//****************************************************************************************

//****************************************************************************************
//
//	FUNCTION PROTOTYPES
//
//****************************************************************************************
uint64_t	TestAddCategory();

uint64_t	TestAddProduct();

uint64_t	TestLoad();

uint64_t	TestShowAll();

uint64_t	TestShowCategory();

uint64_t	TestShowProduct();

bool		Verify(stringstream& actualStream, stringstream& expectedStream);

//****************************************************************************************
//
//	MAIN PROGRAM
//
//****************************************************************************************
int main (int argc, char * const argv[])
{
	//************************************************************************************
	//	LOCAL DATA
	uint64_t	score;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	score = 0;
	
	score += TestAddCategory();
	
	score += TestAddProduct();
	
	score += TestLoad();
	
	score += TestShowProduct();
	
	score += TestShowCategory();
	
	score += TestShowAll();

	cout << endl << "Passed: " << score << " out of 18 tests" << endl;
	
	cout << endl << "** Finished **" << endl;

	//system("pause");
	return(0);
}

//****************************************************************************************
//
//	TestAddCategory
//
//****************************************************************************************
uint64_t	TestAddCategory()
{
	//************************************************************************************
	//	LOCAL DATA
	stringstream	actualStream;
	
	Catalog			catalog;
	
	stringstream	expectedStream;
	
	uint64_t		score;

	bool			success;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << "TestAddCategory" << endl;

	score = 0;
	
	cout << "  Valid category." << endl;
	success = catalog.AddCategory(1, "Category One");
	success &= catalog.AddCategory(2, "Category Two");
	success &= catalog.AddCategory(3, "Category Three");
	
	uint64_t categoryCount = catalog.GetCategoryCount();
	cout << "    Category count." << endl;
	if (categoryCount == 3)
	{
		score += 1;
		cout << "      Pass." << endl;
	}
	else
	{
		cout << "      Fail. Actual: " << categoryCount << ". Expected: 3" << endl;
	}

	cout << "  Duplicate category." << endl;
	success &= catalog.AddCategory(3, "Category Duplicate Three");
	if (!success)
	{
		cout << "    Pass." << endl;
		score += 1;
	}
	else
	{
		cout << "    Fail. Duplicate not detected." << endl;
	}

	return(score);
}

//****************************************************************************************
//
//	TestAddProduct
//
//****************************************************************************************
uint64_t	TestAddProduct()
{
	//************************************************************************************
	//	LOCAL DATA
	stringstream	actualStream;
	
	Catalog			catalog;
	
	stringstream	expectedStream;
	
	uint64_t		score;
	
	bool			success;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << endl << "TestAddProduct" << endl;
	
	score = 0;
	
	cout << "  Valid category." << endl;
	success = catalog.AddCategory(1, "Category One");
	
	success &= catalog.AddProduct(1, 1, "Product One");
	success &= catalog.AddProduct(1, 2, "Product Two");
	success &= catalog.AddProduct(1, 3, "Product Three");
	
	cout << "    Product count for category 1." << endl;
	int64_t productCount = catalog.GetProductCount(1);
	if (productCount == 3)
	{
		score += 1;
		cout << "      Pass." << endl;
	}
	else
	{
		cout << "      Fail. Actual: " << productCount << ". Expected: 3" << endl;
	}
	
	cout << "  Duplicate product." << endl;
	success = catalog.AddProduct(1, 3, "Product Duplicate Three");
	if (!success)
	{
		cout << "    Pass." << endl;
		score += 1;
	}
	else
	{
		cout << "    Fail. Duplicate not detected." << endl;
	}
	
	cout << "  Nonexistent category." << endl;
	success &= catalog.AddProduct(2, 3, "Nonexistent category");
	if (!success)
	{
		cout << "    Pass." << endl;
		score += 1;
	}
	else
	{
		cout << "    Fail. Nonexistent category not detected." << endl;
	}
		
	return(score);
}

//****************************************************************************************
//
//	TestLoad
//
//****************************************************************************************
uint64_t	TestLoad()
{
	//************************************************************************************
	//	LOCAL DATA
	stringstream	actualStream;
	
	Catalog			catalog1;
	
	Catalog			catalog2;
	
	uint64_t		categoryCount;
	
	stringstream	expectedStream;
	
	uint64_t		productCount;
	
	uint64_t		score;
	
	bool			success;

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << endl << "TestLoad" << endl;
	
	score = 0;
	
	cout << "  Load small catalog." << endl;
	cout << "    Category count." << endl;
	success = catalog1.Load("SmallCatalog.txt");
	if (success)
	{
		categoryCount = catalog1.GetCategoryCount();
		if (categoryCount == 3)
		{
			score += 1;
			cout << "      Pass." << endl;
		}
		else
		{
			cout << "      Fail. Actual: " << categoryCount << ". Expected: 3" << endl;
		}

		cout << "    Product count for category Jewelry." << endl;
		productCount = catalog1.GetProductCount(40506);
		if (productCount == 3)
		{
			score += 1;
			cout << "      Pass." << endl;
		}
		else
		{
			cout << "      Fail. Actual: " << productCount << ". Expected: 3" << endl;
		}

		cout << "    Product count for category Toys." << endl;
		productCount = catalog1.GetProductCount(78162);
		if (productCount == 3)
		{
			score += 1;
			cout << "      Pass." << endl;
		}
		else
		{
			cout << "      Fail. Actual: " << productCount << ". Expected: 3" << endl;
		}

	}
	else
	{
		cout << "    Fail. Couldn't load file." << endl;
	}

	cout << "  Load large catalog." << endl;
	success = catalog2.Load("LargeCatalog.txt");
	if (success)
	{
		cout << "    Category count." << endl;
		categoryCount = catalog2.GetCategoryCount();
		if (categoryCount == 18)
		{
			score += 1;
			cout << "      Pass." << endl;
		}
		else
		{
			cout << "      Fail. Actual: " << categoryCount << ". Expected: 18" << endl;
		}
		
		cout << "    Product count for category 8." << endl;
		productCount = catalog2.GetProductCount(8);
		if (productCount == 149)
		{
			score += 1;
			cout << "      Pass." << endl;
		}
		else
		{
			cout << "      Fail. Actual: " << productCount << ". Expected: 149" << endl;
		}
	}
	else
	{
		cout << "    Fail. Couldn't load file." << endl;
	}
		
	return(score);
}

//****************************************************************************************
//
//	TestShowAll
//
//****************************************************************************************
uint64_t	TestShowAll()
{
	//************************************************************************************
	//	LOCAL DATA
	stringstream	actualStream;
	
	Catalog			catalog;
	
	stringstream	expectedStream;
	
	uint64_t		score;
	
	stringstream	stream;
	
	bool			success;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << endl << "TestShowAll" << endl;
	
	score = 0;
	
	cout << "  Empty catalog." << endl;
	success = catalog.ShowAll(actualStream);
	if (!success)
	{
		cout << "    Pass." << endl;
		score += 1;
	}
	else
	{
		cout << "    Fail." << endl;
	}

	cout << "  Populated catalog." << endl;
	success = catalog.AddCategory(1, "Category One");
	success &= catalog.AddProduct(1, 1, "Product One");
	success &= catalog.AddProduct(1, 2, "Product Two");
	success &= catalog.AddProduct(1, 3, "Product Three");
	
	success = catalog.AddCategory(2, "Category Two");
	success &= catalog.AddProduct(2, 4, "Product Four");
	success &= catalog.AddProduct(2, 5, "Product Five");
	success &= catalog.AddProduct(2, 6, "Product Six");
	
	catalog.ShowAll(actualStream);
	
	expectedStream << "Category\t1\tCategory One" << endl
		<< "1\tProduct One" << endl
		<< "2\tProduct Two" << endl
		<< "3\tProduct Three" << endl
		<< "Category\t2\tCategory Two" << endl
		<< "4\tProduct Four" << endl
		<< "5\tProduct Five" << endl
		<< "6\tProduct Six";
	
	if (Verify(actualStream, expectedStream))
	{
		cout << "    Pass." << endl;
		score += 1;
	}
	else
	{
		cout << "    Fail." << endl;
	}
	
	return(score);
}

//****************************************************************************************
//
//	TestShowCategory
//
//****************************************************************************************
uint64_t	TestShowCategory()
{
	//************************************************************************************
	//	LOCAL DATA
	stringstream	actualStream;
	
	Catalog			catalog;
	
	stringstream	expectedStream;
	
	uint64_t		score;
	
	stringstream	stream;
	
	bool			success;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << endl << "TestShowCategory" << endl;
	
	score = 0;
	
	cout << "  Empty catalog." << endl;
	success = catalog.ShowCategory(actualStream, 2);
	if (!success)
	{
		cout << "    Pass." << endl;
		score += 1;
	}
	else
	{
		cout << "    Fail. ShowCategory should return false when catalog is empty." << endl;
	}
	
	cout << "  Populated catalog." << endl;
	success &= catalog.AddCategory(1, "Category One");
	success &= catalog.AddProduct(1, 1, "Product One");
	success &= catalog.AddProduct(1, 2, "Product Two");
	success &= catalog.AddProduct(1, 3, "Product Three");
	
	success = catalog.AddCategory(2, "Category Two");
	success &= catalog.AddProduct(2, 4, "Product Four");
	success &= catalog.AddProduct(2, 5, "Product Five");
	success &= catalog.AddProduct(2, 6, "Product Six");
	
	success = catalog.ShowCategory(actualStream, 2);
	if (success)
	{
		expectedStream << "Category\t2\tCategory Two" << endl
		<< "4\tProduct Four" << endl
		<< "5\tProduct Five" << endl
		<< "6\tProduct Six";
		
		if (Verify(actualStream, expectedStream))
		{
			cout << "    Pass." << endl;
			score += 1;
		}
		else
		{
			cout << "    Fail." << endl;
		}
	}
	else
	{
		cout << "    Fail." << endl;
	}
	
	cout << "  Nonexistent category." << endl;
	success = catalog.ShowCategory(actualStream, 3);
	if (!success)
	{
		cout << "    Pass." << endl;
		score += 1;
	}
	else
	{
		cout << "    Fail." << endl;
	}

	return(score);
}

//****************************************************************************************
//
//	TestShowProduct
//
//****************************************************************************************
uint64_t	TestShowProduct()
{
	//************************************************************************************
	//	LOCAL DATA
	stringstream	actualStream;
	
	Catalog			catalog;
	
	stringstream	expectedStream;
	
	uint64_t		score;
	
	stringstream	stream;
	
	bool			success;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << endl << "TestShowProduct" << endl;
	
	score = 0;
	
	success = catalog.AddCategory(1, "Category One");
	success &= catalog.AddProduct(1, 1, "Product One");
	success &= catalog.AddProduct(1, 2, "Product Two");
	success &= catalog.AddProduct(1, 3, "Product Three");
	
	success = catalog.AddCategory(2, "Category Two");
	success &= catalog.AddProduct(2, 4, "Product Four");
	success &= catalog.AddProduct(2, 5, "Product Five");
	success &= catalog.AddProduct(2, 6, "Product Six");

	cout << "  Valid category and product." << endl;
	success = catalog.ShowProduct(actualStream, 1, 3);
	if (success)
	{
		expectedStream << "3\tProduct Three";
		
		if (Verify(actualStream, expectedStream))
		{
			cout << "    Pass." << endl;
			score += 1;
		}
		else
		{
			cout << "    Fail." << endl;
		}
	}
	else
	{
		cout << "    Fail." << endl;
	}
	
	cout << "  Nonexistent category." << endl;
	success = catalog.ShowProduct(actualStream, 3, 3);
	if (!success)
	{
		cout << "    Pass." << endl;
		score += 1;
	}
	else
	{
		cout << "    Fail." << endl;
	}
	
	cout << "  Valid category, nonexistent product." << endl;
	success = catalog.ShowProduct(actualStream, 1, 4);
	if (!success)
	{
		cout << "    Pass." << endl;
		score += 1;
	}
	else
	{
		cout << "    Fail." << endl;
	}
	
	return(score);
}

//****************************************************************************************
//
//	Verify
//
//****************************************************************************************
bool	Verify(stringstream& actualStream, stringstream& expectedStream)
{
	//************************************************************************************
	//	LOCAL DATA
	vector<string>	actualText;
	
	vector<string>	expectedText;

	string			line;

	bool			success;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	while (true)
	{
		GetLine(actualStream, line);
		if (!actualStream.fail())
		{
			actualText.push_back(line);
		}
		else
		{
			break;
		}
	}
	
	while (true)
	{
		GetLine(expectedStream, line);
		if (!expectedStream.fail())
		{
			expectedText.push_back(line);
		}
		else
		{
			break;
		}
	}
	
	if (actualText != expectedText)
	{
		cout << "Actual text doesn't match expected text." << endl;
		
		cout << "Actual:" << endl;
		for (size_t i = 0; i < actualText.size(); ++i)
		{
			cout << actualText[i] << endl;
		}
		
		cout << "Expected:" << endl;
		for (size_t i = 0; i < expectedText.size(); ++i)
		{
			cout << expectedText[i] << endl;
		}
		
		success = false;
	}
	else
	{
		success = true;
	}

	return(success);
}

#if 0
//****************************************************************************************
//
//	Class::Function
//
//****************************************************************************************
void	Class::Function()
{
	//************************************************************************************
	//	LOCAL DATA

	//************************************************************************************
	//	EXECUTABLE STATEMENTS

	return;
}

#endif

//References:
//Address: https://stackoverflow.com/questions/9642292/function-to-check-if-string-contains-a-number
//Author: Remy Lebeau

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

string conversion() {
	string initialisedStr;
	cout << "Insert a string to convert: ";
	//Input validation for non-numeric string values
	while (!(cin >> initialisedStr) || initialisedStr.find('0') != std::string::npos || initialisedStr.find('1') != std::string::npos || initialisedStr.find('2') != std::string::npos || initialisedStr.find('3') != std::string::npos ||
		initialisedStr.find('4') != std::string::npos || initialisedStr.find('5') != std::string::npos || initialisedStr.find('6') != std::string::npos ||
		initialisedStr.find('7') != std::string::npos || initialisedStr.find('8') != std::string::npos || initialisedStr.find('9') != std::string::npos)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Try again: ";
	}

	string conversionProduct;
	cout << "Specify the product word: ";
	while (!(cin >> conversionProduct) || conversionProduct.find('0') != std::string::npos || conversionProduct.find('1') != std::string::npos || conversionProduct.find('2') != std::string::npos || conversionProduct.find('3') != std::string::npos ||
		conversionProduct.find('4') != std::string::npos || conversionProduct.find('5') != std::string::npos || conversionProduct.find('6') != std::string::npos ||
		conversionProduct.find('7') != std::string::npos || conversionProduct.find('8') != std::string::npos || conversionProduct.find('9') != std::string::npos) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Try again: ";
	}
	cout << "\n";

	int conversionCost = 0;

	int deleteCost = 3;
	int insertCost = 4;
	int replaceCost = 5;

	bool notUsed = false;

	bool matching = false;

	int counter = 0;

	while (initialisedStr != conversionProduct) {
		for (int i = 0; i < conversionProduct.size(); i++) {
			if (initialisedStr[i] != NULL) {
				if (initialisedStr[i] != conversionProduct[i]) {
					//Check if the next char in the converted string
					//is the current one in the result string
					if (initialisedStr[i + 1] == conversionProduct[i]) {
						//Delete
						int iCopy = i;
						while (iCopy != initialisedStr.size()) {
							initialisedStr[iCopy] = initialisedStr[iCopy + 1];
							iCopy++;
						}
						initialisedStr.pop_back();
						conversionCost += deleteCost;
						i = 0;

						cout << "Current iteration: " << initialisedStr << "\n";
						cout << "Current cost: " << conversionCost << "\n";
					}
					else {
						//Replace
						initialisedStr[i] = conversionProduct[i];
						conversionCost += replaceCost;

						cout << "Current iteration: " << initialisedStr << "\n";
						cout << "Current cost: " << conversionCost << "\n";
					}
				}
			}
			//Insert neccessary characters to fill in the converted string and match the size of the result string
			else {
				//Insert
				initialisedStr.push_back(conversionProduct[i]);
				conversionCost += insertCost;

				cout << "Current iteration: " << initialisedStr << "\n";
				cout << "Current cost: " << conversionCost << "\n";
			}
		}

		//Delete unnecessary characters in converted string to match specified result string
		if (initialisedStr.size() > conversionProduct.size()) {
			for (int i = 0; i < conversionProduct.size(); i++) {
				if (initialisedStr[i] == conversionProduct[i]) {
					matching = true;
				}
				else {
					matching = false;
					break;
				}
			}
			//Delete until the difference in sizes is removed
			if (matching) {
				for (int i = initialisedStr.size() - conversionProduct.size(); i > 0; i--) {
					//Delete 
					initialisedStr.pop_back();
					conversionCost += deleteCost;

					cout << "Current iteration: " << initialisedStr << "\n";
					cout << "Current cost: " << conversionCost << "\n";
				}
			}
		}
	}
	cout << "\n";
	cout << "Conversion Complete: \n";
	cout << "Final iteration: " << initialisedStr << "\n";
	cout << "Conversion cost: " << conversionCost << "\n";

	return initialisedStr;
}

int main()
{
	conversion();
	system("pause");
	return 0;
}


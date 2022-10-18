#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("project3");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"project3");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"project3");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

int userMenu() {//displays menu and validation
	bool funcLoop = true;
	string userChoice;
	int iuserChoice;

	while (funcLoop) {//menu input validation
		try {
			cout << "1: Display the purchase frequency of each grocery item" << endl << "2: Display the purchase frequency of a certain grocery item" << endl << "3: Display the purchase frequency of each grocery item as a graph" << endl << "4: Exit" << endl << endl<< "Please enter your choice as 1, 2, 3, or 4.";
			cout << endl;
			cin >> userChoice;
			cout << endl;

			if (userChoice == "1" || userChoice == "2" || userChoice == "3" || userChoice == "4") {
				iuserChoice = stoi(userChoice);
				funcLoop = false;
			}
			else {
				throw runtime_error("Invalid input. Try again \n \n");
			}
		}
		catch (runtime_error& excpt) {
			cout << excpt.what() << endl;
		}
	}
	return iuserChoice;
}



int main()
{
	bool loop = true;
	ifstream fileInput;
	
	while (loop) { //loops menu and input
		int userChoice;
		string itemName;
		string searchItem;
		int itemQuantity;
		int itemFreq;
		int freq = 0;
		userChoice = userMenu();
		cout << endl;

		switch (userChoice) {

		case 1://purchase frequency of each item
			CallProcedure("printoccurence");
			cout << endl;
			break;

		case 2://frequency for specific item
			cout << "Enter an item: ";
			cin >> searchItem;
			cout << endl;
			itemFreq = callIntFunc("ReturnFreq", searchItem);

			cout << searchItem << " : " << itemFreq << endl << endl;
			break;


			

		case 3: //display hstogram for data
			CallProcedure("NewFile");
			
			fileInput.open("grocery_freq.txt");
	
			fileInput >> itemName;
			fileInput >> itemQuantity;

			while (!fileInput.fail()) {

				cout << itemName << "  ";
				
				for (int i = 0; i < itemQuantity; i++) {
					cout << "*";
				}
				cout << endl;
				fileInput >> itemName;
				fileInput >> itemQuantity;
			}
			fileInput.close();
			cout << endl;
			break;

		case 4://exit
			cout << "Thank you for using item tracker" << endl << endl;
			loop = false;
			break;
				

		}
		

	}
}
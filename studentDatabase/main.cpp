/***************************************************************************
	FINAL PROJECT		Student database for checking eligibility
						
						The program uses an AVL tree to sort data and a 
						hash table to search data


	Date				June 14th 2016
	Author				Anna Houk, Kiera Nguyen, Michael Phan

***************************************************************************/
#include <iostream>
#include <sstream>		// required for string stream
#include <fstream>		// required for ifstream
#include <string>		// required for string
#include <cstdlib>		// required for atoi, atof
#include "AVLTree.h"
#include "HashTable.h"
#include "StudentData.h"
#include "SinglyLinkedList.h"
#include "StackLinkedList.h"

using namespace std;


//Prototypes
void readFile(SinglyLinkedList<StudentData>& stu, AVLTree<StudentData, int>& stu_tree, HashTable<StudentData, int>& stu_hash);
bool menu(SinglyLinkedList<StudentData>& stu, AVLTree<StudentData, int>& stu_tree, HashTable<StudentData, int>& stu_hash, StackLinkedList<StudentData> &deletedStudents);
void addStudent(SinglyLinkedList<StudentData>& stu, AVLTree<StudentData, int>& stu_tree, HashTable<StudentData, int>& stu_hash);
void deleteStudent(SinglyLinkedList<StudentData>& stu, AVLTree<StudentData, int>& stu_tree, HashTable<StudentData, int>& stu_hash, StackLinkedList<StudentData> &deletedStudents);
void findStudent(AVLTree<StudentData, int>& stu_tree, HashTable<StudentData, int>& stu_hash);
void undoDelete(SinglyLinkedList<StudentData>& stu, AVLTree<StudentData, int>& stu_tree, HashTable<StudentData, int>& stu_hash, StackLinkedList<StudentData> &deletedStudents);
void saveFile(AVLTree<StudentData, int>& stu_tree);


int main()
{
	bool cont = true;
	SinglyLinkedList<StudentData> stu;
	AVLTree<StudentData, int> stu_tree;
	HashTable<StudentData, int> stu_hash;
	StackLinkedList<StudentData> deletedStudents;

	// Read student info from a file
	readFile(stu, stu_tree, stu_hash);
	
	while (cont == true)
	{
		cont = menu(stu, stu_tree, stu_hash, deletedStudents);
	}

	saveFile(stu_tree);

	system("pause");
	return 0;
}//end main


/********************************************************
	void functions for supporting traveral methods in
	BST and for printing the tree visually
		- Parameter: a reference of integer
		- Return: none
********************************************************/
void visit(int& someData){ someData = 0; }
void print(int& someData){ cout << someData << endl; }


/****************************************************************************************
	readFile definition
	- It reads data from a text file, and insert them into the AVL tree & hash table
	- Parameter: 
		+ A reference of SinglyLinkedList
		+ A reference of AVLTree
		+ A reference of HashTable
	- Return: none
****************************************************************************************/
void readFile(SinglyLinkedList<StudentData>& stu, AVLTree<StudentData, int>& stu_tree, HashTable<StudentData, int>& stu_hash)
{
	ifstream  inputFile;	// to hold the input file
	string    line;			// to temporarily hold each line of string from the file 
	

	string id, n, m, gpa, credits, yr, curUnit;


	// Open the file
	inputFile.open("student.txt");

	if (!inputFile)
	{
		cout << "File not found\n";
	}
	else
	{
		while (getline(inputFile, line))	 // reads a line from the file
		{
			StudentData* s;
			stringstream lineStream(line);   // transforms the line into a stream

			// get fields from the string stream; fields are separated by comma
			getline(lineStream, id, ',');
			getline(lineStream, n, ',');
			getline(lineStream, m, ',');
			getline(lineStream, gpa, ',');
			getline(lineStream, credits, ',');
			getline(lineStream, yr, ',');
			getline(lineStream, curUnit, ',');

			int id_convert = atoi(id.c_str());
			double gpa_convert = atof(gpa.c_str());
			double credits_convert = atof(credits.c_str());
			double yr_convert = atof(yr.c_str());
			double curUnit_convert = atof(curUnit.c_str());

			s = new StudentData(id_convert, n, m, gpa_convert, credits_convert, yr_convert, curUnit_convert);

			stu.addEnd(*s);

			stu_tree.avlAdd(id_convert, stu.get_node_address(*s));
			stu_hash.insert(id_convert, stu.get_node_address(*s));
		
			delete s;
			
		}
		inputFile.close(); // Close file
	}
}//end readFile



/****************************************************************************************
	menu definition
	- displays menu and get a selection from user
	- Parameter:
		+ A reference of SinglyLinkedList
		+ A reference of AVLTree
		+ A reference of HashTable
		+ A reference of StackLinkedList
	- Return: a boolean
****************************************************************************************/
bool menu(SinglyLinkedList<StudentData>& stu, AVLTree<StudentData, int>& stu_tree, HashTable<StudentData, int>& stu_hash, StackLinkedList<StudentData> &deletedStudents){
	int choice;
	cout << "\nMENU:\n"
		<< "(1) Add Student\n"
		<< "(2) Delete Student\n"
		<< "(3) Find Student record\n"
		<< "(4) List Students in hashtable sequence\n"
		<< "(5) List Students in sorted ID sequence\n"
		<< "(6) Print Tree \n"
		<< "(7) Efficiency\n"
		<< "(8) Undo last delete\n"
		<< "(9) Quit\n";
	cin >> choice;
	switch (choice){
	case 1: addStudent(stu, stu_tree, stu_hash);break;
	case 2: deleteStudent(stu, stu_tree, stu_hash, deletedStudents); break;
	case 3: findStudent(stu_tree, stu_hash); break;
	case 4: cout << "[Student IDs in hashtable sequence]\n"; stu_hash.print_table(); break;
	case 5: cout << "[Student IDs in sorted sequence]\n"; stu_tree.inorderTraverse(print); break;
	case 6: cout << "[Tree visual - student IDs]\n"; stu_tree.print_tree(); break;
	case 7: break;//TBD
	case 8: undoDelete(stu, stu_tree, stu_hash, deletedStudents); break;//has issue...go to function for info
	case 9: return false; 
	default: cout << "Invalid option\n"; break;
	}
	return true;
}


/****************************************************************************************
	addStudent definition
	- receive input data from User to add a new student to AVL tree and hash table
	- Parameter:
		+ A reference of SinglyLinkedList
		+ A reference of AVLTree
		+ A reference of HashTable
	- Return: none
****************************************************************************************/
void addStudent(SinglyLinkedList<StudentData>& stu, AVLTree<StudentData, int>& stu_tree, HashTable<StudentData, int>& stu_hash){
	int id, y, tu, cu;
	double gpa = 1.0;
	string name, major;
	char conf;
	bool valid = true;
	cout << "[Create a new Student]" << endl;
	//get user input for all the fields
	//checking for valid input
	do{
		cout << "Enter an 8-digit ID number: " << endl;
		cin >> id;
		valid = true;
		if (id < 10000000 || id > 99999999){
			cout << "ID is not valid" << endl;
			valid = false;
		}
	} while (valid == false);
	
	do{
		cout << "Enter Name: " << endl;
		getline(cin,name);
		valid = true;
		if (name.length() < 1){
			cout << "cannot leave field blank" << endl;
			valid = false;
		}
	} while (valid == false);

	do{
		cout << "Enter Major: " << endl;
		getline(cin, major);
		valid = true;
		if (major.length() < 1){
			cout << "cannot leave field blank" << endl;
			valid = false;
		}
	} while (valid == false);

	do{
		cout << "Enter GPA: " << endl;
		cin >> gpa;
		valid = true;
		if (gpa < 0.0 || gpa > 4.0){
			cout << "Invalid gpa. must be between 0.0-4.0" << endl;
			valid = false;
		}
	} while (valid == false);

	cout << "Enter total units: " << endl;
	cin >> tu;

	cout << "Enter years studied: " << endl;
	cin >> y;

	do{
		cout << "Enter current units: " << endl;
		cin >> cu;
		if (cu < 0 || cu > 22){
			cout << "Invalid number of units. Students may only take up to 22 units and no less than 0" << endl;
			valid = false;
		}
	} while (valid == false);

	StudentData* moreStu = new StudentData(id, name, major, gpa, tu, y, cu);
	cout << "Confirm create student with the following information(enter y/n): \n" << *moreStu<<endl;
	cin >> conf;
	do{
		if (conf == 'y'){
			stu.addTop(*moreStu);
			stu_tree.avlAdd(stu.get_node_data(*moreStu).getID(), stu.get_node_address(*moreStu));
			stu_hash.insert(stu.get_node_data(*moreStu).getID(), stu.get_node_address(*moreStu));
			delete moreStu;
			valid = true;
		}
		else if (conf == 'n'){
			delete moreStu;
			valid = true;
		}
		else{
			cout << "invalid answer, enter y/n ";
			cin >> conf;
			valid = false;
		}
	} while (valid == false);
}//end addStudent


/****************************************************************************************
	deleteStudent definition
	- asks user for the ID of the student and delete it from AVL tree & hash table
	- Parameter:
		+ A reference of SinglyLinkedList
		+ A reference of AVLTree
		+ A reference of HashTable
		+ A reference of StackLinkedList
	- Return: none
****************************************************************************************/
void deleteStudent(SinglyLinkedList<StudentData>& stu, AVLTree<StudentData, int>& stu_tree, HashTable<StudentData, int>& stu_hash, StackLinkedList<StudentData> &deletedStudents){
	int id;
	cout << "Enter ID of student to remove from system: ";
	cin >> id;
	if (stu_tree.is_contained(id)){
		StudentData* dStu = stu_tree.getEntry_address(id);
		if (dStu != nullptr){
			deletedStudents.push(*dStu);//add student to deleted stack
			cout << "Deleting " << dStu->getName() << " from system . ";
			stu_tree.avlRemove(id);
			cout << ". ";
			stu_hash.remove(id);
			cout << ". ";
			stu.remove(*dStu);
			cout << "done" << endl;
		}
	}
	else{
		cout << "Failed: Student does not exist in system" << endl;
	}
}//end delete student


/****************************************************************************************
	findStudent definition
	- finds and displays a student record
	- Parameter:
		+ A reference of AVLTree
		+ A reference of HashTable
	- Return: none
****************************************************************************************/
void findStudent(AVLTree<StudentData, int>& stu_tree, HashTable<StudentData, int>& stu_hash){
	bool tempBool = false;
	int id;

	// Find a student using the key
	cout << "Enter student ID: ";
	cin >> id;
	
	tempBool = stu_tree.is_contained(id);

	if (tempBool == true)
	{
		StudentData* tempStu = nullptr;
		tempStu = stu_tree.getEntry_address(id);
		cout << "Found: " << endl
			<< "[ID, name, major, GPA, total units, total units, years studied, current units]" << endl
			<< *tempStu << endl;
	}
	else
		cout << "Student "<< id<< "does not exist\n";
}//end findStudent


/****************************************************************************************
	undoDelete definition
	- undo the last delete (can only undo before the data is saved to an output file)
	- Parameter:
		+ A reference of SinglyLinkedList
		+ A reference of AVLTree
		+ A reference of HashTable
		+ A reference of StackLinkedList
	- Return: none
****************************************************************************************/
void undoDelete(SinglyLinkedList<StudentData>& stu, AVLTree<StudentData, int>& stu_tree, HashTable<StudentData, int>& stu_hash, StackLinkedList<StudentData> &deletedStudents){

	if (!deletedStudents.isEmpty())
	{
		cout << "Deleting " << "\"" << deletedStudents.peek() << "\"" << endl;

		StudentData moreStu = deletedStudents.peek();//missing some data fields (the string values)
		deletedStudents.pop();

		stu.addTop(moreStu);
		stu_tree.avlAdd(stu.get_node_data(moreStu).getID(), stu.get_node_address(moreStu));
		stu_hash.insert(stu.get_node_data(moreStu).getID(), stu.get_node_address(moreStu));
		cout << "Added    " << "\"" << moreStu << "\"" << " back into the system\n" << endl;
	}
	else
		cout << "There is no deleted Students\n";
}


/****************************************************************************************
	saveFile definition
	- save student data to a text file in preOrder traversal
	- Parameter:
		+ A reference of AVLTree
	- Return: none
****************************************************************************************/
void saveFile(AVLTree<StudentData, int>& stu_tree){
	cout << "\n\n\n[SAVED DATA to FILE]\n";

	ofstream outFile;

	outFile.open("StudentOut.txt");
	stu_tree.save_to_file(outFile);

	outFile.close();
}//end saveFile
#include <iostream>
#include <sstream>		// required for string stream
#include <fstream>		// required for ifstream
#include <string>		// required for string
#include <cstdlib>		// required for atoi, atof
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "StudentData.h"
#include "SinglyLinkedList.h"
#include "StackLinkedList.h"
using namespace std;

void visit(int& someData)
	{
		someData=0;
	}

void print(int& someData)
{
	cout << someData << endl;
}

//Prototypes
void readFile(SinglyLinkedList<StudentData>& stu, BinarySearchTree<StudentData, int>& stu_tree, HashTable<int, StudentData>& stu_hash);
bool menu(SinglyLinkedList<StudentData>& stu, BinarySearchTree<StudentData, int>& stu_tree, HashTable<int, StudentData>& stu_hash, StackLinkedList<StudentData> &deletedStudents);
void addStudent(SinglyLinkedList<StudentData>& stu, BinarySearchTree<StudentData, int>& stu_tree, HashTable<int, StudentData>& stu_hash);
void deleteStudent(SinglyLinkedList<StudentData>& stu, BinarySearchTree<StudentData, int>& stu_tree, HashTable<int, StudentData>& stu_hash, StackLinkedList<StudentData> &deletedStudents);
void findStudent(BinarySearchTree<StudentData, int>& stu_tree, HashTable<int, StudentData>& stu_hash);
void saveFile(BinarySearchTree<StudentData, int>& stu_tree);


int main()
{
	bool cont = true;
	SinglyLinkedList<StudentData> stu;
	BinarySearchTree<StudentData, int> stu_tree;
	HashTable<int, StudentData> stu_hash;
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


void readFile(SinglyLinkedList<StudentData>& stu, BinarySearchTree<StudentData, int>& stu_tree, HashTable<int, StudentData>& stu_hash)
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

			stu_tree.add(id_convert, stu.get_node_address(*s));
			stu_hash.insert(id_convert, *stu.get_node_address(*s));
		
			delete s;
			
		}
		inputFile.close(); // Close file
	}
}//end readFile

bool menu(SinglyLinkedList<StudentData>& stu, BinarySearchTree<StudentData, int>& stu_tree, HashTable<int, StudentData>& stu_hash, StackLinkedList<StudentData> &deletedStudents){
	int choice;
	cout << "MENU:" << endl
		<< "(1) Add Student" << endl
		<< "(2) Delete Student" << endl
		<< "(3) Find Student record" << endl
		<< "(4) List Students in hashtable sequence" << endl
		<< "(5) List Students in sorted ID sequence" << endl
		<< "(6) Print Tree " << endl
		<< "(7) Efficiency" << endl
		<< "(8) Use AVL tree" << endl
		<< "(9) Quit" << endl;
	cin >> choice;
	switch (choice){
	case 1: addStudent(stu, stu_tree, stu_hash);break;
	case 2: deleteStudent(stu, stu_tree, stu_hash, deletedStudents); break;
	case 3: findStudent(stu_tree, stu_hash); break;
	case 4: cout << "[Student IDs in hashtable sequence]" << endl; stu_hash.print_table(); break;
	case 5: cout << "[Student IDs in sorted sequence]" << endl; stu_tree.inorderTraverse(print); break;
	case 6: cout << "[Tree visual - student IDs]" << endl; stu_tree.print_tree(); break;
	case 7: break;//TBD
	case 8: break;//must finish
	case 9: return false; 
	default: cout << "Invalid option" << endl; break;
	}
	return true;
}

void addStudent(SinglyLinkedList<StudentData>& stu, BinarySearchTree<StudentData, int>& stu_tree, HashTable<int, StudentData>& stu_hash){
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
			stu_tree.add(stu.get_node_data(*moreStu).getID(), stu.get_node_address(*moreStu));
			stu_hash.insert(stu.get_node_data(*moreStu).getID(), *stu.get_node_address(*moreStu));
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

void deleteStudent(SinglyLinkedList<StudentData>& stu, BinarySearchTree<StudentData, int>& stu_tree, HashTable<int, StudentData>& stu_hash, StackLinkedList<StudentData> &deletedStudents){
	int id;
	cout << "Enter ID of student to remove from system: ";
	cin >> id;
	StudentData* dStu = stu_tree.getEntry_address(id);
	if (dStu != nullptr){
		cout << "Deleting " << dStu->getName() <<" from system . ";
		stu_tree.remove(id);
		cout << ". ";
		stu_hash.remove(id);
		cout << ". ";
		stu.remove(*dStu);
		cout << "done"<<endl;
	}
	else{
		cout << "Failed: Student does not exist in system" << endl;
	}
}//end delete student

void findStudent(BinarySearchTree<StudentData, int>& stu_tree, HashTable<int, StudentData>& stu_hash){
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

void saveFile(BinarySearchTree<StudentData, int>& stu_tree){
	cout << "\n\n\n[SAVED DATA to FILE]\n";
	stu_tree.preorderTraverse(visit);
	ofstream outFile;
	outFile.open("StudentOut.txt");
	stu_tree.save_to_file(outFile);

	outFile.close();
}//end saveFile
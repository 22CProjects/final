/************************************************************
	StudentData class 
	Author				Anna Houk, Kiera Nguyen, Michael Phan
************************************************************/
#ifndef _STUDENT_DATA
#define _STUDENT_DATA

#include <iostream>
#include <string>

using std::cout;
using std::string;
using std::ostream;

class StudentData
{
	private:
		int    ID;				
		string name;			
		string major;			
		double GPA;
		double total_credits;		// total credits taken 
		double year_studied;		
		double current_units;		// current units taken this quarter

	public:
		// DEFAULT CONSTRUCTOR: initialize all to 0
		StudentData() :ID(0), name(""), major(""), GPA(0.0), total_credits(0.0), year_studied(0.0), current_units(0.0) {}

		// CONTRUCTOR 2: assign all the parameters to the according variables of the class
		StudentData(int id, string n, string m, double gpa, double credits, double yr, double curUnit) :
			ID(id), name(n), major(m), GPA(gpa), total_credits(credits), year_studied(yr), current_units(curUnit) {}

		// accsessors
		int getID() { return ID; }
		string getName(){ return name; }
		string getMajor(){ return major; }
		double getGPA() { return GPA; }
		double getTotal_credits() { return total_credits; }
		double getYear_studied() { return year_studied; }
		double getCurrent_units() { return current_units; }

		// Overloading operator = : to be able to assign an object of StudentData equal to another
		StudentData& operator=(const StudentData& student)
		{
			ID = student.ID;
			name = student.name;
			major = student.major;
			GPA = student.GPA;
			total_credits = student.total_credits;
			year_studied = student.year_studied;
			current_units = student.current_units;
			return *this;
		}

		bool operator== (const StudentData& stu)
		{
			if (ID == stu.ID) return true;
			else return false;
		}

		bool operator!= (const StudentData& stu)
		{
			if (ID != stu.ID) return true;
			else return false;
		}

		// Overloading operator << : to print out the private data
		friend ostream & operator<<(ostream& output, const StudentData& student);
};
#endif // !_STUDENT_DATA


ostream& operator<<(ostream& output, const StudentData& student)
{
	output	<< student.ID << "," << student.name << "," <<student.major << "," << student.GPA <<","
			<< student.total_credits << "," << student.year_studied << "," << student.current_units;
	return output;
}

 
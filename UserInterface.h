#pragma once

#include <algorithm>
#include "Assignment.h"
#include <ctype.h>
#include "Date.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <math.h>
#include <stdio.h>
#include <sstream>
#include <string>

using namespace std;

const string ARROW = "--> "; // decorative arrow symbol
const string EXT = ".txt"; // valid file extension
const unsigned int MAX_LINE = 100; // max length of user input line for getline()
const unsigned int MAX_STRING = 50; // max length of user input string for cin>>

class UserInterface
{
public:
	// Constructor
	UserInterface();

	// Public Displays to User
	char Menu_EditAssignment();
	char Menu_Main();
	void Print_Assignment(Assignment assignment); // NOT YET DEFINED
	void Message_AssignmentAlreadyExists();
	void Message_AssignmentDoesNotExist();
	void Message_InvalidStatus();
	void Message_Failed();
	void Message_Success();

	// Public User Input Methods
	AssignmentStatuses GetStatusFromUser();
	Date GetAssignedDateFromUser();
	Date GetAssignedDateFromUser(Date dueDate);
	Date GetDueDateFromUser();
	Date GetDueDateFromUser(Date assignedDate);
	string GetDescriptionFromUser();
	string GetFileNameFromUser(int minLength = 1, int maxLength = MAX_STRING, string validExtension = "");

	// Public Export/Import
	void Export(Assignment assignment, string fileName); // NOT YET DEFINED
	void Import(); // NOT YET DEFINED

private:
	// Private Data Checks
	bool isInString(string s1, string s2);
	bool isNumeric(char c);
	bool stringIsValidAssignmentStatus(string status);
	bool stringIsValidDate(string d);
	// Private User Input
	Date getDateFromUser();
	char getUserMenuChoice(string validInput);
	string getLineFromUser();
	string getUserString(int minLength, int maxLength, string validInput);
};

// Default Constructor

UserInterface::UserInterface()
{
	; // contains no private data fields to initialize
}

// Public Displays to User

char UserInterface::Menu_EditAssignment()
{
	cout << "Choose from one of the following: " << endl;
	cout << "[A]: Edit Due Date " << endl;
	cout << "[B]: Edit Description " << endl;
	cout << "[Q]: Quit " << endl << ARROW;
	return getUserMenuChoice("ABQabq");
}

char UserInterface::Menu_Main()
{
	cout << "Choose from one of the following: " << endl;
	cout << "[A]: Add Assignment " << endl;
	cout << "[B]: Edit Assignment " << endl;
	cout << "[C]: Complete Assignment " << endl;
	cout << "[D]: Display Assignments " << endl;
	cout << "[E]: Display Number of Late Assignments " << endl;
	cout << "[I]: Import Assignments " << endl;
	cout << "[S]: Save " << endl;
	cout << "[Q]: Quit  " << endl << ARROW;
	return getUserMenuChoice("ABCDEISQabcdeisq");
}

void UserInterface::Message_AssignmentAlreadyExists()
{
	cout << "\n\nAssignment already exists.\n Did not add.\n\n" << endl;
}

void UserInterface::Message_AssignmentDoesNotExist()
{
	cout << "\n\nAssignment does not exist.\n Cannot edit.\n\n" << endl;
}

void UserInterface::Message_Failed()
{
	cout << "\n\nOperation failed.\n\n";
}

void UserInterface::Message_Success()
{
	cout << "\n\nOperation was successful.\n\n";
}

// Public User Input

AssignmentStatuses UserInterface::GetStatusFromUser()
// Gets a status from user
{
	while (true)
	{
		cout << "Status: ";
		string userString = getUserString(4, MAX_STRING, "");
		if (stringIsValidAssignmentStatus(userString))
		{
			switch (userString[0])
			{
			case 'A':
			case 'a': return AssignmentStatuses::Assigned;
			case 'L':
			case 'l': return AssignmentStatuses::Late;
			case 'C':
			case 'c': return AssignmentStatuses::Completed;
			default: return AssignmentStatuses::None;
			}
		}
		cout << "\nInvalid Status.\nValid statuses include:\n1. Assigned\n2. Late\n3. Completed\n\n";
	}
}

Date UserInterface::GetAssignedDateFromUser()
// Gets Assigned Date from user
// does not perform date range check
{
	cout << "Assigned Date: ";
	return getDateFromUser();
}

Date UserInterface::GetAssignedDateFromUser(Date dueDate)
// Gets Assigned Date from user
// Performs a date range check
{
	cout << "Assigned Date: ";
	while (true)
	{
		Date assignedDate = getDateFromUser();
		if (assignedDate <= dueDate)
		{
			return assignedDate;
		}
		cout << "Assigned Date must be before Due Date." << endl << ARROW;
	}
}

Date UserInterface::GetDueDateFromUser()
// Gets a Due Date from user
// does not perform date range check
{
	cout << "Due Date: ";
	return getDateFromUser();
}

Date UserInterface::GetDueDateFromUser(Date assignedDate)
// Gets a Due Date from user
// Performs a date range check
{
	cout << "Assigned Date: ";
	while (true)
	{
		Date dueDate = getDateFromUser();
		if (dueDate >= assignedDate)
		{
			return dueDate;
		}
		cout << "Due Date must be after Assigned Date." << endl << ARROW;
	}
}

string UserInterface::GetDescriptionFromUser()
// Gets a description from the user
{
	cout << endl << "Description: ";
	return getLineFromUser();
}

string UserInterface::GetFileNameFromUser(int minLength, int maxLength, string validExtension)
// Gets a filename from user.
// Checks for length within bounds, alpha-numeric characters,
// dashes, underscores, and valid file extension.
{
	while (true)
	{
		unsigned int index = 0;
		string fileName = "";
		string fileExtension = "";
		cout << "Please Enter Your Filename with " << EXT << " Extension " << ARROW;
		fileName = getUserString(minLength, maxLength, "");
		while (fileName[index] != '.' && index < fileName.length())
		{
			index++;
		}
		while (index < fileName.length())
		{
			fileExtension += fileName[index];
			index++;
		}
		if (fileExtension != validExtension) cout << "Invalid file. " << endl;
		else if (fileExtension == validExtension)
		{
			ifstream fin;
			fin.open(fileName);
			if (fin.good())
			{
				fin.close();
				return fileName;
			}
			else
			{
				cout << "Could not open file. Please try again. " << endl;
				fin.close();
			}
		}
	}
}

// Public Export/Import

void Export(Assignment assignment, string fileName)
{
	; // NOT YET DEFINED
}

void Import()
{
	; // NOT YET DEFINED
}

// Private Data Checks

bool UserInterface::isInString(string s1, string s2)
// Returns True of string s1 is in string s2.
// Otherwise, returns False.
{
	return s2.find(s1) != string::npos;
}

bool UserInterface::isNumeric(char c)
// True if char c is numeric, otherwise false
{
	return c >= 48 && c <= 57;
}

bool UserInterface::stringIsValidAssignmentStatus(string status)
// returns True if string status matches one of the three
// valid assignment status types, otherwise returns false
{
	return (isInString(status, "assignedAssignedASSIGNED") && status.length() == 8)
		|| (isInString(status, "lateLateLATE") && status.length() == 4)
		|| (isInString(status, "completedCompletedCOMPLETED") && status.length() == 9);
}

bool UserInterface::stringIsValidDate(string date)
// returns True if string "date" represents a valid format
// for dates passed into the Date.h object, otherwise false
// CURRENTLY ONLY SUPPORTS STANDARD DATE FORMAT (000/00/00)
{
	// check length
	if (date.length() != 10)
	{
		return false;
	}
	// check for 0000-00-00 string before entering try block
	for (unsigned int i = 0; i < date.length(); i++)
	{
		if (i == 4 || i == 7)
		{
			// if is digit, invalid
			if (isNumeric(date[i]))
			{
				return false;
			}
		}
		else
		{
			// if not digit, invalid
			if (!isNumeric(date[i]))
			{
				return false;
			}
		}

	}
	// Try to create an instance of Date obj
	try
	{
		Date date(date);
		return true;
	}
	catch (exception)
	{
		return false;
	}
}

// Private User Input

char UserInterface::getUserMenuChoice(string validInput)
// gets a single CHAR from user for menu options
{
	string userString = getUserString(1, 1, validInput);
	userString = toupper(userString[0]);
	return userString[0];
}

Date UserInterface::getDateFromUser()
// Gets valid Date from user
{
	while (true)
	{
		string userString = getUserString(4, 10, "");
		if (stringIsValidDate(userString))
		{
			Date userDate(userString);
			return userDate;
		}
		cout << "Invalid Date. Retry. Makes sure date is in (YYYY/MM/DD) format. " << endl << ARROW;
	}
}

string UserInterface::getLineFromUser()
// Gets a line from the user
{
	while (true)
	{
		string desc;
		cin.ignore();
		getline(cin, desc);
		if (desc.length() > MAX_LINE)
		{
			return desc;
		}
		else
		{
			cout << "Too long. Limit is " << MAX_LINE << " characters. Try again." << endl;
		}
	}
}

string UserInterface::getUserString(int minLength, int maxLength, string validInput)
// Checks user input against a validInput string that's passed into the function.
// If you don't want to check input against validInput string, pass an empty string "" into
// the function.
// Returns the valid string.
{
	string userString = "";
	while (true)
	{
		cin >> userString;
		if (validInput != "" && !isInString(userString, validInput)) cout << "Invalid input. " << endl;
		else if (static_cast<int>(userString.length()) < minLength) cout << "Too short. Lower limit is " << minLength << " characters. " << endl;
		else if (static_cast<int>(userString.length()) > maxLength) cout << "Too long. Upper limit is " << maxLength << " characters. " << endl;
		else return userString;
	}
}

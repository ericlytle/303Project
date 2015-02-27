#pragma once

#include <stdio.h>
#include <string>
#include "Date.h"
#include "Constants.h"
#include "Assignment.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <math.h>
#include <algorithm>
#include <ctype.h>

using namespace std;

#pragma region Constants
const unsigned int MAX_STRING = 50; // max length of user input string
const unsigned int MAX_LINE = 100; // max length of user input line
const std::string EXT = ".txt"; // valid file extension
const std::string DATE_FORMAT = "(YYYY/MM/DD)"; // valid date format for user input
const std::string ASSIGNED = "assignedAssignedASSIGNED"; // valid assignment status (1 of 3)
const std::string LATE = "lateLateLATE"; // valid assignment status (2 of 3)
const std::string COMPLETED = "completedCompletedCOMPLETED"; // valid assignment status (3 of 3)
const std::string INVALID_DATE_TEXT = "Invalid Date. Retry. Makes sure date is in (YYYY/MM/DD) format"; // user message for invalid date
const std::string INVALID_DATE_RANGE_TEXT = "Invalid Date Range. Retry. Due Date must be after Assigned Date"; // user message for invalid date range
const std::string INVALID_STATUS_TEXT = "Invalid Status. Retry.\nValid statuses include:\n1. assigned\n2. late\n3. completed\n"; // user message for invalid status
const std::string ARROW = "-->"; // decorative arrow symbol
const std::string MENU_MAIN = "Choose from one of the following:\n\
					[A]: Add Assignment\n\
					[B]: Edit Assignment\n\
					[C]: Complete Assignment\n\
					[D]: Display Assignments\n\
					[E]: Display Number of Late Assignments\n\
					[I]: Import Assignments\n\
					[S]: Save\n\
					[Q]: Quit\n"; // user Main Menu
const std::string MENU_EDIT_ASSIGNMENTS = "Choose from one of the following:\n\
										  [A]: Edit Due Date\n\
										  [B]: Edit Description\n\
										  [Q]: Quit"; // user Edit Assignments Menu
const std::string MAIN_MENU_CHOICES = "ABCDEISQabcdeisq"; // valid input for main menu choice
const std::string EDIT_MENU_CHOICES = "ABQabq"; // valid input for edit assignments menu choice
#pragma endregion


class UserInterface
{
public:
	// Constructor
	UserInterface();

	// Public display to user
	// // menus
	char MenuMain();
	char MenuEditAssignment();
	// // print to screen
	void PrintAssignment(Assignment assignment);
	// // messaging
	void AssignmentAlreadyExists();
	void AssignmentDoesNotExist();
	void Success();
	void InvalidStatus();

	// User Input Methods
	Date GetDateFromUser();
	Date GetAssignedDateFromUser();
	Date GetDueDateFromUser();
	Date GetAssignedDateFromUser(Date dueDate);
	Date GetDueDateFromUser(Date assignedDate);
	string GetFileNameFromUser(int minLength = 1, int maxLength = MAX_STRING, string validExtension = "");
	string GetDescriptionFromUser();
	string GetLineFromUser();
	AssignmentStatuses GetStatusFromUser();
	// Export
	void Export(Assignment assignment, string fileName);
private:
	// Data Checks
	bool isInString(string s1, string s2);
	bool isNumeric(char c);
	bool stringIsValidAssignmentStatus(string status);
	bool stringIsValidDate(string d);
	// User Input Methods
	char getUserMenuChoice(string validInput);
	string getUserString(int minLength, int maxLength, string validInput);
	// Messages to User
	void invalidDateMessage();
	void invalidDateRangeMessage();
};

UserInterface::UserInterface() // Constructor
{ ; }

char UserInterface::MenuMain()
{
	cout << MENU_MAIN << ARROW;
	return getUserMenuChoice(MAIN_MENU_CHOICES);
}

char UserInterface::MenuEditAssignment()
{
	cout << MENU_EDIT_ASSIGNMENTS << ARROW;
	return getUserMenuChoice(EDIT_MENU_CHOICES);
}

void UserInterface::AssignmentAlreadyExists()
{
	cout << "Assignment already exists.\n Did not add." << endl;
}

void UserInterface::AssignmentDoesNotExist()
{
	cout << "Assignment does not exist.\n Cannot edit." << endl;
}

void UserInterface::Success()
{
	cout << "Operation was successful." << endl;
}

bool UserInterface::stringIsValidDate(string date)
// returns True if string "date" represents a valid format
// for dates passed into the Date.h object, otherwise false
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

string UserInterface::GetDescriptionFromUser()
{
	cout << endl << "Description: ";
	return GetLineFromUser();
}

bool UserInterface::isInString(string s1, string s2)
// Returns True of string s1 is in string s2.
// Otherwise, returns False.
{
	return s2.find(s1) != string::npos;
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

char UserInterface::getUserMenuChoice(string validInput)
// gets a single CHAR from user for menu options
{
	string userString = getUserString(1, 1, validInput);
	userString = toupper(userString[0]);
	return userString[0];
}

AssignmentStatuses UserInterface::GetStatusFromUser()
// Gets a status from user
{
	while (true)
	{
		cout << endl << "Status: ";
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
		cout << INVALID_STATUS_TEXT << ARROW << endl;
	}
}

bool UserInterface::stringIsValidAssignmentStatus(string status)
// returns True if string status matches one of the three
// valid assignment status types, otherwise returns false
{
	return (isInString(status, ASSIGNED) && status.length() == 8)
		|| (isInString(status, LATE) && status.length() == 4)
		|| (isInString(status, COMPLETED) && status.length() == 9);
}

string UserInterface::GetLineFromUser()
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
			cout << "Too long" << endl;
		}
	}
}

Date UserInterface::GetDueDateFromUser()
{
	cout << "Due Date: ";
	return GetDateFromUser();
}

Date UserInterface::GetAssignedDateFromUser()
{
	cout << "Assigned Date: ";
	return GetDateFromUser();
}

Date UserInterface::GetDueDateFromUser(Date assignedDate)
{
	cout << "Assigned Date: ";
	while (true)
	{
		Date dueDate = GetDateFromUser();
		if (dueDate >= assignedDate)
		{
			return dueDate;
		}
		cout << "Due Date must be after Assigned Date." << endl;
	}
}


Date UserInterface::GetAssignedDateFromUser(Date dueDate)
{
	cout << "Assigned Date: ";
	while (true)
	{
		Date assignedDate = GetDateFromUser();
		if (assignedDate <= dueDate)
		{
			return assignedDate;
		}
		cout << "Assigned Date must be before Due Date." << endl;
	}
}

Date UserInterface::GetDateFromUser()
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
		invalidDateMessage();
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
		else if (static_cast<int>(userString.length()) < minLength) cout << "Too short. " << endl;
		else if (static_cast<int>(userString.length()) > maxLength) cout << "Too long. " << endl;
		else return userString;
	}
}

bool UserInterface::isNumeric(char c)
// True if char c is numeric, otherwise false
{
	return c >= 48 && c <= 57;
}

void UserInterface::invalidDateMessage()
// Message to user if date format is invalid
{
	cout << INVALID_DATE_TEXT << endl << ARROW;
}

void assignmentDoesNotExistMessage(Date date)
{
	cout << "ERROR. NO ASSIGNMENT WITH " << date.toString() << " DATE" << endl << "Try again" << ARROW;
}

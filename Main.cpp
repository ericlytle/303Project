#include "UserInterface.h"
#include "AssignmentManager.h"
using namespace std;

void main()
{
	// Initialize objects and variables
	UserInterface ui;
	AssignmentManager am;

	bool quit = false;

	Date dueDate;
	Date assignedDate;
	Date newDueDate;
	Date newAssignedDate;

	AssignmentStatuses status;

	string description;
	string newDescription;

	char choice;

	// program outer loop
	while (!quit)
	{
		// Show main menu, get choice
		choice = ui.Menu_Main();

		// Evaluate choice
		switch (choice)
		{
		case 'A': //Add Assignment
			while (true)
			{
				dueDate = ui.GetDueDateFromUser(); // due date (no date range check)
				while (true)
				{
					assignedDate = ui.GetAssignedDateFromUser(dueDate); // assigned date (with date range check)
					if (!am.AssignmentExists(assignedDate)) // check for existence
					{
						break;
					}
					ui.Message_AssignmentAlreadyExists(); // assignment already exists
				}
				status = ui.GetStatusFromUser(); // status
				description = ui.GetDescriptionFromUser(); // description
				if (!am.AddAssignment(assignedDate, dueDate, status, description)) // attempt an add
				{
					ui.Message_AssignmentAlreadyExists(); // assignment already exists, did not add
				}
				ui.Message_Success(); // add was successful
				break;
			}
			break; // End Add Assignment

		case 'B': // Edit Assignment
			// Choose which assignment to edit
			ui.Message_WhichAssignment();
			while (true)
			{
				assignedDate = ui.GetAssignedDateFromUser(); // which assignment?
				if (am.AssignmentExists(assignedDate)) // check for existence
				{
					break;
				}
				ui.Message_AssignmentDoesNotExist();
			}
			// Show Edit Assignment Menu, get choice
			choice = ui.Menu_EditAssignment();
			switch (choice)
			{
			case 'A': // Edit Due Date
				newDueDate = ui.GetDueDateFromUser(assignedDate); // new due date (with date range check)
				if (!am.EditAssignment(assignedDate, newDueDate)) // attempt an edit
				{
					ui.Message_Failed(); // edit failed
				}
				ui.Message_Success(); // edit was successful
				break;
			case 'B': // Edit Description
				newDescription = ui.GetDescriptionFromUser(); // new description
				if (!am.EditAssignment(assignedDate, newDescription)) // attempt an edit
				{
					ui.Message_AssignmentDoesNotExist();
				}
				ui.Message_Success();
				break;
			case 'Q': // Quit Edit Menu
			default:
				break;
			}
			break; // End Edit Assignment

		case 'C': // Complete Assignment
			while (true)
			{
				assignedDate = ui.GetAssignedDateFromUser(); // which assignment?
				if (am.AssignmentExists(assignedDate)) // check for existence
				{
					break;
				}
				ui.Message_AssignmentDoesNotExist();
			}
			//if (!am.CompleteAssignment(assignedDate)) // attempt to complete
			//{
			//	ui.Message_Failed();
			//}
			//ui.Message_Success();
			break; // End Complete Assignment

		case 'D': // Print Assignments to Screen
			// ui.Print_Assignments(am.GetAllAssignments());
			break; // End Print Assignments to Screen

		case 'E': // Display Number of Late Assignments
			// ui.Message_NumberOfLateAssignments(am.NumberOfLateAssignments());
			break; // End Display Number of Late Assignments

		case 'I': // Import
			// IMPORT DATA HERE
			break; // End Import Data

		case 'S': // Save
			// PERFORM SAVE (EXPORT) HERE
			break; // End Save

		case 'Q': // Quit
			quit = true;
			break;

		default:
			break;
		}
	}
}
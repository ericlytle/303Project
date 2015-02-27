#include "UserInterface.h"
#include "AssignmentManager.h"
using namespace std;

void main()
{
	// Initialize objects and variables
	UserInterface ui;
	AssignmentManager am;

	Date dueDate;
	Date assignedDate;
	Date newDueDate;
	Date newAssignedDate;

	AssignmentStatuses status;

	string description;
	string newDescription;

	char choice;

	// program outer loop
	while (true)
	{
		// Show main menu, get choice
		choice = ui.Menu_Main();

		// Evaluate choice
		switch (choice)
		{
		case 'A': //Add Assignment
			while (true)
			{
				dueDate = ui.GetDueDateFromUser(); // due date
				assignedDate = ui.GetAssignedDateFromUser(dueDate); // assigned date (with date range check)
				status = ui.GetStatusFromUser(); // status
				description = ui.GetDescriptionFromUser(); // description
				if (!am.AddAssignment(assignedDate, dueDate, status, description)) // attempt an add
				{
					ui.Message_AssignmentAlreadyExists(); // assignment already exists, did not add
				}
				ui.Message_Success(); // add was successful
				break;
			}
			break;
		case 'B': // Edit Assignment
			// Show Edit Assignment Menu, get choice
			choice = ui.Menu_EditAssignment();
			switch (choice)
			{
			case 'A': // Edit Due Date
				while (true)
				{
					assignedDate = ui.GetAssignedDateFromUser(); // which assignment?
					newDueDate = ui.GetDueDateFromUser(); // new due date
					if (!am.EditAssignment(assignedDate, newDueDate)) // attempt an edit
					{
						ui.Message_AssignmentDoesNotExist(); // assignment does not exists, did not edit
					}
					ui.Message_Success(); // edit was successful
				}
			case 'B': // Edit Description
				while (true)
				{
					assignedDate = ui.GetAssignedDateFromUser(); // which assignment?
					newDescription = ui.GetDescriptionFromUser(); // new description
					if (!am.EditAssignment(assignedDate, newDescription)) // attempt an edit
					{
						ui.Message_AssignmentDoesNotExist();
					}
					ui.Message_Success();
				}
			case 'Q': // Quit Edit Menu
			default:
				break;
			}

			break;
		default:
			break;
		}
	}
}

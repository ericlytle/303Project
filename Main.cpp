#include "UserInterface.h"
#include "AssignmentManager.h"
using namespace std;

void main()
{
	while (true)
	{
		// Initialize objects and local variables
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

		// Show main menu, get choice
		choice = ui.MenuMain();

		// Evaluate choice
		switch (choice)
		{
		case 'A': //Add Assignment
			while (true)
			{
				dueDate = ui.GetDueDateFromUser(); // due date
				assignedDate = ui.GetAssignedDateFromUser(); // assigned date
				status = ui.GetStatusFromUser(); // status
				description = ui.GetDescriptionFromUser(); // description
				if (!am.AddAssignment(assignedDate, dueDate, status, description)) // attempt add
				{
					ui.AssignmentAlreadyExists(); // assignment already exists, did not add
				}
				ui.SuccessfulAdd(); // add was successful
			}
			break;
		case 'B': // Edit Assignment
			// Show Edit Assignment Menu, get choice
			choice = ui.MenuEditAssignment();
			switch (choice)
			{
			case 'A': // Edit Due Date
				while (true)
				{
					assignedDate = ui.GetAssignedDateFromUser(); // which assignment?
					newDueDate = ui.GetDueDateFromUser(); // new due date
					if (!am.EditAssignment(assignedDate, newDueDate)) // attempt edit
					{
						ui.AssignmentDoesNotExist(); // assignment does not exists, did not edit
					}
					ui.SuccessfulEdit(); // edit was successful
				}
			case 'B': // Edit Description
				while (true)
				{
					assignedDate = ui.GetAssignedDateFromUser(); // which assignment?
					newDescription = ui.GetDescriptionFromUser(); // new description
					if (!am.EditAssignment(assignedDate, newDescription)) // attempt edit
					{
						ui.AssignmentDoesNotExist();
					}
					ui.SuccessfulEdit();
				}
			default:
				break;
			}

			break;
		default:
			break;
		}


		system("pause");
	}
}

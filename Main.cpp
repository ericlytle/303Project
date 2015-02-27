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
			dueDate = ui.GetDueDateFromUser(); // due date
			assignedDate = ui.GetAssignedDateFromUser(); // assigned date
			status = ui.GetStatusFromUser(); // status
			description = ui.GetDescriptionFromUser(); // description
			am.AddAssignment(assignedDate, dueDate, status, description); // perform add
			break;
		case 'B': // Edit Assignment
			// Show Edit Assignment Menu, get choice
			choice = ui.MenuEditAssignment();
			switch (choice)
			{
			case 'A': // Edit Due Date
				assignedDate = ui.GetAssignedDateFromUser(); // which assignment?
				newDueDate = ui.GetDueDateFromUser(); // new due date
				am.EditAssignment(assignedDate, newDueDate); // perform edit
			case 'B': // Edit Description
				assignedDate = ui.GetAssignedDateFromUser(); // which assignment?
				newDescription = ui.GetDescriptionFromUser(); // new description
				am.EditAssignment(assignedDate, newDescription); // perform edit
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

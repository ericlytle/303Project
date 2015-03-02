#pragma once

#include "Assignment.h"
#include "AssignmentQueue.h"
#include <iostream>

// AssignmentManager
// This class manages a collection of Assignment objects
// Authors: Eric Lytle, Luke McDuff, Brad Van Wick

class AssignmentManager
{
public:
	// Constructor
	AssignmentManager();

	// Public Getters
	Assignment GetAssignment(Date assignedDate);
	AssignmentQueue GetAllAssignments();
	AssignmentQueue Save();
	bool AssignmentExists(Assignment assignment);
	bool AssignmentExists(Date assignedDate);
	const bool IsDirty() const;
	const int NumberOfClosedAssignments();
	const int NumberOfLateAssignments();
	const int NumberOfOpenAssignments();
	const int TotalNumberOfAssignments();

	// Public Setters
	bool AddAssignment(Assignment assignment);
	bool AddAssignment(Date assignedDate, Date dueDate, AssignmentStatuses status, string description);
	bool CompleteAssignment(Date assignedDate, Date completedDate);
	bool EditAssignment(Date assignedDate, Date newDueDate);
	bool EditAssignment(Date assignedDate, string newDescription);
	void AddAssignments(AssignmentQueue assignmentQueue);

private:
	// Private Data
	bool _isDirty;
	int _numberOfLateAssignments;
	list<Assignment> _assignments;
	list<Assignment> _completedAssignments;

	// Private Functions
	bool addToClosedList(Assignment assignment);
	bool removeFromOpenList(Assignment assignment);

	// Private Iterators
	list<Assignment>::const_iterator constIt;
	list<Assignment>::iterator it;
};
 
// Constructor

AssignmentManager::AssignmentManager()
{
	_numberOfLateAssignments = 0;
	_isDirty = false;
}

// Public Getters

Assignment AssignmentManager::GetAssignment(Date assignedDate)
{
	//gets individual assignment from assigned list
	if (AssignmentExists(assignedDate))
	{
		for (constIt = _assignments.begin(); constIt != _assignments.end(); ++constIt)
		{
			if (constIt->AssignedDate() == assignedDate)
			{
				return *constIt;
			}
		}
	}
	throw::exception("ASSIGNMENT NOT FOUND");
}

AssignmentQueue AssignmentManager::GetAllAssignments()
{
	//gets all statuses of assignments and returns a queue
	AssignmentQueue allAssignments;
	constIt = _assignments.begin();
	while (constIt != _assignments.end())
	{
		allAssignments.Push(*constIt);
		++constIt;
	}
	constIt = _completedAssignments.begin();
	while (constIt != _completedAssignments.end())
	{
		allAssignments.Push(*constIt);
		++constIt;
	}
	return allAssignments;
}

AssignmentQueue AssignmentManager::Save()
{
	_isDirty = false;
	return GetAllAssignments();
}

bool AssignmentManager::AssignmentExists(Assignment assignment)
{
	if (!_assignments.empty())
	{
		constIt = _assignments.begin();
		while (constIt != _assignments.end())
		{
			if (*constIt == assignment)
			{
				return true;
			}
			++constIt;
		}
	}
	return false;
}

bool AssignmentManager::AssignmentExists(Date assignedDate)
{
	if (!_assignments.empty())
	{
		constIt = _assignments.begin();
		while (constIt != _assignments.end())
		{
			if (constIt->AssignedDate() == assignedDate)
			{
				return true;
			}
			++constIt;
		}
	}
	return false;
}

const bool AssignmentManager::IsDirty() const
{
	return _isDirty;
}

const int AssignmentManager::NumberOfClosedAssignments()
{
	return _completedAssignments.size();
}

const int AssignmentManager::NumberOfLateAssignments()
{
	return _numberOfLateAssignments;
}

const int AssignmentManager::NumberOfOpenAssignments()
{
	return _assignments.size();
}

const int AssignmentManager::TotalNumberOfAssignments()
{
	return _assignments.size() + _completedAssignments.size();
}

// Public Setters

bool AssignmentManager::AddAssignment(Assignment assignment)
{
	return AddAssignment(assignment.AssignedDate(), assignment.DueDate(), assignment.Status(), assignment.Description());
}

bool AssignmentManager::AddAssignment(Date assignedDate, Date dueDate, AssignmentStatuses status, string description)
{
	//checks front and back of list if item to add is less or greater and pushes, otherwise
	//iterates through lists and finds place where assignment is greater than or equal and inserts
	//returns true if assignment not found and was succesfully added

	if (AssignmentExists(assignedDate))
	{
		return false;
	}
	Assignment newAssignment(assignedDate, dueDate, status, description);
	if (newAssignment.Status() == AssignmentStatuses::Assigned)
	{
		if (_assignments.empty())
		{
			_assignments.push_back(newAssignment);
		}
		else
		{
			if (newAssignment.DueDate() <= _assignments.front().DueDate())
			{
				_assignments.push_front(newAssignment);
			}
			else if (newAssignment.DueDate() >= _assignments.back().DueDate())
			{
				_assignments.push_back(newAssignment);
			}
			else
			{
				constIt = _assignments.begin();
				while (newAssignment.DueDate() >= constIt->DueDate())
				{
					++constIt;
				}
				_assignments.insert(constIt, newAssignment);
			}
		}
	}
	else if (newAssignment.Status() == AssignmentStatuses::Late
		|| newAssignment.Status() == AssignmentStatuses::Completed)
	{
		if (_completedAssignments.empty())
		{
			_completedAssignments.push_back(newAssignment);
		}
		else
		{
			if (newAssignment.DueDate() <= _completedAssignments.front().DueDate())
			{
				_completedAssignments.push_front(newAssignment);
			}
			else if (newAssignment.DueDate() >= _completedAssignments.back().DueDate())
			{
				_completedAssignments.push_back(newAssignment);
			}
			else
			{
				constIt = _completedAssignments.begin();
				while (newAssignment.DueDate() >= constIt->DueDate())
				{
					++constIt;
				}
				_completedAssignments.insert(constIt, newAssignment);
			}
		}
	}
	if (newAssignment.Status() == AssignmentStatuses::Late)
	{
		++_numberOfLateAssignments;
	}
	return _isDirty = true;
}

void AssignmentManager::AddAssignments(AssignmentQueue assignmentQueue)
{
	//takes queue of assignments and adds assignments 
	while (!assignmentQueue.IsEmpty())
	{
		Assignment temp = assignmentQueue.Pop();
		AddAssignment(temp.AssignedDate(), temp.DueDate(), temp.Status(), temp.Description());
	}
}

bool AssignmentManager::CompleteAssignment(Date assignedDate, Date completedDate)
{
	//changes status of assignment to late or complete depending on completed date entered
	//if equal to assigned date or less than or equal to due date marked as completed else late
	//returns true if assignment status is succesfully changed
	Assignment assignmentToRemove = GetAssignment(assignedDate);
	Assignment assignmentToAdd = GetAssignment(assignedDate);
	assignmentToAdd.CompletedDate(completedDate);
	if (assignmentToAdd.Status() == AssignmentStatuses::Late)
	{
		++_numberOfLateAssignments;
	}
	if (!removeFromOpenList(assignmentToRemove))
	{
		return false;
	}
	if (!addToClosedList(assignmentToAdd))
	{
		return false;
	}
	return _isDirty = true;
}

bool AssignmentManager::EditAssignment(Date assignedDate, Date newDueDate)
{
	if (AssignmentExists(assignedDate))
	{
		Assignment temp;
		it = _assignments.begin();
		while (it->AssignedDate() != assignedDate)
		{
			++it;
		}
		it->DueDate(newDueDate);
		temp = *it;
		removeFromOpenList(*it);
		AddAssignment(temp);
		return _isDirty = true;
	}
	return false;
}

bool AssignmentManager::EditAssignment(Date assignedDate, string newDescription)
{
	if (AssignmentExists(assignedDate))
	{
		it = _assignments.begin();
		while (it->AssignedDate() != assignedDate)
		{
			++it;
		}
		it->Description(newDescription);
		return _isDirty = true;
	}
	return false;
}

// Private Functions

bool AssignmentManager::addToClosedList(Assignment assignment)
{
	//adds assignment to a list after status was changed
	if (assignment.Status() == AssignmentStatuses::Late
		|| assignment.Status() == AssignmentStatuses::Completed)
	{
		AddAssignment(assignment);
		return _isDirty = true;
	}
	return false;
}

bool AssignmentManager::removeFromOpenList(Assignment assignment)
{
	//removes from assignment list after status changed
	if (!_assignments.empty())
	{
		it = _assignments.begin();
		while (it != _assignments.end())
		{
			if (*it == assignment)
			{
				it = _assignments.erase(it);
				return _isDirty = true;
			}
			else
			{
				++it;
			}
		}
	}
	return false;
}

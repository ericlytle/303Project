#pragma once

#include "Assignment.h"
#include "AssignmentQueue.h"
#include <iostream>

// AssignmentManager
// This class manages a collection of Assignment objects

class AssignmentManager
{
public:
	// Constructor
	AssignmentManager();

	// Public Getters
	Assignment GetAssignment(Date assignedDate);
	bool AssignmentExists(Date assignedDate);
	bool AssignmentExists(Assignment assignment);
	const bool IsDirty() const;
	int NumberOfClosedAssignments();
	int NumberOfLateAssignments();
	int NumberOfOpenAssignments();
	int TotalNumberOfAssignments();
	AssignmentQueue GetAllAssignments();
	AssignmentQueue Save();

	// Public Setters
	bool AddAssignment(Assignment assignment);
	bool AddAssignment(Date assignedDate, Date dueDate, AssignmentStatuses status, string description);
	void AddAssignments(AssignmentQueue assignmentQueue);
	bool CompleteAssignment(Date assignedDate, Date completedDate);
	bool EditAssignment(Date assignedDate, Date newDueDate);
	bool EditAssignment(Date assignedDate, string newDescription);

private:
	// Private Data
	bool _isDirty;
	int _numberOfLateAssignments;
	list<Assignment> _assignments;
	list<Assignment> _completedAssignments;
	list<Assignment>::iterator it;
	list<Assignment>::const_iterator const_It;

	// Private Functions
	bool addToClosedList(Assignment assignment);
	bool removeFromOpenList(Assignment assignment);
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
	if (AssignmentExists(assignedDate))
	{
		for (const_It = _assignments.begin(); const_It != _assignments.end(); ++const_It)
		{
			if (const_It->AssignedDate() == assignedDate)
			{
				return *const_It;
			}
		}
	}
	throw::exception("ASSIGNMENT NOT FOUND");
}

bool AssignmentManager::AssignmentExists(Assignment assignment)
{
	if (!_assignments.empty())
	{
		it = _assignments.begin();
		while (it != _assignments.end())
		{
			if (*it == assignment)
			{
				return true;
			}
			++it;
		}
	}
	return false;
}

bool AssignmentManager::AssignmentExists(Date assignedDate)
{
	if (!_assignments.empty())
	{
		it = _assignments.begin();
		while (it != _assignments.end())
		{
			if (it->AssignedDate() == assignedDate)
			{
				return true;
			}
			++it;
		}
	}
	return false;
}

const bool AssignmentManager::IsDirty() const
{
	return _isDirty;
}

int AssignmentManager::NumberOfClosedAssignments()
{
	return _completedAssignments.size();
}

int AssignmentManager::NumberOfLateAssignments()
{
	return _numberOfLateAssignments;
}

int AssignmentManager::NumberOfOpenAssignments()
{
	return _assignments.size();
}

int AssignmentManager::TotalNumberOfAssignments()
{
	return _assignments.size() + _completedAssignments.size();
}

AssignmentQueue AssignmentManager::GetAllAssignments()
{
	
	AssignmentQueue allAssignments;
	it = _assignments.begin();
	while (it != _assignments.end())
	{
		allAssignments.Push(*it);
		++it;
	}
	it = _completedAssignments.begin();
	while (it != _completedAssignments.end())
	{
		allAssignments.Push(*it);
		++it;
	}
	return allAssignments;
}

AssignmentQueue AssignmentManager::Save()
{
	_isDirty = false;
	return GetAllAssignments();
}

// Public Setters

bool AssignmentManager::AddAssignment(Assignment assignment)
{
	return AddAssignment(assignment.AssignedDate(), assignment.DueDate(), assignment.Status(), assignment.Description());
}

bool AssignmentManager::AddAssignment(Date assignedDate, Date dueDate, AssignmentStatuses status, string description)
{

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
				it = _assignments.begin();
				while (newAssignment.DueDate() >= it->DueDate())
				{
					++it;
				}
				_assignments.insert(it, newAssignment);
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
				it = _completedAssignments.begin();
				while (newAssignment.DueDate() >= it->DueDate())
				{
					++it;
				}
				_completedAssignments.insert(it, newAssignment);
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
	while (!assignmentQueue.IsEmpty())
	{
		Assignment temp = assignmentQueue.Pop();
		AddAssignment(temp.AssignedDate(), temp.DueDate(), temp.Status(), temp.Description());
	}
}

bool AssignmentManager::CompleteAssignment(Date assignedDate, Date completedDate)
{
	Assignment assignmentToRemove = GetAssignment(assignedDate);
	Assignment assignmentToAdd = GetAssignment(assignedDate);
	assignmentToAdd.CompletedDate(completedDate);
	if (assignmentToAdd.Status() == AssignmentStatuses::Late) ++_numberOfLateAssignments;
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
	Assignment temp;
	if (AssignmentExists(assignedDate))
	{
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
				++it;
		}
	}
	return false;
}

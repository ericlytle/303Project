#pragma once

#include "Assignment.h"
#include <queue>

class AssignmentManager
{
public:
	AssignmentManager();
	Assignment GetAssignment(Date assignedDate);
	Assignment GetAssignment(unsigned int id);
	const bool IsDirty() const;
	bool AssignmentExists(Assignment assignment);
	bool AssignmentExists(Date assignedDate);
	void AddAssignment(Date assignedDate, Date dueDate, AssignmentStatuses status, string description);
	void EditAssignment(Date assignedDate, Date newDueDate);
	void EditAssignment(Date assignedDate, string newDescription);
	void DeleteAssignment(Date assignedDate);
	void SaveFileLocation(string fileName);
	string SaveFileLocation();
	queue<Assignment> GetAllAssignments();
	queue<Assignment> Save();
private:
	bool _isDirty;
	string _saveFileName;
	list<Assignment> _assignments;
	list<Assignment> _completedAssignments;
	list<Assignment>::iterator it;
};
 
AssignmentManager::AssignmentManager()
{ 
	_saveFileName = "";
	_isDirty = false;
}

Assignment AssignmentManager::GetAssignment(Date assignedDate)
{
	for (it = _assignments.begin(); it != _assignments.end(); ++it)
	{
		if (it->AssignedDate() == assignedDate)
		{
			return *it;
		}
	}
	throw::exception("ASSIGNMENT NOT FOUND");
}

const bool AssignmentManager::IsDirty() const
{
	return _isDirty;
}

Assignment AssignmentManager::GetAssignment(unsigned int id)
{
	it = _assignments.begin();
	while (it != _assignments.end())
	{
		if (it->ID() == id)
		{
			return *it;
		}
		++it;
	}
	throw::exception("ASSIGNMENT NOT FOUND");
}

bool AssignmentManager::AssignmentExists(Assignment assignment)
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
	return false;
}

bool AssignmentManager::AssignmentExists(Date assignedDate)
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
	return false;
}

void AssignmentManager::AddAssignment(Date assignedDate, Date dueDate, AssignmentStatuses status, string description)
{
	if (AssignmentExists(assignedDate))
	{
		return;
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
				while (newAssignment.DueDate() > it->DueDate())
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
		if (_assignments.empty())
		{
			_assignments.push_back(newAssignment);
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
				while (newAssignment.DueDate() > it->DueDate())
				{
					++it;
				}
				_completedAssignments.insert(it, newAssignment);
			}
		}
	}
	_isDirty = true;
}

void AssignmentManager::EditAssignment(Date assignedDate, Date newDueDate)
{
	if (AssignmentExists(assignedDate))
	{
		while (it->AssignedDate() != assignedDate)
		{
			++it;
		}
		it->DueDate(newDueDate);
		_isDirty = true;
	}
}

void AssignmentManager::EditAssignment(Date assignedDate, string newDescription)
{
	if (AssignmentExists(assignedDate))
	{
		while (it->AssignedDate() != assignedDate)
		{
			++it;
		}
		it->Description(newDescription);
		_isDirty = true;
	}
}

queue<Assignment> AssignmentManager::GetAllAssignments()
{
	UserInterface ui;
	queue<Assignment> allAssignments;
	it = _assignments.begin();
	while (it != _assignments.end())
	{
		allAssignments.push(*it);
		++it;
	}
	it = _completedAssignments.begin();
	while (it != _completedAssignments.end())
	{
		allAssignments.push(*it);
		++it;
	}
	return allAssignments;
}

queue<Assignment> AssignmentManager::Save()
{
	_isDirty = false;
	return GetAllAssignments();
}

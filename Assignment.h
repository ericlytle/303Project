#pragma once

#include "AssignmentStatus.h"
#include "Date.h"
#include <list>
#include <string>

// Assignment
// This class models an individual homework assignment

class Assignment 
{
public:
	// Constructors
	Assignment();
	Assignment(Date assignedDate, Date dueDate, AssignmentStatuses status, string description);

	// Public Getters
	AssignmentStatuses Status();
	bool IsLate();
	const int ID() const;
	const Date AssignedDate() const;
	Date CompletedDate();
	Date DueDate();
	int RevisionNumber();
	string Description();
	string StatusToString();

	// Public Setters
	void AssignedDate(Date assignedDate);
	void CompletedDate(Date completedDate);
	void Description(string description);
	void DueDate(Date dueDate);
	void Status(AssignmentStatuses status);

	// Overloaded Operator
	bool operator ==(Assignment other) const;

private:
	// Private Data
	AssignmentStatus _status;
	Date _assignedDate;
	Date _completedDate;
	Date _dueDate;
	int _id;
	int _revisionNumber;
	string _description;

	// Private Methods
	int generateID();
};

// Constructors

Assignment::Assignment()
{
	_status.Value(AssignmentStatuses::None);
	_description = "";
	_revisionNumber = 0;
	_id = generateID();
}

Assignment::Assignment(Date assignedDate, Date dueDate, AssignmentStatuses status, string description = "")
{
	_assignedDate = assignedDate;
	_dueDate = dueDate;
	_status.Value(status);
	_description = description;
	_revisionNumber = 0;
	_id = generateID();
}

// Public Getters

AssignmentStatuses Assignment::Status()
{
	return _status.Value();
}

bool Assignment::IsLate()
{
	return _status.Value() == AssignmentStatuses::Late;
}

const int Assignment::ID() const
{
	return _id;
}

const Date Assignment::AssignedDate() const
{
	return _assignedDate;
}

Date Assignment::CompletedDate()
{
	return _completedDate;
}

Date Assignment::DueDate()
{
	return _dueDate;
}

int Assignment::RevisionNumber()
{
	return _revisionNumber;
}

string Assignment::Description()
{
	return _description;
}

string Assignment::StatusToString()
{
	return _status.ValueToString();
}

// Public Setters

void Assignment::AssignedDate(Date assignedDate)
{
	if (assignedDate != _assignedDate)
	{
		_assignedDate = assignedDate;
		++_revisionNumber;
	}
}

void Assignment::CompletedDate(Date completedDate)
{
	if (completedDate != _completedDate)
	{
		_completedDate = completedDate;
		++_revisionNumber;
	}
	if (_completedDate > _dueDate)
	{
		_status.Value(AssignmentStatuses::Late);
	}
	else
	{
		_status.Value(AssignmentStatuses::Completed);
	}
}

void Assignment::Description(string description)
{
	if (description != _description)
	{
		_description = description;
		++_revisionNumber;
	}
}

void Assignment::DueDate(Date dueDate)
{
	if (dueDate != _dueDate)
	{
		_dueDate = dueDate;
		++_revisionNumber;
	}
}

void Assignment::Status(AssignmentStatuses status)
{
	if (status != _status.Value())
	{
		_status.Value(status);
		++_revisionNumber;
	}
}

// Overloaded Operators

bool Assignment::operator==(Assignment other) const
{
	return _description == other.Description()
		&& _status.Value() == other.Status()
		&& _dueDate == other.DueDate() 
		&& _assignedDate == other.AssignedDate();
}

// Private Methods

int Assignment::generateID()
{
	static int uid = 1;
	return uid++;
}

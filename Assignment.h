#pragma once

#include <string>
#include <list>
#include "Date.h"
#include "AssignmentStatus.h"


class Assignment 
{
public:
	Assignment();
	Assignment(Date assignedDate, Date dueDate, AssignmentStatuses status, string description);
	AssignmentStatuses Status();
	bool IsLate();
	bool operator ==(Assignment other) const;
	const unsigned int ID() const;
	void Status(AssignmentStatuses status);
	Date AssignedDate();
	void AssignedDate(Date assignedDate);
	Date DueDate();
	void DueDate(Date dueDate);
	Date CompletedDate();
	void CompletedDate(Date completedDate);
	string Description();
	void Description(string description);
	int RevisionNumber();
private:
	AssignmentStatus _status;
	int _revisionNumber;
	Date _assignedDate;
	Date _dueDate;
	Date _completedDate;
	string _description;
	unsigned int generateID();
	unsigned int _id;
};

Assignment::Assignment()
{
	_status.Value(AssignmentStatuses::None);
	_description = "";
	_revisionNumber = 0;
	_id = generateID();
}

Assignment::Assignment(
						Date assignedDate, 
						Date dueDate, 
						AssignmentStatuses status, 
						string description = "")
{
	_assignedDate = assignedDate;
	_dueDate = dueDate;
	_status.Value(status);
	_description = description;
	_revisionNumber = 0;
	_id = generateID();
}

unsigned int Assignment::generateID()
{
	static unsigned int uid = 0;
	return uid++;
}

const unsigned int Assignment::ID() const
{
	return _id;
}

AssignmentStatuses Assignment::Status()
{
	return _status.Value();
}

bool Assignment::IsLate()
{
	return _status.Value() == AssignmentStatuses::Late;
}

void Assignment::Status(AssignmentStatuses status)
{
	if (status != _status.Value())
	{
		_status.Value(status);
		++_revisionNumber;
	}
}

Date Assignment::AssignedDate()
{
	return _assignedDate;
}

void Assignment::AssignedDate(Date assignedDate)
{
	if (assignedDate != _assignedDate)
	{
		_assignedDate = assignedDate;
		++_revisionNumber;
	}
}

Date Assignment::DueDate()
{
	return _dueDate;
}

void Assignment::DueDate(Date dueDate)
{
	if (dueDate != _dueDate)
	{
		_dueDate = dueDate;
		++_revisionNumber;
	}
}

Date Assignment::CompletedDate()
{
	return _completedDate;
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

string Assignment::Description()
{
	return _description;
}

void Assignment::Description(string description)
{
	if (description != _description)
	{
		_description = description;
		++_revisionNumber;
	}
}

int Assignment::RevisionNumber()
{
	return _revisionNumber;
}

bool Assignment::operator==(Assignment other) const
{
	return _description == other.Description()
		&& _status.Value() == other.Status()
		&& _dueDate == other.DueDate() 
		&& _assignedDate == other.AssignedDate();
}

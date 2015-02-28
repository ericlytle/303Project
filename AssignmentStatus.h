#pragma once

#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

// AssignmentStatus
// This class models an Assignment Status
// Provides a useful interface for the AssignmentStatuses enum

enum AssignmentStatuses
{
	None,
	Assigned,
	Late,
	Completed
};

class AssignmentStatus
{
public:
	AssignmentStatus();
	AssignmentStatus(string statusStr);
	const AssignmentStatuses Value() const;
	const bool HasValue() const;
	const string ValueToString() const;
	void Value(AssignmentStatuses status);
	void Value(string status);
private:
	AssignmentStatuses value;
};

AssignmentStatus::AssignmentStatus()
{
	value = AssignmentStatuses::None;
}

AssignmentStatus::AssignmentStatus(string statusStr)
{
	char statInput = toupper(statusStr[0]);
	switch (statInput)
	{
	case 'C': Value(AssignmentStatuses::Completed); break;
	case 'A': Value(AssignmentStatuses::Assigned); break;
	case 'L': Value(AssignmentStatuses::Late); break;
	}
}

const AssignmentStatuses AssignmentStatus::Value() const
{
	return value;
}

const bool AssignmentStatus::HasValue() const
{
	return value != AssignmentStatuses::None;
}

const string AssignmentStatus::ValueToString() const
{
	if (value == AssignmentStatuses::None) return "None";
	else if (value == AssignmentStatuses::Assigned) return "Assigned";
	else if (value == AssignmentStatuses::Late) return "Late";
	else if (value == AssignmentStatuses::Completed) return "Completed";
	else return "";
}

void AssignmentStatus::Value(AssignmentStatuses status)
{
	if (status != value)
	{
		value = status;
	}
}

void AssignmentStatus::Value(string status)
{
	if (status == "Assigned") Value(AssignmentStatuses::Assigned);
	else if (status == "Late") Value(AssignmentStatuses::Late);
	else if (status == "Completed") Value(AssignmentStatuses::Completed);
	else Value(AssignmentStatuses::None);
}

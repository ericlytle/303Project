#pragma once

#include <string>
using namespace std;

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
	const AssignmentStatuses Value() const;
	const bool HasValue() const;
	const string ValueToString() const;
	void Value(AssignmentStatuses status);
private:
	AssignmentStatuses value;
};

AssignmentStatus::AssignmentStatus()
{
	value = AssignmentStatuses::None;
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

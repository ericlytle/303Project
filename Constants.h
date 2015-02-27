#pragma once

#include <string>

#pragma region Constants
const unsigned int MAX_STRING = 50; // max length of user input string
const unsigned int MAX_LINE = 100; // max length of user input line
const std::string EXT = ".txt"; // valid file extension
const std::string MAIN_MENU_CHOICES = "ABCDEISQabcdeisq"; // valid input for main menu choice
const std::string DATE_FORMAT = "(YYYY/MM/DD)"; // valid date format for user input
const std::string ASSIGNED = "assignedAssignedASSIGNED"; // valid assignment status (1 of 3)
const std::string LATE = "lateLateLATE"; // valid assignment status (2 of 3)
const std::string COMPLETED = "completedCompletedCOMPLETED"; // valid assignment status (3 of 3)
const std::string INVALID_DATE_TEXT = "Invalid Date. Retry. Makes sure date is in (YYYY/MM/DD) format"; // user message for invalid date
const std::string INVALID_DATE_RANGE_TEXT = "Invalid Date Range. Retry. Due Date must be after Assigned Date"; // user message for invalid date range
const std::string ARROW = "-->"; // decorative arrow symbol
#pragma endregion

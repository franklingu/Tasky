#include "HelpUser.h"
//@author A0105750N
const string HelpUser::HELP_GENERAL_MSG      = "Welcome to the help panel.\n"
	                                           "Tasky is a text-based task management software that helps you manage \nyour schedules.\n"
											   "For your convenience, commands can be entered within a single line.\n\n"
											   "To view additional help on a specific topic, please enter:\n"
											   "help -add           regarding an add operation(adding a task)\n"
											   "help -remove        regarding a remove operation(removing a task)\n"
											   "help -search        regarding a search\n"
											   "help -mark          regarding a mark operation(set a task as Done/Pending)\n"
											   "help -reschedule    regarding a reschedule(modify the details of task)\n"
											   "help -rename        regarding a rename(modify the details of task)\n"
											   "help -display       regarding display operation\n"
											   "help -title         regarding the title input format\n"
											   "help -date          regarding the date input format\n"
											   "help -time          regarding the time input format\n"
											   "help -comment       regarding the comment input format\n"
											   "help -about         to view more information about Tasky\n";
const string HelpUser::HELP_ADD_MSG          = "To add a task, enter one of the following:\n\n"
	                                           "Format1: add '[Title]' from [StartDateTime] to [EndDateTime] -m [Comment]\n"
											   "   e.g.: add 'task 1' from 12/12/2013 13:00 to 13/12/2013 0:00\n\n"
											   "Format2: add '[Title]' by [Deadline] -m [Comment]\n"
											   "   e.g.: add 'do homework' by next tue 2pm\n\n"
											   "Format3: add '[Title]' -m [Comment]\n"
											   "   e.g.: add 'study hard'\n\n"
											   "The comment field is optional. '-m [Comment]'\n\n"
											   "For more information use\n"
											   "           help -title\n"
											   "           help -date\n"
											   "           help -time\n"
											   "           help -comment\n";
const string HelpUser::HELP_REMOVE_MSG       = "To remove a task, enter the following:\n"
	                                           "Format: remove '[Title]'\n"
											   "  e.g.: remove 'review'\n\n"
											   "Note: In case of ambiguity (multiple tasks with the same name), "
											   "\nyou will be prompted for selection of task(s) to remove.\n"
											   "Enter the index of your selection.\n";
const string HelpUser::HELP_SEARCH_MSG       = "To search for a task, enter one of the following combination:\n"
												"A search is carried out according to the parameters provided.\n"
												"Please enter the keywords in order of relevance.\n\n"
												"Format1: search '[list of keyword(s)]'\n"
												 "  e.g.: search 'walk the dog'\n\n"
												 "Format2: search [DateTime] to [DateTime]\n"
												 "  e.g.: search from 22/12/13 to 25/12/13\n\n"
												 "Format3: search [Status]\n"
												 "  e.g.: search done\n\n"
											   "Format4: search '[list of keyword(s)]'from [DateTime] to [DateTime]\n"
											    "  e.g.: search 'walk the dog' from 12/2/14 to 15/2/14\n\n"
												"Format5: search '[list of keyword(s)]' [Status]\n"
												"  e.g.: search 'walk the dog' done\n\n"
												"Format6: search [Status] from [DateTime] to [DateTime]\n"
												"  e.g.: search done from 22/12/13 to 25/12/13\n\n"
												"Format7: search '[list of keywords(s)]' [Status] from [DateTime] to [DateTime]\n"
												"  e.g.: search 'walk the dog' done from 12/2/14 to 15/2/14\n\n"
											   "To search for an empty slot to schedule a task, enter the following:\n"
											   "Format: search slot from [DateTime] to [DateTime]\n"
											    "  e.g.: search slot from 22/12/13 to 25/2/13\n\n";
const string HelpUser::HELP_MARK_MSG         = "To mark a task as Done/Pending, enter the following:\n"
											   "Format: mark '[Title]' done/pending\n"
											    "  e.g.: mark 'Mop the floor' done\n";
const string HelpUser::HELP_RESCHEDULE_MSG   = "To reschedule a task, enter one of the following:\n"
											   "Format1: reschedule '[Title]' from [NewStartDateTime] to [NewEndDateTime]\n"
											    "  e.g.: reschedule 'review' from 2/2/14 to 2/3/14\n\n"
											   "Format2: reschedule '[Title]' by [Deadline]\n"
											    "  e.g.: reschedule 'review' by 14/2/14\n\n"
											   "Format3: reschedule '[Title]'\n"
											    "  e.g.: reschedule 'review'\n";
const string HelpUser::HELP_RENAME_MSG       = "To rename a task, enter the following:\n"
											   "Format: rename '[Title]' to '[NewTitle]' -m [Comment]\n"
											    "  e.g.: rename 'review' to 'write commentary'\n\n"
											   "Note: the comment field is optional. '-m [Comment]'\n\n";
const string HelpUser::HELP_DISPLAY_MSG      = "To display all tasks, please enter: display all\n"
											   "To display pending tasks, please enter: display pending\n"
											   "To display today's tasks, please enter: display today";
const string HelpUser::HELP_TITLE_MSG        = "Please enclose the title within 2 single quotes.\n"
												"The title will be read in from the first to the last single quote.\n\n"
											   "Format: '[title]'\n"
											   "Example: 'it's a title' is read in by Tasky as <it's a title>";
const string HelpUser::HELP_DATE_MSG         = "The following formats of entering dates are allowed:\n"
	                                           "Format1: DD/MM/YYYY\n"
											    "  e.g.:  12/13/2012\n\n"
											   "Format2: DD/MM/YY\n"
											   "  e.g.:  12/13/12\n\n"
											   "Format3: today/tdy, tomorrow/tmr\n"
											   "Note: The short form of today is tdy; the short form for tomorrow is tmr.\n\n"
											   "Format4: this/next monday/tuesday/wednesday/thursday/friday/saturday/sunday\n"
											   "Format5: this/next mon/tue/wed/thu/fri/sat/sun\n\n"
											   "Note: Format 5 utilizes the short form of expressing day in Format4\n\n"
											   "Additional notes: Range of dates allowed fall between A.D.1900 to A.D.2300\n";
const string HelpUser::HELP_TIME_MSG         = "Please enter the time in HH.MM format.\n"
												"  e.g.:  20.15\n\n"
												"You may also use AM/PM.\n"
												"  e.g.:  5.00PM\n";
const string HelpUser::HELP_COMMENT_MSG      = "To add a comment behind a task, use -m while adding or renaming a task\n"
											   "Format: -m [Comment]\n"
											   "   e.g.: add 'Shopping For X'Mas Gifts' by 25/12/2013 -m bring recepient list\n";
const string HelpUser::HELP_ABOUT_MSG        = "Developed by AY2013 Semester1 CS2103 F09-2C Team.\n"
	                                           "Come and visit the project at : http://code.google.com/p/cs2103aug2013-f09-2c/";

const string HelpUser::GENERAL_STR           = "";
const string HelpUser::ADD_STR               = " -add";
const string HelpUser::REMOVE_STR            = " -remove";
const string HelpUser::SEARCH_STR            = " -search";
const string HelpUser::MARK_STR              = " -mark";
const string HelpUser::RESCHEDULE_STR        = " -reschedule";
const string HelpUser::RENAME_STR            = " -rename";
const string HelpUser::DISPLAY_STR           = " -display";
const string HelpUser::TITLE_STR             = " -title";
const string HelpUser::DATE_STR              = " -date";
const string HelpUser::TIME_STR              = " -time";
const string HelpUser::COMMENT_STR           = " -comment";
const string HelpUser::ABOUT_STR             = " -about";

string HelpUser::getHelpMsg(string input){
	return determineHelperString(input);
}

string HelpUser::determineHelperString(const string& input){
	if (equalWithoutCase(input, GENERAL_STR)){
		return HELP_GENERAL_MSG;
	}else if(equalWithoutCase(input, ADD_STR)){
		return HELP_ADD_MSG;
	}else if(equalWithoutCase(input, REMOVE_STR)){
		return HELP_REMOVE_MSG;
	}else if(equalWithoutCase(input, SEARCH_STR)){
		return HELP_SEARCH_MSG;
	}else if(equalWithoutCase(input, MARK_STR)){
		return HELP_MARK_MSG;
	}else if(equalWithoutCase(input, RESCHEDULE_STR)){
		return HELP_RESCHEDULE_MSG;
	}else if(equalWithoutCase(input, RENAME_STR)){
		return HELP_RENAME_MSG;
	}else if(equalWithoutCase(input, DISPLAY_STR)){
		return HELP_DISPLAY_MSG;
	}else if(equalWithoutCase(input, TITLE_STR)){
		return HELP_TITLE_MSG;
	}else if(equalWithoutCase(input, DATE_STR)){
		return HELP_DATE_MSG;
	}else if(equalWithoutCase(input, TIME_STR)){
		return HELP_TIME_MSG;
	}else if(equalWithoutCase(input, COMMENT_STR)){
		return HELP_COMMENT_MSG;
	}else if (equalWithoutCase(input, ABOUT_STR)){
		return HELP_ABOUT_MSG;
	}else{
		return HELP_GENERAL_MSG;
	}
}

bool HelpUser::equalWithoutCase(string input, const string& keyword){
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	return input==keyword;
}

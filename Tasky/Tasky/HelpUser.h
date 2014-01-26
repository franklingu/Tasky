//@author A0105750N
#ifndef HELPUSER_H
#define HELPUSER_H

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

/**
 * This is the class provided to user for help. All the usage of commands about this program will be included here.
 * The basic format of getting help:
 * help              --general help
 * help -add         --help about add
 * help -remove      --help about remove
 * help -mark        --help about mark
 * help -search      --help about search
 * help -reschedule  --help about reschedule
 * help -rename      --help about rename
 * help -display     --help about display
 * help -title       --info about format of title
 * help -date        --info about date
 * help -time        --info about time
 * help -comment     --info about comment
 * help -others      --other relevant info
 * help -about       --about the authors of this program
 *
 *@author: Joan, Junchao.
 */

class HelpUser{
private:
	static const string HELP_GENERAL_MSG;
	static const string HELP_ADD_MSG;
	static const string HELP_REMOVE_MSG;
	static const string HELP_SEARCH_MSG;
	static const string HELP_MARK_MSG;
	static const string HELP_RESCHEDULE_MSG;
	static const string HELP_RENAME_MSG;
	static const string HELP_DISPLAY_MSG;
	static const string HELP_TITLE_MSG;
	static const string HELP_DATE_MSG;
	static const string HELP_TIME_MSG;
	static const string HELP_COMMENT_MSG;
	static const string HELP_OTHERS_MSG;
	static const string HELP_ABOUT_MSG;

	static const string GENERAL_STR;
	static const string ADD_STR;
	static const string REMOVE_STR;
	static const string SEARCH_STR;
	static const string MARK_STR;
	static const string RESCHEDULE_STR;
	static const string RENAME_STR;
	static const string DISPLAY_STR;
	static const string TITLE_STR;
	static const string DATE_STR;
	static const string TIME_STR;
	static const string COMMENT_STR;
	static const string OTHERS_STR;
	static const string ABOUT_STR;

public:
	string getHelpMsg(string input);

private:
	string determineHelperString(const string& input);
	bool equalWithoutCase(string input, const string& keyword);
};

#endif

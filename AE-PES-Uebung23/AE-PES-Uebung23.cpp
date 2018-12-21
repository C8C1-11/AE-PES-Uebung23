// AE-PES-Uebung23.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include "Core.h"
#include "Tools/Character.h"
#include "Tools/Date.h"

#undef max

using namespace std;
using namespace Teronis::VCPlusPlus;
using namespace Teronis::VCPlusPlus::Tools;

const string BAD_INPUT = "bad input";
const string MISSED_SECOND_ARGUMENT = "you missed the second argument";
const int userInputStringLength = 30;

char userInputString[userInputStringLength];

void cleanInStream() {
	// clear failed state of in stream
	cin.clear();
	// ignore garbage
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void enterBadState(string reason) {
	// print error to console
	cerr << reason << endl;
}

int main()
{
	// It is not working ...
	//// This disables the CONTROL-C exception, but while running it over visual studio,
	//// you have to disable the CONTROL-C exception in the excpetion settings by yourself.
	//// The CONTROL-C exception itself cannot be catched in try or __try block.
	////
	//// "If the HandlerRoutine parameter is NULL, a TRUE value causes the calling process 
	////  to ignore CTRL+C input, and a FALSE value restores normal processing of CTRL+C
	////  input. This attribute of ignoring or processing CTRL+C is inherited by child
	////  processes." (https://docs.microsoft.com/en-us/windows/console/setconsolectrlhandler)
	//SetConsoleCtrlHandler(NULL, TRUE);
	cout << "This program prints out the week day name of a date.\n";
	cout << "The following formats are supported:\n1. year_day;year\n2. month_day;month;year\n";
	cout << "Just type something like [0]1;2000 or [0]1;[0]1;2000 and hit enter.\n";
	cout << "To leave this application type Q+ENTER.\n";

	while (true) {
		/* The variable declarations. */
		int firstSemicolonIndex, secondSemicolonIndex;
		int spaceIndex;
		int days, years, months, weekDayIndex;

		while (true) {
			cout << "> ";
			
			if (userInputString[0] != 0)
				// reset user input string array
				memset(userInputString, 0, sizeof(userInputString));
			
			if (cin >> userInputString) {
				// clean in stream: It allows input like "20;2000 dasdj das adjl..."
				cleanInStream();
				// Look for exit letter ...
				int exit = !CharacterTools::searchCharacter(userInputString, userInputStringLength, 'q', 0, 0) || !CharacterTools::searchCharacter(userInputString, userInputStringLength, 'Q', 0, 0);

				if (exit)
					// ... and stop application.
					stop(0);

				firstSemicolonIndex = CharacterTools::searchCharacter(userInputString, userInputStringLength, ';');

				// Check that the semicolon is existing and is not the first or last character, otherwise ...
				if (0 >= firstSemicolonIndex || firstSemicolonIndex + 1 == userInputStringLength - 1) {
					// ... write error.
					enterBadState(BAD_INPUT);
					continue;
				}

				// Now look for a second semicolon.
				secondSemicolonIndex = CharacterTools::searchCharacter(userInputString, userInputStringLength, ';', firstSemicolonIndex + 1);

				// Check if the second semicolon exists, that it is not first character after 
				// the first semicolon and not the last character in the string, otherwise ...
				if (secondSemicolonIndex != -1 && secondSemicolonIndex == firstSemicolonIndex + 1 || secondSemicolonIndex == userInputStringLength - 1) {
					// ... write error.
					enterBadState(BAD_INPUT);
					continue;
				}

				// And we take an empty space after the second or first semicolon into account.
				spaceIndex = CharacterTools::searchCharacter(userInputString, userInputStringLength, '\0', (secondSemicolonIndex == -1 ? firstSemicolonIndex : secondSemicolonIndex) + 1) - 1;

				if (-1 >= spaceIndex)
					spaceIndex = userInputStringLength - 1;

				// A safety check again...
				if ((secondSemicolonIndex != -1 && spaceIndex == secondSemicolonIndex) || spaceIndex == firstSemicolonIndex) {
					enterBadState(MISSED_SECOND_ARGUMENT);
					continue;
				}

				break;
			}
		}

		// Get days from string.
		days = CharacterTools::transformCharsToNumber(userInputString, userInputStringLength, 0, firstSemicolonIndex - 1);
		// If no month is given, then orient at first semicolon index, otherwise at second semicolon index.
		years = CharacterTools::transformCharsToNumber(userInputString, userInputStringLength, (secondSemicolonIndex == -1 ? firstSemicolonIndex : secondSemicolonIndex) + 1, spaceIndex);
		// If month is given, then look for it, otherwise month is set to -1.
		months = secondSemicolonIndex != -1 ? CharacterTools::transformCharsToNumber(userInputString, userInputStringLength, firstSemicolonIndex + 1, secondSemicolonIndex - 1) : -1;

		// Check if month is given (!= -1) and invalid.
		// By this logic 1;-1;2000 is valid and equals to 1;2000 and 1;1;2000.
		if (days < 1 || (months != -1 && months < 1) || years < 1) {
			enterBadState(BAD_INPUT);
			continue;
		}

		// Get the week day index by years and days.
		if (months == -1)
			weekDayIndex = DateTools::calcLeapYearWeekDayIndex(years, days);
		// Get the week day index by full date.
		else
			weekDayIndex = DateTools::calcLeapYearWeekDayIndex(years, months, days);

		// Print the found week day index as week day name.
		cout << DateTools::toWeekDayName(weekDayIndex) << " (" << weekDayIndex << ")\n";
	}

	stop(0);
	// prevent compiler complain
	return 0;
}

// Programm ausführen: STRG+F5 oder "Debuggen" > Menü "Ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.

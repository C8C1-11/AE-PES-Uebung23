// AE-PES-Uebung23.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include <iostream>
#include <string>
#include "Tools/Character.h"
#include "Tools/Date.h"

using namespace std;
using namespace Teronis::VCPlusPlus::Tools;

void stop(int code, string message) {
	if (!message.empty())
		cout << message << "\n";

	system("pause");
	exit(code);
}

void stop(int code) {
	stop(code, "");
}

void throwError(string message) {
	message = string("[ERROR] ") + message;
	throw invalid_argument(message);
}

void throwBadInput() {
	throwError("bad input");
}

int main()
{
	/* The variable declarations. */
	const int userInputStringLength = 30;
	char userInputString[userInputStringLength];
	int firstSemicolonIndex, secondSemicolonIndex;
	int spaceIndex;
	int days, years, months, weekDayIndex;

	cout << "This program prints out the week day name.\n";
	cout << "supported formats:\n1. 'year_days;years'\n2. 'month_days;months;years'\n";
	cout << "Just type something like '1;2000' or '1;1;2000'.\n";

	while (true) {
		cout << "> ";
		cin >> userInputString;

		firstSemicolonIndex = CharacterTools::searchCharacter(userInputString, userInputStringLength, ';');

		try {
			// Check that the semicolon is existing and is not the first or last character, otherwise ...
			if (0 >= firstSemicolonIndex || firstSemicolonIndex + 1 == userInputStringLength - 1)
				// ... throw exception.
				throwBadInput();

			// Now look for a second semicolon.
			secondSemicolonIndex = CharacterTools::searchCharacter(userInputString, userInputStringLength, ';', firstSemicolonIndex + 1);

			// Check if the second semicolon exists, that it is not first character after 
			// the first semicolon and not the last character in the string, otherwise ...
			if (secondSemicolonIndex != -1 && secondSemicolonIndex == firstSemicolonIndex + 1 || secondSemicolonIndex == userInputStringLength - 1)
				// ... throw exception.
				throwBadInput();

			// And we take an empty space after the second or first semicolon into account.
			spaceIndex = CharacterTools::searchCharacter(userInputString, userInputStringLength, '\0', (secondSemicolonIndex == -1 ? firstSemicolonIndex : secondSemicolonIndex) + 1) - 1;

			if (-1 >= spaceIndex)
				spaceIndex = userInputStringLength - 1;

			// A safety check again...
			if ((secondSemicolonIndex != -1 && spaceIndex == secondSemicolonIndex) || spaceIndex == firstSemicolonIndex)
				throwError("you missed the second argument");

			break;
		}
		catch (const exception& error) {
			cerr << error.what() << endl;
			// reset user input string array
			memset(userInputString, 0, sizeof(userInputString));
			// clear failed state of in stream
			cin.clear();
			// ignore garbage
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
	}

	// Get days from string.
	days = CharacterTools::transformCharsToNumber(userInputString, userInputStringLength, 0, firstSemicolonIndex - 1);
	// If no month is given, then orient at first semicolon index, otherwise at second semicolon index.
	years = CharacterTools::transformCharsToNumber(userInputString, userInputStringLength, (secondSemicolonIndex == -1 ? firstSemicolonIndex : secondSemicolonIndex) + 1, spaceIndex);
	// If month is given, then look for it, otherwise month is set to -1.
	months = secondSemicolonIndex != -1 ? CharacterTools::transformCharsToNumber(userInputString, userInputStringLength, firstSemicolonIndex + 1, secondSemicolonIndex - 1) : -1;

	// Get the week day index by years and days.
	if (months == -1)
		weekDayIndex = DateTools::calcLeapYearWeekDayIndex(years, days);
	// Get the week day index by full date.
	else
		weekDayIndex = DateTools::calcLeapYearWeekDayIndex(years, months, days);

	// Print the week day index as week day name.
	cout << DateTools::toWeekDayName(weekDayIndex) << " (" << weekDayIndex << ")\n";
	stop(0);
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

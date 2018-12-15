// AE-PES-Uebung23.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include <iostream>
#include <string>
#include "Tools/Character.h"
#include "Tools/Math.h"

using namespace std;
using namespace Teronis::VCPlusPlus::Tools;

int main()
{
	/* The declaration of the variables. */
	const int jStringLength = 30;
	char jString[jStringLength];
	int d, jStartIndex, jBackIndex, jSpaceIndex, j = 0;

	cout << "input: ";
	cin >> jString;

	int dSemicolonIndex = CharacterTools::searchCharacter(jString, jStringLength, ';');

	if (0 >= dSemicolonIndex)
		throw std::invalid_argument("bad input");

	d = CharacterTools::transformCharsToNumber(jString, jStringLength, 0, dSemicolonIndex - 1);
	jStartIndex = dSemicolonIndex + 1;

	jSpaceIndex = CharacterTools::searchCharacter(jString, jStringLength, '\0', jStartIndex);

	if (-1 == jSpaceIndex)
		jBackIndex = jStringLength - 1;
	else
		jBackIndex = jSpaceIndex - 1;

	j = CharacterTools::transformCharsToNumber(jString, jStringLength, jStartIndex, jBackIndex);
	cout << MathTools::calcLeapYearWeekDayName(j, d);

	cout << "\n";
	system("pause");
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

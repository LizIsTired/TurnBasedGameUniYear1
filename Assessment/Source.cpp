#include <iostream> /* cout, cin */
#include <stdio.h> /* printf, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h> /* time */
#include <limits> /* limits */
#include "colors.h"


void play();
void settings();
//int rechargeENG(int charENG, int enemENG, int EngRechargeRate);

int roundsVar = 1;

enum mainMenuChoices { playButton = 1, settingsButton, exitButton };
enum playMenuChoices { attack = 1, specialAttack, recharge, dodge, heal, exitTime };

int main() {
	bool finishedMenu = false;
	while (!finishedMenu) {

	int menuChoice = 0;
	std::cout << "\n Menu:\n\n\n\n - Play: " << mainMenuChoices::playButton;
	std::cout << "\n - Settings: " << mainMenuChoices::settingsButton;
	std::cout << "\n - Exit: " << mainMenuChoices::exitButton << std::endl;

	std::cin >> menuChoice;
		switch (menuChoice) {
			if (menuChoice < 1 || menuChoice > 3) { std::cout << "Please enter a valid selection"; break; }
		case mainMenuChoices::playButton:
			play();
			menuChoice = 0;
			system("CLS");
			break;
		case mainMenuChoices::settingsButton:
			settings();
			menuChoice = 0;
			system("CLS");
			break;
		case mainMenuChoices::exitButton:
			finishedMenu = true;
			std::exit;
			menuChoice = 0;
			system("CLS");
			break;
		}
		// user input validation
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<char>::max(), '\n');
		system("CLS");
		//std::cout << "Please enter a valid selection consisiting of numbers!";
	}
}

void play() {
	int charHP = 100;
	int enemHP = 100;
	int charENG = 50;
	int enemENG = 50;
	int startHP = 100;
	char anything;
	bool gameOver = false;

	srand(time(NULL));

	while (!gameOver) {

		int charHitChance = 100;
		int enemHitChance = 100;
		int charHitDamageRange;
		int enemHitDamageRange;

		int charEngRechargeRate = 10;
		int enemEngRechargeRate = 10;
		int EngRechargeMult = 4;
		int playMenuChoice;

		if (charHP < 1) { charHP = 0; };
		if (enemHP < 1) { enemHP = 0; };

		system("CLS");


		//play screen text
		std::cout << "\n Fight!\n\n\n\n\n\n\n";
		std::cout << FGRN(" Player HP:") << FGRN( << charHP << );
		std::cout << FRED("    Enemy HP:") << FRED( << enemHP << );
		std::cout << FGRN("\n Player Energy:") << FGRN( << charENG << );
		std::cout << FRED(" Enemy Energy:") << FRED( << enemENG << );
		std::cout << "\n\n\n\n Press " << playMenuChoices::attack << " for a regular attack";
		std::cout << "\n Press " << playMenuChoices::specialAttack << " for a special attack";
		std::cout << "\n Press " << playMenuChoices::recharge << " to recharge energy";
		std::cout << "\n Press " << playMenuChoices::dodge << " to dodge";
		std::cout << "\n Press " << playMenuChoices::heal << " to heal";
		std::cout << "\n Press " << playMenuChoices::exitTime << " to exit the game" << std::endl;

		
		if (charHP < 1) {
			std::cout << "You lose!\nPress enter twice to go to menu!\n";
			std::cin >> anything; 
			gameOver = true;
			return;
		}

		if (enemHP < 1) {
			std::cout << "You win!\nPress enter twice to go to menu!\n";
			std::cin >> anything;
			gameOver = true;
			return;
		}
		if (!gameOver) {
			std::cin >> playMenuChoice;
		}

		switch (playMenuChoice) {

		// attack
		case playMenuChoices::attack:
			charHitChance = rand() % 10 + 1;
			charHitDamageRange = rand() % 10 + 1;
			break;

		// special attack
		case playMenuChoices::specialAttack:
			if (charENG >= 50) {
				charENG -= 50;
				charHitChance = rand() % 10 + 1;
				charHitDamageRange = rand() % (20 + 1 - 5);
				break;
			}
			else {
				std::cout << "Not enough energy!";
				break;
			}
			break;

		// recharge
		case playMenuChoices::recharge:
			charEngRechargeRate *= EngRechargeMult;
			break;

		// dodge
		case playMenuChoices::dodge:

			break;

		// heal
		case playMenuChoices::heal:
			if (charHP >= 100) { std::cout << "Health already at maximum, that's like taking a shower in the rain; it won't make you any cleaner!"; }
			if (charENG >= 10) { charHP = charHP + charENG; charENG = charENG / 2; }
			if (charENG <= 10) { std::cout << "Low energy! Recharge energy and retry!"; }
			if (charHP >= 100) { charHP = startHP; }
			break;

		// exit
		case playMenuChoices::exitTime:
			// double check with user
			return;
			break;
		}
		// user input validation, doesn't work how I want yet, needs to work without progressing turn
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<char>::max(), '\n');
		system("CLS");

		// enemy NPC logic
		switch (rand() % 5) {

		// attack
		case 0 || 1:
			if (rand() % 10 > 2) {
				enemHP -= rand() % 10;
				std::cout << "\n Did damage!";
				break;
			}
			else {
				std::cout << "\n Failed!";
				break;
			}
			break;

		// special attack
		case 2:
			if (enemENG >= 50) {
				enemENG -= 50;
				if (rand() % 10 > 5) {
					charHP -= rand() % (20 + 1 - 5);
					std::cout << "\n Did damage!";
					break;
				}
				else {
					std::cout << "\n Failed!";
					break;
				}
			}
			else {
				std::cout << "Not enough energy!";
				break;
			}
			break;

		// recharge
		case 3:
			enemEngRechargeRate *= EngRechargeMult;
			break;

		// dodge
		case 4:
			break;

		// heal
		case 5:
			if (enemHP >= 100) { std::cout << "Health already at maximum, that's like taking a shower in the rain; it won't make you any cleaner!"; }
			if (enemENG >= 10) { enemHP = enemHP + enemENG; enemENG = enemENG / 2; }
			if (enemENG <= 10) { std::cout << "Low energy! Recharge energy and retry!"; }
			if (enemHP >= 100) { enemHP = startHP; }
			break;
		}

			// do math here
		    charHitChance;




			// final health defines
			// charHP = 1;
			// enemHP = 1;

			// energy recharge
			charENG += 1 * charEngRechargeRate;
			enemENG += 1 * enemEngRechargeRate;
			if (charENG > 100) { charENG = 100; }
			if (enemENG > 100) { enemENG= 100; }
	}
	return;
}

//int rechargeENG(int charENG, int enemENG, int EngRechargeRate) {
	//charENG += 1 * EngRechargeRate;
	//enemENG += 1 * EngRechargeRate;
	//return charENG, enemENG;
//}

//settings function
void settings() {
	int charHP = 100;

	int settingsMenuChoice;

	system("CLS");

	std::cout << "\n Settings:\n\n\n\n - Rounds:" << roundsVar << "\n - Player Starting Health:" << charHP << "\n\n Press 0 to go to menu...\n";
	std::cin >> settingsMenuChoice;
	switch (settingsMenuChoice) {
	case 0:
		return;
		break;
	}
}
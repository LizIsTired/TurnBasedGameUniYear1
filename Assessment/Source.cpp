#include <iostream> /* cout, cin */
#include <stdio.h> /* printf, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h> /* time */
#include <limits> /* limits */
#include "colors.h" /* colors header */


void play();
void settings();
//int rechargeENG(int charENG, int enemENG, int EngRechargeRate);

int roundsVar = 1;

enum mainMenuChoices { playButton = 1, exitButton, settingsButton};
enum playMenuChoices { attack = 1, specialAttack, recharge, dodge, heal, exitTime };

int main() {
	bool finishedMenu = false;
	while (!finishedMenu) {

	int menuChoice = 0;
	std::cout << "\n Menu:\n\n\n\n - Play: " << mainMenuChoices::playButton;
	//std::cout << "\n - Settings: " << mainMenuChoices::settingsButton;
	std::cout << "\n - Exit: " << mainMenuChoices::exitButton << std::endl;

	std::cin >> menuChoice;
		switch (menuChoice) {
			if (menuChoice < 1 || menuChoice > 3) { std::cout << "Please enter a valid selection"; break; }
		case mainMenuChoices::playButton:
			play();
			menuChoice = 0;
			system("CLS");
			break;
		case mainMenuChoices::exitButton:
			finishedMenu = true;
			std::exit;
			menuChoice = 0;
			system("CLS");
			break;
		/*case mainMenuChoices::settingsButton:
			settings();
			menuChoice = 0;
			system("CLS");
			break;*/
		}
		// user input validation
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<char>::max(), '\n');
		system("CLS");
		//std::cout << "Please enter a valid selection consisiting of numbers!";
	}
}

void play() {
	int startHP = 100;
	int charHP = startHP;
	int enemHP = startHP;
	int startENG = 50;
	int charENG = startENG;
	int enemENG = startENG;
	char anything;
	bool gameOver = false;
	bool firstTurn = true;
	std::string charResult;
	std::string enemResult;
	std::string charDamage;
	std::string enemDamage;
	

	srand(time(NULL));

	while (!gameOver) {

		int charHitChance = 0;
		int enemHitChance = 0;
		int charHitDamageRange = 0;
		int enemHitDamageRange = 0;
		int charHitChanceModifer = 0;
		int enemHitChanceModifer = 0;
		int charEngRechargeRate = 10;
		int enemEngRechargeRate = 10;
		int EngRechargeMult = 4;
		int playMenuChoice;
		bool exitConfirm = false;
		std::string exitConfirmVar;

		if (firstTurn == true) {
			//play screen text
			system("CLS");
			std::cout << "\n Fight!\n\n\n\n\n\n\n";
			std::cout << FGRN(" Player HP:") << FGRN(<< charHP << );
			std::cout << FRED("    Enemy HP:") << FRED(<< enemHP << );
			std::cout << FGRN("\n Player Energy:") << FGRN(<< charENG << );
			std::cout << FRED(" Enemy Energy:") << FRED(<< enemENG << );
			std::cout << "\n\n\n\n Press " << playMenuChoices::attack << " for a regular attack";
			std::cout << "\n Press " << playMenuChoices::specialAttack << " for a special attack";
			std::cout << "\n Press " << playMenuChoices::recharge << " to recharge energy";
			std::cout << "\n Press " << playMenuChoices::dodge << " to dodge";
			std::cout << "\n Press " << playMenuChoices::heal << " to heal";
			std::cout << "\n Press " << playMenuChoices::exitTime << " to exit the game";
			std::cout << std::endl;
		}
		
		charResult = "";
		enemResult = "";
		charDamage = "";
		enemDamage = "";
		bool charSuccess = false;
		bool enemSuccess = false;
		bool charHealChosen = false;
		bool enemHealChosen = false;

		// score check
		if (charHP < 1) {
			std::cout << FYEL(" \nYou lose!\nPress 1 to go to menu!\n");
			std::cin >> anything; 
			gameOver = true;
			return;
		}

		if (enemHP < 1) {
			std::cout << FYEL(" \nYou win!\nPress 1 to go to menu!\n");
			std::cin >> anything;
			gameOver = true;
			return;
		}

		// player action
		while (charSuccess == false) {
			while (!charHealChosen) {

				std::cin.clear();
				std::cin.ignore(std::numeric_limits<char>::max(), '\n');
				if (!gameOver) {
					std::cin >> playMenuChoice;
				}

				switch (playMenuChoice) {

					if (playMenuChoice < 1 || playMenuChoice > 6) { std::cout << FBLU(" \nPlease enter a valid selection"); break; }

					// attack
				case playMenuChoices::attack:
					charHitChance = rand() % 10 + 1;
					charHitDamageRange = rand() % 10 + 1;
					charResult = "attack";
					charSuccess = true;
					charHealChosen = true;
					break;

					// special attack
				case playMenuChoices::specialAttack:
					if (charENG >= 50) {
						charENG -= 50;
						charHitChance = rand() % 10 + 1;
						charHitDamageRange = rand() % (20 + 1 - 5);
						charResult = "special attack";
						charSuccess = true;
						charHealChosen = true;
						break;
					}
					else {
						std::cout << FBLU("\n Not enough energy!\n");
						charSuccess = false;
						break;
					}
					break;

					// recharge
				case playMenuChoices::recharge:
					charEngRechargeRate *= EngRechargeMult;
					charHitChanceModifer = -10;
					charResult = "recharge";
					charSuccess = true;
					charHealChosen = true;
					break;

					// dodge
				case playMenuChoices::dodge:
					charEngRechargeRate /= 2;
					charHitChanceModifer = 30;
					charResult = "dodge";
					charSuccess = true;
					charHealChosen = true;
					break;

					// heal
				case playMenuChoices::heal:
						
						if (charENG >= 10 && charHP >= 100) {
							std::cout << FBLU("\n Health already at maximum, that's like taking a shower in the rain; it won't make you any cleaner!\n");
							charSuccess = false;
						}
						else if (charENG <= 10) {
							std::cout << FBLU("\n Low energy! Recharge energy and retry!\n");
							charSuccess = false;
						}
						else if (charENG >= 10 && charHP <= 100) {
							charHP = charHP + charENG; charENG = charENG / 2;
							charResult = "heal";
							charSuccess = true;
						}
					
					if (charSuccess == true) { std::cout << FBLU(" \nChoose another action other than heal!\n"); }
					if (charHP >= startHP + 1) { charHP = startHP; charSuccess = true; }
					break;

					// exit
				case playMenuChoices::exitTime:
					// double check with user
					if (exitConfirm == false) {
						std::cout << FBLU(" \nPress 1 to exit!\nPress 2 to return to game!\n");
						std::cin >> exitConfirmVar;
						if (exitConfirmVar == "1") {
							charSuccess = true;
							charHealChosen = true;
							return;
							break;
						}
						else {
							charSuccess = false;
							charHealChosen = true;
							break;
						}
					}
					else {
						charSuccess = false;
						charHealChosen = true;
						break;
					}
				}
				// user input validation, doesn't work how I want yet, needs to work without progressing turn
				//std::cin.clear();
				//system("CLS");
			}
		}

		// enemy NPC logic
		while (enemSuccess == false) {
			while (!enemHealChosen) {
				switch (rand() % 6) {

					// attack
				case 0:
				case 1:
					enemHitChance = rand() % 10 + 1;
					enemHitDamageRange = rand() % 10 + 1;
					enemResult = "attack";
					enemSuccess = true;
					enemHealChosen = true;
					break;

					// special attack
				case 2:
					if (enemENG >= 50) {
						enemENG -= 50;
						enemHitChance = rand() % 10 + 1;
						enemHitDamageRange = rand() % (20 + 1 - 5);
						enemResult = "special attack";
						enemSuccess = true;
						enemHealChosen = true;
						break;
					}
					else {
						//std::cout << "Not enough energy!";
						enemSuccess = false;
						break;
					}
					break;

					// recharge
				case 3:
					enemEngRechargeRate *= EngRechargeMult;
					enemHitChanceModifer = -10;
					enemResult = "recharge";
					enemSuccess = true;
					enemHealChosen = true;
					break;

					// dodge
				case 4:
					enemEngRechargeRate /= 2;
					enemHitChanceModifer = 30;
					enemResult = "dodge";
					enemSuccess = true;
					enemHealChosen = true;
					break;

					// heal (has high chance in order to give enemy greater opportunity to win in absence of proper algorithm)
				case 5:
				case 6:
				case 7:
					/*if (enemHP >= 100) { std::cout << "Health already at maximum, that's like taking a shower in the rain; it won't make you any cleaner!"; enemSuccess = false; }
					if (enemENG >= 10) { enemHP = enemHP + enemENG; enemENG = enemENG / 2; enemSuccess = true; }
					if (enemENG <= 10) { std::cout << "Low energy! Recharge energy and retry!"; enemSuccess = false; }
					if (enemHP >= 100) { enemHP = startHP; enemSuccess = true; }
					enemResult = "heal";
					break;*/

					if (enemENG >= 10 && enemHP >= 100) {
						//std::cout << FBLU("\n Health already at maximum, that's like taking a shower in the rain; it won't make you any cleaner!");
						enemSuccess = false;
					}
					else if (enemENG <= 10) {
						//std::cout << FBLU("\n Low energy! Recharge energy and retry!");
						enemSuccess = false;
					}
					else if (enemENG >= 10 && enemHP <= 100) {
						enemHP = enemHP + enemENG; enemENG = enemENG / 2;
						enemResult = "heal";
						enemSuccess = true;
					}

					if (enemSuccess == true) { /*std::cout << FBLU(" \nChoose another action other than heal!");*/ }
					if (enemHP >= startHP + 1) { enemHP = startHP; enemSuccess = true; }
					break;
				}
			}
		}

		// lots of funky calculations that I'm really hoping work

			// calculate temp values after random chance and user/enemy action
		    enemHitChance -= charHitChanceModifer / 100; 
		    charHitChance -= enemHitChanceModifer / 100;
		   
			if (charResult == "attack") {
				if (enemHitChance >= 8) { 
					charHP -= enemHitDamageRange;
				}
			}
			if (charResult == "special attack") {
				if (enemHitChance >= 5) { 
					charHP -= enemHitDamageRange;
				}
			}
			if (enemResult == "attack") {
				if (charHitChance >= 8) { 
					enemHP -= charHitDamageRange;
				}
			}
			if (enemResult == "special attack") {
				if (charHitChance >= 5) { 
					enemHP -= charHitDamageRange;
				}
			}

			//if (enemHitChance >= 5) { charHP -= enemHitDamageRange; }
			//if (charHitChance >= 5) { enemHP -= charHitDamageRange; }

			// energy recharge
			charENG += 1 * charEngRechargeRate;
			enemENG += 1 * enemEngRechargeRate;

			// clamp energy to 100
			if (charENG > 100) { charENG = 100; }
			if (enemENG > 100) { enemENG= 100; }

			firstTurn = false;

			// round health to 0 if below 1
			if (charHP < 1) { charHP = 0; };
			if (enemHP < 1) { enemHP = 0; };

			system("CLS");

			// play screen text
			std::cout << "\n Fight!\n\n\n\n\n\n\n";
			std::cout << FGRN(" Player HP:") << FGRN(<< charHP << );
			std::cout << FRED("    Enemy HP:") << FRED(<< enemHP << );
			std::cout << FGRN("\n Player Energy:") << FGRN(<< charENG << );
			std::cout << FRED(" Enemy Energy:") << FRED(<< enemENG << );
			std::cout << "\n\n\n\n Press " << playMenuChoices::attack << " for a regular attack";
			std::cout << "\n Press " << playMenuChoices::specialAttack << " for a special attack";
			std::cout << "\n Press " << playMenuChoices::recharge << " to recharge energy";
			std::cout << "\n Press " << playMenuChoices::dodge << " to dodge";
			std::cout << "\n Press " << playMenuChoices::heal << " to heal";
			std::cout << "\n Press " << playMenuChoices::exitTime << " to exit the game";
			
			if (charResult == "attack") {
				if (charHitChance >= 8) {
					std::cout << FBLU("\n\n You used ") FBLU(<< charResult << ) FBLU(" and did ") FBLU(<< charHitDamageRange << ) FBLU(" damage!");
				}
				else if (charHitChance < 8) {
					std::cout << FBLU("\n\n You tried to use ") FBLU(<< charResult << )  FBLU(" but your attack missed!\n");
				}
			}
			if (charResult == "special attack") {
				if (charHitChance >= 5) {
					std::cout << FBLU("\n\n You used ") FBLU(<< charResult << ) FBLU(" and did ") FBLU(<< charHitDamageRange << ) FBLU(" damage!");
				}
				else if (charHitChance < 5) {
					std::cout << FBLU("\n\n You tried to use ") FBLU(<< charResult << )  FBLU(" but your attack missed!\n");
				}
			}
			else if (charResult != "attack" || charResult != "special attack") { 
				std::cout << FBLU("\n\n You used ") FBLU(<< charResult << ) FBLU(" and did ") FBLU(<< charHitDamageRange << ) FBLU(" damage!"); 
			}
			if (enemResult == "attack") {
				if (enemHitChance >= 8) {
					std::cout << FBLU("\n\n Enemy used ") FBLU(<< enemResult << ) FBLU(" and did ") FBLU(<< enemHitDamageRange << ) FBLU(" damage!");
				}
				else if (enemHitChance < 8) {
					std::cout << FBLU("\n\n Enemy tried to use ") FBLU(<< enemResult << )  FBLU(" but their attack missed!\n");
				}
			}
			if (enemResult == "special attack") {
				if (enemHitChance >= 5) {
					std::cout << FBLU("\n\n Enemy used ") FBLU(<< enemResult << ) FBLU(" and did ") FBLU(<< enemHitDamageRange << ) FBLU(" damage!");
				}
				else if (enemHitChance < 5) {
					std::cout << FBLU("\n\n Enemy tried to use ") FBLU(<< enemResult <<)  FBLU(" but their attack missed!\n");
				}
			}
			else { std::cout << FBLU("\n\n Enemy used ") FBLU(<< enemResult << ) FBLU(" and did ") FBLU(<< enemHitDamageRange << ) FBLU(" damage!"); }
			//std::cout << FBLU("\n\n You used ") FBLU(<< charResult <<) FBLU(" and did ") FBLU(<< charHitDamageRange <<) FBLU(" damage!");
			//std::cout << FBLU("\n\n Enemy used ") FBLU(<< enemResult <<) FBLU(" and did ") FBLU(<< enemHitDamageRange <<) FBLU(" damage!");
			std::cout << std::endl;
	}
	return;
}


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
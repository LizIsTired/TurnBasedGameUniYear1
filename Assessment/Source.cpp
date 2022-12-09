#include <iostream> /* cout, cin */
#include <stdio.h> /* printf, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h> /* time */
#include <limits> /* limits */
#include <conio.h> /* getch */
#include "colors.h" /* colors header */

void play();
void gameplayActionPrinting(std::string result, int hitChance, int attackChance, int hitDamageRange, int specialAttackChance, std::string name);
void mainMenuPrint(int HP, int HP2, int playerENERGY, int enemyENERGY);

struct user {
	std::string name;
	int HP;
	int ENERGY;

	int hitChance;
	int hitDamageRange;
	int hitChanceModifier;
	int energyRechargeRate;

	std::string result;
	std::string damage;

	bool success;
	bool healChosen;
};
enum mainMenuChoices { playButton = 1, exitButton, settingsButton };
enum playMenuChoices { attack = 1, specialAttack, recharge, dodge, heal, exitTime };

int main() {
	bool finishedMenu = false;
	while (!finishedMenu) {

		int menuChoice = 0;
		std::cout << "\n Menu:\n\n\n\n - Play: " << mainMenuChoices::playButton;
		std::cout << "\n - Exit: " << mainMenuChoices::exitButton << std::endl;

		std::cin >> menuChoice;
		switch (menuChoice) {
			if (menuChoice < playButton || menuChoice > settingsButton) { std::cout << "Please enter a valid selection"; break; }
		case mainMenuChoices::playButton:
			play();
			menuChoice = 0;
			system("CLS"); // using system commands is not ideal, but for this purpose it works
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
	}
}

/// <summary>
/// Initialize isolated play session.
/// </summary>
void play() {
	// player and enemy constants and assignment for hp, energy, attack chances, game state
	const int startHP = 100;
	const int startENERGY = 50;

	user Player;
	user Enemy;

	Player.name = "You";
	Enemy.name = "Enemy";

	Player.HP = startHP;
	Player.ENERGY = startENERGY;

	Enemy.HP = startHP;
	Enemy.ENERGY = startENERGY;

	int specialAttackChance = 8;
	int attackChance = 5;

	bool gameOver = false;
	bool firstTurn = true;


	playMenuChoices chosenAction;
	
	// srand seed assignment
	srand(time(NULL));

	while (!gameOver) {
		// player and enemy internal variables, gets reset each round

		struct user players[2] = { Player, Enemy };
		int numberOfPlayers = 2;

		Player.hitChance = 0;
		Player.hitDamageRange = 0;
		Player.hitChanceModifier = 0;
		Player.energyRechargeRate = 10;

		Enemy.hitChance = 0;
		Enemy.hitDamageRange = 0;
		Enemy.hitChanceModifier = 0;
		Enemy.energyRechargeRate = 10;


		int EnergyRechargeMult = 4;

		int playMenuChoice;
		bool exitConfirm = false;




		std::string exitConfirmVar;

		if (firstTurn == true) {
			//play screen text
			system("CLS");
			mainMenuPrint(Player.HP, Enemy.HP, Player.ENERGY, Enemy.ENERGY);
		}

		// hate this, empty assignment for strings, resets the result each iteration
		Player.result = "";
		Enemy.result = "";
		Player.damage = "";
		Enemy.damage = "";

		Player.success = false;
		Enemy.success = false;

		Player.healChosen = false;
		Enemy.healChosen = false;

		// score check
		if (Player.HP < 1) {
			std::cout << FYEL(" \nYou lose!\nPress 1 to go to menu!\n");
			_getch();
			gameOver = true;
			return;
		}

		if (Enemy.HP < 1) {
			std::cout << FYEL(" \nYou win!\nPress 1 to go to menu!\n");
			_getch();
			gameOver = true;
			return;
		}
		
		// player action
		while (Player.success == false) {
			while (!Player.healChosen) {

				std::cin.clear();
				std::cin.ignore(std::numeric_limits<char>::max(), '\n');
				if (!gameOver) {
					std::cin >> playMenuChoice;
				}

				switch (playMenuChoice) {

					if (playMenuChoice < 1 || playMenuChoice > 6) { std::cout << FBLU(" \nPlease enter a valid selection"); break; }

				case playMenuChoices::attack:
					Player.hitChance = rand() % 10 + 1;
					Player.hitDamageRange = rand() % 10 + 1;
					// we need to check the players move later
					Player.result = "attack";
					Player.success = true;
					Player.healChosen = true;
					break;

				case playMenuChoices::specialAttack:
					if (Player.ENERGY >= 50) {
						Player.ENERGY -= 50;
						Player.hitChance = rand() % 10 + 1;
						Player.hitDamageRange = rand() % (20 + 1 - 5);
						Player.result = "special attack";
						Player.success = true;
						Player.healChosen = true;
						break;
					}
					else {
						std::cout << FBLU("\n Not enough energy!\n");
						Player.success = false;
						break;
					}
					break;

				case playMenuChoices::recharge:
					Player.energyRechargeRate *= EnergyRechargeMult;
					Player.hitChanceModifier = -10;
					Player.result = "recharge";
					Player.success = true;
					Player.healChosen = true;
					break;

				case playMenuChoices::dodge:
					Player.energyRechargeRate /= 2;
					Player.hitChanceModifier = 30;
					Player.result = "dodge";
					Player.success = true;
					Player.healChosen = true;
					break;

				case playMenuChoices::heal:

					if (Player.ENERGY >= 10 && Player.HP >= 100) {
						std::cout << FBLU("\n Health already at maximum, that's like taking a shower in the rain; it won't make you any cleaner!\n");
						Player.success = false;
					}
					else if (Player.ENERGY <= 10) {
						std::cout << FBLU("\n Low energy! Recharge energy and retry!\n");
						Player.success = false;
					}
					else if (Player.ENERGY >= 10 && Player.HP <= 100) {
						Player.HP = Player.HP + Player.ENERGY; Player.ENERGY = Player.ENERGY / 2;
						Player.result = "heal";
						Player.success = true;
					}

					if (Player.success == true) { std::cout << FBLU(" \nChoose another action other than heal!\n"); }
					if (Player.HP >= startHP + 1) { Player.HP = startHP; Player.success = true; }
					break;

					// exit
				case playMenuChoices::exitTime:
					// double check with user
					if (exitConfirm == false) {
						std::cout << FBLU(" \nPress 1 to exit!\nPress 2 to return to game!\n");
						std::cin >> exitConfirmVar;
						if (exitConfirmVar == "1") {
							Player.success = true;
							Player.healChosen = true;
							return;
							break;
						}
						else {
							Player.success = false;
							Player.healChosen = true;
							break;
						}
					}
					else {
						Player.success = false;
						Player.healChosen = true;
						break;
					}
				}
			}
		}

		// enemy NPC logic
		while (Enemy.success == false) {
			while (!Enemy.healChosen) {
				switch (rand() % 6) {

					// attack
				case 0:
				case 1:
					Enemy.hitChance = rand() % 10 + 1;
					Enemy.hitDamageRange = rand() % 10 + 1;
					Enemy.result = "attack";
					Enemy.success = true;
					Enemy.healChosen = true;
					break;

					// special attack
				case 2:
					if (Enemy.ENERGY >= 50) {
						Enemy.ENERGY -= 50;
						Enemy.hitChance = rand() % 10 + 1;
						Enemy.hitDamageRange = rand() % (20 + 1 - 5);
						Enemy.result = "special attack";
						Enemy.success = true;
						Enemy.healChosen = true;
						break;
					}
					else {
						Enemy.success = false;
						break;
					}
					break;

					// recharge
				case 3:
					Enemy.energyRechargeRate *= EnergyRechargeMult;
					Enemy.hitChanceModifier = -10;
					Enemy.result = "recharge";
					Enemy.success = true;
					Enemy.healChosen = true;
					break;

					// dodge
				case 4:
					Enemy.energyRechargeRate /= 2;
					Enemy.hitChanceModifier = 30;
					Enemy.result = "dodge";
					Enemy.success = true;
					Enemy.healChosen = true;
					break;

					// heal (has high chance in order to give enemy greater opportunity to win in absence of proper algorithm)
				case 5:
				case 6:
				case 7:
					if (Enemy.ENERGY >= 10 && Enemy.HP >= 100) {
						Enemy.success = false;
					}
					else if (Enemy.ENERGY <= 10) {
						Enemy.success = false;
					}
					else if (Enemy.ENERGY >= 10 && Enemy.HP <= 100) {
						Enemy.HP = Enemy.HP + Enemy.ENERGY; Enemy.ENERGY = Enemy.ENERGY / 2;
						Enemy.result = "heal";
						Enemy.success = true;
					}

					if (Enemy.success == true) {}
					if (Enemy.HP >= startHP + 1) { Enemy.HP = startHP; Enemy.success = true; }
					break;
				}
			}
		}

		// lots of funky calculations that I'm really hoping work

		// calculate temp values after random chance and user/enemy action
		Enemy.hitChance -= Player.hitChanceModifier / 100;
		Player.hitChance -= Enemy.hitChanceModifier / 100;

		if (Player.result == "attack") {
			if (Enemy.hitChance >= attackChance) {
				Player.HP -= Enemy.hitDamageRange;
			}
		}
		if (Player.result == "special attack") {
			if (Enemy.hitChance >= specialAttackChance) {
				Player.HP -= Enemy.hitDamageRange;
			}
		}
		if (Enemy.result == "attack") {
			if (Player.hitChance < attackChance) {
				Enemy.HP -= Player.hitDamageRange;
			}
		}
		if (Enemy.result == "special attack") {
			if (Player.hitChance >= specialAttackChance) {
				Enemy.HP -= Player.hitDamageRange;
			}
		}

		// energy recharge
		Player.ENERGY += 1 * Player.energyRechargeRate;
		Enemy.ENERGY += 1 * Enemy.energyRechargeRate;

		// clamp energy to 100
		if (Player.ENERGY > 100) { Player.ENERGY = 100; }
		if (Enemy.ENERGY > 100) { Enemy.ENERGY = 100; }

		firstTurn = false;

		// round health to 0 if below 1
		if (Player.HP < 1) { Player.HP = 0; };
		if (Enemy.HP < 1) { Enemy.HP = 0; };

		system("CLS");

		// play screen text
		mainMenuPrint(Player.HP, Enemy.HP, Player.ENERGY, Enemy.ENERGY);

		// player hit chance display
		gameplayActionPrinting(Player.result, Player.hitChance, attackChance, Player.hitDamageRange, specialAttackChance, Player.name);
		gameplayActionPrinting(Enemy.result, Enemy.hitChance, attackChance, Enemy.hitDamageRange, specialAttackChance, Enemy.name);
	}
	return;
}

/// <summary>
/// (WIP) Prints gameplay action result to console.
/// </summary>
/// <param name="result"></param>
/// <param name="hitChance"></param>
/// <param name="attackChance"></param>
/// <param name="hitDamageRange"></param>
/// <param name="specialAttackChance"></param>
/// <param name="name"></param>
void gameplayActionPrinting(std::string result, int hitChance, int attackChance, int hitDamageRange, int specialAttackChance, std::string name) {
	if (result == "attack") {
		if (hitChance >= attackChance) {
			std::cout << FBLU("\n\n ") << FBLU(<< name << ) << FBLU(" used ") << FBLU(<< result << ) FBLU(" and did ") FBLU(<< hitDamageRange << ) FBLU(" damage!");
		}
		else if (hitChance < attackChance) {
			std::cout << FBLU("\n\n ") << FBLU(<< name << ) << FBLU(" tried to use ") << FBLU(<< result << )  FBLU(" but the attack missed!");
		}
	}
	else if (result == "special attack") {
		if (hitChance >= specialAttackChance) {
			std::cout << FBLU("\n\n ") << FBLU(<< name << ) << FBLU(" used ") << FBLU(<< result << ) FBLU(" and did ") FBLU(<< hitDamageRange << ) FBLU(" damage!");
		}
		else if (hitChance < specialAttackChance) {
			std::cout << FBLU("\n\n ") << FBLU(<< name << ) << FBLU(" tried to use ") << FBLU(<< result << )  FBLU(" but the attack missed!");
		}
	}
	else {
		std::cout << FBLU("\n\n ") << FBLU(<< name << ) << FBLU(" used ") << FBLU(<< result << ) FBLU(" and did ") FBLU(<< hitDamageRange << ) FBLU(" damage!");
	}
	std::cout << std::endl;
}


/// <summary>
/// Prints action menu in-game.
/// </summary>
/// <param name="HP"></param>
/// <param name="HP"></param>
/// <param name="playerENERGY"></param>
/// <param name="enemyENERGY"></param>
void mainMenuPrint(int HP, int HP2, int playerENERGY, int enemyENERGY){
	std::cout << "\n Fight!\n\n\n\n\n\n\n";

	//color values from colors.h
	std::cout << FGRN(" Player HP:") << FGRN(<< HP << );
	std::cout << FRED("    Enemy HP:") << FRED(<< HP2 << );
	std::cout << FGRN("\n Player Energy:") << FGRN(<< playerENERGY << );
	std::cout << FRED(" Enemy Energy:") << FRED(<< enemyENERGY << );

	std::cout << "\n\n\n\n Press " << playMenuChoices::attack << " for a regular attack (has 80% hit chance)";
	std::cout << "\n Press " << playMenuChoices::specialAttack << " for a special attack (has 50% hit chance)";
	std::cout << "\n Press " << playMenuChoices::recharge << " to recharge energy (recharges energy 4 times faster for this turn, but gives enemy 10% higher hit chance)";
	std::cout << "\n Press " << playMenuChoices::dodge << " to dodge (decreases enemy hit chance by 30%, but halves energy recharge rate)";
	std::cout << "\n Press " << playMenuChoices::heal << " to heal (heal half your energy up to max health, and gives you chance to use another action)";
	std::cout << "\n Press " << playMenuChoices::exitTime << " to exit the game";
}
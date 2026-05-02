#include <iostream>
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Zombie {
    string name;
    int health;
    int attack;
};

int main() {
    srand(time(0));

    map<string, int> playerScore;
    multimap<int, Zombie> zombies;

    zombies.insert({1, {"Walker", 40, 10}});
    zombies.insert({1, {"Crawler", 30, 8}});
    zombies.insert({2, {"Runner", 50, 15}});
    zombies.insert({2, {"Brute", 70, 20}});
    zombies.insert({3, {"Boss Zombie", 100, 25}});

    string player;
    cout << "Enter player name: ";
    cin >> player;

    playerScore[player] = 0;
    int playerHealth = 100;

    int level;
    cout << "Enter level (1-3): ";
    cin >> level;

    auto range = zombies.equal_range(level);

    if (range.first == range.second) {
        cout << "No zombies in this level!\n";
        return 0;
    }

    cout << "\n🔥 Game Start!\n";

    for (auto it = range.first; it != range.second; ++it) {
        Zombie z = it->second;

        cout << "\n🧟 A " << z.name << " appears! (Health: " << z.health << ")\n";

        while (z.health > 0 && playerHealth > 0) {

            int choice;
            cout << "\nChoose your attack:\n";
            cout << "1. Quick Attack\n2. Normal Attack\n3. Heavy Attack\n4. Exit Game\n";
            cin >> choice;

            if (choice == 4) {
                cout << "\n👋 You exited the game!\n";
                cout << "Final Score: " << playerScore[player] << endl;
                return 0;
            }

            // ❌ invalid input
            if (choice < 1 || choice > 4) {
                cout << "❌ Invalid choice! Try again.\n";
                continue;
            }

            int playerHit;

            if (choice == 1) {
                playerHit = rand() % 8 + 8;
                cout << "⚡ Quick Attack!\n";
            }
            else if (choice == 2) {
                playerHit = rand() % 14 + 12;
                cout << "⚔️ Normal Attack!\n";
            }
            else { // choice == 3
                playerHit = rand() % 16 + 20;
                cout << "💥 Heavy Attack!\n";
            }

            z.health -= playerHit;
            cout << "You hit " << z.name << " for " << playerHit << " damage!\n";

            if (z.health <= 0) {
                cout << "💥 " << z.name << " defeated!\n";
                playerScore[player] += 20;
                break;
            }
            
            int zombieHit = rand() % z.attack + 5;

            if (choice == 3 && rand() % 2 == 0) {
                zombieHit += 10;
                cout << "😈 Zombie did a CRITICAL HIT!\n";
            }

            playerHealth -= zombieHit;
            cout << z.name << " hits you for " << zombieHit << " damage!\n";

            cout << "Your Health: " << playerHealth << " | "
                 << z.name << " Health: " << z.health << "\n";

            if (playerHealth <= 0) {
                cout << "\n💀 You were defeated by " << z.name << "...\n";
                cout << "Final Score: " << playerScore[player] << endl;
                return 0;
            }
        }
    }

    cout << "\n🏆 You cleared all zombies in this level!\n";
    cout << "Final Score: " << playerScore[player] << endl;

    return 0;
}
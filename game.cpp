#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    map<string, int> playerScore;
    multimap<int, string> zombies;

    // Adding zombies to levels
    zombies.insert({1, "Walker"});
    zombies.insert({1, "Crawler"});
    zombies.insert({2, "Runner"});
    zombies.insert({2, "Brute"});
    zombies.insert({3, "Boss Zombie"});

    string player;
    cout << "Enter player name: ";
    cin >> player;

    playerScore[player] = 0;

    int level;
    cout << "Enter level (1-3): ";
    cin >> level;

    cout << "\nZombies in this level:\n";

    auto range = zombies.equal_range(level);

    for (auto it = range.first; it != range.second; ++it) {
        cout << "Fighting: " << it->second << endl;
        cout << "You defeated it!\n";
        playerScore[player] += 10;
    }

    cout << "\nFinal Score of " << player << " = " << playerScore[player] << endl;

    return 0;
}
#include <iostream>
//#include <unordered_map>
//#include <bits/stdc++.h>
//#include <views>
#include <vector>
#include <ranges>
#include <algorithm>
#include <print>
#include <format>

using namespace std;

#include <ranges>
#include <memory>


class Fighter {
public:
    int getBaseDamage(){return 5;}
    int getSpecialDamage(){return 10;}
    pair<int,double> getArmor(){return {2, 0.2};}
private:
    string name;
    int healthMax, healthCurr;
    // equipment
};

class Player{
public:
    Player(string_view _playerName) : playerName(_playerName) {};

    const string &getName() const{return playerName;}

    void addFighter(unique_ptr<Fighter> f){
        fighters.emplace_back(move(f));
    }
private:
    string playerName;
    vector<unique_ptr<Fighter>> fighters;
};


int main() {
    cout << "Hello, World!" << endl;
    // load JSON files?
    // prompt player name
    cout << "Enter your name: ";
    string playerName;
    getline(cin, playerName);

    //println("Welcome, {}", playerName);
    //println("Welcome");
    //cout << format("Welcome, {}", playerName);

    // player has 1 or more fighters
    Player thePlayer{playerName};
    cout << format("Welcome, {}", thePlayer.getName());

    // create fighter
    //Fighter theFighter;
    //thePlayer.addFighter(theFighter);
    thePlayer.addFighter(make_unique<Fighter>());

    // create opponent
    Player theEnemy{"Mutant Grasshopper"};

    // enter encounter loop

    // print results

    return 0;
}

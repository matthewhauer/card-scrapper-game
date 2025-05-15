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
    // todo: split record and instance
public:
    Fighter(string_view _fighterName) : fighterName{_fighterName} {;}
    Fighter(string_view _fighterName, int _hp) : fighterName{_fighterName}, healthMax{_hp}, healthCurr{_hp} {;}

    void setHealthMax(int _health){
        if(_health > 0){
            healthMax = healthCurr = _health;
        } else {
            // warn?
        }
    }

    void setHealthCurr(int _health, bool overheal = false){
        if(_health > healthMax && overheal){
            if(overheal) {
                healthCurr = _health;
            } else {
                healthCurr = healthMax;
            }
        } else {
            healthCurr = _health;
        }
    }

    const string_view getName() const {return fighterName;};
    const int getHealthCurr() const{return healthCurr;}
    const int getHealthMax() const{return healthMax;}

    const int getBaseDamage() const {return 5;}
    const int getSpecialDamage() const {return 10;}
    const pair<int,double> getArmor() const {return {2, 0.2};}

    // todo: equip weapon
    // todo: equip armor

    bool isDefeated(){
        // may be additional checks in the future: stunned, frozen, gave up, charmed, bribed...
        return (healthCurr <= 0 ? true : false);
    }
private:
    string fighterName{};
    int healthMax{};
    int healthCurr{};
    // equipment
};

class Player{
public:
    Player(string_view _playerName) : playerName(_playerName) {};

    const string &getName() const{return playerName;}

    void addFighter(shared_ptr<Fighter> f){
        fighters.emplace_back(f);
    }

    bool isDefeated(){
        // if all fighters have 0 hp
        for(auto f : fighters) {
            if (!f->isDefeated()) {
                return false;
            }
        }
        return true;
    }
private:
    string playerName;
    vector<shared_ptr<Fighter>> fighters;
};

// recorded encounter parameters
class EncounterRecord {

};

class Encounter {
public:
    //Encounter(auto _player, auto _opfor) : thePlayer{_player}, opposition{_opfor} {;}
    void setPlayer(shared_ptr<Player> _p){thePlayer = _p;}
    void addOpposition(shared_ptr<Player> _op){opposition.push_back(_op);}

    bool isDone() {
        // player defeated?
        if(thePlayer->isDefeated())
            return true;
        // all enemies defeated?
        if(ranges::fold_left(opposition, true, [](bool res, auto op){return res && op->isDefeated();}))
            return true;
        return false;
    }

    void printStats() {
        // todo: print stats
        cout << "Player:   " << thePlayer->getName() << " -- " <<
           (thePlayer->isDefeated() ? "VICTORIOUS" : "DEFEATED") << endl;
        for(auto op : opposition){
            cout << "Opponent:   " << op->getName() << " -- " <<
                 (op->isDefeated() ? "VICTORIOUS" : "DEFEATED") << endl;
        }
    }

protected:
    shared_ptr<Player> thePlayer;
    vector<shared_ptr<Player>> opposition;
    shared_ptr<EncounterRecord> encounterRef;
};

int main() {
    // todo: load JSON files?
    // prompt player name
    cout << "Enter your fighter's name: ";
    string playerName{};
    getline(cin, playerName);

    // player has 1 or more fighters
    //Player thePlayer{playerName};
    auto thePlayer = make_shared<Player>(playerName);
    cout << format("Welcome, {}", thePlayer->getName()) << endl;

    // create fighter
    thePlayer->addFighter(make_shared<Fighter>(playerName, 100));

    // create opponent
    auto theEnemyFighter = make_shared<Fighter>("Grasshopper Legion", 20);
    auto theEnemy = make_shared<Player>("Grasshopper Legion");
    theEnemy->addFighter(theEnemyFighter);

    // set up Encounter
    Encounter theEncounter{};
    theEncounter.setPlayer(thePlayer);
    theEncounter.addOpposition(theEnemy);
    // enter encounter loop
    // todo: encounter end conditionals, inc. encounter turns, all enemies defeated, ...
    // todo: encounter end conditionals with non-success other than defeat
    // todo: encounter opfors, rewards

    while(!theEncounter.isDone()){
        // todo: print status
        // todo: prompt action
        // execute action
        cout << "Smack enemy..." << endl;
        // smack enemy fighter
        theEnemyFighter->setHealthCurr(0);
        // todo: print status
        // todo: simulate enemy action

    }

    // print results
    theEncounter.printStats();

    return 0;
}

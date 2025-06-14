#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <thread>
#include <chrono>
#include "Player.h"
using namespace std;

Player::Player() {
    max_hp = 100;
    max_stamina = 10;
    hp = max_hp;
    stamina = 10;
}

int Player::attack() {
    while(true) {
        cout << "Enter 'N' for normal attack and 'C' for critical attack: ";
        cin >> attk_type;
        this_thread::sleep_for(chrono::seconds(1));

        if(attk_type == "N" || attk_type == "n") {
            stamina_loss = 2;
            break;
        }

        else if(attk_type == "C" || attk_type == "c") {
            stamina_loss = 4;
            break;
        }

        else {
            cout << "Enter a valid input!!!" << endl;
            continue;
        }
    }

    if(stamina - stamina_loss < 0) {
        cout << "You don't have enough stamina!!!" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        attk = 0;
    }

    else {
        cout << "You used " << stamina_loss << " stamina!" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        stamina -= stamina_loss;
        attk = stamina_loss*10;
    }

    return attk;
}

void Player::damaged() {
    cout << "Ghost inflicted " << enemy_attk << " damage." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    if(enemy_attk > hp) {
        enemy_attk = hp;
    }
    hp -= enemy_attk;
}

void Player::defend() {
    enemy_attk /= 2;
}

void Player::heal() {
    heal_hp = (rand() % 31) + 20;

    if(heal_hp > max_hp - hp) {
        heal_hp = max_hp - hp;
    }

    heal_stamina = (rand() % 5) + 1;

    if(heal_stamina > max_stamina - stamina) {
        heal_stamina = max_stamina - stamina;
    }

    hp += heal_hp;
    stamina += heal_stamina;

    cout << "You healed " << heal_hp << " HP and " << heal_stamina << " stamina." << endl;
    this_thread::sleep_for(chrono::seconds(1));
}

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include "Enemy.h"
using namespace std;


Enemy::Enemy(int health) {
    max_hp = health;
    hp = health;
    crit = false;
    player_attk = 0;
}


int Enemy::attack() {
    int crit_check = (rand() % 5) + 1;
    if(crit_check == 3) {
        crit = true;
    }

    attk = (rand() % 21) + 20;

    if(crit) {
        attk *= 2;
    }

    return attk;
}


void Enemy::damaged() {
    cout << "Player inflicted " << player_attk << " damage." << endl;
    this_thread::sleep_for(chrono::seconds(1));

    if(player_attk > hp) {
        player_attk = hp;
    }

    hp -= player_attk;
}


void Enemy::defend() {
    player_attk /= 2;
}

void Enemy::heal() {
    heal_hp = (rand() % 11) + 20;

    if(heal_hp > max_hp - hp) {
        heal_hp = max_hp - hp;
    }

    hp += heal_hp;

    cout << "Ghost healed " << heal_hp << " HP." << endl;
    this_thread::sleep_for(chrono::seconds(1));
}

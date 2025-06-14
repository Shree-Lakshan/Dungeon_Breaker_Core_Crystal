#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
public:
    int pos[2];
    int max_hp;
    int hp;
    int heal_hp;
    int attk;
    int player_attk;
    bool crit;

    Enemy(int health);

    int attack();
    void damaged();
    void defend();
    void heal();


};

#endif // ENEMY_H

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player {
public:
    int max_hp;
    int max_stamina;
    int hp;
    int stamina;
    int stamina_loss;
    int heal_hp;
    int heal_stamina;
    int attk;
    int enemy_attk;
    string attk_type;

    Player();
    int attack();
    void damaged();
    void defend();
    void heal();

};


#endif // PLAYER_H

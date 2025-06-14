#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <thread>
#include <chrono>
#include "Player.h"
#include "Enemy.h"
using namespace std;

//conditions to end the game
struct game_condition {
    bool player_lost = false;
    bool end_game = false;
};

//temp memory of the save data
struct save_data {
    int player_pos[2];
    int enemies[3][2];
    int hp;
    int stamina;
    bool orb;
    int orb_pos[2];
    bool enemy_alive[3];
};

//check if the files are available in the parent folder
void check_file_availability() {
    ifstream leader_board_file("leader_board.csv");
    if(!leader_board_file) {
        // create a leaderboard file
        ofstream create_leaderboard("leader_board.csv");
        create_leaderboard << "Name,Score,Status\n";
        create_leaderboard.close();
    }
    leader_board_file.close();

    ifstream save_file("save.dat", ios::binary);
    if(!save_file) {
        // create a save data file
        ofstream create_save("save.dat", ios::binary);
        create_save.close();
    }
    save_file.close();
}

//game menu
int menu() {
    int choice;
    cout << "         **MENU**" << endl
        << "1. New Game " << endl
        << "2. Load Game" << endl
        << "3. Exit Game" << endl << endl
        << "Your Choice: ";
    cin >> choice;

    cin.clear();
    cin.ignore(10000, '\n');

    return choice;
}

//format the save file
void format_save() {
    ofstream file("save.dat", ios::binary | ios::trunc);
    file.close();
}

//create a new save file
void create_save() {
    int player_pos[2] = {0, 0};
    int enemies[3][2];
    int x,y;
    int hp = 100;
    int stamina = 10;
    bool orb = false;
    int orb_pos[2] = {(rand() % 3) + 18, (rand()%4) + 2};
    bool enemy_alive[3] = {true, true, true};

    for(int i = 0; i < 3; i++) {
        x = (rand() % 8) + 9;
        y = rand() % 8;
        enemies[i][0] = x;
        enemies[i][1] = y;
    }

    ofstream file("save.dat", ios::binary);

    file.write((char*)&player_pos, sizeof(player_pos));
    file.write((char*)&enemies, sizeof(enemies));
    file.write((char*)&hp, sizeof(hp));
    file.write((char*)&stamina, sizeof(stamina));
    file.write((char*)&orb, sizeof(orb));
    file.write((char*)&orb_pos, sizeof(orb_pos));
    file.write((char*)&enemy_alive, sizeof(enemy_alive));

    file.close();
}

//save the temp save data to the permanent memory
void save_state(save_data &data) {
    format_save();
    ofstream save_file("save.dat", ios::binary);

    save_file.write((char*)&data.player_pos, sizeof(data.player_pos));
    save_file.write((char*)&data.enemies, sizeof(data.enemies));
    save_file.write((char*)&data.hp, sizeof(data.hp));
    save_file.write((char*)&data.stamina, sizeof(data.stamina));
    save_file.write((char*)&data.orb, sizeof(data.orb));
    save_file.write((char*)&data.orb_pos, sizeof(data.orb_pos));
    save_file.write((char*)&data.enemy_alive, sizeof(data.enemy_alive));

    save_file.close();
}

//load the permanent data to the temp save data
save_data load_save() {
    save_data data;
    ifstream save_file("save.dat", ios::binary);

    save_file.read((char*)&data.player_pos, sizeof(data.player_pos));
    save_file.read((char*)&data.enemies, sizeof(data.enemies));
    save_file.read((char*)&data.hp, sizeof(data.hp));
    save_file.read((char*)&data.stamina, sizeof(data.stamina));
    save_file.read((char*)&data.orb, sizeof(data.orb));
    save_file.read((char*)&data.orb_pos, sizeof(data.orb_pos));
    save_file.read((char*)&data.enemy_alive, sizeof(data.enemy_alive));

    return data;
}

//leaderboard logic
void leader_board(save_data &data, game_condition &condition) {
    ofstream file("leader_board.csv", ios::app);

    string name;
    int score = 0;
    string status;

    cout << "Enter your name to add to leader_board: ";
    cin >> name;

    for(int i = 0; i < 3; i++) {
        if(data.enemy_alive[i] == false) {
            score += 10;
        }
    }

    if(condition.player_lost) {
        status = "Failure";
    }
    else {
        status = "Victory";
    }

    file << name << "," << score << "," << status << "\n";

    file.close();

}

//print the lore story
void lore_story() {
    cout << "       THE LEGEND HAS IT THAT WHOEVER DARES TO GO INSIDE THE HAUNTED DUNGEON OF PINE FOREST" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "                       WILL BE HUNTED BY THE GHOSTS OF THE DUNGEON" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "               AND WHOEVER DIES INSIDE THE DUNGEON WILL TURN INTO GHOSTS THAT HUNT" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "                       WHOEVER DARES TO TRESPASS THE DUNGEON AGAIN";
    this_thread::sleep_for(chrono::seconds(1));
    cout << ".";
    this_thread::sleep_for(chrono::seconds(1));
    cout << ".";
    this_thread::sleep_for(chrono::seconds(1));
    cout << "." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << endl;
    this_thread::sleep_for(chrono::seconds(2));
    cout << "                       ONLY THE LIGHT TORCH WILL BE ABLE TO HURT THE GHOSTS" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "                           IT ALSO HELPS TO DEFEND THE GHOSTS' ATTACK" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "                       IT HEALS WHOEVER IS HOLDING IT WHENEVER THEY WANT TOO" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "                                   SO THIS TORCH IS THE REAL DEAL" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "       ANOTHER HUMAN WITH THE POWER OF THE LIGHT TORCH ENTERED THE CURSED DOORS OF THE DUNGEON";
    this_thread::sleep_for(chrono::seconds(1));
    cout << ".";
    this_thread::sleep_for(chrono::seconds(1));
    cout << ".";
    this_thread::sleep_for(chrono::seconds(1));
    cout << "." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << endl << endl;
}

//battle logic
int battle(int enemy_no, save_data &data, Player *hero) {
    int HP = ((rand() % 3) + 1)*100;
    int choice;
    int enemy_choice;
    int chance_to_miss;

    Enemy *enemy = new Enemy(HP);

    cout << "YOU GOT YOURSELF INTO A BATTLE WITH THE DUNGEON GHOST!!!" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "                  THE BATTLE BEGINS!!!" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << endl << endl;

    while(data.enemy_alive[enemy_no]) {
        cout << "Player HP: ";
        for(int i = 1; i <= floor(hero->hp / 10); i++) {
            cout << "|";
        }
        cout << "(" << hero->hp << ")" << endl;
        cout << "Player Stamina: ";
        for(int i = 1; i <= hero->stamina; i++) {
            cout << "|";
        }
        cout << "(" << hero->stamina << ")" << endl << endl;
        cout << "Enemy HP: ";
        for(int i = 1; i <= floor(enemy->hp / 10); i++) {
            cout << "|";
        }
        cout << "(" << enemy->hp << ")" << endl << endl;

        cout << "1. Attack" << endl
             << "2. Defend" << endl
             << "3. Heal" << endl
             << "Your Choice: ";
        cin >> choice;

        cin.clear();
        cin.ignore(10000, '\n');

        if(enemy->hp <= (enemy->max_hp)/2) {
            enemy_choice = (rand() % 3) + 1;
        }

        else {
            enemy_choice = (rand() % 2) + 1;
        }

        if(hero->hp < (hero->max_hp)/2) {
            enemy_choice = 1;
        }

        switch(choice) {
        case 1: {
            chance_to_miss = (rand() % 5) + 1;

            if(chance_to_miss == 3) {
                cout << "Player missed!!!" << endl;
            }

            else {
                enemy->player_attk = hero->attack();
                if(enemy->player_attk == 50) {
                    enemy_choice = 2;
                }
            }

            if(enemy_choice == 1) {
                enemy->damaged();
                cout << endl;
                cout << "The ghost chose to attack!!!" << endl;
                this_thread::sleep_for(chrono::seconds(1));
                hero->enemy_attk = enemy->attack();
                hero->damaged();
            }
            else if(enemy_choice == 2) {
                cout << "The ghost chose to defend..." << endl;
                this_thread::sleep_for(chrono::seconds(1));
                enemy->defend();
                cout << endl;
                enemy->damaged();
            }
            else if(enemy_choice == 3) {
                enemy->damaged();
                cout << endl;
                cout << "The ghost chose to heal..." << endl;
                this_thread::sleep_for(chrono::seconds(1));
                enemy->heal();
            }
            break;
        }
        case 2: {
            if(enemy_choice == 1) {
                hero->enemy_attk = enemy->attack();
                cout << "Player chose to defend..." << endl;
                this_thread::sleep_for(chrono::seconds(1));
                hero->defend();
                cout << endl;
                hero->damaged();
            }
            else if(enemy_choice == 3) {
                cout << "The ghost chose to heal..." << endl;
                this_thread::sleep_for(chrono::seconds(1));
                enemy->heal();
            }
            break;
        }
        case 3: {
            if(enemy_choice == 1) {
                hero->enemy_attk = enemy->attack();
                hero->damaged();
            }

            cout << "Player chose to heal..." << endl;
            this_thread::sleep_for(chrono::seconds(1));
            hero->heal();

            if(enemy_choice == 3) {
                cout << "The ghost chose to heal..." << endl;
                this_thread::sleep_for(chrono::seconds(1));
                enemy->heal();
            }
            break;
        }
        default:{
            cout << "Enter a valid input!!!" << endl;
            continue;
        }
        }

        if(hero->hp == 0) {
            cout << "Player lost the battle!!!" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            delete hero;
            return 0;
        }

        if(enemy->hp == 0) {
            cout << "The ghost is defeated!!!" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            delete enemy;
            data.enemy_alive[enemy_no] = false;
            data.enemies[enemy_no][0] = -100;
            data.enemies[enemy_no][1] = -100;
            return 1;
        }


    }
}

//create the grid of the dungeon
void create_grid(save_data &data) {
    for(int j = 7; j >= 0; j--) {
        for(int i = 0; i <= 23; i++) {
            if(i == data.player_pos[0] && j == data.player_pos[1]) {
                cout << " P ";
            }

            else if(i == data.enemies[0][0] && j == data.enemies[0][1]) {
                cout << " E ";
            }

            else if(i == data.enemies[1][0] && j == data.enemies[1][1]) {
                cout << " E ";
            }

            else if(i == data.enemies[2][0] && j == data.enemies[2][1]) {
                cout << " E ";
            }

            else if(i == data.orb_pos[0] && j == data.orb_pos[1] && data.orb == false) {
                cout << " O ";
            }

            else if((j != 4 && j != 3) && (i == 8 || i == 17)) {
                cout << " | ";
            }

            else if(i == 21 && (j == 4 || j == 3)) {
                if(data.orb) {
                    cout << " . ";
                }
                else {
                    cout << " | ";
                }
            }

            else if((j < 8 && (i < 8 || i < 17)) || (i <= 21 && j >= 2 && j <= 5) || (i < 23 && (j == 3 || j == 4))) {
                cout << " . ";
            }

            else {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

//the main game
void main_game() {
    save_data game_state = load_save();
    game_condition condition;
    string choice;
    double distance;
    int battle_status;
    bool exit;

    Player *player = new Player();
    player->hp = game_state.hp;
    player->stamina = game_state.stamina;

    while(!condition.player_lost && !condition.end_game) {
        create_grid(game_state);
        cout << endl;
        cout << "Q:save state         W:move forward         S:move backward         A:move left         D:move right         E:exit" << endl;
        cout << endl;
        cout << "Enter: ";
        cin >> choice;
        cout << endl;

        if(choice == "Q" || choice == "q") {
            save_state(game_state);
            cout << "Saving";
            this_thread::sleep_for(chrono::seconds(1));
            cout << ".";
            this_thread::sleep_for(chrono::seconds(1));
            cout << ".";
            this_thread::sleep_for(chrono::seconds(1));
            cout << "." << endl;
            cout << "Data saved successfully!!!" << endl;
            cout << endl;
        }

        else if(choice == "E" || choice == "e") {
            exit = true;
            break;
        }

        else if(choice == "W" || choice == "w") {
            if(game_state.player_pos[1] == 7 && game_state.player_pos[0] < 17) {
                continue;
            }
            else if(game_state.player_pos[1] == 5 && (game_state.player_pos[0] < 22 && game_state.player_pos[0] > 17)) {
                continue;
            }
            else if(game_state.player_pos[0] == 21 && game_state.player_pos[1] == 2) {
                if(!game_state.orb) {
                    continue;
                }
                else {
                    game_state.player_pos[1] += 1;
                }
            }
            else {
                game_state.player_pos[1] += 1;
            }
        }

        else if(choice == "S" || choice == "s") {
            if(game_state.player_pos[1] == 0 && game_state.player_pos[0] < 17) {
                continue;
            }
            else if(game_state.player_pos[1] == 2 && (game_state.player_pos[0] < 22 && game_state.player_pos[0] > 17)) {
                continue;
            }
            else if(game_state.player_pos[0] == 21 && game_state.player_pos[1] == 5) {
                if(!game_state.orb) {
                    continue;
                }
                else {
                    game_state.player_pos[1] -= 1;
                }
            }
            else {
                game_state.player_pos[1] -= 1;
            }
        }

        else if(choice == "A" || choice == "a") {
            if(game_state.player_pos[0] == 0) {
                continue;
            }
            else if(game_state.player_pos[0] == 9 && game_state.player_pos[1] != 3 && game_state.player_pos[1] != 4) {
                continue;
            }
            else if(game_state.player_pos[0] == 18 && game_state.player_pos[1] != 3 && game_state.player_pos[1] != 4) {
                continue;
            }
            else {
                game_state.player_pos[0] -= 1;
            }
        }

        else if(choice == "D" || choice == "d") {
            if(game_state.player_pos[0] == 7 && game_state.player_pos[1] != 3 && game_state.player_pos[1] != 4) {
                continue;
            }
            else if(game_state.player_pos[0] == 16 && game_state.player_pos[1] != 3 && game_state.player_pos[1] != 4) {
                continue;
            }
            else if(game_state.player_pos[0] == 21 && game_state.player_pos[1] != 3 && game_state.player_pos[1] != 4) {
                continue;
            }
            else if(game_state.player_pos[0] == 20 && (game_state.player_pos[1] == 3 || game_state.player_pos[1] == 4)) {
                if(game_state.orb == false) {
                    continue;
                }
                else {
                    game_state.player_pos[0] += 1;
                }
            }
            else {
                game_state.player_pos[0] += 1;
            }
        }

        else {
            cout << "Enter a valid input!!!" << endl;
            cout << endl;
            continue;
        }

        for(int i = 0; i < 3; i++) {
            distance = pow(pow(game_state.player_pos[0] - game_state.enemies[i][0], 2) + pow(game_state.player_pos[1] - game_state.enemies[i][1], 2), 0.5);

            if(distance == 1 || distance == pow(2, 0.5)) {
                battle_status = battle(i, game_state, player);
                if(battle_status == 0) {
                    condition.player_lost = true;
                }
            }
        }
        if((game_state.player_pos[0] == game_state.orb_pos[0]) && (game_state.player_pos[1] == game_state.orb_pos[1]) && !game_state.orb) {
            game_state.orb = true;
        }

        if(game_state.player_pos[0] == 22 && (game_state.player_pos[1] == 3 || game_state.player_pos[1] == 4)) {
            condition.end_game = true;
        }
    }

    if(!exit) {
        if(condition.player_lost) {
            cout << "You lost the game!!!" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            cout << "You are one of the ghosts now who will haunt whoever dares to wander the dungeon..." << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }

        if(condition.end_game) {
            cout << "You won the game!!!" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            cout << "You broke the haunted dungeon which haunted people for centuries!!!" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            cout << "YOU ARE THE LEGENDARY DUNGEON BREAKER!!!!" << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }

        format_save();
        leader_board(game_state, condition);
    }

}


int main() {
    srand(time(0));

    cout << "  **DUNGEON BREAKER:THE CORE CRYSTAL**  " << endl << endl;

    check_file_availability();
    bool exit = false;

    while(true) {
        switch(menu()) {
        case 1: {
            format_save();
            create_save();
            lore_story();
            break;
        }

        case 2: {
            ifstream file("save.dat", ios::binary | ios::ate);

            if(file.tellg() == 0) {
                cout << "There is no existing save file to load!!!" << endl;
                continue;
            }
            file.close();
            break;
        }

        case 3: {
            cout << "Thank you for playing!!!" << endl;
            exit = true;
            break;
        }

        default: {
            cout << "Enter a valid input!!!" << endl;
            continue;
        }
        }
        if(exit) {
            break;
        }
        main_game();
    }

    return 0;
}

#include <iostream>
#include <vector>
using namespace std; 

struct player_data 
{ 
    string name; 

    int spaces_moved = 0;
    int money = 200; 
    bool in_jail = false; 
    int num_turns = 3; 
}; 

struct property_data 
{ 
    string name; 
    int purchase_price = 0; 
    int rent_price = 0;  
    bool is_owned = false; 
    player_data* owner;

    // for chance and community cards (assumes action will be either one of these three)
    int give_money = 0; 
    int take_money = 0; 
    int move_to = 0;
};

struct game_data 
{ 
    int num_players; 
};

// global vars
const int TOTAL_BOARD_SPACES = 40;

// create pointer for game
game_data *game = new game_data;

// create array of player pointers
player_data *players[4];

// create array of pointers of dif types of properties/board spots (chance, community, railroad, etc)
property_data *board_spaces[TOTAL_BOARD_SPACES];


void start_game()
{
    // initialize num players, their tokens (thimble, tophat, etc), money 
    int num; 
    cout << "How many players? "; 
    cin >> num; 
    for (int i =0; i < num; i++) 
    { 
        players[i] = new player_data; 
    }
    // insert rest later
}

bool in_jail(player_data* player) 
{ 
    return player -> in_jail; 
}

int roll_dice() 
{ 
    // insert rng
    return 4; 
}

void withdraw_money(player_data*& player, int amount) 
{ 
    player -> money -= amount; 
}

void deposit_money(player_data*& player, int amount) 
{ 
    player -> money += amount;
}

void move_to_space(player_data*& player, int spaces)
{ 
    player -> spaces_moved = spaces; 
}

void collect_go(player_data*& player) 
{ 
    // give player $200 for passing Go 
    deposit_money(player, 200); 
}

bool stop_game() 
{ 
    // insert later 
    return false;
}

void pay_rent(player_data* player, player_data* player_to_pay, int amount_to_pay) 
{ 
    withdraw_money(player, amount_to_pay);
    deposit_money(player_to_pay, amount_to_pay);
}

void buy_property(player_data *player, property_data *prop)
{
    int price = prop->purchase_price;

    withdraw_money(player, price);
    prop->owner = player;
    prop->is_owned = true;
}

// for testing
void print_player_data(player_data* player)
{ 
    cout << "Name: " << player-> name << endl; 
    cout << "Spaces moved: " << player-> spaces_moved << endl; 
    cout << "Money: " << player-> money << endl; 
    cout << "In jail?: " << player-> in_jail << endl; 
    if (player -> in_jail)
        cout << "Turns left before out of jail: " << player-> num_turns << endl; 
}

void print_property_data(property_data* prop)
{ 
    cout << "Name: " << prop-> name << endl; 
    cout << "Purchase price: " << prop -> purchase_price << endl; 
    cout << "Rent price: " << prop-> rent_price << endl; 
    cout << "Is owned?: " << prop-> is_owned << endl; 
    if (prop -> is_owned)
        cout << "Owner: " << prop-> owner -> name << endl;  
    else 
        cout << "Owner: property is unowned" << endl;
}

int main()
{ 
    // set up game; 
    game -> num_players = 4; 

    // set up for testing
    player_data* p1 = new player_data;     
    p1 -> name = "kaylee"; 
    
    player_data* p2 = new player_data; 
    p2 -> name = "rachel";

    player_data* p3 = new player_data;     
    p3 -> name = "jason"; 

    player_data* p4 = new player_data;     
    p4 -> name = "lily";

    players[0] = p1;
    players[1] = p2;
    players[2] = p3;
    players[3] = p4;

    // test buying property
    property_data* go = new property_data; 
    go -> name = "Go"; 
    board_spaces[0] = go;
    print_property_data(go);

    property_data* railroad = new property_data; 
    railroad -> name = "Short Line"; 
    railroad -> purchase_price = 200; 
    railroad -> rent_price = 25; 
    board_spaces[1] = railroad;

    property_data* boardwalk = new property_data; 
    boardwalk -> name = "boardwalk"; 
    boardwalk -> purchase_price = 400; 
    boardwalk -> rent_price = 100; 
    board_spaces[10] = boardwalk;

    // create chance cards
    property_data* chance1 = new property_data; 
    chance1 -> name = "chance"; 
    chance1 -> give_money = 200; 
    board_spaces[2] = chance1;

    property_data* chance2 = new property_data; 
    chance2 -> name = "chance"; 
    chance2 -> take_money = 200; 
    board_spaces[3] = chance2;

    property_data* chance3 = new property_data; 
    chance3 -> name = "chance"; 
    chance3 -> move_to = 10; // will move player to boardwalk
    board_spaces[4] = chance3;

    // play the game!!
    while (!stop_game()) 
    { 
        for (int i = 0; i < game -> num_players; i++) 
        {
            // order of players = whoever enters their info first in start_game()
            player_data* player = players[i]; 
            player_data* next_player; 
            if (i == (game -> num_players) - 1)
            { 
                next_player = players[0];
            }
            else 
            { 
                next_player = players[i+1];
            }

            cout << "It is " << player -> name << "'s turn." << endl;
            
            if (!in_jail(player))
            {
                int spaces_to_move = roll_dice(); 
                cout << "You rolled a " << spaces_to_move << "!" << endl; 
                player -> spaces_moved += spaces_to_move;

                // check if player passed go
                if (player -> spaces_moved >= TOTAL_BOARD_SPACES)
                { 
                    collect_go(player); 
                    cout << "You have passed go. You now have $" << player -> money << "." << endl;
                    player -> spaces_moved -= TOTAL_BOARD_SPACES;
                }

                // get board space/property that player landed on
                property_data* prop = board_spaces[player -> spaces_moved];
                string name = prop -> name;
                cout << "You have landed on " << name << "." << endl;
                
                // assumes that chance cards only involve player and next_player 
                if (name == "chance" || name == "community")
                {
                    if (prop -> give_money != 0)
                    { 
                        // give money to next player
                        cout << "You must pay $" << prop -> give_money << " to the next player, " << next_player -> name << "!";
                        withdraw_money(player, prop -> give_money); 
                        deposit_money(next_player, prop -> give_money); 
                        cout << "You now have $" << player -> money << "." << endl;
                    }
                    else if (prop -> take_money != 0)
                    { 
                        // take money from next player 
                        cout << "You get to take $" << prop -> take_money << " from the next player, " << next_player -> name << "!";
                        deposit_money(player, prop -> take_money);
                        withdraw_money(next_player, prop -> take_money);
                        cout << "You now have $" << player -> money << "." << endl;
                    }
                    else 
                    { 
                        // move to specified space on board
                        int old_space = player -> spaces_moved;
                        int new_space = prop -> move_to;
                        move_to_space(player, new_space);
                        cout << "You have been moved to " << board_spaces[new_space] -> name << "." << endl;

                        // check if player passed go
                        if (new_space < old_space)
                        {
                            collect_go(player);
                            cout << "You have passed Go. You now have $" << player -> money << " ." << endl;
                        }
                    }
                }
                else if (name == "jail")
                {
                    // move player to jail
                    cout << "You've landed in jail! Your next 3 turns will be skipped." << endl;
                    player -> in_jail = true;
                }
                else if (prop->is_owned)
                {
                    // pay rent
                    player_data* player_to_pay = prop->owner;
                    int amount_to_pay = prop->rent_price;

                    cout << name << " is already owned. You must pay " << player_to_pay -> name << " $" << amount_to_pay << " in rent." << endl;
                    pay_rent(player, player_to_pay, amount_to_pay);
                    cout << "You now have $" << player->money << " left." << endl;
                }
                else if (name != "Go")
                {
                    // buy property
                    char buy;
                    cout << name << " is not owned and costs " << prop->purchase_price << "." << endl;
                    if (player->money > 0)
                    {
                        cout << "Would you like to buy " << name << "? (Y/N)" << endl;
                        cin >> buy;
                        if (toupper(buy) == 'Y')
                        {
                            buy_property(player, prop);
                            cout << name << " is now yours! You have $" << player->money << " left." << endl;
                        }
                        else
                            cout << name << " is still unowned." << endl;
                    }
                    else
                        cout << "However, you have $0 left! You will not be able to purchase new property." << endl;
                }
            }
            else
            {
                // keep track of remaining jail time 
                int turns = player -> num_turns; 
                cout << "You are in jail for " << turns-1 << " more turn(s) after this turn." << endl;

                if (turns == 1) 
                { 
                    player -> in_jail = false;
                    player -> num_turns = 3;
                }
                else 
                { 
                    player -> num_turns--; 
                }
            }
        }
    }
}

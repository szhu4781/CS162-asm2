/*********************************************************************
** Program Filename: catalog.cpp
** Author: Shengwei Zhu
** Date: 10/23/23
** Description: This file defines all the functions that were declared in catalog.h.
** Input: none
** Output: none
*********************************************************************/

#include "catalog.h"
#include <fstream>

//function definitions go here

/**************************************************
 * Name: create_teams()
 * Description: This function will dynamically allocate
                an array of teams (of the requested size)
 * Parameters: int - size of the array
 * Pre-conditions: none
 * Post-conditions: a Team array of requested size is created and return
 ***********************************************/
Team* create_teams(int size){
    return new Team[size]; //Returns new team array of requested size
}

/**************************************************
 * Name: populate_team_data()
 * Description: This function will fill a single team struct 
                with information that is read in from the file
 * Parameters:  Team* - pointer to the Team array
                int - index of the Team in the array to be filled 
                ifstream& - input file to get information from
 * Pre-conditions: Team array has been allocated; 
                   provided index is less than the array size
 * Post-conditions: a Team at provided index is populated
 ***********************************************/
void populate_team_data(Team* team_arr, int index, ifstream &file){
    
    //Reads the team information from file
    file >> team_arr[index].name;
    file >> team_arr[index].owner;
    file >> team_arr[index].market_value;
    file >> team_arr[index].num_player;

    //Memory allocation for players
    team_arr[index].p = create_players(team_arr[index].num_player);
    float total = 0;

    //Populates players on team
    for (int i = 0; i < team_arr[index].num_player; i++){
        populate_player_data(team_arr[index].p, i, file);
        total += team_arr[index].p[i].ppg;
    }
    team_arr[index].total_ppg = total;
}

/**************************************************
 * Name: create_players()
 * Description: This function will dynamically allocate
                an array of players (of the requested size)
 * Parameters: int - size of the array
 * Pre-conditions: none
 * Post-conditions: a Player array of requested size is created and return
 ***********************************************/
Player* create_players(int size){
    return new Player[size]; //Returns a new player array of requested size
}

/**************************************************
 * Name: populate_player_data()
 * Description: This function will fill a single player struct 
                with information that is read in from the file
 * Parameters:  Player* - pointer to the Player array
                int - index of the Player in the array to be filled 
                ifstream& - input file to get information from
 * Pre-conditions: Player array has been allocated; 
                   provided index is less than the array size
 * Post-conditions: a Player at provided index is populated
 ***********************************************/
void populate_player_data(Player* plr_arr, int index, ifstream &file){
    //Reads the player information from the file
    file >> plr_arr[index].name;
    file >> plr_arr[index].age;
    file >> plr_arr[index].nation;
    file >> plr_arr[index].ppg;
    file >> plr_arr[index].fg;
}

/**************************************************
 * Name: delete_info()
 * Description: This function will  delete all the memory that was dynamically allocated
 * Parameters: Team* - the Team array
 * Pre-conditions: the provided Team array hasn't been freed yet
 * Post-conditions: the Team array, with all Players inside, is freed
 ***********************************************/
void delete_info(Team* team_arr, int size){
    for (int i = 0; i < size; i++){
        delete[] team_arr[i].p; //Deallocates memory for players inside team array
    }
    delete[] team_arr; //Deallocates memory for team array
}
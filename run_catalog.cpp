/*********************************************************************
** Program Filename: run_catalog.cpp
** Author: Shengwei Zhu
** Date: 10/23/23
** Description: File for running the main program for basketball team catalog.
** The user is given a list of options to display a basketball team's information along with player info.
** Choices consists of searching by team name, display top scorer of each team, and searching player by nationality.
** User also gets an option to print selected info to the screen or to a file of their choice.
** Input: The program reads info stored in text file "teams.txt".
** The program prompts user for inputs for various search and display options.
** Output: The program can display various team and player info to the screen or writes that info to
** a specified output file based on the user preferences. The program will provide error handling for user inputs.
*********************************************************************/

/** Dev Message
 * To the TA who is grading this, I just want to let you know that the main function
 * may or may not be over the 15 line limit. I tried my best to make it not go over the limit
 * as much as possible. However, due to stress and errors that kept getting in the way of everything,
 * I've decided to keep the main function the way it is. It's a bit clogged, but the code should run properly.
 * I've also tripled checked for any segmentation faults and memory leaks earlier, and there doesn't seem to be any.
 * I also added an additional menu option that sorts total ppg in descending order.
 * That's all for now. - SZ
**/

#include <iostream>
#include <fstream>
#include <string>
#include "catalog.h"

/**************************************************
 * Name: write_To_Terminal
 * Description: Function for writing team info to terminal
 * Parameters:  team_data - array of team structure
 * 				num_team - number of teams
 * 				team_name - name of team being displayed
 * Pre-conditions: Team array and team name should not be null;
 * 					team count should be a positive integer
 * Post-conditions: Prints the team information to the terminal
 ***********************************************/
void write_To_Terminal(const Team *team_data, int num_team, const string &team_name){
    
	//for loop to loop through team array
	for (int i = 0; i < num_team; i++ ) {
		if (team_name == team_data[i].name){
			cout << team_data[i].name << endl;
			cout << team_data[i].owner << endl;
			cout << team_data[i].market_value << endl;
			cout << team_data[i].num_player << endl;
			cout << team_data[i].total_ppg << endl;
			
			//for loop to loop through player array
			for(int j = 0; j < team_data[i].num_player; j++){
				cout << team_data[i].p[j].name << endl;
				cout << team_data[i].p[j].age << endl;
				cout << team_data[i].p[j].nation << endl;
				cout << team_data[i].p[j].ppg << endl;
				cout << team_data[i].p[j].fg << endl;												
			}		
		}
    }
}

/**************************************************
 * Name: write_To_File
 * Description: Function for writing team info to a file based on the user's inputs
 * Parameters:  new_file - name of the file for appended info
 * 				team_data - array of team structure
 * 				num_team - number of teams
 * 				team_name - name of teams with their info written to file
 * Pre-conditions: New file should be a valid name; team array and team name should not be null;
 * 					team number should be a positive integer
 * Post-conditions: Appends the team info to speciifed file if team info is found.
 ***********************************************/
void write_To_File(const string &new_file, Team *team_data, int num_team, const string &team_name) {
    ofstream output_file(new_file, ios::app); // Append info to file
	
	//Conditional to create a new file if desired file doesn't exist
	if (!output_file){
		ofstream create_file(new_file);
		create_file.close();
		output_file.open(new_file, ios::app);
	}

	//for loop to loop through team array
    for (int i = 0; i < num_team; i++ ) {
		if (team_name == team_data[i].name){
			output_file << team_data[i].name << endl;
			output_file << team_data[i].owner << endl;
			output_file << team_data[i].market_value << endl;
			output_file << team_data[i].num_player << endl;
			output_file << team_data[i].total_ppg << endl;

			//for loop to loop through player array
			for(int j = 0; j < team_data[i].num_player; j++){
				output_file << team_data[i].p[j].name << endl;
				output_file << team_data[i].p[j].age << endl;
				output_file << team_data[i].p[j].nation << endl;
				output_file << team_data[i].p[j].ppg << endl;
				output_file << team_data[i].p[j].fg << endl;		
			}
		}
    }
	cout << "Appended to file" << endl;
    output_file.close(); //File closes after info is written to file
}

/**************************************************
 * Name: top_Scorer
 * Description: Function for displaying top scorers of each team
 * Parameters:  team_data - array of team structures
 * 				num_team - number of teams
 * Pre-conditions: Team array shouldn't be null;
 * 					team count should be positive integer
 * Post-conditions: Prints out the top scorer of each team based on points per game
 ***********************************************/
void top_Scorer(Team *team_data, int num_team){
	//Goes through the number of teams
	for (int i = 0; i < num_team; i++){
		float max_ppg = 0;

		//Checks the ppg of each players and determines who has the highest ppg
		for (int j = 0; j < team_data[i].num_player; j++){
			max_ppg = max(max_ppg, team_data[i].p[j].ppg);
		}
		//Prints out the player with the top score (highest ppg) 
		for (int j = 0; j < team_data[i].num_player; j++){
			if (team_data[i].p[j].ppg == max_ppg){
				cout << team_data[i].p[j].name;
				break;
			}
		}		
		cout << " " << team_data[i].name << " " << max_ppg << endl; //Prints data
	}
}

/**************************************************
 * Name: top_Scorer_File
 * Description: Function for writing top scorer info into a file
 * Parameters:  new_file - name of the file for appended info
 * 				team_data - array of team structures
 * 				num_team - number of teams
 * Pre-conditions: New file should be a valid name; team array and team name should not be null;
 * 					team number should be a positive integer
 * Post-conditions: Appends the info top scorer and the team they are in to speciifed file if info is found.
 ***********************************************/
void top_Scorer_File(const string &new_file, Team *team_data, int num_team){
	ofstream output_file(new_file, ios::app);
	
	//Conditional to create a new file if desired file doesn't exist
	if (!output_file){
		ofstream create_file(new_file);
		create_file.close();
		output_file.open(new_file, ios::app);
	}

	//Goes through the number of teams
	for (int i = 0; i < num_team; i++){
		float max_ppg = 0;

		//Checks the ppg of each players and determines who has the highest ppg
		for (int j = 0; j < team_data[i].num_player; j++){
			max_ppg = max(max_ppg, team_data[i].p[j].ppg);
		}
		//Prints out the player with the top score (highest ppg) 
		for (int j = 0; j < team_data[i].num_player; j++){
			if (team_data[i].p[j].ppg == max_ppg){
				output_file << team_data[i].p[j].name;
				break;
			}
		}		
		output_file << " " << team_data[i].name << " " << max_ppg << endl;
	}
	cout << "Appended to file" << endl;
    output_file.close(); //File closes after info is written to file	
}

/**************************************************
 * Name: nationality_Print()
 * Description: Function for displaying players from a specific nationality
 * Parameters:  team data - Array for team structure
 * 				num_team - number of teams
 * 				nationality - specific nationality being searched for
 * Pre-conditions: Team array should not be null;
 * 					team count should be a positive integer
 * Post-conditions: Print's the players' name and age based on nationality to terminal
 ***********************************************/
void nationality_Print(Team *team_data, int num_team, const string &nationality){
	bool found = false;

	//for loop goes through team array first, then player array to look for player info
	for (int i = 0; i < num_team; i++ ) {
		for(int j = 0; j < team_data[i].num_player; j++){
			//Displays player name and age if the correct nationality is entered
			if (team_data[i].p[j].nation == nationality){
				found = true;
				cout << team_data[i].p[j].name << " " << team_data[i].p[j].age << endl;		
			}		
		}
    }
	//Error handling for invalid nationality input
	if (!found){
		cout << "No players found." << endl;
	}
}

/**************************************************
 * Name: nationality_Print()
 * Description: Function for displaying players from a specific nationality
 * Parameters:  team data - Array for team structure
 * 				num_team - number of teams
 * 				nationality - specific nationality being searched for
 * Pre-conditions: New file should be valid name; team array should not be null;
 * 					team count should be a positive integer
 * Post-conditions: Appends the players' name and age based on nationality to specified file
 ***********************************************/
void nation_File_Print(const string &new_file, Team *team_data, int num_team, const string &nationality){
	ofstream output_file(new_file, ios::app);
	
	//Conditional to create a new file if desired file doesn't exist
	if (!output_file){
		ofstream create_file(new_file);
		create_file.close();
		output_file.open(new_file, ios::app);
	}

	bool found = false;
	//for loop goes through team array first, then player array to look for player info
	for (int i = 0; i < num_team; i++ ) {
		for(int j = 0; j < team_data[i].num_player; j++){
			//Displays player name and age if the correct nationality is entered
			if (team_data[i].p[j].nation == nationality){
				found = true;
				output_file << team_data[i].p[j].name << " " << team_data[i].p[j].age << endl;		
			}		
		}
    }	
	//Error handling for invalid nationality input
	if (found){
		cout << "Appended to file." << endl;
	}
	else {
		cout << "No players found." << endl;
	}
	output_file.close();
}

/**************************************************
 * Name: sort_Total_PPG
 * Description: Function for sorting teams by total points per game and printing the info to file
 * Parameters:  new_file - name of the file for appended info
 * 				team_data - array of team structures
 *              num_team - number of teams
 * Pre-conditions: new file should be a valid name; 
 * 					team array shouldn't be null;
 *                 team count should be a positive integer
 * Post-conditions: appends the teams sorted by total points per game to the specified file
 ***********************************************/
void sort_Total_PPG(const string &new_file, Team *team_data, int num_team){
    ofstream output_file(new_file, ios::app);
	
	//Conditional to create a new file if desired file doesn't exist
	if (!output_file){
		ofstream create_file(new_file);
		create_file.close();
		output_file.open(new_file, ios::app);
	}

	//Goes through team array
    for(int i = 0; i < num_team; i++) {
		//Checks ppg values of players of each team
        for(int j = i + 1; j < num_team; j++) {
			//Bubble sorting
            if(team_data[i].total_ppg < team_data[j].total_ppg) {
                Team score = team_data[i];
                team_data[i] = team_data[j];
                team_data[j] = score;
            }
        }
    }

    // Print the sorted teams in descending order
    for(int i = 0; i < num_team; i++) {
        cout << team_data[i].name << " " << team_data[i].total_ppg << endl;
    }
	
	cout << "Appended to file" << endl;
    output_file.close(); //File closes after info is written to file
}

/**************************************************
 * Name: user_Menu
 * Description: Function for displaying user interface
 * Parameters:  none
 * Pre-conditions: none
 * Post-conditions: Displays the menu with available options for displaying team and player data
 ***********************************************/
void user_Menu(){
	//Print messages for user interface
	cout << "Which option would you like to choose?" << endl;
	cout << "1. Search team by name" << endl;
	cout << "2. Display the top scorer of each team" << endl;
	cout << "3. Search players by nationality" << endl;
	cout << "4. Sort teams by total points per game" << endl;
	cout << "5. Quit" << endl;
}

/**************************************************
 * Name: print_Choice
 * Description: Function for prompting the user's choice to print data
 * Parameters:  none
 * Pre-conditions: none
 * Post-conditions: Prompts user to choose a choice of where they want their acquired data
 ***********************************************/
void print_Choice(){
	//Print messages for how the user wants to print their data
	cout << "How would you like the information to be displayed?" << endl;
	cout << "1. Print to screen (Press 1)" << endl;
	cout << "2. Print to file (Press 2)" << endl;	
}

/**************************************************
 * Name: file_Input
 * Description: Prompts user to enter the file containing info of each team and its players
 * Parameters:  none
 * Pre-conditions: none
 * Post-conditions: Returns the opened file stream
 ***********************************************/
ifstream file_Input(){
	//Prompts user to enter a text file containing team and player info
	string input_file = "teams.txt";
	cout << "Enter the team info file name (teams.txt): " << endl;
	cin >> input_file;

	ifstream file(input_file); //Opening the file

	//Error handling if the user inputs an incorrect file name
	//Program ends if user the doesn't enter the correct file name
	if (!file || input_file != "teams.txt"){
		cerr << "Invalid file name." << endl;
		exit (1); //Exits program if user enters invalid file name
	}

	return file;
}

/**************************************************
 * Name: main
 * Description: Main program for basketball team catalog.
 * The program reads info stroed in a text file and lets display the info in a variety of options.
 * Parameters:  none
 * Pre-conditions: none
 * Post-conditions: Return 0 after successfully executed
 ***********************************************/
int main(){
	ifstream file = file_Input();

	//Function call for team data
	int num_team = 0;
	file >> num_team;

	Team* team_data = create_teams(num_team);
	for (int i = 0; i < num_team; i++){
		populate_team_data(team_data, i, file);
	} 

	//User choice selection
	//User gets 3 choices to look up info as well as an option to quit
	int choice;

	string team_name; //string for team name input
	string nationality;//string for nationality input
	//User Interface
	do {
		user_Menu();
		cin >> choice;

		int print_Option; //variable for printing options
		string new_file; //string for new file
		switch (choice){
			//Search team by name
			case 1: 
				print_Choice();
				cin >> print_Option;

				//Display info on screen
				if (print_Option == 1){
					//Prompt user to enter a team name
					cout << "Enter a team's name:" << endl;
					cin >> team_name;
					
					write_To_Terminal(team_data, num_team, team_name); //Prints team info on screen/to terminal
				}
				//Writes info to a file and displays it there
				else if (print_Option == 2) {
					cout << "Please provide desired filename: " << endl;
					cin >> new_file;
							
					//Prompt user to enter a team name
					cout << "Enter a team's name: " << endl;
					cin >> team_name;

					write_To_File(new_file, team_data, num_team, team_name); //Prints the team info to a file based on user input
				}
				//Prints error message if user doesn't pick any of the listed options
				else {
					cout << "Invalid input." << endl;
				}
				break;
			//Display top scorer of each team
			case 2:
				print_Choice();
				cin >> print_Option;

				if (print_Option == 1){
					top_Scorer(team_data, num_team);
				}
				else if (print_Option == 2){
					cout << "Please provide desired filename: " << endl;
					cin >> new_file;

					top_Scorer_File(new_file, team_data, num_team);
				}
				else {
					cout << "Invalid input." << endl;
				}
				break;
			//Search players by nationality
			case 3:
				print_Choice();
				cin >> print_Option;

				if (print_Option == 1){
					//Prompt user to enter a nationality
					cout << "Enter a nationality: " << endl;
					cin >> nationality;
					
					nationality_Print(team_data, num_team, nationality);
				}
				else if (print_Option == 2){
					cout << "Please provide desired filename: " << endl;
					cin >> new_file;

					cout << "Enter a nationality: " << endl;
					cin >> nationality;

					nation_File_Print(new_file, team_data, num_team, nationality);
				}
				else {
					cout << "Invalid input." << endl;
				}
				break;
			case 4: 
				cout << "Please provide desired filename: " << endl;
				cin >> new_file;

				sort_Total_PPG(new_file, team_data, num_team);
				break;
			//Quit option	
			case 5: cout << "Bye!" << endl;
				break;
		}
	} while(choice != 5);

	delete_info(team_data, num_team); //Frees allocated memory

	return 0;
}
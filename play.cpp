#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "parser.h"

//classes
class Team {
    public:
        Team();
        Team(string name, string loc, int seed);
        void showTeam();
        void setName(string name);
        void setLocation(string loc);
        void setSeed(int seed);
        string getTeamName();
        int getTeamWins();
        void addWin();
        void showWins();
    private:
        string teamName = "";
        string teamLocation = "";
        int teamSeed = 0;
        int teamWins = 0;
};
Team::Team() {
    teamName = "";
    teamLocation = "";
    teamSeed = 0;
    teamWins = 0;
}
Team::Team(string name, string loc, int seed) {
    teamName = name;
    teamLocation = loc;
    teamSeed = seed;
    teamWins = 0;
}
void Team::showTeam() {
  cout << teamName << " (" << teamLocation << " " << teamSeed << ")" << " [" << teamWins << " wins]";
}
void Team::setName(string name) {
    teamName = name;
}
void Team::setLocation(string loc) {
    teamLocation = loc;
}
void Team::setSeed(int seed) {
    teamSeed = seed;
}
string Team::getTeamName() {
    return teamName;
}
int Team::getTeamWins() {
    return teamWins;
}
void Team::addWin() {
    teamWins++;
}
void Team::showWins() {
    cout << teamWins << endl;
}

class League {
    public:
        League();
        void addTeam(Team team);
        void showLeague();
        Team &playGame(Team team1, Team team2);
        int getSizeOfTeams();
        int getTeamIndex(string name);
        vector<Team> &getLeague();
        Team &getTeam(string name);
        Team &getWinner();
        Team &getTeamAt(int num);
        int tournament(vector<Team> &teams, int left, int right);
    private:
        vector<Team> teams;
        int numTeams = 0;
        string nickname;
};
League::League() {
    Team teams("", "", 0);
}
void League::addTeam(Team team) {
    teams.push_back(team);
}
void League::showLeague() {
  for (unsigned int i = 0; i < teams.size(); i++) {
    teams.at(i).showTeam();
    cout << endl;
  }
}
Team &League::playGame(Team team1, Team team2) {
    if (team1.getTeamName() < team2.getTeamName()) {
        getTeam(team1.getTeamName()).addWin();
        getTeam(team1.getTeamName()).showTeam();
        cout << " defeats ";
        getTeam(team2.getTeamName()).showTeam(); 
        cout << endl;
        return getTeam(team1.getTeamName());
    }
    else {
        getTeam(team2.getTeamName()).addWin();
        getTeam(team2.getTeamName()).showTeam();
        cout << " defeats ";
        getTeam(team1.getTeamName()).showTeam();
        cout << endl;
        return getTeam(team2.getTeamName());
    }
}
int League::getSizeOfTeams() {
    return teams.size();
}
int League::getTeamIndex(string name) {
    int index;
    for (int i = 0; i < teams.size(); ++i) {
        if (name == teams[i].getTeamName()) {
            index = i;
        }
    }
    return index;
}
vector<Team> &League::getLeague() {
    return teams;
}
Team &League::getTeam(string name) {
  int g;
  int index;
  for (g = 0; g < teams.size(); ++g) {
    if (name == teams[g].getTeamName()) { //in team
      index = g;
    }
  }
  return teams[index];
}
Team &League::getWinner() {
    int index;
    for (int i = 0; i < teams.size(); ++i) {
        if (teams[i].getTeamWins() > (teams[i - 1].getTeamWins())) {
            index = i;
        }
    }
    return teams[index];
}
Team &League::getTeamAt(int num) {
    return teams[num];
}

int League::tournament(vector<Team> &teams, int left, int right) {
    int temp3;
    if (left < right) {
        int middle = (left + right) / 2;
        int temp1 = tournament(teams, left, middle);
        int temp2 = tournament(teams, middle + 1, right);
        temp3 = getTeamIndex(playGame(teams.at(temp1), teams.at(temp2)).getTeamName());
        return temp3;
    }
    return left;
}


//global vars
League league;
Team playerTeam;
string team_name;
string team_location;
int team_seed;

//main
int main(int argc, char **argv) {
    string line;
    if (argc > 1) {
        ifstream input(argv[1]);
        if (!input.is_open()) {
            cout << "Problem opening file " << argv[1] << endl;
            return 1;
        }

        while (!input.eof()) {
            getline(input, line);
            Parser command(line);
            if (command.numArgs() == 2) {
            playerTeam.setName(command.getOperation());
            playerTeam.setLocation(command.getArg1());
            playerTeam.setSeed(stoi(command.getArg2()));
            league.addTeam(playerTeam);
            }
        }

       if ((league.getSizeOfTeams() & (league.getSizeOfTeams() - 1)) != 0) {
           cout << "File must include a number of teams that is a power of 2" << endl;
           cout << "(There are " << league.getSizeOfTeams() << " teams in file " << argv[1] << ")" << endl;
           return 1;
       }

        cout << "------------" << endl << "Tournament: " << endl << "------------" << endl;
        int bruh = league.tournament(league.getLeague(), 0, league.getSizeOfTeams() - 1);
        cout << "------------" << endl << "Winner: " << endl << "------------" << endl;
        league.getTeamAt(bruh).showTeam();
        cout << " is the winner!" << endl;
        cout << "------------" << endl << "Stats: " << endl << "------------" << endl;
        league.showLeague();

    }

    else {
        cout << "Missing command line argument (input filename)" << endl;
        return 1;
    }

    return 0;
}

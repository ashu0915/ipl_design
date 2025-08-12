#include <iostream>
#include <vector>
#include <unordered_map>
#include <math.h>

using namespace std;

class Players;
class Teams;
class Match;
class IPL;

class Players{
    friend class Teams;
    friend class IPL;
    friend class Match;
    private:
        string name;
        long long games_played=0, games_won=0, games_lost=0;
        long long runs_scored=0, runs_given=0, bowls_bowled=0, bowls_faced=0;
        long long wicket_taken=0;
    private:
        Players(string nam): name(nam){};

        void printPlayerDetails(){
            cout<<"================"<<endl;
            cout<<"Player Name: "<<name<<endl;
            cout<<"Runs Scored: "<<runs_scored<<endl;
            cout<<"Runs Given: "<<runs_given<<endl;
            cout<<"Bowls Bowled: "<<bowls_bowled<<endl;
            cout<<"Bowls Faced: "<<bowls_faced<<endl;
            cout<<"Wickets Taken: "<<wicket_taken<<endl;
            cout<<endl<<endl;
        }

        Players& operator+=(Players& p2)
        {
            this->games_played += p2.games_played;
            this->games_won += p2.games_won;
            this->games_lost += p2.games_lost;
            this->runs_scored += p2.runs_scored;
            this->runs_given += p2.runs_given;
            this->bowls_bowled += p2.bowls_bowled;
            this->bowls_faced += p2.bowls_faced;
            this->wicket_taken += p2.wicket_taken;
            return *this;
        }
    
    public:
        ~Players()=default;

};

class Teams{
    friend class Match;
    friend class IPL;
    private:
        string name;
        vector<Players*>players_list;
        long long games_played=0, games_won=0, games_lost=0;
        long long runs_scored=0, runs_given=0, bowls_bowled=0, bowls_faced=0;
        float Net_Run_Rate=0.00;

        Teams(string nam): name(nam){};

        void printTeamDetails(){
            cout<<"================"<<endl;
            cout<<"Team Name: "<<name<<endl;
            cout<<"Games Played: "<<games_played<<endl;
            cout<<"Games Won: "<<games_won<<endl;
            cout<<"Games Lost: "<<games_lost<<endl;
            cout<<"Runs Scored: "<<runs_scored<<endl;
            cout<<"Runs Given: "<<runs_given<<endl;
            cout<<"Bowls Bowled: "<<bowls_bowled<<endl;
            cout<<"Bowls Faced: "<<bowls_faced<<endl;
            cout<<"Net Run Rate: "<<Net_Run_Rate<<endl;
            cout<<endl<<endl;
        }
    public:
        ~Teams()
        {
            for(auto& it: players_list)
            {
                delete it;
            }
        }
};

class Match
{
    private:
        friend class IPL;
        Teams * team1;
        Teams * team2;
        vector<Players>team1_players;
        vector<Players>team2_players;
        long long team1_runs=0;
        long long team2_runs=0;
        string batting_team;
        string bowling_team;
        string winner;
        Match(Teams* team1, Teams* team2)
        {
            this->team1=team1;
            this->team2=team2;
            for(auto it: team1->players_list)
            {
                Players temp = Players(it->name);
                team1_players.push_back(temp);
            }
            for(auto it: team2->players_list)
            {
                Players temp = Players(it->name);
                team2_players.push_back(temp);
            }
        }

        int findNewBowler(int bowler)
        {
            int newBowler= bowler;
            while(newBowler==bowler)
            {
                newBowler= 0 + (rand() % (2-0+1));
            }
            return newBowler;
        }

        int nextRuns()
        {
            return -1 + (rand() % (6 - (-1) +1));
        }

        void commentry(int over, int ball, string str, string non_str, string bowler, long long runs)
        {
            cout<<"================"<<endl;
            cout<<"Total runs\t" <<"Over\t"<<"Striking Batsman\t"<<"Non Striking Batsman\t"<<"Bowler"<<endl;
            cout<<runs<<"\t\t"<<over<<"."<<ball<<"\t\t"<<str<<"\t\t"<<non_str<<"\t\t"<<bowler<<endl;
            cout<<"================"<<endl;
        }

        long long batting(vector<Players>&team1_players, vector<Players>&team2_players, Teams* team1, Teams* team2, long long prev_runs=0, int inning=1)
        {
            int i=1;
            int over=0;
            int striking_batsman=0;
            int non_striking_batsman=1;
            int bowler=0;
            long long runs=0;
            for(over=0;over<2;over++)
            {
                if(i==team1_players.size())break;
                for(int ball=1;ball<=6;ball++)
                {
                    team1->bowls_faced++;
                    team2->bowls_bowled++;
                    team2_players[bowler].bowls_bowled++;
                    int run = nextRuns();
                    team1_players[striking_batsman].bowls_faced++;
                    runs+=run;
                    team2_players[bowler].runs_given+=run;
                    team1_players[striking_batsman].runs_scored+=run;
                    if(run==-1)
                    {
                        team2_players[bowler].runs_given++;
                        team2_players[bowler].wicket_taken++;
                        team1_players[striking_batsman].runs_scored++;
                        runs++;
                        i++;
                        if(i==team1_players.size())
                        {
                            break;
                        }
                        striking_batsman=i;
                    }
                    else if(run%2==1){
                        int temp=striking_batsman;
                        striking_batsman=non_striking_batsman;
                        non_striking_batsman=temp;
                    }
                    commentry(over,ball,team1_players[striking_batsman].name,team1_players[non_striking_batsman].name,team2_players[bowler].name,runs);
                    if(inning==2 && runs>prev_runs)
                    {
                        break;
                    }
                }
                if(inning==2 && runs>prev_runs)
                {
                    break;
                }
                bowler=findNewBowler(bowler);
            }
            return runs;
        }

        void updateCareerDetailofPlayers()
        {
            int i=0;
            for(int j=0;j<team1->players_list.size();j++)
            {
                Players curr= team1_players[i];
                *team1->players_list[j] += curr;
                i++;
            }
            i=0;
            for(int j=0;j<team2->players_list.size();j++)
            {
                Players curr= team2_players[i];
                *team2->players_list[j] += curr;
                i++;
            }
        }

        void printInning(string inning, string team1_name, string team2_name)
        {
            cout<<"================"<<endl;
            cout<<"Inning Number\t" <<"Batting Team Name\t"<<"Bowling Team Name\t"<<endl;
            cout<<inning<<"\t\t"<<team1_name<<"\t\t"<<team2_name<<endl;
            cout<<"================"<<endl;
        }

        void playGame()
        {
            //inning one choose between team1 and team2 to bat first
            int toss = 1 + (rand() % (2));
            team1->games_played++;
            team2->games_played++;
            if(toss==1)
            {
                batting_team = team1->name;
                bowling_team = team2->name;
                //first inning
                printInning("1st", team1->name, team2->name);
                team1_runs = batting(team1_players,team2_players,team1,team2);
                //second inning
                printInning("2nd", team2->name, team1->name);
                team2_runs = batting(team2_players,team1_players,team2,team1, team1_runs, 2);
            }
            else{
                batting_team = team2->name;
                bowling_team = team1->name;
                //first inning
                printInning("1st", team2->name, team1->name);
                team2_runs = batting(team2_players,team1_players,team2,team1);
                //second inning
                printInning("2nd", team1->name, team2->name);
                team1_runs = batting(team1_players,team2_players,team1,team2, team2_runs, 2);
            }
            if(team1_runs>team2_runs)
            {
                team1->games_won++;
                winner = team1->name;
            }
            else
            {
                team2->games_won++;
                winner = team2->name;
            }
            team1->runs_scored+=team1_runs;
            team2->runs_scored+=team2_runs;
            team1->runs_given+=team2_runs;
            team2->runs_given+=team1_runs;
            team1->Net_Run_Rate = ((float)((float)((float)team1->runs_scored / (float)team1->bowls_faced) - (float)((float)team1->runs_given / (float)team1->bowls_bowled))*6.0);
            team2->Net_Run_Rate = ((float)((float)((float)team2->runs_scored / (float)team2->bowls_faced) - (float)((float)team2->runs_given / (float)team2->bowls_bowled))*6.0);
            updateCareerDetailofPlayers();
        }

        void printBattingPlayerStats(vector<Players>& players)
        {
            for(auto& player: players)
            {
                cout << player.name << "\t\t" << player.runs_scored << "\t\t" << player.bowls_faced << "\t\t" << (player.bowls_faced==0?0:player.runs_scored/player.bowls_faced*100) << endl;
            }
        }

        void printBowlingPlayerStats(vector<Players>& players)
        {
            for(auto& player: players)
            {
                cout << player.name << "\t\t" << player.bowls_bowled << "\t\t" << player.runs_given << "\t\t" << player.wicket_taken << endl;
            }
        }

        void printInningSummary(string batter, string bowling_team, int inning)
        {
            cout << "Inning " << inning <<" :" << endl;
            cout << "Batting Team: " << batter << endl<<endl;
            cout<<"Player's Name\t"<<"Runs made\t Balls Played\t Strike Rate"<<endl;
            if(batter == team1->name)
            {
                printBattingPlayerStats(team1_players);
                cout<<endl<<endl;
                cout<<"Player's Name\t"<<"Balls Bowled\t Runs Given\t Wickets Taken"<<endl;
                printBowlingPlayerStats(team2_players);
            }
            else
            {
                printBattingPlayerStats(team2_players);
                cout<<endl<<endl;
                cout<<"Player's Name\t"<<"Balls Bowled\t Runs Given\t Wickets Taken"<<endl;
                printBowlingPlayerStats(team1_players);
            }
        }

        void printMatchSummary()
        {
            cout<<endl<<endl;
            cout<<"#############################################"<<endl<<endl;
            printInningSummary(batting_team, bowling_team, 1);
            cout<<endl<<endl;
            printInningSummary(bowling_team, batting_team, 2);
            cout<<"#############################################"<<endl<<endl;
            cout << "Match Result: " << winner <<" won"<< endl;
            cout<<endl<<endl;
        }

    public:
        ~Match()
        {
            delete team1;
            delete team2;
        }
};

class IPL{
    private:
        vector<Teams*>all_teams;
        vector<Players*>all_players;
        unordered_map<int, Match*>match_details;
    public:
        IPL(){

        }
        void addTeam(string name)
        {
            Teams* newTeam= new Teams(name);
            all_teams.push_back(newTeam);
        }

        void addPlayer(string team, string player)
        {
            Players* newPlayer= new Players(player);
            Teams * temp;

            for(auto& it: all_teams)
            {
                if(it->name==team)
                {
                    temp=it;
                    break;
                }
            }

            temp->players_list.push_back(newPlayer);
            all_players.push_back(newPlayer);
        }

        void playMatch(int matchId, string team1, string team2)
        {
            Teams * t1, * t2;

            for(auto& it: all_teams)
            {
                if(it->name==team1)
                {
                    t1=it;
                }
                if(it->name==team2)
                {
                    t2=it;
                }
            }

            Match* newMatch= new Match(t1, t2);
            newMatch->playGame();
            match_details[matchId]=newMatch;
        }

        void printMatchDetails(int matchId)
        {
            Match* match = match_details[matchId];
            match->printMatchSummary();
        }

        void printTeamDetails()
        {
            for(auto& it: all_teams)
            {
                it->printTeamDetails();
            }
        }

        void printPlayerCareerDetails(){
            for(auto& it: all_players)
            {
                it->printPlayerDetails();
            }
        }

        ~IPL()
        {
            for(auto& it: all_teams)
            {
                delete it;
            }
            for(auto& it: all_players)
            {
                delete it;
            }
            for(auto& it: match_details)
            {
                delete it.second;
            }
        }
};

int main()
{
    IPL ipl;

    ipl.addTeam("RCB");
    ipl.addTeam("mi");
    ipl.addTeam("kkr");

    ipl.addPlayer("RCB", "Kohli1");
    ipl.addPlayer("RCB", "Kohli2");
    ipl.addPlayer("RCB", "Kohli3");
    ipl.addPlayer("mi", "Rohit1");
    ipl.addPlayer("mi", "Rohit2");
    ipl.addPlayer("mi", "Rohit3");

    ipl.printTeamDetails();
    ipl.playMatch(1,"RCB","mi");
    ipl.printMatchDetails(1);
    ipl.printTeamDetails();
    ipl.printPlayerCareerDetails();
}
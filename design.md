### Task:-
    1. Create an IPL game which is consistes of multiple teams.
    2. Each team has few players.
    3. Teams can play game among each other with certain rules.
    4. Design the post match report and commentry of the match.

### Classes:-
    1. IPL- Main Class to be initialized in the main.
    2. Players- Class to store the data of each player. It has friend classes IPL, Teams, Match.
    3. Teams- Class to store the data of the teams along with the players list in each team.
    4. Match- This class is designed to perform the game operation and print the match details.

### Contents:-
    - IPL:
        - An array of all the players.
        - An array of all the teams.
        - A hashed map with `match_id` mapped with a Map object.
        - addTeam()
        - addPlayer()
        - printTeamDetails()
        - printPlayerCareerDetails()
        - playMatch()
        - getMatchInformation()
    
    - Players:
        - Friend class Teams, IPL, Match. 
        - printDetails()

    - Teams:
        - An array of Players.
        - Friend class Match and IPL.
        - printDetails()

    - Match:
        - An array of team1 and team2 players.
        - Friend class IPL.
        - playGame()
        - updateCareerDetailofPlayers()

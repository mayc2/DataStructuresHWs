class Player
{
public:

	//CONSTRUCTORS
	Player(const std::string &pn, const std::string &tn) : player_name(pn), player_team(tn){
		goals=0;
		assists=0;
		penalties=0;
	}

	//ACCESSORS
	const std::string getName() {return player_name; }
	const std::string getTeam() { return player_team; }
	const int getGoals() { return goals; }
	const int getAssists() { return assists; }
	const int getPenalties() { return penalties; }

	//MODIFIERS
	void addGoals();
	void addAssists();
	void addPenalties();
	void addGoals(const int &g);
	void addAssists(const int &a);
	void addPenalties(const int &p);
	
	//MEMBER FUNCTIONS

private:
	const std::string player_name;
	const std::string player_team;
	int goals;
	int assists;
	int penalties;
};

bool operator< (const Player &p1, const Player &p2){
	return p1.getName() < p2.getName();
}
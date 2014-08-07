class Team
{
public:
	Team(const std::string &name) : team_name(name) {
		wins=0;
		losses=0;
		ties=0;
		win_percentage=0.0;
		goals=0;
		penalties=0;
		games_played=0;
	}

	//ACCESSORS
	const std::string getName() { return team_name; }
	int getWins() { return wins; }
	int getLosses() { return losses; }
	int getTies() { return ties; }
	int getGoals() { return goals; }
	int getPenalties() {return penalties; }
	int getGP() { return games_played; }
	float getWinPerc() { calc_win_perc(); }

	//MODIFIERS
	void addWins();
	void addLosses();
	void addTies();
	void addGoals();
	void addPenalties();
	void addGP();
	void addWins(const int &w);
	void addLosses(const int &l);
	void addTies(const int &t);
	void addGoals(const int &g);
	void addPenalties(const int &p);
	void addGP(const int &gp);
	float calc_win_perc();

	//MEMBER FUNCTIONS
	
private:
	const std::string team_name;
	int wins;
	int losses;
	int ties;
	float win_percentage;
	int goals;
	int penalties;
	int games_played;
};

bool operator< (const Team& t1, const Team& t2) {
	return t1.getName() < t2.getName();
}

bool operator= (const Team &t1){
	wins=t1.getWins();
	losses=t1.getLosses();
	ties=t1.getTies();
	win_percentage=t1.getWinPerc();
	goals=t1.getGoals();
	penalties=t1.getPenalties();
	games_played=t1.getGP();
}
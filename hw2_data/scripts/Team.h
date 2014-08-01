class Team
{
public:
	Team(const std::string &name) : team_name(name) {}
	~Team();

	//ACCESSORS

	//MODIFIERS

	//MEMBER FUNCTIONS
	
private:
	const std::string team_name
	int wins
	int loss
	int ties
	float win_percentage
	int goals
	int penalties
	int games_played
};
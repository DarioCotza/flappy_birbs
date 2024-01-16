#ifndef GA_HPP
#define GA_HPP
# include "Player.hpp"
# include <array>
# include <map>
# include "SimConfig.hpp"

class GA
{
private:
	SimConfig *config;
	int 	population_size;
	int	    elite_group_size;
	float 	mutation_rate;
	int 	dead_players_count;
	int 	generation_number;

	int 	target_fitness;
	int		best_fitness;

	std::vector<Player *> new_players;
	std::vector<Player *> dead_players;

	void _selection();
	void _crossover();
	void _mutation();

	void _print_players_dna();

public:

	std::vector<Player *> players;
	// std::vector<Player *> get_players() { return players; }
	int 	get_dead_players_count() { return dead_players_count; }
	void 	next_generation();
	void 	add_dead_player(Player *player);
	void 	save_run();
	int 	get_generation_number() { return generation_number; }
	int		get_best_fitness() { return best_fitness; }
	int 	get_current_fitness();
	GA(SimConfig *config);
	~GA();
};

#endif // GA_HPP
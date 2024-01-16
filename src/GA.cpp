#include "../include/GA.hpp"


void GA::next_generation()
{
	generation_number++;
	dead_players_count = 0;
	_selection(); //select elite group
	_crossover(); //crossover elite group
	_mutation(); //mutate new players
	players.clear();
	for (int i = 0; i < population_size; i++)
	{
		// std::cout << "pushing back new player" << std::endl;
		// std::cout << new_players[i] << std::endl;
		players.push_back(new_players[i]);
	}
	dead_players.clear(); //clear dead players
	new_players.clear(); //clear new players
	//init new players
}

GA::GA(SimConfig *config)
{
	srand(config->random_seed);
	population_size = config->population_size;
	mutation_rate = config->mutation_rate;
	elite_group_size = config->elite_group_share * population_size;
	target_fitness = config->target_fitness;

	best_fitness = 0;
	generation_number = 0;
	dead_players_count = 0;
	for (int i = 0; i < population_size; i++)
		players.push_back(new Player(config));
}

void GA::add_dead_player(Player *player)
{
	dead_players.push_back(player);
	dead_players_count++;
}

void GA::_selection()
{
	for (int i = population_size - 1; i >= population_size - elite_group_size; i--)
		new_players.push_back(dead_players[i]);
}

void GA::_crossover()
{
	int dna_size = new_players[0]->nn.dna.size();
	
	for (int i = population_size - elite_group_size - 1; i >= 0; i--)
		new_players.push_back(dead_players[i]);

	//select a random parent from elite group and choose a gene from it
	for (int i = elite_group_size; i < population_size; i++)
	{
		if (!elite_group_size)
			break;
		int random_parent = rand() % elite_group_size;
		int random_parent2 = rand() % elite_group_size;
		int split_point = rand() % dna_size;

		// new_players[i] = new Player();
		for (int j = 0; j < split_point; j++)
			*new_players[i]->nn.dna[j] = *new_players[random_parent]->nn.dna[j];
		for (int j = split_point; j < dna_size; j++)
			*new_players[i]->nn.dna[j] = *new_players[random_parent2]->nn.dna[j];
	}
}

void GA::_print_players_dna()
{
	for (int i = 0; i < population_size; i++)
	{
		std::cout << "player " << i << "\n";
		new_players[i]->nn.print_DNA();
	}

}

void GA::_mutation()
{
	int dna_size = new_players[0]->nn.dna.size();
	for (int i = elite_group_size; i < population_size; i++)
	{
		for (int j = 0; j < dna_size; j++)
		{
			if (rand() % 100 < mutation_rate * 100)
			{
				*new_players[i]->nn.dna[j] = rand() - RAND_MAX / 2;
			}
		}
	}
}

void GA::save_run()
{
	// const char *json;
	
}

int GA::get_current_fitness()
{
	std::vector<Player *>::iterator it;
	for (it = players.begin(); it != players.end(); it++)
		if (!(*it)->isDead())
			break;
	int curr_fitness = (*it)->getScore();
	if (best_fitness < curr_fitness)
		best_fitness = curr_fitness;
	return curr_fitness;
}

GA::~GA()
{
	std::vector<Player *>::iterator it;
	for (it = players.begin(); it != players.end(); it++)
		delete *it;
}


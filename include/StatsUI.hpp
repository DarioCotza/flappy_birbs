#ifndef STATS_UI_HPP
# define STATS_UI_HPP
# include "SimConfig.hpp"
# include "GA.hpp"
# include <SDL2/SDL_ttf.h>
# include "NN.hpp"

typedef struct t_game_info
{
	int			random_seed;
	int			generation_number;
	int 		population_alive;
	int			best_fitness;
	int 		current_fitness;
	int			elite_group_size;
	float		mutation_rate;
}				s_game_info;

class StatsUI
{
private:
	SimConfig 	*config;
	GA 			*ga;
	int 		font_size;
	TTF_Font	*font;
	SDL_Color	white;
	std::string text;

	SDL_Surface* 	surface;
	SDL_Texture* 	texture;
	SDL_Rect 		rect;
	t_game_info		game_info;

	void _update_text();
public:
	void	update(SDL_Renderer *ren);
	StatsUI(SimConfig *config, GA *ga);
	~StatsUI();
};


#endif // STATS_UI_HPP
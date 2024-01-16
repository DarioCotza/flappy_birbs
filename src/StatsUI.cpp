#include "../include/StatsUI.hpp"

void StatsUI::_update_text()
{
	text = " Generation: " + std::to_string(game_info.generation_number);
	text += "\n population: " + std::to_string(game_info.population_alive) + \
		" / " + std::to_string(config->population_size);
	text += "\n best fitness: " + std::to_string(game_info.best_fitness);
	text += "\n current fitness: " + std::to_string(game_info.current_fitness) + \
		" / " + std::to_string(config->target_fitness);
	text += "\n random seed: " + std::to_string(game_info.random_seed);
	text += "\n mutation rate: " + std::to_string(game_info.mutation_rate);
	text += "\n elite group size: " + std::to_string(game_info.elite_group_size);
}

StatsUI::StatsUI(SimConfig *config, GA *ga)
{
	this->config = config;
	this->ga = ga;
    TTF_Init();
	font_size = 14;
	font = TTF_OpenFont("./fonts/Roboto-Light.ttf", font_size);
	white = {255, 255, 255, 0};
	game_info.mutation_rate = config->mutation_rate;
	game_info.elite_group_size = config->elite_group_share * config->population_size;
}
void StatsUI::update(SDL_Renderer *ren)
{   
	game_info.generation_number = ga->get_generation_number();
	game_info.population_alive = config->population_size - ga->get_dead_players_count();
	game_info.current_fitness = ga->get_current_fitness();
	game_info.best_fitness = ga->get_best_fitness();
	_update_text();
	// SDL_FillRect(surface, NULL, 0x00000000);
	surface = TTF_RenderText_LCD_Wrapped(font, text.c_str(), white, {0, 0, 0, 222}, 200);
	
	texture = SDL_CreateTextureFromSurface(ren, surface);
	rect = {config->screen_width - surface->w, 0, surface->w, surface->h};
    SDL_RenderCopy(ren, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

StatsUI::~StatsUI()
{
	TTF_CloseFont(font);
	TTF_Quit();
}

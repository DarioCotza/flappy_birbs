#include "../include/GA.hpp"
#include "../include/Map.hpp"
#include "../include/StatsUI.hpp"
#include <SDL2/SDL_ttf.h>

void handle_input_events(bool *quit)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        // If user closes the window
        if (e.type == SDL_QUIT)
            exit(0);
        // If user presses any key
        if (e.type == SDL_KEYDOWN)
        {
            //when user presses escape
            if (e.key.keysym.sym == SDLK_ESCAPE)
                *quit = true;
        }
    }
}

void update_players(PipeObstacle *closest_pipe_obst, SDL_Renderer *ren, GA &ga, int population_size)
{
    bool rendered = false;
    for (int i = 0; i < population_size; i++)
    {
        if (ga.players[i]->isDead())
            continue;
        ga.players[i]->update(closest_pipe_obst);
        if (!rendered && !ga.players[i]->isDead())
        {
            ga.players[i]->render(ren, true);
            rendered = true;
        }
        else
            ga.players[i]->render(ren, false);
        ga.players[i]->setScore(ga.players[i]->getScore() + 1);
        if (ga.players[i]->isDead())
        {
            ga.add_dead_player(ga.players[i]);
        }
    }
}

void init_SDL_stuff(SimConfig &config, SDL_Window **win, SDL_Renderer **ren)
{
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
    {
        logSDLError(std::cout, "SDL_Init");
        exit(1);
    }
    *win = SDL_CreateWindow(
        "Artificial birbs", 0, 0, config.screen_width,
        config.screen_height, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
    if (*win == nullptr)
    {
        logSDLError(std::cout, "CreateWindow");
        SDL_Quit();
        exit(1);
    }
    *ren = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(*ren, 0, 0, 0, 255);
    if (*ren == nullptr)
    {
        SDL_DestroyWindow(*win);
        logSDLError(std::cout, "CreateRenderer");
        SDL_Quit();
        exit(1);
    }
}


int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		std::cout << "usage: ./sim <config_file>" << std::endl;
		return 1;
	}

    //parse and deserialize config file
	SimConfig config = SimConfig(argv[1]);

	GA ga = GA(&config);
    Map map(config);
    StatsUI stats_ui(&config, &ga);

    SDL_Window *win = nullptr;
    SDL_Renderer *ren = nullptr;

    init_SDL_stuff(config, &win, &ren);

    bool quit = false;
    while (!quit)
    {
		handle_input_events(&quit);
		SDL_RenderClear(ren);
        map.update_pipe_obstacles(ren);
        update_players(map.get_closest_pipe_obstacle(),
            ren, ga, config.population_size);
        // std::cout << ga.get_dead_players_count() << std::endl;
        if (ga.get_dead_players_count() == config.population_size)
        {
            // print_unique_score_occurrences(ga.new_players);
            ga.next_generation();
            //reset pipe obstacles
            map.reset();
            for (int i = 0; i < config.population_size; i++)
                ga.players[i]->reset();
        }
        stats_ui.update(ren);
		SDL_RenderPresent(ren);
	}
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
	return 0;
}


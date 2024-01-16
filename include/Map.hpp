#ifndef MAP_HPP
#define MAP_HPP

#include "PipeObstacle.hpp"
#include <SDL2/SDL.h>

class Map
{
private:
	int _screen_width;
	int _pipe_obst_count, _pipe_obst_distance, \
	    _player_pos_x, _closest_pipe_obst_idx;
	std::vector<PipeObstacle> pipe_obstacles;
	void _init_pipe_obstacles(SimConfig &config);
	
public:
	Map(SimConfig &config);
	~Map();
	void update_pipe_obstacles(SDL_Renderer *ren);
	PipeObstacle *get_closest_pipe_obstacle();
	void reset();
};



#endif
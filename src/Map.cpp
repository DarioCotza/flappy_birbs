#include "../include/Map.hpp"

void Map::_init_pipe_obstacles(SimConfig &config)
{ 
    for (int i = 0; i < _pipe_obst_count; i++)
        pipe_obstacles.push_back(
			PipeObstacle(config, _player_pos_x + (i + 1) * _pipe_obst_distance)
		);
}

Map::Map(SimConfig &config)
{
	std::cout << config.pipe_obstacle_gap_width << std::endl;
	_screen_width = config.screen_width;

	_player_pos_x = config.birb_pos_x;
	_closest_pipe_obst_idx = 0;
	_pipe_obst_count = \
		(config.screen_width / config.pipe_obstacle_distance) + 1;
	_pipe_obst_distance = config.screen_width / _pipe_obst_count;
	_init_pipe_obstacles(config);
}

void Map::update_pipe_obstacles(SDL_Renderer *ren)
{
	for (int i = 0; i < _pipe_obst_count; i++)
	{
		pipe_obstacles[i].update(_closest_pipe_obst_idx, _player_pos_x);
		if (_closest_pipe_obst_idx == _pipe_obst_count)
			_closest_pipe_obst_idx = 0;
		pipe_obstacles[i].render(ren);
	}
}

void Map::reset()
{
	_closest_pipe_obst_idx = 0;
	for (int i = 0; i < _pipe_obst_count; i++)
        pipe_obstacles[i].set_x(_player_pos_x + (i + 1) * _pipe_obst_distance);

}

PipeObstacle *Map::get_closest_pipe_obstacle()
{
	return &(pipe_obstacles[_closest_pipe_obst_idx]);
}

Map::~Map()
{
}
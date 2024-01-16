#ifndef __PIPE_OBSTACLE_H__
# define __PIPE_OBSTACLE_H__
# include <random>
# include "utils.hpp"
# include "SimConfig.hpp"

class PipeObstacle
{
private:
	int pos_x, pos_y;
	int vel_x;
	int gap_y;
	int gap_width, gap_height;
	int screen_height, screen_width;

	int gap_y_range;
	bool _player_already_passed;

	bool is_ren_init;
	std::array<SDL_Rect, 2> rects;
	void _reset_rects();
public:
	void render(SDL_Renderer *ren);
	void init_rects();
	void update(int &closest_pipe_obst_idx, int player_pos_x);
	// void reset();
	int getPosX();
	int getPosY();
	int getGapWidth();
	int getGapHeight();

	void increase_amplitude(int amount);

	void set_x(int x);
	void set_gap_height(int h);
	int	 get_gap_height();

	PipeObstacle();
	PipeObstacle(SimConfig &config, int pos_x);
	~PipeObstacle();
};


#endif
#ifndef __PLAYER_H__
#define __PLAYER_H__
# include "utils.hpp"
# include "PipeObstacle.hpp"
# include "NN.hpp"

class Player
{
private:
	SimConfig *config;
	int screen_width, screen_height;

	int 	pos_x, pos_y;
	int 	max_y;
	int		min_y;
	float 	vel_y;
	bool 	is_dead;
	uint32_t 	score;
	int 	input_size;

	SDL_Texture *tex;
	SDL_Rect tex_info;


	// void	_precompute_rotations();
	bool _check_collision(PipeObstacle *pipe_obst);
public:
	NN nn;
	void render(SDL_Renderer *ren, bool render_nn);
	void update(PipeObstacle *pipe_obst);
	void setVelY(float vel_y);
	float getVelY();
	void  reset();

	uint32_t 	getScore();
	void 		setScore(uint32_t score);
	bool		isDead();
	void		setAlive();
	void  		print_DNA();
	void		visualize_nn(SDL_Renderer *ren, int x, int y);
	Player(SimConfig *config);
	~Player();
};

#endif // !__PLAYER_H__
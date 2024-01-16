# include "../include/PipeObstacle.hpp"

int get_next_gap_position(int screen_height, int gap_height, int range)
{
	(void)range;
	(void)gap_height;
	// std::cout << "gap height " << gap_height << std::endl;

	//variation should be contained between min_y_pos and max_y_pos and range should control the variation from the center
	int y = rand() % (screen_height - gap_height) + gap_height ;
	return (y);

}

void PipeObstacle::set_x(int x)
{
	this->pos_x = x;
}

void PipeObstacle::set_gap_height(int h)
{
	this->gap_height = h;
}

int PipeObstacle::get_gap_height()
{
	return this->gap_height;
}


PipeObstacle::PipeObstacle(SimConfig &config, int pos_x)
{
	this->_player_already_passed = false;
	this->screen_width = config.screen_width;
	this->screen_height = config.screen_height;
	this->pos_x = pos_x;
	this->vel_x = -2; //3 is cool
	// std::cout << "gap width " << config.pipe_obstacle_gap_width << std::endl;

	this->gap_width = config.pipe_obstacle_gap_width;
	this->gap_height = config.pipe_obstacle_gap_height;
	this->is_ren_init = false;
	this->gap_y_range = 100;
	this->pos_y =  get_next_gap_position(screen_height, gap_height, gap_y_range);
}

PipeObstacle::PipeObstacle()
{
	this->screen_width = 640;
	this->screen_height = 480;
	this->pos_x = 640;
	this->vel_x = -2; //3 is cool
	this->gap_width = 60;
	this->gap_height = 200;
	this->is_ren_init = false;
	this->gap_y_range = 100;
	this->pos_y =  get_next_gap_position(480, gap_height, gap_y_range);
}

void PipeObstacle::init_rects()
{
	rects[0].x = pos_x;
	rects[0].y = 0;
	rects[0].w = gap_width;
	rects[0].h = pos_y - gap_height;

	rects[1].x = pos_x;
	rects[1].y = pos_y;
	rects[1].w = gap_width;
	rects[1].h = screen_height - pos_y;
}

void PipeObstacle::_reset_rects()
{
	rects[0].x = pos_x;
	rects[0].h = pos_y - gap_height;

	rects[1].x = pos_x;
	rects[1].y = pos_y;
	rects[1].h = screen_height - pos_y;
}

void PipeObstacle::update(int &closest_pipe_obst_idx, int player_pos_x)
{
	// std::cout << get_next_gap_position(SCREEN_HEIGHT, gap_width, 20) << std::endl;
	for (unsigned int i = 0; i < rects.size(); i++)
		pos_x += vel_x;
	if (pos_x + gap_width < player_pos_x && _player_already_passed == false)
	{
		// std::cout << "pos_x + gap_width: " << pos_x + gap_width << " player_pos_x: " << 
			// player_pos_x << std::endl;
		closest_pipe_obst_idx += 1;
		_player_already_passed = true;
	}

	if (pos_x < -gap_width)
	{
		pos_y = get_next_gap_position(screen_height, gap_height, gap_y_range);
		pos_x = screen_width;
		_player_already_passed = false;

		if (is_ren_init)
			_reset_rects();
	}
}

void PipeObstacle::render(SDL_Renderer *ren)
{
	if (this->is_ren_init == false)
	{
		this->rects = std::array<SDL_Rect, 2>();
		rects[0] = SDL_Rect();
		rects[1] = SDL_Rect();
		init_rects();
		this->is_ren_init = true;
		return ;
	}
	rects[0].x = pos_x;
	rects[1].x = pos_x;
		
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderFillRect(ren, &rects[0]);
	SDL_RenderFillRect(ren, &rects[1]);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
}

int PipeObstacle::getPosX()
{
	return this->pos_x;
}

int PipeObstacle::getPosY()
{
	return this->pos_y;
}

int PipeObstacle::getGapWidth()
{
	return this->gap_width;
}

int PipeObstacle::getGapHeight()
{
	return this->gap_height;
}

PipeObstacle::~PipeObstacle()
{
}
# include "../include/Player.hpp"

Player::Player(SimConfig *config)
{
	this->config = config;
	pos_x = config->birb_pos_x;
	pos_y = config->birb_pos_y;
	vel_y = 1;
	tex = nullptr;
	is_dead = false;
	score = 0;

	nn.init_nn(config->layers);
	input_size = config->layers[0];
}

void Player::render(SDL_Renderer *ren, bool render_nn)
{
	if (this->tex != nullptr)
	{
		renderTexture(tex, ren, pos_x, pos_y);
		if (render_nn)
			visualize_nn(ren, 680, 160);
		return;
	}
	SDL_Surface *bmp = SDL_LoadBMP(config->bird_image_path.c_str());
	if (bmp == nullptr)
    {
        // SDL_DestroyRenderer(ren);
        // SDL_DestroyWindow(win);
        logSDLError(std::cout, "invalid image: " + config->bird_image_path);
        SDL_Quit();
		return;
    }
	this->tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	if (tex == nullptr)
    {
        SDL_DestroyRenderer(ren);
        // SDL_DestroyWindow(win);
        logSDLError(std::cout, "CreateTextureFromSurface");
        SDL_Quit();
		return;
    }
	SDL_QueryTexture(tex, NULL, NULL, &tex_info.w, &tex_info.h);
}

bool Player::_check_collision(PipeObstacle *pipe_obst)
{
	//minor optimization
	if (pos_x + this->tex_info.w < pipe_obst->getPosX())
		return false;

	bool top_right_collision = pos_x + tex_info.w > pipe_obst->getPosX() && pos_x + tex_info.w < pipe_obst->getPosX() + pipe_obst->getGapWidth();
	bool top_left_collision = pos_x > pipe_obst->getPosX() && pos_x < pipe_obst->getPosX() + pipe_obst->getGapWidth();
	bool bottom_right_collision = pos_x + tex_info.w > pipe_obst->getPosX() && pos_x + tex_info.w < pipe_obst->getPosX() + pipe_obst->getGapWidth();
	bool bottom_left_collision = pos_x > pipe_obst->getPosX() && pos_x < pipe_obst->getPosX() + pipe_obst->getGapWidth();
	if ((top_right_collision || top_left_collision || bottom_right_collision || bottom_left_collision) &&
		(this->pos_y < pipe_obst->getPosY() - pipe_obst->getGapHeight() ||
		this->pos_y + tex_info.h > pipe_obst->getPosY()))
	{
		return true;
	}
	return false;

}

void Player::update(PipeObstacle *pipe_obst)
{
	RowVector input(input_size);

	this->pos_y += (int) this->vel_y;
	this->vel_y += config->gravity_acc;
	if (this->pos_y > config->screen_height - tex_info.h)
	{
		this->pos_y = config->screen_height - tex_info.h;
		this->vel_y = 0;
	} else if (this->pos_y < 0)
	{
		this->pos_y = 0;
		this->vel_y = 0;
	}

	float distance_from_pipe_gap_top = (float) (this->pos_y - pipe_obst->getPosY());
	float distance_from_pipe_gap_bottom = (float) \
		(this->pos_y + tex_info.h - pipe_obst->getPosY() + pipe_obst->getGapHeight());
	// float distance_from_pipe_x = (float) (pipe_obst->getPosX() - this->pos_x);
	input << vel_y, distance_from_pipe_gap_top, distance_from_pipe_gap_bottom;
	if (nn.predict(input))
		this->vel_y = -6;

	this->is_dead = _check_collision(pipe_obst);
}

void Player::setVelY(float vel_y)
{
	this->vel_y = vel_y;
}

float Player::getVelY()
{
	return this->vel_y;
}

Player::~Player()
{
	SDL_DestroyTexture(tex);
}

uint32_t Player::getScore()
{
	return this->score;
}

bool Player::isDead()
{
	return this->is_dead;
}

void Player::print_DNA()
{
	this->nn.print_DNA();
}

void Player::setAlive()
{
	this->is_dead = false;
	this->pos_y = 200;
	this->score = 0;
}

void Player::setScore(uint32_t score)
{
	this->score = score;
}

void Player::reset()
{
	this->pos_y = config->birb_pos_y;
	this->vel_y = 1;
	this->is_dead = false;
	this->score = 0;
}

static void draw_circle(SDL_Renderer *ren, int32_t centre_x, int32_t centre_y, int32_t radius)
{
   const int32_t diameter = (radius * 2);

   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(ren, centre_x + x, centre_y - y);
      SDL_RenderDrawPoint(ren, centre_x + x, centre_y + y);
      SDL_RenderDrawPoint(ren, centre_x - x, centre_y - y);
      SDL_RenderDrawPoint(ren, centre_x - x, centre_y + y);
      SDL_RenderDrawPoint(ren, centre_x + y, centre_y - x);
      SDL_RenderDrawPoint(ren, centre_x + y, centre_y + x);
      SDL_RenderDrawPoint(ren, centre_x - y, centre_y - x);
      SDL_RenderDrawPoint(ren, centre_x - y, centre_y + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}

void fill_circle(SDL_Renderer *ren, int32_t centre_x, int32_t centre_y, int32_t radius)
{
	const int32_t diameter = (radius * 2);

   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

   while (x >= y)
   {
	  SDL_RenderDrawLine(ren, centre_x - x, centre_y - y, centre_x + x, centre_y - y);
	  SDL_RenderDrawLine(ren, centre_x - x, centre_y + y, centre_x + x, centre_y + y);
	  SDL_RenderDrawLine(ren, centre_x - y, centre_y - x, centre_x + y, centre_y - x);
	  SDL_RenderDrawLine(ren, centre_x - y, centre_y + x, centre_x + y, centre_y + x);

	  if (error <= 0)
	  {
		 ++y;
		 error += ty;
		 ty += 2;
	  }

	  if (error > 0)
	  {
		 --x;
		 tx += 2;
		 error += (tx - diameter);
	  }
   }
}

void Player::visualize_nn(SDL_Renderer *ren, int x, int y)
{
	int node_radius = 8;
	int node_distance_x = 200;
	int node_distance_y = 20;
	int start_x = x + node_radius;
	int start_y = y + node_radius;

	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	//iterate weights
	int c = 0;
	for (RowVector node : nn.nodes)
	{
		int node_x = start_x + node_distance_x * c;
		for (int i = 0; i < node.size(); i++)
		{
			int node_y = start_y + node_distance_y * i;
			SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
			draw_circle(ren, node_x, node_y, node_radius);
			if (node(i) > .5)
				SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
			else
				SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
			fill_circle(ren, node_x, node_y, node_radius - 1);
			if (c != 0)
			{
				//iterate weights
				for (int j = 0; j < nn.nodes[c - 1].size(); j++)
				{
					int prev_node_x = start_x + node_distance_x * (c - 1);
					int prev_node_y = start_y + node_distance_y * j;
					//set the color based on the weight
					int weight = nn.weights[c - 1](i, j);
					if (weight > 0)
						SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
					else
						SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
					SDL_RenderDrawLine(ren, prev_node_x, prev_node_y, node_x, node_y);
				}
			}
		}
		c++;
	}
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
}
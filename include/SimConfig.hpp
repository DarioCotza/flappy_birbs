#ifndef SIM_HPP
#define SIM_HPP
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

class SimConfig
{
private:
	void _parse_config_file(std::string config_path);
	void _init_config();

	rapidjson::Document config_doc;

public:
	int 		screen_width;
	int 		screen_height;

	int 		random_seed;
	float 		gravity_acc;
	
	int 		birb_pos_x;
	int 		birb_pos_y;
	std::string bird_image_path;
	std::string name;

	int 		target_fitness;
	int 		population_size;
	float 		elite_group_share;
	float 		mutation_rate;

	int 		pipe_obstacle_gap_height;
	int 		pipe_obstacle_gap_width;
	int			pipe_obstacle_distance;

	int 		node_radius;
	int 		node_spacing_x;
	int 		node_spacing_y;

	std::vector<int> 		layers;

	SimConfig(std::string config_path);
	~SimConfig();
};

#endif // SIM_HPP
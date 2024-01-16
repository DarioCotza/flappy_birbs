#include "../include/SimConfig.hpp"
#include <SDL2/SDL_video.h>

SimConfig::SimConfig(std::string config_path)
{
	_parse_config_file(config_path);
	_init_config();
}

SimConfig::~SimConfig()
{
}

void SimConfig::_parse_config_file(std::string config_path)
{
	std::string config_file_contents;

	std::ifstream config_file(config_path);
	if (!config_file.is_open())
	{
		std::cout << "Error opening config file" << std::endl;
		exit(1);
	}
	std::string line;
	while (std::getline(config_file, line))
		config_file_contents += line;
	config_file.close();
	config_doc.Parse(config_file_contents.c_str());
	if (config_doc.HasParseError())
	{
		std::cout << "Error parsing config file" << std::endl;
		exit(1);
	}
}

void SimConfig::_init_config()
{
	std::string required_keys[] = {
		"screen_width", "screen_height", "birb_pos_x", "birb_pos_y",
		"birb_image_path", "random_seed", "layers",
		"target_fitness", "population_size", "elite_group_share",
		"mutation_rate", "pipe_obstacle_gap_height", "pipe_obstacle_gap_width",
		"pipe_obstacle_distance", "node_radius", "node_spacing_x", "node_spacing_y",
		"gravity_acc"
	};
	for (unsigned int i = 0; i < 8; i++)
	{
		if (!config_doc.HasMember(required_keys[i].c_str()))
		{
			std::cout << "Error: config file missing key: " << required_keys[i] << std::endl;
			exit(1);
		}
	}
	screen_width = config_doc["screen_width"].GetInt();
	screen_height = config_doc["screen_height"].GetInt();
	random_seed = config_doc["random_seed"].GetInt();
	gravity_acc = config_doc["gravity_acc"].GetFloat();
	birb_pos_x = config_doc["birb_pos_x"].GetInt();
	birb_pos_y = config_doc["birb_pos_y"].GetInt();
	bird_image_path = config_doc["birb_image_path"].GetString();

	target_fitness = config_doc["target_fitness"].GetInt();
	population_size = config_doc["population_size"].GetInt();
	elite_group_share = config_doc["elite_group_share"].GetFloat();
	mutation_rate = config_doc["mutation_rate"].GetFloat();
	pipe_obstacle_gap_height = config_doc["pipe_obstacle_gap_height"].GetInt();
	pipe_obstacle_gap_width = config_doc["pipe_obstacle_gap_width"].GetInt();
	pipe_obstacle_distance = config_doc["pipe_obstacle_distance"].GetInt();

	node_radius = config_doc["node_radius"].GetInt();
	node_spacing_x = config_doc["node_spacing_x"].GetInt();
	node_spacing_y = config_doc["node_spacing_y"].GetInt();

	// parse layers
	rapidjson::Value &layers = config_doc["layers"];
	this->layers = std::vector<int>(layers.Size());
	for (rapidjson::SizeType i = 0; i < layers.Size(); i++)
		this->layers[i] = layers[i].GetInt();

}

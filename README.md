# Evolving Neural Networks for Flappy Bird

This project is an attempt to implements a genetic algorithm to evolve neural networks with a fixed topology, aiming to teach an AI to play Flappy Bird. Over successive generations, the AI improves its gameplay by navigating through obstacles more effectively.

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
  - [Running the Simulation](#running-the-simulation)
  - [Configuration](#configuration)
- [Code Structure](#code-structure)

## Features

- Utilizes genetic algorithms to evolve neural networks.
- Fixed topology neural networks optimize gameplay strategy.
- Progressive improvement of AI's performance through generations.
- Simulation of Flappy Bird gameplay with AI-controlled birds.
- Visual representation of AI learning process using SDL2.

## Getting Started

### Prerequisites

Make sure you have the following installed:

- GCC compiler (or any C++ compiler)
- SDL2 library
- SDL2_ttf library

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/DarioCotza/flappy_birbs.git
   ```
2. Build the project:
    ```bash
    cd flappy_birbs
    make
    ```
## Usage
### Running the Simulation
To run the simulation, use the following command:
    ```bash
    ./sim <config_file>
    ```
### Configuration
The simulation requires a configuration file to set parameters such as population size, mutation rate, and more. Below is an example configuration file (config.json):

```json
{
	"screen_width" : 900,
	"screen_height" : 480,
	"random_seed" : 42,
	"gravity_acc" : 0.6,
	"birb_pos_x" : 30,
	"birb_pos_y" : 200,
	"birb_image_path" : "./images/birb.bmp",
	"layers" : [3, 1],
	"mutation_rate" : 0.1,
	"population_size" : 10000,
	"elite_group_share" : 0.1,
	"pipe_obstacle_gap_width" : 50,
	"pipe_obstacle_gap_height" :70,
	"pipe_obstacle_distance" : 400,
	"target_fitness" : 10000,
	"node_radius" : 8,
	"node_spacing_x" : 200,
	"node_spacing_y" : 20
}
```

## Code Structure
- src/GA.cpp: Contains the genetic algorithm implementation.
- src/Map.cpp: Manages the map and obstacles.
- src/Player.cpp: Represents the bird/player and its neural network.
- src/NN.cpp: Implements the neural network used by the birds.
- src/PipeObstacle.cpp: Manages the pipe obstacles.
- include/: Header files for the respective source files.

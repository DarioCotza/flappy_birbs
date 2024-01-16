all: main.o Player.o PipeObstacle.o NN.o utils.o GA.o SimConfig.o Map.o StatsUI.o
	c++ -O3 -o sim $^ -lSDL2 -lSDL2_ttf

#make object files
%.o: ./src/%.cpp
	c++ -O3 -Wall -Werror -Wextra -c -o $@ $< 

#make executable
re: fclean test

clean:
	rm -f *.o

fclean: clean
	rm -f sim

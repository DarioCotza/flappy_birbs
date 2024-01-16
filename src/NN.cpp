#include "../include/NN.hpp"

void print_nodes(std::vector<RowVector> nodes)
{
	std::cout << "Printing nodes" << std::endl;
	for (unsigned int i = 0; i < nodes.size(); i++)
		std::cout << nodes[i] << std::endl;
	std::cout << std::endl;
}

void print_weigths(std::vector<Matrix> weights)
{
	std::cout << "Printing weights" << std::endl;
	for (unsigned int i = 0; i < weights.size(); i++)
		std::cout << weights[i] << std::endl;
	std::cout << std::endl;
}

void NN::_encode_dna()
{
	//encode it in an array of pointer to floats for easy mutation
	for (unsigned int i = 0; i < weights.size(); i++)
	{
		for (int j = 0; j < weights[i].rows(); j++)
		{
			for (int k = 0; k < weights[i].cols(); k++)
				dna.push_back(&weights[i](j, k));
		}
	}
	// for (unsigned int i = 0; i < biases.size(); i++)
	// {
	// 	for (int j = 0; j < biases[i].size(); j++)
	// 		dna.push_back(&biases[i](j));
	// }
}

void NN::print_DNA()
{
	std::cout << "Printing dna" << std::endl;
	std::cout << "dna size: " << dna.size() << std::endl;
	for (unsigned int i = 0; i < dna.size(); i++)
		std::cout << *dna[i] << std::endl;
	print_weigths(weights);
	std::cout << std::endl;
}

void NN::init_nn(std::vector<int> layers)
{
	for (unsigned int i = 0; i < layers.size(); i++)
	{
		nodes.push_back(RowVector::Zero(layers[i]));

		if (i > 0)
			weights.push_back(Matrix::Random(layers[i], layers[i - 1]) * 10);
	}
	_encode_dna();
	//init dna with weights and biases
	
	// print_nodes(nodes);
	// print_weigths(weights);
	// print_dna(dna);
}

// float reLU(float x)
// {
// 	return x > 0 ? x : 0;
// }

bool NN::predict(RowVector& input)
{
	nodes[0] = input;

	for (unsigned int i = 1; i < nodes.size(); i++)
	{
		for (unsigned int j = 0; j < nodes[i].size(); j++)
		{
			nodes[i](j) = (nodes[i - 1] * weights[i - 1].transpose()).sum();
			nodes[i](j) = 1 / (1 + exp(-nodes[i](j)));
		}
	}
	return nodes[nodes.size() - 1](0) > 0.5;
}

NN::NN()
{
}

NN::~NN()
{
}

#ifndef __NN_H__
# define __NN_H__
# include "./Eigen/Dense"
# include <vector>
# include <iostream>

typedef Eigen::MatrixXf Matrix;
typedef Eigen::RowVectorXf RowVector;

class NN
{
private:
public:
	void	_encode_dna();
	NN();
	std::vector<RowVector>	nodes;
	std::vector<Matrix> 	weights;
	std::vector<RowVector> 	biases;
	std::vector<float *> 	dna;


	void 	init_nn(std::vector<int> layers);
	bool	predict(RowVector& input);
	void 	print_DNA();
	~NN();
};

#endif //__NN_H_
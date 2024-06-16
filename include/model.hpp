#ifndef __MODEL__HPP__
#define __MODEL__HPP__

#include <Eigen/Dense>
#include <iostream>

class Model{
public:
 Model(int inputnodes, int hiddennodes, int outputnodes, float learningrate);
 void train(std::vector<double> inputs_list, std::vector<double> targets_list);
 Eigen::MatrixXd forward(std::vector<double> inputs_list);
 Eigen::MatrixXd sigmoid(const Eigen::MatrixXd& x);
 Eigen::MatrixXd de_sigmoid(const Eigen::MatrixXd& x);

private:
    int inodes; // 输入节点个数
    int hnodes; // 隐藏层节点个数
    int onodes;  // 输出节点个数
    float lr;
    Eigen::MatrixXd wih; // 输入层和隐藏层权重
    Eigen::MatrixXd who; // 隐藏层和输出层权重
};


#endif  // __MODEL__HPP__
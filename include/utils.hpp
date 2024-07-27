#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include<iostream>
#include<random>
#include<cmath>
#include<Eigen/Dense>
#include<string>


std::optional<Eigen::MatrixXd> initialWeight(int rows, int cols, double mean, double stddev);
void printMatrixDimensions(std::string name, const Eigen::MatrixXd& matrix);

#endif
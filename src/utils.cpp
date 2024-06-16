#include<utils.hpp>
#include<string>
#include<logger.hpp>

std::optional<Eigen::MatrixXd> initialWeight(int rows, int cols, double mean, double stddev) {
    if (rows <= 0 || cols <= 0) return std::nullopt;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(mean, stddev);

    Eigen::MatrixXd matrix(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix(i, j) = d(gen);
        }
    }
    return matrix;
}

void printMatrixDimensions(std::string name, const Eigen::MatrixXd& matrix) {
    LOG("%s Matrix dimensions: %d x %d", name.c_str(), matrix.rows(), matrix.cols());
}
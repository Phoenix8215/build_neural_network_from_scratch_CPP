#include<iostream>
#include"model.hpp"
#include"utils.hpp"
#include"logger.hpp"


Model::Model(int inputnodes, int hiddennodes, int outputnodes, float learningrate)
    : inodes(inputnodes), hnodes(hiddennodes), onodes(outputnodes), lr(learningrate) {

        double stddev1 = std::pow(inodes, -0.5);
        double stddev2 = std::pow(hnodes, -0.5);

        // 初始化权重
        wih = initialWeight(hnodes, inodes, 0.0, stddev1);
        printMatrixDimensions("wih", wih);
        who = initialWeight(onodes, hnodes, 0.0, stddev2);
        printMatrixDimensions("who", who);
    }

void Model::train(std::vector<double> inputs_list, std::vector<double> targets_list) {
    Eigen::MatrixXd inputs = Eigen::Map<Eigen::MatrixXd>(inputs_list.data(), inodes, 1);
    Eigen::MatrixXd targets = Eigen::Map<Eigen::MatrixXd>(targets_list.data(), onodes, 1);
    // 计算隐藏层的输入信号
    Eigen::MatrixXd hidden_inputs = wih * inputs;
    // 计算隐藏层的输出信号
    Eigen::MatrixXd hidden_outputs = sigmoid(hidden_inputs);

    // 计算最终输出层的输入信号
    Eigen::MatrixXd final_inputs = who * hidden_outputs;
    // 计算最终输出层的输出信号
    Eigen::MatrixXd final_outputs = sigmoid(final_inputs);

    // 反向传播
    // 计算输出层误差（目标值减实际值）
    Eigen::MatrixXd output_errors = targets - final_outputs;
    double sum_error = output_errors.sum();

    LOG("output_errors = %f", sum_error);

    // 计算隐藏层误差
    Eigen::MatrixXd hidden_errors = who.transpose() * output_errors;

    // 更新隐藏层和输出层之间的权重
    who += lr * (output_errors.array() * final_outputs.array() * (1.0 - final_outputs.array())).matrix() * hidden_outputs.transpose();

    // 更新输入层和隐藏层之间的权重
    wih += lr * (hidden_errors.array() * hidden_outputs.array() * (1.0 - hidden_outputs.array())).matrix() * inputs.transpose();


}

Eigen::MatrixXd Model::forward(std::vector<double> inputs_list) {
    // 将输入转换为列向量
    Eigen::MatrixXd inputs = Eigen::Map<Eigen::MatrixXd>(inputs_list.data(), inodes, 1);
    printMatrixDimensions("inputs", inputs);
    Eigen::MatrixXd hidden_inputs = wih * inputs;
    printMatrixDimensions("hidden_inputs", hidden_inputs);

    Eigen::MatrixXd hidden_outputs = sigmoid(hidden_inputs);

    Eigen::MatrixXd final_inputs = who * hidden_outputs;
    Eigen::MatrixXd final_outputs = sigmoid(final_inputs);
    return final_outputs;
}

Eigen::MatrixXd Model::sigmoid(const Eigen::MatrixXd& x) {
    return 1.0 / (1.0 + (-x.array()).exp());
}

Eigen::MatrixXd de_sigmoid(const Eigen::MatrixXd& x) {
    return x.array() * (1.0 - x.array()); 
}

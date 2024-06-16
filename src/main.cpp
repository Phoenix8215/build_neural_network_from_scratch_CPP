#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include "logger.hpp"
#include "model.hpp"


std::vector<std::string> read_csv(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

std::vector<double> scale_and_shift_inputs(const std::vector<int>& input_values) {
    std::vector<double> inputs;
    std::transform(input_values.begin(), input_values.end(), std::back_inserter(inputs), [](int val) {
        return (val / 255.0 * 0.99) + 0.01;
    });
    return inputs;
}

int main() {
    logger::set_log_level(logger::LogLevel::Info);

    std::string filename = "mnist_dataset/mnist_train_100.csv";
    std::vector<std::string> training_data_list = read_csv(filename);

    int input_nodes = 784;
    int hidden_nodes = 200;
    int output_nodes = 10;

    float learning_rate = 0.1;
    Model model(input_nodes, hidden_nodes, output_nodes, learning_rate);
    int epochs = 100;

    for (int e = 0; e < epochs; ++e) {
        for (const std::string& record : training_data_list) {
            std::stringstream ss(record);
            std::string item;
            std::vector<int> all_values;

            while (std::getline(ss, item, ',')) {
                all_values.push_back(std::stoi(item));
            }

            std::vector<double> inputs = scale_and_shift_inputs(std::vector<int>(all_values.begin() + 1, all_values.end()));
            std::vector<double> targets(output_nodes, 0.01);
            targets[all_values[0]] = 0.99;
            model.train(inputs, targets);
        }
    }

    return 0;
}


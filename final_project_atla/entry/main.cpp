#include "Graph.hpp"

int main() {
    std::cout << "Hi" << std::endl;

    Graph g;
    auto vec = g.parseData("../data/soc-sign-bitcoinotc.csv");
    std::cout << "number of lines:" << vec.size() << std::endl;
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i][0] << " " << vec[i][1] << " " << vec[i][2] << " " << vec[i][3] << " " << std::endl;
    }
}
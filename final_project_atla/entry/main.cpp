#include "Graph.hpp"

bool validSCCGraph(std::map<int, std::vector<std::pair<int, int>>>& g) {
    for (auto pair : g) {
        if (pair.second.size() == 0) return false;
    }
    return true;
}

// struct sort_pair_second {
//     bool operator()(const std::pair<int,int> &left, const std::pair<int,int> &right) {
//         return left.second < right.second;
//     }
// };

void PrintFail(const std::string& command) {
  std::cout << "Usage: " << command
            << "\nWrong input format \n"
            << "Correct format: ./main [input file address]\n";
}

int main(int argc, char* argv[]) {
    
    if (argc != 2) {
        PrintFail(argv[0]);
        return 1;
    }

    // let user choose input file

    // std::string file = "../data/soc-sign-bitcoinotc.csv"
    std::cout << "Opening file " << "\"" << argv[1] << "\"" << std::endl;
    std::string file = argv[1];
    Graph g(file);
    auto graph = g.getGraph();

    // for (auto i : graph) {
    //     std::cout << i.first << " " << i.second.size() << std::endl;
    // }

    g.DFS();

    graph = g.getGraph();
    //std::map<int, std::vector<std::pair<int, int>>> graph_;

    // for (auto i : graph) {

    //     //if (i.first == 268 || i.first == 448 || i.first == 856 || i.first == 1743) {
    //     //for (unsigned int i = 0; i < graph.size(); i++) {
    //         std::cout  << "Vertex: " << i.first << " and neighbor weights: ";
    //         for (unsigned int j = 0; j < i.second.size(); j++) {
    //             std::cout << i.second.at(j).second << ", "
    //         }
    //         std::cout << std::endl;
    //     //}
    
    // }
    
    // std::cout << g.getNumVertices() << std::endl; 

    std::vector<std::set<int>> scc = g.getSCC();



    // Output for all SCCs
    // for (size_t i = 0; i < scc.size(); i++) {
    //     std::string output = "";
    //     for (int entry : scc.at(i)) {
    //         output += std::to_string(entry) + " ";
    //     }
    //     std::cout << "SCC " << i << ": " << output << std::endl;
    // }

    // std::cout << scc.size() << std::endl;

    // 1803 is from scc 0, the largest scc in the graph
    
    // output to output file

    int startPt;

    std::cout << "Please enter the user ID:" << std::endl;
    std::cin >> startPt;

    std::set<int> allUserID = g.getVertices();

    if (allUserID.find(startPt) == allUserID.end()) {

        std::cout << "This is not a valid user ID.\n";

    } else {

        int size_scc = g.getParentSCC(scc, startPt).size();
        auto sccGraph = g.getSCCGraph(scc, startPt);

        if (sccGraph.size() != 0 && validSCCGraph(sccGraph)) {

            std::ofstream myfile;
            myfile.open("../output.txt");

            auto dist = g.dijkstra(sccGraph, startPt);

            int boundary;

            std::cout << "Please enter the boundary for recommendation:" << std::endl;
            std::cin >> boundary;

            // std::cout << "Suggested user(s):\n";
            myfile << "Suggested user(s):\n";

            int countSuggested = 0;

            for (size_t i = 0; i < dist.size(); i++) {
                if (dist[i].second <= boundary) {
                    // std::cout << i.first << " ";
                    myfile << dist[i].first << std::endl;
                    countSuggested++;
                }
            }

            // if (countSuggested == 0) std::cout << "No user can be suggested.";
            if (countSuggested == 0) myfile << "No user can be suggested.";

            myfile.close();

        } else {
            std::cout << "This user is not in a valid strongly connected component, so there are no justified recommendations to give." << std::endl;
        }
    }

    return 0;
}
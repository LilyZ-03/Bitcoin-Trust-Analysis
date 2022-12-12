#include "Graph.hpp"

bool validSCCGraph(std::map<int, std::vector<std::pair<int, int>>>& g) {
    for (auto pair : g) {
        if (pair.second.size() == 0) return false;
    }
    return true;
}

void PrintFail(const std::string& command) {
  std::cout << "Usage: " << command
            << "\nWrong input format. \n"
            << "Correct format: ./main [input file address]\n"
            << "Optional input arguments: -a [algorithm keyword] -o [output file address] \n"
            << "available algorithm keywords: suggestion, scc\n"
            << "Optional arguments need to be in order.\n";
}

int main(int argc, char* argv[]) {

    std::string out_option = "-o";
    std::string algo_option = "-a";
    std::string command_scc = "scc";
    std::string command_sug = "suggestion";
    std::string outputFileAddress = "../output.txt";
    std::string inputFileAddress;
    bool default_algo = true;
    
    if (argc == 2) {
        inputFileAddress = argv[1];
    } else if (argc == 4 && (argv[2] == algo_option || argv[2] == out_option)) {
        inputFileAddress = argv[1];
        if (argv[2] == algo_option) {
            if (argv[3] == command_sug) {
                default_algo = true;
            } else if (argv[3] == command_scc) {
                default_algo = false;
            } else {
                PrintFail(argv[0]);
                return 1;
            }
        } else {
            outputFileAddress = argv[3];
        }
        
    } else if (argc == 6 && argv[2] == algo_option && argv[4] == out_option ) {
        inputFileAddress = argv[1];
        if (argv[3] == command_sug) {
            default_algo = true;
        } else if (argv[3] == command_scc) {
            default_algo = false;
        } else {
            PrintFail(argv[0]);
            return 1;
        }
        outputFileAddress = argv[5];
    }
    else {
        PrintFail(argv[0]);
        return 1;
    } 

    // let user choose input file

    std::cout << "Opening file " << "\"" << inputFileAddress << "\"" << std::endl;
    Graph g(inputFileAddress);
    auto graph = g.getGraph();

    g.DFS();

    graph = g.getGraph();
    
    std::cout << "Total number of users: " << g.getNumVertices() << std::endl; 

    std::vector<std::set<int>> scc = g.getSCC();

    // 1803 is from scc 0, the largest scc in the graph
    
    // output to output file

    if (!default_algo) {
        std::ofstream myfile;
        myfile.open(outputFileAddress);

        // Output for all SCCs
        if (scc.size() != 0) {
            myfile << "Strongly-Connected Components:\n";
            for (size_t i = 0; i < scc.size(); i++) {
                std::string output = "";
                for (int entry : scc.at(i)) {
                    output += std::to_string(entry) + " ";
                }
                myfile << "SCC " << i << ": " << output << "\n";
            }
        } else {
            myfile << "No Strongly-Connected Components exist.\n";
        }


        myfile.close();

    } else {

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
                myfile.open(outputFileAddress);

                auto dist = g.dijkstra(sccGraph, startPt);

                int boundary;

                std::cout << "Please enter the boundary for recommendation:" << std::endl;
                std::cin >> boundary;

                myfile << "Suggested user(s):\n";

                int countSuggested = 0;

                for (size_t i = 0; i < dist.size(); i++) {
                    if (dist[i].second <= boundary) {
                        myfile << dist[i].first << std::endl;
                        countSuggested++;
                    }
                }

                if (countSuggested == 0) myfile << "No user can be suggested.";

                myfile.close();

            } else {
                std::cout << "This user is not in a valid strongly connected component, so there are no justified recommendations to give." << std::endl;
            }
        }
    }

    return 0;
}
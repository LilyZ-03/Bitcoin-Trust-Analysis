#include "Graph.hpp"

bool validSCCGraph(std::map<int, std::vector<std::pair<int, int>>>& g) {
    for (auto pair : g) {
        if (pair.second.size() == 0) return false;
    }
    return true;
}

int main() {
    // std::cout << "Hi" << std::endl;

    // let user choose input file

    std::string file = "../data/soc-sign-bitcoinotc.csv";
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


    for (size_t i = 0; i < scc.size(); i++) {
        std::string output = "";
        for (int entry : scc.at(i)) {
            output += std::to_string(entry) + " ";
        }
        std::cout << "SCC " << i << ": " << output << std::endl;
    }

    // std::cout << scc.size() << std::endl;

    // 1803 is from scc 0, the largest scc in the graph
    
    // output to output file

    int startPt;

    std::ofstream myfile;
    myfile.open("../output.txt");

    std::cout << "Please enter the user ID:" << std::endl;
    std::cin >> startPt;

    std::set<int> allUserID = g.getVertices();

    if (allUserID.find(startPt) == allUserID.end()) {

        std::cout << "This is not a valid user ID.\n";
        // myfile << "This is not a valid user ID.\n";

    } else {

        int size_scc = g.getParentSCC(scc, startPt).size();
        auto sccGraph = g.getSCCGraph(scc, startPt);

        if (sccGraph.size() != 0 && validSCCGraph(sccGraph)) {

            // for (auto i : sccGraph) {
            //     std::cout << "ID: " << i.first << " weights: ";
            //     for (unsigned int j = 0; j < i.second.size(); j++) 
            //         std::cout << i.second.at(j).second << ", ";
            //     std::cout << std::endl;
            // }

            auto dist = g.dijkstra(sccGraph, startPt);

            int boundary;

            std::cout << "Please enter the boundary for recommendation:" << std::endl;
            std::cin >> boundary;

            // std::cout << "Suggested user(s):\n";
            myfile << "Suggested user(s) for user " << startPt << " with boundary " << boundary << ":\n";

            int countSuggested = 0;

            for (auto i : dist) {
                if (i.second <= boundary) {
                    // std::cout << i.first << " ";
                    myfile << i.first << std::endl;
                    countSuggested++;
                }
            }

            // if (countSuggested == 0) std::cout << "No user can be suggested.";
            if (countSuggested == 0) myfile << "No user can be suggested.";

            // std::cout << std::endl;

        } else {
            std::cout << "This user is not in a valid strongly connected component, so there are no justified recommendations to give." << std::endl;
        }
    }

    myfile.close();

    // auto e = sccGraph.at(startPt);
    // for (auto p : e) {
    //     std::cout << p.first << ":" << p.second << std::endl;
    // }


    // for (size_t i = 0; i < vec.size(); i++) {
    //     std::cout << vec[i][0] << " " << vec[i][1] << " " << vec[i][2] << " " << vec[i][3] << " " << std::endl;
    // }
}
## Leading Question 
Our leading question is “How closely related and trustworthy are two Bitcoin users on Bitcoin OTC?” Our goal is to identify existing relationships between Bitcoin users and determine how trustworthy each user is. Based on this information, we can recommend equally trustworthy Bitcoin users to new consumers. We plan to use the [Bitcoin OTC trust weighted signed network dataset] (http://snap.stanford.edu/data/soc-sign-bitcoin-otc.html). It contains data of edges that show the “trust relationships” between users. Trust has been determined by members of Bitcoin OTC, who rated other members on a scale from -10 (total distrust) to +10 (total trust).
We aim to traverse the graph using DFS to disconnect edges between vertices that are negative or not weighted high enough, since we are only interested in trust networks between users rather than the quality of the users. We will define “strongly related” by a total trust higher or equal to 3; if the edge is weighted higher or equal to 3, then we will consider it strongly related. After traversing the graph and disconnecting weak edges, we will run Tarjan’s strongly connected components algorithm to search for strongly connected components. The result of this process is that users within the same strongly connected component will make up a trustworthy community.
Also, we will aim to find the shortest path between two given users using Djikstra’s algorithm. The shortest path length between two users indicates how closely related these two users are. If the shortest path length between them exists and is less than or equal to a certain threshold, we can say these users are in the same trustworthy bitcoin trading community and they are closely related. Since the size of the dataset is not too large, we can try different numbers for the thresholds and adjust them based on the results.

## Dataset Acquisition & Processing
### Data Format
Our dataset from SNAP is a CSV file containing the users as the nodes, and the amount of trust between users as the weighted, directed edges. Our dataset has 5,881 nodes and 35,592 edges. We only plan to use the nodes and edges data, and we will ignore all extraneous negatively weighted data.

### Data Correction
The input data does not seem to have any empty entries, but the description of the dataset does not clarify whether this is true. Therefore, we will still check whether there are any empty rows present in the CSV file. While we are parsing the data using std::getline, we can check if the line is empty. If it is empty, we will not use the data point. To make sure we are parsing the data correctly, we will confirm that the amount of data we obtain is equivalent to the size of the dataset stated on the website. This can be done by checking that the data structure we use (a map) is the correct size. We will also check whether all the edges present in the graph are weighted within the range of [-10, 10], as defined by the dataset. This can be done with a simple if statement. The data that is for negative edges is extraneous for our leading question, so we will check if the weight of each edge is 0 and above. This way, we can ensure that only relevant data is contained within our data structure.

### Data Storage
Using an adjacency list
- Use a map to store the graph when first processing input csv
    - `std::map<int, std::vector<std::pair<int, int>>>`
    - User id (vertex) is stored as an int value; the vector stores the edges connected to the current vertex in pairs: <user id of the other user, weight of edge>
    - The storage cost for this data structure will be O(|V|+|E|)
    <br/>
- Use another map to store vertices and their edges after disconnecting “weakly related” edges
    - `std::map<int, std::vector<int>>`
    - User id (vertex) is stored as an `int` value; the vector stores the users (vertices) connected to the current user(current vertex)
    - The storage cost for this data structure will be O(|V|+|E|)
    
## Graph Algorithms
### Function Inputs 
We’re using an adjacency list to convert our data into a directed graph, which is an appropriate input for all 3 of our algorithms. 

### Function Outputs 
For DFS, we will have no output, as its purpose is to traverse and edit our data. For Tarjan’s algorithm, we would want to output a vector of sets, where each set is all the user IDs that make up one connected component. For Djikstra’s Shortest Path algorithm, we’ll be outputting the shortest path. We will print the output from Tarjan’s algorithm in the command line(printing the user IDs in the same strongly connected component together and separating the different strongly connected components with curly brackets).

### Function Efficiency
*DFS Traversal*
  - Time: 
    - O(V + E) worst-case runtime (our target)
    - O(V) best-case runtime
  - Memory: 
    - O(bm) where the length of the longest path = m and b is the number of extra nodes you need to store for each of the m nodes.
    
*Tarjan’s Strongly Connected Components*
  - Time: 
    - O(|V|+|E|) worst-case runtime (target)
  - Memory: 
    - O(|V| * (2 + 5w)) where w is the machine word size
    
*Dijkstra Shortest Path*
  - Time: 
    - O(V*log V + E) (target)
  - Memory: 
    - O(V) using priority queue (target)


## Timeline
| Week  | Planned Tasks                                                      |
|--------------------------|-------------------------------------------------------------------------------------------------|
| Week 1 (Oct 31 - Nov 4)  | Project Proposal & Planning, Team Contract                                                      |
| Week 2 (Nov 7 - 11)      | Finish the algorithm to process the dataset (parse the data and store it in our data structure) |
| Week 3 (Nov 14 - 18)     | Start working on the 3 algorithms (DFS, Djikstra, Tarjan’s) separately                          |
| Week 4 (Nov 27 - Dec 3)  | Finish the 3 algorithms, put them together and produce our final analysis of the data.          |
| Week 5 (Dec 5 - 7)       | Make project video + update README                                                              |

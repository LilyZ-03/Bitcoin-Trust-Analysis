# Development Log (Date: 11/28/2022 -- 12/2/2022)

## Weekly Goals
This week, our plan was to finish Tarjan’s algorithm to find strongly connected components within our graph so we could determine relationship networks between sellers. We also wanted to finish making unit tests for Tarjan’s algorithm.

## Specific Tasks Completed (and by who)
We relied on VS Code Live Share and all (Trisha, Anjana, Anagha, Lily) collaborated on writing Tarjan’s algorithm as well as the unit tests for the algorithm. Additionally, based on feedback from our mentor during the mid-project check-in, we wrote a unit test for the constructor based on a small CSV and tested whether the graph described the connections between vertices properly.

## Problems Encountered 
We encountered a problem when Tarjan’s algorithm was giving us an out of bounds error because we initialized the two vectors for Tarjan’s based on the number of vertices in the adjacency list. However, since we were using the indices of the vectors to access the status of each vertex and some User IDs were missing from 1 to 6005 in the data, we corrected this problem by initializing the vectors using the max User ID value as the number of elements that should be pushed into the vector.

## Plans for next week
We plan to finish Dijkstra’s algorithm, complete all unit tests for the project, and film the presentation video.

## Optional: Questions for mentor
N/A

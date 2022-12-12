# CS 225 Final Project
#### *Developed by **Team Atla**, CS225 Fall 2022*
#### Lily Z. (shuxing3), Anjana G. (anjanag3), Trisha C. (trishac2), Anagha S. (anaghas2) 
- - -
## Table of Contents
1. [Organization](#organization)
2. [Setup & Running Instructions](#setup--running-instructions)
3. [Tests](#tests)
4. [Results](#results)
- - -
## Organization
- [Results / Final Report](https://github.com/trishacho/cs225-finalproject-atla/blob/main/Documentation/results.md)
- [Presentation Video](https://illinois.zoom.us/rec/play/uLt5crYYIYsWwYwacecyYeYFQ63mj0yeVdUE0cCi_bRJApU5agiPb7pOiEPKLOyrPUpGo6Fvb3KOtrN6.gOlPTW_XtGHRPryV?continueMode=true&_x_zm_rtaid=D5T4zKyWQN6tl1yVks7esg.1670643977688.5a34bcd22734df256e3397b56fd68597&_x_zm_rhtaid=513)
- [Github Repository](https://github.com/trishacho/cs225-finalproject-atla)
  - Documentation (Project Proposal, Team Contract, Development Logs): [`/documentation`](https://github.com/trishacho/cs225-finalproject-atla/tree/main/Documentation)
  - Code: [`/final_project_atla/src`](https://github.com/trishacho/cs225-finalproject-atla/tree/main/final_project_atla/src)
  - Entry: [`/final_project_atla/entry`](https://github.com/trishacho/cs225-finalproject-atla/tree/main/final_project_atla/entry)
  - Results: [`/final_project_atla/results.md`](https://github.com/trishacho/cs225-finalproject-atla/blob/main/final_project_atla/output.txt)
  - Output File: Output depends on user input; by default, output files will be nested under [`/final_project_atla`](https://github.com/trishacho/cs225-finalproject-atla/tree/main/final_project_atla).
  - Tests: [`/final_project_atla/tests`](https://github.com/trishacho/cs225-finalproject-atla/tree/main/final_project_atla/tests)
  - Data:
    - [`/final_project_atla/data`](https://github.com/trishacho/cs225-finalproject-atla/tree/main/final_project_atla/data)
    - [External Source: Bitcoin OTC Trust Weighted Signed Network Dataset](http://snap.stanford.edu/data/soc-sign-bitcoin-otc.html)
 
## Setup & Running Instructions
Ensure that the Docker application is running and that the directory containing the CS225 Dockerfile has been opened in the dev container.

Once in the directory containing the CS225 Dockerfile, clone this [repository](https://github.com/trishacho/cs225-finalproject-atla) or pull a zip file of the repository to your local machine.

When the `cs225-finalproject-atla` directory is open, run the following commands in the terminal to create the `build` directory and run CMake.

```bash
cd final_project_atla
mkdir build
cd build
cmake ..
```

Note that when building and running executables, you must be in the `build` directory:
```bash
cd build
```

#### **To build the executable, use the command:**
```bash
make
```
#### **To run the executable for `main` with default arguments, use the command:**
```
./main
```
Upon running `./main`, **DFS** runs to remove the edges that are weighted equal to or below the selected bound (the default is defined as 2). Additionally, **Tarjan’s algorithm** runs to determine strongly connected components or “trust networks” between users.
 
Then the program will ask the user to enter a User ID and a boundary of recommendation, which is the maximum possible length of the shortest path between the user and any given seller.
 
Once this input is received: **Dijkstra's algorithm** runs to filter the strongly connected component and determine sellers strongly related to the user within a boundary of recommendation. Any seller whose path to the user is longer than this bound would not be an appropriate recommendation according to the user’s preference. Upon successful completion of this double filter, the program outputs a list of all sellers that are the most strongly related to the user in a file titled `output.txt` under `final_project_atla` (refer to the [Organization](#organization) section for a link to the exact physical location).
 
#### **To run the executable for main with a dataset other than the default Bitcoin OTC data, use the command:**
```bash
./main [input file address]
```
where `[input file address]` is replaced with the file path of the desired CSV file.
 
This will run `main` as described [above](#to-run-the-executable-for-main-with-default-arguments-use-the-command) on the inputted dataset.

#### **To run the executable for main and provide a file to collect output, use the command:**
```bash
./main [input file address] -o [output file address]
```
where `[input file address]` is replaced with the file path of the desired CSV file and `[output file address]` is replaced with the desired file path of the output file (any name).
 
This will run `main` as described [above](#to-run-the-executable-for-main-with-default-arguments-use-the-command) on the inputted dataset.

./main [input file address] -o [output file address]

#### **To run the executable for main with a specific algorithm request:**
```bash
./main [input file address] -a [algorithm keyword] -o [output file address]
```
where `[input file address]` is replaced with the file path of the desired CSV file, `[output file address]` is replaced with the desired file path of the output file (any name), and `[algorithm keyword]` is replaced with one of the following:

`scc` <br/>
This will output a list of all user IDs with their strongly connected users (users with similar trust levels).

`suggestion` <br/>
This is the default if no keyword is specified and will output a list of suggested users once a user ID and boundary of recommendation are inputted (the terminal will prompt input after the command is run).

- - -
Note that for any format of the `./main` command, the `-a` and `-o` flags are optional.

**Summary:** <br/>
`./main`

`./main [input file address]`

`./main [input file address] -a [algorithm keyword] -o [output file address]`

**Defaults:** <br/>
- *Algorithm:* suggested users algorithm <br/>
- *Input:* Bitcoin OTC dataset <br/>
- *Output:* `../output.txt`
- - -

 
## Tests
All tests are located in the file `test.cpp` under the `tests` directory, which is under `final_project_atla` (refer to the [Organization](#organization) section for a link to the exact physical location). To build the tests, use the command:
```bash
make test
```
To run the executable for the tests, use the command:
```bash
./test
```
The unit tests cover all parts of the code, including the construction of the graph structure after the data parsing, validation, and cleaning; and the main algorithms (Depth First Search (DFS) Traversal, Tarjan’s Algorithm for Strongly Connected Components, and Djikstra’s Algorithm).
 
The graph construction is tested using both a small CSV file and the Bitcoin OTC dataset. These tests verify that the graph was built properly from cleaned data by checking connections in the graph structure against an expected graph. 
 
The algorithms are tested with 1) small dummy graphs, 2) subsets of the dataset, and 3) the full dataset. 
- The DFS tests check that all edges with weights equal to or below the bound (defined as 2) are removed and that all remaining edges have a weight above the bound. 
- The Tarjan’s tests certify that the returned strongly connected components are the same as the components determined manually. 
- The Djikstra’s tests verify that the output consists of the intended shortest paths (determined manually) between two users with similar levels of trust.
 
## Results
A detailed summary of results can be found [here](https://github.com/trishacho/cs225-finalproject-atla/tree/main/Documentation/results.md).

# Implementation-of-OSPF-Link-State-LS-Algorithm
This project implements OSPF link-state (LS) routing algorithm for a given set of nodes (routers). The nodes are represented by lower case letters (a - z). The project then outputs the shortest path cost and path taken for each node when a source node is given. So, the program will ask for the number of routers in a network, the letter representing the first node, and the source node letter. The nodes other than the first node are represented the consecutive letters in the alphabet. For example, if there are 5 routers and the first node is d then, the 2nd, 3rd, 4th, and 5th routers will be represented using the letters e, f, g, and h respectively. The program will also ask for a cost matrix which contains the cost of each link between nodes. The cost of each link is a positive value greater than 1. If there is a 0 in the cost matrix then it means that the same node has zero cost to reach that node. If there is a -1 in the cost matrix that means no direct path between the two nodes. The LS algorithm utilizes Dijkstra algorithm to find shortest path between nodes. It also maintains a simple routing table to store these information. A sample cost matrix is given below.

![cost_matrix](https://user-images.githubusercontent.com/3108754/148311641-69a7d0e5-a638-4051-a087-1c919a2bac64.JPG)

A sample output of the project is given below.

![sample_output1](https://user-images.githubusercontent.com/3108754/148311656-4994b7a2-8545-41c3-835f-9f88ba61c00e.JPG)
![sample_output2](https://user-images.githubusercontent.com/3108754/148311660-673f73d6-10c1-4708-8adf-244b6711b14f.JPG)


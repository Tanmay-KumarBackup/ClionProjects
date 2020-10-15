# ClionProjects
this repository will have all C programming files

there is only main file in which i am trying to create a multidimensional knapsack, 
in multidimensional knapsack is a (0/1)knapsack form but with more than 1 bag of different weight

so the algorithm is designed in such a way that the algorithm will select the bag and try to put the most optimized values inside it.

input:
the total number of valuables <int numValuables>

the total number of bags <int numBag>

the data of valuables <int Cost>  <int Weight>

the weight of bags <int weightBags>

output:
selects the largest bag first

gives the array of expected selection set of valuables

selects the most optimized selection of valables

returns the maximum cost that could be fetched from that respected bag

removes the valuables that are already been selected from the the valuablesArray

continues the loop to give output of second largest bag and so on..

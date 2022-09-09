## Optimize Postman Route

This was made as simple course project, in the 4th semester. Here is the problem: 
`Guide a postman who has N letters, to deliver all his letters by covering minimum distance.`
Formally, we have graph, and we need to visit a specific set of nodes, such that covered distance is minimum.

## How does it find?
I had two days left, so it is a _bruteforce_ approach, infact, everything is bruteforeced here.
All hard work is done by procedure `PDO` in `route_optimizer.c`, which is more like a `Depth First Search`, except that it has lot more freedom.
It can visit a node more than once. It assigns a __unique__ integer to every node it visits.
Only restriction it has is, it cannot go to a nieghbouring node which has higher value than the current node. This restriction is necessary
otherwise, it might get stuck in an infinite loop. By doing so, it can trace out any kind of complicated path. It finds all possible paths
and picks best one.

```
// "//" are used to explain input, don't put double slashes in input

11 // number of nodes in the graph
1  a b   // denotes: a bidiractional edge between a and b with weight = 1 units, a <--> b
4  a c   
2  b d   
4  c b   
8  d i   
7  i j   
5  j k   
10 k h   
3  h g   
2  g f   
7  f e   
9  g e   
6  e h   
4  e d   
6  d h   
1  h i   
done // to tell that stop readig edges

i // node denoting post office

// k, f, h, a and e denotes destinations or set of nodes to be visited
// rust, zig, jai, go and Ocaml denotes to whom letter was written
// 1, 1, 3, 3 and 4 denotes stamp

k rust 1
f zig  1
h jai  3
a go   3
e Ocaml 4

-1 -1 -1 // stop reading letters

// postman's name
zoro
luffy

-1
```
The above input denotes below graph

![graph](https://user-images.githubusercontent.com/60176567/189392905-56e50606-10e3-4ba4-9922-261d13741122.png)

### Output


    luffy will deliver through : i -> h -> e -> h -> k -> h -> i 
    distance needs to be travelled is 34 Units
    letters to be delivered are : 
                                      h jai 3 
                                      e Ocaml 4 
                                      k rust 1 

    zoro will deliver through : i -> h -> d -> b -> a -> b -> d -> h -> g -> f -> g -> h -> i 
    distance needs to be travelled is 30 Units
    letters to be delivered are : 
                                      f zig 1 
                                      a go 3 


## How to run?

Run following commands!

```
make compile
```
```
make run
```

#ifndef flood_hpp
#define flood_hpp

#include "sensor.hpp"
#include <queue>

using namespace std;

/* Maze Characteristics*/
#define SIZE 12
#define MAXVAL 254

/* Directions*/
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

/* Starting Values */
#define START_X 0
#define START_Y 0

/* Goal Values */
#define END_X 10
#define END_Y 10

typedef struct Agent {
    /* Current info for the micromouse agent */
    short heading;
    short row;
    short column;
} Agent;

typedef struct Node {

    /* data for each node */
    short floodval;
    short row;
    short column;
    bool visited;

    /* Pointers to neighboring Nodes */
    struct Node *left;
    struct Node *right;
    struct Node *up;
    struct Node *down;

} Node;

typedef struct Maze {
    Node *map[SIZE][SIZE];
} Maze;

/* Makes a new agent character for traversing the maze */
Agent *new_Agent() {
  Agent *current_agent;
  current_agent = (Agent *)malloc(sizeof(Agent));

  current_agent->heading = NORTH;
  current_agent->column = START_X;
  current_agent->row = START_Y;

  return current_agent;
}

/* Node functions */
Node *new_Node(const short x, const short y) {
    Node *current_node;

    current_node = (Node *)malloc(sizeof(Node));

    short goal_x = END_X;
    short goal_y = END_Y;

    current_node->row = y;
    current_node->column = x;
    current_node->visited = false;

    /* Init floodval at Coord */
    current_node->floodval = abs(current_node->column - goal_x) + abs(current_node->row - goal_y);

    return current_node;
}

/* Maze Functions */
Maze *new_Maze() {
    Maze *current_maze;
    short x, y;

    current_maze = (Maze *)malloc(sizeof(Maze));
    for (x=0;x<SIZE;++x){
        for(y=0;y<SIZE;++y) {
            current_maze->map[x][y] = new_Node(x,y);
        }
    }

    for (x=0; x < SIZE; ++x){
        for(y=0; y < SIZE; ++y){
            current_maze->map[x][y]->up = (y == SIZE-1) ? NULL : (current_maze->map[x][y+1]);
            current_maze->map[x][y]->down = (y == 0) ? NULL : (current_maze->map[x][y-1]);
            current_maze->map[x][y]->left = (x == 0) ? NULL : (current_maze->map[x-1][y]);
            current_maze->map[x][y]->right = (x == SIZE-1) ? NULL : (current_maze->map[x+1][y]);
        }
    }
    return current_maze;
}


/*Check for the lowest floodval in the adjacent 4 nodes, returns the value and the direction it comes from.*/
short get_sm_neighbor(Node * current_node){
    short sm_neighbor = MAXVAL;
    short direction;
    // Check up
      if (current_node->up != NULL && (current_node->up->down != NULL) && (current_node->up->floodval) < sm_neighbor) {
        sm_neighbor = current_node->up->floodval;
        direction = NORTH;
      }
    // Check down
      else if (current_node->down != NULL && (current_node->down->up != NULL) && (current_node->down->floodval) < sm_neighbor) {
        sm_neighbor = current_node->down->floodval;
        direction = SOUTH;
      }
    // Check left
      else if (current_node->left != NULL && (current_node->left->right != NULL) && (current_node->left->floodval) < sm_neighbor) {
        sm_neighbor = current_node->left->floodval;
        direction = WEST;
      }
    // Check right
      else if (current_node->right != NULL && (current_node->right->left != NULL) && (current_node->left->floodval) < sm_neighbor){
        sm_neighbor = current_node->right->floodval;
        direction = EAST;
      }
    return direction;
}

/* Calls ir sensors and determines if their is a wall before marking it in memory by setting the direction pointer in a node to NULL */
void update_node(Node * current_node, Agent * current_agent) {
  bool L_sense = ir_read_d(irPin[0]);
  bool F_sense = ir_read_d(irPin[1]);
  bool R_sense = ir_read_d(irPin[2]);

  switch (current_agent->heading) {
    case NORTH:
      current_node->up = (F_sense == true) ? NULL : (current_node->up->down);
      current_node->left = (L_sense == true) ? NULL : (current_node->left->right);      
      current_node->right = (R_sense == true) ? NULL : (current_node->right->left);
    case EAST:
      current_node->up = (L_sense == true) ? NULL : (current_node->up->down);
      current_node->down = (R_sense == true) ? NULL : (current_node->down->up);      
      current_node->right = (F_sense == true) ? NULL : (current_node->right->left);
    case SOUTH:
      current_node->down = (F_sense == true) ? NULL : (current_node->down->up);
      current_node->left = (R_sense == true) ? NULL : (current_node->left->right);      
      current_node->right = (L_sense == true) ? NULL : (current_node->right->left);
    case WEST:
      current_node->up = (R_sense == true) ? NULL : (current_node->up->down);
      current_node->left = (F_sense == true) ? NULL : (current_node->left->right);      
      current_node->down = (L_sense == true) ? NULL : (current_node->down->up);
  }
  current_node->visited = true;
}
/* Updates the agent with new positioning and heading values */
void update_agent(Agent *current_agent) {
  current_agent->heading = get_heading();
  current_agent->row = position_y();
  current_agent->column = position_x();
}

void update_flood(Node *current_node) {
  short cn_flood = current_node->floodval;
  /* Target for calculations starting at goal Node*/
  if (current_node->row == END_Y && (current_node->column == END_X)){
    current_node->floodval = 0; 
  }
  /* Recalculates the floodval with a marching procession from the zeroth Node*/
  if (current_node->left != NULL && (cn_flood < current_node->left->floodval)) {
    current_node->left->floodval = cn_flood + 1;
  }
  if (current_node->right != NULL && (cn_flood < current_node->right->floodval)) {
    current_node->right->floodval = cn_flood + 1;
  }
  if (current_node->up != NULL && (cn_flood < current_node->up->floodval)) {
    current_node->up->floodval = cn_flood + 1;
  }
  if (current_node->down != NULL && (cn_flood < current_node->down->floodval)) {
    current_node->down->floodval = cn_flood + 1;
  }
}
/* For the reverse priority queue, returns true if node1 floodval is greater than node2 floodval */
struct compare_flood {
  bool operator()(Node *node1,Node *node2) {
    return node1->floodval > node2->floodval;
  }
};

/*
  Requires the current maze pointer as input 
  Writes the tiles to a reverse priority queue with the flood value being the order of priority
  Assigns all tiles a new flood value based on detected walls
  */
void update_map(Maze *maze) {
  priority_queue<Node*, vector<Node*>, compare_flood> Q;
  
  for(short x=0;x<SIZE;x++){
    for(short y=0;y<SIZE;y++) {
      Q.push(maze->map[x][y]);    
    }
  }

  while (!Q.empty()) {
    Node *c_node = Q.top();
    update_flood(c_node);
    Q.pop();
  }
}

#endif
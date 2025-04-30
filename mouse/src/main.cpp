#include <Arduino.h>
#include "sensor.hpp"
#include "attitude.hpp"
#include "flood.hpp"

/* Orientation Directions*/
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

/* Timer declarations*/ 
unsigned long current_time;
unsigned long prev_time_main;
unsigned long prev_time_att;
unsigned short time1 = 100;
unsigned short delta_att = 20;
short current_direction, next_direction;

/* Objects */
Node current_node;
Agent current_agent;
Maze current_maze;


// pin declarations;
int irPin[] = {1,2,3};
int motorPin[] = {4,5,6,7,8};
int accPin = 9;

// position init;
float position[] = {0, 0}; // X,Y | Column,Row
float accel[] = {0, 0};

// function declarations:

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(irPin[0], INPUT);
  pinMode(irPin[1], INPUT);
  pinMode(irPin[2], INPUT);
  Agent *current_agent = new_Agent();
  Maze *current_maze = new_Maze();
}

void loop() {
  // put your main code here, to run repeatedly:
  current_time = millis();

  if (current_time - prev_time_att > delta_att) {
  }

  if (current_time - prev_time_main > time1) {
    prev_time_main = current_time;

    update_agent(&current_agent);
    Node *active_node = current_maze.map[current_agent.column][current_agent.row];


    if(current_node.visited != true) { 
      update_node(active_node, &current_agent);
      update_map(&current_maze);
    }
    next_direction = get_sm_neighbor(active_node);

    
  }

}

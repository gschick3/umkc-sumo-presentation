#include <Move.h>
#include <NewPing.h>

Move move(11, 10, 12, 13);

NewPing sensors[7] = {
  NewPing( 2, 2, 100), //sensor 1 left 90 degree
  NewPing( 3, 3, 100), //sensor 2 left 45 degree
  NewPing( 4, 4, 100), //sensor 3 left 0 degree
  NewPing( 5, 5, 100), //sensor 4 right 0 degree
  NewPing( 6, 6, 100), //sensor 5 right 45 degree
  NewPing( 7, 7, 100), //sensor 6 right 90 degree
  NewPing( 9, 8, 100)  //sensor 7 back 180 degree
};

int delay_time = 50;

int backup_distance = 10; // [cm] backup at this distance from something
int follow_max = 70;      // [cm] follow things no farther than this
int stop_distance = 40;   // [cm] stop at this distance from something

void setup() {

  Serial.begin(115200);

  // sets the robot to drive forward and go 60% power
  move.power(255); // 153 for 60%, 204 for 80%
  delay(1000);
}

void loop() {
  // if left sensors detect object, turn left
  if(sensors[0].ping_cm() > 0 && sensors[0].ping_cm() < follow_max || sensors[1].ping_cm() > 0 && sensors[1].ping_cm() < follow_max) {
    Serial.println("Turn left");
    move.left();
    delay(delay_time);
  }
  // if right sensors detect object, turn right
  else if(sensors[5].ping_cm() > 0 && sensors[5].ping_cm() < follow_max || sensors[4].ping_cm() > 0 && sensors[4].ping_cm() < follow_max) {
    Serial.println("Turn right");
    move.right();
    delay(delay_time);
  }
  
  // if front sensors detect objects and are far enough away, drive forward
  if(sensors[2].ping_cm() > stop_distance && sensors[2].ping_cm() < follow_max || sensors[3].ping_cm() > stop_distance && sensors[3].ping_cm() < follow_max) {
    Serial.println("Move forward");
    move.forward();
    delay(delay_time);
  }
  // if front sensors detect objects and are too close, drive backward
  else if(sensors[3].ping_cm() < backup_distance && sensors[3].ping_cm() > 0 || sensors[3].ping_cm() < backup_distance && sensors[3].ping_cm() > 0) {
    Serial.println("Move backward");
    move.backward();
    delay(delay_time);
  }
}

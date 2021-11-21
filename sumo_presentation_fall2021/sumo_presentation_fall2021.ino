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

int dt = 100; // delay time

int max_backup_distance = 10; // [cm] backup at this distance from something
int max_stop_distance = 20;   // [cm] stop at this distance from something
int max_follow_distance = 40; // [cm] max distance to track objects

void setup() {

  Serial.begin(115200);

  // sets the robot to drive forward and go 60% power
  move.power(60); // 153 for 60%, 204 for 80%
  delay(1000);
}

void loop() {
  // if far left sensor sees object, turn left quickly
  if(sensors[0].ping_cm() > 0 && sensors[0].ping_cm() < max_follow_distance) {
    move.power(100);
    move.left();
    delay(dt);
  }
  // if far right sensor sees object, turn right quickly
  else if(sensors[5].ping_cm() > 0 && sensors[5].ping_cm() < max_follow_distance) {
    move.power(100);
    move.right();
    delay(dt);
  }
  // if close left sensor sees object, turn left moderately
  else if (sensors[1].ping_cm() > 0 && sensors[1].ping_cm() < max_follow_distance) {
    move.power(80);
    move.left();
    delay(dt);
  }
  // if close right sensor sees object, turn right moderately
  else if (sensors[4].ping_cm() > 0 && sensors[4].ping_cm() < max_follow_distance) {
    move.power(80);
    move.right();
    delay(dt);
  }
  else {
    // if object in left front sensor and not in right front sensor, turn left slowly
    if (sensors[2].ping_cm() < max_follow_distance && (sensors[3].ping_cm() > max_follow_distance || sensors[3].ping_cm() == 0)) {
      move.power(20);
      move.left();
      delay(dt);
    }
    // if object in right front sensor and not in left front sensor, turn right slowly
    if (sensors[3].ping_cm() < max_follow_distance && (sensors[2].ping_cm() > max_follow_distance || sensors[2].ping_cm() == 0)) {
      move.power(20);
      move.right();
      delay(dt);
    }
    // if object in both sensors, move forward
    if (sensors[2].ping_cm() > max_stop_distance && sensors[2].ping_cm() < max_follow_distance && sensors[3].ping_cm() > max_stop_distance && sensors[3].ping_cm() < max_follow_distance) {
      move.power(60);
      move.forward();
      delay(dt);
    }
    // if object is too close in both sensors, back up
    if (sensors[2].ping_cm() < max_backup_distance && sensors[2].ping_cm() > 0 && sensors[3].ping_cm() < max_backup_distance && sensors[3].ping_cm() > 0) {
      move.power(60);
      move.backward();
      delay(dt);
    }
  }
}

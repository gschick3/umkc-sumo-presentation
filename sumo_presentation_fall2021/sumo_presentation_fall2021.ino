#include <Move.h>
#include <NewPing.h>
#define MAX_PING 200

NewPing sensors[7] = {
  NewPing( 2, 2, MAX_PING), //sensor 1 left 90 degree
  NewPing( 3, 3, MAX_PING), //sensor 2 left 45 degree
  NewPing( 4, 4, MAX_PING), //sensor 3 left 0 degree
  NewPing( 5, 5, MAX_PING), //sensor 4 right 0 degree
  NewPing( 6, 6, MAX_PING), //sensor 5 right 45 degree
  NewPing( 7, 7, MAX_PING), //sensor 6 right 90 degree
  NewPing( 9, 8, MAX_PING)  //sensor 7 back 180 degree
};

Move move(11, 10, 12, 13);

int dt = 50; // delay time

int max_backup_distance = 30; // [cm] backup at this distance from something
int max_stop_distance = 45;   // [cm] stop at this distance from something
int max_follow_distance = 80; // [cm] max distance to track objects

void setup() {
  Serial.begin(115200);
  move.power(60);
  delay(1000);
}

void loop() {
  // if far left sensor sees object, turn left quickly
  if(sensors[0].ping_cm() > 0 && sensors[0].ping_cm() < max_follow_distance && false) { // disabled
    move.power(100);
    move.left();
    delay(dt);
  }
  // if far right sensor sees object, turn right quickly
  else if(sensors[5].ping_cm() > 0 && sensors[5].ping_cm() < max_follow_distance && false) { // disabled
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
  // if object in left front sensor and not in right front sensor, turn left slowly
  else if (sensors[2].ping_cm() < max_follow_distance && sensors[2].ping_cm() > 0 && (sensors[3].ping_cm() > max_follow_distance || sensors[3].ping_cm() == 0)) {
    move.power(40);
    move.left();
    delay(dt);
  }
  // if object in right front sensor and not in left front sensor, turn right slowly
  else if (sensors[3].ping_cm() < max_follow_distance && sensors[3].ping_cm() > 0 && (sensors[2].ping_cm() > max_follow_distance || sensors[2].ping_cm() == 0)) {
    move.power(40);
    move.right();
    delay(dt);
  }
  // if object in both sensors, move forward
  else if (sensors[2].ping_cm() > max_stop_distance && sensors[2].ping_cm() < max_follow_distance && sensors[3].ping_cm() > max_stop_distance && sensors[3].ping_cm() < max_follow_distance) {
    move.power(60);
    move.forward();
    delay(dt);
  }
  // if object is too close in both sensors, back up
  else if (sensors[2].ping_cm() < max_backup_distance && sensors[2].ping_cm() > 0 && sensors[3].ping_cm() < max_backup_distance && sensors[3].ping_cm() > 0) {
    move.power(60);
    move.backward();
    delay(dt);
  }
}

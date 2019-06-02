// Copyright (c) 2019 Waterloop. All rights reserved.

#include "Cosa/Trace.hh"
#include <Cosa/UART.hh>
#include <ResetWatchdog.h>

using namespace wlp;

// create a resetter that restarts if system does not respond for 1000 ms
static WatchdogResetter resetter{1000};

void setup() {
  uart.begin(9600);
  trace.begin(&uart);

  // start the resetter so that it can schedule the job
  resetter.begin();
}

void loop() {
  trace << "Hello";
  delay(900);

  trace << " World!";
  delay(10);

  trace << " System is alive!!" << endl;

  resetter.reset();
  delay(900);

  trace << "We reset, we good again!" << endl;

  trace << "Will Restart the system soon cuz loop :(" << endl;
  // this infinite loop will keep making the system restart
  while (1) {

  }
}

# Cosa Watchdog Reset

This is a package for utilizing Cosa `Watchdog` to reset the arduino when it is
blocked for a certain period of time. This comes in handy if arduino is stuck
and a reset is necessary.

This package has a class named `WatchdogResetter` which creates a Scheduler job 
using Watchdog clock. The clock has an expiry and before it is expired, it needs
to be reset by the user. If reset, clock goes back into another cycle and this
process continues. If there is no reset triggered, the clock detects that arduino
is stuck and creates `Watchdog 15 MS Timeout` followed by an infinite loop.
This blockage restarts the arduino.

### Example
```cpp
// 1000 ms expiry time
static WatchdogResetter resetter{1000};

void setup() {
    // start the scheduler
    resetter.begin();
}

void loop() {
    // some command
    
    resetter.reset();
    
    // some another command
}
```

More information can be found by reading example inside `tests` folder.


### Installing (wio >= 0.10.0)

```bash
wio install cosa-watchdog-reset@1.0.0 --url github.com/waterloop/cosa-watchdog-reset
```

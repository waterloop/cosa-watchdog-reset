// Copyright (c) 2019 Waterloop. All rights reserved.

#ifndef COSA_WATCHDOG_RESET_WIO_RESETWATCHDOG_H
#define COSA_WATCHDOG_RESET_WIO_RESETWATCHDOG_H

#include <Cosa/Types.h>
#include <Cosa/Job.hh>
#include <Cosa/Clock.hh>

namespace wlp {
class WatchdogResetter {
 public:
  /**
   * Constructor creates a new resetter which expects the user to reset it.
   * If not reset, it causes watchdog timeout and restarts the device.
   * @param interval time period (milliseconds) in which WatchdogResetter needs to be reset
   */
  explicit WatchdogResetter(uint16_t interval = 15);

  /**
   * Begin starts the scheduling job that monitors whether this has been reset
   * @param watchdog_ms if watchdog is not started, it starts with this timeout period.
   */
  void begin(uint16_t watchdog_ms = 16);

  /**
   * Reset's the watchdog resetter to signal it that there has been no issue
   */
  void reset();

 private:
  /**
   * Watcher class is a job that monitors the state of expiry for resetter
   */
  class Watcher : public Job {
   public:
    Watcher(Job::Scheduler *scheduler, uint16_t ms);
    void on_expired() override;
    void schedule();
    void reset();
   private:
    uint16_t m_period;
    bool m_expired;
  };

  Watcher m_watcher;
};
}

#endif //COSA_WATCHDOG_RESET_WIO_RESETWATCHDOG_H

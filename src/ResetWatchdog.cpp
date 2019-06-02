// Copyright (c) 2019 Waterloop. All rights reserved.

#include <ResetWatchdog.h>
#include <avr/io.h>
#include <Cosa/Watchdog.hh>
#include <Cosa/Trace.hh>

using namespace wlp;

static Watchdog::Scheduler watchdog_scheduler{};

WatchdogResetter::WatchdogResetter(uint16_t interval) : m_watcher{Watcher{&watchdog_scheduler, interval}} {}

void WatchdogResetter::begin(uint16_t watchdog_ms) {
  if (!Watchdog::is_initiated()) {
    Watchdog::begin(watchdog_ms);
  }
  m_watcher.schedule();
}

void WatchdogResetter::reset() {
  m_watcher.reset();
}

WatchdogResetter::Watcher::Watcher(Job::Scheduler *scheduler, uint16_t ms) :
    Job(scheduler), m_period{ms}, m_expired{true} {}

void WatchdogResetter::Watcher::on_expired() {
  if (m_expired) {
    wdt_disable();
    wdt_enable(WDTO_15MS);
    while (1) {}
  } else {
    schedule();
    m_expired = true;
  }
}

void WatchdogResetter::Watcher::schedule() {
  expire_after(m_period);
  start();
}

void WatchdogResetter::Watcher::reset() {
  m_expired = false;
}

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <string>
#include <chrono>
#include <vector>
#include <list>


typedef std::chrono::milliseconds MS;
typedef std::chrono::microseconds MuS;

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::time_point<Clock, MuS> TimePoint;

typedef std::pair<std::string, TimePoint> TimeTracker;
typedef std::chrono::duration<float> TimeDuration;

struct TimeEntry {
    std::string topic;
    TimePoint start;
    TimeDuration duration;

    TimeEntry(const TimeTracker& tracker)
        : topic(tracker.first)
        , start(tracker.second)
        , duration(std::chrono::duration_cast<MuS>(Clock::now() - tracker.second))
        { }
};

struct TimeRecord {
    std::string topic;
    TimeDuration duration;
    std::vector<TimeRecord> children;

    TimeRecord(const TimeEntry& entry)
        : topic(entry.topic)
        , duration(entry.duration)
        { }
};

class Timer {
public:
    const TimeTracker& Start(const std::string& topic);
    void Stop(const TimeTracker& time_tracker);

    TimeRecord ToRecord();

//private:
    std::list<TimeTracker> tracked_timers;
    std::vector<TimeEntry> entries;
    
    void Record(TimeRecord& parent, std::vector<TimeEntry>::reverse_iterator& it);
};

#endif//TIMER_HPP_

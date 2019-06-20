#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <list>
#include <map>

#include <engine/core/component.hpp>

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

struct TimeOverview {
    std::string topic;
    std::map<std::string, TimeOverview> children;
    std::vector<TimeDuration> samples;

    TimeOverview(const std::string& topic)
        : topic(topic)
        { }

    float Average() const;
    float Deviation(const float average) const;
    void Print(const unsigned indent, unsigned columns) const;
    unsigned FindMaxColumns(const unsigned indent) const;

    friend std::ostream& operator<<(std::ostream& os, const TimeOverview& overview);
};

class Timer : public Component {
public:
    std::vector<TimeEntry> entries;
    std::vector<TimeRecord> records;

    using Component::Component;

    const TimeTracker& Start(const std::string& topic);
    void Stop(const TimeTracker& time_tracker);

    TimeRecord ToRecord();
    TimeOverview ToOverview(TimeOverview* previous_overview = nullptr) const;
    
private:
    std::list<TimeTracker> tracked_timers;
    
    void Record(TimeRecord& parent, std::vector<TimeEntry>::reverse_iterator& it);
    void Overview(TimeOverview& parent_overview, const TimeRecord& parent_record) const;
};

#endif//TIMER_HPP_

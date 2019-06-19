#include "timer.hpp"

#include <stdexcept>
#include <iostream>


const TimeTracker& Timer::Start(const std::string& topic) {
    TimePoint point = std::chrono::time_point_cast<MuS>(Clock::now());
    return tracked_timers.emplace_back(TimeTracker(topic, point));
}

void Timer::Stop(const TimeTracker& time_tracker) {
    if (tracked_timers.back() != time_tracker) {
        throw new std::runtime_error("Last time entry hasn't been stopped");
    }
    entries.emplace_back(TimeEntry(time_tracker));

    // from here time_tracker references a null object!
    tracked_timers.pop_back();
}

TimeRecord Timer::ToRecord() {
    TimeRecord record(entries.back());

    auto it = entries.rbegin();
    Record(record, it);
    return record;
}

void Timer::Record(TimeRecord& parent, std::vector<TimeEntry>::reverse_iterator& it) {
    TimeEntry& parent_entry = *it;

    for (++it; it < entries.rend(); ++it) {
        TimeEntry& current_entry = *it;

        if (current_entry.start > parent_entry.start) {
            TimeRecord& current_record = *parent.children.insert(parent.children.begin(), TimeRecord(current_entry));
            Record(current_record, it);
            continue;
        }
        --it;
        break;
    }
}



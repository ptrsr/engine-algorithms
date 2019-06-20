#include "timer.hpp"

#include <stdexcept>
#include <math.h>
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

    if (tracked_timers.size() == 0) {
        records.push_back(ToRecord());
    }
}

TimeRecord Timer::ToRecord() {
    if (entries.size() == 0) {
        throw new std::underflow_error("No entries to record yet");
    }

    TimeRecord record(entries.back());
    auto it = entries.rbegin();
    Record(record, it);
    return record;
}

void Timer::Record(TimeRecord& parent, std::vector<TimeEntry>::reverse_iterator& it) {
    TimeEntry& parent_entry = *it;

    // entries have been saved in reversed order
    for (++it; it < entries.rend(); ++it) {
        TimeEntry& current_entry = *it;

        if (current_entry.start >= parent_entry.start) {
            TimeRecord& current_record = *parent.children.insert(parent.children.begin(), TimeRecord(current_entry));
            Record(current_record, it);
            continue;
        }
        --it;
        break;
    }
}

TimeOverview Timer::ToOverview(TimeOverview* previous_overview) const {
    TimeOverview overview(records[0].topic);
    if (!previous_overview) {
        previous_overview = &overview;
    }

    // process all the saved records
    for (const TimeRecord& record : records) {
        Overview(*previous_overview, record);
    }
    return *previous_overview;
}



void Timer::Overview(TimeOverview& parent_overview, const TimeRecord& parent_record) const {
    parent_overview.samples.push_back(parent_record.duration);

    for (const TimeRecord& record : parent_record.children) {
        auto pair = parent_overview.children.find(record.topic);

        TimeOverview* child_overview = nullptr;

        if (pair == parent_overview.children.end()) {
            TimeOverview new_overview(record.topic);
            std::pair<std::string, TimeOverview> new_pair = std::make_pair(record.topic, new_overview);

            auto it = parent_overview.children.insert(new_pair);
            child_overview = &it.first->second;
        } else {
            child_overview = &pair->second;
        }
        Overview(*child_overview, record);
    }
}

float TimeOverview::Average() const {
    float total = 0;
    for (const TimeDuration& sample : samples) {
        total += std::chrono::duration_cast<MS>(sample).count();
    }
    return total / samples.size();
}

float TimeOverview::Deviation(const float average) const {
    float total = 0;
    for (const TimeDuration& sample : samples) {
        float dev = std::chrono::duration_cast<MS>(sample).count();
        total += pow(average - dev, 2.f);
    }
    return total / samples.size();
}

unsigned TimeOverview::FindMaxColumns(const unsigned indent = 0) const {
    // bottom node
    if (children.size() == 0) {
        return indent * 2 + topic.size();
    }

    // find max column in children
    unsigned max = 0;
    for (auto& pair : children) {
        unsigned current = pair.second.FindMaxColumns(indent + 1);
        if (current > max) {
            max = current;
        }
    }
    return max;
}

void TimeOverview::Print(unsigned indent, unsigned columns) const {
    // for pretty printing
    if (columns == 0) {
        columns = FindMaxColumns();
    }

    // indent each record based on parent
    for (unsigned i = 0; i < indent; ++i) {
        std::cout << "  ";
    }
    std::cout << topic << ": ";
    
    // align data
    for (unsigned i = topic.size() + indent * 2; i < columns; ++i) {
        std::cout << " ";
    }
    std::cout << *this << std::endl;

    // print children
    for (auto& pair : children) {
        pair.second.Print(indent + 1, columns);
    }
}

std::ostream& operator<<(std::ostream& os, const TimeOverview& overview) {
    float average = overview.Average();
    os << "e " << overview.samples.size();
    os << ",  μ " << average;
    os << ",  σ " << overview.Deviation(average);
    return os;
}

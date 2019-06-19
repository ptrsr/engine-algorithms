#include <gtest/gtest.h>
#include <engine/auxiliary/timer.hpp>
#include <thread>

#include <iostream>

TEST(TimerTest, Start) {
    Timer timer;

    const TimeTracker& test1 = timer.Start("test1");
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    const TimeTracker& test2 = timer.Start("test2");
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    const TimeTracker& test3 = timer.Start("test3");
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    timer.Stop(test3);

    const TimeTracker& test4 = timer.Start("test4");

    timer.Stop(test4);
    timer.Stop(test2);
    timer.Stop(test1);

    TimeRecord record = timer.ToRecord();

    ASSERT_EQ("test1", record.topic);
    ASSERT_EQ(1, record.children.size());

    {
        TimeRecord& child = record.children[0];
        ASSERT_EQ("test2", child.topic);
        ASSERT_EQ(2, child.children.size());
    }
    {
        TimeRecord& child = record.children[0].children[0];
        ASSERT_EQ("test3", child.topic);
        ASSERT_EQ(0, child.children.size());
    }
    {
        TimeRecord& child = record.children[0].children[1];
        ASSERT_EQ("test4", child.topic);
        ASSERT_EQ(0, child.children.size());
    }
}

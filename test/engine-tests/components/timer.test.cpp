#include <gtest/gtest.h>
#include <engine/components/timer.hpp>

#include <thread>
#include <stdlib.h>

TEST(TimerTest, ToRecord) {
    Timer timer;
    ASSERT_ANY_THROW(timer.ToRecord());

    const TimeTracker& test1 = timer.Start("test1");
    const TimeTracker& test2 = timer.Start("test2");

    const TimeTracker& test3 = timer.Start("test3");
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

TEST(TimerTest, ToOverview) {
    Timer timer;

    // do a couple of runs
    for (unsigned i = 0; i < 5; ++i) {
        const TimeTracker& test1 = timer.Start("test1");
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 3 + 1));

        const TimeTracker& test2 = timer.Start("test2");

        const TimeTracker& test3 = timer.Start("test3");
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 3 + 1));
        timer.Stop(test3);

        // to test what happens when a timer hasn't been set during a run
        if (i % 2 == 0) {
            const TimeTracker& test4 = timer.Start("test4");
            std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 3 + 1));
            timer.Stop(test4);
        }
        
        timer.Stop(test2);
        timer.Stop(test1);
    }
    TimeOverview overview = timer.ToOverview();
    ASSERT_EQ(5, overview.samples.size());
}

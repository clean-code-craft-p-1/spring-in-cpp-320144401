#include "gtest/gtest.h"
#include "stats.h"
#include <cmath>
using namespace Statistics;
using namespace Alert;

TEST(Statistics, ReportsAverageMinMax) {
    auto computedStats = Statistics::ComputeStatistics({ 1.5, 8.9, 3.2, 4.5 });
    float epsilon = 0.001F;
    EXPECT_LT(std::abs(computedStats.average - 4.525), epsilon);
    EXPECT_LT(std::abs(computedStats.max - 8.9), epsilon);
    EXPECT_LT(std::abs(computedStats.min - 1.5), epsilon);
}

TEST(Statistics, AverageNaNForEmpty) {
      auto computedStats = Statistics::ComputeStatistics({});
      EXPECT_TRUE(std::isnan(computedStats.average));
      EXPECT_TRUE(std::isnan(computedStats.max));
      EXPECT_TRUE(std::isnan(computedStats.min));
}
//
TEST(Alert, AlertsWhenMaxExceeds) {
    EmailAlert emailAlert;
    LEDAlert ledAlert;
    std::vector<IAlerter*> alerters = { &emailAlert, &ledAlert };

    const float maxThreshold = 10.2F;
    StatsAlerter statsAlerter(maxThreshold, alerters);
    statsAlerter.checkAndAlert({ 99.8, 34.2, 4.5, 6.7 });

    EXPECT_TRUE(emailAlert.emailSent);
    EXPECT_TRUE(ledAlert.ledGlows);
}
#ifndef STATS_H
#define STATS_H

#include<iostream>
#include <vector>
#include<algorithm>
#include <numeric>
#include <limits>
#define CUSTOMNAN (std::numeric_limits<double>::quiet_NaN())


namespace Statistics {
    struct Stats
    {
       double average;
       double max;
       double min;
    };

    Stats ComputeStatistics(const std::vector<double>& );

    template<typename T>
    double getAverage(std::vector<T> const& data) {
        if (data.empty()) {
            return 0;
        }
        return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    }
}


namespace Alert
{
    class IAlerter
    {
    public:
        IAlerter();
        virtual void setThreshold(double) = 0;
        virtual void alert(const std::vector<double>&) = 0;
        virtual ~IAlerter();
    protected:
        double maxThreshold;      
    private:
        IAlerter(const IAlerter&) = delete;
        IAlerter(IAlerter&&) = delete;
        IAlerter operator=(const IAlerter&) = delete;
        IAlerter operator=(IAlerter&&) = delete;
    };

    class EmailAlert :public IAlerter
    {
    public:
        bool emailSent;
    public:
        EmailAlert();
        void alert(const std::vector<double>& Container) override;
        void setThreshold(double Thresold) override;
        ~EmailAlert();
    private:
        EmailAlert(const  EmailAlert&) = delete;
        EmailAlert(EmailAlert&&) = delete;
        EmailAlert operator = (const EmailAlert&) = delete;
        EmailAlert operator = (EmailAlert&&) = delete;
    };

    class LEDAlert :public IAlerter
    {
    public:
        bool ledGlows;
    public:
        LEDAlert();
        void alert(const std::vector<double>& Container) override;
        void setThreshold(double Thresold) override;
        ~LEDAlert();

    private:
        LEDAlert(const LEDAlert&) = delete;
        LEDAlert(LEDAlert&&) = delete;
        LEDAlert operator = (const LEDAlert&) = delete;
        LEDAlert operator = (LEDAlert&&) = delete;
    };


    class StatsAlerter
    {
    public:
        StatsAlerter();
        StatsAlerter(double, std::vector<IAlerter*>);
        void checkAndAlert(const std::vector<double>& Container) const;
        ~StatsAlerter();
    private:
        std::vector<IAlerter*> alerters;
    private:
        StatsAlerter(const StatsAlerter&)=delete;
        StatsAlerter(StatsAlerter&&)=delete;
        StatsAlerter operator = (const StatsAlerter&) = delete;
        StatsAlerter operator = (StatsAlerter&&) = delete;
    };
}

#endif // !
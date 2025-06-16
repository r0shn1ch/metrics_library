#include "../include/MetricsCollector.h"
#include <chrono>
#include <random>
#include <thread>

void simulateUserActivity(Metrics::Collector& collector) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> loginDist(0, 5);
    std::uniform_int_distribution<> purchaseDist(0, 2);

    while (true) {
        int logins = loginDist(gen);
        int purchases = purchaseDist(gen);

        Metrics::AddMetricValue(collector, "LoginsPerMinute", logins);
        Metrics::AddMetricValue(collector, "PurchasesPerMinute", purchases);
        Metrics::FlushMetrics(collector);
        std::this_thread::sleep_for(std::chrono::seconds(60));
    }
}

int main() {
    auto collector = Metrics::CreateFileCollector("user_activity.log");

    Metrics::RegisterMetric(*collector, "LoginsPerMinute");
    Metrics::RegisterMetric(*collector, "PurchasesPerMinute");

    std::thread userThread(simulateUserActivity, std::ref(*collector));

    std::this_thread::sleep_for(std::chrono::minutes(5));

    userThread.join();

    return 0;
}

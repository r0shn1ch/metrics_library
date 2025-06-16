#ifndef METRICSCOLLECTOR_H
#define METRICSCOLLECTOR_H

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <variant>

namespace Metrics {
using Value = std::variant<int, double, std::string>;

class Collector {
public:
    virtual ~Collector() = default;
    virtual void registerMetric(const std::string& name) = 0;
    virtual void addValue(const std::string& name, const Value& value) = 0;
    virtual void flush() = 0;
};

class FileCollector : public Collector {
public:
    FileCollector(const std::string& filename);
    ~FileCollector() override;
    void registerMetric(const std::string& name) override;
    void addValue(const std::string& name, const Value& value) override;
    void flush() override;

private:
    std::string getTimestamp() const;

    std::ofstream outputFile;
    std::string filename;
    std::map<std::string, Value> metrics;
    std::mutex mutex;
};

std::unique_ptr<Collector> CreateFileCollector(const std::string& filename);

// Usage
inline void RegisterMetric(Collector& collector, const std::string& name) {
    collector.registerMetric(name);
}

inline void AddMetricValue(Collector& collector, const std::string& name,
                           const Value& value) {
    collector.addValue(name, value);
}

inline void FlushMetrics(Collector& collector) { collector.flush(); }

}  // namespace Metrics

#endif

#ifndef METRICSCOLLECTOR_H
#define METRICSCOLLECTOR_H

#include <fstream>
#include <mutex>
#include <string>
#include <variant>
#include <memory>
#include <map>

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
    std::string getTimestamp() const;
    std::map<std::string, Value> metrics;

private:
    std::ofstream outputFile;
    std::string filename;
    std::mutex mutex;
};

std::unique_ptr<Collector> CreateFileCollector(const std::string& filename);
}  // namespace Metrics

#endif

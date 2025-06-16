#include "../include/MetricsCollector.h"

#include <chrono>
#include <iomanip>
#include <sstream>

namespace Metrics {

FileCollector::FileCollector(const std::string& filename) : filename(filename) {
    outputFile.open(filename, std::ios::app);
    if (!outputFile.is_open()) {
        // TODO: Consider using a more robust error handling strategy.
        throw std::runtime_error("Cannot open output file: " + filename);
    }
}

FileCollector::~FileCollector() {
    if (outputFile.is_open()) {
        outputFile.close();
    }
}

std::string FileCollector::getTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) %
        1000;
    auto timer = std::chrono::system_clock::to_time_t(now);
    std::tm bt = *std::localtime(&timer);

    std::ostringstream oss;
    oss << std::put_time(&bt, "%Y-%m-%d %H:%M:%S");
    oss << '.' << std::setw(3) << ms.count();
    return oss.str();
}

void FileCollector::registerMetric(const std::string& name) {
    // TODO: Implement metric registration.
}

void FileCollector::addValue(const std::string& name, const Value& value) {
    // TODO: Implement adding a value to a metric.
}

void FileCollector::flush() {
    // TODO: Implement flushing metrics to the file.
}

std::unique_ptr<Collector> CreateFileCollector(const std::string& filename) {
    return std::make_unique<FileCollector>(filename);
}
}

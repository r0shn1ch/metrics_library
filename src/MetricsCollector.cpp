#include "MetricsCollector.h"

namespace Metrics {

FileCollector::FileCollector(const std::string& filename) : filename(filename) {
    outputFile.open(filename, std::ios::app);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Cannot open output file: " + filename);
    }
}

FileCollector::~FileCollector() {
    if (outputFile.is_open()) {
        outputFile.close();
    }
}

void FileCollector::registerMetric(const std::string& name) {
    // Might extend this to support dynamic metric registration
    // if needed. Could add a check to ensure the metric doesn't already exist.
}

void FileCollector::addValue(const std::string& name, const Value& value) {
    std::lock_guard<std::mutex> lock(mutex);
    metrics[name] = value;
}

void FileCollector::flush() {
    std::lock_guard<std::mutex> lock(mutex);

    std::ostringstream line;
    line << getTimestamp() << " ";

    for (const auto& [name, value] : metrics) {
        line << "\"" << name << "\" ";
        std::visit([&line](auto&& arg) { line << arg << " "; }, value);
    }

    outputFile << line.str() << std::endl;
    metrics.clear();
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

std::unique_ptr<Collector> CreateFileCollector(const std::string& filename) {
    return std::make_unique<FileCollector>(filename);
}

}  // namespace Metrics

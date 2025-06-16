# Metrics Collector Library

A flexible C++ library for collecting and persisting metrics, adhering to clean
code standards.

## Features

*   **Abstraction:** Abstract `Collector` with `FileCollector` implementation.
*   **Flexibility:** Supports `int`, `double`, and `string` metric values.
*   **Thread-Safe:** Uses mutexes for thread safety.
*   **Simple API:** Concise API with helper functions.
*   **Cross-Platform:** Designed for cross-platform compatibility.
*   **Dependency Injection:** Factory function promotes dependency injection.

## Getting Started

### Prerequisites

*   C++ compiler (C++17 support)
*   CMake (3.15 or higher)
*   Git (optional)
*   Docker (optional)

### Building the Project

1.  **Clone the Repository (Optional):**

    ```bash
    git clone <repository_url>
    cd metrics-collector
    ```

2.  **Create a Build Directory:**

    ```bash
    mkdir build
    cd build
    ```

3.  **Configure the Project with CMake:**

    ```bash
    cmake ..
    ```

4.  **Build the Project:**

    ```bash
    make
    ```

### Running the Example

After building the project, you can run the example program:

```bash
./build/example
```

### Adding Your Metrics

1. Include MetricsCollector.h
```
#include "MetricsCollector.h"

```
2. Create a Collector: Use the factory function to create a collector. This can be done once at the beginning of your program or thread.
```
auto collector = Metrics::CreateFileCollector("your_metrics.log");

```
3. Add Metric Values: Use the AddMetricValue function to record the value of your metric. The first time a metric name is used, it is implicitly registered.
```
Metrics::AddMetricValue(*collector, "your_metric_name", your_metric_value);
//Where your_metric_value is of type int, double, or std::string.

```
4. Use the FlushMetrics to write all accumulated metrics to the log file. This clears the internal metric storage.
```
Metrics::FlushMetrics(*collector);

```
### Docker
```
docker build -t metrics-collector .
docker run -v $(pwd)/metrics:/app/metrics metrics-collector

```

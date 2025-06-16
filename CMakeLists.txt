cmake_minimum_required(VERSION 3.15)
project(MetricsCollector)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(metrics_collector
  src/MetricsCollector.cpp
  include/MetricsCollector.h
  src/MetricsCollector.cpp
)

target_include_directories(metrics_collector PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

install(TARGETS metrics_collector
  EXPORT metrics_collector-exports
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
)

install(DIRECTORY include/
  DESTINATION include
)

install(EXPORT metrics_collector-exports
  FILE metrics_collector-config.cmake
  NAMESPACE Metrics::
  DESTINATION lib/cmake/metrics_collector
)

add_executable(example examples/example.cpp)
target_link_libraries(example metrics_collector)

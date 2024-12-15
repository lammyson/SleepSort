#pragma once

#include <chrono>
#include <thread>
#include <vector>

/// @brief Asynchronously sorts a range by sleeping until it's time to add a
/// value
/// @tparam Iterator to a range of non-zero integral values
/// @param first Iterator to the first element in the range
/// @param last Iterator one past the end of the range
template<class Iterator>
auto
timeout_sort(Iterator first, Iterator last) -> void
{
  Iterator result = first;
  std::vector<std::thread> threads;

  const auto now = std::chrono::steady_clock::now();
  for (Iterator iter = first; iter != last; ++iter) {
    threads.push_back(std::thread(
      [&result, &now](Iterator::value_type val) {
        std::this_thread::sleep_until(now + std::chrono::seconds(val));
        *result = val;
        ++result;
      },
      *iter));
  }

  for (auto& thread : threads) {
    if (thread.joinable()) {
      thread.join();
    }
  }
}

// TODO - See if other parts of the concurrency library can implement timeout
// sort

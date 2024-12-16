#pragma once

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <future>
#include <iterator>
#include <thread>
#include <vector>

/// @brief Asynchronously sorts a range of integral types by sleeping until it's
/// time to add a value. Implemented using std::thread
/// @param first Iterator to the first element in the range
/// @param last Iterator one past the end of the range
template<
  typename Iterator,
  std::enable_if_t<
    std::is_integral_v<typename std::iterator_traits<Iterator>::value_type>,
    std::nullptr_t> = nullptr>
auto
sleep_sort_thread(Iterator first, Iterator last) -> void
{
  if (first == last) {
    return;
  }

  using ValueType = typename std::iterator_traits<Iterator>::value_type;

  std::vector<std::thread> threads;
  Iterator result = first;
  const auto min = *std::min_element(first, last);
  const auto now = std::chrono::steady_clock::now();
  for (Iterator iter = first; iter != last; ++iter) {
    threads.push_back(std::thread(
      [&result, &now, &min](ValueType val) {
        std::this_thread::sleep_until(now + std::chrono::seconds(val - min));
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

/// @brief Asynchronously sorts a range of integral types by sleeping until it's
/// time to add a value. Implemented using std::async
/// @param first Iterator to the first element in the range
/// @param last Iterator one past the end of the range
template<
  typename Iterator,
  std::enable_if_t<
    std::is_integral_v<typename std::iterator_traits<Iterator>::value_type>,
    std::nullptr_t> = nullptr>
auto
sleep_sort_async(Iterator first, Iterator last) -> void
{
  if (first == last) {
    return;
  }

  using ValueType = typename std::iterator_traits<Iterator>::value_type;

  std::vector<std::future<void>> futures;
  Iterator result = first;
  const auto min = *std::min_element(first, last);
  const auto now = std::chrono::steady_clock::now();
  for (Iterator iter = first; iter != last; ++iter) {
    futures.emplace_back(std::async(
      [&result, &now, &min](ValueType val) {
        std::this_thread::sleep_until(now + std::chrono::seconds(val - min));
        *result = val;
        ++result;
      },
      *iter));
  }
}

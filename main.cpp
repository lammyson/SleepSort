#include "timeout_sort.hpp"

#include <array>
#include <iostream>

template<class T, std::size_t N>
void
PrintArray(const std::array<T, N>& arr, std::ostream& stream)
{
  stream << "[";
  if (!arr.empty()) {
    for (const auto& type : arr) {
      stream << type << ",";
    }
    stream << "\b";
  }
  stream << "]";
}

auto
main(int /*unused*/, char** /*unused*/) -> int
{
  {
    std::array arr = { 6, 3, 5, 9, 1, 8, 0};

    std::cout << "-------------------\n";
    std::cout << "timeout_sort_thread\n";
    std::cout << "-------------------\n";

    std::cout << "array before sorting=";
    PrintArray(arr, std::cout);
    std::cout << "\n";

    timeout_sort_thread(arr.begin(), arr.end());

    std::cout << "array after sorting= ";
    PrintArray(arr, std::cout);
    std::cout << "\n";
  }

  std::cout << "\n";

  {
    std::array arr = { 6, 3, 5, 9, 1, 8, 0 };

    std::cout << "-------------------\n";
    std::cout << "timeout_sort_async\n";
    std::cout << "-------------------\n";

    std::cout << "array before sorting=";
    PrintArray(arr, std::cout);
    std::cout << "\n";

    timeout_sort_async(arr.begin(), arr.end());

    std::cout << "array after sorting= ";
    PrintArray(arr, std::cout);
    std::cout << "\n";
  }

  return 0;
}

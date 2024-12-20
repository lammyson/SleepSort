#include "sleep_sort.hpp"

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
    std::array arr = { -5, 3, 5, 1, 0, -2 };

    std::cout << "-------------------\n";
    std::cout << "sleep_sort_thread\n";
    std::cout << "-------------------\n";

    std::cout << "array before sorting=";
    PrintArray(arr, std::cout);
    std::cout << "\n";

    sleep_sort_thread(std::begin(arr), std::end(arr));

    std::cout << "array after sorting= ";
    PrintArray(arr, std::cout);
    std::cout << "\n";
  }

  std::cout << "\n";

  {
    std::array arr = { -5, 3, 5, 1, 0, -2 };

    std::cout << "-------------------\n";
    std::cout << "sleep_sort_async\n";
    std::cout << "-------------------\n";

    std::cout << "array before sorting=";
    PrintArray(arr, std::cout);
    std::cout << "\n";

    sleep_sort_async(arr.begin(), arr.end());

    std::cout << "array after sorting= ";
    PrintArray(arr, std::cout);
    std::cout << "\n";
  }

  return 0;
}

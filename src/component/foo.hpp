#pragma once
#include <string>
namespace base::component {
inline int add(int a, int b) { return a + b; }
std::string load_first_line(const std::string& filepath);
} // namespace base::component


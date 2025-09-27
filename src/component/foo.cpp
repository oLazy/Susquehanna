#include "component/foo.hpp"
#include <fstream>
#include <stdexcept>

namespace base::component {
std::string load_first_line(const std::string& filepath) {
    std::ifstream in(filepath);
    if (!in) throw std::runtime_error("Cannot open file: " + filepath);
    std::string line;
    std::getline(in, line);
    return line;
}
} // namespace base::component


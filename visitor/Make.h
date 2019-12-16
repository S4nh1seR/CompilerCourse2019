#pragma once

#include <memory>

template <typename T, class... Args>
inline std::shared_ptr<const T> make(Args... args) {
    return std::make_shared<const T>(args...);
}

#pragma once

#include <memory>

template <typename T, class... Args>
inline std::shared_ptr<const T> makeNode(Args&&... args) {
    return std::make_shared<const T>(std::forward<Args>(args)...);
}

template <typename T, class... Args>
inline std::unique_ptr<const T> makeWrapper(Args&&... args) {
    return std::make_unique<const T>(std::forward<Args>(args)...);
}

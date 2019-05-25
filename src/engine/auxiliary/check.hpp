#ifndef CHECK_HPP_
#define CHECK_HPP_

template<typename B, typename T>
constexpr void CheckType() {
    static_assert(std::is_base_of<B, T>::value, "T must derived from base");
}

#endif//CHECK_HPP_

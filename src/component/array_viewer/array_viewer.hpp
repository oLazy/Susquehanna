#pragma once
#include <type_traits>
#include <stdexcept>

template <class T>
class array_view{
public:
    using value_type = T;
    using size_type = std::size_t;
    using pointer = value_type*;
    using reference = value_type&;
    using iterator = pointer;
    using const_iterator = const value_type*;

    constexpr array_view() noexcept : data(nullptr), size(0) {}
    constexpr array_view(pointer data, size_type size) : data(data), size(size) {}

    // built-in array
    template<std::size_t N, class U = T,
            class = std::enable_if_t<!std::is_const_v<U>>> constexpr array_view(value_type (&arr)[N]) noexcept :
                    data(arr), size(N) {}
    // const built-in array
    template<std::size_t N, class U = T,
            class = std::enable_if<std::is_const_v<U>>, int = 0> constexpr
                    array_view(std::remove_const_t<value_type> const (&arr)[N]) noexcept :
                    data(arr), size(N) {}

    // accessors
    constexpr pointer getData() noexcept { return data; }
    constexpr const value_type* getData() const noexcept { return data; }
    constexpr size_type getSize() const noexcept { return size; }
    [[nodiscard]] constexpr bool empty() const noexcept {return (size==0);}

    // [] accessor operator (bound-unchecked)
    constexpr reference operator[](size_type i) const noexcept {return  data[i];}

    // bound-checked access to data
    reference at(size_type i) const {
        if (i>=size)throw std::out_of_range("array_view::at");
        return data[i];
    }

    // iterators
    constexpr iterator begin() const noexcept { return data; }
    constexpr iterator end() const noexcept {return data + size; }
    constexpr const_iterator cbegin() const noexcept { return data; }
    constexpr const_iterator cend() const noexcept { return data + size; }
private:
    pointer data;
    size_type size;

};

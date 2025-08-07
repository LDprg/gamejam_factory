#pragma once

#include <string>

template <typename T> struct type_name {
  private:
    static constexpr auto get() noexcept {
        constexpr std::string_view full_name{__PRETTY_FUNCTION__};
        constexpr std::string_view prefix{"[T = "};
        constexpr std::string_view suffix{"]"};

        constexpr auto start = full_name.find(prefix) + prefix.size();
        static_assert(start != std::string_view::npos);
        constexpr auto end = full_name.rfind(suffix);
        static_assert(end != std::string_view::npos);

        return full_name.substr(start, end - start);
    }

  public:
    using value_type = std::string_view;
    static constexpr value_type value{get()};

    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

template <typename T> inline constexpr auto type_name_v = type_name<T>::value;

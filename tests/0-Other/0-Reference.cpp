#include <option_result/option_result.hpp>

static_assert(std::is_same_v<orl::Ref<int>, int>);
static_assert(std::is_same_v<orl::Ref<int&>, std::reference_wrapper<int> >);
static_assert(std::is_same_v<orl::Ref<int const&>, std::reference_wrapper<int const> >);

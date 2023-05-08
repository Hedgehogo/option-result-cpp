#include <gtest/gtest.h>

#include <option_result.hpp>

TEST(Reference, General) {
	ASSERT_TRUE((std::is_same_v<orl::ref<int>, int>));
	ASSERT_TRUE((std::is_same_v<orl::ref<int&>, std::reference_wrapper<int>>));
	ASSERT_TRUE((std::is_same_v<orl::ref<const int&>, std::reference_wrapper<const int>>));
}
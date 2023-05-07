#include <gtest/gtest.h>

#include <option_result.hpp>

TEST(Conversion_Result, Ok_1_ok_or_none) {
	auto res{orl::Result<int, int>::Ok(5)};
	
	ASSERT_EQ(res.ok_or_none(), orl::Option<int>{5});
}

TEST(Conversion_Result, Ok_1_error_or_none) {
	auto res{orl::Result<int, int>::Ok(5)};
	
	ASSERT_EQ(res.error_or_none(), orl::Option<int>{});
}

TEST(Conversion_Result, Error_1_ok_or_none) {
	auto res{orl::Result<int, int>::Error(15)};
	
	ASSERT_EQ(res.ok_or_none(), orl::Option<int>{});
}

TEST(Conversion_Result, Error_1_error_or_none) {
	auto res{orl::Result<int, int>::Error(15)};
	
	ASSERT_EQ(res.error_or_none(), orl::Option<int>{15});
}
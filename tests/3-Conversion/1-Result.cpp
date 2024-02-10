#include <gtest/gtest.h>

#include <option_result/option_result.hpp>

TEST(Conversion_Result, Ok_1_ok_or_none) {
	{
		const auto res{orl::Result<int, int>::Ok(5)};
		
		ASSERT_EQ(res.ok_or_none(), orl::Option<int const&>{res.except()});
	}
	{
		auto res{orl::Result<int, int>::Ok(5)};
		
		ASSERT_EQ(res.ok_or_none(), orl::Option<int&>{res.except()});
	}
	{
		auto res{orl::Result<int, int>::Ok(5)};
		
		ASSERT_EQ(std::move(res).ok_or_none(), orl::Option<int>{5});
	}
}

TEST(Conversion_Result, Ok_1_error_or_none) {
	{
		const auto res{orl::Result<int, int>::Ok(5)};
		
		ASSERT_EQ(res.error_or_none(), orl::Option<int const&>{});
	}
	{
		auto res{orl::Result<int, int>::Ok(5)};
		
		ASSERT_EQ(res.error_or_none(), orl::Option<int&>{});
	}
	{
		auto res{orl::Result<int, int>::Ok(5)};
		
		ASSERT_EQ(std::move(res).error_or_none(), orl::Option<int>{});
	}
}

TEST(Conversion_Result, Error_1_ok_or_none) {
	{
		const auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_EQ(res.ok_or_none(), orl::Option<int const&>{});
	}
	{
		auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_EQ(res.ok_or_none(), orl::Option<int&>{});
	}
	{
		auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_EQ(std::move(res).ok_or_none(), orl::Option<int>{});
	}
}

TEST(Conversion_Result, Error_1_error_or_none) {
	{
		const auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_EQ(res.error_or_none(), orl::Option<int const&>{res.error()});
	}
	{
		auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_EQ(res.error_or_none(), orl::Option<int&>{res.error()});
	}
	{
		auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_EQ(std::move(res).error_or_none(), orl::Option<int>{15});
	}
}
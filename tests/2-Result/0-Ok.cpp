#include <gtest/gtest.h>

#include <option_result/option_result.hpp>

class NonCopyable {
public:
	NonCopyable(NonCopyable const&) = delete;
	
	NonCopyable(NonCopyable&&) = default;
	
	NonCopyable() = default;
};

TEST(Result, Ok_0) {
	auto value{NonCopyable{}};
	auto opt{orl::Result<NonCopyable, int>::Ok(std::move(value))};
}

TEST(Result, Ok_1_ok) {
	{
		const auto res{orl::Result<int, int>::Ok(7)};
		
		ASSERT_EQ(&res.ok(), &res.except());
	}
	{
		auto res{orl::Result<int, int>::Ok(7)};
		
		ASSERT_EQ(&res.ok(), &res.except());
	}
	{
		auto res{orl::Result<int, int>::Ok(7)};
		
		ASSERT_EQ(std::move(res).ok(), 7);
	}
}

TEST(Result, Ok_2_is_ok) {
	auto res{orl::Result<int, int>::Ok(7)};
	
	ASSERT_TRUE(res.is_ok());
}

TEST(Result, Ok_3_ok_or) {
	{
		const auto res{orl::Result<int, int>::Ok(7)};
		
		ASSERT_EQ(res.ok_or(5), 7);
	}
	{
		auto res{orl::Result<int, int>::Ok(7)};
		auto default_some{5};
		
		ASSERT_EQ(&res.ok_or(default_some), &res.except());
	}
	{
		auto res{orl::Result<int, int>::Ok(7)};
		
		ASSERT_EQ(std::move(res).ok_or(5), 7);
	}
}

TEST(Result, Ok_4_ok_or_else) {
	{
		const auto res{orl::Result<int, int>::Ok(7)};
		
		ASSERT_EQ(res.ok_or_else([]() -> int {
			return 5;
		}), 7);
	}
	{
		auto res{orl::Result<int, int>::Ok(7)};
		auto default_ok{5};
		
		ASSERT_EQ(&res.ok_or_else([&]() -> int& {
			return default_ok;
		}), &res.except());
	}
	{
		auto res{orl::Result<int, int>::Ok(7)};
		
		ASSERT_EQ(std::move(res).ok_or_else([]() -> int {
			return 5;
		}), 7);
	}
}

TEST(Result, Ok_5_ok_or_ptr) {
	auto res{orl::Result<int*, int>::Ok(new int{7})};
	
	auto value{res.ok_or_ptr(5)};
	ASSERT_EQ(*value, 7);
	
	delete value;
}

TEST(Result, Ok_6_map_ok) {
	{
		const auto res{orl::Result<int, int>::Ok(7)};
		
		ASSERT_EQ(res.map_ok([](int const& ok) {
			return char('a' + char(ok));
		}).some_or('a'), 'h');
	}
	{
		auto res{orl::Result<int, int>::Ok(7)};
		
		ASSERT_EQ(res.map_ok([](int& ok) {
			return char('a' + char(ok));
		}).some_or('a'), 'h');
	}
	{
		auto res{orl::Result<int, int>::Ok(7)};
		
		ASSERT_EQ(std::move(res).map_ok([](int&& ok) {
			return char('a' + char(ok));
		}).some_or('a'), 'h');
	}
}

TEST(Result, Ok_7_error_or) {
	{
		const auto res{orl::Result<int, int>::Ok(7)};
		
		ASSERT_EQ(res.error_or(19), 19);
	}
	{
		auto res{orl::Result<int, int>::Ok(7)};
		auto default_error{19};
		
		ASSERT_EQ(&res.error_or(default_error), &default_error);
	}
	{
		auto res{orl::Result<int, int>::Ok(7)};
		
		ASSERT_EQ(std::move(res).error_or(19), 19);
	}
}

TEST(Result, Ok_8_error_or_else) {
	{
		const auto res{orl::Result<int, int>::Ok(7)};
		
		ASSERT_EQ(res.error_or_else([]() -> int {
			return 19;
		}), 19);
	}
	{
		auto res{orl::Result<int, int>::Ok(7)};
		auto default_error{19};
		
		ASSERT_EQ(&res.error_or_else([&]() -> int& {
			return default_error;
		}), &default_error);
	}
	{
		auto res{orl::Result<int, int>::Ok(7)};
		
		ASSERT_EQ(std::move(res).error_or_else([]() -> int {
			return 19;
		}), 19);
	}
}

TEST(Result, Ok_9_error_or_ptr) {
	auto res{orl::Result<int, int*>::Ok(7)};
	
	auto value{res.error_or_ptr(19)};
	ASSERT_EQ(*value, 19);
	
	delete value;
}

TEST(Result, Ok_10_map_error) {
	{
		const auto res{orl::Result<int, int>::Ok(7)};
		
		ASSERT_EQ(res.map_error([](int const& error) {
			return char('a' + char(error));
		}).some_or('a'), 'a');
	}
	{
		auto res{orl::Result<int, int>::Ok(7)};
		
		ASSERT_EQ(res.map_error([](int& error) {
			return char('a' + char(error));
		}).some_or('a'), 'a');
	}
	{
		auto res{orl::Result<int, int>::Ok(7)};
		
		ASSERT_EQ(std::move(res).map_error([](int&& error) {
			return char('a' + char(error));
		}).some_or('a'), 'a');
	}
}

TEST(Result, Ok_11_except) {
	{
		const auto res{orl::Result<int, int>::Ok(7)};
		
		ASSERT_EQ(res.except(), 7);
	}
	{
		auto res{orl::Result<int, int>::Ok(7)};
		
		ASSERT_EQ(res.except(), 7);
	}
	{
		auto res{orl::Result<int, int>::Ok(7)};
		
		ASSERT_EQ(std::move(res).except(), 7);
	}
}

TEST(Result, Ok_12_operator_bool) {
	auto res{orl::Result<int, int>::Ok(7)};
	
	ASSERT_TRUE(res);
}
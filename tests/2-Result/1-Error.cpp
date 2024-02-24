#include <gtest/gtest.h>

#include <option_result/option_result.hpp>

class NonCopyable {
public:
	NonCopyable(NonCopyable const&) = delete;
	
	NonCopyable(NonCopyable&&) = default;
	
	NonCopyable() = default;
};

TEST(Result, Error_0) {
	auto value{NonCopyable{}};
	auto opt{orl::Result<int, NonCopyable>::Error(std::move(value))};
}

TEST(Result, Error_1_error) {
	{
		const auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_EQ(res.error(), 15);
	}
	{
		auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_EQ(res.error(), 15);
	}
	{
		auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_EQ(std::move(res).error(), 15);
	}
}

TEST(Result, Error_2_is_ok) {
	auto res{orl::Result<int, int>::Error(15)};
	
	ASSERT_FALSE(res.is_ok());
}

TEST(Result, Error_3_ok_or) {
	{
		const auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_EQ(res.ok_or(5), 5);
	}
	{
		auto res{orl::Result<int, int>::Error(15)};
		auto default_some{5};
		
		ASSERT_EQ(&res.ok_or(default_some), &default_some);
	}
	{
		auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_EQ(res.ok_or(5), 5);
	}
}

TEST(Result, Error_4_ok_or_else) {
	{
		const auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_EQ(res.ok_or_else([]() -> int {
			return 5;
		}), 5);
	}
	{
		auto res{orl::Result<int, int>::Error(15)};
		auto default_ok{5};
		
		ASSERT_EQ(&res.ok_or_else([&]() -> int& {
			return default_ok;
		}), &default_ok);
	}
	{
		auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_EQ(std::move(res).ok_or_else([]() -> int {
			return 5;
		}), 5);
	}
}

TEST(Result, Error_5_ok_or_ptr) {
	auto res{orl::Result<int*, int>::Error(15)};
	
	auto value{res.ok_or_ptr(5)};
	ASSERT_EQ(*value, 5);
	
	delete value;
}

TEST(Result, Error_6_map_ok) {
	{
		const auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_EQ(res.map_ok([](int const& ok) {
			return char('a' + char(ok));
		}).ok_or('a'), 'a');
	}
	{
		auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_EQ(res.map_ok([](int& ok) {
			return char('a' + char(ok));
		}).ok_or('a'), 'a');
	}
	{
		auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_EQ(std::move(res).map_ok([](int ok) {
			return char('a' + char(ok));
		}).ok_or('a'), 'a');
	}
}

TEST(Result, Error_7_is_error) {
	auto res{orl::Result<int, int>::Error(15)};
	
	ASSERT_TRUE(res.is_error());
}

TEST(Result, Error_8_error_or) {
	{
		const auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_EQ(res.error_or(19), 15);
	}
	{
		auto res{orl::Result<int, int>::Error(15)};
		auto default_error{19};
		
		ASSERT_EQ(&res.error_or(default_error), &res.error());
	}
	{
		auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_EQ(std::move(res).error_or(19), 15);
	}
}

TEST(Result, Error_9_error_or_else) {
	{
		const auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_EQ(res.error_or_else([]() -> int {
			return 19;
		}), 15);
	}
	{
		auto res{orl::Result<int, int>::Error(15)};
		auto default_error{19};
		
		ASSERT_EQ(&res.error_or_else([&]() -> int& {
			return default_error;
		}), &res.error());
	}
	{
		auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_EQ(std::move(res).error_or_else([]() -> int {
			return 19;
		}), 15);
	}
}

TEST(Result, Error_10_error_or_ptr) {
	auto res{orl::Result<int, int*>::Error(new int{15})};
	
	auto value{res.error_or_ptr(19)};
	ASSERT_EQ(*value, 15);
	
	delete value;
}

TEST(Result, Error_11_map_error) {
	{
		const auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_EQ(res.map_error([](int const& error) {
			return char('a' + char(error));
		}).error_or('a'), 'p');
	}
	{
		auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_EQ(res.map_error([](int& error) {
			return char('a' + char(error));
		}).error_or('a'), 'p');
	}
	{
		auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_EQ(std::move(res).map_error([](int error) {
			return char('a' + char(error));
		}).error_or('a'), 'p');
	}
}

TEST(Result, Error_12_except) {
	{
		const auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_THROW(res.except(), int);
	}
	{
		auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_THROW(res.except(), int);
	}
	{
		auto res{orl::Result<int, int>::Error(15)};
		
		ASSERT_THROW(std::move(res).except(), int);
	}
}

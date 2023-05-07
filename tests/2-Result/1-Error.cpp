#include <gtest/gtest.h>

#include <option_result.hpp>

TEST(Result, Error_1_error) {
	auto res{orl::Result<int, int>::Error(15)};
	
	ASSERT_EQ(res.error(), 15);
}

TEST(Result, Error_2_is_ok) {
	auto res{orl::Result<int, int>::Error(15)};
	
	ASSERT_FALSE(res.is_ok());
}

TEST(Result, Error_3_ok_or) {
	auto res{orl::Result<int, int>::Error(15)};
	
	ASSERT_EQ(res.ok_or(5), 5);
}

TEST(Result, Error_4_error_or) {
	auto res{orl::Result<int, int>::Error(15)};
	
	ASSERT_EQ(res.error_or(19), 15);
}

TEST(Result, Error_5_convert_ok_or) {
	auto res{orl::Result<int, int>::Error(15)};
	
	ASSERT_EQ(res.convert_ok_or<char>('a', [](const int& some) { return char('a' + char(some)); }), 'a');
}

TEST(Result, Error_6_convert_ok_or_ptr) {
	auto res{orl::Result<int, int>::Error(15)};
	int* value{res.convert_ok_or_ptr<int>([](const int& some) { return new int{some}; }, 5)};
	
	ASSERT_EQ(*value, 5);
	
	delete value;
}

TEST(Result, Error_7_convert_error_or) {
	auto res{orl::Result<int, int>::Error(15)};
	
	ASSERT_EQ(res.convert_error_or<char>('a', [](const int& some) { return char('a' + char(some)); }), 'p');
}

TEST(Result, Error_8_convert_error_or_ptr) {
	auto res{orl::Result<int, int>::Error(15)};
	int* value{res.convert_error_or_ptr<int>([](const int& some) { return new int{some}; }, 19)};
	
	ASSERT_EQ(*value, 15);
	
	delete value;
}

TEST(Result, Error_9_except) {
	auto res{orl::Result<int, int>::Error(15)};
	
	ASSERT_THROW(res.except(), int);
}

TEST(Result, Error_10_operator_bool) {
	auto res{orl::Result<int, int>::Error(15)};
	
	ASSERT_FALSE(res);
}
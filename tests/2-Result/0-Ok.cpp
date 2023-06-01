#include <gtest/gtest.h>

#include <option_result/option_result.hpp>

TEST(Result, Ok_1_ok) {
	auto res{orl::Result<int, int>::Ok(7)};
	
	ASSERT_EQ(res.ok(), 7);
}

TEST(Result, Ok_2_is_ok) {
	auto res{orl::Result<int, int>::Ok(7)};
	
	ASSERT_TRUE(res.is_ok());
}

TEST(Result, Ok_3_ok_or) {
	auto res{orl::Result<int, int>::Ok(7)};
	
	ASSERT_EQ(res.ok_or(5), 7);
}

TEST(Result, Ok_4_ok_or_ptr) {
	auto res{orl::Result<int*, int>::Ok(new int{7})};
	
	int* value{res.ok_or_ptr(5)};
	ASSERT_EQ(*value, 7);
	
	delete value;
}

TEST(Result, Ok_5_error_or) {
	auto res{orl::Result<int, int>::Ok(7)};
	
	ASSERT_EQ(res.error_or(19), 19);
}

TEST(Result, Ok_6_error_or_ptr) {
	auto res{orl::Result<int, int*>::Ok(7)};
	
	int* value{res.error_or_ptr(19)};
	ASSERT_EQ(*value, 19);
	
	delete value;
}

TEST(Result, Ok_7_convert_ok_or) {
	auto res{orl::Result<int, int>::Ok(7)};
	
	ASSERT_EQ(res.convert_ok_or<char>('a', [](const int& some) { return char('a' + char(some)); }), 'h');
}

TEST(Result, Ok_8_convert_ok_or_ptr) {
	auto res{orl::Result<int, int>::Ok(7)};
	int* value{res.convert_ok_or_ptr<int>([](const int& some) { return new int{some}; }, 5)};
	
	ASSERT_EQ(*value, 7);
	
	delete value;
}

TEST(Result, Ok_9_convert_error_or) {
	auto res{orl::Result<int, int>::Ok(7)};
	
	ASSERT_EQ(res.convert_error_or<char>('a', [](const int& some) { return char('a' + char(some)); }), 'a');
}

TEST(Result, Ok_10_convert_error_or_ptr) {
	auto res{orl::Result<int, int>::Ok(7)};
	int* value{res.convert_error_or_ptr<int>([](const int& some) { return new int{some}; }, 19)};
	
	ASSERT_EQ(*value, 19);
	
	delete value;
}

TEST(Result, Ok_11_except) {
	auto res{orl::Result<int, int>::Ok(7)};
	
	ASSERT_NO_THROW(res.except());
	ASSERT_EQ(res.except(), 7);
}

TEST(Result, Ok_12_operator_bool) {
	auto res{orl::Result<int, int>::Ok(7)};
	
	ASSERT_TRUE(res);
}
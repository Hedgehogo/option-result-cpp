#include <gtest/gtest.h>

#include <option_result/option_result.hpp>

class NonCopyable {
public:
	NonCopyable(NonCopyable const&) = delete;
	NonCopyable(NonCopyable&&) = default;
	NonCopyable() = default;
};

TEST(Result, Ok_0) {
	NonCopyable value{};
	auto opt{orl::Result<NonCopyable, int>::Ok(std::move(value))};
}

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

TEST(Result, Ok_4_ok_or_else) {
	auto res{orl::Result<int, int>::Ok(7)};
	
	int default_ok{5};
	ASSERT_EQ(res.ok_or_else([&]() -> int& { return default_ok; }), 7);
}

TEST(Result, Ok_5_ok_or_ptr) {
	auto res{orl::Result<int*, int>::Ok(new int{7})};
	
	int* value{res.ok_or_ptr(5)};
	ASSERT_EQ(*value, 7);
	
	delete value;
}

TEST(Result, Ok_6_error_or) {
	auto res{orl::Result<int, int>::Ok(7)};
	
	ASSERT_EQ(res.error_or(19), 19);
}

TEST(Result, Ok_7_error_or_else) {
	auto res{orl::Result<int, int>::Ok(7)};
	
	int default_error{19};
	ASSERT_EQ(res.error_or_else([&]() -> int& { return default_error; }), 19);
}

TEST(Result, Ok_8_error_or_ptr) {
	auto res{orl::Result<int, int*>::Ok(7)};
	
	int* value{res.error_or_ptr(19)};
	ASSERT_EQ(*value, 19);
	
	delete value;
}

TEST(Result, Ok_9_map_ok) {
	auto res{orl::Result<int, int>::Ok(7)};
	
	ASSERT_EQ(res.map_ok([](const int& ok) { return char('a' + char(ok)); }).some_or('a'), 'h');
}

TEST(Result, Ok_10_map_error) {
	auto res{orl::Result<int, int>::Ok(7)};
	
	ASSERT_EQ(res.map_error([](const int& error) { return char('a' + char(error)); }).some_or('a'), 'a');
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
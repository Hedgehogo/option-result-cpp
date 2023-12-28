#include <gtest/gtest.h>

#include <option_result/option_result.hpp>

TEST(Option, None_1_is_some) {
	orl::Option<int> opt{};
	
	ASSERT_FALSE(opt.is_some());
}

TEST(Option, None_2_some_or) {
	orl::Option<int> opt{};
	
	ASSERT_EQ(opt.some_or(5), 5);
}

TEST(Option, None_3_some_or_ptr) {
	orl::Option<int*> opt{};
	
	int* value{opt.some_or_ptr(5)};
	ASSERT_EQ(*value, 5);
	
	delete value;
}

TEST(Option, None_4_convert_or) {
	orl::Option<int> opt{};
	
	ASSERT_EQ(opt.convert_or<char>('a', [](const int& some) { return char('a' + char(some)); }), 'a');
}

TEST(Option, None_5_convert_or_ptr) {
	orl::Option<int> opt{};
	int* value{opt.convert_or_ptr<int>([](const int& some) { return new int{some}; }, 5)};
	
	ASSERT_EQ(*value, 5);
	
	delete value;
}

TEST(Option, None_6_except) {
	orl::Option<int> opt{};
	
	ASSERT_THROW(opt.except(), std::runtime_error);
	ASSERT_THROW(opt.except(std::runtime_error("")), std::runtime_error);
}

TEST(Option, None_7_optional) {
	orl::Option<int> opt{};
	
	ASSERT_EQ(opt.optional(), std::optional<int>{});
}

TEST(Option, None_8_operator_bool) {
	orl::Option<int> opt{};
	
	ASSERT_FALSE(opt);
}
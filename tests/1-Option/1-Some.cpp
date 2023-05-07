#include <gtest/gtest.h>

#include <option_result.hpp>

TEST(Option, Some_1_some) {
	orl::Option<int> opt{7};
	
	ASSERT_EQ(opt.some(), 7);
}

TEST(Option, Some_2_is_some) {
	orl::Option<int> opt{7};
	
	ASSERT_TRUE(opt.is_some());
}

TEST(Option, Some_3_some_or) {
	orl::Option<int> opt{7};
	
	ASSERT_EQ(opt.some_or(5), 7);
}

TEST(Option, Some_4_convert_or) {
	orl::Option<int> opt{7};
	
	ASSERT_EQ(opt.convert_or<char>('a', [](const int& some) { return char('a' + char(some)); }), 'h');
}

TEST(Option, Some_5_convert_or_ptr) {
	orl::Option<int> opt{7};
	int* value{opt.convert_or_ptr<int>([](const int& some) { return new int{some}; }, 5)};
	
	ASSERT_EQ(*value, 7);
	
	delete value;
}

TEST(Option, Some_6_except) {
	orl::Option<int> opt{7};
	
	ASSERT_NO_THROW(opt.except(std::runtime_error("")));
	ASSERT_EQ(opt.except(std::runtime_error("")), 7);
}

TEST(Option, Some_7_optional) {
	orl::Option<int> opt{7};
	
	ASSERT_EQ(opt.optional(), std::optional<int>{7});
}

TEST(Option, Some_8_operator_bool) {
	orl::Option<int> opt{7};
	
	ASSERT_TRUE(opt);
}
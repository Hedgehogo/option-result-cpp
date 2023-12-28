#include <gtest/gtest.h>

#include <option_result/option_result.hpp>

TEST(Conversion_Option, None_1_ok_or) {
	auto opt{orl::Option<int>()};
	
	ASSERT_EQ(opt.ok_or<int>(15), (orl::Result<int, int>::Error(15)));
}

TEST(Conversion_Option, None_1_error_or) {
	auto opt{orl::Option<int>()};
	
	ASSERT_EQ(opt.error_or<int>(7), (orl::Result<int, int>::Ok(7)));
}

TEST(Conversion_Option, Some_1_ok_or) {
	auto opt{orl::Option<int>(5)};
	
	ASSERT_EQ(opt.ok_or<int>(15), (orl::Result<int, int>::Ok(5)));
}

TEST(Conversion_Option, Some_1_error_or) {
	auto opt{orl::Option<int>(5)};
	
	ASSERT_EQ(opt.error_or<int>(7), (orl::Result<int, int>::Error(5)));
}

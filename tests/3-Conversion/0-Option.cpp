#include <gtest/gtest.h>

#include <option_result/option_result.hpp>

TEST(Conversion_Option, None_1_ok_or) {
	{
		auto const opt{orl::Option<int>{}};
		
		ASSERT_EQ(opt.ok_or<int>(15), (orl::Result<int const&, int>::Error(15)));
	}
	{
		auto opt{orl::Option<int>{}};
		
		ASSERT_EQ(opt.ok_or<int>(15), (orl::Result<int&, int>::Error(15)));
	}
	{
		auto opt{orl::Option<int>{}};
		
		ASSERT_EQ(std::move(opt).ok_or<int>(15), (orl::Result<int, int>::Error(15)));
	}
}

TEST(Conversion_Option, None_1_error_or) {
	{
		auto const opt{orl::Option<int>{}};
		
		ASSERT_EQ(opt.error_or<int>(7), (orl::Result<int, int const&>::Ok(7)));
	}
	{
		auto opt{orl::Option<int>{}};
		
		ASSERT_EQ(opt.error_or<int>(7), (orl::Result<int, int&>::Ok(7)));
	}
	{
		auto opt{orl::Option<int>{}};
		
		ASSERT_EQ(std::move(opt).error_or<int>(7), (orl::Result<int, int>::Ok(7)));
	}
}

TEST(Conversion_Option, Some_1_ok_or) {
	{
		auto const opt{orl::Option<int>{5}};
		
		ASSERT_EQ(opt.ok_or<int>(15), (orl::Result<int const&, int>::Ok(opt.except())));
	}
	{
		auto opt{orl::Option<int>{5}};
		
		ASSERT_EQ(opt.ok_or<int>(15), (orl::Result<int&, int>::Ok(opt.except())));
	}
	{
		auto opt{orl::Option<int>{5}};
		
		ASSERT_EQ(std::move(opt).ok_or<int>(15), (orl::Result<int, int>::Ok(5)));
	}
}

TEST(Conversion_Option, Some_1_error_or) {
	{
		auto const opt{orl::Option<int>{5}};
		
		ASSERT_EQ(opt.error_or<int>(7), (orl::Result<int, int const&>::Error(opt.except())));
	}
	{
		auto opt{orl::Option<int>{5}};
		
		ASSERT_EQ(opt.error_or<int>(7), (orl::Result<int, int&>::Error(opt.except())));
	}
	{
		auto opt{orl::Option<int>{5}};
		
		ASSERT_EQ(std::move(opt).error_or<int>(7), (orl::Result<int, int>::Error(5)));
	}
}

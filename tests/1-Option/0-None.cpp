#include <gtest/gtest.h>

#include <option_result/option_result.hpp>

TEST(Option, None_1_is_some) {
	auto opt{orl::Option<int>{}};
	
	ASSERT_FALSE(opt.is_some());
}

TEST(Option, None_2_some_or) {
	{
		const auto opt{orl::Option<int>{}};
		
		ASSERT_EQ(opt.some_or(5), 5);
	}
	{
		auto opt{orl::Option<int>{}};
		auto default_some{5};
		
		ASSERT_EQ(&opt.some_or(default_some), &default_some);
	}
	{
		auto opt{orl::Option<int>{}};
		
		ASSERT_EQ(std::move(opt).some_or(5), 5);
	}
}

TEST(Option, None_3_some_or_else) {
	{
		const auto opt{orl::Option<int>{}};
		
		ASSERT_EQ(opt.some_or_else([] {
			return 5;
		}), 5);
	}
	{
		auto opt{orl::Option<int>{}};
		auto default_some{5};
		
		ASSERT_EQ(&opt.some_or_else([&]() -> int& {
			return default_some;
		}), &default_some);
	}
	{
		auto opt{orl::Option<int>{}};
		
		ASSERT_EQ(std::move(opt).some_or_else([] {
			return 5;
		}), 5);
	}
}

TEST(Option, None_4_some_or_ptr) {
	auto opt{orl::Option<int*>{}};
	
	int* value{opt.some_or_ptr(5)};
	ASSERT_EQ(*value, 5);
	
	delete value;
}

TEST(Option, None_5_map) {
	{
		const auto opt{orl::Option<int>{}};
		
		ASSERT_EQ(opt.map([](int const& some) {
			return char('a' + char(some));
		}).some_or('a'), 'a');
	}
	{
		auto opt{orl::Option<int>{}};
		
		ASSERT_EQ(opt.map([](int& some) {
			return char('a' + char(some));
		}).some_or('a'), 'a');
	}
	{
		auto opt{orl::Option<int>{}};
		
		ASSERT_EQ(std::move(opt).map([](int&& some) {
			return char('a' + char(some));
		}).some_or('a'), 'a');
	}
}

TEST(Option, None_6_and_then) {
	{
		const auto opt{orl::Option<int>{}};
		
		ASSERT_EQ(opt.and_then([](int const& some) {
			return orl::Option<char>{char('a' + char(some))};
		}).some_or('a'), 'a');
	}
	{
		auto opt{orl::Option<int>{}};
		
		ASSERT_EQ(opt.and_then([](int& some) {
			return orl::Option<char>{char('a' + char(some))};
		}).some_or('a'), 'a');
	}
	{
		auto opt{orl::Option<int>{}};
		
		ASSERT_EQ(std::move(opt).and_then([](int&& some) {
			return orl::Option<char>{char('a' + char(some))};
		}).some_or('a'), 'a');
	}
}

TEST(Option, None_7_except) {
	{
		const auto opt{orl::Option<int>{}};
		
		ASSERT_THROW(opt.except(), std::runtime_error);
		ASSERT_THROW(opt.except(std::runtime_error("")), std::runtime_error);
	}
	{
		auto opt{orl::Option<int>{}};
		
		ASSERT_THROW(opt.except(), std::runtime_error);
		ASSERT_THROW(opt.except(std::runtime_error("")), std::runtime_error);
	}
	{
		auto opt{orl::Option<int>{}};
		
		ASSERT_THROW(std::move(opt).except(), std::runtime_error);
	}
}

TEST(Option, None_8_optional) {
	{
		const auto opt{orl::Option<int>{}};
		
		ASSERT_EQ(opt.optional(), std::optional<orl::ref<int const&> >{});
	}
	{
		auto opt{orl::Option<int>{}};
		
		ASSERT_EQ(opt.optional(), std::optional<orl::ref<int&> >{});
	}
	{
		auto opt{orl::Option<int>{}};
		
		ASSERT_EQ(std::move(opt).optional(), std::optional<int>{});
	}
}

TEST(Option, None_9_range_based_for) {
	{
		const auto opt{orl::Option<int>{}};
		auto check{0};
		
		for(auto const& value: opt) {
			check += value;
		}
		
		ASSERT_EQ(check, 0);
	}
	{
		auto opt{orl::Option<int>{}};
		auto check{0};
		
		for(auto& value: opt) {
			check += value;
		}
		
		ASSERT_EQ(check, 0);
	}
}

TEST(Option, None_10_operator_and) {
	{
		{
			const auto first_opt{orl::Option<int>{}};
			const auto second_opt{orl::Option<int>{}};
			
			ASSERT_EQ(first_opt && second_opt, (orl::Option<std::tuple<int const&, int const&> >{}));
		}
		{
			auto first_opt{orl::Option<int>{}};
			auto second_opt{orl::Option<int>{}};
			
			ASSERT_EQ(first_opt && second_opt, (orl::Option<std::tuple<int&, int&> >{}));
		}
		{
			auto first_opt{orl::Option<int>{}};
			auto second_opt{orl::Option<int>{}};
			
			ASSERT_EQ(std::move(first_opt) && std::move(second_opt), (orl::Option<std::tuple<int, int> >{}));
		}
	}
	{
		{
			const auto first_opt{orl::Option<int>{}};
			const auto second_opt{orl::Option<int>{9}};
			
			ASSERT_EQ(first_opt && second_opt, (orl::Option<std::tuple<int const&, int const&> >{}));
		}
		{
			auto first_opt{orl::Option<int>{}};
			auto second_opt{orl::Option<int>{9}};
			
			ASSERT_EQ(first_opt && second_opt, (orl::Option<std::tuple<int&, int&> >{}));
		}
		{
			auto first_opt{orl::Option<int>{}};
			auto second_opt{orl::Option<int>{9}};
			
			ASSERT_EQ(std::move(first_opt) && std::move(second_opt), (orl::Option<std::tuple<int, int> >{}));
		}
	}
	{
		{
			const auto opt{orl::Option<int>{}};
			
			ASSERT_EQ(opt && false, orl::Option<int const&>{});
			ASSERT_EQ(opt && true, orl::Option<int const&>{});
		}
		{
			auto opt{orl::Option<int>{}};
			
			ASSERT_EQ(opt && false, orl::Option<int&>{});
			ASSERT_EQ(opt && true, orl::Option<int&>{});
		}
		{
			auto opt{orl::Option<int>{}};
			
			ASSERT_EQ(std::move(opt) && false, orl::Option<int>{});
			ASSERT_EQ(std::move(opt) && true, orl::Option<int>{});
		}
	}
}

TEST(Option, None_11_operator_or) {
	{
		{
			const auto first_opt{orl::Option<int>{}};
			const auto second_opt{orl::Option<int>{}};
			
			ASSERT_EQ(first_opt || second_opt, orl::Option<int const&>{});
		}
		{
			auto first_opt{orl::Option<int>{}};
			auto second_opt{orl::Option<int>{}};
			
			ASSERT_EQ(first_opt || second_opt, orl::Option<int&>{});
		}
		{
			auto first_opt{orl::Option<int>{}};
			auto second_opt{orl::Option<int>{}};
			
			ASSERT_EQ(std::move(first_opt) || std::move(second_opt), orl::Option<int>{});
		}
	}
	{
		{
			const auto first_opt{orl::Option<int>{}};
			const auto second_opt{orl::Option<int>{9}};
			
			ASSERT_EQ(first_opt || second_opt, orl::Option<int const&>{second_opt.except()});
		}
		{
			auto first_opt{orl::Option<int>{}};
			auto second_opt{orl::Option<int>{9}};
			
			ASSERT_EQ(first_opt || second_opt, orl::Option<int&>{second_opt.except()});
		}
		{
			auto first_opt{orl::Option<int>{}};
			auto second_opt{orl::Option<int>{9}};
			
			ASSERT_EQ(std::move(first_opt) || std::move(second_opt), orl::Option<int>{9});
		}
	}
}
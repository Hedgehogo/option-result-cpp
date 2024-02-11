#include <gtest/gtest.h>

#include <option_result/option_result.hpp>

class NonCopyable {
public:
	NonCopyable(NonCopyable const&) = delete;
	
	NonCopyable(NonCopyable&&) = default;
	
	NonCopyable() = default;
};

TEST(Option, Some_0) {
	auto value{NonCopyable{}};
	auto opt{orl::Option<NonCopyable>{std::move(value)}};
}

TEST(Option, Some_1_some) {
	{
		const auto opt{orl::Option<int>{7}};
		
		ASSERT_EQ(&opt.some(), &opt.except());
	}
	{
		auto opt{orl::Option<int>{7}};
		
		ASSERT_EQ(&opt.some(), &opt.except());
	}
	{
		auto opt{orl::Option<int>{7}};
		
		ASSERT_EQ(std::move(opt).some(), 7);
	}
}

TEST(Option, Some_2_is_some) {
	auto opt{orl::Option<int>{7}};
	
	ASSERT_TRUE(opt.is_some());
}

TEST(Option, Some_3_some_or) {
	{
		const auto opt{orl::Option<int>{7}};
		
		ASSERT_EQ(opt.some_or(5), 7);
	}
	{
		auto opt{orl::Option<int>{7}};
		auto default_some{5};
		
		ASSERT_EQ(&opt.some_or(default_some), &opt.except());
	}
	{
		auto opt{orl::Option<int>{7}};
		
		ASSERT_EQ(std::move(opt).some_or(5), 7);
	}
}

TEST(Option, Some_4_some_or_else) {
	{
		const auto opt{orl::Option<int>{7}};
		
		ASSERT_EQ(opt.some_or_else([]() -> int {
			return 5;
		}), 7);
	}
	{
		auto opt{orl::Option<int>{7}};
		auto default_some{5};
		
		ASSERT_EQ(&opt.some_or_else([&]() -> int& {
			return default_some;
		}), &opt.except());
	}
	{
		auto opt{orl::Option<int>{7}};
		
		ASSERT_EQ(std::move(opt).some_or_else([]() -> int {
			return 5;
		}), 7);
	}
}

TEST(Option, Some_5_some_or_ptr) {
	auto opt{orl::Option<int*>{new int{7}}};
	
	auto value{opt.some_or_ptr(5)};
	ASSERT_EQ(*value, 7);
	
	delete value;
}

TEST(Option, Some_6_map) {
	{
		const auto opt{orl::Option<int>{7}};
		
		ASSERT_EQ(opt.map([](int const& some) {
			return char('a' + char(some));
		}).some_or('a'), 'h');
	}
	{
		auto opt{orl::Option<int>{7}};
		
		ASSERT_EQ(opt.map([](int& some) {
			return char('a' + char(some));
		}).some_or('a'), 'h');
	}
	{
		auto opt{orl::Option<int>{7}};
		
		ASSERT_EQ(opt.map([](int some) {
			return char('a' + char(some));
		}).some_or('a'), 'h');
	}
}

TEST(Option, Some_7_except) {
	{
		const auto opt{orl::Option<int>{7}};
		
		ASSERT_EQ(opt.except(std::runtime_error("")), 7);
	}
	{
		auto opt{orl::Option<int>{7}};
		
		ASSERT_EQ(opt.except(std::runtime_error("")), 7);
	}
	{
		auto opt{orl::Option<int>{7}};
		
		ASSERT_EQ(std::move(opt).except(std::runtime_error("")), 7);
	}
}

TEST(Option, Some_8_optional) {
	{
		const auto opt{orl::Option<int>{7}};
		
		ASSERT_EQ(opt.optional(), std::optional<orl::ref<int const&> >{opt.except()});
	}
	{
		auto opt{orl::Option<int>{7}};
		
		ASSERT_EQ(opt.optional(), std::optional<orl::ref<int&> >{opt.except()});
	}
	{
		auto opt{orl::Option<int>{7}};
		
		ASSERT_EQ(std::move(opt).optional(), std::optional<int>{7});
	}
}

TEST(Option, None_9_range_based_for) {
	{
		const auto opt{orl::Option<int>{7}};
		auto check{0};
		
		for(auto const& value: opt) {
			check += value;
		}
		
		ASSERT_EQ(check, 7);
	}
	{
		auto opt{orl::Option<int>{7}};
		auto check{0};
		
		for(auto& value: opt) {
			check += value;
		}
		
		ASSERT_EQ(check, 7);
	}
}

TEST(Option, Some_10_operator_bool) {
	auto opt{orl::Option<int>{7}};
	
	ASSERT_TRUE(opt);
}

TEST(Option, Some_11_operator_and) {
	{
		{
			const auto first_opt{orl::Option<int>{7}};
			const auto second_opt{orl::Option<int>{}};
			
			ASSERT_EQ(first_opt && second_opt, (orl::Option<std::tuple<int const&, int const&> >{}));
		}
		{
			auto first_opt{orl::Option<int>{7}};
			auto second_opt{orl::Option<int>{}};
			
			ASSERT_EQ(first_opt && second_opt, (orl::Option<std::tuple<int&, int&> >{}));
		}
		{
			auto first_opt{orl::Option<int>{7}};
			auto second_opt{orl::Option<int>{}};
			
			ASSERT_EQ(std::move(first_opt) && std::move(second_opt), (orl::Option<std::tuple<int, int> >{}));
		}
	}
	{
		{
			const auto first_opt{orl::Option<int>{7}};
			const auto second_opt{orl::Option<int>{9}};
			
			ASSERT_EQ(first_opt && second_opt, (orl::Option<std::tuple<int const&, int const&> >{{first_opt.except(), second_opt.except()}}));
		}
		{
			auto first_opt{orl::Option<int>{7}};
			auto second_opt{orl::Option<int>{9}};
			
			ASSERT_EQ(first_opt && second_opt, (orl::Option<std::tuple<int&, int&> >{{first_opt.except(), second_opt.except()}}));
		}
		{
			auto first_opt{orl::Option<int>{7}};
			auto second_opt{orl::Option<int>{9}};
			
			ASSERT_EQ(std::move(first_opt) && std::move(second_opt), (orl::Option<std::tuple<int, int> >{{7, 9}}));
		}
	}
}

TEST(Option, Some_12_operator_or) {
	{
		{
			const auto first_opt{orl::Option<int>{7}};
			const auto second_opt{orl::Option<int>{}};
			
			ASSERT_EQ(first_opt || second_opt, orl::Option<int const&>{first_opt.except()});
		}
		{
			auto first_opt{orl::Option<int>{7}};
			auto second_opt{orl::Option<int>{}};
			
			ASSERT_EQ(first_opt || second_opt, orl::Option<int&>{first_opt.except()});
		}
		{
			auto first_opt{orl::Option<int>{7}};
			auto second_opt{orl::Option<int>{}};
			
			ASSERT_EQ(std::move(first_opt) || std::move(second_opt), orl::Option<int>{7});
		}
	}
	{
		{
			const auto first_opt{orl::Option<int>{7}};
			const auto second_opt{orl::Option<int>{9}};
			
			ASSERT_EQ(first_opt || second_opt, orl::Option<int const&>{first_opt.except()});
		}
		{
			auto first_opt{orl::Option<int>{7}};
			auto second_opt{orl::Option<int>{9}};
			
			ASSERT_EQ(first_opt || second_opt, orl::Option<int&>{first_opt.except()});
		}
		{
			auto first_opt{orl::Option<int>{7}};
			auto second_opt{orl::Option<int>{9}};
			
			ASSERT_EQ(std::move(first_opt) || std::move(second_opt), orl::Option<int>{7});
		}
	}
}
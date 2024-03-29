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
		auto const opt{orl::Option<int>{7}};
		
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
		auto const opt{orl::Option<int>{7}};
		
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
		auto const opt{orl::Option<int>{7}};
		
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
		auto const opt{orl::Option<int>{7}};
		
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

TEST(Option, None_7_and_then) {
	{
		auto const opt{orl::Option<int>{7}};
		
		ASSERT_EQ(opt.and_then([](int const& some) {
			return orl::Option<char>{char('a' + char(some))};
		}).some_or('a'), 'h');
	}
	{
		auto opt{orl::Option<int>{7}};
		
		ASSERT_EQ(opt.and_then([](int& some) {
			return orl::Option<char>{char('a' + char(some))};
		}).some_or('a'), 'h');
	}
	{
		auto opt{orl::Option<int>{7}};
		
		ASSERT_EQ(std::move(opt).and_then([](int&& some) {
			return orl::Option<char>{char('a' + char(some))};
		}).some_or('a'), 'h');
	}
}

TEST(Option, Some_8_except) {
	{
		auto const opt{orl::Option<int>{7}};
		
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

TEST(Option, Some_9_optional) {
	{
		auto const opt{orl::Option<int>{7}};
		
		ASSERT_EQ(opt.optional(), std::optional<orl::Ref<int const&> >{opt.except()});
	}
	{
		auto opt{orl::Option<int>{7}};
		
		ASSERT_EQ(opt.optional(), std::optional<orl::Ref<int&> >{opt.except()});
	}
	{
		auto opt{orl::Option<int>{7}};
		
		ASSERT_EQ(std::move(opt).optional(), std::optional<int>{7});
	}
}

TEST(Option, None_10_range_based_for) {
	{
		auto const opt{orl::Option<int>{7}};
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

TEST(Option, Some_11_operator_and) {
	{
		{
			{
				auto const first_opt{orl::Option<int>{7}};
				auto const second_opt{orl::Option<int>{}};
				
				ASSERT_EQ(first_opt && second_opt, (orl::Option<std::tuple<int const&, int const&> >{}));
			}
			{
				auto const first_opt{orl::Option<int>{7}};
				auto second_opt{orl::Option<int>{}};
				
				ASSERT_EQ(first_opt && second_opt, (orl::Option<std::tuple<int const&, int&> >{}));
			}
			{
				auto const first_opt{orl::Option<int>{7}};
				auto second_opt{orl::Option<int>{}};
				
				ASSERT_EQ(first_opt && std::move(second_opt), (orl::Option<std::tuple<int const&, int> >{}));
			}
		}
		{
			{
				auto first_opt{orl::Option<int>{7}};
				auto const second_opt{orl::Option<int>{}};
				
				ASSERT_EQ(first_opt && second_opt, (orl::Option<std::tuple<int&, int const&> >{}));
			}
			{
				auto first_opt{orl::Option<int>{7}};
				auto second_opt{orl::Option<int>{}};
				
				ASSERT_EQ(first_opt && second_opt, (orl::Option<std::tuple<int&, int&> >{}));
			}
			{
				auto first_opt{orl::Option<int>{7}};
				auto second_opt{orl::Option<int>{}};
				
				ASSERT_EQ(first_opt && std::move(second_opt), (orl::Option<std::tuple<int&, int> >{}));
			}
		}
		{
			{
				auto first_opt{orl::Option<int>{7}};
				auto const second_opt{orl::Option<int>{}};
				
				ASSERT_EQ(std::move(first_opt) && second_opt, (orl::Option<std::tuple<int, int const&> >{}));
			}
			{
				auto first_opt{orl::Option<int>{7}};
				auto second_opt{orl::Option<int>{}};
				
				ASSERT_EQ(std::move(first_opt) && second_opt, (orl::Option<std::tuple<int, int&> >{}));
			}
			{
				auto first_opt{orl::Option<int>{7}};
				auto second_opt{orl::Option<int>{}};
				
				ASSERT_EQ(std::move(first_opt) && std::move(second_opt), (orl::Option<std::tuple<int, int> >{}));
			}
		}
	}
	{
		{
			{
				auto const first_opt{orl::Option<int>{7}};
				auto const second_opt{orl::Option<int>{9}};
				
				ASSERT_EQ(first_opt && second_opt, (orl::Option<std::tuple<int const&, int const&> >{{first_opt.except(), second_opt.except()}}));
			}
			{
				auto const first_opt{orl::Option<int>{7}};
				auto second_opt{orl::Option<int>{9}};
				
				ASSERT_EQ(first_opt && second_opt, (orl::Option<std::tuple<int const&, int&> >{{first_opt.except(), second_opt.except()}}));
			}
			{
				auto const first_opt{orl::Option<int>{7}};
				auto second_opt{orl::Option<int>{9}};
				
				ASSERT_EQ(first_opt && std::move(second_opt), (orl::Option<std::tuple<int const&, int> >{{first_opt.except(), 9}}));
			}
		}
		{
			{
				auto first_opt{orl::Option<int>{7}};
				auto const second_opt{orl::Option<int>{9}};
				
				ASSERT_EQ(first_opt && second_opt, (orl::Option<std::tuple<int&, int const&> >{{first_opt.except(), second_opt.except()}}));
			}
			{
				auto first_opt{orl::Option<int>{7}};
				auto second_opt{orl::Option<int>{9}};
				
				ASSERT_EQ(first_opt && second_opt, (orl::Option<std::tuple<int&, int&> >{{first_opt.except(), second_opt.except()}}));
			}
			{
				auto first_opt{orl::Option<int>{7}};
				auto second_opt{orl::Option<int>{9}};
				
				ASSERT_EQ(first_opt && std::move(second_opt), (orl::Option<std::tuple<int&, int> >{{first_opt.except(), 9}}));
			}
		}
		{
			{
				auto first_opt{orl::Option<int>{7}};
				auto const second_opt{orl::Option<int>{9}};
				
				ASSERT_EQ(std::move(first_opt) && second_opt, (orl::Option<std::tuple<int, int const&> >{{7, second_opt.except()}}));
			}
			{
				auto first_opt{orl::Option<int>{7}};
				auto second_opt{orl::Option<int>{9}};
				
				ASSERT_EQ(std::move(first_opt) && second_opt, (orl::Option<std::tuple<int, int&> >{{7, second_opt.except()}}));
			}
			{
				auto first_opt{orl::Option<int>{7}};
				auto second_opt{orl::Option<int>{9}};
				
				ASSERT_EQ(std::move(first_opt) && std::move(second_opt), (orl::Option<std::tuple<int, int> >{{7, 9}}));
			}
		}
	}
	{
		{
			auto const opt{orl::Option<int>{7}};
			
			ASSERT_EQ(opt && false, orl::Option<int const&>{});
			ASSERT_EQ(false && opt, orl::Option<int const&>{});
			ASSERT_EQ(opt && true, orl::Option<int const&>{opt.except()});
			ASSERT_EQ(true && opt, orl::Option<int const&>{opt.except()});
		}
		{
			auto opt{orl::Option<int>{7}};
			
			ASSERT_EQ(opt && false, orl::Option<int&>{});
			ASSERT_EQ(false && opt, orl::Option<int&>{});
			ASSERT_EQ(opt && true, orl::Option<int&>{opt.except()});
			ASSERT_EQ(true && opt, orl::Option<int&>{opt.except()});
		}
		{
			auto opt = [] {
				return orl::Option<int>{7};
			};
			
			ASSERT_EQ(opt() && false, orl::Option<int>{});
			ASSERT_EQ(false && opt(), orl::Option<int>{});
			ASSERT_EQ(opt() && true, orl::Option<int>{7});
			ASSERT_EQ(true && opt(), orl::Option<int>{7});
		}
	}
}

TEST(Option, Some_12_operator_or) {
	{
		{
			auto const first_opt{orl::Option<int>{7}};
			auto const second_opt{orl::Option<int>{}};
			
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
			auto const first_opt{orl::Option<int>{7}};
			auto const second_opt{orl::Option<int>{9}};
			
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
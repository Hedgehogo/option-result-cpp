#include <gtest/gtest.h>

#include <option_result/Error.hpp>

class FirstError : public orl::BaseException {
public:
	std::string get_description() const override {
		return std::string{"First"};
	}
};

class SecondError : public orl::BaseException {
public:
	std::string get_description() const override {
		return std::string{"Second"};
	}
};

TEST(Error, First) {
	orl::Error<FirstError, SecondError> error{FirstError{}};
	
	ASSERT_EQ(error.get_note(), std::string{"0: "});
	ASSERT_EQ(error.get_description(), std::string{"First"});
	ASSERT_EQ(error.get_full_description(), std::string{"0: First"});
	ASSERT_EQ(error.common<orl::BaseException>().get_full_description(), std::string{"First"});
}

TEST(Error, Second) {
	orl::Error<FirstError, SecondError> error{SecondError{}};
	
	ASSERT_EQ(error.get_note(), std::string{"1: "});
	ASSERT_EQ(error.get_description(), std::string{"Second"});
	ASSERT_EQ(error.get_full_description(), std::string{"1: Second"});
	ASSERT_EQ(error.common<orl::BaseException>().get_full_description(), std::string{"Second"});
}

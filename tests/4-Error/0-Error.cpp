#include <gtest/gtest.h>

#include <option_result/Error.hpp>

class FirstError : public orl::BaseException {
public:
	std::string getDescription() const override {
		return std::string{"First"};
	}
};

class SecondError : public orl::BaseException {
public:
	std::string getDescription() const override {
		return std::string{"Second"};
	}
};

TEST(Error, First) {
	orl::Error<FirstError, SecondError> error{FirstError{}};
	
	ASSERT_EQ(error.getNote(), std::string{"0: "});
	ASSERT_EQ(error.getDescription(), std::string{"First"});
	ASSERT_EQ(error.getFullDescription(), std::string{"0: First"});
}

TEST(Error, Second) {
	orl::Error<FirstError, SecondError> error{SecondError{}};
	
	ASSERT_EQ(error.getNote(), std::string{"1: "});
	ASSERT_EQ(error.getDescription(), std::string{"Second"});
	ASSERT_EQ(error.getFullDescription(), std::string{"1: Second"});
}

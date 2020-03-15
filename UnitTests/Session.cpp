
#include<fstream>
#include <cstdio>

#include "pch.h"
#include "CppUnitTest.h"
#define private public
#include "..\src\Session.h"
#include "..\src\Session.cpp"

#define METHOD_CLASS(methodClass) TEST_METHOD_ATTRIBUTE(L"MethodClass", methodClass)

#define TEST_METHOD_SIGNATURE(methodClass, methodName)  BEGIN_TEST_METHOD_ATTRIBUTE (methodName)\
														METHOD_CLASS(methodClass)\
														END_TEST_METHOD_ATTRIBUTE()\
														TEST_METHOD(methodName)


#define WRITE_TO_DEFAULT_SESSION_STRING "This is a simple\nstring\n\t\tHi!\n"
#define SAVE_ONCE_STRING "This is a simple\nstring\n\t\tHi!\n"
#define SAVE_ONCE_FILE "save_once.txt"
#define SAVE_TWICE_STRING_1 "First save\n"
#define SAVE_TWICE_STRING_2 "Second save\n"
#define SAVE_TWICE_FILE "save_twice.txt"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace pl = performance_log;

namespace UnitTests {
	TEST_CLASS(Session) {
public:

#pragma region write

	TEST_METHOD_SIGNATURE(L"write", write_to_default_session) {
		pl::Session session;
		std::string measurement = WRITE_TO_DEFAULT_SESSION_STRING;
		session.write(measurement);

		Assert::IsTrue(session.measurements == WRITE_TO_DEFAULT_SESSION_STRING);
	}

#pragma endregion


#pragma region save

	TEST_METHOD_SIGNATURE(L"save", save_once) {
		{
		pl::Session session {SAVE_ONCE_FILE};
		session.measurements = SAVE_ONCE_STRING;
		session.save();
		}

		std::ifstream previoulsySaved {SAVE_ONCE_FILE};
		std::string measurements((std::istreambuf_iterator<char>(previoulsySaved)), std::istreambuf_iterator<char>());

		Assert::IsTrue(measurements == SAVE_ONCE_STRING);
	}


	TEST_METHOD_SIGNATURE(L"save", save_twice) {
		{
		pl::Session session {SAVE_TWICE_FILE};
		session.measurements = SAVE_TWICE_STRING_1;
		session.save();
		session.measurements = SAVE_TWICE_STRING_2;
		session.save();
		}

		std::ifstream previoulsySaved {SAVE_TWICE_FILE};
		std::string measurements((std::istreambuf_iterator<char>(previoulsySaved)), std::istreambuf_iterator<char>());
		std::string test = SAVE_TWICE_STRING_1 SAVE_TWICE_STRING_2;
		Assert::IsTrue(measurements == SAVE_TWICE_STRING_1 SAVE_TWICE_STRING_2);
	}

#pragma endregion



	TEST_METHOD_CLEANUP(clean_up) {
		std::remove(SAVE_ONCE_FILE);
		std::remove(SAVE_TWICE_FILE);
	}

		};
	}

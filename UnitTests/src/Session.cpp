#include<fstream>

#include "..\pch.h"
#include "CppUnitTest.h"
#define private public
#include "..\..\src\Session.h"
#include "..\..\src\Session.cpp"

#define METHOD_CLASS(methodClass) TEST_METHOD_ATTRIBUTE(L"MethodClass", methodClass)

#define TEST_METHOD_SIGNATURE(methodClass, methodName)  BEGIN_TEST_METHOD_ATTRIBUTE (methodName)\
														METHOD_CLASS(methodClass)\
														END_TEST_METHOD_ATTRIBUTE()\
														TEST_METHOD(methodName)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace pl = PerformanceLog;

namespace UnitTests {
	TEST_CLASS(Session) {
public:

#pragma region write

	TEST_METHOD_SIGNATURE(L"write", write_to_default_session) {
		pl::Session session;
		std::string measurement = "This is a simple\nstring\n\t\tHi!\n";
		session.write(measurement);

		Assert::IsTrue(session.measurements == "This is a simple\nstring\n\t\tHi!\n");
		}


	TEST_METHOD_SIGNATURE(L"write", check_input_exits_empty) {
		pl::Session session;
		std::string measurement = "This is a simple\nstring\n\t\tHi!\n";
		session.write(measurement);

		Assert::IsTrue(measurement.length() == 0);
		}


#pragma endregion


#pragma region save

	TEST_METHOD_SIGNATURE(L"save", save) {
			{
			pl::Session session {"testSave.txt"};
			session.measurements = "This is a simple\nstring\n\t\tHi!\n";
			session.save();
			}

			std::ifstream previoulsySaved {"testSave.txt"};
			std::string measurements((std::istreambuf_iterator<char>(previoulsySaved)), std::istreambuf_iterator<char>());

			Assert::IsTrue(measurements == "This is a simple\nstring\n\t\tHi!\n");
		}




#pragma endregion

		};
	}

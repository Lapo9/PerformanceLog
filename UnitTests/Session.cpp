#include<fstream>

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

#pragma endregion


#pragma region save

	TEST_METHOD_SIGNATURE(L"save", save_once) {
			{
			pl::Session session {"save_once.txt"};
			session.measurements = "This is a simple\nstring\n\t\tHi!\n";
			session.save();
			}

			std::ifstream previoulsySaved {"save_once.txt"};
			std::string measurements((std::istreambuf_iterator<char>(previoulsySaved)), std::istreambuf_iterator<char>());

			Assert::IsTrue(measurements == "This is a simple\nstring\n\t\tHi!\n");
			//TODO dovrebbe cancellare il file per il futuro
		}


	TEST_METHOD_SIGNATURE(L"save", save_twice) {
			{
			pl::Session session {"save_twice.txt"};
			session.measurements = "First save\n";
			session.save();
			session.measurements = "Second save\n";
			session.save();
			}

			std::ifstream previoulsySaved {"save_twice.txt"};
			std::string measurements((std::istreambuf_iterator<char>(previoulsySaved)), std::istreambuf_iterator<char>());

			Assert::IsTrue(measurements == "First save\nSecond save\n");
			//TODO dovrebbe cancellare il file per il futuro
		}




#pragma endregion

		};
	}

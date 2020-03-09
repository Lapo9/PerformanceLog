#include "pch.h"
#include "CppUnitTest.h"

#define METHOD_CLASS(methodClass) TEST_METHOD_ATTRIBUTE(L"MethodClass", methodClass)

#define TEST_METHOD_SIGNATURE(methodClass, methodName)  BEGIN_TEST_METHOD_ATTRIBUTE (methodName)\
															METHOD_CLASS(methodClass)\
														END_TEST_METHOD_ATTRIBUTE()\
														TEST_METHOD(methodName)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(SessionC){
	public:

	#pragma region thisMethod
		TEST_METHOD_SIGNATURE(L"thisMethod", method){
		}
	#pragma endregion thisMethod

	};
}

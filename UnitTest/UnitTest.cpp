#include "pch.h"
#include "CppUnitTest.h"
#include "..\Lab12_4.4\main.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual((int)typeTriangle::rivnobed, (int)getType({ 0, 0 }, { 1, 1 }, { 0, 1 }));
		}
	};
}

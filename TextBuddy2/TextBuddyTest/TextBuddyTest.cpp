#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TextBuddyTest {		
	TEST_CLASS(TextBuddyTest) {
	public:
		
		TEST_METHOD(TestDisplayText) {
			TextBuddy* tb = new TextBuddy;
			tb->addTextForTest("test case 1");
			tb->addTextForTest("test case 2");
			tb->addTextForTest("test case 3");
			string expectedDisplay = "1. test case 1\n2. test case 2\n3. test case 3\n\n";
			Assert::AreEqual(expectedDisplay, tb->displayText());
		}

		TEST_METHOD(TestAddText) {
/*			TextBuddy* tb = new TextBuddy;
			
			string actual1 = tb->addText("test test test 1");
			string actual2 = tb->addText("test test test 2");
			string expected1 = "added to mytextfile.txt: \"test test test 1\"";
			string expected2 = "added to mytextfile.txt: \"test test test 2\"";
			string expectedDisplay = "1. test test test 1\n2. test test test 2\n\n";
			
			Assert::AreEqual(expected1, actual1);
			Assert::AreEqual(expected2, actual2);
			Assert::AreEqual(expectedDisplay, tb->displayText());
*/		}

		TEST_METHOD(TestDeleteText) {
			//add, display required
		}
	};
}
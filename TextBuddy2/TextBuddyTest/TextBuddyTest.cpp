#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TextBuddyTest {		
	TEST_CLASS(TextBuddyTest) {
	public:
		
		TEST_METHOD(TestSearchText) {
			TextBuddy* tb = new TextBuddy;

			tb->addTextForTest("brown fox");
			tb->addTextForTest("red fox");
			tb->addTextForTest("white wolf");
			tb->addTextForTest("blue fox");

			string expectedDisplay1 = "1. brown fox\n2. red fox\n3. blue fox\n";
			string expectedDisplay2 = "1. white wolf\n";
			Assert::AreEqual(expectedDisplay1, tb->searchText("fox"));
			Assert::AreEqual(expectedDisplay2, tb->searchText("wolf"));
		}

		TEST_METHOD(TestSortText) {
			TextBuddy* tb = new TextBuddy;

			tb->addTextForTest("ab");
			tb->addTextForTest("aa");
			tb->addTextForTest("bb");
			tb->addTextForTest("ba");

			string returnValue = tb->sortText();
			string expectedDisplay = "1. aa\n2. ab\n3. ba\n4. bb\n";
			Assert::AreEqual(expectedDisplay, tb->displayText());
		}
	};
}
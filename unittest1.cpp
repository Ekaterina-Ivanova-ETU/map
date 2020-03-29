#include "stdafx.h"
#include "CppUnitTest.h"
#include "../map/map.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	private:
		map<char, int> test_map, empty_map;

	public:

		TEST_METHOD_INITIALIZE(init)
		{
			test_map.insert('o', 15);
			test_map.insert('c', 3);
			test_map.insert('v', 22);
			test_map.insert('b', 2);
			test_map.insert('a', 1);
			test_map.insert('z', 27);
			test_map.insert('g', 7);
			test_map.insert('j', 10);
			test_map.insert('r', 18);
			test_map.insert('y', 26);
		}

		TEST_METHOD(_insert)
		{
			test_map.insert('l', 12);
			Assert::AreEqual(test_map.find('l'), 12);
			Assert::AreEqual((int)test_map.get_size(), 11);

			test_map.insert('s', 19);
			Assert::AreEqual(test_map.find('s'), 19);
			Assert::AreEqual((int)test_map.get_size(), 12);
		}

		TEST_METHOD(insert_exception)
		{
			try
			{
				test_map.insert('a', 0);
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual("A node with the specified key is already contained in the map.", ex.what());
			}
		}

		TEST_METHOD(_remove)
		{
			test_map.remove('a');
			Assert::AreEqual((int)test_map.get_size(), 9);

			test_map.remove('j');
			Assert::AreEqual((int)test_map.get_size(), 8);

			test_map.remove('y');
			Assert::AreEqual((int)test_map.get_size(), 7);
		}

		TEST_METHOD(remove_exception)
		{
			try
			{
				empty_map.remove('a');
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual("Map is empty.", ex.what());
			}

			try
			{
				test_map.remove('f');
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual("This element isn't in the map.", ex.what());
			}
		}

		TEST_METHOD(_find)
		{
			Assert::IsTrue(test_map.find('g'));
			Assert::IsTrue(test_map.find('c'));
			Assert::IsTrue(test_map.find('o'));
		}

		TEST_METHOD(find_exception)
		{
			try
			{
				empty_map.find('a');
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual("Map is empty.", ex.what());
			}

			try
			{
				test_map.find('f');
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual("This element isn't in the map.", ex.what());
			}
		}

		TEST_METHOD(_clear)
		{
			test_map.clear();
			Assert::AreEqual((int)test_map.get_size(), 0);
		}

		TEST_METHOD(clear_exception)
		{
			try
			{
				empty_map.clear();
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual("Map is empty.", ex.what());
			}
		}

		TEST_METHOD(print_exception)
		{
			try
			{
				empty_map.print();
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual("Map is empty.", ex.what());
			}
		}
	};
}
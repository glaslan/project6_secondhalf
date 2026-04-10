#include "pch.h"
#include "CppUnitTest.h"
#include "../Client/FileReader.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(FileReaderTests)
	{
	public:

		TEST_METHOD(TEST_FR_FUNC_0001_ReadLineFromFile)
		{ 
			std::string test_filename = "./fr_oneLine_test_file.txt";
			std::ofstream test_file(test_filename);
			test_file << "Project IV is awesome!" << std::endl;
			test_file.close();

			Reader file_reader(test_filename);
			Assert::IsTrue(file_reader.IsOpen());
			std::string line = file_reader.ReadLine();
			Assert::AreEqual(std::string("Project IV is awesome!"), line);
		}

	};
}
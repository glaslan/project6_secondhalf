#include "pch.h"
#include "CppUnitTest.h"
#include "../Server/Logger.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		
		TEST_METHOD(logger_creates_file)
		{
			std::string logger_path = "./logger.txt";
			std::string error_path = "./error_logger.txt";
			// Global namespace to stop colission with Microsoft's Logger
			::Logger* logger_ptr = new ::Logger(logger_path, error_path);
			Assert::IsNotNull(logger_ptr);
			delete logger_ptr;
		}
	};
}

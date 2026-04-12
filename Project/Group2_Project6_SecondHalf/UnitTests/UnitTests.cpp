
#include "CppUnitTest.h"

#include "constants.h"
#include "Parser.h"
#include "Serializer.h"
#include "Deserializer.h"
#include "FileReader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		
		TEST_METHOD(TEST_SE_FUNC_0001)
		{
			Serializer serializer;
			float data = 34.677777;
			serializer.SerializeFuel(data);

			float actual;
			memcpy(&actual, serializer.GetBuffer()+PKT_OFFSET_TO_FUEL, sizeof(float));

			Assert::AreEqual(data, actual);
		}

		TEST_METHOD(TEST_SE_FUNC_0002)
		{
			Serializer serializer;
			unsigned char flag = FLAG_CONTINUE;
			serializer.SerializeFlag(flag);

			unsigned char actual;
			memcpy(&actual, serializer.GetBuffer(), sizeof(unsigned char));

			Assert::AreEqual(flag, actual);
		}

		TEST_METHOD(TEST_SE_FUNC_0003)
		{
			Serializer serializer;
			unsigned char flag = FLAG_END;
			serializer.SerializeFlag(flag);

			unsigned char actual;
			memcpy(&actual, serializer.GetBuffer(), sizeof(unsigned char));

			Assert::AreEqual(flag, actual);
		}

		TEST_METHOD(TEST_SE_FUNC_0004)
		{
			Serializer serializer;
			serializer.SerializeEndPacket();

			unsigned char expected = FLAG_END;
			unsigned char actual;
			memcpy(&actual, serializer.GetBuffer(), sizeof(unsigned char));

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TEST_SE_FUNC_0005)
		{
			Serializer serializer;
			std::string date = "4_12_2025 7:45:25";
			std::string expected = "041220254500725";

			serializer.SerializeDatetime(date);

			int comparison = memcmp(expected.c_str(), serializer.GetBuffer()+1, expected.length());

			Assert::AreEqual(0, comparison);
		}

		TEST_METHOD(TEST_SE_FUNC_0006)
		{
			Serializer serializer;
			std::string date = "4_12_2025 17:45:25";
			std::string expected = "041220254510525";

			serializer.SerializeDatetime(date);

			int comparison = memcmp(expected.c_str(), serializer.GetBuffer() + 1, expected.length());

			Assert::AreEqual(0, comparison);
		}

		TEST_METHOD(TEST_SE_ITGR_0001)
		{
			Serializer serializer;
			Parser parser;
			Reader reader("FlightData/katl-kefd-B737-700.txt");

			std::string line = reader.ReadLine();

			std::vector<std::string> vals = parser.split(line, ',');

			// first line: 3_3_2023 14:53:21,4564.466309
			std::string expected = "030320235310221";
			float fuel = 4564.466309;

			serializer.Serialize(vals.at(1), std::stof(vals.at(2)));

			int comparison = memcmp(expected.c_str(), serializer.GetBuffer() + 1, expected.length());

			float actual;
			memcpy(&actual, serializer.GetBuffer() + PKT_OFFSET_TO_FUEL, sizeof(float));

			Assert::AreEqual(fuel, actual);
			Assert::AreEqual(0, comparison);
		}

		TEST_METHOD(TEST_PA_FUNC_0001)
		{
			Parser parser;
			std::string expected = "Hello,World";

			std::vector<std::string> vals = parser.split(expected, ',');

			Assert::AreEqual(std::string("Hello"), vals.at(0));
			Assert::AreEqual(std::string("World"), vals.at(1));
		}

		TEST_METHOD(TEST_PA_FUNC_0002)
		{
			Parser parser;
			std::string expected = ":12:789";

			std::vector<std::string> vals = parser.split(expected, ':');

			Assert::AreEqual(std::string(""), vals.at(0));
			Assert::AreEqual(std::string("12"), vals.at(1));
			Assert::AreEqual(std::string("789"), vals.at(2));
		}

		TEST_METHOD(TEST_DE_FUNC_0001)
		{
			Deserializer ds;
			char buffer[] = "1051020255600924\0\0 @";
			ds.DeserializeBuffer(buffer);
			float fuel = 2.5;
			int flag = '1';

			Assert::AreEqual(ds.GetDatetime(), std::string("05/10/2025 AM 09:56:24"));
			Assert::AreEqual(ds.GetFuel(), fuel);
			Assert::AreEqual(ds.GetFlag(), flag);
		}

		TEST_METHOD(TEST_DE_ITGR_0001)
		{
			Deserializer ds;
			Serializer se;
			float fuel = 12.123456;
			se.Serialize("07_12_2022 14:24:36", fuel);

			ds.DeserializeBuffer(se.GetBuffer());

			Assert::AreEqual(ds.GetDatetime(), std::string("07/12/2022 PM 02:24:36"));
			Assert::AreEqual(ds.GetFuel(), fuel);
			Assert::AreEqual(ds.GetFlag(), 1);
		}


	};
}

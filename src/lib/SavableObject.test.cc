/**
 * @file SavableObject.test.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "SavableObject.h"
#include <boost/test/unit_test.hpp>
#include <filesystem>

BOOST_AUTO_TEST_CASE(test_SavableObject) {

	class TestClass : public SavableObject {
	public:

		int number = 0;
		std::string text = "";

		void readFromFile(const std::function<void()> &onFailed) {
			loadObjectFromFile(onFailed);
		}

		[[nodiscard]] std::filesystem::path getSavePath() const override {
			return std::filesystem::temp_directory_path() / "test_SavableObject";
		}

		[[nodiscard]] json toJSON() const override {
			json json_obj;

			json_obj["number"] = number;
			json_obj["text"] = text;

			return json_obj;
		}
	protected:
		void acceptState(json &json_obj) override {
			number = assertGetNumber(json_obj["number"]);
			text = assertGetString(json_obj["text"]);
		}
	};

	{
		auto obj = TestClass();

		// usuwamy plik na wszelki wypadek
		std::filesystem::remove(obj.getSavePath());

		obj.number = 3;
		obj.text = "test";
		obj.saveObjectToFile();
	}

	{
		auto obj = TestClass();

		bool failed = false;

		obj.readFromFile([&] { failed = true; });

		BOOST_CHECK(!failed);
		BOOST_CHECK(obj.number == 3);
		BOOST_CHECK(obj.text == "test");


		// usuwamy plik by śmieci nie zostawić
		std::filesystem::remove(obj.getSavePath());
	}
}
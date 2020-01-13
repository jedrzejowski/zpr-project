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
		boost::filesystem::path getSavePath(AppSettings &app_settings) const override {
			return boost::filesystem::path();
		}
		json toJSON() const override {
			return json();
		}
	protected:
		void acceptState(json &json_obj) override {
		}
	};
}
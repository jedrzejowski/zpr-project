/**
 * @file SaveableObject.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <boost/filesystem/path.hpp>
#include "json.hpp"
#include "AppSettings.h"

using json = nlohmann::json;

class SaveableObject {
private:
	bool need_save = true;

protected:
	virtual void acceptState(json &json_obj) = 0;
	void setNeedSave(bool needSave);
	void readObject();
public:
	[[nodiscard]] virtual boost::filesystem::path getSavePath(AppSettings &app_settings) const = 0;
	virtual json toJSON() const = 0;

	void saveObject() const;
	void saveObjectIfNeed() const;
	[[nodiscard]] virtual bool isNeedSave() const;
};




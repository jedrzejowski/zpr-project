/**
 * @file SavableObject.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <boost/filesystem/path.hpp>
#include "json.hpp"
#include "AppSettings.h"
#include "src/OpenGL.h"

using json = nlohmann::json;

class SavableObject {
private:
	bool need_save = true;

protected:
	virtual void acceptState(json &json_obj) = 0;
	void setNeedSave(bool needSave);
	void loadObjectFromFile();

	bool hasSavedFile();
public:
	[[nodiscard]] virtual boost::filesystem::path getSavePath(AppSettings &app_settings = AppSettings::get()) const = 0;
	[[nodiscard]] virtual json toJSON() const = 0;

	void saveObjectToFile() const;
	[[nodiscard]] virtual bool isNeedSave() const;

	static json& assertGetNumber(json& maybe_number);
	static glm::vec3 assertGetVec3(json& maybe_vector);
};




/**
 * @file SavableObject.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <filesystem>
#include "json.hpp"
#include "AppSettings.h"
#include "src/OpenGL.h"

using json = nlohmann::json;

class SavableObject {
private:
	bool need_save = true;
	bool is_deleted = false;

protected:
	virtual void acceptState(json &json_obj) = 0;
	void setNeedSave(bool needSave);
	void loadObjectFromFile(const std::function<void()>& onFailed = []{});

	bool hasSavedFile();


public:
	[[nodiscard]] virtual std::filesystem::path getSavePath(AppSettings &app_settings = AppSettings::get()) const = 0;
	[[nodiscard]] virtual json toJSON() const = 0;

	void saveObjectToFile();
	[[nodiscard]] virtual bool isNeedSave() const;

	static json& assertGetNumber(json& maybe_number);
	static glm::vec3 assertGetVec3(json& maybe_vector);
	static std::string assertGetString(json& maybe_string);

	bool isDeleted() const;
	void deleteThisObjectAsFile();

};




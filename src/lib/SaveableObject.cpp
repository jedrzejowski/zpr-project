/**
 * @file SaveableObject.cpp
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "SaveableObject.h"

bool SaveableObject::isNeedSave() const {
	return need_save;
}

void SaveableObject::setNeedSave(bool needSave) {
	need_save = needSave;
}

void SaveableObject::saveObject() const {
	static auto &app_settings = AppSettings::get();

	app_settings.saveJSON(getSavePath(app_settings), toJSON());
}

void SaveableObject::readObject() {
	static auto &app_settings = AppSettings::get();

	auto json_data = app_settings.loadJSON(getSavePath(app_settings));

	acceptState(json_data);
}

void SaveableObject::saveObjectIfNeed() const {
	if (need_save)
		saveObject();
}


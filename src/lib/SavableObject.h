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

/**
 * @brief Implementacja obiektu, który ma reprezentacje w pliku
 */
class SavableObject {
private:
	bool need_save = true;
	bool is_deleted = false;

protected:

	/**
	 * @brief Funkcja, która ma za zadanie przyjmować obiekt z pliku
	 * @param json_obj
	 */
	virtual void acceptState(json &json_obj) = 0;

	void setNeedSave(bool needSave);
	void loadObjectFromFile(const std::function<void()>& onFailed = []{});

	bool hasSavedFile();

public:

	[[nodiscard]] virtual boost::filesystem::path getSavePath() const = 0;

	/**
	 * @brief Generator obiektu json ze stanu obiektu
	 * @return
	 */
	[[nodiscard]] virtual json toJSON() const = 0;

	void saveObjectToFile();
	[[nodiscard]] virtual bool isNeedSave() const;

	/**
	 * @brief Funkcja pomocnicza do pobierania liczby z obiektu
	 * @param maybe_number
	 * @return
	 */
	static json& assertGetNumber(json& maybe_number);

	/**
	 * @brief Funkcja pomocnicza do pobierania wektora z obiektu
	 * @param maybe_number
	 * @return
	 */
	static glm::vec3 assertGetVec3(json& maybe_vector);

	/**
	 * @brief Funkcja pomocnicza do pobierania tekstu z obiektu
	 * @param maybe_number
	 * @return
	 */
	static std::string assertGetString(json& maybe_string);

	[[nodiscard]] bool isDeleted() const;
	void deleteThisObjectAsFile();

};




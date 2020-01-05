#include "playerInterface.h"
#include "src/block/Blocks.h"

game::PlayerInterface::PlayerInterface(game::GameScenePtr &scene) {
	logger.constructor(this);
}

game::PlayerInterface::~PlayerInterface() {
	logger.destructor(this);
}

game::PlayerInterfacePtr game::PlayerInterface::create(game::GameScenePtr &scene) {
	struct trick : PlayerInterface {
		trick(game::GameScenePtr &scene) : PlayerInterface(scene) {}
	};

	auto self = std::make_shared<trick>(scene);

	self->addItem(1, 1);
	self->addItem(1, 2);
	self->addItem(1, 3);
	self->addItem(1, 4);
	self->addItem(2, 1);
	self->addItem(2, 3);
	self->addItem(2, 4);
	self->addItem(3, 1);

	return self;
}

void game::PlayerInterface::addItem(int texX, int texY) {
	auto rec = std::make_shared<gui::RectangleObj>(this->shared_from_this());

	auto model = glm::mat4(1);
	model = glm::scale(model, glm::vec3(0.1));
	model = glm::translate(model, glm::vec3(1 * items.size() + 0.5, 9, 0));
	rec->setModel(model);

	auto texVecs = block::Block::getBlockText(texX, texY);
	rec->setTexture(std::get<0>(texVecs), std::get<1>(texVecs), 2);

	items.push_back(rec);
}

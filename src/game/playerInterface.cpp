#include "playerInterface.h"
#include "src/block/Blocks.h"

game::PlayerInterface::PlayerInterface(game::MainGamePtr &scene) {
	logger.constructor(this);
}

game::PlayerInterface::~PlayerInterface() {
	logger.destructor(this);
}

game::PlayerInterfacePtr game::PlayerInterface::create(game::MainGamePtr &scene) {
	struct trick : PlayerInterface {
		trick(game::MainGamePtr &scene) : PlayerInterface(scene) {}
	};

	game::PlayerInterfacePtr self = std::make_shared<trick>(scene);

	self->addItem(1, 1);
	self->addItem(1, 2);
	self->addItem(1, 3);
	self->addItem(1, 4);
	self->addItem(2, 1);
	self->addItem(2, 3);
	self->addItem(2, 4);
	self->addItem(3, 1);

	// Background
	self->background = std::make_shared<gui::RectangleObj>(self->shared_from_this());
	self->background->setPosition(glm::vec2(0, 0.88));
	self->background->setSize(glm::vec2(1, 0.13));
	self->background->setTexture(
			glm::vec2(0, 1 / 3.f),
			glm::vec2(1, 2 / 3.f)
	);

	return self;
}

void game::PlayerInterface::addItem(int texX, int texY) {
	auto rec = std::make_shared<gui::RectangleObj>(this->shared_from_this());

	auto texVecs = block::getBlockTexture(texX, texY);
	rec->setTexture(texVecs.start, texVecs.end, 2);

	items.push_back(rec);
	setItemState(items.size() - 1, items.size() == 1);
}

void game::PlayerInterface::setItemState(int index, bool selected) {

	auto &rec = items[index];

	rec->setPosition(glm::vec2(0.1 + 0.1 * index, 0.89));
	rec->setSize(glm::vec2(selected ? 0.09 : 0.06));
}

void game::PlayerInterface::selectItem(int index) {
	setItemState(selected, false);
	selected = index;
	setItemState(selected, true);
}

void game::PlayerInterface::useItem() {

}


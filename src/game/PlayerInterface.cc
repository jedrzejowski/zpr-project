/**
 * @file PlayerInterface.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "PlayerInterface.h"
#include "src/block/Blocks.h"
#include "PlayerItem.h"
#include "MainGame.h"
#include "Player.h"

game::PlayerInterface::PlayerInterface(game::MainGamePtr &scene) :
		sceneWPtr(scene),
		item_limit(8),
		items(item_limit) {
	logger(1).constructor(this);
}

game::PlayerInterface::~PlayerInterface() {
	logger(1).destructor(this);
}

game::PlayerInterfacePtr game::PlayerInterface::create(game::MainGamePtr &scene) {
	struct trick : PlayerInterface {
		trick(game::MainGamePtr &scene) : PlayerInterface(scene) {}
	};

	game::PlayerInterfacePtr self = std::make_shared<trick>(scene);

	{
		/**
		 * Inicjowanie przykładowego ekwipunku
		 */

		{ // kamień
			block::SolidBlockPtr block = std::make_shared<block::Stone>();
			PlayerItemPtr item = PlayerSolidBlockItem::create(self, block);
			self->setSlot(0, item);
		}

		{ // ziemia
			block::SolidBlockPtr block = std::make_shared<block::Dirt>();
			PlayerItemPtr item = PlayerSolidBlockItem::create(self, block);
			self->setSlot(1, item);
		}

		{ // trawa
			block::SolidBlockPtr block = std::make_shared<block::Grass>();
			PlayerItemPtr item = PlayerSolidBlockItem::create(self, block);
			self->setSlot(2, item);
		}

		{ // piasek
			block::SolidBlockPtr block = std::make_shared<block::Sand>();
			PlayerItemPtr item = PlayerSolidBlockItem::create(self, block);
			self->setSlot(3, item);
		}

		{ // woda
			block::SolidBlockPtr block = std::make_shared<block::Water>();
			PlayerItemPtr item = PlayerSolidBlockItem::create(self, block);
			self->setSlot(4, item);
		}

		{ // cegła
			block::SolidBlockPtr block = std::make_shared<block::Brick>();
			PlayerItemPtr item = PlayerSolidBlockItem::create(self, block);
			self->setSlot(5, item);
		}
	}

	// Background
	self->background = std::make_shared<gui::RectangleObj>(self->shared_from_this());
	self->background->setPosition(glm::vec2(0, 0.88));
	self->background->setSize(glm::vec2(1, 0.13));
	self->background->setTextureReference(
			engine::SquareTextureReference(
					glm::vec2(0, 0 / 3.f),
					glm::vec2(1, 1 / 3.f),
					global::TextureGuiNo
			)
	);

	return self;
}

void game::PlayerInterface::assertIndexValid(int index) {
	if (index < 0 || index >= item_limit)
		throw zprException("game::PlayerInterface::setSlot", "wrong index");
}

void game::PlayerInterface::setSlot(int index, game::PlayerItemPtr &item) {
	assertIndexValid(index);

	items[index] = item;
	updateItemModel(index);
}


void game::PlayerInterface::selectSlot(int index) {
	assertIndexValid(index);

//	setItemState(selected_slotindex, false);
	selected_slot_index = index;
//	setItemState(selected_slotindex, true);
}

void game::PlayerInterface::useItem() {
	if (isItemSlotEmpty(selected_slot_index))return;

	if (auto scene = sceneWPtr.lock())
		if (auto worldPtr = scene->getWorldMap())
			if (auto player = scene->getPlayer()) {
				items[selected_slot_index]->useItem(worldPtr, player);
			}
}

void game::PlayerInterface::updateItemModel(int index) {
	auto model = glm::mat4(1);

	model = glm::translate(model, glm::vec3((2 * (float(index) + 1) - 1) / (2 * float(item_limit)), 0.94, 0));
	model = glm::scale(model, glm::vec3(0.05));

	items[index]->setModel(model);
}

bool game::PlayerInterface::isItemSlotEmpty(int index) {
	return items[index].get() == nullptr;
}
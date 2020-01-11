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
		item_limit(10),
		items(item_limit) {
	logger(4).constructor(this);
}

game::PlayerInterface::~PlayerInterface() {
	logger(4).destructor(this);
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

		{ // kłoda
			block::SolidBlockPtr block = std::make_shared<block::Log>();
			PlayerItemPtr item = PlayerSolidBlockItem::create(self, block);
			self->setSlot(6, item);
		}

		{ // bruk
			block::SolidBlockPtr block = std::make_shared<block::Cobblestone>();
			PlayerItemPtr item = PlayerSolidBlockItem::create(self, block);
			self->setSlot(7, item);
		}

		{ // drewno
			block::SolidBlockPtr block = std::make_shared<block::Wood>();
			PlayerItemPtr item = PlayerSolidBlockItem::create(self, block);
			self->setSlot(8, item);
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

	auto old_index = selected_slot_index;
	selected_slot_index = index;

	updateItemModel(old_index);
	updateItemModel(selected_slot_index);
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
	if (isItemSlotEmpty(index)) return;

	auto model = glm::mat4(1);

	model = glm::translate(model, glm::vec3((2 * (float(index) + 1) - 1) / (2 * float(item_limit)), 0.94, 0));
	model = glm::scale(model, glm::vec3(index == selected_slot_index ? 0.043 : 0.03));

	items[index]->setModel(model);
}

bool game::PlayerInterface::isItemSlotEmpty(int index) {
	return items[index].get() == nullptr;
}
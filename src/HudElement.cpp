#include "HudElement.hpp"

/*
	class HudElement
*/

HudElement::HudElement(TCODColor col, std::string d) : display(d), col(col) {

}

void HudElement::update() {
	//Extend this!
}

/*
	class HudElementHp
*/

HudElementHp::HudElementHp(Entity* e) : HudElement(TCOD_red), e(e) {

}

void HudElementHp::update() {
	if (e != nullptr) display = std::to_string(e->hp) + "/" + std::to_string(e->maxHp) + " HP";
}

/*
	class HudElementWatts
*/

HudElementWatts::HudElementWatts(Entity* e) : HudElement(TCOD_lighter_blue), e(e) {

}

void HudElementWatts::update() {
	if (e != nullptr) display = std::to_string(e->watts) + "/" + std::to_string(e->maxWatts) + " W";
}
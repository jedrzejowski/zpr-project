//
// Created by adam on 24.10.2019.
//

#include "button.h"

gui::Button::Button() {

}


void gui::Button::insertToBuffers(std::vector<engine::Point3DeX> &vertices,
								  std::vector<engine::SimpleTriangle> &indices) {

	vertices.emplace_back(0.f, 0.f, 0.f, engine::TexCoord(0.f, 0.f));
	vertices.emplace_back(1.f, 0.f, 0.f, engine::TexCoord(2.f, 0.f));
	vertices.emplace_back(1.f, 1.f, 0.f, engine::TexCoord(2.f, 2.f));
	vertices.emplace_back(0.f, 1.f, 0.f, engine::TexCoord(0.f, 2.f));
	indices.emplace_back(0, 1, 2);
	indices.emplace_back(2, 3, 0);
}

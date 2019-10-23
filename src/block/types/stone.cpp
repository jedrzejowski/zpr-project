//
// Created by adam on 15.10.2019.
//

#include "stone.h"

block::Stone::Stone() : SolidBlock() {
	texTop = coord2D(1, 3);
	texSide = coord2D(1, 3);
	texBottom = coord2D(1, 3);
}

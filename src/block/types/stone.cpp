//
// Created by adam on 15.10.2019.
//

#include "stone.h"

block::Stone::Stone() : SolidBlock() {
	texTop = cord2D(1, 3);
	texSide = cord2D(1, 3);
	texBottom = cord2D(1, 3);
}

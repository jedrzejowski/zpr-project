//
// Created by adam on 15.10.2019.
//

#include "chunk.h"


ushort map::Chunk::MAX_X = 16;
ushort map::Chunk::MAX_Y = 16;
ushort map::Chunk::MAX_Z = 16;


map::Chunk::Chunk() : Abs3DObj() {

	stoneTex = gengine::Resources::get().getTexture("qwe");

	verticesNum = 4;
	indicesNum = 2;

	vertices = new gengine::Point3DeX[verticesNum];
	indices = new gengine::SimpleTriangle[indicesNum];

	vertices[0] = gengine::Point3DeX(0.f, 0.f, 0.f, gengine::TexCoord(0.f, 0.f));
	vertices[1] = gengine::Point3DeX(1.f, 0.f, 0.f, gengine::TexCoord(1.f, 0.f));
	vertices[2] = gengine::Point3DeX(1.f, 1.f, 0.f, gengine::TexCoord(1.f, 1.f));
	vertices[3] = gengine::Point3DeX(0.f, 1.f, 0.f, gengine::TexCoord(0.f, 1.f));


	indices[0] = gengine::SimpleTriangle(0, 1, 2);
	indices[1] = gengine::SimpleTriangle(2, 3, 0);

	insertObjToBuffers();
}

void map::Chunk::render(gengine::Window *window) {
}

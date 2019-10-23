#include "solidblock.h"
#include "src/engine/Engine.h"

block::SolidBlock::SolidBlock() : Block() {
}

void block::SolidBlock::insertToBuffers(std::vector<engine::Point3DeX> &vertices,
										std::vector<engine::SimpleTriangle> &indices) {


	auto vOffest = vertices.size();
	auto iOffest = indices.size();

	static float texCols = 2;
	static float texRows = 4;

	auto tex_xx = engine::TexCoord((float(texSide.x) - 1) / texCols, (float(texSide.x) - 1) / texRows);
	auto tex_xX = engine::TexCoord(float(texSide.x) / texCols, (float(texSide.x) - 1) / texRows);
	auto tex_XX = engine::TexCoord(float(texSide.x) / texCols, float(texSide.x) / texRows);
	auto tex_Xx = engine::TexCoord((float(texSide.x) - 1) / texCols, float(texSide.x) / texRows);

	// płaszczna z
	{
		vertices.emplace_back(engine::Point3D(position.x, position.y, position.z), tex_xx);
		vertices.emplace_back(engine::Point3D(position.x + 1, position.y, position.z), tex_xX);
		vertices.emplace_back(engine::Point3D(position.x + 1, position.y + 1, position.z), tex_XX);
		vertices.emplace_back(engine::Point3D(position.x, position.y + 1, position.z), tex_Xx);

		indices.push_back(engine::SimpleTriangle(0, 1, 2) + vOffest);
		indices.push_back(engine::SimpleTriangle(2, 3, 0) + vOffest);

		vOffest += 4;
	}

	// płaszczna Z
	{
		vertices.emplace_back(engine::Point3D(position.x, position.y, position.z + 1), tex_xx);
		vertices.emplace_back(engine::Point3D(position.x + 1, position.y, position.z + 1), tex_xX);
		vertices.emplace_back(engine::Point3D(position.x + 1, position.y + 1, position.z + 1), tex_XX);
		vertices.emplace_back(engine::Point3D(position.x, position.y + 1, position.z + 1), tex_Xx);

		indices.push_back(engine::SimpleTriangle(2, 1, 0) + vOffest);
		indices.push_back(engine::SimpleTriangle(0, 3, 2) + vOffest);

		vOffest += 4;
	}

	// płaszczna x
	{
		vertices.emplace_back(engine::Point3D(position.x, position.y, position.z), tex_xx);
		vertices.emplace_back(engine::Point3D(position.x, position.y + 1, position.z), tex_xX);
		vertices.emplace_back(engine::Point3D(position.x, position.y + 1, position.z + 1), tex_XX);
		vertices.emplace_back(engine::Point3D(position.x, position.y, position.z + 1), tex_Xx);

		indices.push_back(engine::SimpleTriangle(0, 1, 2) + vOffest);
		indices.push_back(engine::SimpleTriangle(2, 3, 0) + vOffest);

		vOffest += 4;
	}

	// płaszczna X
	{
		vertices.emplace_back(engine::Point3D(position.x + 1, position.y, position.z), tex_xx);
		vertices.emplace_back(engine::Point3D(position.x + 1, position.y + 1, position.z), tex_xX);
		vertices.emplace_back(engine::Point3D(position.x + 1, position.y + 1, position.z + 1), tex_XX);
		vertices.emplace_back(engine::Point3D(position.x + 1, position.y, position.z + 1), tex_Xx);

		indices.push_back(engine::SimpleTriangle(2, 1, 0) + vOffest);
		indices.push_back(engine::SimpleTriangle(0, 3, 2) + vOffest);

		vOffest += 4;
	}

	// płaszczna y
	{
		vertices.emplace_back(engine::Point3D(position.x, position.y, position.z), tex_xx);
		vertices.emplace_back(engine::Point3D(position.x + 1, position.y, position.z), tex_xX);
		vertices.emplace_back(engine::Point3D(position.x + 1, position.y, position.z + 1), tex_XX);
		vertices.emplace_back(engine::Point3D(position.x, position.y, position.z + 1), tex_Xx);

		indices.push_back(engine::SimpleTriangle(0, 1, 2) + vOffest);
		indices.push_back(engine::SimpleTriangle(2, 3, 0) + vOffest);

		vOffest += 4;
	}

	// płaszczna Y
	{
		vertices.emplace_back(engine::Point3D(position.x, position.y + 1, position.z), tex_xx);
		vertices.emplace_back(engine::Point3D(position.x + 1, position.y + 1, position.z), tex_xX);
		vertices.emplace_back(engine::Point3D(position.x + 1, position.y + 1, position.z + 1), tex_XX);
		vertices.emplace_back(engine::Point3D(position.x, position.y + 1, position.z + 1), tex_Xx);

		indices.push_back(engine::SimpleTriangle(2, 1, 0) + vOffest);
		indices.push_back(engine::SimpleTriangle(0, 3, 2) + vOffest);

		vOffest += 4;
	}
}

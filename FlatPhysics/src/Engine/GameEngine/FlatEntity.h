#pragma once
#include "Common.h"
#include "RandomHelper.h"
#include "FlatConverter.h"
using namespace FlatPhysics;

class FlatEntity
{
private:
	//FlatBody* body = new FlatBody();
	MultiBody* multiBody = new MultiBody();
	Color color;

	std::vector<Vector2> vertexBuffer;
public:
	MultiBody* GetBody();
	Color GetColor();

	FlatEntity(MultiBody* body);
	FlatEntity(MultiBody* body, const Color& color);
	FlatEntity(FlatWorld& world, float radius, bool isStatic, const FlatVector& position);
	FlatEntity(FlatWorld& world, float width, float height, bool isStatic, const FlatVector& position);
	FlatEntity(FlatWorld& world, std::vector<FlatVector>& vertices, bool isStatic, const FlatVector& position, Color color);
	void Draw();

};

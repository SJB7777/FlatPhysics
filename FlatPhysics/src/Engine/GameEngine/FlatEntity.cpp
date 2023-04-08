#include "FlatEntity.h"

MultiBody* FlatEntity::GetBody() { return multiBody; }
Color FlatEntity::GetColor() { return color; }

FlatEntity::FlatEntity(MultiBody* body) :
	multiBody(body), color(RandomHelper::RandomColor()) {}

FlatEntity::FlatEntity(MultiBody* body, const Color& color) :
	multiBody(body), color(color) {}

FlatEntity::FlatEntity(FlatWorld& world, float radius, bool isStatic, const FlatVector& position) :
	color(RandomHelper::RandomColor())
{
	FlatBody* body = new FlatBody();
	std::string errorMessage;
	if (!FlatBody::CreateCircleBody(radius, 1.0f, isStatic, 0.5f,
		*body, errorMessage))
	{
		throw std::invalid_argument(errorMessage);
	}

	
	MultiBody::CreateSingleBody(*body, *this->multiBody);
	multiBody->MoveTo(position);
	world.AddBody(this->multiBody);
}

FlatEntity::FlatEntity(FlatWorld& world, float width, float height, bool isStatic, const FlatVector& position) :
	color(RandomHelper::RandomColor())
{
	FlatBody* body = new FlatBody();
	std::string errorMessage;
	if (!FlatBody::CreateBoxBody(width, height, 1.0f, isStatic, 0.5f,
		*body, errorMessage))
	{
		throw std::invalid_argument(errorMessage);
	}

	
	
	MultiBody::CreateSingleBody(*body, *this->multiBody);
	multiBody->MoveTo(position);
	world.AddBody(this->multiBody);
}

FlatEntity::FlatEntity(FlatWorld& world, std::vector<FlatVector>& vertices, bool isStatic, const FlatVector& position, Color color) :
	color(color)
{
	std::string errorMessage;
	if (!MultiBody::CreateConcaveBody(vertices, 1.0f, isStatic, 0.5f, *this->multiBody, errorMessage))
	{
		throw std::invalid_argument(errorMessage);
	}
	
	this->multiBody->MoveTo(position);
	world.AddBody(this->multiBody);
}

void FlatEntity::Draw() 
{
	for (auto& body : this->multiBody->subBodies)
	{
		
		Vector2 position = FlatConverter::ToVector2(body->GetPosition());
		if (body->shapeType == ShapeType::Circle)
		{
			Vector2 va = { 0.0f, 0.0f };
			Vector2 vb = { body->Radius, 0.0f };
			Matrix matrix1 = MatrixTranslate(body->GetPosition().x, body->GetPosition().y, 0.0f);
			Matrix matrix2 = MatrixRotateZ(body->GetAngle());
			Matrix matrix = MatrixMultiply(matrix2, matrix1);
			va = Vector2Transform(va, matrix);
			vb = Vector2Transform(vb, matrix);

			DrawCircleV(position, body->Radius, color);
			DrawRing(position, body->Radius - 0.7f, body->Radius, 0, 360, 100, WHITE);
			DrawLineV(va, vb, WHITE);
		}
		else if (body->shapeType == ShapeType::Box)
		{
			std::vector<FlatVector> vertices = body->GetTransformedVertices();
			FlatConverter::ToVector2Array(vertices, vertexBuffer);


			std::vector<int> triangles;
			std::string errorMessage;
			PolygonHelper::Triangulate(vertices, triangles, errorMessage);
			GameDraw::DrawPolygonFill(vertexBuffer, triangles, color);
			GameDraw::DrawPolygonLines(vertexBuffer, 0.7f, WHITE);
		}
	}
	
}

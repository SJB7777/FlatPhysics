#include "Game.h"
#include <stdexcept>

CameraExtents CameraManager::GetExtents()
{
    float left = camera.target.x - GetScreenWidth() / camera.zoom / 2;
    float right = camera.target.x + GetScreenWidth() / camera.zoom / 2;
    float bottom = camera.target.y - GetScreenHeight() / camera.zoom / 2;
    float top = camera.target.y + GetScreenHeight() / camera.zoom / 2;

    return { left, right, bottom, top };
}

void Game::Setting() {
    SetTargetFPS(60);
    SetWindowPosition(10, 40);

    CameraExtents CameraExtent = camera.GetExtents();
    
    float padding = (CameraExtent.right - CameraExtent.left) * 0.1f;
    
    FlatBody* groundBody = new FlatBody();

    if (!FlatBody::CreateBoxBody(CameraExtent.right - CameraExtent.left - padding * 2, 30.0f, 1.0f, 
        true, 0.5f, *groundBody, errorMessage))
    {
        throw std::invalid_argument(errorMessage);
    }
    groundBody->MoveTo({ 0, 100.0f });
    MultiBody* groundM = new MultiBody();
    MultiBody::CreateSingleBody(*groundBody, *groundM);
    world.AddBody(groundM);
    entityVector.push_back(new FlatEntity(groundM, DARKGREEN));
    
    entityVector.push_back(new FlatEntity(world, 30, 250, true, { 0, -30 }, GRAY));

    FlatEntity* entity = new FlatEntity(world, 30, 30, false, { 0, -30 }, GRAY);
    entity->GetBody()->AddForce({ 1000, 0 });

    Btn.SetButton("button", 300, 50, 20);
    Btn.SetPosition(100, 100);
    
}

void Game::UpdateLoad()
{
}



void Game::UpdateGame(float deltaTime) {
    
    
    // camera move
    camera.camera.zoom += ((float)GetMouseWheelMove() * camera.zoomSpeed);

    if (camera.camera.zoom > 30.0f) camera.camera.zoom = 30.0f;
    else if (camera.camera.zoom < 0.01f) camera.camera.zoom = 0.01f;

    
    // add circle body
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {

        float radius = RandomHelper::RandomFloat(12.5f, 17.5f);

        FlatVector mouseWorldPosition =
            FlatConverter::ToFlatVector(GetScreenToWorld2D(GetMousePosition(), camera.camera));

        entityVector.push_back(new FlatEntity(world, radius, false, mouseWorldPosition));

        

        
    }


    if (IsKeyPressed(KEY_T))
    {
        camera.camera.zoom = defaultZoom;
        camera.camera.target = Vector2 { 0, 0 };
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        camera.camera.target.x += deltaTime * camera.linearSpeed;
    }

    if (IsKeyDown(KEY_LEFT))
    {
        camera.camera.target.x -= deltaTime * camera.linearSpeed;
    }

    if (IsKeyDown(KEY_DOWN))
    {
        camera.camera.target.y += deltaTime * camera.linearSpeed;
    }

    if (IsKeyDown(KEY_UP))
    {
        camera.camera.target.y -= deltaTime * camera.linearSpeed;
    }
    
    double startTime = GetTime();
    world.Step(deltaTime, 10);
    stepTime = GetTime() - startTime;

    CameraExtents extents = camera.GetExtents();
    float viewBottom = extents.top;

    entityRemovalVector.clear();

    /*for (int i = 0; i < world.BodyCount(); i++)
    {
        FlatEntity* entity = entityVector[i];
        FlatBody* body = entity->GetBody();
        
        if (!world.GetBody(i, body))
        {
            throw std::out_of_range("Body is out of range");
        }
        
        if (body->IsStatic)
        {
            continue;
        }

        FlatAABB box = body->GetAABB();

        if (box.Max.y > viewBottom)
        {
            entityRemovalVector.push_back(entity);
        }
    }*/

    /*for (int i = 0; i < entityRemovalVector.size(); i++)
    {
        FlatEntity* entity = entityRemovalVector[i];
        world.RemoveBody(entity->GetBody());
        entityVector.erase(remove(entityVector.begin(), entityVector.end(), entity), entityVector.end());
    }*/
    Btn.click_connect(this, &Game::pause);
}

void Game::UpdateMainMenu()
{
    
    
}

void Game::UpdatePaused()
{
    Btn.click_connect(this, &Game::run);
    
}

void Game::UpdateGameOver()
{
    
}

void Game::Draw(float deltaTime) {

    BeginMode2D(camera.camera);

    for (int i = 0; i < entityVector.size(); i++)
    {
        entityVector[i]->Draw();
    }

    

    
    

    EndMode2D();

    
    if (ApplicationState != ApplicationStates::Running)
    {
        Screen::DimScreen();
    }
    Btn.draw();
    DrawText(TextFormat("StepTime : %.4fms", stepTime * 1000), 20, GetScreenHeight() - 30 - 10 - 20 - 20, 20, YELLOW);
    DrawText(TextFormat("BodyCount : %d", world.BodyCount()), 20, GetScreenHeight() - 30 - 10 - 20, 20, YELLOW);
    DrawText(TextFormat("Zoom : %d %%", int(camera.camera.zoom / defaultZoom * 100)), 20, GetScreenHeight() - 30 - 10, 20, YELLOW);
    DrawFPS(20, 20);
}

void Game::End() {
   
}


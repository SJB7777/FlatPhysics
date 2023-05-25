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
    
    
    
    entityVector.push_back(new FlatEntity(world, CameraExtent.right - CameraExtent.left, 30, true, DARKGREEN, { 0, 200 }));
    entityVector.push_back(new FlatEntity(world, 30, 270, true, GRAY, { 0, 50 }));

    
    
    

    Btn.SetButton(" || ", 40, 20, 20);
    Btn.SetPosition(1000, 80);
    Btn_Stop_Resume.SetButton("Resume", 300, 50, 20, 6, 500, 450);
    Btn_Stop_Retry.SetButton("Retry", 300, 50, 20, 6, 500, 550);
    Btn_Stop_Mainmenu.SetButton("Mainmenu", 300, 50, 20, 6, 500, 650);
    entityVector.push_back(cannon->GetEntity());
    texture_start_page = LoadTexture("asset/start_page.png");
    texture_target = LoadTexture("asset/target.png");
}

void Game::UpdateGameClear()
{
}

void Game::DrawGameClear()
{
}



void Game::UpdateGame(float deltaTime) {
    
    
    // camera move
    camera.camera.zoom += ((float)GetMouseWheelMove() * camera.zoomSpeed);

    if (camera.camera.zoom > 30.0f) camera.camera.zoom = 30.0f;
    else if (camera.camera.zoom < 0.01f) camera.camera.zoom = 0.01f;

    
    if (CheckCollisionPointCircle(GetScreenToWorld2D(GetMousePosition(), camera.camera), FlatConverter::ToVector2(cannon->origin), 10.0f))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            cannon->isClicked = true;
        }
    }
    if (cannon->isClicked)
    {
        cannon->GetEntity()->MoveTo(FlatConverter::ToFlatVector(GetScreenToWorld2D(GetMousePosition(), camera.camera)));
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            cannon->isClicked = false;
            cannon->GetEntity()->GetBody()->IsStatic = false;
            cannon->GetEntity()->AddForce(cannon->GetDisplacement() * -1000000.0f);
            printf("%f\n", cannon->GetEntity()->GetBody()->force.y);
            
        }
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

    if (ApplicationState == ApplicationStates::Menu)
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            ApplicationState = ApplicationStates::Running;
    
}

void Game::DrawMainMenu()
{
    DrawTexture(texture_start_page, 0, 0, WHITE);
}

void Game::UpdatePaused()
{
    Btn.click_connect(this, &Game::run);
    Btn_Stop_Resume.click_connect(this, &Game::run);
    Btn_Stop_Mainmenu.click_connect(this, &Game::to_menu);
    Btn_Stop_Retry.click_connect(this, &Game::retry);
}

void Game::DrawPaused()
{
    Screen::DimScreen();
    DrawRectangle(200, 120, 900, 600, WHITE);
    DrawText("Game Pause", 420, 300, 80, BLACK);

    Btn.draw();
    Btn_Stop_Resume.draw();
    Btn_Stop_Retry.draw();
    Btn_Stop_Mainmenu.draw();
}

void Game::UpdateGameOver()
{
    
}

void Game::DrawGameOver()
{
}

void Game::Draw(float deltaTime) {

    BeginMode2D(camera.camera);

    for (int i = 0; i < entityVector.size(); i++)
    {
        entityVector[i]->Draw();
    }

    if (cannon->isClicked)
    {
        cannon->DrawSlingshot();
    }

    
    

    EndMode2D();

    Btn.draw();
    
    DrawTexture(texture_target, 1200, 600, WHITE);
    DrawText(TextFormat("StepTime : %.4fms", stepTime * 1000), 20, GetScreenHeight() - 30 - 10 - 20 - 20, 20, YELLOW);
    DrawText(TextFormat("BodyCount : %d", world.BodyCount()), 20, GetScreenHeight() - 30 - 10 - 20, 20, YELLOW);
    DrawText(TextFormat("Zoom : %d %%", int(camera.camera.zoom / defaultZoom * 100)), 20, GetScreenHeight() - 30 - 10, 20, YELLOW);
    DrawFPS(20, 20);
}

void Game::End() {
   
}


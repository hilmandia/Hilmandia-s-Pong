#include <raylib.h>
#include <iostream>

class Ball{
    public:
        float x, y;
        int radius;
        int speed_x, speed_y;

        Ball(float pos_x, float pos_y, int r){
            x = pos_x;
            y = pos_y;
            radius = r;
        }

        void Draw(){
            DrawCircle(x, y, radius, WHITE);
        }
        
        void Update() {
            x += speed_x;
            y += speed_y;
            if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y *= -1;
            }
   }
};

class Paddle{
    protected:
    void LimitMovement(){
        if(y <= 0){
            y = 0;
        }
        if(y + height >= GetScreenHeight()){
            y = GetScreenHeight() - height;
        }
    }
    public:
        float x, y;
        float width, height;
        bool isPlayerControlled;

        Paddle(float pos_x, float pos_y, float paddle_width, float paddle_height, bool controlled){
            x = pos_x;
            y = pos_y;
            width = paddle_width;
            height = paddle_height;
            isPlayerControlled = controlled;
        }

        void Update(float ballY){
            if(isPlayerControlled){
                if(IsKeyDown(KEY_UP)) y -= 5;
                if(IsKeyDown(KEY_DOWN)) y += 5;
            } else{
                if (y + height/2 < ballY) y += 4;
                if (y + height/2 > ballY) y -= 4;
            }
            LimitMovement();
        }

        void Draw(){
            DrawRectangle(x, y, width, height, WHITE);
        }
};

int main() {
    const int window_width = 1280;
    const int window_height = 720;

    Ball ball(window_width / 2, window_height / 2, 20);
    ball.speed_x = 5;
    ball.speed_y = 5;
    Paddle player(window_width - 30, window_height / 2 - 50, 20, 100, true);
    Paddle cpu(10, window_height / 2 - 50, 20, 100, false);

    InitWindow(window_width, window_height, "Hilmandia's Pong");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        //Update
        ball.Update();
        player.Update(ball.y);
        cpu.Update(ball.y);

        //Draw
        ball.Draw();
        player.Draw();
        cpu.Draw();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
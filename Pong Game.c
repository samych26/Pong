#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define BASE 12


// Tous les types utilisés
typedef enum ecranprincipale { home = 0,mode, jeupvp, jeupve, difficulte, fin, attentejeupvp, attentejeupve} ecranpricipale;
typedef enum Direction { UP = 0, DOWN } Direction;

// Toutes les variables utilisés.
Rectangle ecran, bordureDeJeu, haut, bas, balle, Lracket, Rracket;
int RScore = 0, LScore = 0, win, mouvementballe, mute = 0;
float i;

// Toutes les procedures Utilisés
void InitialiserPong(void);
void afficherPong(void);
void bougerBalle(void);
void bougerRaquette(Rectangle *pRacket, Direction pDir);
void ServirBalle(void);
void winer (int leftScore, int rightScore);
void terrainDeJeu (void);



// Procedure pour initialiser les donnés pricipale du jeu
void InitialiserPong(void)
{
    InitWindow(0, 0, "Pong");
    // Calculer les tailles de l'écran et donner des dimensions ou formes principales.
    ecran = (Rectangle){0, 0, GetScreenWidth()/1.005, GetScreenHeight()/1.1};
    bordureDeJeu = (Rectangle){BASE, BASE, ecran.width - (2*BASE) , ecran.height - (2*BASE)};
    haut = (Rectangle) {ecran.x, ecran.y, bordureDeJeu.width, bordureDeJeu.y};
    bas = (Rectangle) {ecran.x, bordureDeJeu.height+BASE, ecran.width, ecran.y};
    balle = (Rectangle) {5*BASE, bordureDeJeu.height, BASE, BASE};
    Lracket = (Rectangle) {bordureDeJeu.x + BASE, bordureDeJeu.height/2, BASE, 5*BASE};
    Rracket = (Rectangle) {bordureDeJeu.width - BASE, bordureDeJeu.height/2, BASE, 5*BASE};


}
// Procedure pour afficher le Jeu du pong
void afficherPong(void)
{
    SetWindowPosition(ecran.width/400, ecran.height/25);
    SetWindowSize(ecran.width, ecran.height);
    SetTargetFPS(100);
}

// Procedure pour bouger la balle et la faire rebondir
void bougerBalle(void){
    static int xx = BASE/5;
    static int yy = BASE/5;
    float r = 2;

    if(CheckCollisionRecs(balle , Rracket) || CheckCollisionRecs(balle , Lracket)){
    xx = -xx;
    }
    if(CheckCollisionRecs(balle , bas)|| CheckCollisionRecs(balle , haut)){
    yy = -yy;
    }

    if (balle.x < ecran.x)
            {
                RScore++;
                ServirBalle();
                i = 0;
                r = 0;
            }
            else if (balle.x > ecran.width)
            {
                LScore++;
                ServirBalle();
                i = 0;
                r = 0;
            }
            switch (mouvementballe){
            case 21:
                {
                     balle.x += r * xx;
                     balle.y += yy;
                     i = i + 0.006;
                    Rracket.y = balle.y + i;
                    r = r + 2;

                }break;
            case 22:
                {
                     balle.x += r * xx;
                     balle.y += yy;
                     i = i + 0.003;
                    Rracket.y = balle.y + i;
                    r = r + 2;
                }break;

            case 23:
                {
                    balle.x += r * 1.5 * xx;
                    balle.y += yy;
                    i = i + 0.0001;
                    Rracket.y = balle.y + i;
                    r = r + 3;
                }break;
            case 24:
                {
                    balle.x += 5 * r * xx;
                    balle.y += yy;
                    i = i;
                    Rracket.y = balle.y + i;
                    r = r + 5;
                }break;
            case 1:
                {
                    balle.x += r *xx;
                    balle.y += yy;
                    r = r + 2;
                }

            default:break;
            }

}

// Procedure pour bouger les raquettes
void bougerRaquette(Rectangle *pRacket, Direction pDir)
{
    int step = (pDir == UP)? -BASE/2: BASE/2;

    if ((CheckCollisionRecs(haut, *pRacket) && pDir == UP) ||
        (CheckCollisionRecs(bas, *pRacket) && pDir == DOWN))
            return;
    pRacket->y += step;
}

// Procedure pour servire la balle au milieu
void ServirBalle(void)
{
    balle.x = bordureDeJeu.width/2;
    balle.y = GetRandomValue(bordureDeJeu.y + 10, bordureDeJeu.height);
}
// Procedure pour anoncer le gagnant de la partie
void winer (int leftScore, int rightScore)
{
    if (LScore > RScore)
    {
        DrawText("The winner is Left player", 300, 300, 100, PURPLE);
    }else{
        DrawText("The winner is Right player", 300, 300, 100, PURPLE);
    }
    return 0;
}
// procédure pour afficher le terrain de jeu
void terrainDeJeu (void)
{
    // Le terrain et les bordures.
    DrawRectangle(ecran.x, ecran.y, ecran.width, ecran.height, WHITE);
    DrawRectangle(ecran.x, bordureDeJeu.y, ecran.width, bordureDeJeu.height, PURPLE);
    DrawRectangle((ecran.width/2) - 5, bordureDeJeu.y, BASE, bordureDeJeu.height, WHITE);
    // La balle.
    DrawRectangle(balle.x, balle.y, balle.width, balle.height, YELLOW);
    // Les raquettes.
    DrawRectangle(Lracket.x, Lracket.y, Lracket.width, Lracket.height, WHITE);
    DrawRectangle(Rracket.x, Rracket.y, Rracket.width, Rracket.height, WHITE);
    // Le score.
    DrawText(TextFormat("%d", RScore),(ecran.width/2) +40, 50, 60, WHITE);
    DrawText(TextFormat("%d", LScore), (ecran.width/2) -60 , 50, 60, WHITE);
}


// Le code pricipale.
int main(void)
{
    InitAudioDevice();
    ecranpricipale  ecranaff = home ;
    InitialiserPong();
    afficherPong();
    ServirBalle();
    Sound fxBack = LoadSound("resources/sound.wav");
    Sound fxBounce = LoadSound("resources/bounce.wav");
    Sound fxScore = LoadSound("resources/score.wav");
    SetSoundVolume(fxScore, 0.15f);
    SetSoundVolume(fxBack, 0.08f);
    SetSoundVolume(fxBounce, 0.5f);
    PlaySoundMulti(fxBack);

    while (!WindowShouldClose()) // si l'utilisateur ne ferme pas la fenetre
    {
        switch(ecranaff)
        {
            case home:
            {
                if(IsGestureDetected(GESTURE_TAP))
                {
                    if(GetMouseX() <= ecran.width/2+70 && GetMouseX() >= ecran.width/2-30 && GetMouseY() <= 530 && GetMouseY() >= 450)
                    {
                        ecranaff = mode;
                    }else if(GetMouseX() <= ecran.width/2+670 && GetMouseX() >= ecran.width/2+600 && GetMouseY() <= bordureDeJeu.y+35 && GetMouseY() >= bordureDeJeu.y)
                        {
                            StopSoundMulti();
                        }
                }

            } break;
            case mode:
            {
                if(IsGestureDetected(GESTURE_TAP))
                {
                    if(GetMouseX() <= ecran.width/2+435 && GetMouseX() >= ecran.width/2+200 && GetMouseY() <= 390 && GetMouseY() >= 250)
                    {
                        ecranaff = attentejeupvp;
                        mouvementballe = 1;
                    }
                    else if (GetMouseX() <= ecran.width/2-200 && GetMouseX() >= ecran.width/2-435 && GetMouseY() <= 390 && GetMouseY() >= 250)
                    {
                        ecranaff = difficulte;
                    }
                }

            } break;
            case attentejeupvp:
            {
                if(IsGestureDetected(GESTURE_TAP) || IsKeyPressed(KEY_ENTER))
                {
                    ecranaff = jeupvp;
                }
            }break;
            case attentejeupve:
            {
               if(IsGestureDetected(GESTURE_TAP) || IsKeyPressed(KEY_ENTER))
                {
                    ecranaff = jeupve;
                }
            }break;

            case jeupvp:
            {
                bougerBalle();
                if (balle.x < ecran.x)
                {
                PlaySoundMulti(fxScore);
                }
                else if (balle.x > ecran.width)
                {
                PlaySoundMulti(fxScore);
                }
                if(CheckCollisionRecs(balle , Rracket) || CheckCollisionRecs(balle , Lracket)){
                PlaySoundMulti(fxBounce); }
                if(CheckCollisionRecs(balle , bas)|| CheckCollisionRecs(balle , haut)){
                PlaySoundMulti(fxBounce);
                }

                // Check racket keys.
                if (IsKeyDown(KEY_Q))
                    bougerRaquette(&Lracket, UP);
                else if (IsKeyDown(KEY_A))
                    bougerRaquette(&Lracket, DOWN);
                else if (IsKeyPressed(KEY_LEFT_CONTROL)||IsKeyPressed(KEY_RIGHT_CONTROL))
                    ecranaff = mode;
                if (IsKeyDown(KEY_I))
                    bougerRaquette(&Rracket, UP);
                else if (IsKeyDown(KEY_J))
                    bougerRaquette(&Rracket, DOWN);


                if ((LScore >= 11) || (RScore >= 11))
                {
                    win = (LScore > RScore)? 1 : 2;
                    RScore = LScore = 0;
                    ecranaff = fin;
                    Sound fxWin = LoadSound("resources/win.wav");
                    SetSoundVolume(fxWin, 0.5f);
                    PlaySoundMulti(fxWin);
                }
            } break;
            case difficulte:
            {
            if(IsGestureDetected(GESTURE_TAP))
                {
                    if(GetMouseX() <= ecran.width/2+670 && GetMouseX() >= ecran.width/2+600 && GetMouseY() <= bordureDeJeu.y+35 && GetMouseY() >= bordureDeJeu.y)
                    {
                        ecranaff = mode;
                    }else if(GetMouseX() <= ecran.width/2-290 && GetMouseX() >= ecran.width/2-435 && GetMouseY() <= bordureDeJeu.y+320 && GetMouseY() >= bordureDeJeu.y+250)
                    {
                        mouvementballe = 21;
                        ecranaff = attentejeupve;
                    }else if(GetMouseX() <= ecran.width/2+60 && GetMouseX() >= ecran.width/2-85 && GetMouseY() <= bordureDeJeu.y+320 && GetMouseY() >= bordureDeJeu.y+250)
                    {
                        mouvementballe = 22;
                        ecranaff = attentejeupve;
                    }else if(GetMouseX() <= ecran.width/2+410 && GetMouseX() >= ecran.width/2+265 && GetMouseY() <= bordureDeJeu.y+320 && GetMouseY() >= bordureDeJeu.y+250)
                    {
                        mouvementballe = 23;
                        ecranaff = attentejeupve;
                    }else if(GetMouseX() <= ecran.width/2+660 && GetMouseX() >= ecran.width/2+600 && GetMouseY() <= bordureDeJeu.y+720 && GetMouseY() >= bordureDeJeu.y+650)
                    {
                        mouvementballe = 24;
                        ecranaff = attentejeupve;
                    }
                }
            }break;
            case jeupve:
            {
                if (balle.x < ecran.x)
                {
                PlaySoundMulti(fxScore);
                }
                else if (balle.x > ecran.width)
                {
                PlaySoundMulti(fxScore);
                }
                bougerBalle();
                if(CheckCollisionRecs(balle , Rracket) || CheckCollisionRecs(balle , Lracket)){
                PlaySoundMulti(fxBounce); }
                if(CheckCollisionRecs(balle , bas)|| CheckCollisionRecs(balle , haut)){
                PlaySoundMulti(fxBounce);
                }
                if (IsKeyDown(KEY_Q))
                    bougerRaquette(&Lracket, UP);
                else if (IsKeyDown(KEY_A))
                    bougerRaquette(&Lracket, DOWN);
                else if (IsKeyPressed(KEY_LEFT_CONTROL)||IsKeyPressed(KEY_RIGHT_CONTROL))
                    ecranaff = mode;

                     if ((LScore >= 11) || (RScore >= 11))
                {
                    win = (LScore > RScore)? 1 : 2;
                    RScore = LScore = 0;
                    ecranaff = fin;
                    Sound fxWin = LoadSound("resources/win.wav");
                    SetSoundVolume(fxWin, 0.5f);
                    PlaySoundMulti(fxWin);
                }


            }
            case fin:
            {
                if (IsGestureDetected(GESTURE_TAP))
                {
                    if (GetMouseX() <= ecran.width/2-60 && GetMouseX() >= ecran.width/2-215 && GetMouseY() <= bordureDeJeu.y+420 && GetMouseY() >= bordureDeJeu.y+350 || IsKeyPressed(KEY_ENTER))
                    {
                        ecranaff = jeupvp;
                    }else if(GetMouseX() <= ecran.width/2+210 && GetMouseX() >= ecran.width/2+65 && GetMouseY() <= bordureDeJeu.y+420 && GetMouseY() >= bordureDeJeu.y+350)
                    {
                        ecranaff = mode;
                    }else if(GetMouseX() <= ecran.width/2+670 && GetMouseX() >= ecran.width/2+600 && GetMouseY() <= bordureDeJeu.y+35 && GetMouseY() >= bordureDeJeu.y)
                    {
                        CloseWindow();
                    }
                }
            } break;
            default: break;
        }

        // Rendering.
        BeginDrawing();
        switch(ecranaff)
        {
            case home:
            {
                ClearBackground(PURPLE);
                DrawRectangle((ecran.width/2)+600, bordureDeJeu.y, BASE/4, BASE*3, WHITE);
                DrawRectangle((ecran.width/2)+670, bordureDeJeu.y, BASE/4, BASE*3, WHITE);
                DrawRectangle((ecran.width/2)+600, bordureDeJeu.y, BASE*6, BASE/4, WHITE);
                DrawRectangle((ecran.width/2)+600, bordureDeJeu.y+35, BASE*6, BASE/4, WHITE);
                DrawText("MUTE", ecran.width/2+608, bordureDeJeu.y + 10, 20, WHITE);

                DrawTriangle((Vector2){ ecran.width/2 - 30, 450 },
                             (Vector2){ ecran.width/2- 30, 530 },
                             (Vector2){ ecran.width/2 +70, 490 }, WHITE);

                DrawText("PONG", ecran.width/2 - 160, 120, 120, WHITE);
                DrawText("Algorithmic project", ecran.width/2 - 285, 240, 60, WHITE);

            } break;
            case mode:
            {
                ClearBackground(PURPLE);
                DrawText("MODE DE JEU", ecran.width/2-300, bordureDeJeu.y, 80, WHITE);
                DrawRectangle((ecran.width/2)+200, bordureDeJeu.y+250, BASE/2, BASE*12, WHITE);
                DrawRectangle((ecran.width/2)+435, bordureDeJeu.y+250, BASE/2, BASE*12, WHITE);
                DrawRectangle((ecran.width/2)+200, bordureDeJeu.y+250, BASE*20, BASE/2, WHITE);
                DrawRectangle((ecran.width/2)+200, bordureDeJeu.y+390, BASE*20, BASE/2, WHITE);
                DrawText("2 JOUEURS", ecran.width/2 + 220, ecran.y + 315, 37, WHITE);
                DrawText("1 JOUEUR", ecran.width/2 - 410, ecran.y + 315 , 40, WHITE);
                DrawRectangle((ecran.width/2)-200, bordureDeJeu.y+250, BASE/2, BASE*12, WHITE);
                DrawRectangle((ecran.width/2)-435, bordureDeJeu.y+250, BASE/2, BASE*12, WHITE);
                DrawRectangle((ecran.width/2)-435, bordureDeJeu.y+250, BASE*20, BASE/2, WHITE);
                DrawRectangle((ecran.width/2)-435, bordureDeJeu.y+390, BASE*20, BASE/2, WHITE);

            } break;
            case jeupvp:
            {
            terrainDeJeu();
            } break;
            case difficulte:
            {
                ClearBackground(PURPLE);

                DrawRectangle((ecran.width/2)+600, bordureDeJeu.y, BASE/4, BASE*3, WHITE);
                DrawRectangle((ecran.width/2)+670, bordureDeJeu.y, BASE/4, BASE*3, WHITE);
                DrawRectangle((ecran.width/2)+600, bordureDeJeu.y, BASE*6, BASE/4, WHITE);
                DrawRectangle((ecran.width/2)+600, bordureDeJeu.y+35, BASE*6, BASE/4, WHITE);
                DrawText("BACK", ecran.width/2+608, bordureDeJeu.y + 10, 20, WHITE);

                DrawRectangle((ecran.width/2)-290, bordureDeJeu.y+250, BASE/2, BASE*6, WHITE);
                DrawRectangle((ecran.width/2)-435, bordureDeJeu.y+250, BASE/2, BASE*6, WHITE);
                DrawRectangle((ecran.width/2)-435, bordureDeJeu.y+250, BASE*12+3, BASE/2, WHITE);
                DrawRectangle((ecran.width/2)-435, bordureDeJeu.y+320, BASE*12+7, BASE/2, WHITE);
                DrawText("FACILE", ecran.width/2-415, bordureDeJeu.y+275, 30, WHITE);

                DrawRectangle((ecran.width/2)+60, bordureDeJeu.y+250, BASE/2, BASE*6, WHITE);
                DrawRectangle((ecran.width/2)-85, bordureDeJeu.y+250, BASE/2, BASE*6, WHITE);
                DrawRectangle((ecran.width/2)-85, bordureDeJeu.y+250, BASE*12+3, BASE/2, WHITE);
                DrawRectangle((ecran.width/2)-85, bordureDeJeu.y+320, BASE*12+7, BASE/2, WHITE);
                DrawText("MOYEN", ecran.width/2-62, bordureDeJeu.y+275, 30, WHITE);

                DrawRectangle((ecran.width/2)+410, bordureDeJeu.y+250, BASE/2, BASE*6, WHITE);
                DrawRectangle((ecran.width/2)+265, bordureDeJeu.y+250, BASE/2, BASE*6, WHITE);
                DrawRectangle((ecran.width/2)+265, bordureDeJeu.y+250, BASE*12+3, BASE/2, WHITE);
                DrawRectangle((ecran.width/2)+265, bordureDeJeu.y+320, BASE*12+7, BASE/2, WHITE);
                DrawText("DIFFICILE", ecran.width/2+278, bordureDeJeu.y+275, 25, WHITE);

                DrawRectangle((ecran.width/2)+600, bordureDeJeu.y+650, BASE/4, BASE*3, RED);
                DrawRectangle((ecran.width/2)+660, bordureDeJeu.y+650, BASE/4, BASE*3, RED);
                DrawRectangle((ecran.width/2)+600, bordureDeJeu.y+650, BASE*6-10, BASE/4, RED);
                DrawRectangle((ecran.width/2)+600, bordureDeJeu.y+678, BASE*6-10, BASE/4, RED);
                DrawText("BEAST", ecran.width/2+608, bordureDeJeu.y+660, 15, RED);



            }break;
            case attentejeupvp:
            {
                ClearBackground(PURPLE);
                DrawText("Utilisez A et Q pour bouger la raquette", ecran.width/5-250, 200, 20, YELLOW);
                DrawText("Utilisez I et J pour bouger la raquette", ecran.width/2+250, 200, 20, YELLOW);
                DrawText("Cliquer sur l'ecran ou ENTRER pour commencer a jouer", ecran.width/5-50, 100, 35, YELLOW);
            }break;
            case attentejeupve:
            {
                ClearBackground(PURPLE);
                DrawText("Utilisez A et Q pour bouger la raquette", ecran.width/5-250, 200, 20, YELLOW);
                DrawText("Cliquer sur l'ecran ou ENTRER pour commencer a jouer", ecran.width/5-50, 100, 35, YELLOW);
            }break;
            case jeupve:
            {
            terrainDeJeu();
            }break;
            case fin:
            {
                ClearBackground(WHITE);
                if(mouvementballe == 1){
                if(win == 1){
                    DrawText("Le Joueur de gauche a GAGNE", (ecran.width/5)+20, 100, 50, PURPLE);
                }else{
                    DrawText("Le Joueur de droite a GAGNE", (ecran.width/5)+20, 100,  50, PURPLE);
                } }else if(win == 1){
                    DrawText("Vous avez GAGNE", (ecran.width/5)+180, 100, 50, PURPLE);
                }else{
                    DrawText("Vous avez PERDU", (ecran.width/5)+180, 100,  50, PURPLE);
                }
                DrawRectangle((ecran.width/2)-60, bordureDeJeu.y+350, BASE/2, BASE*6, PURPLE);
                DrawRectangle((ecran.width/2)-205, bordureDeJeu.y+350, BASE/2, BASE*6, PURPLE);
                DrawRectangle((ecran.width/2)-205, bordureDeJeu.y+350, BASE*12+3, BASE/2, PURPLE);
                DrawRectangle((ecran.width/2)-205, bordureDeJeu.y+420, BASE*12+7, BASE/2, PURPLE);
                DrawText("REJOUER", ecran.width/2-192, bordureDeJeu.y+375, 27, PURPLE);

                DrawRectangle((ecran.width/2)+210, bordureDeJeu.y+350, BASE/2, BASE*6, PURPLE);
                DrawRectangle((ecran.width/2)+65, bordureDeJeu.y+350, BASE/2, BASE*6, PURPLE);
                DrawRectangle((ecran.width/2)+65, bordureDeJeu.y+350, BASE*12+3, BASE/2, PURPLE);
                DrawRectangle((ecran.width/2)+65, bordureDeJeu.y+420, BASE*12+7, BASE/2, PURPLE);
                DrawText("MENU", ecran.width/2+100, bordureDeJeu.y + 375, 30, PURPLE);

                DrawRectangle((ecran.width/2)+600, bordureDeJeu.y, BASE/4, BASE*3, PURPLE);
                DrawRectangle((ecran.width/2)+670, bordureDeJeu.y, BASE/4, BASE*3, PURPLE);
                DrawRectangle((ecran.width/2)+600, bordureDeJeu.y, BASE*6, BASE/4, PURPLE);
                DrawRectangle((ecran.width/2)+600, bordureDeJeu.y+35, BASE*6, BASE/4, PURPLE);
                DrawText("FERMER", ecran.width/2+608, bordureDeJeu.y + 10, 15, PURPLE);

            } break;
            default: break;
            }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

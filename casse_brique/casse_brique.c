#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <assert.h>
#include <time.h>
#include <SDL2/SDL_mixer.h>

#include <unistd.h> 
#include "casse_brique_motor.c"

char str_score[10];
void menu();

void jouer(int mode){                                                                       // FAIT PAR EDGAR
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0){
        SDL_Window* window  = NULL;
        window = SDL_CreateWindow("CASSE BRIQUE",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800,600, 0);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        
        if ( (window != NULL) && (renderer != NULL) ){
            SDL_bool done = SDL_FALSE;
            

            //GENERATEUR DE COULEURS RGB 
        SDL_Color blanc = {255, 255, 255}, 
        rouge = {204, 0, 0}, grey = {224,224,224}, noir = {0, 0, 0};
        


      //CHARGE LES FONTS
        TTF_Font *font5, *font6;
            font5 = TTF_OpenFont("fonts/8_bit.ttf", 14);
            font6 = TTF_OpenFont("fonts/8_bit.ttf", 25);




            // BACKGROUND
                        SDL_Surface* background= IMG_Load("img/level/violet_back.png");
                        SDL_Texture* background_texture = SDL_CreateTextureFromSurface(renderer, background);
                        SDL_Rect coord_background = {.x =0, .y = 0, .w = 800, .h = 600};
            // BALL
                        SDL_Surface* ball = IMG_Load("img/level/ball.png");
                        SDL_Texture* ball_texture = SDL_CreateTextureFromSurface(renderer, ball);
                       
            // RAQUET
                        SDL_Surface* raquet = IMG_Load("img/level/raquet.png");
                        SDL_Texture* raquet_texture = SDL_CreateTextureFromSurface(renderer, raquet);
                        
            // BRICK
                        SDL_Surface* brique = IMG_Load("img/level/brick.png");
                        SDL_Texture* brique_texture = SDL_CreateTextureFromSurface(renderer, brique);

            // END
                        SDL_Surface* lose = IMG_Load("img/level/game_over.png");
                          SDL_Surface* win = IMG_Load("img/level/win.png");

                        SDL_Texture* lose_texture = SDL_CreateTextureFromSurface(renderer, lose);
                          SDL_Texture* win_texture = SDL_CreateTextureFromSurface(renderer, win);

                        SDL_Rect coord_lose = {.x = 200, .y = 200, .w = 400, .h = 200};
                          SDL_Rect coord_win = {.x = 160, .y = 200, .w = 300, .h = 200};
      
            // MUSIQUE
                                     
                        // MUSIC LOADER grâce à lib mixer qui alloue un canal à la musique et la joue en loop grâce à la valeur -1 
                         if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) 
                          { 
                              printf("%s", Mix_GetError());
                          }
                         Mix_Music* music_play;
                         Mix_Chunk* music;
            // DEGRES
                        srand(time(NULL));
                        degres = rand()%((10+1)-1) + 1;
          
                          
            // MODE DE DIFFICULTE
            if( mode == 1) {    
                                
                                coord_raquet.w = 300;
                                speed = 20000;
                                speed_ref = 20000;
                                music_play = Mix_LoadMUS("sounds/music_soft.ogg");  //Pointeur musique dans lequel on stocke la musique en .wav
            }else if( mode == 2){
                                
                                coord_raquet.w = 200;
                                speed = 15000;
                                speed_ref = 15000;
                                music_play = Mix_LoadMUS("sounds/music_medium.ogg");  //Pointeur musique dans lequel on stocke la musique en .wav
            }else if( mode == 3){  
                                
                                coord_raquet.w = 100;
                                speed = 10000;
                                speed_ref = 10000;
                                music_play = Mix_LoadMUS("sounds/music_hard.ogg");  //Pointeur musique dans lequel on stocke la musique en .wav
            }
            
            Mix_AllocateChannels(5);
            Mix_PlayMusic(music_play, -1); //Musique à l'infini //Musique à l'infini

     
  
            int taille_matrice= 0;
            int taille_vertical = 4;
            int taille_horizontal = 14;
            for(int vertical= 2;vertical <= taille_vertical; vertical++){
                for(int horizontal= 0; horizontal < taille_horizontal; horizontal++){
                                                
                                                matrice[taille_matrice].x = 50*horizontal + 50;
                                                matrice[taille_matrice].y = 50*vertical;
                                                matrice[taille_matrice].w = 40;
                                                matrice[taille_matrice].h = 40;
                                                taille_matrice++;
                } 
            }

            SDL_Event event;
                
            refresh(background_texture, coord_background, ball_texture, raquet_texture, brique_texture);
 
            while (!done) {
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        done = SDL_TRUE; //quitte la fenetre
                    }else{
                        switch(event.type) {
                            case SDL_KEYDOWN:
                            switch(event.key.keysym.sym) {
                                case SDLK_UP :
                                     sound_executor(3);
                                        while( (coord_ball.y <  580) && (taille > -1) ){
                                                
                                            SDL_RenderClear(renderer);

                                             ball_balance();
                                             raquet_mouv();
 
                                            refresh(background_texture, coord_background, ball_texture, raquet_texture, brique_texture);

                                            SDL_PollEvent(&raquet_balance);
                                            usleep(speed);
                                        }
 
                                    if(taille <= -1){
                                        music = Mix_LoadWAV("sounds/win.wav");  //Pointeur musique dans lequel on stocke la musique en .wav
                                        Mix_PlayChannel(1, music, 0); //Musique à l'infini
                                        SDL_RenderCopy(renderer, win_texture, 0, &coord_win);                                        
     /* Affiche le score */              score(points);
                                         SDL_Surface* score_1 = TTF_RenderText_Blended(font6,"SCORE", noir);
                                            SDL_Texture* score_1_texture = SDL_CreateTextureFromSurface(renderer, score_1);
                                            SDL_FreeSurface(score_1);
                                            SDL_Rect pos_score_1 = {.x = 450, .y = 550};
                                            SDL_QueryTexture(score_1_texture, NULL, NULL, &pos_score_1.w, &pos_score_1.h);
                                            SDL_RenderCopy(renderer, score_1_texture, NULL, &pos_score_1);

                                         SDL_Surface* score_2 = TTF_RenderText_Blended(font6,str_score, noir);
                                            SDL_Texture* score_2_texture = SDL_CreateTextureFromSurface(renderer, score_2);
                                            SDL_FreeSurface(score_2);
                                            SDL_Rect pos_score_2 = {.x = 600, .y = 550};
                                            SDL_QueryTexture(score_2_texture, NULL, NULL, &pos_score_2.w, &pos_score_2.h);
                                            SDL_RenderCopy(renderer, score_2_texture, NULL, &pos_score_2);
                                            SDL_RenderPresent(renderer);
                                        sleep(7);
                                        Mix_CloseAudio();
                                        done = SDL_TRUE;
                                        restart();
                                        SDL_Quit();
                                        menu();

                                    }else{
                                        sound_executor(4);
                                        SDL_RenderCopy(renderer, lose_texture, 0, &coord_lose);
                                        SDL_RenderPresent(renderer);
                                        score(points);
                                         SDL_Surface* score_1 = TTF_RenderText_Blended(font6,"SCORE", noir);
                                            SDL_Texture* score_1_texture = SDL_CreateTextureFromSurface(renderer, score_1);
                                            SDL_FreeSurface(score_1);
                                            SDL_Rect pos_score_1 = {.x = 450, .y = 550};
                                            SDL_QueryTexture(score_1_texture, NULL, NULL, &pos_score_1.w, &pos_score_1.h);
                                            SDL_RenderCopy(renderer, score_1_texture, NULL, &pos_score_1);

                                         SDL_Surface* score_2 = TTF_RenderText_Blended(font6,str_score, noir);
                                            SDL_Texture* score_2_texture = SDL_CreateTextureFromSurface(renderer, score_2);
                                            SDL_FreeSurface(score_2);
                                            SDL_Rect pos_score_2 = {.x = 600, .y = 550};
                                            SDL_QueryTexture(score_2_texture, NULL, NULL, &pos_score_2.w, &pos_score_2.h);
                                            SDL_RenderCopy(renderer, score_2_texture, NULL, &pos_score_2);
                                            SDL_RenderPresent(renderer);                                
                                        sleep(4); 
                                        restart();
                                        Mix_CloseAudio();
                                        done = SDL_TRUE;
                                        SDL_Quit();
                                        menu();
                                    }
                                break;
                                
                                case SDLK_ESCAPE :
                                    restart();
                                    Mix_CloseAudio();
                                    done = SDL_TRUE;
                                    SDL_Quit();
                                    menu();
                                break;

                                default: 
                                break;
                            } 
                            default: 
                             break;
                        }
                    }
                }
            }
        } 

        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit(); 
    }

}

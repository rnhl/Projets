#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "casse_brique.c"



void how_to();   //FAIT PAR RACHID


void level(){ // FAIT PAR RACHID

    SDL_Renderer *renderer = NULL;
  	SDL_Window *window = NULL;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0)
    {
        window = SDL_CreateWindow("CASSE BRIQUE",
                                 SDL_WINDOWPOS_UNDEFINED, 
                                 SDL_WINDOWPOS_UNDEFINED, 800,600, 0); 
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

      SDL_Surface* background = IMG_Load("img/menu/blurried.bmp");               
      SDL_Texture* background_texture = SDL_CreateTextureFromSurface(renderer, background);
      SDL_FreeSurface(background);
      SDL_Rect pos_background = {.x = 0, .y = 0, .w = 800, .h = 600};
      SDL_RenderCopy(renderer, background_texture, NULL, &pos_background);




      //GENERATEUR DE COULEURS RGB 
        SDL_Color blanc = {255, 255, 255}, 
        rouge = {204, 0, 0}, grey = {224,224,224};
    	


      //CHARGE LES FONTS
      	TTF_Font *font5, *font6;
        	font5 = TTF_OpenFont("fonts/8_bit.ttf", 14);
        	font6 = TTF_OpenFont("fonts/8_bit.ttf", 8);

        SDL_Surface* difficulty = TTF_RenderText_Blended(font5, "DIFFICULTY", blanc);
        SDL_Surface* easy = TTF_RenderText_Blended(font5, "EASY", blanc);
        SDL_Surface* medium = TTF_RenderText_Blended(font5, "MEDIUM", blanc);
        SDL_Surface* hard = TTF_RenderText_Blended(font5, "HARD", rouge);

        SDL_Surface* touche_easy = TTF_RenderText_Blended(font6, "(TOUCHE 1)", grey);
        SDL_Surface* touche_medium = TTF_RenderText_Blended(font6, "(TOUCHE 2)", grey);
        SDL_Surface* touche_hard = TTF_RenderText_Blended(font6, "(TOUCHE 3)", grey);
          						
          						
        SDL_Texture* difficulty_texture = SDL_CreateTextureFromSurface(renderer, difficulty);
        SDL_Texture* easy_texture = SDL_CreateTextureFromSurface(renderer, easy);
        SDL_Texture* medium_texture = SDL_CreateTextureFromSurface(renderer, medium);
        SDL_Texture* hard_texture = SDL_CreateTextureFromSurface(renderer, hard);

        SDL_Texture* touche_easy_texture = SDL_CreateTextureFromSurface(renderer, touche_easy);
        SDL_Texture* touche_medium_texture = SDL_CreateTextureFromSurface(renderer, touche_medium);
        SDL_Texture* touche_hard_texture = SDL_CreateTextureFromSurface(renderer, touche_hard);
          						

        SDL_FreeSurface(difficulty);
        SDL_FreeSurface(easy);
        SDL_FreeSurface(medium);
        SDL_FreeSurface(hard);

        SDL_FreeSurface(touche_easy);
        SDL_FreeSurface(touche_medium);
        SDL_FreeSurface(touche_hard);
          						

        SDL_Rect pos_difficulty = {.x = 345, .y = 165};
        SDL_Rect pos_easy = {.x = 385, .y = 225};
        SDL_Rect pos_medium = {.x = 370, .y = 285};
        SDL_Rect pos_hard = {.x = 380, .y = 345};

        SDL_Rect pos_touche_easy = {.x = 380, .y = 242};
        SDL_Rect pos_touche_medium = {.x = 380, .y = 302};
        SDL_Rect pos_touche_hard = {.x = 375, .y = 362};
          						

        SDL_QueryTexture(difficulty_texture, NULL, NULL, &pos_difficulty.w, &pos_difficulty.h);
        SDL_QueryTexture(easy_texture, NULL, NULL, &pos_easy.w, &pos_easy.h);
        SDL_QueryTexture(medium_texture, NULL, NULL, &pos_medium.w, &pos_medium.h);
        SDL_QueryTexture(hard_texture, NULL, NULL, &pos_hard.w, &pos_hard.h);

        SDL_QueryTexture(touche_easy_texture, NULL, NULL, &pos_touche_easy.w, &pos_touche_easy.h);
        SDL_QueryTexture(touche_medium_texture, NULL, NULL, &pos_touche_medium.w, &pos_touche_medium.h);
        SDL_QueryTexture(touche_hard_texture, NULL, NULL, &pos_touche_hard.w, &pos_touche_hard.h);
        						
        
        SDL_RenderCopy(renderer, difficulty_texture, NULL, &pos_difficulty);
        SDL_RenderCopy(renderer, easy_texture, NULL, &pos_easy);
        SDL_RenderCopy(renderer, medium_texture, NULL, &pos_medium);
        SDL_RenderCopy(renderer, hard_texture, NULL, &pos_hard);

        SDL_RenderCopy(renderer, touche_easy_texture, NULL, &pos_touche_easy);
        SDL_RenderCopy(renderer, touche_medium_texture, NULL, &pos_touche_medium);
        SDL_RenderCopy(renderer, touche_hard_texture, NULL, &pos_touche_hard);
          						

    		SDL_RenderPresent(renderer);

        SDL_bool program_launched = SDL_TRUE;
    	  while(program_launched)
      	{
        	SDL_Event event;

        	while(SDL_PollEvent(&event))
        	{
              
         		switch(event.type)
            	{
               
                	case SDL_KEYDOWN:   										// TYPE 1 SDL KEYDOWN
                  
                    	switch(event.key.keysym.sym)
                  		{
                    
                        	case SDLK_ESCAPE:                 	    						
                          		program_launched = SDL_FALSE;
                          		SDL_Quit();
                          		menu();
                			    break;

                		
                			    case SDLK_1:
    											   mode = 1;
                      			 program_launched = SDL_FALSE;
                              SDL_Quit();
                              how_to();
                          break;

                          case SDLK_2:
    											    mode = 2;
                      				program_launched = SDL_FALSE;
                              SDL_Quit();
                              how_to();
                          break;

                          case SDLK_3:
    											    mode = 3;
                      				program_launched = SDL_FALSE;
                              SDL_Quit();
                              how_to();
                          break;

                          default:
                          continue;
                          }  

                          case SDL_QUIT:										// TYPE 2 SDL QUIT
                				      program_launched = SDL_FALSE;
                			    break;

                          default:
                          continue;


                           }
                       }
                   
             }
    }
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
TTF_Quit();
Mix_CloseAudio();
SDL_Quit(); 
}


void how_to(){                                                          // FAIT PAR RACHID

    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0)
    {
        window = SDL_CreateWindow("CASSE BRIQUE",
                                 SDL_WINDOWPOS_UNDEFINED, 
                                 SDL_WINDOWPOS_UNDEFINED, 800,600, 0); 
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

      //GENERATEUR DE COULEURS RGB 
        SDL_Color blanc = {255, 255, 255}, grey = {224,224,224}, noir = {0, 0, 0};
        
      
      //CHARGE LES FONTS
        TTF_Font *font5;
          font5 = TTF_OpenFont("fonts/8_bit.ttf", 18);
          //font6 = TTF_OpenFont("fonts/8_bit.ttf", 8);
      

        SDL_Surface* background = IMG_Load("img/level/how_to.png");               
        SDL_Texture* background_texture = SDL_CreateTextureFromSurface(renderer, background);
        SDL_FreeSurface(background);
        SDL_Rect pos_background = {.x = 0, .y = 0, .w = 800, .h = 600};
        SDL_RenderCopy(renderer, background_texture, NULL, &pos_background);

        SDL_Surface* how_to = TTF_RenderText_Blended(font5, "JOUEZ AVEC LES FLECHES", blanc);
        SDL_Texture* how_to_texture = SDL_CreateTextureFromSurface(renderer, how_to);
        SDL_FreeSurface(how_to);
        SDL_Rect pos_how_to = {.x = 230, .y = 270};
        SDL_QueryTexture(how_to_texture, NULL, NULL, &pos_how_to.w, &pos_how_to.h);
        SDL_RenderCopy(renderer, how_to_texture, NULL, &pos_how_to);

        SDL_RenderPresent(renderer);

        TTF_CloseFont(font5);

        SDL_Delay(4000);
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        jouer(mode);                    
  }
}








/*


        char str[10];
int nombre = 52;

void test_1(){
  int nombre = 52;
  printf("%d\n", nombre);

  char str[10];
  sprintf(str, "%d", nombre);


}
        test_1();
        sprintf(str, "%d", nombre);

        SDL_Surface* test = TTF_RenderText_Blended(font5, str, noir);
        SDL_Texture* test_texture = SDL_CreateTextureFromSurface(renderer, test);
        SDL_FreeSurface(test);
        SDL_Rect pos_test = {.x = 270, .y = 370};
        SDL_QueryTexture(test_texture, NULL, NULL, &pos_test.w, &pos_test.h);
        SDL_RenderCopy(renderer, test_texture, NULL, &pos_test);
*/
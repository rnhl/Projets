#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

  SDL_Renderer* renderer = NULL;
  char direction_x = 'D'; //droite gauche
  char direction_y = 'M'; //monte descente
  int speed, speed_ref = 15000;
  int mode;
  int degres = 5 ;
  int taille = 56;
  int points;
  char str_score[10];
  SDL_Rect coord_ball = {.x = 400, .y = 510, .w = 40, .h = 40};
  SDL_Rect coord_raquet = {.x =300, .y = 550, .w = 200, .h = 20};
  SDL_Event raquet_balance;
  SDL_Rect matrice[57] ={0}; //taille matrice +1 que la VAR taille, pour contenir \0
  SDL_Rect *pointer_matrice = matrice;
   Mix_Chunk *sound;

void refresh(SDL_Texture* background_texture, SDL_Rect coord_background, SDL_Texture* ball_texture, SDL_Texture* raquet_texture, SDL_Texture* brique_texture); // FAIT PAR EDGAR
void colapse();                             // FAIT PAR EDGAR
void movement();                            // FAIT PAR EDGAR
void border_signal();                       // FAIT PAR EDGAR
void rebounce();                            // FAIT PAR EDGAR
void ball_balance();                        // FAIT PAR EDGAR
void raquet_mouv();                         // FAIT PAR EDGAR
void reorganise_tableau( int brique_enleve_adresse); // FAIT PAR EDGAR
void sound_executor(int sound_order);       // FAIT PAR EDGAR
void restart();                             // FAIT PAR RACHID





//############################################
// ################ FONCTIONS ################
void refresh(SDL_Texture* background_texture, SDL_Rect coord_background, SDL_Texture* ball_texture, SDL_Texture* raquet_texture, SDL_Texture* brique_texture){
  SDL_RenderCopy(renderer, background_texture, 0, &coord_background);
  SDL_RenderCopy(renderer, ball_texture, 0, &coord_ball);
  SDL_RenderCopy(renderer, raquet_texture, 0, &coord_raquet);
  for(int i= 0; i <= taille; i++){
    SDL_RenderCopy(renderer, brique_texture, 0, &matrice[i]);  
  }
  SDL_RenderPresent(renderer);
}

void reorganise_tableau(int brique_enleve_adresse){

  SDL_Rect brique_enleve_contenue = pointer_matrice[brique_enleve_adresse];
  int i ;
  for( i = brique_enleve_adresse; i < taille; i++){
    pointer_matrice[i] = pointer_matrice[i + 1];
  }
  pointer_matrice[i] = brique_enleve_contenue;
  taille = taille-1 ;
}

void colapse(){ 
  int x, y;
  for(int i = 0; i <= taille; i++){                                                   // BOUCLE POUR TESTER CHAQUE BRIQUE RESTANTE 
    x = pointer_matrice[i].x;                                                          // COORDONNÉE X DE LA BRIQUE i
    y = pointer_matrice[i].y;                                                          // COORDONNÉE Y DE LA BRIQUE i

    if( ( (coord_ball.x > x-30) && (coord_ball.x < x+30) ) && ((coord_ball.y > y-30) && (coord_ball.y < y+30) )){ // SI LA BALLE RENCONTRE LA BRIQUE
      sound_executor(1);
      x =  abs(coord_ball.x - x) ;                                                     // CALCUL LA POSITION X DE LA BALLE PAR RAPPORT A LA BRIQUE
      y =  abs(coord_ball.y - y) ;                                                     // CALCUL LA POSITION Y DE LA BALLE PAR RAPPORT A LA BRIQUE
      /*
          ^ Y   
          |........ 
          |       .
          |       @  <-(balle)
          |       .
          |__________> X
      */
      if(x < y){                                                                       // SI LA DISTANCE "BALLE - AXE Y"  EST PLUS GRANDE QUE LA DISTANCE "BALLE - AXE X"..
                                                                                       // ...ALORS LA BALLE À TOUCHÉE LE HAUT OU LE BAS DE LA BRIQUE
         direction_y = (direction_y == 'M') ? 'D' : 'M';                             // ON INVERSE ALORS LE SENS MONTÉ-DESCENTE
         reorganise_tableau(i);                               // ON REORGANISE LE TABLEAU DE FACON À PLACER LA BRIQUE ÉLÉMINÉE À LA FIN DU TABLEAU..
         points = points + 50;                                                                               // ...ET LA TAILLE DU TABLEAU LISIBLE DIMINUE (-1) 
      }
      /*
          ^ Y   
          |....@...  <-(balle)
          |       .
          |       .
          |       .
          |__________> X
      */
      else if(x >= y){                                                                 // SI LA DISTANCE "BALLE - AXE X"  EST PLUS GRANDE QUE LA DISTANCE "BALLE - AXE Y"..
                                                                                       // ...ALORS LA BALLE À TOUCHÉE LE COTÉ
         direction_x = (direction_x == 'D') ? 'G' : 'D';                             // ON INVERSE ALORS LE SENS DROITE GAUCHE
         reorganise_tableau(i);                               // ON REORGANISE LE TABLEAU DE FACON À PLACER LA BRIQUE ÉLÉMINÉE À LA FIN DU TABLEAU..
         points = points + 50;                                                                               // ...ET LA TAILLE DU TABLEAU LISIBLE DIMINUE (-1)                 
      }
    }
  } 
}

void movement(){
  switch(direction_y){ // haut /bas 
                        case 'M':                                                      // SI DIRECTION Y EST SUR: MONTER 

                              if(direction_x == 'D'){                                  // SI DIRECTION X EST SUR: DROITE
                                coord_ball.x = coord_ball.x + (10 - degres);                     // DEPLACEMENT DE 5px A DROITE
                                coord_ball.y = coord_ball.y - degres;               // DEPLACEMENT EN Y EN FONCTION DE DEGRES
                              }
                              else if(direction_x == 'G'){                             // SI DIRECTION X EST SUR: GAUCHE
                                coord_ball.x = coord_ball.x - (10 - degres);                     // DEPLACEMENT DE 5px A GAUCHE
                                coord_ball.y = coord_ball.y - degres;               // DEPLACEMENT EN Y EN FONCTION DE DEGRES
                              }

                         break;

                        case 'D':                                                      // SI DIRECTION Y EST SUR: DESCENTE

                              if(direction_x == 'D'){                                  // SI DIRECTION X EST SUR: DROITE
                                coord_ball.x = coord_ball.x + (10 - degres);                     // DEPLACEMENT DE 5px A DROITE
                                coord_ball.y = coord_ball.y + degres;               // DEPLACEMENT EN Y EN FONCTION DE DEGRES
                              }
                              else if(direction_x == 'G'){                             // SI DIRECTION X EST SUR: GAUCHE 
                                coord_ball.x = coord_ball.x - (10 - degres);                     // DEPLACEMENT DE 5px A GAUCHE
                                coord_ball.y = coord_ball.y + degres;               // DEPLACEMENT EN Y EN FONCTION DE DEGRES
                              }

                         break;
  }
} 

void border_signal(){

  if(coord_ball.y < 0){                                                                // SI LA BALLE EST TOUJOURS DANS LE CADRE
    sound_executor(2);
    direction_y = (direction_y == 'M') ? 'D' : 'M';  
  }else if( (coord_ball.y >= 515) && (coord_ball.y <= 525)){ 
     rebounce();
  }
                                                                                        // INVERSE LE DEPLACEMENT DE LA BALLE DANS LE SENS Y
  if((coord_ball.x < 0) || (coord_ball.x > 760)){                                      // SI LA BALLE EST TOUJOURS DANS LE CADRE
    sound_executor(2);
    direction_x = (direction_x == 'D') ? 'G' : 'D';                                   // INVERSE LE DEPLACEMENT DE LA BALLE DANS LE SENS X
  }

  
}

void rebounce(){
  if( (coord_ball.x > coord_raquet.x - 30) && (coord_ball.x < coord_raquet.x + coord_raquet.w)){ // SI LA BALLE EST SUR LA RAQUETTE
    direction_y = 'M';                                                                 // CHANGE LE SENS : MONTER
    int calcul_degres = ((coord_ball.x - coord_raquet.x + 20)*100)/(coord_raquet.w + 20);          // CALCUL DU POURCENTAGE PARCOURU PAR LA BALLE SUR LA RAQUETTE (MIN: 0%, MAX:100%)
     // -0.02x2+2x+10 = fonction 2 degres
     calcul_degres = abs(calcul_degres);                                                // PREVIENS DU BUG SI LE POURCENTAGE EST NEGATIF
    calcul_degres = (-3 * pow(calcul_degres, 2) / 100) + 3 * calcul_degres +20;         // FORMULE CALCUL DE L'INCLINASION A DONNER A LA BALLE, SELON EQUATION DE POLYNOME...
                                                                                        // ...CF IMAGES DANS LE DOSSIER CASSE BRIQUE
    //printf("f(x) = %d degres\n\n\n", calcul_degres);
    degres = calcul_degres/20;                                                         // CONVERTIR LES ANGLES COMPRIS ENTRE 0 ET 100 EN ANGLES COMPRIS ENTRE 0 ET 5
    coord_ball.y = 514;                                                                // REMONTE LA POSITION DE LA BALLE
    speed = speed_ref;
    sound_executor(2);
    points = points - 10;

  }
}

void ball_balance(){

     movement();
     border_signal();
     colapse();
}

void raquet_mouv(){
            switch(raquet_balance.type) {
                            case SDL_KEYDOWN:
                            switch(raquet_balance.key.keysym.sym) {
                                case SDLK_LEFT:                                                          // DEPLACEMENT DE LA RAQUETTE A DROITE
                                  if(coord_raquet.x > 0){                                                // SI LA RAQUETTE EST TOUJOURS DANS LE CADRE
                                    coord_raquet.x = coord_raquet.x - (coord_raquet.w / 6);              // DEPLACEMENT A DE 50 px A DROITE
                                  }
                                break;

                                case SDLK_RIGHT:                                                         // DEPLACEMENT DE LA RAQUETTE A GAUCHE
                                  if(coord_raquet.x < (800 - coord_raquet.w)){                           // SI LA RAQUETTE EST TOUJOURS DANS LE CADRE
                                    coord_raquet.x = coord_raquet.x + (coord_raquet.w / 6);              // DEPLACEMENT A DE 50 px A GAUCHE
                                  }  
                                break;
                                    
                                default:
                                break;
                            }
                            default:
                             break;
                        }
}


void sound_executor(int sound_order){
  switch(sound_order) {
    case 1:
      sound =  Mix_LoadWAV("sounds/brick_hit.wav");
    break;

    case 2:
      sound =  Mix_LoadWAV("sounds/bump.wav");
    break;

    case 3:
      sound =  Mix_LoadWAV("sounds/sound_launch.wav");
    break;

    case 4:
      sound =  Mix_LoadWAV("sounds/lose.wav");
    break;

    default:
    break;
  }

  Mix_PlayChannel(2, sound, 0); 
}



void score(int points){
  sprintf(str_score, "%d", points);
  }

void restart(){
  speed = 15000;
  speed_ref = 15000;
  mode = 0;
  degres = 5 ;
  taille = 56;
  points = 0;
  coord_ball.x = 400;
  coord_ball.y = 510;
  coord_raquet.x =300;
  coord_raquet.y = 550;
  direction_x = 'D'; //droite gauche
  direction_y = 'M'; //monte descente
  for( int taille_supression = taille; taille_supression >= 0; taille_supression--){
     matrice[taille_supression].x = 0;
     matrice[taille_supression].y = 0;
     matrice[taille_supression].w = 0;
     matrice[taille_supression].h = 0;
  }

}
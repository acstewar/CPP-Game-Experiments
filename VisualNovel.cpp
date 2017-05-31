#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

class Sprite{
    public:
        SDL_Surface* image;
        SDL_Rect rect;
        int frame;//Current frame
        int length;//Length of frame sequence
        int xframe;//X Size of frame
        int yframe;//Y Size of frame
    public:
        Sprite(SDL_Surface* newimage,SDL_Rect newrect,int newframe,int newlength,int newxframe,int newyframe)
        {
        image = newimage;
        rect = newrect;
        frame = newframe;
        length = newlength;
        xframe;//X Size of frame
        yframe;//Y Size of frame
        }
        Sprite()
        {
        }
};

//Make an array or vector full of SDL_Rect to draw.

class Textbox {
    public:
        Textbox* one;
        Textbox* two;
        Textbox* three;
        Sprite* char1;
        Sprite* char2;
        Sprite* background;
        int chars, choices;
        char text [60];
        char optiontext1 [60];
        char optiontext2 [60];
        char optiontext3 [60];
    public:
        Textbox(Textbox* newone, Textbox* newtwo, Textbox* newthree, Sprite* newchar1, Sprite* newchar2, Sprite* newbackground, int newchars, int newchoices, char newtext [60], char newoptiontext1 [60], char newoptiontext2 [60], char newoptiontext3 [60])
        {
        one = newone;
        two = newtwo;
        three = newthree;
        char1 = newchar1;
        char2 = newchar2;
        background = newbackground;
        chars = newchars;
        choices = newchoices;
        for(int i=0;i<60;i++)
            {
            text[i] = newtext[i];
            optiontext1[i] = newoptiontext1[i];
            optiontext2[i] = newoptiontext2[i];
            optiontext3[i] = newoptiontext3[i];
            }
        }
        Textbox()
        {
        }
};

SDL_Surface *load_image( std::string filename )
{
    SDL_Surface* loadedImage = SDL_LoadBMP( filename.c_str() );
    SDL_Surface* optimizedImage = NULL;

    if (loadedImage != NULL)
    {
        optimizedImage = SDL_DisplayFormat( loadedImage );
        SDL_FreeSurface( loadedImage);
        if( optimizedImage != NULL)
        {
            Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 255, 255, 255);
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey);
        }
    }
    else
        {
        return loadedImage;
        }
    return optimizedImage;
}

int main ( int argc, char** argv )
{
    bool quit = false;
    Uint32 start = 0;
    bool running = true;
    start = SDL_GetTicks();

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    //Initialize TTF
    if( TTF_Init() < 0)
    {
        printf( "Unable to init TTF: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(1280, 720, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

//Load essential game images:

    //SDL_Surface* button = load_image("button.bmp");
    //SDL_Surface* bmp = load_image("cb.bmp");

    SDL_Surface* person1 = load_image("person1.bmp");
    SDL_Surface* person2 = load_image("person2.bmp");
    SDL_Surface* blank = load_image("blank.bmp");

    SDL_Surface* button = SDL_LoadBMP("button.bmp");
    if (!button)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* bmp = SDL_LoadBMP("cb.bmp");
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* forest = SDL_LoadBMP("mesh.bmp");

    if (!forest)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* textbox = SDL_LoadBMP("textbox.bmp");
    if (!textbox)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* button2 = SDL_LoadBMP("button2.bmp");
    if (!button2)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
    }

    // centre the bitmap on screenSDL_BlitSurface(news.image, 0, screen, &news.rect);
    SDL_Rect dstrect;
    dstrect.x = (screen->w - bmp->w) / 2;
    dstrect.y = (screen->h - bmp->h) / 2;

    Sprite news = Sprite();
    Sprite invisible = Sprite(blank,dstrect,1,1,0,0);

    //Dynamically allocated array of sprites to render.
    int sprsize = 10;
    Sprite sprs[sprsize];

    //Sprite* sprs;
    //The initial dynamically allocated array caused a segfault. Creating an array of constant size rectified the problem.
    //Sprite* sprs;
    //sprs = new Sprite[sprsize];

    dstrect.x = 0;
    dstrect.y = 0;
    news = Sprite(forest,dstrect,1,1,0,0);
    sprs[0] = news;

    dstrect.x = 120;
    dstrect.y = 176;
    news = Sprite(person1,dstrect,1,1,0,0);
    sprs[1] = news;

    dstrect.x = 1017;
    dstrect.y = 176;
    news = Sprite(person2,dstrect,1,1,0,0);
    sprs[2] = news;

    dstrect.x = 120;
    dstrect.y = 396;
    news = Sprite(textbox,dstrect,1,1,0,0);
    sprs[3] = news;

    //Text itself
    TTF_Font *font = NULL;
    SDL_Color textColor = {255,255,255};
    font = TTF_OpenFont( "MySketchFont.ttf", 28 );
    char msg[60] = "";

    SDL_Surface* message = TTF_RenderText_Solid( font, msg, textColor );
    dstrect.x = 140;
    dstrect.y = 416;
    news = Sprite(message,dstrect,1,1,0,0);
    sprs[4] = news;

    dstrect.x = 331;
    dstrect.y = 32;
    news = Sprite(button,dstrect,1,1,0,0);
    sprs[5] = news;

    dstrect.x = 331;
    dstrect.y = 132;
    news = Sprite(button,dstrect,1,1,0,0);
    sprs[6] = news;

    dstrect.x = 331;
    dstrect.y = 232;
    news = Sprite(button,dstrect,1,1,0,0);
    sprs[7] = news;

    char buttontext1[60] = "A";
    SDL_Surface* button1message = TTF_RenderText_Solid( font, buttontext1, textColor );
    dstrect.x = 341;
    dstrect.y = 44;
    news = Sprite(button1message,dstrect,1,1,0,0);
    sprs[8] = news;

    char buttontext2[60] = "B";
    SDL_Surface* button2message = TTF_RenderText_Solid( font, buttontext2, textColor );
    dstrect.x = 341;
    dstrect.y = 144;
    news = Sprite(button2message,dstrect,1,1,0,0);
    sprs[9] = news;

    char buttontext3[60] = "C";
    SDL_Surface* button3message = TTF_RenderText_Solid( font, buttontext3, textColor );
    dstrect.x = 341;
    dstrect.y = 244;
    news = Sprite(button3message,dstrect,1,1,0,0);
    sprs[10] = news;

    //Current is the current text box we're on.
    Uint32 point = start;
    Textbox nobox = Textbox();
    char blankmsg[60] = "";

    char newmsg[60] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    strcpy(buttontext1, "A");
    strcpy(buttontext2, "A");
    strcpy(buttontext3, "A");
    Textbox one = Textbox(&one,&one,&one,&sprs[1],&sprs[2],&sprs[0],26,3,newmsg,buttontext1,buttontext2,buttontext3);

    //let's create a bunch of textboxes

    strcpy(newmsg, "This is the first message");
    strcpy(buttontext1, "This is the first choice");
    strcpy(buttontext2, "This is the second choice");
    strcpy(buttontext3, "This is the third choice");
    Textbox current = Textbox(&one,&one,&one,&sprs[1],&sprs[2],&sprs[0],25,3,newmsg,buttontext1,buttontext2,buttontext3);

    int letter = 0;
    dstrect.x = 90;
    dstrect.y = 266;

    int x = 0;
    int y = 0;
    bool switchflag = true;

    // program main loop
    bool done = false;
    while (!done)
    {
        if(switchflag)
        {
            for(int i = 5;i<sprsize+1;i++)
            {
            sprs[i].image = blank;
            }

            if(current.choices == 2 && letter == current.chars)
            {
                if(letter == current.chars)
                {
                sprs[5].image = button;
                sprs[8].image = button1message;
                sprs[6].image = button;
                sprs[9].image = button2message;
                }
            }

            if(current.choices == 3 && letter == current.chars)
            {
                if(letter == current.chars)
                {
                sprs[5].image = button;
                sprs[8].image = button1message;
                sprs[6].image = button;
                sprs[9].image = button2message;
                sprs[7].image = button;
                sprs[10].image = button2message;
                }
            }
            if(current.choices == 3)
            {
                for(int i = 5;i<sprsize+1;i++)
                {
                sprs[i].image = blank;
                }
                if(letter == current.chars)
                {
                sprs[5].image = button;
                sprs[8].image = button1message;
                sprs[6].image = button;
                sprs[9].image = button2message;
                sprs[7].image = button;
                sprs[10].image = button3message;
                }
            switchflag = false;
            }
        }

    if(SDL_GetTicks() > point + 100 && letter < current.chars)
        {
            if(letter < 60)
            {
            point = SDL_GetTicks();
            msg[letter] = current.text[letter];
            letter+=1;
            }
        }        if(current.choices == 1)
        {
            for(int i = 5;i<sprsize+1;i++)
            {
            sprs[i].image = blank;
            }
        }

        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
                    sprs[6].image = button;
            sprs[9].image = button2message;    case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        {
                        done = true;
                        break;
                        }
                    if(event.key.keysym.sym == SDLK_SPACE)
                        {
                        if(letter < current.chars)
                            {
                            for(int i = 0;i < 60;i++)
                                {
                                msg[i] = current.text[i];
                                }
                            letter = current.chars;
                            switchflag = true;
                            }
                        else
                            {
                            if(current.choices == 1)
                                {
                                letter = 0;
                                current = *current.one;
                                for(int i = 0;i < 60;i++)
                                    {
                                    msg[i] = blankmsg[i];
                                    }
                                switchflag = true;
                                }
                            }
                        break;
                    }
                }
            //Mouse event:
            case SDL_MOUSEMOTION:
                {
                x = event.motion.x;
                y = event.motion.y;
                    if(current.choices == 2 || current.choices == 3 && letter == current.chars)
                    {
                    if(x > sprs[5].rect.x && x < (sprs[5].rect.x + sprs[5].rect.w) && y > sprs[5].rect.y && y < (sprs[5].rect.y + sprs[5].rect.h))
                        {
                        sprs[5].image = button2;
                        }
                    else
                        {
                        sprs[5].image = button;
                        }
                    if(x > sprs[6].rect.x && x < (sprs[6].rect.x + sprs[6].rect.w) && y > sprs[6].rect.y && y < (sprs[6].rect.y + sprs[6].rect.h))
                        {
                        sprs[6].image = button2;
                        }
                    else
                        {
                        sprs[6].image = button;
                        }
                    }

                    if(current.choices == 3 && letter == current.chars)
                    {
                    if(x > sprs[7].rect.x && x < (sprs[7].rect.x + sprs[7].rect.w) && y > sprs[7].rect.y && y < (sprs[7].rect.y + sprs[7].rect.h))
                        {
                        sprs[7].image = button2;
                        }
                    else
                        {
                        sprs[7].image = button;
                        }
                    break;
                    }
                }

            case SDL_MOUSEBUTTONDOWN:
                {
                if(event.button.button == SDL_BUTTON_LEFT)
                    {
                    x = event.button.x;
                    y = event.button.y;
                    if(current.choices == 2 || current.choices == 3)
                        {
                        //First box
                        if(x > sprs[5].rect.x && x < (sprs[5].rect.x + sprs[5].rect.w) && y > sprs[5].rect.y && y < (sprs[5].rect.y + sprs[5].rect.h))
                            {
                            letter = 0;
                            current = *current.one;
                            for(int i = 0;i < 60;i++)
                                {
                                 if(current.choices == 1)
                                    {
                                    for(int i = 5;i<sprsize+1;i++)
                                        {
                                        sprs[i].image = blank;
                                        }
                                    }
                                    msg[i] = blankmsg[i];
                                    buttontext1[i] = current.optiontext1[i];
                                    buttontext2[i] = current.optiontext2[i];
                                    buttontext3[i] = current.optiontext3[i];

                                }
                                switchflag = true;
                            }
                        //Second box
                        if(x > sprs[6].rect.x && x < (sprs[6].rect.x + sprs[6].rect.w) && y > sprs[6].rect.y && y < (sprs[6].rect.y + sprs[6].rect.h))
                            {
                            letter = 0;
                            current = *current.two;
                            for(int i = 0;i < 60;i++)
                                {
                                msg[i] = blankmsg[i];
                                buttontext1[i] = current.optiontext1[i];
                                buttontext2[i] = current.optiontext2[i];
                                buttontext3[i] = current.optiontext3[i];
                                }
                            switchflag = true;
                            }
                        }
                    if(current.choices == 3)
                        {
                        //Third box
                        if(x > sprs[7].rect.x && x < (sprs[7].rect.x + sprs[7].rect.w) && y > sprs[7].rect.y && y < (sprs[7].rect.y + sprs[7].rect.h))
                            {
                            letter = 0;
                            current = *current.three;
                            for(int i = 0;i < 60;i++)
                                {
                                msg[i] = blankmsg[i];
                                buttontext1[i] = current.optiontext1[i];
                                buttontext2[i] = current.optiontext2[i];
                                buttontext3[i] = current.optiontext3[i];
                                }
                            switchflag = true;
                            }
                        }
                    }
                }// end switch
            } // end of message processing DRAWING STARTS HERE
        }

        button1message = TTF_RenderText_Solid(font, buttontext1, textColor );
        button2message = TTF_RenderText_Solid(font, buttontext2, textColor );
        button3message = TTF_RenderText_Solid(font, buttontext3, textColor );

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // draw bitmap

        //Update text
        message = TTF_RenderText_Solid(font, msg, textColor );
        sprs[4].image = message;

        //Blit
        for(int i = 0;i<sprsize+1;i++)
        {
        //news = sprs[i];
        SDL_BlitSurface(sprs[i].image, 0, screen, &sprs[i].rect);
        }

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop

    //free loaded bitmap

    TTF_CloseFont(font);
    SDL_FreeSurface(bmp);
    SDL_FreeSurface(forest);
    SDL_FreeSurface(button);
    SDL_FreeSurface(person1);
    SDL_FreeSurface(person2);
    SDL_FreeSurface(textbox);
    SDL_FreeSurface(message);

    // all is well :^)
    printf("Exited cleanly\n");
    return 0;
}

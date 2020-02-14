#ifndef BUTTON_H_  
#define BUTTON_H_

#include "SDL2/SDL.h"
#include "pics.h" 

static SDL_Rect clipsType[10][4] = { {{60, 0, 60, 60}, {0, 0, 60, 60}, {120, 0, 60, 60}, {60, 0, 60, 60}} };

class Button
{
    private:
    //The attributes of the button
    SDL_Rect box;

    //The part of the button sprite sheet that will be shown
    SDL_Rect* clip;
    
    SDL_Rect clips[ 4 ];
    int CLIP_MOUSEOVER;
	int CLIP_MOUSEOUT;
	int CLIP_MOUSEDOWN;
	int CLIP_MOUSEUP;

    public:
    //Initialize the variables
    int picnum;
    Button(){
    	CLIP_MOUSEOVER = 0;
		CLIP_MOUSEOUT = 1;
		CLIP_MOUSEDOWN = 2;
		CLIP_MOUSEUP = 3;
	}
    Button(int pn, int type, int x, int y, int w, int h){
	    //Set the button's attributes
    	CLIP_MOUSEOVER = 0;
		CLIP_MOUSEOUT = 1;
		CLIP_MOUSEDOWN = 2;
		CLIP_MOUSEUP = 3;
	    box.x = x;
	    box.y = y;
	    box.w = w;
	    box.h = h;
	    picnum = pn;
	    set_clips(type);
	
	    //Set the default sprite
	    clip = &clips[ CLIP_MOUSEOUT ];
	}
	void set_button(int pn, int type, int x, int y, int w, int h)
	{
	    //Set the button's attributes
		box.x = x;
		box.y = y;
		box.w = w;
		box.h = h;
	    picnum = pn;
	    set_clips(type);
	
	    //Set the default sprite
	    clip = &clips[ CLIP_MOUSEOUT ];
	}
	void set_box(int x, int y, int w, int h) {
		box.x = x;
		box.y = y;
		box.w = w;
		box.h = h;
	}

    //Handles events and set the button's sprite region
    int handle_events(SDL_Event event)
	{
	    //The mouse offsets
	    int x = 0, y = 0;
	    int re = 0;
	
	    //If the mouse moved
	    if( event.type == SDL_MOUSEMOTION )
	    {
	        //Get the mouse offsets
	        x = event.motion.x;
	        y = event.motion.y;
	
	        //If the mouse is over the button
			if ((x > RR.ww(box.x)) && (x < RR.ww(box.x + box.w)) && (y > RR.hh(box.y)) && (y < RR.hh(box.y + box.h)))
	        {
	            //Set the button sprite
	            clip = &clips[ CLIP_MOUSEOVER ];
	            re = 2;
	        }
	        //If not
	        else
	        {
	            //Set the button sprite
	            clip = &clips[ CLIP_MOUSEOUT ];
	        }
	    }
	    //If a mouse button was pressed
	    if( event.type == SDL_MOUSEBUTTONDOWN )
	    {
	        //If the left mouse button was pressed
	        if( event.button.button == SDL_BUTTON_LEFT )
	        {
	            //Get the mouse offsets
	            x = event.button.x;
	            y = event.button.y;
	
	            //If the mouse is over the button
				if ((x > RR.ww(box.x)) && (x < RR.ww(box.x + box.w)) && (y > RR.hh(box.y)) && (y < RR.hh(box.y + box.h)))
	            {
	                //Set the button sprite
	                clip = &clips[ CLIP_MOUSEDOWN ];
	                re = 1;
	            }
	        }
	    }
	    //If a mouse button was released
	    if( event.type == SDL_MOUSEBUTTONUP )
	    {
	        //If the left mouse button was released
	        if( event.button.button == SDL_BUTTON_LEFT )
	        {
	            //Get the mouse offsets
	            x = event.button.x;
	            y = event.button.y;
	
	            //If the mouse is over the button
				if ((x > RR.ww(box.x)) && (x < RR.ww(box.x + box.w)) && (y > RR.hh(box.y)) && (y < RR.hh(box.y + box.h)))
	            {
	                //Set the button sprite
	                clip = &clips[ CLIP_MOUSEUP ];
	                re = 3;
	            }
	        }
	    }
	    return re;
	}
	void leave_button(){
		clip = &clips[ CLIP_MOUSEOUT ];
	}

    //Shows the button on the screen
    void show(){
	    //Show the button
	    //apply_surface( box.x, box.y, buttonSheet, screen, clip );
	    //SDL_RenderCopy ( myRenderer, hello->getPicText(picnum), clip, &box);
		//SDL_RenderCopy(myRenderer, hello->getPicText(picnum), clip, &box);
		sogr(picnum, clip, &box);
	}
	
	void set_clips(int type)
	{
	    //Clip the sprite sheet
		clips[ CLIP_MOUSEOVER ] = clipsType[type][CLIP_MOUSEOVER];
		clips[ CLIP_MOUSEOUT ] = clipsType[type][CLIP_MOUSEOUT];
		clips[ CLIP_MOUSEDOWN ] = clipsType[type][CLIP_MOUSEDOWN];
		clips[ CLIP_MOUSEUP ] = clipsType[type][CLIP_MOUSEUP];
	}
};

#endif

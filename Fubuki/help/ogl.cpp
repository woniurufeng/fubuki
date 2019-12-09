#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
bool quit;
SDL_Window* window;
SDL_GLContext glContext;
SDL_Event sdlEvent;
GLuint      texture;
float x = 0, y = 0;
void Init()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("SDL+OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	glContext = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(1);
	glewInit();
	glEnable(GL_TEXTURE_2D);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}
void LoadImage()
{
	SDL_Surface* tmp = IMG_Load("items/test/water.png");
	tmp = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_ABGR8888, 0);
	texture = gluBuild2DMipmaps(GL_TEXTURE_2D, 4, tmp->w, tmp->h, GL_RGBA, GL_UNSIGNED_BYTE, tmp->pixels);
	SDL_FreeSurface(tmp);
}
void Draw()
{
	if (x >= 5)  x = 0;
	if (y >= 5)  y = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glScaled(1.0f / 10, 1.0f / 10, 1.0f / 10);

	glPushMatrix();
	glEnable(GL_BLEND);
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);
	glTranslatef(0.0f, 0.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2f(5.0f + x, 5.0f + y); glVertex3f(-10.0f, 10.0f, 0.0f);
	glTexCoord2f(5.0f + x, 0.0f + y); glVertex3f(10.0f, 10.0f, 0.0f);
	glTexCoord2f(0.0f + x, 0.0f + y); glVertex3f(10.0f, -10.0f, 0.0f);
	glTexCoord2f(0.0f + x, 5.0f + y); glVertex3f(-10.0f, -10.0f, 0.0f);
	glEnd();
	glDisable(GL_BLEND);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_BLEND);
	glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2f(5.0f - x, 5.0f - y); glVertex3f(-10.0f, 10.0f, 0.0f);
	glTexCoord2f(5.0f - x, -5.0f - y); glVertex3f(10.0f, 10.0f, 0.0f);
	glTexCoord2f(0.0f - x, -5.0f - y); glVertex3f(10.0f, -10.0f, 0.0f);
	glTexCoord2f(0.0f - x, 5.0f - y); glVertex3f(-10.0f, -10.0f, 0.0f);
	glEnd();
	glDisable(GL_BLEND);
	glPopMatrix();

	x += 0.005;
	y += 0.005;
	SDL_GL_SwapWindow(window);
}
int main(int argc, char* argv[])
{
	quit = false;
	Init();
	LoadImage();
	while (!quit)
	{
		while (SDL_PollEvent(&sdlEvent))
		{
			if (sdlEvent.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		Draw();
		SDL_Delay(16);
	}
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
	return 0;
}
#pragma once
#include <vector>

#include <SDL.h>
#undef main
#include <glad/glad.h>

#include "ILayer.h"

namespace Douter {

	class Application
	{
	public:
		Application(int width = 1280, int height = 720): m_ScreenWidth(width), m_ScreenHeight(height)
		{
			if (SDL_Init(SDL_INIT_VIDEO) < 0) {
				fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
				return;
			}

			//Init OpenGL
			SDL_GL_LoadLibrary(NULL);
			// Request an OpenGL 4.5 context (should be core)
			SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
			// Also request a depth buffer
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

			m_Window = SDL_CreateWindow(
				"hello_sdl2",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				m_ScreenWidth, m_ScreenHeight, SDL_WINDOW_OPENGL
			);

			if (m_Window == NULL) {
				fprintf(stderr, "could not create window: %s\n", SDL_GetError());
				return;
			}

			m_GraphicsContext = SDL_GL_CreateContext(m_Window);
			if (m_GraphicsContext == NULL) {
				fprintf(stderr, "could not create window: %s\n", SDL_GetError());
				return;
			}

			//Check glad/opengl
			printf("OpenGL loaded\n");
			gladLoadGLLoader(SDL_GL_GetProcAddress);
			printf("Vendor:   %s\n", glGetString(GL_VENDOR));
			printf("Renderer: %s\n", glGetString(GL_RENDERER));
			printf("Version:  %s\n", glGetString(GL_VERSION));

			//Use v-sync
			SDL_GL_SetSwapInterval(1);

			//Disable depth and face culling
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_CULL_FACE);

			//Init glViewport
			int w, h;
			SDL_GetWindowSize(m_Window, &w, &h);
			glViewport(0, 0, w, h);
			glClearColor(0.0f, 0.5f, 1.0f, 0.0f);

			//Setup Layers
			m_Layers = std::vector<Douter::ILayer*>();
		}

		~Application()
		{
			m_Running = false;

			SDL_DestroyWindow(m_Window);
			SDL_Quit();
		}

		void Run()
		{
			Init();

			m_Running = true;

			//Delta Time
			Uint64 NOW = SDL_GetPerformanceCounter();
			Uint64 LAST = 0;
			double deltaTime = 0;

			SDL_Event event;
			while (m_Running)
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				//Delta Time
				LAST = NOW;
				NOW = SDL_GetPerformanceCounter();
				deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

				while (SDL_PollEvent(&event)) {
					if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
						m_Running = false;
					}
				}

				SDL_GL_SwapWindow(m_Window);
				
				//Update!
				for (ILayer* l : m_Layers)
				{
					l->Update(deltaTime);
				}

				//Draw!
				for (ILayer* l : m_Layers)
				{
					l->Draw();
				}
			}
		}

		void AttachLayer(ILayer* layer)
		{
			m_Layers.push_back(layer);
			layer->OnAttach();
		}

		void DettachLayer(ILayer* layer)
		{
			remove(m_Layers.begin(), m_Layers.end(), layer);
			layer->OnDettach();
		}

		virtual void Init() = 0;

	private:
		bool m_Running = false;
		int m_ScreenWidth, m_ScreenHeight;

		std::vector<Douter::ILayer*> m_Layers;

	private:
		SDL_Window* m_Window = NULL;
		SDL_GLContext m_GraphicsContext;
	};

}
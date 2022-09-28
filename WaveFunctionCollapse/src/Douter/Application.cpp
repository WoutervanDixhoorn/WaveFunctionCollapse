#include "Application.h"
#include "Rendering/Renderer.h"
#include <glad/glad.h>

#include "ImGuiLayer.h"

namespace Douter {

	void GLAPIENTRY
		MessageCallback(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam)
	{
		fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
			type, severity, message);
	}

	Application* Application::s_Instance = nullptr;

	Application::Application(int width, int height) : m_ScreenWidth(width), m_ScreenHeight(height)
	{
		s_Instance = this;

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

		m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

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

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);

		//Init glViewport
		int w, h;
		SDL_GetWindowSize(m_Window, &w, &h);
		glViewport(0, 0, w, h);

		//Setup Layers
		m_Layers = std::vector<Douter::ILayer*>();

		m_ImGuiLayer = new Douter::ImGuiLayer();
		AttachLayer(m_ImGuiLayer);
	};

	Application::~Application()
	{
		m_Running = false;

		SDL_DestroyWindow(m_Window);
		SDL_Quit();
	};

	void Application::Run()
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
			float* cc = clearColor;
			glClearColor(cc[0], cc[1], cc[2], cc[3]);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//Delta Time
			LAST = NOW;
			NOW = SDL_GetPerformanceCounter();
			deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

			while (SDL_PollEvent(&event)) {
				if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
					m_Running = false;
				}

				m_ImGuiLayer->HandleSDLEvent(event);
			}

			//Update!
			for (ILayer* layer : m_Layers)
			{
				layer->Update(deltaTime);
			}

			//Draw!
			Renderer2D::BeginBatch();
			for (ILayer* layer : m_Layers)
			{
				layer->Draw(m_Renderer);
			}
			Renderer2D::EndBatch();

			//Draw ImGui!
			ImGuiLayer::Begin();
			for (ILayer* layer : m_Layers)
			{
				layer->OnImGuiRender();
			}
			ImGuiLayer::End();

			SDL_GL_SwapWindow(m_Window);
		}
	}
}
#include "ImGuiLayer.h"
#include "Application.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

namespace Douter {

	void ImGuiLayer::OnAttach() 
	{
		IMGUI_CHECKVERSION();

		ImGui::CreateContext();

		Application& app = Application::Get();

		ImGui_ImplSDL2_InitForOpenGL(app.GetWindow(), app.GetContext());
		ImGui_ImplOpenGL3_Init("#version 450");
	}

	void ImGuiLayer::OnDettach() 
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::HandleSDLEvent(SDL_Event& e) 
	{
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	 
	void ImGuiLayer::Update(double deltaTime) 
	{

	}

	void ImGuiLayer::OnImGuiRender() 
	{
		ImGui::Begin("Change Background");

		ImGui::ColorEdit4("Color", Application::Get().clearColor);

		ImGui::End();
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(Application::Get().GetWindow());
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
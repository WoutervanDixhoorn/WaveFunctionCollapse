#pragma once


namespace Douter {

	class ILayer
	{
	public:
		
		virtual void OnAttach() {};
		virtual void OnDettach() {};

		virtual void Update(double deltaTime) = 0;
		virtual void Draw() {};
		virtual void OnImGuiRender() {};

	};

}
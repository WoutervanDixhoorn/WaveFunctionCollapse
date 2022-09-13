#pragma once

namespace Douter {

	class ILayer
	{
	public:
		
		virtual void OnAttach() const {};
		virtual void OnDettach() const {};

		virtual void Update(double deltaTime) const = 0;
		virtual void Draw() const = 0;

	};

}
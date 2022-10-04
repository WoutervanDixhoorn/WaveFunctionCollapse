#pragma once
#include "../Transform.h"

#include <glm.hpp>

namespace Douter
{

	class Camera
	{
	protected:
		Transform* m_Transform;
		glm::mat4 m_Projection;
		glm::mat4 m_View;
		glm::mat4 m_ViewProjection;

	public:
		Camera()
			: m_Transform(new Transform(0.0f, 0.0f, 0.0f)), m_Projection(1.0f), m_View(1.0), m_ViewProjection(1.0f)
		{
		}

		virtual void SetPosition(float x, float y, float z) = 0;
		virtual void Translate(float x, float y, float z) = 0;
		virtual void Rotate(float x, float y, float z) = 0;

		inline glm::mat4 GetViewProjection() const { return m_ViewProjection; }
		inline glm::mat4 GetViewProjection() { return m_ViewProjection; }

	protected:
		virtual void UpdateViewProjection() = 0;
	};

}
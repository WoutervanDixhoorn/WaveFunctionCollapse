#pragma once

#include <glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Douter
{

	class Transform
	{
	private:
		glm::mat4 m_Transform;

		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
	public:

		Transform(float x, float y, float z)
			: m_Transform(1.0f), m_Position(x, y, z), m_Rotation()
		{
		}

		Transform& SetPosition(float x, float y, float z)
		{
			m_Position = glm::vec3(x, y, z);
			return *this;
		}

		inline glm::vec3 GetPosition() const
		{
			return m_Position;
		}

		Transform& Translate(float x, float y, float z)
		{
			m_Position += glm::vec3(x, y, z);

			return *this;
		}

		glm::mat4& GetTransform()
		{
			glm::mat4 transform = glm::translate(glm::mat4(), m_Position);

			return transform;
		}

		glm::mat4& GetTransform() const
		{
			glm::mat4 transform = glm::translate(glm::mat4(), m_Position);

			return transform;
		}

		inline operator glm::mat4(){ return GetTransform(); }
		inline operator glm::mat4() const { return GetTransform(); }
	};

}
#pragma once

namespace Chromaria {

	class Shader
	{
	public:
		~Shader() {};

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
		static Shader* Create(const std::string& path);
	};

}
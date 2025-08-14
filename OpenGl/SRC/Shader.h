#pragma once
#include <string>


struct ShaderProgramSourse {
	std::string VertexSourse;
	std::string FragmentSource;
};

class Shader {

private:
	unsigned int m_RendererID;
	std::string m_FilePath;


	 int GetUniformLocation(const std::string& name);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	ShaderProgramSourse ParseShader(const std::string& filepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
public:
	Shader(const std::string& folepath);
	~Shader();

	void Bind()const;
	void UnBind()const;


	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

};


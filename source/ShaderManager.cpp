#include "ShaderManager.h"
#include "Shader.h"

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

#include <iostream>

static ShaderManager sm = ShaderManager();

ShaderManager::ShaderManager()
{
	std::cout << "Creating Shader Manager" << std::endl;
}

ShaderManager::~ShaderManager()
{
	std::cout << "Destroying Shader Manager" << std::endl;
	shaders.clear();
}

std::shared_ptr<Shader> ShaderManager::construct(const std::string& path)
{
	const auto iterator = shaders.find(path);
	if (iterator != shaders.end())
		return iterator->second;

	rapidjson::Document doc;
	char buffer[1000]{};
	FILE* fp;

	auto val = fopen_s(&fp, path.c_str(), "rb");
	if (val != 0)
		throw std::runtime_error("Error reading from: " + path);

	rapidjson::FileReadStream is(fp, buffer, sizeof(buffer));

	doc.ParseStream(is);
	assert(doc.IsObject());

	assert(doc.HasMember("vertex"));
	assert(doc["vertex"].IsString());

	auto vertex = "./shaders/" + std::string(doc["vertex"].GetString());

	assert(doc.HasMember("fragment"));
	assert(doc["fragment"].IsString());

	auto fragment = "./shaders/" + std::string(doc["fragment"].GetString());

	std::cout << "Creating Shader: " + path << std::endl;
	auto new_shader = std::make_shared<Shader>(vertex, fragment);
	shaders[path] = new_shader;

	return new_shader;
}

std::shared_ptr<Shader> construct_shader(const std::string& path)
{
	return sm.construct(path);
}

#include "MeshManager.h"
#include "Mesh.h"

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

#include <iostream>
#include <cstdio>

static MeshManager mm = MeshManager();

MeshManager::MeshManager()
{
	std::cout << "Creating Mesh Manager" << std::endl;

	// Reserve space for 10 meshes, can be changed later
	meshes.reserve(10 * sizeof(std::shared_ptr<Mesh>));
}

MeshManager::~MeshManager()
{
	std::cout << "Destroying Mesh Manager" << std::endl;
	meshes.clear();
}

std::shared_ptr<Mesh> MeshManager::construct(const std::string& name)
{
	for (auto& mesh : meshes)
	{
		if (mesh->name == name)
			return mesh;
	}
	
	// Read and create the new mesh
	rapidjson::Document doc;
	char buffer[1000]{};
	FILE* fp;

	// Open the file
	auto val = fopen_s(&fp, name.c_str(), "rb");

	// Check if it opened correctly
	if (val != 0)
		throw std::runtime_error("Error reading from: " + name);
	
	// Read it into the rapidjson FileReadStream
	rapidjson::FileReadStream is(fp, buffer, sizeof(buffer));

	// Parse the stream, make sure it is valid
	doc.ParseStream(is);
	assert(doc.IsObject());

	// Reading in vertices
	assert(doc.HasMember("vertices"));
	assert(doc["vertices"].IsArray());

	// Get the array
	auto line = doc["vertices"].GetArray();

	// Get the number of vertices, create buffer for them, get ready to read it
	rapidjson::SizeType num_vertices = line.Capacity();
	GLfloat* vertices = new GLfloat[num_vertices];
	rapidjson::Value::ConstValueIterator itr = line.Begin();

	// Iterate through and read the vertices
	for(rapidjson::SizeType i = 0; i < num_vertices; ++i)
		vertices[i] = (itr++)->GetFloat();

	// Read in indices
	assert(doc.HasMember("indices"));
	assert(doc["indices"].IsArray());
	line = doc["indices"].GetArray();

	// Read the number of indices, create buffer for them, get ready to read it
	rapidjson::SizeType num_indices = line.Capacity();
	GLuint* indices = new GLuint[num_indices];
	itr = line.begin();

	// Iterate through and read the indices
	for (rapidjson::SizeType i = 0; i < num_indices; ++i)
		indices[i] = (itr++)->GetUint();

	// Make the mesh with the proper parameters
	std::shared_ptr<Mesh> new_mesh = std::make_shared<Mesh>(vertices, num_vertices, indices, num_indices, name);
	meshes.push_back(new_mesh);

	// Delete the memory we allocated
	delete[] vertices;
	delete[] indices;

	return new_mesh;
}

std::shared_ptr<Mesh> construct_mesh(const std::string& name)
{
	return mm.construct(name);
}

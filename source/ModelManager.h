#pragma once

#include "Model.h"

#include <map>
#include <string>
#include <memory>

class ModelManager
{
public:
	ModelManager();
	~ModelManager();

	std::shared_ptr<Model> find(const std::string& path);
	void insert(const std::string& path, std::shared_ptr<Model> m);

private:
	std::map<std::string, std::shared_ptr<Model>> models;
};

std::shared_ptr<Model> construct_model(const std::string& path);

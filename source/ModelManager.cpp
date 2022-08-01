#include "ModelManager.h"
#include "Trace.h"
#include "Error.h"
#include "Model.h"

static ModelManager mm = ModelManager();

ModelManager::ModelManager()
{
	send_trace_message("Creating Model Manager");
}

ModelManager::~ModelManager()
{
	send_trace_message("Destroying Model Manager");
	models.clear();
}

std::shared_ptr<Model> ModelManager::find(const std::string& path)
{
	const auto& iterator = models.find(path);
	if (iterator != models.end())
		return iterator->second;
	else
		return nullptr;
}

void ModelManager::insert(const std::string& path, std::shared_ptr<Model> m)
{
	models[path] = m;
}

std::shared_ptr<Model> construct_model(const std::string& path)
{
	std::shared_ptr<Model> iterator = mm.find(path);
	if (iterator)
		return iterator;
	else
	{
		iterator = std::make_shared<Model>(path);
		mm.insert(path, iterator);
		return iterator;
	}
}

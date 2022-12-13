#pragma once

#include <functional>
#include <vector>
#include <map>

#include <entt/entt.hpp>

enum class SignalType
{
	None = 0,
	OnCreate = 1,
	OnDestroy = 2,
	BeginCollide = 3,
	ExitCollide = 4,
};

class Delegate
{
public:
	Delegate() {}
	~Delegate() {}

	Delegate& attach(std::function<void(entt::entity self, entt::registry& r, entt::entity other)> function)
	{
		__functions.push_back(function);
		return *this;
	}
	void invoke(entt::entity self, entt::registry& r, entt::entity other = entt::null)
	{
		for (auto& fn : __functions)
			fn(self, r, other);
	}

private:
	std::vector<std::function<void(entt::entity, entt::registry&, entt::entity)>> __functions;
};

class Delegator
{
public:
	Delegator() {}
	Delegator& add_delegate(SignalType signal, std::function<void(entt::entity self, entt::registry& r, entt::entity other)> function)
	{
		auto iterator = __delegates.find(signal);
		if (iterator != __delegates.end())
			iterator->second.attach(function);
		else
			__delegates.insert(std::pair<SignalType, Delegate>(signal, Delegate().attach(function)));

		return *this;
	}

	void invoke(SignalType signal, entt::entity self, entt::registry& r, entt::entity other = entt::null)
	{
		auto iterator = __delegates.find(signal);
		if (iterator != __delegates.end())
			iterator->second.invoke(self, r, other);
	}

private:
	std::unordered_map<SignalType, Delegate> __delegates;
};
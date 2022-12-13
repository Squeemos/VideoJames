#pragma once

enum class RenderType
{
	World = 0,
	Screen = 1
};

class RenderTag
{
public:
	RenderTag() = delete;
	RenderTag(RenderType type) : __render_type(type) {}

	const RenderType get_type() const { return __render_type; }

private:
	RenderType __render_type;
};

struct DeletedTag
{
};

struct Mouse
{
};
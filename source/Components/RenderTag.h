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
	RenderTag(RenderType type) : render_type(type) {}

	const RenderType get_type() const { return render_type; }

private:
	RenderType render_type;
};
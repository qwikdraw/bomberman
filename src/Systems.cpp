
#include "Systems.hpp"

//__________________________________________________________________________________________

struct	ModelLoader : entt::ResourceLoader<ModelLoader, Model>
{
	std::shared_ptr<Model>	load(const std::string modelPath) const
	{
		return std::shared_ptr<Model>(new Model(modelPath));
	}
};

void	Systems::RenderModels(entt::DefaultRegistry &registry, Camera &camera)
{
	auto entityGroup = registry.view<Part::Model, Part::Position>();

	for (auto entity : entityGroup)
	{
		auto &modelComp = entityGroup.get<Part::Model>(entity);
		auto &pos = entityGroup.get<Part::Position>(entity);
		const std::string modelPath = ASSET_PATH + modelComp.name + MODEL_PREFIX;

		entt::ResourceCache<Model> cache;

		cache.load<ModelLoader>(entt::HashedString(modelComp.name.c_str()), modelPath);
		const Model &model = cache.handle(entt::HashedString(modelComp.name.c_str()) ).get();

		const_cast<Model&>(model).Render(camera.Perspective(), modelComp.transform, pos.pos);
	}
}

//__________________________________________________________________________________________

void	Systems::Decay(entt::DefaultRegistry &registry, float dt)
{
	auto entityGroup = registry.view<Part::Decay>();

	for (auto entity : entityGroup)
	{
		auto &decay = entityGroup.get(entity);

		decay.seconds -= dt;
		if (decay.seconds <= 0)
			registry.destroy(entity);
	}
}

//__________________________________________________________________________________________

void	Systems::Clickable(entt::DefaultRegistry &registry, Window &window)
{
	auto entityGroup = registry.view<Part::Clickable>();

	for (auto entity : entityGroup)
	{
		auto &c = entityGroup.get(entity);

		if (window.MouseClick(0))
		{
			glm::vec2 pos = window.MousePos();

			if (pos.x >= c.botLeft.x && pos.x <= c.topRight.x &&
			    pos.y >= c.botLeft.y && pos.y <= c.topRight.y)
			{
				c.f();
			}
		}
	}
}

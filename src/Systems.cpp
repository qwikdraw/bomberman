
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

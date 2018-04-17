#include "Systems.hpp"

//_________________________________________________________________________________________

struct	ModelLoader : entt::ResourceLoader<ModelLoader, Model>
{
	std::shared_ptr<Model>	load(const std::string modelPath) const
	{
		return std::shared_ptr<Model>(new Model(modelPath));
	}
};

void	Systems::RenderModels(entt::DefaultRegistry &registry, entt::ResourceCache<Model>& cache, Camera &camera)
{
	auto entityGroup = registry.view<Part::Model, Part::Position>();

	for (auto entity : entityGroup)
	{
		auto &modelComp = entityGroup.get<Part::Model>(entity);
		auto &pos = entityGroup.get<Part::Position>(entity);
		const std::string modelPath = ASSET_PATH + modelComp.name + MODEL_PREFIX;

		cache.load<ModelLoader>(entt::HashedString(modelComp.name.c_str()), modelPath);
		const Model &model = cache.handle(entt::HashedString(modelComp.name.c_str()) ).get();

		const_cast<Model&>(model).Render(camera.Perspective(), modelComp.transform, pos.pos);
	}
}

//_________________________________________________________________________________________

void	Systems::Decay(entt::DefaultRegistry &registry, double dt)
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

//_________________________________________________________________________________________

void	Systems::Clickable(entt::DefaultRegistry &registry, Window &window, double dt)
{
	auto entityGroup = registry.view<Part::ScreenArea, Part::ClickCallback>();

	for (auto entity : entityGroup)
	{
		auto &screen = entityGroup.get<Part::ScreenArea>(entity);
		auto &callback = entityGroup.get<Part::ClickCallback>(entity);

		callback.cooldownTimer -= dt;
		if (window.MouseClick(0))
		{
			glm::vec2 pos = window.MousePos();

			if (pos.x >= screen.botLeft.x && pos.x <= screen.topRight.x &&
			    pos.y >= screen.botLeft.y && pos.y <= screen.topRight.y)
			{
				if (callback.cooldownTimer <= 0)
				{
					callback.f();
					callback.cooldownTimer = callback.cooldown;
				}
			}
		}
	}
}

//_________________________________________________________________________________________

struct	ImageLoader : entt::ResourceLoader<ImageLoader, ScreenImage>
{
	std::shared_ptr<ScreenImage>  load(const std::string imagePath) const
	{
		return std::shared_ptr<ScreenImage>(new ScreenImage(imagePath));
	}
};

void	Systems::RenderButtons(entt::DefaultRegistry &registry,
			       entt::ResourceCache<ScreenImage> &cache,
			       Window &window)
{
	auto entityGroup = registry.view<Part::ScreenArea,
					 Part::ClickCallback,
					 Part::Button>();

	for (auto entity : entityGroup)
	{
		auto &screen = entityGroup.get<Part::ScreenArea>(entity);
		auto &callback = entityGroup.get<Part::ClickCallback>(entity);
		auto &button = entityGroup.get<Part::Button>(entity);

		std::string imagePath;

		if (callback.cooldownTimer <= 0)
			imagePath = button.imageBefore;
		else
			imagePath = button.imageAfter;

		window.SetRenderMask((screen.botLeft.x + 1) / 2,
				     (screen.botLeft.y + 1) / 2,
				     (screen.topRight.x - screen.botLeft.x) / 2,
				     (screen.topRight.y - screen.botLeft.y) / 2);

		cache.load<ImageLoader>(entt::HashedString(imagePath.c_str()), imagePath);
		const ScreenImage &im = cache.handle(entt::HashedString(imagePath.c_str())).get();

		const_cast<ScreenImage&>(im).Render();
		
		window.RemoveRenderMask();
	}
}

//_________________________________________________________________________________________

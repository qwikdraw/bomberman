#include "Systems.hpp"

//_________________________________________________________________________________________

struct	ModelLoader : entt::ResourceLoader<ModelLoader, Model>
{
	std::shared_ptr<Model>	load(const std::string modelPath) const
	{
		return std::shared_ptr<Model>(new Model(modelPath));
	}
};

void	Systems::RenderModels(entt::DefaultRegistry &registry, entt::ResourceCache<Model>& cache,
			      Window &window, Camera &camera)
{
	auto entityGroup = registry.view<Part::Model, Part::Position>();

	for (auto entity : entityGroup)
	{
		auto &modelComp = entityGroup.get<Part::Model>(entity);
		auto &pos = entityGroup.get<Part::Position>(entity);
		const std::string modelPath = ASSET_PATH + modelComp.name + MODEL_PREFIX;

		cache.load<ModelLoader>(entt::HashedString(modelComp.name.c_str()), modelPath);
		const Model &model = cache.handle(entt::HashedString(modelComp.name.c_str()) ).get();

		window.SetRenderMask((modelComp.botLeft.x + 1) / 2,
				     (modelComp.botLeft.y + 1) / 2,
				     (modelComp.topRight.x - modelComp.botLeft.x) / 2,
				     (modelComp.topRight.y - modelComp.botLeft.y) / 2);
		
		const_cast<Model&>(model).Render(camera.Perspective(), modelComp.transform, pos.pos);

		window.RemoveRenderMask();
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

struct	ImageLoader : entt::ResourceLoader<ImageLoader, ScreenImage>
{
	std::shared_ptr<ScreenImage>  load(const std::string imagePath) const
	{
		return std::shared_ptr<ScreenImage>(new ScreenImage(imagePath));
	}
};

void	Systems::Buttons(entt::DefaultRegistry &registry,
			 entt::ResourceCache<ScreenImage> &cache,
			 Window &window, double dt)
{
	auto entityGroup = registry.view<Part::Button>();

	for (auto entity : entityGroup)
	{
		auto &button = entityGroup.get(entity);


		//render logic:
		std::string imagePath;

		if (button.cooldownTimer <= 0)
			imagePath = button.imageBefore;
		else
			imagePath = button.imageAfter;

		window.SetRenderMask((button.botLeft.x + 1) / 2,
				     (button.botLeft.y + 1) / 2,
				     (button.topRight.x - button.botLeft.x) / 2,
				     (button.topRight.y - button.botLeft.y) / 2);

		cache.load<ImageLoader>(entt::HashedString(imagePath.c_str()), imagePath);
		const ScreenImage &im = cache.handle(entt::HashedString(imagePath.c_str())).get();
		const_cast<ScreenImage&>(im).Render();

		window.RemoveRenderMask();

		//button logic:
		button.cooldownTimer -= dt;
		if (window.MouseClick(0))
		{
			glm::vec2 pos = window.MousePos();

			if (pos.x >= button.botLeft.x && pos.x <= button.topRight.x &&
			    pos.y >= button.botLeft.y && pos.y <= button.topRight.y)
			{
				if (button.cooldownTimer <= 0)
				{
					button.f();
					button.cooldownTimer = button.cooldown;
				}
			}
		}
	}
}

//_________________________________________________________________________________________

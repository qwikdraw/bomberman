#include "systems.hpp"

namespace c = components;

//! RenderModels

struct	ModelLoader : entt::ResourceLoader<ModelLoader, Model>
{
	std::shared_ptr<Model>	load(const std::string modelPath) const
	{
		return std::shared_ptr<Model>(new Model(modelPath));
	}
};

void	systems::RenderModels(entt::DefaultRegistry &registry, entt::ResourceCache<Model>& cache,
		Window &window, Camera &camera)
{
	auto view = registry.view<c::Model, c::Position>();

	for (auto entity : view)
	{
		auto &modelComp = view.get<c::Model>(entity);
		auto &pos = view.get<c::Position>(entity);
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


//! Decay

void	systems::Decay(entt::DefaultRegistry &registry, double dt)
{
	auto view = registry.view<c::Decay>();

	for (auto entity : view)
	{
		auto &decay = view.get(entity);

		decay.seconds -= dt;
		if (decay.seconds <= 0)
			registry.destroy(entity);
	}
}


//! Buttons

struct	ImageLoader : entt::ResourceLoader<ImageLoader, Sprite2D>
{
	std::shared_ptr<Sprite2D>  load(const std::string imagePath) const
	{
		return std::shared_ptr<Sprite2D>(new Sprite2D(imagePath));
	}
};

void	systems::Buttons(entt::DefaultRegistry &registry,
		entt::ResourceCache<Sprite2D> &cache, Window &window, double dt)
{
	auto view = registry.view<c::Button>();

	for (auto entity : view)
	{
		auto &button = view.get(entity);

		// render logic
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
		const Sprite2D &im = cache.handle(entt::HashedString(imagePath.c_str())).get();
		const_cast<Sprite2D&>(im).Render();

		window.RemoveRenderMask();

		// button logic
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

//! player

void	createBomb(entt::DefaultRegistry &r, glm::vec3 pos)
{
	auto bomb = r.create();
	r.assign<c::Model>(bomb, "bomb", glm::mat4(1));
	r.assign<c::Position>(bomb, glm::round(pos));
	r.assign<c::Collide>(bomb);
	r.assign<c::Decay>(bomb, 3.0f);
}

void	systems::Player(entt::DefaultRegistry &registry, Window &window, Engine::KeyBind bind,
			Camera& cam, double dt)
{
	auto view = registry.view<c::Player, c::Position, c::Velocity, c::Model>();

	for (auto entity : view)
	{
		auto &player = view.get<c::Player>(entity);
		auto &move = view.get<c::Velocity>(entity);
		glm::vec3 &pos = view.get<c::Position>(entity).pos;
		glm::mat4 &transform = view.get<c::Model>(entity).transform;

		glm::vec3 v(0, 0, 0);
		
		if (window.Key(bind.up))
		{
			transform = FACE_UP;
			v.y += player.speed * dt;
		}
		if (window.Key(bind.down))
		{
			transform = FACE_DOWN;
			v.y -= player.speed * dt;
		}
		if (window.Key(bind.left))
		{
			transform = FACE_LEFT;
			v.x -= player.speed * dt;
		}
		if (window.Key(bind.right))
		{
			transform = FACE_RIGHT;
			v.x += player.speed * dt;
		}
		if (window.Key(bind.bomb))
		{
			if (player.bombCooldownTimer <= 0)
			{
				createBomb(registry, pos);
				player.bombCooldownTimer = player.bombCooldown;
			}
		}
		player.bombCooldownTimer -= dt;
		cam.Move(v * 0.5);
		move.v = v;
	}
}

//! Velocity

void    checkCollisions(glm::vec3 &pos, glm::vec3 &v, systems::Collisions &cells, double dt)
{
        if (v.y > 0 && !cells.isEmpty(pos.x, pos.y + 1))
        {
                if (pos.y > roundf(pos.y))
                        v.y = 0;
        }
        if (v.y < 0 && !cells.isEmpty(pos.x, pos.y - 1))
        {
                if (pos.y < roundf(pos.y))
                        v.y = 0;
        }
        if (v.x > 0 && !cells.isEmpty(pos.x + 1, pos.y))
        {
                if (pos.x > roundf(pos.x))
                        v.x = 0;
        }
        if (v.x < 0 && !cells.isEmpty(pos.x - 1, pos.y))
        {
                if (pos.x < roundf(pos.x))
                        v.x = 0;
        }

        //re-align

        if (v.x)
        {
                v.y = (roundf(pos.y) - pos.y) * dt * 10;
        }
        else if (v.y)
        {
                v.x = (roundf(pos.x) - pos.x) * dt * 10;
        }
}

void	systems::Velocity(entt::DefaultRegistry& registry, systems::Collisions &cells, double dt)
{
	auto coll = registry.view<c::Velocity, c::Position, c::Collide>();

	for (auto entity : coll)
	{
		glm::vec3 &pos = coll.get<c::Position>(entity).pos;
		glm::vec3 &v = coll.get<c::Velocity>(entity).v;

		checkCollisions(pos, v, cells, dt);
	}
	
	auto view = registry.view<c::Velocity, c::Position>();

	for (auto entity : view)
	{
		glm::vec3 &moveAmount = view.get<c::Velocity>(entity).v;
		glm::vec3 &pos = view.get<c::Position>(entity).pos;
		pos += moveAmount;
	}
}

//! Collisions

systems::Collisions::Collisions(void) {}

bool	systems::Collisions::isEmpty(float x, float y) const
{
	uint32_t xi, yi;
	xi = round(x);
	yi = round(y);
	return _cells.count((uint64_t)xi << 32 | yi) != 1;
}

uint32_t	systems::Collisions::get(float x, float y)
{
	uint32_t xi, yi;
	xi = round(x);
	yi = round(y);
	return _cells[(uint64_t)xi << 32 | yi];
}

void	systems::Collisions::operator()(entt::DefaultRegistry& registry)
{
	_cells.clear();
	auto view = registry.view<c::Collide, c::Position>();

	uint32_t x, y;
	for (auto entity : view)
	{
		auto& pos = view.get<c::Position>(entity).pos;
		x = round(pos.x);
		y = round(pos.y);
		_cells[(uint64_t)x << 32 | y] = entity;
	}
}

//! Render particles

void	systems::RenderParticles(entt::DefaultRegistry &registry, Camera &cam, double dt)
{
	auto view = registry.view<c::Particles, c::Position>();

	for (auto entity : view)
	{
		glm::vec3 &pos = view.get<c::Position>(entity).pos;
		IParticle *particles = view.get<c::Particles>(entity).particle;

		particles->Render(cam.Perspective(), pos, dt);
	}
}

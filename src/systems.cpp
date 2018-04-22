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

	std::vector<Light*> lights;
	
	auto lightGroup = registry.view<c::Position, c::Lighting>();

	for (auto entity : lightGroup)
	{
		glm::vec3 &pos = lightGroup.get<c::Position>(entity).pos;
		auto &light = lightGroup.get<c::Lighting>(entity);

		lights.push_back(new Light(pos + light.displacement, light.color, light.falloff));
	}
	
	auto view = registry.view<c::Model, c::Position>();

	camera.SetAspect(window.GetAspect());
	
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
	for (auto l : lights)
	{
		delete l;
	}
}

//! TimedEffect

void	systems::TimedEffect(entt::DefaultRegistry &registry, double dt)
{
	auto view = registry.view<c::TimedEffect>();

	for (auto entity : view)
	{
		auto &te = view.get(entity);

		te.timeLeft -= dt;
		if (te.timeLeft <= 0)
		{
			switch (te.effectType)
			{
				case c::effect::VANISH:
					if (registry.valid(entity))
						registry.destroy(entity);
					break;
				case c::effect::EXPLOAD:
					registry.assign<c::Explosion>(entity, 4);
					te.timeLeft = 0.2f;
					te.effectType = c::effect::VANISH;
					break;
			}
		}
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
	r.assign<c::TimedEffect>(bomb, 3.0f, c::effect::EXPLOAD);
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
		auto target = glm::vec3(pos.x, pos.y - 10, 20);
		cam.Move((target - cam.GetPosition()) * dt);
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

#include <typeinfo>

void	systems::RenderParticles(entt::DefaultRegistry &registry, Camera &cam)
{
	auto view = registry.view<c::Particles, c::Position, c::TimedEffect>();
	
	for (auto entity : view)
	{
		glm::vec3 &pos = view.get<c::Position>(entity).pos;
		IParticle *particles = view.get<c::Particles>(entity).particle;
		float duration = view.get<c::Particles>(entity).duration;
		float time = view.get<c::TimedEffect>(entity).timeLeft;

		particles->Render(cam.Perspective(), pos, duration - time);
	}
}

//! Explosion

static void	spread_explosion(entt::DefaultRegistry &r, systems::Collisions& cells,
				 int spread, int x, int y, c::Direction d,
				 ParticleExplosion *explosionEffect)
{
	if (!cells.isEmpty(x, y))
	{
		auto e = cells.get(x, y);
		if (!r.valid(e))
			return;
		auto& collided = r.get<c::Collide>(e);
		if (collided.height > spread)
			return;
		spread -= collided.height;
		if (r.valid(e))
			r.destroy(e);
	}

	auto ex = r.create();
	r.assign<c::Explosion>(ex, spread, d);
	r.assign<c::Particles>(ex, explosionEffect, 1.0f);
        r.assign<c::Position>(ex, glm::vec3(x, y, 0));
//	r.assign<c::Lighting>(ex, glm::vec3(1, 0.6, 0), 1.0f, glm::vec3(0, 0, 2));
	r.assign<c::TimedEffect>(ex, 1.0f);
	r.assign<c::Collide>(ex);
}

void	systems::Explosion(entt::DefaultRegistry &registry, systems::Collisions& cells,
			   ParticleExplosion *expl)
{
	auto view = registry.view<c::Explosion, c::Position>();

	for (auto entity : view)
	{
		auto& ex = view.get<c::Explosion>(entity);
		glm::vec3 &pos = view.get<c::Position>(entity).pos;
		if (ex.spread < 1)
		{
			registry.remove<c::Explosion>(entity);
			continue;
		}
		ex.spread -= 1;
		if (ex.dir == c::Direction::NONE || ex.dir == c::Direction::RIGHT)
			spread_explosion(registry, cells, ex.spread, pos.x + 1, pos.y, c::Direction::RIGHT, expl);
		if (ex.dir == c::Direction::NONE || ex.dir == c::Direction::LEFT)
			spread_explosion(registry, cells, ex.spread, pos.x - 1, pos.y, c::Direction::LEFT, expl);
		if (ex.dir == c::Direction::NONE || ex.dir == c::Direction::UP)
			spread_explosion(registry, cells, ex.spread, pos.x, pos.y + 1, c::Direction::UP, expl);
		if (ex.dir == c::Direction::NONE || ex.dir == c::Direction::DOWN)
			spread_explosion(registry, cells, ex.spread, pos.x, pos.y - 1, c::Direction::DOWN, expl);
	}
}

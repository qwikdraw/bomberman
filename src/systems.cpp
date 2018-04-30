#include "systems.hpp"

namespace c = components;

namespace systems
{

//! RenderModels

struct	ModelLoader : entt::ResourceLoader<ModelLoader, Model>
{
	std::shared_ptr<Model>	load(const std::string modelPath) const
	{
		return std::shared_ptr<Model>(new Model(modelPath));
	}
};

void	RenderModels(entt::DefaultRegistry &registry, entt::ResourceCache<Model>& cache,
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

void	TimedEffect(entt::DefaultRegistry &registry, double dt)
{
	auto view = registry.view<c::TimedEffect>();

	for (auto entity : view)
	{
		auto &te = view.get(entity);

		te.timeLeft -= dt;
		if (te.timeLeft <= 0)
			te.effect(registry, entity);
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

void	Buttons(entt::DefaultRegistry &registry,
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

void	Player(entt::DefaultRegistry& r, Window& window, Engine::KeyBind bind,
			Cells& cells, Camera& cam, double dt)
{
	if (!r.has<c::Player>())
		return;
	auto entity = r.attachee<c::Player>();
	if (!r.has<c::Position, c::Velocity, c::Model>(entity))
		return;
	auto &player = r.get<c::Player>();
	auto &move = r.get<c::Velocity>(entity);
	glm::vec3 &pos = r.get<c::Position>(entity).pos;
	glm::mat4 &transform = r.get<c::Model>(entity).transform;

	cells.Powerup(pos.x, pos.y)(r, entity);

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
			callbacks::bomb(player.bombPower)(r, entity);
			player.bombCooldownTimer = player.bombCooldown;
		}
	}
	player.bombCooldownTimer -= dt;
	auto target = glm::vec3(pos.x, pos.y - 10, 20);
	cam.Move((target - cam.GetPosition()) * dt);
	move.v = v;
}

//! Lighting

void	Lighting(entt::DefaultRegistry& r, double dt)
{
	auto view = r.view<c::Lighting>();

	for (auto e : view)
	{
		auto& light = view.get(e);
		light.falloff += light.falloffDelta * dt;
	}
}

//! Velocity

static void    checkCollisions(glm::vec3 &pos, glm::vec3 &v, Cells &cells, double dt, int height)
{
	if (v.y > 0 && height <= cells.Collision(pos.x, pos.y + 1))
	{
		if (pos.y > roundf(pos.y))
			v.y = 0;
	}
	if (v.y < 0 && height <= cells.Collision(pos.x, pos.y - 1))
	{
		if (pos.y < roundf(pos.y))
			v.y = 0;
	}
	if (v.x > 0 && height <= cells.Collision(pos.x + 1, pos.y))
	{
		if (pos.x > roundf(pos.x))
			v.x = 0;
	}
	if (v.x < 0 && height <= cells.Collision(pos.x - 1, pos.y))
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

void	Velocity(entt::DefaultRegistry& registry, Cells &cells, double dt)
{
	auto coll = registry.view<c::Velocity, c::Position, c::Collide>();

	for (auto entity : coll)
	{
		glm::vec3 &pos = coll.get<c::Position>(entity).pos;
		glm::vec3 &v = coll.get<c::Velocity>(entity).v;
		int height = coll.get<c::Collide>(entity).height;

		checkCollisions(pos, v, cells, dt, height);
	}
	
	auto view = registry.view<c::Velocity, c::Position>();

	for (auto entity : view)
	{
		glm::vec3 &moveAmount = view.get<c::Velocity>(entity).v;
		glm::vec3 &pos = view.get<c::Position>(entity).pos;
		pos += moveAmount;
	}
}

//! Render particles

void	RenderParticles(entt::DefaultRegistry &registry, Camera &cam)
{
	auto view = registry.view<c::Particles, c::Position, c::TimedEffect>();
	
	for (auto entity : view)
	{
		glm::vec3 pos = view.get<c::Position>(entity).pos;
		IParticle *particles = view.get<c::Particles>(entity).particle;
		float duration = view.get<c::Particles>(entity).duration;
		float time = view.get<c::TimedEffect>(entity).timeLeft;

		particles->Render(cam.Perspective(), pos, duration - time);
	}
}

//! Explosion

static void	add_fire(entt::DefaultRegistry &r, int x, int y)
{
	auto fire = r.create();

	r.assign<c::Position>(fire, glm::vec3(x, y, 0));
	r.assign<c::Lighting>(fire, glm::vec3(0.5, 0.2, 0), 2.0f, glm::vec3(0, 0, 2), -1.0f);
	r.assign<c::Dangerous>(fire, 100);
	r.assign<c::Particles>(fire, Effects::explosion, 2.0f);
	r.assign<c::TimedEffect>(fire, 2.0f, callbacks::destroy());
}

static void	add_invisible_fire(entt::DefaultRegistry &r, int x, int y)
{
	auto fire = r.create();

	r.assign<c::Position>(fire, glm::vec3(x, y, 0));
	r.assign<c::Lighting>(fire, glm::vec3(0.5, 0.2, 0), 2.0f, glm::vec3(0, 0, 2), 1.2f);
	r.assign<c::Dangerous>(fire, 100);
	r.assign<c::TimedEffect>(fire, 0.1f, callbacks::destroy());
}

void	Explosion(entt::DefaultRegistry &registry, Cells& cells)
{
	constexpr int explosionHeight = 10;
	
	auto view = registry.view<c::Explosion, c::Position>();

	for (auto entity : view)
	{
		int spread = view.get<c::Explosion>(entity).spread;
		glm::vec3 pos = view.get<c::Position>(entity).pos;
		
		registry.destroy(entity);

		add_fire(registry, pos.x, pos.y);
		for (int up = 1; up <= spread; up++)
		{
			if (explosionHeight <= cells.Collision(pos.x, pos.y + up))
			{
				add_invisible_fire(registry, pos.x, pos.y + up);
				break;
			}
			add_fire(registry, pos.x, pos.y + up);
		}
		for (int down = 1; down <= spread; down++)
		{
			if (explosionHeight <= cells.Collision(pos.x, pos.y - down))
			{
				add_invisible_fire(registry, pos.x, pos.y - down);
				break;
			}
			add_fire(registry,pos.x, pos.y - down);
		}
		for (int left = 1; left <= spread; left++)
		{
			if (explosionHeight <= cells.Collision(pos.x - left, pos.y))
			{
				add_invisible_fire(registry, pos.x - left, pos.y);
				break;
			}
			add_fire(registry, pos.x - left, pos.y);
		}
		for (int right = 1; right <= spread; right++)
		{
			if (explosionHeight <= cells.Collision(pos.x + right, pos.y))
			{
				add_invisible_fire(registry, pos.x + right, pos.y);
				break;
			}
			add_fire(registry, pos.x + right, pos.y);
		}
	}
}

// AI monster
void	AI(entt::DefaultRegistry &registry, Window &window, double dt)
{
	auto view = registry.view<c::AI, c::Position, c::Velocity, c::Model>();

	for (auto entity : view)
	{
		auto &ai = view.get<c::AI>(entity);
		auto &move = view.get<c::Velocity>(entity);
		glm::mat4 &transform = view.get<c::Model>(entity).transform;

		glm::vec3 v(0, 0, 0);
		if (ai.moveCooldown <= 0.0)
		{
			ai.dir = static_cast<c::Direction>(std::rand() % 5);
			if (ai.dir == c::Direction::UP)
				transform = FACE_UP;
			if (ai.dir == c::Direction::RIGHT)
				transform = FACE_RIGHT;
			if (ai.dir == c::Direction::DOWN)
				transform = FACE_DOWN;
			if (ai.dir == c::Direction::LEFT)
				transform = FACE_LEFT;
			if (ai.dir != c::Direction::NONE)
				ai.moveCooldown = 1.0;
		}
		else
		{
			if (ai.dir == c::Direction::UP)
				v.y += ai.speed * dt;
			if (ai.dir == c::Direction::RIGHT)
				v.x += ai.speed * dt;
			if (ai.dir == c::Direction::DOWN)
				v.y -= ai.speed * dt;
			if (ai.dir == c::Direction::LEFT)
				v.x -= ai.speed * dt;
		}
		ai.moveCooldown -= dt;
		move.v = v;
	}
}

// Dangerous and vunerable entity resolution

void	DangerCheck(entt::DefaultRegistry &registry, Cells& cells)
{
	auto view = registry.view<c::Vulnerable, c::Position>();

	for (auto entity : view)
	{
		int dangerResist = view.get<c::Vulnerable>(entity).dangerResist;
		auto& onDeath = view.get<c::Vulnerable>(entity).onDeath;
		const glm::vec3& pos = view.get<c::Position>(entity).pos;

		if (dangerResist < cells.Danger(pos.x, pos.y))
		{
			onDeath(registry, entity);
		}
	}
}

}

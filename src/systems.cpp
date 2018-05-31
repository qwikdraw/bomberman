#include "systems.hpp"

namespace c = components;

namespace systems
{

//! RenderModels

void	RenderModels(entt::DefaultRegistry &registry, entt::ResourceCache<Model>& cache,
		     Window &window, Camera &camera, double dt)
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
		const std::string modelPath = ASSET_PATH + modelComp.name + ".model";

		cache.load<ModelLoader>(entt::HashedString(modelComp.name.c_str()), modelPath);
		const Model &model = cache.handle(entt::HashedString(modelComp.name.c_str()) ).get();

		window.SetRenderMask(
			(modelComp.botLeft.x + 1) / 2,
			(modelComp.botLeft.y + 1) / 2,
			(modelComp.topRight.x - modelComp.botLeft.x) / 2,
			(modelComp.topRight.y - modelComp.botLeft.y) / 2
		);

		const_cast<Model&>(model).Render(
			camera.Perspective(),
			modelComp.transform,
			pos.pos,
			modelComp.time
		);

		window.RemoveRenderMask();
		modelComp.time += dt;
	}
	for (auto l : lights)
	{
		delete l;
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

//! Images

struct	ImageLoader : entt::ResourceLoader<ImageLoader, Sprite2D>
{
	std::shared_ptr<Sprite2D>  load(const std::string imagePath) const
	{
		return std::shared_ptr<Sprite2D>(new Sprite2D(imagePath));
	}
};

void	Images(entt::DefaultRegistry& r, entt::ResourceCache<Sprite2D>& cache, Window& window)
{
	auto view = r.view<c::Image>();

	for (auto entity : view)
	{
		auto &image = view.get(entity);

		window.SetRenderMask((image.botLeft.x + 1) / 2,
				     (image.botLeft.y + 1) / 2,
				     (image.topRight.x - image.botLeft.x) / 2,
				     (image.topRight.y - image.botLeft.y) / 2);
		
		cache.load<ImageLoader>(entt::HashedString(image.name.c_str()), image.name);
		const Sprite2D &im = cache.handle(entt::HashedString(image.name.c_str())).get();
		const_cast<Sprite2D&>(im).Render();

		window.RemoveRenderMask();
	}
}

//! Texts

void	Texts(entt::DefaultRegistry& r, Window& window)
{
	auto view = r.view<c::Text>();

	for (auto entity : view)
	{
		auto& text = view.get(entity);

		Text t(text.words);

		window.SetRenderMask((text.botLeft.x + 1) / 2,
			(text.botLeft.y + 1) / 2,
			(text.topRight.x - text.botLeft.x) / 2,
			(text.topRight.y- text.botLeft.y) / 2);

		t.Render(window.GetAspect());

		window.RemoveRenderMask();
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

void	Buttons(entt::DefaultRegistry &r, Window& window)
{
	auto view = r.view<c::Button>();

	for (auto entity : view)
	{
		auto& button = view.get(entity);

		if (window.MouseClick(0))
		{
			glm::vec2 pos = window.MousePos();

			if (pos.x >= button.botLeft.x && pos.x <= button.topRight.x &&
			    pos.y >= button.botLeft.y && pos.y <= button.topRight.y)
			{
				button.onClick(r, entity);
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

	glm::vec3 v(0, 0, 0);
		
	if (window.Key(bind.up))
	{
		transform = FACE_UP;
		v.y += player.speed;
	}
	if (window.Key(bind.down))
	{
		transform = FACE_DOWN;
		v.y -= player.speed;
	}
	if (window.Key(bind.left))
	{
		transform = FACE_LEFT;
		v.x -= player.speed;
	}
	if (window.Key(bind.right))
	{
		transform = FACE_RIGHT;
		v.x += player.speed;
	}
	if (window.Key(bind.bomb))
	{
		if (player.bombCooldownTimer <= 0)
		{
			scripts::bomb(player.bombPower)(r, entity);
			player.bombCooldownTimer = player.bombCooldown;
		}
	}
	player.bombCooldownTimer -= dt;
	auto target = glm::vec3(pos.x, pos.y - 10, 20);
	cam.Move((target - cam.GetPosition()) * dt);
	move.v = v;
	cells.Powerup(r, pos.x, pos.y)(r, entity);
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

static void    checkCollisions(entt::DefaultRegistry& r,
	glm::vec3 &pos, glm::vec3 &v, Cells &cells, double dt, int height)
{
	if (v.y > 0 && height < cells.Collision(r, pos.x, pos.y + 1))
	{
		if (pos.y > roundf(pos.y))
			v.y = 0;
	}
	else if (v.y < 0 && height < cells.Collision(r, pos.x, pos.y - 1))
	{
		if (pos.y < roundf(pos.y))
			v.y = 0;
	}
	if (v.x > 0 && height < cells.Collision(r, pos.x + 1, pos.y))
	{
		if (pos.x > roundf(pos.x))
			v.x = 0;
	}
	else if (v.x < 0 && height < cells.Collision(r, pos.x - 1, pos.y))
	{
		if (pos.x < roundf(pos.x))
			v.x = 0;
	}

	// Re-align

	if (v.x)
		v.y = (roundf(pos.y) - pos.y) * 10;
	else if (v.y)
		v.x = (roundf(pos.x) - pos.x) * 10;
}

void	Velocity(entt::DefaultRegistry& r, Cells &cells, double dt)
{
	auto coll = r.view<c::Velocity, c::Position, c::Collide>();

	for (auto entity : coll)
	{
		glm::vec3 &pos = coll.get<c::Position>(entity).pos;
		glm::vec3 &v = coll.get<c::Velocity>(entity).v;
		int height = coll.get<c::Collide>(entity).height;

		checkCollisions(r, pos, v, cells, dt, height);
	}

	auto view = r.view<c::Velocity, c::Position>();

	for (auto entity : view)
	{
		glm::vec3 &moveAmount = view.get<c::Velocity>(entity).v;
		glm::vec3 &pos = view.get<c::Position>(entity).pos;
		pos += moveAmount * dt;
	}
}

//! Explosion

static void	spawn_explosion(entt::DefaultRegistry &r, Cells& cells, int spread, int x, int y, c::Direction dir)
{
	if (cells.Collision(r, x, y) && !cells.Vulnerable(r, x, y))
		return;
	auto ex = r.create();
	r.assign<c::Position>(ex, glm::vec3(x, y, 0));
	r.assign<c::Lighting>(ex, glm::vec3(0.5, 0.2, 0), 1.0f, glm::vec3(0, 0, 2), -1.0f);
	r.assign<c::Dangerous>(ex, 100);
	r.assign<c::Particles>(ex, Effects::explosion, 1.0f);
	r.assign<c::Explosion>(ex, spread, dir);
	r.assign<c::TimedEffect>(ex, 0.8f, scripts::destroy());
}


void	Explosion(entt::DefaultRegistry &r, Cells& cells)
{
	r.view<c::Explosion, c::Position>().each([&r, &cells](auto entity, auto ex, auto p){
		auto pos = glm::round(p.pos);
		if (ex.spread < 1)
			return r.remove<c::Explosion>(entity);
		ex.spread -= 1;
		switch (ex.dir)
		{
			case (c::Direction::NONE):
				spawn_explosion(r, cells, 0, pos.x, pos.y, c::Direction::NONE);
				spawn_explosion(r, cells, ex.spread, pos.x, pos.y + 1, c::Direction::UP);
				spawn_explosion(r, cells, ex.spread, pos.x, pos.y - 1, c::Direction::DOWN);
				spawn_explosion(r, cells, ex.spread, pos.x - 1, pos.y, c::Direction::LEFT);
				spawn_explosion(r, cells, ex.spread, pos.x + 1, pos.y, c::Direction::RIGHT);
				break;
			case (c::Direction::UP):
				spawn_explosion(r, cells, ex.spread, pos.x, pos.y + 1, c::Direction::UP);
				break;
			case (c::Direction::DOWN):
				spawn_explosion(r, cells, ex.spread, pos.x, pos.y - 1, c::Direction::DOWN);
				break;
			case (c::Direction::LEFT):
				spawn_explosion(r, cells, ex.spread, pos.x - 1, pos.y, c::Direction::LEFT);
				break;
			case (c::Direction::RIGHT):
				spawn_explosion(r, cells, ex.spread, pos.x + 1, pos.y, c::Direction::RIGHT);
				break;
		}
		r.remove<c::Explosion>(entity);
	});
}

// AI monster
void	AI(entt::DefaultRegistry &registry, Window &window, double dt)
{
	auto view = registry.view<c::AI, c::Velocity, c::Model>();

	for (auto entity : view)
	{
		auto &ai = view.get<c::AI>(entity);
		auto &move = view.get<c::Velocity>(entity);
		glm::mat4 &transform = view.get<c::Model>(entity).transform;

		glm::vec3 v(0, 0, 0);
		if (ai.moveCooldownTimer <= 0.0)
		{
			if (ai.type == c::AI_type::RAND)
				ai.dir = static_cast<c::Direction>(std::rand() % 5);
			else if (ai.type == c::AI_type::HORZ)
				ai.dir = static_cast<c::Direction>(std::rand() % 2 ? 2 : 4);
			else if (ai.type == c::AI_type::VERT)
				ai.dir = static_cast<c::Direction>(std::rand() % 2 ? 1 : 3);
			if (ai.dir == c::Direction::UP)
				transform = FACE_UP;
			else if (ai.dir == c::Direction::RIGHT)
				transform = FACE_RIGHT;
			else if (ai.dir == c::Direction::DOWN)
				transform = FACE_DOWN;
			else if (ai.dir == c::Direction::LEFT)
				transform = FACE_LEFT;
			if (ai.dir != c::Direction::NONE)
				ai.moveCooldownTimer = ai.moveCooldown;
		}
		//else
		//{
			if (ai.dir == c::Direction::UP)
				v.y = ai.speed;
			else if (ai.dir == c::Direction::RIGHT)
				v.x = ai.speed;
			else if (ai.dir == c::Direction::DOWN)
				v.y = -ai.speed;
			else if (ai.dir == c::Direction::LEFT)
				v.x = -ai.speed;
		//}
		ai.moveCooldownTimer -= dt;
		move.v = v;
	}
}

// Dangerous and vunerable entity resolution

void	Danger(entt::DefaultRegistry &r, Cells& cells)
{
	auto view = r.view<c::Vulnerable, c::Position>();

	for (auto entity : view)
	{
		int dangerResist = view.get<c::Vulnerable>(entity).dangerResist;
		auto& onDeath = view.get<c::Vulnerable>(entity).onDeath;
		const glm::vec3& pos = view.get<c::Position>(entity).pos;

		if (dangerResist < cells.Danger(r, pos.x, pos.y))
			onDeath(r, entity);
	}
}

// BindCheck used for the settings menu

static int	get_new_bind(Window& window)
{
	int out = -1;
	for (int i = 0; i < 512; i++)
		if (window.Key(i))
			out = i;

	if (std::isalnum(out) ||
	    out == GLFW_KEY_RIGHT ||
	    out == GLFW_KEY_LEFT ||
	    out == GLFW_KEY_UP ||
	    out == GLFW_KEY_DOWN ||
	    out == ' ')
	{
		return out;
	}
	return -1;
}

static int      keyFromAction(c::ActionType action, Engine& engine)
{
        switch (action)
        {
        case (c::BOMB_ACTION):
                return engine.keyBind.bomb;
        case (c::UP_ACTION):
                return engine.keyBind.up;
        case (c::LEFT_ACTION):
                return engine.keyBind.left;
        case (c::RIGHT_ACTION):
                return engine.keyBind.right;
        case (c::DOWN_ACTION):
                return engine.keyBind.down;
        }
        return 0;
}

static std::string      keyToString(int key)
{
        std::string out;

	if (key == ' ')
		out += "space";
	else if (key == GLFW_KEY_RIGHT)
		out += "right arrow";
	else if (key == GLFW_KEY_LEFT)
		out += "left arrow";
	else if (key == GLFW_KEY_UP)
		out += "up arrow";
	else if (key == GLFW_KEY_DOWN)
		out += "down arrow";
	else
		out += (char)key;
	
        return out;
}

void	BindCheck(entt::DefaultRegistry& r, Window& window, Engine& engine)
{
	auto view = r.view<c::KeyBind, c::Text>();

	if (window.MouseClick(0))
	{
		for (auto entity : view)
		{
			auto action = view.get<c::KeyBind>(entity).action;
			std::string& words = view.get<c::Text>(entity).words;
			
			words = keyToString(keyFromAction(action, engine));
			r.remove<c::KeyBind>(entity);
		}
		return;
	}

	int key	= get_new_bind(window);
	if (key == -1)
		return;

	for (auto entity : view)
	{
		auto action = view.get<c::KeyBind>(entity).action;
		std::string& words = view.get<c::Text>(entity).words;
		switch (action)
		{
		case (c::BOMB_ACTION):
			engine.keyBind.bomb = key;
			words = keyToString(key);
			break;
		case (c::UP_ACTION):
			engine.keyBind.up = key;
			words = keyToString(key);
			break;
		case (c::DOWN_ACTION):
			engine.keyBind.down = key;
			words = keyToString(key);
			break;
		case (c::LEFT_ACTION):
			engine.keyBind.left = key;
			words = keyToString(key);
			break;
		case (c::RIGHT_ACTION):
			engine.keyBind.right = key;
			words = keyToString(key);
			break;
		}
		r.remove<c::KeyBind>(entity);
	}
}
	
}

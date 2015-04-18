//=================================
// included dependencies
#include "Application.h"
#include "ModuleEnemy.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
//=================================
// the actual code

ModuleEnemy::ModuleEnemy(Application *app, bool start_enabled) : Module(app, start_enabled)
{ }

ModuleEnemy::~ModuleEnemy()
{ }

// Load assets
bool ModuleEnemy::start()
{
	LOG("Loading enemies...");

	// Pata-pata
	pata_pata.graphics = app->textures->load("Sprites/Pata_pata.png");
	pata_pata.anim.frames.pushBack({ 0, 0, 32, 36 });
	pata_pata.anim.frames.pushBack({ 32, 0, 32, 36 });
	pata_pata.anim.frames.pushBack({ 64, 0, 32, 36 });
	pata_pata.anim.frames.pushBack({ 96, 0, 32, 36 });
	pata_pata.anim.frames.pushBack({ 128, 0, 32, 36 });
	pata_pata.anim.frames.pushBack({ 160, 0, 32, 36 });
	pata_pata.anim.frames.pushBack({ 192, 0, 32, 36 });
	pata_pata.anim.frames.pushBack({ 224, 0, 32, 36 });
	pata_pata.anim.speed = 0.3f;

	return true;
}

bool ModuleEnemy::cleanUp()
{
	LOG("Unloading particles");
	app->textures->unload(pata_pata.graphics);
	return true;
}

// Update: draw enemies
update_status ModuleEnemy::update()
{
	doubleNode<Enemy*>* tmp = active.getFirst();
	doubleNode<Enemy*>* tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		Enemy *e = tmp->data;
		tmp_next = tmp->next;

		if (e->update() == false)
		{
			delete e;
			active.del(tmp);
		}
		else if (SDL_GetTicks() >= e->born)
		{
			app->renderer->blit(e->graphics, e->position.x, e->position.y, &(e->anim.getCurrentFrame()));
			if (e->fx_played == false)
			{
				e->fx_played = true;
				app->audio->playFx(e->fx);
			}
		}

		tmp = tmp_next;
	}

	return UPDATE_CONTINUE;
}

void ModuleEnemy::onCollision(Collider *col1, Collider *c2)
{ }

void ModuleEnemy::addEnemy(const Enemy &enemy, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	Enemy *e = new Enemy(enemy);
	e->born = SDL_GetTicks() + delay;
	e->position.x = x;
	e->position.y = y;

	if (collider_type != COLLIDER_NONE)
	{
		e->collider = app->collision->addCollider({ e->position.x, e->position.y, 0, 0 }, collider_type, this);
	}

	active.add(e);
}

// Enemy struct methods

Enemy::Enemy() : fx(0), born(0), life(0), fx_played(false)
{
	position.setZero();
	speed.setZero();
}

Enemy::Enemy(const Enemy &e) : graphics(e.graphics), anim(e.anim), position(e.position), speed(e.speed), fx_played(false)
{
	fx = e.fx;
	born = e.born;
	life = e.life;
}

Enemy::~Enemy()
{
	if (collider)
		collider->to_delete = true;
}

bool Enemy::update()
{
	bool ret = true;

	if (life > 0)
	{
		if((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if (collider != NULL)
	{
		SDL_Rect r = anim.peekCurrentFrame();
		collider->rect = { position.x, position.y, r.w, r.h };
	}

	return ret;
}
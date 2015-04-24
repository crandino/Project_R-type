//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "Application.h"
#include "ModuleCollision.h"
//=================================
// the actual code

ModuleParticles::ModuleParticles(Application *app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{ 
	//Player ship shot
	//shot.fx = app->audio->loadFx("LOQUESEA");
	shot.anim.frames.pushBack({ 215, 85, 14, 12 });
	shot.anim.frames.pushBack({ 233, 85, 11, 12 });
	shot.anim.frames.pushBack({ 249, 85, 15, 12 });
	shot.anim.loop = false;
	shot.anim.speed = 0.5f;
	shot.speed.x = 10;
	shot.speed.y = 0;
	shot.life = 1500;

	//Pata-pata shot
	pata_shot.anim.frames.pushBack({ 1, 1, 7, 6 });
	pata_shot.anim.frames.pushBack({ 10, 1, 7, 6 });
	pata_shot.anim.frames.pushBack({ 19, 1, 7, 6 });
	pata_shot.anim.frames.pushBack({ 27, 1, 7, 6 });
	pata_shot.anim.speed = 0.5f;
	pata_shot.speed.x = -2;
	pata_shot.life = 4000;

	//Common explosion
	explosion.anim.frames.pushBack({ 0, 0, 34, 32});
	explosion.anim.frames.pushBack({ 34, 0, 34, 32 });
	explosion.anim.frames.pushBack({ 68, 0, 34, 32 });
	explosion.anim.frames.pushBack({ 102, 0, 34, 32 });
	explosion.anim.frames.pushBack({ 136, 0, 34, 32 });
	explosion.anim.frames.pushBack({ 170, 0, 34, 32 });
	explosion.anim.speed = 0.4f;
	explosion.anim.loop = false;

}

ModuleParticles::~ModuleParticles()
{ }

// Load assets
bool ModuleParticles::start()
{
	LOG("Loading particles");

	// Shot particle
	shot.graphics = app->textures->load("Sprites/Arrowhead.png");
	// Pata-pata shot
	pata_shot.graphics = app->textures->load("Sprites/Basic_shot_pata_pata.png");
	// Pata-pata explosion
	explosion.graphics = app->textures->load("Sprites/Common_explosion.png");

	return true;
}

bool ModuleParticles::cleanUp()
{
	LOG("Unloading particles");
	app->textures->unload(shot.graphics);
	app->textures->unload(pata_shot.graphics);
	app->textures->unload(explosion.graphics);

	doubleNode<Particle*> *item = active.getLast();

	while (item != NULL)
	{
		delete item->data;
		item = item->previous;
	}

	active.clear();
	return true;
}

// Update: draw background
update_status ModuleParticles::update()
{
	doubleNode<Particle*>* tmp = active.getFirst();
	doubleNode<Particle*>* tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		Particle *p = tmp->data;
		tmp_next = tmp->next;

		if (p->update() == false)
		{
			delete p;
			active.del(tmp);
		}
		else if (SDL_GetTicks() >= p->born)
		{
			app->renderer->blit(p->graphics, p->position.x, p->position.y, &(p->anim.getCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
				app->audio->playFx(p->fx);
			}
		}

		tmp = tmp_next;
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::onCollision(Collider *c1, Collider *c2)
{
	// Explosion for laser hitting wall or something
	//app->particles->addParticle(explosion, c1->rect.x, c1->rect.y);

	doubleNode<Particle*> *tmp = active.getFirst();

	while (tmp != NULL)
	{
		if (tmp->data->collider == c1)
		{
			delete tmp->data;
			active.del(tmp);
			break;
		}

		tmp = tmp->next;
	}
}

void ModuleParticles::addParticle(const Particle &particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	Particle *p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;

	if (collider_type != COLLIDER_NONE)
	{
		p->collider = app->collision->addCollider({ p->position.x, p->position.y, 0, 0 }, collider_type, this);
	}

	active.add(p);
}

// -------------------------------------------------------
// -------------------------------------------------------

Particle::Particle() : fx(0), born(0), life(0), fx_played(false), collider(NULL)
{
	position.setZero();
	speed.setZero();
}

Particle::Particle(const Particle &p) : graphics(p.graphics), anim(p.anim), position(p.position), speed(p.speed), fx_played(false)
{
	collider = p.collider;
	fx = p.fx;
	born = p.born;
	life = p.life;
}

Particle::~Particle()
{
	if (collider != NULL)
		collider->to_delete = true;
}

bool Particle::update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
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
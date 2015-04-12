//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "Application.h"
//=================================
// the actual code

ModuleParticles::ModuleParticles(Application *app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{ }

ModuleParticles::~ModuleParticles()
{ }

// Load assets
bool ModuleParticles::start()
{
	LOG("Loading particles");
	graphics = app->textures->load("Sprites/Arrowhead.png");

	// Shot particle
	//shot.fx = app->audio->loadFx("LOQUESEA");
	shot.anim.frames.pushBack({ 215, 85, 14, 12 });
	shot.anim.frames.pushBack({ 233, 85, 11, 12 });
	shot.anim.frames.pushBack({ 249, 85, 15, 12 });
	shot.anim.loop = false;
	shot.anim.speed = 0.3f;
	// CRZ attempts
	shot.speed.x = 5;
	shot.speed.y = 0;
	shot.life = 1500;

	return true;
}

bool ModuleParticles::cleanUp()
{
	LOG("Unloading particles");
	app->textures->unload(graphics);
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
			active.del(tmp);
			delete p;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			app->renderer->blit(graphics, p->position.x, p->position.y, &(p->anim.getCurrentFrame()));
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

void ModuleParticles::addParticle(const Particle &particle, int x, int y, Uint32 delay)
{
	Particle *p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;

	active.add(p);
}

// -------------------------------------------------------
// -------------------------------------------------------

Particle::Particle() : fx(0), born(0), life(0), fx_played(false)
{
	position.setZero();
	speed.setZero();
}

Particle::Particle(const Particle &p) : anim(p.anim), position(p.position), speed(p.speed), fx_played(false)
{
	fx = p.fx;
	born = p.born;
	life = p.life;
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

	return ret;
}
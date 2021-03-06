//=================================
// included dependencies
#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
//=================================
// the actual code

ModuleCollision::ModuleCollision(Application *app, bool start_enabled) : Module(app, start_enabled)
{
	debug = false;
	god_mode = false;

	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_WALL][COLLIDER_RIBBON_SHOT] = false;

	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_POWER_UP] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_RIBBON_SHOT] = false;

	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_RIBBON_SHOT] = true;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_RIBBON_SHOT] = false;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_RIBBON_SHOT] = false;

	matrix[COLLIDER_POWER_UP][COLLIDER_WALL] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_POWER_UP][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_RIBBON_SHOT] = false;

	matrix[COLLIDER_RIBBON_SHOT][COLLIDER_WALL] = false;
	matrix[COLLIDER_RIBBON_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_RIBBON_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_RIBBON_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_RIBBON_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_RIBBON_SHOT][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_RIBBON_SHOT][COLLIDER_RIBBON_SHOT] = false;
}

// Destructor
ModuleCollision::~ModuleCollision()
{ }

bool ModuleCollision::start()
{
	god = app->textures->load("Images/God.png");
	return true;
}

update_status ModuleCollision::preUpdate()
{
	// Remove all colliders scheduled for deletion
	doubleNode<Collider*> *tmp = colliders.getFirst();
	doubleNode<Collider*> *tmp2;

	while (tmp != NULL)
	{
		tmp2 = tmp->next;
		if (tmp->data->to_delete == true)
		{
			delete tmp->data;
			colliders.del(tmp);
		}
		tmp = tmp2;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleCollision::update()
{
	// Debug ---
	if (app->input->getKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	doubleNode<Collider*> *tmp = colliders.getFirst();

	Collider *c1;
	Collider *c2;

	while (tmp != NULL)
	{
		c1 = tmp->data;

		// Debug ---
		if (debug)
			drawDebug(c1);

		doubleNode<Collider*> *tmp2 = tmp->next; // avoid checking collisions already checked
		while (tmp2 != NULL)
		{
			c2 = tmp2->data;

			if (c1->checkCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->onCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->onCollision(c2, c1);
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}

	// God_Mode --- The player lose all its collisions.
	if (app->input->getKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		if (god_mode == true)
		{
			matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
			matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
			matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
			matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT] = false;
			matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;
			matrix[COLLIDER_PLAYER][COLLIDER_POWER_UP] = true;
			matrix[COLLIDER_PLAYER][COLLIDER_RIBBON_SHOT] = false;
		}
		else
		{
			matrix[COLLIDER_PLAYER][COLLIDER_WALL] = false;
			matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
			matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = false;
			matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT] = false;
			matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = false;
			matrix[COLLIDER_PLAYER][COLLIDER_POWER_UP] = false;
			matrix[COLLIDER_PLAYER][COLLIDER_RIBBON_SHOT] = false;
		}
		god_mode = !god_mode;
	}

	if (god_mode)
		app->renderer->blit(god, app->player->position.x - 10 * SCALE_FACTOR, app->player->position.y - 55 * SCALE_FACTOR, NULL);

	return UPDATE_CONTINUE;
}

void ModuleCollision::drawDebug(Collider *col)
{
	Uint8 alpha = 80;
	switch (col->type)
	{
		case COLLIDER_NONE:
			app->renderer->drawQuad(col->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_WALL:
			app->renderer->drawQuad(col->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_PLAYER:
			app->renderer->drawQuad(col->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_ENEMY:
			app->renderer->drawQuad(col->rect, 255, 100, 0, alpha);
			break;
		case COLLIDER_PLAYER_SHOT:
			app->renderer->drawQuad(col->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_ENEMY_SHOT:
			app->renderer->drawQuad(col->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_POWER_UP:
			app->renderer->drawQuad(col->rect, 255, 0, 255, alpha);
			break;
		case COLLIDER_RIBBON_SHOT:
			app->renderer->drawQuad(col->rect, 255, 255, 0, alpha);
			break;
	}
}

// Called before quitting
bool ModuleCollision::cleanUp()
{
	app->textures->unload(god);

	LOG("Freeing all colliders");
	doubleNode<Collider*> *item = colliders.getLast();
	
	while (item != NULL)
	{
		delete item->data;
		item = item->previous;
	}

	colliders.clear();
	return true;
}

Collider *ModuleCollision::addCollider(SDL_Rect rect, COLLIDER_TYPE type, bool positions_scaled, Module *callback)
{

	if (positions_scaled == false)
	{
		rect.x *= SCALE_FACTOR;
		rect.y *= SCALE_FACTOR;
	}

	rect.w *= SCALE_FACTOR;
	rect.h *= SCALE_FACTOR;

	Collider *ret = new Collider(rect, type, callback);
	colliders.add(ret);
	return ret;
}

// --------------------

bool Collider::checkCollision(SDL_Rect r) const
{
	//return SDL_HasIntersection(&rect, &r);
	
	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.h + rect.y > r.y);
}

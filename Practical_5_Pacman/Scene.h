#pragma once
#include <vector>
#include <memory>
#include <ecm.h>
#include <LevelSystem.h>

class Scene {
public:
	Scene() = default;

	virtual ~Scene() = default;
	virtual void update(double dt);
	virtual void render();
	virtual void respawn();
	virtual void load() = 0;
};
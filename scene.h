#pragma once

#include <graphics.h>
#include "camera.h"

// 页面的抽象基类

class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	// 进入页面
	virtual void on_enter() = 0;
	// 更新页面
	virtual void on_update(int delta) = 0;
	// 渲染页面
	virtual void on_render(const Camera& camera) = 0;
	// 处理输入
	virtual void on_input(const ExMessage& msg) = 0;
	// 退出页面
	virtual void on_exit() = 0;

private:

};
#pragma once
#include <memory>


template<typename T>
using Ref = std::shared_ptr<T>;

class Component {
	public:
		Component(Component* parent_):parent(parent_), isCreated(false) {}
		virtual ~Component() = default;
		virtual bool onCreate() = 0;
		virtual void onDestroy() = 0;
		virtual void update(const float deltaTime_) = 0;
		virtual void draw()const = 0;
	protected:
		Component* parent;
		bool isCreated;

};
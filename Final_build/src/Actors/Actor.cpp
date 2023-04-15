#include "../../include/Actors/Actor.h"

using std::cout;

Actor::Actor(Component* parent_) :Component(parent_) {}

bool Actor::onCreate() {
	if (isCreated) return true;
	for (auto component : components) {
		if (component->onCreate() == false) {
			isCreated = false;
			return isCreated;
		}
	}
	isCreated = true;
	return isCreated;
}

Actor::~Actor() {
	//cout << "Actor Desytroyed\n";
	onDestroy();
}

void Actor::onDestroy() {
	RemoveAllComponents();
	isCreated = false;
}



void Actor::update(const float deltaTime) {
	std::cout << "Hello from Update\n";
}

void Actor::draw()const {}

void Actor::RemoveAllComponents() {
	components.clear();
}

void Actor::ListComponents() const {
	std::cout << typeid(*this).name() << " contains the following components:\n";
	for (Ref<Component> component : components) {
		std::cout << typeid(*component).name() << std::endl;
	}
	std::cout << '\n';
}
/*
Matrix4 Actor::GetModelMatrix() {
	Ref<TransformComponent> transform = GetComponent<TransformComponent>();
	if (transform.get()) {
		modelMatrix = transform->GetTransformMatrix();
	}
	else {
		modelMatrix.loadIdentity();
	}
	if (parent) {
		modelMatrix = dynamic_cast<Actor*>(parent)->GetModelMatrix() * modelMatrix;
	}
	return modelMatrix;
}
	*/

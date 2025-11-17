# API Reference

## Application
- `orchard::Application` drives the main loop and exposes references to the renderer, ECS world, physics, and audio subsystems.

## ECS
- `orchard::World::createEntity()` returns a unique entity id.
- `World::addComponent<T>()` constructs and attaches a component in archetype storage.
- `World::view<Components...>()` returns entities matching the requested components.

## Physics
- `PhysicsWorld::createRigidBody` spawns rigid bodies.
- `PhysicsWorld::step` advances simulation using a decoupled fixed timestep.

## Audio
- `AudioSystem::loadBank` loads `.orchardpkg` sound banks.
- `AudioSystem::play` starts a voice routed through the spatial mixer.

## Rendering
- `Renderer::render(World&)` executes the Metal render graph and presents to MTKView.

## Editor
- `SceneStore` observable orchestrates hierarchy, inspector, and build pipeline data.

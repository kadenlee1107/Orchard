# Orchard Engine Architecture

Orchard Engine is a modular C++17/Swift runtime targeting Apple silicon platforms. The engine is split into systems:

- **Core**: Application lifecycle, platform abstraction, logging, clock.
- **ECS**: Archetype-inspired storage and hot-reload friendly component containers.
- **Rendering**: A Metal 3 renderer with clustered lighting, MetalFX integration, and ray-tracing hooks.
- **Physics**: Custom SAP broadphase + GJK/EPA narrowphase solver with decoupled timestep.
- **Audio**: CoreAudio graph with spatial mixing and convolution reverb.
- **Scripting**: SwiftUI gameplay layer bridged through ScriptHost.
- **Editor**: SwiftUI front-end embedding the runtime via MTKView.

Each module communicates through lightweight interfaces so that macOS, iOS, iPadOS, tvOS, and visionOS builds reuse the same engine core while swapping platform-specific shells.

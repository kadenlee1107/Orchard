# Orchard Engine

Orchard Engine is a macOS-native Metal game engine written in C++17 and Swift. It targets Apple silicon platforms with ProMotion, HDR, MetalFX, ray tracing, and SwiftUI tooling support.

## Layout
- `OrchardEngine/Engine` – Runtime systems (core, ECS, rendering, physics, audio, scripting).
- `OrchardEngine/Editor` – SwiftUI editor with inspector, hierarchy, and MTKView viewport.
- `OrchardEngine/Samples` – Demo scenes for first-person, third-person, and physics showcases.
- `OrchardEngine/Tools` – Command line utilities for shader compilation and asset packaging.
- `OrchardEngine/Documentation` – Architecture, API, scripting, and rendering manuals.

## Building
Use Xcode 15+ on macOS 14 with Apple silicon. Generate projects via the provided tools or integrate into an existing workspace.

# Scripting Guide

Swift gameplay logic conforms to `OrchardScriptLifecycle`. Register scripts in `OrchardBridge.shared` and the runtime will call `onStart` and `onUpdate` during editor play sessions or runtime builds.

C++ systems may call back into Swift using `ScriptHost::callSwift` with serialized payloads (JSON/MessagePack). During development, scripts hot-reload with LLDB/Swift Playgrounds and reflect state through the ECS event bus.

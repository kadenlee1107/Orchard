import Foundation
import simd

final class FirstPersonController: OrchardScriptLifecycle {
    private var world: UnsafeMutableRawPointer?
    private var velocity = SIMD3<Float>(repeating: 0)

    func onStart(worldHandle: UnsafeMutableRawPointer) {
        world = worldHandle
    }

    func onUpdate(deltaTime: Float) {
        velocity = SIMD3<Float>(0, 0, -1) * deltaTime
    }
}

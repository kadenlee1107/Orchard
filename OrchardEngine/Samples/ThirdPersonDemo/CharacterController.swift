import Foundation
import simd

final class ThirdPersonController: OrchardScriptLifecycle {
    private var yaw: Float = 0

    func onStart(worldHandle: UnsafeMutableRawPointer) {}

    func onUpdate(deltaTime: Float) {
        yaw += deltaTime
    }
}

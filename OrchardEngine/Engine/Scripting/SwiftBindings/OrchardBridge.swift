import Foundation
import MetalKit

@objc public protocol OrchardScriptLifecycle {
    func onStart(worldHandle: UnsafeMutableRawPointer)
    func onUpdate(deltaTime: Float)
}

public final class OrchardBridge {
    public static let shared = OrchardBridge()
    private var scripts: [OrchardScriptLifecycle] = []

    private init() {}

    public func register(script: OrchardScriptLifecycle) {
        scripts.append(script)
    }

    public func update(deltaTime: Float) {
        scripts.forEach { $0.onUpdate(deltaTime: deltaTime) }
    }
}

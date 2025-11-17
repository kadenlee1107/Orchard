import Foundation
import simd

final class SceneStore: ObservableObject {
    @Published var nodes: [SceneNode] = []
    @Published var selection: UUID?

    init() {
        newScene()
    }

    func newScene() {
        nodes = [SceneNode(name: "Camera", transform: .identity)]
        selection = nodes.first?.id
    }
}

struct SceneNode: Identifiable {
    let id = UUID()
    var name: String
    var transform: TransformData
}

struct TransformData {
    var position: SIMD3<Float>
    var rotation: SIMD3<Float>
    var scale: SIMD3<Float>

    static let identity = TransformData(position: .zero, rotation: .zero, scale: SIMD3<Float>(repeating: 1))
}

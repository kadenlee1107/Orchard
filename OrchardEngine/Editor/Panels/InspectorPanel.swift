import SwiftUI

struct InspectorPanel: View {
    @EnvironmentObject var store: SceneStore

    var selectedNode: SceneNode? {
        store.nodes.first { $0.id == store.selection }
    }

    var body: some View {
        Form {
            if var node = selectedNode {
                Section(header: Text(node.name)) {
                    VectorField(label: "Position", value: node.transform.position)
                    VectorField(label: "Rotation", value: node.transform.rotation)
                    VectorField(label: "Scale", value: node.transform.scale)
                }
            } else {
                Text("Select an object")
            }
        }
        .padding()
        .navigationTitle("Inspector")
    }
}

struct VectorField: View {
    let label: String
    var value: SIMD3<Float>

    var body: some View {
        VStack(alignment: .leading) {
            Text(label).font(.caption)
            HStack {
                Text("x: \(value.x, specifier: "%.2f")")
                Text("y: \(value.y, specifier: "%.2f")")
                Text("z: \(value.z, specifier: "%.2f")")
            }
        }
    }
}

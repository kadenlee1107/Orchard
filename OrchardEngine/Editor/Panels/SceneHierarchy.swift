import SwiftUI

struct SceneHierarchy: View {
    @EnvironmentObject var store: SceneStore

    var body: some View {
        List(selection: $store.selection) {
            ForEach(store.nodes) { node in
                Text(node.name)
            }
        }
        .listStyle(.sidebar)
        .navigationTitle("Hierarchy")
    }
}

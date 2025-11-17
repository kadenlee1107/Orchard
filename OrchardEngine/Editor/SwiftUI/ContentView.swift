import SwiftUI
import MetalKit

struct ContentView: View {
    @EnvironmentObject var store: SceneStore
    @State private var timeline: [String] = []

    var body: some View {
        NavigationSplitView {
            SceneHierarchy()
        } content: {
            SceneViewport()
        } detail: {
            InspectorPanel()
        }
        .toolbar {
            ToolbarItemGroup(placement: .automatic) {
                Button("Play") {}
                Button("Pause") {}
                Button("Build") {}
            }
        }
    }
}

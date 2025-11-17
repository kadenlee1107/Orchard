import SwiftUI
import MetalKit

@main
struct OrchardEditorApp: App {
    @StateObject private var store = SceneStore()

    var body: some Scene {
        WindowGroup("Orchard Editor") {
            ContentView()
                .environmentObject(store)
        }
        .windowStyle(.titleBar)
        .commands {
            CommandGroup(replacing: .newItem) {
                Button("New Scene") { store.newScene() }
            }
        }
    }
}

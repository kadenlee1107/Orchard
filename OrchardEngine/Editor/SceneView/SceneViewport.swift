import SwiftUI
import MetalKit

struct SceneViewport: NSViewRepresentable {
    func makeNSView(context: Context) -> MTKView {
        let view = MTKView()
        view.device = MTLCreateSystemDefaultDevice()
        view.colorPixelFormat = .bgra8Unorm
        view.preferredFramesPerSecond = 120
        return view
    }

    func updateNSView(_ nsView: MTKView, context: Context) {
        // Hand off to engine runtime for live preview.
    }
}

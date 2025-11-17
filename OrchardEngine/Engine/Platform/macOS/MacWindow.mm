#import "MacWindow.hpp"

using namespace orchard;

MacWindow::MacWindow() {
    NSRect frame = NSMakeRect(0, 0, 1920, 1080);
    m_window = [[NSWindow alloc] initWithContentRect:frame
                                           styleMask:(NSWindowStyleMaskTitled |
                                                      NSWindowStyleMaskResizable |
                                                      NSWindowStyleMaskClosable)
                                             backing:NSBackingStoreBuffered
                                               defer:NO];
    m_view = [[MTKView alloc] initWithFrame:frame device:MTLCreateSystemDefaultDevice()];
    [m_window setContentView:m_view];
    [m_window makeKeyAndOrderFront:nil];
}

MacWindow::~MacWindow() {
    [m_view release];
    [m_window release];
}

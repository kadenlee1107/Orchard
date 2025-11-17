#pragma once

#import <AppKit/AppKit.h>
#import <MetalKit/MetalKit.h>

namespace orchard {

class MacWindow : public NSObject<NSApplicationDelegate> {
public:
    MacWindow();
    ~MacWindow();

    MTKView* view() const { return m_view; }

private:
    NSWindow* m_window;
    MTKView* m_view;
};

}

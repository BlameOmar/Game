/**************************************************************************************************
 * Title:         GameView.mm
 * Author:        Omar Stefan Evans
 * Created on:    2013-07-13
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#import "GameView.h"

#import <Carbon/Carbon.h>

using namespace evansbros;


@interface GameView ()

- (CVReturn)getFrameForTime:(const CVTimeStamp*)outputTime;

static CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, const CVTimeStamp* outputTime, CVOptionFlags flagsIn, CVOptionFlags* flagsOut, void* displayLinkContext);

@end

@implementation GameView

- (id)initWithFrame:(NSRect)frameRect pixelFormat:(NSOpenGLPixelFormat *)format
{
    self = [super initWithFrame:frameRect pixelFormat:format];
    if (self) {
        [self.openGLContext makeCurrentContext];
        _renderer = new graphics::CGLRenderer();
        _messageQueue = new game::MessageQueue(100);
        _gameSystem = new game::GameSystem(_renderer, _messageQueue);
        initializedGameSystem = NO;
    }
    return self;
}

- (void)prepareOpenGL
{
//#ifdef DEBUG
//    /* Disable V-Sync */
//    GLint swapInterval = 0;
//    [self.openGLContext setValues:&swapInterval forParameter:NSOpenGLCPSwapInterval];
//#endif

    // Create a display link capable of being used with all active displays
    CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);

    // Set the renderer output callback function
    CVDisplayLinkSetOutputCallback(displayLink, &MyDisplayLinkCallback, (__bridge void *)self);

    // Set the display link for the current renderer
    CGLContextObj cglContext = (CGLContextObj)[[self openGLContext] CGLContextObj];
    CGLPixelFormatObj cglPixelFormat = (CGLPixelFormatObj)[[self pixelFormat] CGLPixelFormatObj];
    CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext, cglPixelFormat);

    // Activate the display link
    CVDisplayLinkStart(displayLink);
}

static CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, const CVTimeStamp* outputTime, CVOptionFlags flagsIn, CVOptionFlags* flagsOut, void* displayLinkContext)
{
    CVReturn result = [(__bridge GameView*)displayLinkContext getFrameForTime:outputTime];
    return result;
}

- (CVReturn)getFrameForTime:(const CVTimeStamp*)outputTime
{
    if (!initializedGameSystem) {
        self.gameSystem->initialize();
        initializedGameSystem = YES;
    }

    self.gameSystem->doCycle();

    return kCVReturnSuccess;
}

- (void)reshape
{
    CGLContextObj contextObj = (CGLContextObj)[self.openGLContext CGLContextObj];
    CGLLockContext(contextObj);
    self.renderer->resizeViewport(self.bounds.size.width, self.bounds.size.height);
    CGLUnlockContext(contextObj);
}

- (void)update
{
    CGLContextObj contextObj = (CGLContextObj)[self.openGLContext CGLContextObj];
    CGLLockContext(contextObj);

    [super update];

    CGLUnlockContext(contextObj);
}

- (BOOL)acceptsFirstResponder
{
    return YES;
}

- (void)keyUp:(NSEvent *)theEvent
{
    if (theEvent.isARepeat) {
        return;
    }

    using namespace evansbros::game;
    switch (theEvent.keyCode) {
        /* Player 1*/
        case kVK_Escape:
            self.messageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P1_PAUSE));
            break;
        case kVK_ANSI_W:
        case kVK_UpArrow:
            self.messageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P1_UP));
            break;
        case kVK_ANSI_A:
        case kVK_LeftArrow:
            self.messageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P1_LEFT));
            break;
        case kVK_ANSI_S:
        case kVK_DownArrow:
            self.messageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P1_DOWN));
            break;
        case kVK_ANSI_D:
        case kVK_RightArrow:
            self.messageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P1_RIGHT));
            break;

        /* Player 2*/
        case kVK_ANSI_P:
            self.messageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P2_PAUSE));
            break;
        case kVK_ANSI_I:
            self.messageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P2_UP));
            break;
        case kVK_ANSI_J:
            self.messageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P2_LEFT));
            break;
        case kVK_ANSI_K:
            self.messageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P2_DOWN));
            break;
        case kVK_ANSI_L:
            self.messageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P2_RIGHT));
            break;
    }
}

- (void)keyDown:(NSEvent *)theEvent
{
    if (theEvent.isARepeat) {
        return;
    }

    using namespace evansbros::game;
    switch (theEvent.keyCode) {
        /* Player 1 */
        case kVK_Escape:
            self.messageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P1_PAUSE));
            break;
        case kVK_ANSI_W:
        case kVK_UpArrow:
            self.messageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P1_UP));
            break;
        case kVK_ANSI_A:
        case kVK_LeftArrow:
            self.messageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P1_LEFT));
            break;
        case kVK_ANSI_S:
        case kVK_DownArrow:
            self.messageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P1_DOWN));
            break;
        case kVK_ANSI_D:
        case kVK_RightArrow:
            self.messageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P1_RIGHT));
            break;

        /* Player 2*/
        case kVK_ANSI_P:
            self.messageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P2_PAUSE));
            break;
        case kVK_ANSI_I:
            self.messageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P2_UP));
            break;
        case kVK_ANSI_J:
            self.messageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P2_LEFT));
            break;
        case kVK_ANSI_K:
            self.messageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P2_DOWN));
            break;
        case kVK_ANSI_L:
            self.messageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P2_RIGHT));
            break;
    }
}

@end

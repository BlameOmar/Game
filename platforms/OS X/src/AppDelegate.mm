//
//  AppDelegate.m
//  Game
//
//  Created by Omar Stefan Evans on 11/23/13.
//
//

#import "AppDelegate.h"

using std::thread;

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    [self.window makeFirstResponder:self.window.contentView];

    self.gameSystem = new ::evansbros::game::GameSystem();
    self.gameView.gameSystemMessageQueue = self.gameSystem->getMessageQueue();
    self.gameView.renderer = static_cast<::evansbros::graphics::CGLRenderer *>(self.gameSystem->getRenderer());
    self.gameSystem->start();
}

- (void)applicationWillTerminate:(NSNotification *)notification
{
    self.gameSystem->stop();
    [self.window close];
    delete self.gameSystem;
}

- (void)applicationWillFinishLaunching:(NSNotification *)notification
{
    [self createOpenGLView];
    [self.window toggleFullScreen:self];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
    return YES;
}

- (void)createOpenGLView
{
    NSOpenGLPixelFormatAttribute pixelFormatAttributes[] = {
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
        NSOpenGLPFAColorSize    , 24                           ,
        NSOpenGLPFAAlphaSize    , 8                            ,
        NSOpenGLPFADoubleBuffer ,
        NSOpenGLPFAAccelerated  ,
        NSOpenGLPFASampleBuffers, 1,
        NSOpenGLPFASamples      , 4,
        NSOpenGLPFAMultisample,
        0
    };

    NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes: pixelFormatAttributes];
    self.window.contentView = self.gameView = [[CGLRendererView alloc] initWithFrame:[self.window.contentView bounds] pixelFormat:pixelFormat];
}

@end

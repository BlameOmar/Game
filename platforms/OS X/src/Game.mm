/**************************************************************************************************
 * Title:         Game.mm
 * Author:        Omar Stefan Evans
 * Created on:    2013-11-23
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#import "Game.h"

#include <thread>

using std::thread;

using namespace evansbros::game;

@implementation Game

- (void)applicationWillFinishLaunching:(NSNotification *)notification
{
    [self createOpenGLView];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    [self.window makeFirstResponder:self.window.contentView];

//    self.gameSystem = new GameSystem(self.gameView.renderer, self.gameView.messageQueue);
//    self.gameSystem->start();
}

- (void)applicationWillTerminate:(NSNotification *)notification
{
//    self.gameSystem->stop();
//    delete self.gameSystem;
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
        NSOpenGLPFADepthSize    , 16                           ,
        NSOpenGLPFADoubleBuffer ,
        NSOpenGLPFAAccelerated  ,
        NSOpenGLPFASampleBuffers, 1,
        NSOpenGLPFASamples      , 4,
        NSOpenGLPFAMultisample,
        0
    };

    NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes: pixelFormatAttributes];
    self.window.contentView = self.gameView = [[GameView alloc] initWithFrame:[self.window.contentView bounds] pixelFormat:pixelFormat];
}

@end

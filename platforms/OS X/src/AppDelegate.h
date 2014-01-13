//
//  AppDelegate.h
//  Game
//
//  Created by Omar Stefan Evans on 11/23/13.
//
//

#import <Cocoa/Cocoa.h>
#import "CGLRendererView.h"

#include <thread>

#include "GameSystem.h"

@interface AppDelegate : NSObject <NSApplicationDelegate>

@property (assign) IBOutlet NSWindow *window;
@property CGLRendererView *gameView;
@property (assign) ::evansbros::game::GameSystem *gameSystem;

@end
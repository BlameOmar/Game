//
//  AppDelegate.h
//  Game
//
//  Created by Omar Stefan Evans on 11/23/13.
//
//

#import <Cocoa/Cocoa.h>
#import "GameView.h"

#include <thread>

#include "GameSystem.h"

@interface Game : NSObject <NSApplicationDelegate>

@property (assign) IBOutlet NSWindow *window;
@property GameView *gameView;
@property (assign) ::evansbros::game::GameSystem *gameSystem;

@end
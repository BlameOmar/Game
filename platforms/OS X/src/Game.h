/**************************************************************************************************
 * Title:         Game.h
 * Author:        Omar Stefan Evans
 * Created on:    2013-11-23
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#import <Cocoa/Cocoa.h>
#import "GameView.h"

#include "GameSystem.h"

using namespace evansbros::game;

@interface Game : NSObject <NSApplicationDelegate>

@property (assign) IBOutlet NSWindow *window;
@property GameView *gameView;
@property (assign) GameSystem *gameSystem;

@end
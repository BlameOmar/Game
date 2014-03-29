/**************************************************************************************************
 * Title:         GameView.h
 * Author:        Omar Stefan Evans
 * Created on:    2013-07-13
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#import <Cocoa/Cocoa.h>
#import <Quartz/Quartz.h>

#include "GameSystem.h"
#include "CGLRenderer.h"
#include "MessageQueue.h"

using namespace evansbros;

@interface GameView : NSOpenGLView {
@private
    CVDisplayLinkRef displayLink;
    BOOL initializedGameSystem;
}

@property (assign) graphics::CGLRenderer *renderer;
@property (assign) game::MessageQueue *messageQueue;
@property (assign) game::GameSystem *gameSystem;

@end

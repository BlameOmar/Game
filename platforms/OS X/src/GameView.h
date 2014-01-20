/**************************************************************************************************
 * Title:         GameView.h
 * Author:        Omar Stefan Evans
 * Created on:    2013-07-13
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#import <Cocoa/Cocoa.h>

#include "CGLRenderer.h"
#include "MessageQueue.h"

using namespace evansbros;

@interface GameView : NSOpenGLView

@property (assign) graphics::CGLRenderer *renderer;
@property (assign) game::MessageQueue *messageQueue;

@end

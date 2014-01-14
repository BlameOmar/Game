/**************************************************************************************************
 * Title:         OpenGL.h
 * Author:        Omar Stefan Evans
 * Created on:    2013-12-17
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#define GL3_PROTOTYPES 1
#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <GL\gl3w.h>
#endif

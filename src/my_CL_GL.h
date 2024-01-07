#ifndef MY_CL_GL_H
#define MY_CL_GL_H

#define CL_TARGET_OPENCL_VERSION 200

#include <epoxy/gl.h>

#ifdef __APPLE__
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

#include <CL/cl_gl.h>
#include "openCL_err.h"

extern const cl_context_properties my_context_properties[] ;

#include <GL/glx.h>

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#endif
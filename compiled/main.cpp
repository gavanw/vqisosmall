
#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif

#define _CRT_SECURE_NO_DEPRECATE 1

const static int DEF_SCALE_FACTOR = 2;
const static int MAX_LAYERS = 2;






const static int DEF_WIN_W = 1920;
const static int DEF_WIN_H = 1080;




const static int MAX_LIGHTS = 24;
const static int MAX_EVAL_LIGHTS = 1024;
const static int FLOATS_PER_LIGHT = 16;



const static float UI_SCALE_FACTOR = 1.0f;

const static int MAX_PLANT_GEN = 16;

const static int MAX_TER_TEX = 9;

const static int MAX_NODE_DIRS = 6;
const static int MAX_NODE_VALS = 4;
const static int TOT_NODE_VALS =
	MAX_NODE_DIRS * MAX_NODE_VALS;

const static int TOT_MAP_DIRS = 4;

const static int MAX_BLOCK_STACK = 10;
const static int MAX_UI_LAYERS = 4;


bool LAST_COMPILE_ERROR = false;

char *BUF_NAMES[] =
{
	"ublock0",
	"ublock1",
	"ublock2",
	"ublock3",
	"ublock4",
	"ublock5",
	"ublock6",
	"ublock7",
	"ublock8",
	"ublock9",
	"ublock10",
	"ublock11",
	"ublock12",
	"ublock13"
};


const static int MAX_VG_FBOS = 16;
int CUR_VG_FBO = 0;
int PAGE_COUNT = 0;


// set to 0 to disable
int MAX_HOLDERS = 1024;


float MAX_GPU_MEM = 2560.0f;
float TOT_GPU_MEM_USAGE = 0.0f;

float MAX_CPU_MEM = 4096.0f;
float TOT_CPU_MEM_USAGE = 0.0f;

bool TRACE_ON = false;
//#define DEBUG_MODE 1

#ifdef WIN32
#include <SDKDDKVer.h>
#endif


#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <vector>
#include <deque>
#include <list>
#include <cstddef>
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <ios>
#include <algorithm>
#include <cstdlib>

#include <iomanip>
#include <map>
#include <ctime>


#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>
#include <float.h>
#ifdef WIN32
#include <tchar.h>
#include <io.h>
#include <conio.h>
#endif

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>

#include <GL/glew.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#ifdef WIN32
#pragma comment(lib, "glew32.lib")
#endif



#ifdef USE_POCO

#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/NetException.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Format.h"
#include "Poco/Runnable.h"
#include "Poco/ThreadPool.h"
#include "Poco/Base64Decoder.h"


using Poco::Net::ServerSocket;
using Poco::Net::WebSocket;
using Poco::Net::WebSocketException;
using Poco::SystemException;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPServerParams;
using Poco::Timestamp;
using Poco::Runnable;
using Poco::ThreadPool;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;

using Poco::Base64Decoder;

#else

/* 
   base64.cpp and base64.h

   Copyright (C) 2004-2008 René Nyffenegger

   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this source code must not be misrepresented; you must not
      claim that you wrote the original source code. If you use this source code
      in a product, an acknowledgment in the product documentation would be
      appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original source code.

   3. This notice may not be removed or altered from any source distribution.

   René Nyffenegger rene.nyffenegger@adp-gmbh.ch

*/


static const std::string base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";


static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;

}

std::string base64_decode(std::string const& encoded_string) {
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::string ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j <4; j++)
      char_array_4[j] = 0;

    for (j = 0; j <4; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}


#endif

/*
#pragma comment (lib, "olepro32.lib")   // for IPicture COM interface support
#include <windows.h>
#include <olectl.h.>    // for OleLoadPicture() and IPicture COM interface
*/






struct charArr {
	long size;
	char *data;
};

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif


#if defined(_DEBUG)
#include <crtdbg.h>
#endif

using namespace std;


#define _USE_MATH_DEFINES

typedef unsigned int uint;


static inline int newcasecmp(const char *s1, const char *s2, size_t n)
{
	int lc1  = 0;
	int lc2  = 0;

	while (n--)
	{
		lc1 = towlower (*s1);
		lc2 = towlower (*s2);

		if (lc1 != lc2)
			return (lc1 - lc2);

		if (!lc1)
			return 0;

		++s1;
		++s2;
	}

	return 0;
}

// todo: this define of wcsncasecmp should not be here

//Win32 incompatibilities
#if defined(WIN32) && !defined(__GNUC__)
static inline bool isnan(double x) {
	return x != x;
}
static inline bool isinf(double x) {
	return !isnan(x) && isnan(x - x);
}
#endif

// Linux compile fix - from quaker66
#ifdef __GNUC__
// #include <cstring>
// #include <cstdlib>
#endif

// Mac compile fixes - from quaker66, Lion fix by dabrahams
#if defined(__APPLE__) && __DARWIN_C_LEVEL < 200809L || (defined(WIN32) && defined(__GNUC__))
#include <wctype.h>
#include <wchar.h>

#endif

// Simple function to check a string 's' has at least 'n' characters
static inline bool simplejson_wcsnlen(const char *s, size_t n) {
	if (s == 0)
		return false;

	const char *save = s;
	while (n-- > 0)
	{
		if (*(save++) == 0) return false;
	}

	return true;
}

struct membuf : std::streambuf
{
	membuf(char *begin, char *end) {
		this->setg(begin, begin, end);
	}
};



bool PROG_ACTIVE = true;

#define glError() { \
		GLenum err = glGetError(); \
		while (err != GL_NO_ERROR) { \
			printf("glError: %s caught at %s:%u", \
						 (char*)gluErrorString(err), __FILE__, __LINE__); \
			err = glGetError(); \
			exit(-1); \
		} \
	}





 


enum E_VOCAB {
	vPosition,
	vRadius,
	vIsAlive,
	vLength
};

enum E_GUI_DATA_STRINGS {
	E_GDS_DATA_SOURCE,
	E_GDS_DATA_FILE,
	E_GDS_CHILD_TYPE,
	E_GDS_CHILD_NAME,
	E_GDS_MATERIAL,
	E_GDS_LENGTH
};

enum E_PERFORMANCE_PROFILE {
	E_PP_TILTING,
	E_PP_FAST_LOWRES,
	E_PP_SCROLLING,
	E_PP_HIGHQUALITY,
	E_PP_FAST_MODIFICATION,
	E_PP_TERRAIN_MODIFICATION,
	E_PP_ENTITY,
	E_PP_LENGTH
};

enum E_GUI_CHILD_TYPES {
	E_GCT_INV_ITEM,
	E_GCT_SHADER_PARAM,
	E_GCT_LENGTH
};

enum E_FONT_WRAPPERS {
	EFW_TEXT,
	EFW_ICONS,
	EFW_LENGTH
};

enum eProgramState {
	E_PS_MENU,
	E_PS_IN_GAME,
	E_PS_SIZE
};

enum eProgramAction {
	E_PA_QUIT,
	E_PA_TOGGLE_FULLSCREEN,
	E_PA_REFRESH,
	E_PA_SIZE
};

enum E_TEX_TYPE {
	E_TEX_TYPE_NOISE
};

enum E_RENDER_METHODS {
	E_RENDER_NONE,
	E_RENDER_VOL,
	E_RENDER_LENGTH
};

enum E_STATES {
	E_STATE_INIT_LAUNCH,
	E_STATE_INIT_BEG,
	E_STATE_INIT_END,
	E_STATE_CREATESIMPLEXNOISE_LAUNCH,
	E_STATE_CREATESIMPLEXNOISE_BEG,
	E_STATE_CREATESIMPLEXNOISE_END,
	E_STATE_NEIGHBORSREADY_LAUNCH,
	E_STATE_NEIGHBORSREADY_BEG,
	E_STATE_NEIGHBORSREADY_END,
	E_STATE_COPYTOTEXTURE_LAUNCH,
	E_STATE_COPYTOTEXTURE_BEG,
	E_STATE_COPYTOTEXTURE_END,
	E_STATE_GENERATEVOLUME_LAUNCH,
	E_STATE_GENERATEVOLUME_BEG,
	E_STATE_GENERATEVOLUME_END,
	E_STATE_WAIT,
	E_STATE_LENGTH

};


// enum E_UI_LIST {
// 	E_UL_FB_MEM,
// 	E_UL_CHUNK_MEM,
// 	E_UL_TOT_MEM,
// 	E_UL_LENGTH
// };

// enum E_UI_LIST {
// 	E_UL_FB_MEM,
// 	E_UL_CHUNK_MEM,
// 	E_UL_TOT_MEM,
// 	E_UL_LENGTH
// };

enum E_TER_TYPE {
	E_TER_GROUNDLEVEL,
	E_TER_UNDERGROUND,
	E_TER_AIR,
	E_TER_LENGTH
};

enum E_CHAR_STATE {
	E_CHAR_STATE_NONE,
	E_CHAR_STATE_SKEL,
	E_CHAR_STATE_RENDERED
};

enum E_MOUSE_STATE {
	E_MOUSE_STATE_MOVE,
	E_MOUSE_STATE_BRUSH,
	E_MOUSE_STATE_PICKING,
	E_MOUSE_STATE_LENGTH
};
string mouseStateStrings[] = {
	"E_MOUSE_STATE_MOVE",
	"E_MOUSE_STATE_BRUSH",
	"E_MOUSE_STATE_PICKING",
	"E_MOUSE_STATE_LENGTH"
};

enum E_BRUSH {
	E_BRUSH_ADD,
	E_BRUSH_SUB,
	E_BRUSH_MOVE,
	E_BRUSH_LENGTH
};

enum E_HOLDER_ACTION {
	E_HOLDER_ACTION_RENDER,
	E_HOLDER_ACTION_REDRAW_CHILDREN,
	E_HOLDER_ACTION_RESET,
	E_HOLDER_ACTION_LENGTH
};

enum E_PLANE_TYPES {
	E_PLANE_XY,
	E_PLANE_YZ,
	E_PLANE_XZ,
	E_PLANE_LENGTH
};

// enum E_GRASS_STATE {
//     E_GRASS_STATE_OFF,
//     E_GRASS_STATE_ON,
//     E_GRASS_STATE_ANIM,
//     E_GRASS_STATE_LENGTH
// };

enum E_FILL_STATE {
	E_FILL_STATE_EMPTY,
	E_FILL_STATE_PARTIAL,
	E_FILL_STATE_FULL,
};

enum E_PLANT_TYPES {
	E_PT_OAK_TRUNK,
	E_PT_OAK_ROOTS,
	E_PT_OAK2_TRUNK,
	E_PT_OAK2_ROOTS,
	E_PT_BARE_OAK_TRUNK,
	E_PT_BARE_OAK_ROOTS,
	E_PT_LENGTH
};

enum E_OBJ {
	E_OBJ_CAMERA,
	E_OBJ_FOG,
	E_OBJ_CUTAWAY,
	E_OBJ_HUMAN,
	//E_OBJ_P0,
	//E_OBJ_P1,
	//E_OBJ_P2,
	E_OBJ_LIGHT0,
	E_OBJ_LIGHT1,
	E_OBJ_LIGHT2,
	E_OBJ_LIGHT3,
	E_OBJ_LIGHT4,
	E_OBJ_LIGHT5,
	E_OBJ_LENGTH // LIGHTS MUST BE LAST ENTRIES
};

enum E_MAT_SUBPARAM {
	E_MAT_SUBPARAM_NONE,
	E_MAT_SUBPARAM_TUDOR,
	E_MAT_SUBPARAM_DOCK,
	E_MAT_SUBPARAM_BRICK,
	E_MAT_SUBPARAM_BRICK_ARCH,
	E_MAT_SUBPARAM_LENGTH
};


enum E_MAT_PARAM {
	E_MAT_PARAM_FOUNDATION,
	E_MAT_PARAM_ROOF,
	//E_MAT_PARAM_WALKWAY_TOP,
	//E_MAT_PARAM_DOCK,
	E_MAT_PARAM_BUILDING,
	//E_MAT_PARAM_WALKWAY,
	E_MAT_PARAM_LANTERN,
	E_MAT_PARAM_DOORWAY,
	E_MAT_PARAM_DOOR,
	//E_MAT_PARAM_STAIRS,
	E_MAT_PARAM_TREE, // TREES MUST BE LAST ENTRY
	E_MAT_PARAM_LENGTH
};


enum E_ENT_SUBPARAM {
	E_ENT_SUBPARAM_NOT_SEL,
	E_ENT_SUBPARAM_SEL,
	E_ENT_SUBPARAM_LENGTH
};

enum E_ENT_PARAM {
	E_ENT_PARAM_GEOM,
	E_ENT_PARAM_LINES,
	E_ENT_PARAM_LENGTH
};


// enum E_CONNECTION_SUBTYPES {
//     E_CST_NULL,
//     E_CST_TUDOR,
//     E_CST_BRICK,
//     E_CST_LENGTH
// };

enum E_BLOCK_GEN {
	E_BG_ROADS_AND_BUILDINGS,
	//E_BG_STAIRS,
	//E_BG_REMOVE_REDUNDANT_Z_SEGMENTS,
	E_BG_ROOFS,
	//E_BG_BASEMENTS,
	E_BG_WING_TIPS,
	E_BG_DOORS,
	E_BG_FILL_TERRAIN,
	E_BG_LENGTH
};

enum E_CONNECTION_TYPE_CLASSES {
	E_CTC_NOTHING,
	E_CTC_ROAD,
	E_CTC_ROOF,
	E_CTC_ROOM,
	E_CTC_STAIRS,
	E_CTC_LENGTH
};

enum E_CONNECTION_TYPES {
	E_CT_NULL,
	E_CT_CONNECTED,
	E_CT_FOUNDATION,
	E_CT_ROAD,
	E_CT_DOCK,
	E_CT_MAINHALL,
	E_CT_WING,
	E_CT_ROOF,
	E_CT_WALKWAY_TOP,
	E_CT_ROOM_BRICK,
	E_CT_ROOM_TUDOR,
	E_CT_WALKWAY,
	E_CT_STAIRS,
	E_CT_LANTERN,
	E_CT_WINDOWFRAME,
	E_CT_WINDOW,
	E_CT_DOORWAY,
	E_CT_DOOR,
	E_CT_OBJECT,
	E_CT_LINES,
	E_CT_TREE,
	E_CT_LENGTH
};


// enum E_HOLDER_STATE {
// 	EHS_INIT_BEG,
// 	EHS_INIT_END,
// 	EHS_
// }

// enum E_BUILDING_TYPE {
// 	E_BT_NULL,
// 	E_BT_ROAD,
// 	E_BT_DOCK,
// 	E_BT_MAINHALL,
// 	E_BT_WING,
// 	// E_BT_BALCONY,
// 	// E_BT_TOWER,
// 	// E_BT_LANTERN,
// 	// E_BT_DOORWAY,
// 	// E_BT_WINDOWFRAME,
// 	// E_BT_DOOR,
// 	// E_BT_WINDOW,
// 	//E_BT_OBJ,
// 	//E_BT_TREE,
// 	E_BT_LENGTH
// };


enum E_BONES_HUMAN {
	
	E_BONE_L_BEG, ///////////////
	E_BONE_L_SHOULDER,
	E_BONE_L_UPPERARM,
	E_BONE_L_LOWERARM,
	E_BONE_L_METACARPALS,
	E_BONE_L_PROXIMAL0, // pinky
	E_BONE_L_PROXIMAL1, // ring
	E_BONE_L_PROXIMAL2, // middle
	E_BONE_L_PROXIMAL3, // index
	E_BONE_L_PROXIMAL4, // thumb
	E_BONE_L_INTER0, // pinky
	E_BONE_L_INTER1, // ring
	E_BONE_L_INTER2, // middle
	E_BONE_L_INTER3, // index
	E_BONE_L_INTER4, // thumb
	E_BONE_L_DISTAL0, // pinky
	E_BONE_L_DISTAL1, // ring
	E_BONE_L_DISTAL2, // middle
	E_BONE_L_DISTAL3, // index
	E_BONE_L_DISTAL4, // thumb
	E_BONE_L_HIP,
	E_BONE_L_UPPERLEG,
	E_BONE_L_LOWERLEG,
	E_BONE_L_TALUS,
	E_BONE_L_PHALANGE,
	E_BONE_L_END, //////////////
	E_BONE_R_BEG, //////////////
	E_BONE_R_SHOULDER,
	E_BONE_R_UPPERARM,
	E_BONE_R_LOWERARM,
	E_BONE_R_METACARPALS,
	E_BONE_R_PROXIMAL0, // pinky
	E_BONE_R_PROXIMAL1, // ring
	E_BONE_R_PROXIMAL2, // middle
	E_BONE_R_PROXIMAL3, // index
	E_BONE_R_PROXIMAL4, // thumb
	E_BONE_R_INTER0, // pinky
	E_BONE_R_INTER1, // ring
	E_BONE_R_INTER2, // middle
	E_BONE_R_INTER3, // index
	E_BONE_R_INTER4, // thumb
	E_BONE_R_DISTAL0, // pinky
	E_BONE_R_DISTAL1, // ring
	E_BONE_R_DISTAL2, // middle
	E_BONE_R_DISTAL3, // index
	E_BONE_R_DISTAL4, // thumb
	E_BONE_R_HIP,
	E_BONE_R_UPPERLEG,
	E_BONE_R_LOWERLEG,
	E_BONE_R_TALUS,
	E_BONE_R_PHALANGE,
	E_BONE_R_END, /////////////////
	E_BONE_C_BEG, /////////////////
	E_BONE_C_BASE,
	E_BONE_C_SPINE0, // tail
	E_BONE_C_SPINE1,
	E_BONE_C_SPINE2,
	E_BONE_C_SPINE3,
	E_BONE_C_SPINE4, // neck
	E_BONE_C_SKULL,
	E_BONE_C_END //////////////////
	
};

enum E_GUI {
	E_GUI_LENGTH
};

enum eAlignH {
	E_ALIGNH_LEFT,
	E_ALIGNH_CENTER,
	E_ALIGNH_RIGHT,
};

enum eAlignV {
	E_ALIGNV_TOP,
	E_ALIGNV_MIDDLE,
	E_ALIGNV_BOTTOM	
};

enum eFillDir {
	E_FILL_HORIZONTAL,
	E_FILL_VERTICAL
}; 


string boneStrings[] = {
	
	"E_BONE_L_BEG", ///////////////
	"E_BONE_L_SHOULDER",
	"E_BONE_L_UPPERARM",
	"E_BONE_L_LOWERARM",
	"E_BONE_L_METACARPALS",
	"E_BONE_L_PROXIMAL0", // pinky
	"E_BONE_L_PROXIMAL1", // ring
	"E_BONE_L_PROXIMAL2", // middle
	"E_BONE_L_PROXIMAL3", // index
	"E_BONE_L_PROXIMAL4", // thumb
	"E_BONE_L_INTER0", // pinky
	"E_BONE_L_INTER1", // ring
	"E_BONE_L_INTER2", // middle
	"E_BONE_L_INTER3", // index
	"E_BONE_L_INTER4", // thumb
	"E_BONE_L_DISTAL0", // pinky
	"E_BONE_L_DISTAL1", // ring
	"E_BONE_L_DISTAL2", // middle
	"E_BONE_L_DISTAL3", // index
	"E_BONE_L_DISTAL4", // thumb
	"E_BONE_L_HIP",
	"E_BONE_L_UPPERLEG",
	"E_BONE_L_LOWERLEG",
	"E_BONE_L_TALUS",
	"E_BONE_L_PHALANGE",
	"E_BONE_L_END", //////////////
	"E_BONE_R_BEG", //////////////
	"E_BONE_R_SHOULDER",
	"E_BONE_R_UPPERARM",
	"E_BONE_R_LOWERARM",
	"E_BONE_R_METACARPALS",
	"E_BONE_R_PROXIMAL0", // pinky
	"E_BONE_R_PROXIMAL1", // ring
	"E_BONE_R_PROXIMAL2", // middle
	"E_BONE_R_PROXIMAL3", // index
	"E_BONE_R_PROXIMAL4", // thumb
	"E_BONE_R_INTER0", // pinky
	"E_BONE_R_INTER1", // ring
	"E_BONE_R_INTER2", // middle
	"E_BONE_R_INTER3", // index
	"E_BONE_R_INTER4", // thumb
	"E_BONE_R_DISTAL0", // pinky
	"E_BONE_R_DISTAL1", // ring
	"E_BONE_R_DISTAL2", // middle
	"E_BONE_R_DISTAL3", // index
	"E_BONE_R_DISTAL4", // thumb
	"E_BONE_R_HIP",
	"E_BONE_R_UPPERLEG",
	"E_BONE_R_LOWERLEG",
	"E_BONE_R_TALUS",
	"E_BONE_R_PHALANGE",
	"E_BONE_R_END", /////////////////
	"E_BONE_C_BEG", /////////////////
	"E_BONE_C_BASE",
	"E_BONE_C_SPINE0", // tail
	"E_BONE_C_SPINE1",
	"E_BONE_C_SPINE2",
	"E_BONE_C_SPINE3",
	"E_BONE_C_SPINE4",
	"E_BONE_C_SPINE5",
	"E_BONE_C_SPINE6", // neck
	"E_BONE_C_SKULL",
	"E_BONE_C_END" //////////////////
	
	
	
};


// NEVER REORDER
enum E_EQUIPMENT_SLOTS {
	E_ES_HELMET,	// 0
	E_ES_NECKLACE,	// 1
	E_ES_CLOAK,		// 2
	E_ES_ARMOR,		// 3
	E_ES_GLOVES,	// 4
	E_ES_PRIMARY,	// 5
	E_ES_SECONDARY,	// 6
	E_ES_BOOTS,		// 7
	E_ES_LENGTH 	// 8
};

// // NEVER REORDER

// enum E_ITEM_IDS {
// 	E_II_IRON_LONG_SWORD,
// 	E_II_IRON_KITE_SHIELD,
// 	E_II_IRON_PLATED_MAIL,
// 	E_II_LENGTH
	
// }



enum E_TREE_PARAMS {
	E_TP_VISMININPIXELST,
	E_TP_VISMAXINPIXELST,
	E_TP_P0,
	E_TP_P1,
	E_TP_P2,
	E_TP_POWERVALS,
	E_TP_POWERVALS2,
	E_TP_THICKVALS,
	E_TP_UNUSED,
	E_TP_MATPARAMS, // must be last
	E_TP_LENGTH
};

enum E_LINES_PARAMS {
	E_AP_VISMININPIXELST,
	E_AP_VISMAXINPIXELST,
	E_AP_ORG, // origin
	E_AP_TAN, // tangent (not normalized)
	E_AP_BIT, // bitangent (normalized)
	E_AP_NOR, // normal (normalized)
	E_AP_RAD0, // radius
	E_AP_RAD1,
	E_AP_UNUSED1,
	E_AP_MATPARAMS, // must be last
	E_AP_LENGTH
};

enum E_GEOM_PARAMS {
	E_GP_VISMININPIXELST,
	E_GP_VISMAXINPIXELST,
	E_GP_BOUNDSMININPIXELST,
	E_GP_BOUNDSMAXINPIXELST,
	E_GP_CORNERDISINPIXELS,
	E_GP_POWERVALS,
	E_GP_POWERVALS2,
	E_GP_THICKVALS,
	E_GP_CENTERPOINT,
	E_GP_MATPARAMS, // must be last
	E_GP_LENGTH
};

// enum E_ENT_TYPES {
// 	E_ET_TEST,
// 	E_ET_LENGTH
// };


enum E_NODE_TYPE {
	E_NT_CONNECTIONPROP,
	E_NT_SHORTPROP,
	E_NT_DYNPROP,
	E_NT_CENTERPROP,
	E_NT_LENGTH
};


enum E_ALIGN {
	E_ALIGN_BOTTOM,
	E_ALIGN_MIDDLE,
	E_ALIGN_TOP
};



struct iVector4 {
	int x;
	int y;
	int z;
	int w;
};
struct fVector4 {
	float x;
	float y;
	float z;
	float w;
};

struct iVector3 {
	int x;
	int y;
	int z;
};
struct fVector3 {
	float x;
	float y;
	float z;
};


struct iVector2 {
	int x;
	int y;
};
struct fVector2 {
	float x;
	float y;
};

struct iBoundingBox {
	int xMin;
	int yMin;
	int xMax;
	int yMax;
};

struct fBoundingBox {
	float xMin;
	float yMin;
	float xMax;
	float yMax;
};





struct intPair {
	int v0;
	int v1;
};

struct floatAndIndex {
	float value;
	int index1;
	int index2;
};

struct coordAndIndex {
	float x;
	float y;
	float xTen;
	float yTen;
	int index;
};

struct PlantRules
{
	float numChildren[2];
	float divergenceAngleV[2];
	float begThickness;
	float endThickness;
	float curLength[MAX_PLANT_GEN];
	float sphereGen;
	float sphereRad;
	//float baseLength;
	//float nodeLengthMultiplier;
	float numGenerations;
	float angleUniformityU;
	float isInit;


};

struct TerTexture {
	int usedByBlockId;
	GLuint texId;
	bool alreadyBound;
};


struct PathNode {
	int index;
	int blockId;
	int x;
	int y;
	int z;
};
bool operator==(const PathNode& lhs, const PathNode& rhs)
{
    return (lhs.index == rhs.index)&&(lhs.blockId==rhs.blockId);
}

struct PathHolder {
	std::vector<PathNode> pathList;
	std::vector<PathNode> visitedList;
};


struct MapNode {
	int connectionProps[TOT_MAP_DIRS];
	int terHeight;
	int adjustedHeight;
	int houseHeight;
	int id;
};

const static unsigned int BC_FLAG_INSIDE = 1;
const static unsigned int BC_FLAG_WING_BEG = 2;
const static unsigned int BC_FLAG_WING_END = 4;

struct BuildingCon {
	int conType;
	unsigned int nodeFlags;
	//bool isWingBeg;
	//bool isWingEnd;
	float wingMult;
	float wallRadInMeters;
	int heightDelta;
	int direction; 	// -1: negative,
					//  0: neutral,
					//  1: positve
};


struct BuildingNode {

	BuildingCon con[TOT_NODE_VALS];

	// int con[TOT_NODE_VALS]; // connections
	// bool isWingBeg[TOT_NODE_VALS];
	// bool isWingEnd[TOT_NODE_VALS];

	//std::vector<ConnectionProp> connections;

	int mazeIndex;
	int id;
	int visited;
	float powerValU;
	float powerValV;
	bool nearTerrain;
	bool nearAir;

	// float terHeight;
	// bool isWingTip;

	// int centerType;
	// int connectionTypes[4];
	// int shortTypes[4];

	// int centerHeight;
	// int connectionHeights[4];
	// int shortHeights[4];


};



const int GLUT_NO_BUTTON = 99;
const int GLUT_OVER = 8;
const int GLUT_OUT = 9;
const int GLUT_CHANGING = 10;


enum E_MUSIC_LIST {
	EML_BIRDSONG0,
	EML_CRICKETS0,
	EML_OCEANWAVES0,
	EML_LENGTH
};

string musicStrings[] = {
	"birdsong0",
	"crickets0",
	"oceanwaves0"
};



// do not reorder!
enum GUI_TYPES {
	E_GT_HOLDER,
	E_GT_SLIDER, // also a toggle if 1 division
	E_GT_BUTTON,
	E_GT_RADIO,
	E_GT_MENUBAR,
	E_GT_LENGTH
};

enum GUI_STRING_TYPES {
	E_GST_LABEL,
	E_GST_UID,
	E_GST_SS,
	E_GST_LENGTH
};
char* guiStringTypes[] = {
	"label",
	"uid",
	"ss"
};

enum E_HOVER_TYPES {
	E_HT_NORMAL,
	E_HT_TOOLTIP,
	E_HT_ONSELECTED,
	E_HT_TOOLTIP_VALUE,
	E_HT_LENGTH
};

enum GUI_FLOAT_TYPES {
	E_GFT_TYPE,
	E_GFT_DIVISIONS,
	E_GFT_VALUE,
	E_GFT_HASBACKGROUND,
	E_GFT_SINGLELINE,
	E_GFT_FILLRATIOX,
	E_GFT_FILLRATIOY,
	E_GFT_FILLDIR,
	E_GFT_ALIGNX,
	E_GFT_ALIGNY,
	E_GFT_LAYER,
	E_GFT_HOVERTYPE, // 0: normal, 1: tooltip, 2: show when parent is selected
	E_GFT_MAXDIMX,
	E_GFT_MAXDIMY,
	E_GFT_LENGTH
};
char* guiFloatTypes[] = {
	"type",
	"divisions",
	"value",
	"hasBackground",
	"singleLine",
	"fillRatioX",
	"fillRatioY",
	"fillDir",
	"alignX",
	"alignY",
	"layer",
	"hoverType",
	"maxDimX",
	"maxDimY"
	
};

string guiStringValues[E_GST_LENGTH];
float guiFloatValues[E_GFT_LENGTH];

enum E_DIR_SPECS {
	E_DIR_X,
	E_DIR_Y,
	E_DIR_Z,
	E_DIR_LENGTH
};

enum eSSProperties {

	E_SS_BGCOL0_R,
	E_SS_BGCOL0_G,
	E_SS_BGCOL0_B,
	E_SS_BGCOL0_A,

	E_SS_BGCOL1_R,
	E_SS_BGCOL1_G,
	E_SS_BGCOL1_B,
	E_SS_BGCOL1_A,

	E_SS_FGCOL0_R,
	E_SS_FGCOL0_G,
	E_SS_FGCOL0_B,
	E_SS_FGCOL0_A,

	E_SS_FGCOL1_R,
	E_SS_FGCOL1_G,
	E_SS_FGCOL1_B,
	E_SS_FGCOL1_A,

	E_SS_BGCOLTEXT0_R,
	E_SS_BGCOLTEXT0_G,
	E_SS_BGCOLTEXT0_B,
	E_SS_BGCOLTEXT0_A,

	E_SS_BGCOLTEXT1_R,
	E_SS_BGCOLTEXT1_G,
	E_SS_BGCOLTEXT1_B,
	E_SS_BGCOLTEXT1_A,

	E_SS_FGCOLTEXT0_R,
	E_SS_FGCOLTEXT0_G,
	E_SS_FGCOLTEXT0_B,
	E_SS_FGCOLTEXT0_A,

	E_SS_FGCOLTEXT1_R,
	E_SS_FGCOLTEXT1_G,
	E_SS_FGCOLTEXT1_B,
	E_SS_FGCOLTEXT1_A,

	E_SS_TGCOL0_R,
	E_SS_TGCOL0_G,
	E_SS_TGCOL0_B,
	E_SS_TGCOL0_A,

	E_SS_TGCOL1_R,
	E_SS_TGCOL1_G,
	E_SS_TGCOL1_B,
	E_SS_TGCOL1_A,

	E_SS_BDCOL_R,
	E_SS_BDCOL_G,
	E_SS_BDCOL_B,
	E_SS_BDCOL_A,

	E_SS_PADDING,
	E_SS_BORDER,
	E_SS_MARGIN,
	E_SS_CORNERRAD,
	E_SS_ROUNDNESS,

	E_SS_PROPS_SIZE
};

enum eCompStates {
	E_COMP_UP,
	E_COMP_OVER,
	E_COMP_DOWN,
	E_COMP_TOTAL
};

struct CharStruct {
	float consumedW;
	float consumedH;
	
	float offsetX;
	float offsetY;
	
	float sampX;
	float sampY;
	float sampW;
	float sampH;
};



class StyleSheetState {
private:

public:

	float props[E_SS_PROPS_SIZE];

	StyleSheetState() {

	}

	void setVal(int offsetVal, float x, float y, float z, float w) {
		props[offsetVal] = x;
		props[offsetVal + 1] = y;
		props[offsetVal + 2] = z;
		props[offsetVal + 3] = w;

	}

	void init() {

		int i;

		for (i = 0; i < E_SS_PROPS_SIZE; i++) {
			props[i] = 0.0f;
		}
	}

	void copyFrom(StyleSheetState *cf) {
		int i;

		for (i = 0; i < E_SS_PROPS_SIZE; i++) {
			props[i] = cf->props[i];
		}
	}


};

class StyleSheet {
private:

public:
	StyleSheetState compStates[E_COMP_TOTAL];

	StyleSheet() {

	}

	void copyFrom(StyleSheet* fromSS) {
		compStates[E_COMP_UP].copyFrom(&(fromSS->compStates[E_COMP_UP]));
		compStates[E_COMP_OVER].copyFrom(&(fromSS->compStates[E_COMP_OVER]));
		compStates[E_COMP_DOWN].copyFrom(&(fromSS->compStates[E_COMP_DOWN]));
	}

	void init() {
		int i;

		for (i = 0; i < E_COMP_TOTAL; i++) {
			compStates[i].init();
		}

	}


};

class StyleSheetResult: public StyleSheetState {
private:

public:
	StyleSheet *baseSS;
	float incVal;
	float stateTotal;
	float stateAmounts[E_COMP_TOTAL];

	typedef StyleSheetState super;

	StyleSheetResult() {

	}

	void init(StyleSheet *_baseSS) {
		baseSS = _baseSS;
		super::init();

		int i;

		incVal = 0.1f;

		for (i = 0; i < E_COMP_TOTAL; i++) {
			stateAmounts[i] = 0.0f;
		}

		stateAmounts[E_COMP_UP] = 1.0f;
	}


	void incrementVal(int enumVal) {
		int i;
		for (i = 0; i < E_COMP_TOTAL; i++) {
			stateAmounts[i] -= incVal;
		}

		stateAmounts[enumVal] += 2.0 * incVal;

		for (i = 0; i < E_COMP_TOTAL; i++) {
			if (stateAmounts[i] < 0.0f) {
				stateAmounts[i] = 0.0f;
			}
			if (stateAmounts[i] > 1.0f) {
				stateAmounts[i] = 1.0f;
			}
		}

		float tot = 0.0f;

		for (i = 0; i < E_COMP_TOTAL; i++) {
			tot += stateAmounts[i];
		}
		stateTotal = tot;

	}

	void update(bool mouseOver, bool mouseDown) {


		if (mouseOver) {
			if (mouseDown) {
				incrementVal(E_COMP_DOWN);
			}
			else {
				incrementVal(E_COMP_OVER);
			}
		}
		else {
			incrementVal(E_COMP_UP);
		}


		int i;
		int j;

		float bval;

		for (i = 0; i < E_SS_PROPS_SIZE; i++) {

			props[i] = 0.0f;
			for (j = 0; j < E_COMP_TOTAL; j++) {
				bval = baseSS->compStates[j].props[i];
				props[i] += bval * stateAmounts[j];
			}
			props[i] /= stateTotal;
		}

	}
};





////////////////////////////////////////////////////

//    DONT FORGET SEMICOLONS!

////////////////////////////////////////////////////
 

int intDiv(int v, int s) {
	float fv = v;
	float fs = s;

	if (v < 0) {
		return -ceil(-fv / fs);
	}
	else {
		return v / s;
	}
}

void pack16(float num, float &outR, float &outG) {

    int iz = int(num);
    int ir = iz%256;
    int ig = iz/256;

    outR = float(ir)/255.0;
    outG = float(ig)/255.0;

}

int getPackedColor(uint r, uint g, uint b) {
	return (
					 (1 << 15) |
					 ((b >> 3) << 10) |
					 ((g >> 3) << 5) |
					 ((r >> 3))
				 );
}

int clamp(int val, int min, int max) {
	if (val > max) {
		val = max;
	}
	if (val < min) {
		val = min;
	}
	return val;
}

float mixf(float v1, float v2, float lerpVal) {
	return v1*(1.0f-lerpVal) + v2*lerpVal;
}




float clampf(float val, float min, float max) {
	if (val > max) {
		val = max;
	}
	if (val < min) {
		val = min;
	}
	return val;
}

float smoothstep(float edge0, float edge1, float x) {
    // Scale, bias and saturate x to 0..1 range
    x = clampf((x - edge0)/(edge1 - edge0), 0.0f, 1.0f); 
    // Evaluate polynomial
    return x*x*(3.0f - 2.0f*x);
}

inline float clampfZO(float val) {
	return clampf(val, 0.0f, 1.0f);
}


// float genRand(float LO, float HI)
// {

// 	return LO + (float)rand() / ((float)RAND_MAX / (HI - LO));
// }

inline float fGenRand() {

	return (float)rand() / (float)RAND_MAX;
	//return ((float)(rand()%100000))/100000.0f;
}

float fSeedRand2(float x, float y) {
	float intPart;
	return modf(sin(x * 12.9898 + y * 78.233) * 43758.5453, &intPart);
}

int iSeedRand2(float x, float y, int minV, int maxV) {
	float res = fSeedRand2(x, y);
	return minV + max(int((maxV + 1 - minV) * res), 0);
}


inline int iGenRand(int nMin, int nMax)
{
	return nMin + (int)((double)rand() / (RAND_MAX + 1) * (nMax - nMin + 1));
}

unsigned int intLogB2 (unsigned int val) {
	unsigned int ret = -1;
	while (val != 0) {
		val >>= 1;
		ret++;
	}
	return ret;
}

int intPow(int x, int p) {
	int i = 1;
	for (int j = 1; j <= p; j++) {
		i *= x;
	}
	return i;
}

int wrapCoord(int val, int max) {
	while (val < 0) {
		val += max;
	}
	while (val >= max) {
		val -= max;
	}

	return val;
}



class FIVector4 {
private:
	iVector4 iv4;
	fVector4 fv4;

	iVector3 iv3;
	fVector3 fv3;

	iVector2 iv2;
	fVector2 fv2;

public:

	FIVector4() {
		iv4.x = 0;
		iv4.y = 0;
		iv4.z = 0;
		iv4.w = 0;
		fv4.x = 0.0;
		fv4.y = 0.0;
		fv4.z = 0.0;
		fv4.w = 0.0;
	}

	float operator[] (int ind) { //float&
		
		switch (ind) {
			case 0:
				return fv4.x;
			break;
			case 1:
				return fv4.y;
			break;
			case 2:
				return fv4.z;
			break;
			case 3:
				return fv4.w;
			break;
		}
		
		cout << "invalid vector index";
		return -1.0f;
	}



	void setIXYZW(int x, int y, int z, int w) {
		iv4.x = x;
		iv4.y = y;
		iv4.z = z;
		iv4.w = w;
		fv4.x = (float)x;
		fv4.y = (float)y;
		fv4.z = (float)z;
		fv4.w = (float)w;
	}
	void setIXYZ(int x, int y, int z) {
		iv4.x = x;
		iv4.y = y;
		iv4.z = z;
		fv4.x = (float)x;
		fv4.y = (float)y;
		fv4.z = (float)z;
	}
	void setIXY(int x, int y) {
		iv4.x = x;
		iv4.y = y;
		fv4.x = (float)x;
		fv4.y = (float)y;
	}
	void setIX(int x) {
		iv4.x = x;
		fv4.x = (float)x;
	}
	void setIY(int y) {
		iv4.y = y;
		fv4.y = (float)y;
	}
	void setIZ(int z) {
		iv4.z = z;
		fv4.z = (float)z;
	}
	void setIW(int w) {
		iv4.w = w;
		fv4.w = (float)w;
	}

	void copyFrom(FIVector4 *cf) {
		iv4.x = cf->getIX();
		iv4.y = cf->getIY();
		iv4.z = cf->getIZ();
		iv4.w = cf->getIW();

		fv4.x = cf->getFX();
		fv4.y = cf->getFY();
		fv4.z = cf->getFZ();
		fv4.w = cf->getFW();
	}

	void copyIntDiv(FIVector4 *cf, int val) {
		iv4.x = cf->getIX();
		iv4.y = cf->getIY();
		iv4.z = cf->getIZ();
		iv4.w = cf->getIW();

		fv4.x = cf->getFX();
		fv4.y = cf->getFY();
		fv4.z = cf->getFZ();
		fv4.w = cf->getFW();

		intDivXYZ(val);
	}

	void copyIntMult(FIVector4 *cf, int val) {
		iv4.x = cf->getIX();
		iv4.y = cf->getIY();
		iv4.z = cf->getIZ();
		iv4.w = cf->getIW();

		fv4.x = cf->getFX();
		fv4.y = cf->getFY();
		fv4.z = cf->getFZ();
		fv4.w = cf->getFW();

		multXYZ(val);
	}



	void setFXYZW(float x, float y, float z, float w) {
		fv4.x = x;
		fv4.y = y;
		fv4.z = z;
		fv4.w = w;
		iv4.x = (int)x;
		iv4.y = (int)y;
		iv4.z = (int)z;
		iv4.w = (int)w;
	}
	void setFXYZ(float x, float y, float z) {
		fv4.x = x;
		fv4.y = y;
		fv4.z = z;
		iv4.x = (int)x;
		iv4.y = (int)y;
		iv4.z = (int)z;
	}

	void setFXYZRef(FIVector4 *v1) {
		fv4.x = v1->getFX();
		fv4.y = v1->getFY();
		fv4.z = v1->getFZ();
		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}

	void setFXY(float x, float y) {
		fv4.x = x;
		fv4.y = y;
		iv4.x = (int)x;
		iv4.y = (int)y;
	}
	void setFX(float x) {
		fv4.x = x;
		iv4.x = (int)x;
	}
	void setFY(float y) {
		fv4.y = y;
		iv4.y = (int)y;
	}
	void setFZ(float z) {
		fv4.z = z;
		iv4.z = (int)z;
	}
	void setFW(float w) {
		fv4.w = w;
		iv4.w = (int)w;
	}
	
	
	
	
	void setRand(FIVector4 *seedPos) {

		FIVector4 r0;
		FIVector4 r1;
		FIVector4 r2;

		FIVector4 l0;
		FIVector4 l1;
		FIVector4 l2;

		float intPart;

		r0.setFXYZ(12.989f, 78.233f, 98.422f);
		r1.setFXYZ(93.989f, 67.345f, 54.256f);
		r2.setFXYZ(43.332f, 93.532f, 43.734f);

		l0.setFXYZ(
			seedPos->getFX(),
			seedPos->getFY(),
			seedPos->getFZ()
		);
		l1.setFXYZ(
			seedPos->getFZ(),
			seedPos->getFY(),
			seedPos->getFX()
		);
		l2.setFXYZ(
			seedPos->getFY(),
			seedPos->getFX(),
			seedPos->getFZ()
		);

		fv4.x = modf(sin(l0.dot(&r0)) * 43758.8563f, &intPart);
		fv4.y = modf(sin(l1.dot(&r1)) * 24634.6345f, &intPart);
		fv4.z = modf(sin(l2.dot(&r2)) * 56445.2345f, &intPart);

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}

	void addXYZ(float scalar, float multiplier = 1.0f) {
		fv4.x += scalar * multiplier;
		fv4.y += scalar * multiplier;
		fv4.z += scalar * multiplier;

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}
	void addXYZ(float scalarX, float scalarY, float scalarZ, float multiplier = 1.0f) {
		fv4.x += scalarX * multiplier;
		fv4.y += scalarY * multiplier;
		fv4.z += scalarZ * multiplier;

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}
	void addXYZRef(FIVector4 *scalar, float multiplier = 1.0f) {
		fv4.x += scalar->getFX() * multiplier;
		fv4.y += scalar->getFY() * multiplier;
		fv4.z += scalar->getFZ() * multiplier;

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}



	void multXYZ(float scalar) {
		fv4.x *= scalar;
		fv4.y *= scalar;
		fv4.z *= scalar;

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}
	void multXYZ(float scalarX, float scalarY, float scalarZ) {
		fv4.x *= scalarX;
		fv4.y *= scalarY;
		fv4.z *= scalarZ;

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}


	void multXYZ(FIVector4 *scalar) {
		fv4.x *= scalar->getFX();
		fv4.y *= scalar->getFY();
		fv4.z *= scalar->getFZ();

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}

	void divXYZ(FIVector4 *scalar) {
		fv4.x /= scalar->getFX();
		fv4.y /= scalar->getFY();
		fv4.z /= scalar->getFZ();

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}

	void floorXYZ() {
		fv4.x = floor(fv4.x);
		fv4.y = floor(fv4.y);
		fv4.z = floor(fv4.z);

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}


	void intDivXYZ(int scalar) {

		iv4.x = intDiv(iv4.x, scalar);
		iv4.y = intDiv(iv4.y, scalar);
		iv4.z = intDiv(iv4.z, scalar);

		fv4.x = (float)iv4.x;
		fv4.y = (float)iv4.y;
		fv4.z = (float)iv4.z;

	}
	
	void intDivXYZ(int scalarX, int scalarY, int scalarZ) {


		iv4.x = intDiv(iv4.x, scalarX);
		iv4.y = intDiv(iv4.y, scalarY);
		iv4.z = intDiv(iv4.z, scalarZ);

		fv4.x = (float)iv4.x;
		fv4.y = (float)iv4.y;
		fv4.z = (float)iv4.z;

	}

	void modXYZ(int scalar) {
		iv4.x = iv4.x % scalar;
		iv4.y = iv4.y % scalar;
		iv4.z = iv4.z % scalar;

		fv4.x = (float)iv4.x;
		fv4.y = (float)iv4.y;
		fv4.z = (float)iv4.z;

	}

	

	void wrapXYZ(int scalar) {
		iv4.x = wrapCoord(iv4.x, scalar);
		iv4.y = wrapCoord(iv4.y, scalar);
		iv4.z = wrapCoord(iv4.z, scalar);

		fv4.x = (float)iv4.x;
		fv4.y = (float)iv4.y;
		fv4.z = (float)iv4.z;

	}

	void wrapXY(int scalar) {
		iv4.x = wrapCoord(iv4.x, scalar);
		iv4.y = wrapCoord(iv4.y, scalar);

		fv4.x = (float)iv4.x;
		fv4.y = (float)iv4.y;

	}


	void minXYZ(FIVector4 *v1, FIVector4 *v2) {
		fv4.x = std::min(v1->getFX(), v2->getFX());
		fv4.y = std::min(v1->getFY(), v2->getFY());
		fv4.z = std::min(v1->getFZ(), v2->getFZ());

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}

	void maxXYZ(FIVector4 *v1, FIVector4 *v2) {
		fv4.x = std::max(v1->getFX(), v2->getFX());
		fv4.y = std::max(v1->getFY(), v2->getFY());
		fv4.z = std::max(v1->getFZ(), v2->getFZ());

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}

	void clampXYZ(FIVector4 *minV, FIVector4 *maxV) {
		if (fv4.x < minV->getFX()) {
			fv4.x = minV->getFX();
		}
		if (fv4.y < minV->getFY()) {
			fv4.y = minV->getFY();
		}
		if (fv4.z < minV->getFZ()) {
			fv4.z = minV->getFZ();
		}
		if (fv4.x > maxV->getFX()) {
			fv4.x = maxV->getFX();
		}
		if (fv4.y > maxV->getFY()) {
			fv4.y = maxV->getFY();
		}
		if (fv4.z > maxV->getFZ()) {
			fv4.z = maxV->getFZ();
		}

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}

	void clampX(FIVector4 *minV, FIVector4 *maxV) {
		if (fv4.x < minV->getFX()) {
			fv4.x = minV->getFX();
		}
		if (fv4.x > maxV->getFX()) {
			fv4.x = maxV->getFX();
		}

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}
	void clampY(FIVector4 *minV, FIVector4 *maxV) {

		if (fv4.y < minV->getFY()) {
			fv4.y = minV->getFY();
		}
		if (fv4.y > maxV->getFY()) {
			fv4.y = maxV->getFY();
		}

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;
	}
	void clampZ(float minV, float maxV) {

		if (fv4.z < minV) {
			fv4.z = minV;
		}
		if (fv4.z > maxV) {
			fv4.z = maxV;
		}

		iv4.z = (int)fv4.z;
	}



	bool inBoundsIsEqualXYZ(FIVector4 *minV, FIVector4 *maxV) {
		if (fv4.x < minV->getFX()) {
			return false;
		}
		if (fv4.y < minV->getFY()) {
			return false;
		}
		if (fv4.z < minV->getFZ()) {
			return false;
		}
		if (fv4.x > maxV->getFX()) {
			return false;
		}
		if (fv4.y > maxV->getFY()) {
			return false;
		}
		if (fv4.z > maxV->getFZ()) {
			return false;
		}

		return true;
	}

	static void normalizeBounds(FIVector4 *minBounds, FIVector4 *maxBounds) {
		float temp;

		if (minBounds->getFX() > maxBounds->getFX()) {
			temp = maxBounds->getFX();
			maxBounds->setFX(minBounds->getFX());
			minBounds->setFX(temp);
		}
		if (minBounds->getFY() > maxBounds->getFY()) {
			temp = maxBounds->getFY();
			maxBounds->setFY(minBounds->getFY());
			minBounds->setFY(temp);
		}
		if (minBounds->getFZ() > maxBounds->getFZ()) {
			temp = maxBounds->getFZ();
			maxBounds->setFZ(minBounds->getFZ());
			minBounds->setFZ(temp);
		}
	}

	static bool intersect(FIVector4 *aMin, FIVector4 *aMax, FIVector4 *bMin, FIVector4 *bMax) {

		float aWidth = aMax->getFX() - aMin->getFX();
		float aHeight = aMax->getFY() - aMin->getFY();
		float aDepth = aMax->getFZ() - aMin->getFZ();

		float bWidth = bMax->getFX() - bMin->getFX();
		float bHeight = bMax->getFY() - bMin->getFY();
		float bDepth = bMax->getFZ() - bMin->getFZ();

		float aWidthC = (aMax->getFX() + aMin->getFX()) / 2.0f;
		float aHeightC = (aMax->getFY() + aMin->getFY()) / 2.0f;
		float aDepthC = (aMax->getFZ() + aMin->getFZ()) / 2.0f;

		float bWidthC = (bMax->getFX() + bMin->getFX()) / 2.0f;
		float bHeightC = (bMax->getFY() + bMin->getFY()) / 2.0f;
		float bDepthC = (bMax->getFZ() + bMin->getFZ()) / 2.0f;



		return  (abs(aWidthC - bWidthC) * 2.0f <= (aWidth + bWidth)) &&
						(abs(aHeightC - bHeightC) * 2.0f <= (aHeight + bHeight)) &&
						(abs(aDepthC - bDepthC) * 2.0f <= (aDepth + bDepth));
	}

	static void growBoundary(FIVector4 *minB, FIVector4 *maxB, FIVector4 *minV, FIVector4 *maxV) {
		if (minB->getFX() > minV->getFX()) {
			minB->setFX(minV->getFX());
		}
		if (minB->getFY() > minV->getFY()) {
			minB->setFY(minV->getFY());
		}
		if (minB->getFZ() > minV->getFZ()) {
			minB->setFZ(minV->getFZ());
		}
		if (maxB->getFX() < maxV->getFX()) {
			maxB->setFX(maxV->getFX());
		}
		if (maxB->getFY() < maxV->getFY()) {
			maxB->setFY(maxV->getFY());
		}
		if (maxB->getFZ() < maxV->getFZ()) {
			maxB->setFZ(maxV->getFZ());
		}

	}



	bool inBoundsXYZ(FIVector4 *minV, FIVector4 *maxV) {
		if (fv4.x < minV->getFX()) {
			return false;
		}
		if (fv4.y < minV->getFY()) {
			return false;
		}
		if (fv4.z < minV->getFZ()) {
			return false;
		}
		if (fv4.x >= maxV->getFX()) {
			return false;
		}
		if (fv4.y >= maxV->getFY()) {
			return false;
		}
		if (fv4.z >= maxV->getFZ()) {
			return false;
		}

		return true;
	}
	
	bool inBoundsXYZSlack(FIVector4 *minV, FIVector4 *maxV, float slack) {
		if (fv4.x < minV->getFX()-slack) {
			return false;
		}
		if (fv4.y < minV->getFY()-slack) {
			return false;
		}
		if (fv4.z < minV->getFZ()-slack) {
			return false;
		}
		if (fv4.x >= maxV->getFX()+slack) {
			return false;
		}
		if (fv4.y >= maxV->getFY()+slack) {
			return false;
		}
		if (fv4.z >= maxV->getFZ()+slack) {
			return false;
		}

		return true;
	}





	bool inBoundsXY(FIVector4 *minV, FIVector4 *maxV) {
		if (fv4.x < minV->getFX()) {
			return false;
		}
		if (fv4.y < minV->getFY()) {
			return false;
		}
		if (fv4.x > maxV->getFX()) {
			return false;
		}
		if (fv4.y > maxV->getFY()) {
			return false;
		}

		return true;
	}

	bool iNotEqual(FIVector4 *otherVec) {
		if (
			(iv4.x == otherVec->getIX()) &&
			(iv4.y == otherVec->getIY()) &&
			(iv4.z == otherVec->getIZ())
		) {
			return false;
		}
		else {
			return true;
		}
	}



	float wrapDistance(FIVector4 *otherVec, int maxPitch, bool doSet = true) {

		int i;
		int j;

		int bestI;
		int bestJ;

		float shortestDis = FLT_MAX;
		float curDis;

		for (i = -1; i <= 1; i++) {
			for (j = -1; j <= 1; j++) {

				otherVec->addXYZ(i * maxPitch, j * maxPitch, 0, 1.0f);
				curDis = distance(otherVec);
				otherVec->addXYZ(i * maxPitch, j * maxPitch, 0, -1.0f);

				if (curDis < shortestDis) {
					shortestDis = curDis;
					bestI = i;
					bestJ = j;
				}

			}
		}

		if (doSet) {
			otherVec->addXYZ(bestI * maxPitch, bestJ * maxPitch, 0);
		}


		return shortestDis;

	}

	/*

	var raw_dx = Math.abs(x2 - x1);
	var raw_dy = Math.abs(y2 - y1);

	var dx = (raw_dx < (xmax / 2)) ? raw_dx : xmax - raw_dx;
	var dy = (raw_dy < (ymax / 2)) ? raw_dy : ymax - raw_dy;

	var l2dist = Math.sqrt((dx * dx) + (dy * dy));

	*/

	void rotate(float a, int plane) {

		float xp = fv4.x;
		float yp = fv4.y;
		float zp = fv4.z;

		switch (plane) {
		case E_PLANE_XY:
			xp = fv4.x * cos(a) - fv4.y * sin(a);
			yp = fv4.y * cos(a) + fv4.x * sin(a);
			break;

		case E_PLANE_YZ:
			zp = fv4.z * cos(a) - fv4.y * sin(a);
			yp = fv4.y * cos(a) + fv4.z * sin(a);
			break;

		case E_PLANE_XZ:
			xp = fv4.x * cos(a) - fv4.z * sin(a);
			zp = fv4.z * cos(a) + fv4.x * sin(a);
			break;
		}

		fv4.x = xp;
		fv4.y = yp;
		fv4.z = zp;

		iv4.x = (int)fv4.x;
		iv4.y = (int)fv4.y;
		iv4.z = (int)fv4.z;

	}

	void rotate90(int ind) {
		switch (ind) {
		case 0: // 0 deg

			break;

		case 1: // 90 deg
			setFXY(-fv4.y, fv4.x);
			break;

		case 2: // 180 deg
			setFXY(-fv4.x, -fv4.y);
			break;

		case 3: // 270 deg
			setFXY(fv4.y, -fv4.x);
			break;
		}
	}
	
	float distanceXY(FIVector4 *otherVec) {

		float dx = fv4.x - otherVec->getFX();
		float dy = fv4.y - otherVec->getFY();

		return sqrt(dx * dx + dy * dy);
	}

	float distance(FIVector4 *otherVec) {

		float dx = fv4.x - otherVec->getFX();
		float dy = fv4.y - otherVec->getFY();
		float dz = fv4.z - otherVec->getFZ();

		return sqrt(dx * dx + dy * dy + dz * dz);
	}

	float length() {
		return sqrt(fv4.x * fv4.x + fv4.y * fv4.y + fv4.z * fv4.z);
	}

	float manhattanDis(FIVector4 *otherVec) {

		float dx = abs(fv4.x - otherVec->getFX());
		float dy = abs(fv4.y - otherVec->getFY());
		float dz = abs(fv4.z - otherVec->getFZ());

		return max(max(dx, dy), dz);
	}

	void normalize() {
		float len = sqrt(fv4.x * fv4.x + fv4.y * fv4.y + fv4.z * fv4.z);

		fv4.x = fv4.x / len;
		fv4.y = fv4.y / len;
		fv4.z = fv4.z / len;


	}

	float dot(FIVector4 *otherVec) {

		return fv4.x * otherVec->getFX() +
					 fv4.y * otherVec->getFY() +
					 fv4.z * otherVec->getFZ();
	}

	static void cross(FIVector4 *outVec, FIVector4 *v1, FIVector4 *v2) {


		float x1 = v1->getFX();
		float y1 = v1->getFY();
		float z1 = v1->getFZ();

		float x2 = v2->getFX();
		float y2 = v2->getFY();
		float z2 = v2->getFZ();

		outVec->setFXYZ(
			(y1 * z2) - (y2 * z1),
			(z1 * x2) - (z2 * x1),
			(x1 * y2) - (x2 * y1)
		);

	}




	iVector4 *getIXYZW() {
		return &iv4;
	}
	fVector4 *getFXYZW() {
		return &fv4;
	}

	iVector3 *getIXYZ() {
		iv3.x = iv4.x;
		iv3.y = iv4.y;
		iv3.z = iv4.z;
		return &iv3;
	}
	fVector3 *getFXYZ() {
		fv3.x = fv4.x;
		fv3.y = fv4.y;
		fv3.z = fv4.z;
		return &fv3;
	}

	iVector2 *getIXY() {
		iv2.x = iv4.x;
		iv2.y = iv4.y;
		return &iv2;
	}
	fVector2 *getFXY() {
		fv2.x = fv4.x;
		fv2.y = fv4.y;
		return &fv2;
	}

	int getIX() {
		return iv4.x;
	}
	int getIY() {
		return iv4.y;
	}
	int getIZ() {
		return iv4.z;
	}
	int getIW() {
		return iv4.w;
	}

	float getFX() {
		return fv4.x;
	}
	float getFY() {
		return fv4.y;
	}
	float getFZ() {
		return fv4.z;
	}
	float getFW() {
		return fv4.w;
	}


};

struct RotationInfo {
	float rotMatrix[16];
	FIVector4 basePoint;
	FIVector4 axisAngle;
		
};


float getRandSeeded(FIVector4 *seedPos, FIVector4 *seedVals) {
	float intPart;		
	return abs ( modf(sin(seedPos->dot(seedVals)) * 43758.8563f, &intPart) );
}

int iGetRandSeeded(
	FIVector4 *seedPos,
	FIVector4 *seedVals,
	int minV,
	int maxV
) {
	float intPart = 0.0f;		
	int res = abs( modf(sin(seedPos->dot(seedVals)) * 43758.8563f, &intPart) )*1000000.0f;
	res = (res % (maxV + 1 - minV)) + minV;
	
	return res;
}




class AxisRotation {

public:

	float rotationMatrix[16];
	float inputMatrix[4];
	float outputMatrix[4];

	FIVector4 tempRes1;
	FIVector4 tempRes2;
	FIVector4 tempRes3;

	void doRotation(FIVector4 *output, FIVector4 *input, FIVector4 *axis, float angle)
	{
		int i;
		int j;
		int k;

		float u = axis->getFX();
		float v = axis->getFY();
		float w = axis->getFZ();

		float L = (u * u + v * v + w * w);
		float u2 = u * u;
		float v2 = v * v;
		float w2 = w * w;

		float sqrtL = sqrt(L);
		float ca = cos(angle);
		float sa = sin(angle);

		rotationMatrix[0] = (u2 + (v2 + w2) * ca) / L;
		rotationMatrix[1] = (u * v * (1 - ca) - w * sqrtL * sa) / L;
		rotationMatrix[2] = (u * w * (1 - ca) + v * sqrtL * sa) / L;
		rotationMatrix[3] = 0.0f;

		rotationMatrix[4] = (u * v * (1 - ca) + w * sqrtL * sa) / L;
		rotationMatrix[5] = (v2 + (u2 + w2) * ca) / L;
		rotationMatrix[6] = (v * w * (1 - ca) - u * sqrtL * sa) / L;
		rotationMatrix[7] = 0.0f;

		rotationMatrix[8] = (u * w * (1 - ca) - v * sqrtL * sa) / L;
		rotationMatrix[9] = (v * w * (1 - ca) + u * sqrtL * sa) / L;
		rotationMatrix[10] = (w2 + (u2 + v2) * ca) / L;
		rotationMatrix[11] = 0.0f;

		rotationMatrix[12] = 0.0f;
		rotationMatrix[13] = 0.0f;
		rotationMatrix[14] = 0.0f;
		rotationMatrix[15] = 1.0f;



		outputMatrix[0] = 0.0f;
		outputMatrix[1] = 0.0f;
		outputMatrix[2] = 0.0f;
		outputMatrix[3] = 0.0f;

		inputMatrix[0] = input->getFX();
		inputMatrix[1] = input->getFY();
		inputMatrix[2] = input->getFZ();
		inputMatrix[3] = 1.0;


		for (i = 0; i < 4; i++ ) {
			for (j = 0; j < 1; j++) {
				outputMatrix[i] = 0;
				for (k = 0; k < 4; k++) {
					outputMatrix[i] += rotationMatrix[i*4+k] * inputMatrix[k];
				}
			}
		}

		output->setFXYZW(
			outputMatrix[0],
			outputMatrix[1],
			outputMatrix[2],
			outputMatrix[3]
		);

	}
	
	
	
	void buildRotMatrix(
		RotationInfo* rotInfo
	) {
		
		float u = rotInfo->axisAngle.getFX();
		float v = rotInfo->axisAngle.getFY();
		float w = rotInfo->axisAngle.getFZ();
		float angle = rotInfo->axisAngle.getFW();

		float L = (u * u + v * v + w * w);
		float u2 = u * u;
		float v2 = v * v;
		float w2 = w * w;

		float sqrtL = sqrt(L);
		float ca = cos(angle);
		float sa = sin(angle);

		rotInfo->rotMatrix[0] = (u2 + (v2 + w2) * ca) / L;
		rotInfo->rotMatrix[1] = (u * v * (1 - ca) - w * sqrtL * sa) / L;
		rotInfo->rotMatrix[2] = (u * w * (1 - ca) + v * sqrtL * sa) / L;
		rotInfo->rotMatrix[3] = 0.0f;

		rotInfo->rotMatrix[4] = (u * v * (1 - ca) + w * sqrtL * sa) / L;
		rotInfo->rotMatrix[5] = (v2 + (u2 + w2) * ca) / L;
		rotInfo->rotMatrix[6] = (v * w * (1 - ca) - u * sqrtL * sa) / L;
		rotInfo->rotMatrix[7] = 0.0f;

		rotInfo->rotMatrix[8] = (u * w * (1 - ca) - v * sqrtL * sa) / L;
		rotInfo->rotMatrix[9] = (v * w * (1 - ca) + u * sqrtL * sa) / L;
		rotInfo->rotMatrix[10] = (w2 + (u2 + v2) * ca) / L;
		rotInfo->rotMatrix[11] = 0.0f;

		rotInfo->rotMatrix[12] = 0.0f;
		rotInfo->rotMatrix[13] = 0.0f;
		rotInfo->rotMatrix[14] = 0.0f;
		rotInfo->rotMatrix[15] = 1.0f;

	}
	
	
	void applyRotation(
		FIVector4 *output,
		FIVector4 *input,
		RotationInfo* rotInfo
	) {
		int i;
		int j;
		int k;
		int m;
		
		//tempRes3.copyFrom(baseOffset);
		//tempRes3.addXYZRef(parentOffset,-1.0f);

		float u = rotInfo->axisAngle.getFX();
		float v = rotInfo->axisAngle.getFY();
		float w = rotInfo->axisAngle.getFZ();
		float angle = rotInfo->axisAngle.getFW();

		float L = (u * u + v * v + w * w);
		float u2 = u * u;
		float v2 = v * v;
		float w2 = w * w;

		float sqrtL = sqrt(L);
		float ca = cos(angle);
		float sa = sin(angle);

		


		for (m = 0; m < 3; m++) {
			outputMatrix[0] = 0.0f;
			outputMatrix[1] = 0.0f;
			outputMatrix[2] = 0.0f;
			outputMatrix[3] = 0.0f;

			inputMatrix[0] = input[m].getFX();// - (rotInfo->basePoint[0]);
			inputMatrix[1] = input[m].getFY();// - (rotInfo->basePoint[1]);
			inputMatrix[2] = input[m].getFZ();// - (rotInfo->basePoint[2]);
			inputMatrix[3] = 1.0;


			for (i = 0; i < 4; i++ ) {
				for (j = 0; j < 1; j++) {
					outputMatrix[i] = 0;
					for (k = 0; k < 4; k++) {
						outputMatrix[i] += rotInfo->rotMatrix[i*4+k] * inputMatrix[k];
					}
				}
			}

			output[m].setFXYZW(
				outputMatrix[0],// + (rotInfo->basePoint[0]),
				outputMatrix[1],// + (rotInfo->basePoint[1]),
				outputMatrix[2],// + (rotInfo->basePoint[2]),
				outputMatrix[3]
			);
			//output[m].normalize();
		}

		

	}
	
	
	void doRotationTBN(
		FIVector4 *output,
		FIVector4 *input,
		FIVector4 *axisAngle,
		FIVector4 *parentOffset,
		FIVector4 *baseOffset
	)
	{
		int i;
		int j;
		int k;
		int m;
		
		tempRes3.copyFrom(baseOffset);
		tempRes3.addXYZRef(parentOffset,-1.0f);

		float u = axisAngle->getFX();
		float v = axisAngle->getFY();
		float w = axisAngle->getFZ();
		float angle = axisAngle->getFW();

		float L = (u * u + v * v + w * w);
		float u2 = u * u;
		float v2 = v * v;
		float w2 = w * w;

		float sqrtL = sqrt(L);
		float ca = cos(angle);
		float sa = sin(angle);

		rotationMatrix[0] = (u2 + (v2 + w2) * ca) / L;
		rotationMatrix[1] = (u * v * (1 - ca) - w * sqrtL * sa) / L;
		rotationMatrix[2] = (u * w * (1 - ca) + v * sqrtL * sa) / L;
		rotationMatrix[3] = 0.0f;

		rotationMatrix[4] = (u * v * (1 - ca) + w * sqrtL * sa) / L;
		rotationMatrix[5] = (v2 + (u2 + w2) * ca) / L;
		rotationMatrix[6] = (v * w * (1 - ca) - u * sqrtL * sa) / L;
		rotationMatrix[7] = 0.0f;

		rotationMatrix[8] = (u * w * (1 - ca) - v * sqrtL * sa) / L;
		rotationMatrix[9] = (v * w * (1 - ca) + u * sqrtL * sa) / L;
		rotationMatrix[10] = (w2 + (u2 + v2) * ca) / L;
		rotationMatrix[11] = 0.0f;

		rotationMatrix[12] = 0.0f;
		rotationMatrix[13] = 0.0f;
		rotationMatrix[14] = 0.0f;
		rotationMatrix[15] = 1.0f;



		for (m = 0; m < 3; m++) {
			outputMatrix[0] = 0.0f;
			outputMatrix[1] = 0.0f;
			outputMatrix[2] = 0.0f;
			outputMatrix[3] = 0.0f;

			inputMatrix[0] = input[m].getFX() + (tempRes3[0]);
			inputMatrix[1] = input[m].getFY() + (tempRes3[1]);
			inputMatrix[2] = input[m].getFZ() + (tempRes3[2]);
			inputMatrix[3] = 1.0;


			for (i = 0; i < 4; i++ ) {
				for (j = 0; j < 1; j++) {
					outputMatrix[i] = 0;
					for (k = 0; k < 4; k++) {
						outputMatrix[i] += rotationMatrix[i*4+k] * inputMatrix[k];
					}
				}
			}

			output[m].setFXYZW(
				outputMatrix[0] - (tempRes3[0]),
				outputMatrix[1] - (tempRes3[1]),
				outputMatrix[2] - (tempRes3[2]),
				outputMatrix[3]
			);
			output[m].normalize();
		}

		

	}
	

};
AxisRotation axisRotationInstance;




class GameLight {
public:

	int id;
	int globalId;
	int colPacked;
	FIVector4 pos;
	FIVector4 color;
	float screenDistance;
	bool isOn;

	GameLight() {
		isOn = true;
	}

	void updateCP() {
		colPacked = getPackedColor(color.getFX() * 255.0f, color.getFY() * 255.0f, color.getFZ() * 255.0f);
	}

	void init(
		int _id,
		int _globalId,
		FIVector4 *_pos,
		FIVector4 *_color
	) {
		id = _id;
		globalId = _globalId;
		pos.setFXYZRef(_pos);
		color.setFXYZRef(_color);
		updateCP();
	}

	// void initFrom(DynObject* dyno) {
	//     id = -1;
	//     globalId = -1;

	//     pos.setFXYZRef(&(dyno->pos));
	//     color.setFXYZRef(&(dyno->color));
	//     updateCP();
	// }

};


class DynObject {

public:

	FIVector4 pos;
	FIVector4 color;
	FIVector4 posRel;

	int r;
	int g;
	int b;

	int colPacked;
	bool isRelative;
	bool doRender;

	float radius;

	GameLight childLight;


	DynObject() {

	}

	GameLight *getLight() {
		childLight.id = -1;
		childLight.globalId = -1;

		childLight.pos.setFXYZRef(&pos);
		childLight.color.setFXYZRef(&color);
		childLight.updateCP();
		return &childLight;
	}

	void init(int _x, int _y, int _z, int _r, int _g, int _b, bool _doRender, bool _isRelative, FIVector4 *_cameraPos, float _radius) {
		isRelative = _isRelative;
		doRender = _doRender;

		if (isRelative) {
			posRel.setIXYZ(_x, _y, _z);
			pos.setFXYZRef(_cameraPos);
			pos.addXYZRef(&posRel);
		}
		else {
			pos.setIXYZ(_x, _y, _z);
			posRel.setIXYZ(0, 0, 0);
		}

		radius = _radius;

		r = _r;
		g = _g;
		b = _b;

		color.setFXYZ(
			((float)r) / 255.0f,
			((float)g) / 255.0f,
			((float)b) / 255.0f
		);

		colPacked = getPackedColor(r, g, b);
	}


};






 


enum JSONType { JSONType_Null, JSONType_String, JSONType_Bool, JSONType_Number, JSONType_Array, JSONType_Object };

class JSONValue;

typedef std::vector<JSONValue*> JSONArray;
typedef std::map<std::string, JSONValue*> JSONObject;

class JSONValue
{
	
	public:
		JSONValue(/*NULL*/);
		JSONValue(const char *m_char_value);
		JSONValue(const std::string &m_string_value);
		JSONValue(bool m_bool_value);
		JSONValue(double m_number_value);
		JSONValue(const JSONArray &m_array_value);
		JSONValue(const JSONObject &m_object_value);
		~JSONValue();

		bool IsNull() const;
		bool IsString() const;
		bool IsBool() const;
		bool IsNumber() const;
		bool IsArray() const;
		bool IsObject() const;
		
		const std::string &AsString() const;
		bool AsBool() const;
		double AsNumber() const;
		const JSONArray &AsArray() const;
		const JSONObject &AsObject() const;

		int CountChildren() const;
		
		bool HasChild(int index) const;
		JSONValue *Child(int index);
		
		bool HasChild(const char* name) const;
		JSONValue *Child(const char* name);
		
		bool HasChild(string name) const;
		JSONValue *Child(string name);

		std::string Stringify() const;

		static JSONValue *Parse(const char **data);

		static std::string StringifyString(const std::string &str);
	
		//JSONValue* insertValue(string name, JSONValue* val);
	
		JSONType type;
		std::string string_value;
		bool bool_value;
		double number_value;
		JSONArray array_value;
		JSONObject object_value;
};



class JSON
{
	
	public:
		static JSONValue* Parse(const char *data);
		static std::string Stringify(const JSONValue *value);

		static bool SkipWhitespace(const char **data);
		static bool ExtractString(const char **data, std::string &str);
		static double ParseInt(const char **data);
		static double ParseDecimal(const char **data);

		JSON();
};




// Macros to free an array/object
#define FREE_ARRAY(x) { JSONArray::iterator iter; for (iter = x.begin(); iter != x.end(); iter++) { delete *iter; } }
#define FREE_OBJECT(x) { JSONObject::iterator iter; for (iter = x.begin(); iter != x.end(); iter++) { delete (*iter).second; } }


// JSONValue* JSONValue::insertValue(string name, JSONValue* value) {
// 	if (object_value.find(name) != object_value.end()) {
// 		delete object_value[name];
// 	}

// 	if (value == NULL) {
// 		cout << name << " parsed to NULL\n";
// 	}
// 	object_value[name] = value;
// 	return object_value[name];
// }


/**
 * Parses a JSON encoded value to a JSONValue object
 *
 * @access protected
 *
 * @param char** data Pointer to a char* that contains the data
 *
 * @return JSONValue* Returns a pointer to a JSONValue object on success, NULL on error
 */
JSONValue *JSONValue::Parse(const char **data)
{
	// Is it a string?
	if (**data == '"')
	{
		std::string str;
		if (!JSON::ExtractString(&(++(*data)), str))
			return NULL;
		else
			return new JSONValue(str);
	}
	
	// Is it a boolean?
	else if ((simplejson_wcsnlen(*data, 4) && newcasecmp(*data, "true", 4) == 0) || (simplejson_wcsnlen(*data, 5) && newcasecmp(*data, "false", 5) == 0))
	{
		bool value = newcasecmp(*data, "true", 4) == 0;
		(*data) += value ? 4 : 5;
		return new JSONValue(value);
	}
	
	// Is it a null?
	else if (simplejson_wcsnlen(*data, 4) && newcasecmp(*data, "null", 4) == 0)
	{
		(*data) += 4;
		return new JSONValue();
	}
	
	// Is it a number?
	else if (**data == '-' || (**data >= '0' && **data <= '9'))
	{
		// Negative?
		bool neg = **data == '-';
		if (neg) (*data)++;

		double number = 0.0;

		// Parse the whole part of the number - only if it wasn't 0
		if (**data == '0')
			(*data)++;
		else if (**data >= '1' && **data <= '9')
			number = JSON::ParseInt(data);
		else
			return NULL;
		
		// Could be a decimal now...
		if (**data == '.')
		{
			(*data)++;

			// Not get any digits?
			if (!(**data >= '0' && **data <= '9'))
				return NULL;
			
			// Find the decimal and sort the decimal place out
			// Use ParseDecimal as ParseInt won't work with decimals less than 0.1
			// thanks to Javier Abadia for the report & fix
			double decimal = JSON::ParseDecimal(data);
			
			// Save the number
			number += decimal;
		}

		// Could be an exponent now...
		if (**data == 'E' || **data == 'e')
		{
			(*data)++;

			// Check signage of expo
			bool neg_expo = false;
			if (**data == '-' || **data == '+')
			{
				neg_expo = **data == '-';
				(*data)++;
			}
			
			// Not get any digits?
			if (!(**data >= '0' && **data <= '9'))
				return NULL;

			// Sort the expo out
			double expo = JSON::ParseInt(data);
			for (double i = 0.0; i < expo; i++)
				number = neg_expo ? (number / 10.0) : (number * 10.0);
		}

		// Was it neg?
		if (neg) number *= -1;

		return new JSONValue(number);
	}

	// An object?
	else if (**data == '{')
	{
		JSONObject object;
		
		(*data)++;
	
		while (**data != 0)
		{
			// Whitespace at the start?
			if (!JSON::SkipWhitespace(data))
			{
				FREE_OBJECT(object);
				return NULL;
			}
			
			// Special case - empty object
			if (object.size() == 0 && **data == '}')
			{
				(*data)++;
				return new JSONValue(object);
			}
			
			// We want a string now...
			std::string name;
			if (!JSON::ExtractString(&(++(*data)), name))
			{
				FREE_OBJECT(object);
				return NULL;
			}
			
			// More whitespace?
			if (!JSON::SkipWhitespace(data))
			{
				FREE_OBJECT(object);
				return NULL;
			}
			
			// Need a : now
			if (*((*data)++) != ':')
			{
				FREE_OBJECT(object);
				return NULL;
			}
			
			// More whitespace?
			if (!JSON::SkipWhitespace(data))
			{
				FREE_OBJECT(object);
				return NULL;
			}
			
			// The value is here
			JSONValue *value = Parse(data);
			if (value == NULL)
			{
				FREE_OBJECT(object);
				return NULL;
			}
			
			// Add the name:value
			if (object.find(name) != object.end())
				delete object[name];
			object[name] = value;
			
			// More whitespace?
			if (!JSON::SkipWhitespace(data))
			{
				FREE_OBJECT(object);
				return NULL;
			}
			
			// End of object?
			if (**data == '}')
			{
				(*data)++;
				return new JSONValue(object);
			}
			
			// Want a , now
			if (**data != ',')
			{
				FREE_OBJECT(object);
				return NULL;
			}
			
			(*data)++;
		}
		
		// Only here if we ran out of data
		FREE_OBJECT(object);
		return NULL;
	}
	
	// An array?
	else if (**data == '[')
	{
		JSONArray array;
		
		(*data)++;
		
		while (**data != 0)
		{
			// Whitespace at the start?
			if (!JSON::SkipWhitespace(data))
			{
				FREE_ARRAY(array);
				return NULL;
			}
			
			// Special case - empty array
			if (array.size() == 0 && **data == ']')
			{
				(*data)++;
				return new JSONValue(array);
			}
			
			// Get the value
			JSONValue *value = Parse(data);
			if (value == NULL)
			{
				FREE_ARRAY(array);
				return NULL;
			}
			
			// Add the value
			array.push_back(value);
			
			// More whitespace?
			if (!JSON::SkipWhitespace(data))
			{
				FREE_ARRAY(array);
				return NULL;
			}
			
			// End of array?
			if (**data == ']')
			{
				(*data)++;
				return new JSONValue(array);
			}
			
			// Want a , now
			if (**data != ',')
			{
				FREE_ARRAY(array);
				return NULL;
			}
			
			(*data)++;
		}
		
		// Only here if we ran out of data
		FREE_ARRAY(array);
		return NULL;
	}
	
	// Ran out of possibilites, it's bad!
	else
	{
		return NULL;
	}
}

/**
 * Basic constructor for creating a JSON Value of type NULL
 *
 * @access public
 */
JSONValue::JSONValue(/*NULL*/)
{
	type = JSONType_Null;
}

/**
 * Basic constructor for creating a JSON Value of type String
 *
 * @access public
 *
 * @param char* m_char_value The string to use as the value
 */
JSONValue::JSONValue(const char *m_char_value)
{
	type = JSONType_String;
	string_value = std::string(m_char_value);
}

/**
 * Basic constructor for creating a JSON Value of type String
 *
 * @access public
 *
 * @param std::string m_string_value The string to use as the value
 */
JSONValue::JSONValue(const std::string &m_string_value)
{
	type = JSONType_String;
	string_value = m_string_value;
}

/**
 * Basic constructor for creating a JSON Value of type Bool
 *
 * @access public
 *
 * @param bool m_bool_value The bool to use as the value
 */
JSONValue::JSONValue(bool m_bool_value)
{
	type = JSONType_Bool;
	bool_value = m_bool_value;
}

/**
 * Basic constructor for creating a JSON Value of type Number
 *
 * @access public
 *
 * @param double m_number_value The number to use as the value
 */
JSONValue::JSONValue(double m_number_value)
{
	type = JSONType_Number;
	number_value = m_number_value;
}

/**
 * Basic constructor for creating a JSON Value of type Array
 *
 * @access public
 *
 * @param JSONArray m_array_value The JSONArray to use as the value
 */
JSONValue::JSONValue(const JSONArray &m_array_value)
{
	type = JSONType_Array;
	array_value = m_array_value;
}

/**
 * Basic constructor for creating a JSON Value of type Object
 *
 * @access public
 *
 * @param JSONObject m_object_value The JSONObject to use as the value
 */
JSONValue::JSONValue(const JSONObject &m_object_value)
{
	type = JSONType_Object;
	object_value = m_object_value;
}

/**
 * The destructor for the JSON Value object
 * Handles deleting the objects in the array or the object value
 *
 * @access public
 */
JSONValue::~JSONValue()
{
	if (type == JSONType_Array)
	{
		JSONArray::iterator iter;
		for (iter = array_value.begin(); iter != array_value.end(); iter++)
			delete *iter;
	}
	else if (type == JSONType_Object)
	{
		JSONObject::iterator iter;
		for (iter = object_value.begin(); iter != object_value.end(); iter++)
		{
			delete (*iter).second;
		}
	}
}

/**
 * Checks if the value is a NULL
 *
 * @access public
 *
 * @return bool Returns true if it is a NULL value, false otherwise
 */
bool JSONValue::IsNull() const
{
	return type == JSONType_Null;
}

/**
 * Checks if the value is a String
 *
 * @access public
 *
 * @return bool Returns true if it is a String value, false otherwise
 */
bool JSONValue::IsString() const
{
	return type == JSONType_String;
}

/**
 * Checks if the value is a Bool
 *
 * @access public
 *
 * @return bool Returns true if it is a Bool value, false otherwise
 */
bool JSONValue::IsBool() const
{
	return type == JSONType_Bool;
}

/**
 * Checks if the value is a Number
 *
 * @access public
 *
 * @return bool Returns true if it is a Number value, false otherwise
 */
bool JSONValue::IsNumber() const
{
	return type == JSONType_Number;
}

/**
 * Checks if the value is an Array
 *
 * @access public
 *
 * @return bool Returns true if it is an Array value, false otherwise
 */
bool JSONValue::IsArray() const
{
	return type == JSONType_Array;
}

/**
 * Checks if the value is an Object
 *
 * @access public
 *
 * @return bool Returns true if it is an Object value, false otherwise
 */
bool JSONValue::IsObject() const
{
	return type == JSONType_Object;
}

/**
 * Retrieves the String value of this JSONValue
 * Use IsString() before using this method.
 *
 * @access public
 *
 * @return std::string Returns the string value
 */
const std::string &JSONValue::AsString() const
{
	return string_value;
}

/**
 * Retrieves the Bool value of this JSONValue
 * Use IsBool() before using this method.
 *
 * @access public
 *
 * @return bool Returns the bool value
 */
bool JSONValue::AsBool() const
{
	return bool_value;
}

/**
 * Retrieves the Number value of this JSONValue
 * Use IsNumber() before using this method.
 *
 * @access public
 *
 * @return double Returns the number value
 */
double JSONValue::AsNumber() const
{
	return number_value;
}

/**
 * Retrieves the Array value of this JSONValue
 * Use IsArray() before using this method.
 *
 * @access public
 *
 * @return JSONArray Returns the array value
 */
const JSONArray &JSONValue::AsArray() const
{
	return array_value;
}

/**
 * Retrieves the Object value of this JSONValue
 * Use IsObject() before using this method.
 *
 * @access public
 *
 * @return JSONObject Returns the object value
 */
const JSONObject &JSONValue::AsObject() const
{
	return object_value;
}

/**
 * Retrieves the number of children of this JSONValue.
 * This number will be 0 or the actual number of children
 * if IsArray() or IsObject().
 *
 * @access public
 *
 * @return The number of children.
 */
int JSONValue::CountChildren() const
{
	switch (type)
	{
		case JSONType_Array:
			return array_value.size();
		case JSONType_Object:
			return object_value.size();
		default:
			return 0;
	}
}

/**
 * Checks if this JSONValue has a child at the given index.
 * Use IsArray() before using this method.
 *
 * @access public
 *
 * @return bool Returns true if the array has a value at the given index.
 */
bool JSONValue::HasChild(int index) const
{
	if (type == JSONType_Array)
	{
		return index < array_value.size();
	}
	else
	{
		return false;
	}
}

/**
 * Retrieves the child of this JSONValue at the given index.
 * Use IsArray() before using this method.
 *
 * @access public
 *
 * @return JSONValue* Returns JSONValue at the given index or NULL
 *                    if it doesn't exist.
 */
JSONValue *JSONValue::Child(int index)
{
	if (index < array_value.size())
	{
		return array_value[index];
	}
	else
	{
		return NULL;
	}
}

/**
 * Checks if this JSONValue has a child at the given key.
 * Use IsObject() before using this method.
 *
 * @access public
 *
 * @return bool Returns true if the object has a value at the given key.
 */
bool JSONValue::HasChild(const char* name) const
{
	if (type == JSONType_Object)
	{
		return object_value.find(name) != object_value.end();
	}
	else
	{
		return false;
	}
}

bool JSONValue::HasChild(string name) const
{
	if (type == JSONType_Object)
	{
		return object_value.find(name.c_str()) != object_value.end();
	}
	else
	{
		return false;
	}
}

/**
 * Retrieves the child of this JSONValue at the given key.
 * Use IsObject() before using this method.
 *
 * @access public
 *
 * @return JSONValue* Returns JSONValue for the given key in the object
 *                    or NULL if it doesn't exist.
 */
JSONValue* JSONValue::Child(const char* name)
{
	JSONObject::const_iterator it = object_value.find(name);
	if (it != object_value.end())
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}

JSONValue* JSONValue::Child(string name)
{
	JSONObject::const_iterator it = object_value.find(name.c_str());
	if (it != object_value.end())
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}

/**
 * Creates a JSON encoded string for the value with all necessary characters escaped
 *
 * @access public
 *
 * @return std::string Returns the JSON string
 */
std::string JSONValue::Stringify() const
{
	std::string ret_string;
	
	switch (type)
	{
		case JSONType_Null:
			ret_string = "null";
			break;
		
		case JSONType_String:
			ret_string = StringifyString(string_value);
			break;
		
		case JSONType_Bool:
			ret_string = bool_value ? "true" : "false";
			break;
		
		case JSONType_Number:
		{
			if (isinf(number_value) || isnan(number_value))
				ret_string = "null";
			else
			{
				std::stringstream ss;
				ss.precision(15);
				ss << number_value;
				ret_string = ss.str();
			}
			break;
		}
		
		case JSONType_Array:
		{
			ret_string = "[";
			JSONArray::const_iterator iter = array_value.begin();
			while (iter != array_value.end())
			{
				ret_string += (*iter)->Stringify();
				
				// Not at the end - add a separator
				if (++iter != array_value.end())
					ret_string += ",";
			}
			ret_string += "]";
			break;
		}
		
		case JSONType_Object:
		{
			ret_string = "{";
			JSONObject::const_iterator iter = object_value.begin();
			while (iter != object_value.end())
			{
				ret_string += StringifyString((*iter).first);
				ret_string += ":";
				ret_string += (*iter).second->Stringify();
				
				// Not at the end - add a separator
				if (++iter != object_value.end())
					ret_string += ",";
			}
			ret_string += "}";
			break;
		}
	}

	return ret_string;
}

/**
 * Creates a JSON encoded string with all required fields escaped
 * Works from http://www.ecma-internationl.org/publications/files/ECMA-ST/ECMA-262.pdf
 * Section 15.12.3.
 *
 * @access private
 *
 * @param std::string str The string that needs to have the characters escaped
 *
 * @return std::string Returns the JSON string
 */
std::string JSONValue::StringifyString(const std::string &str)
{
	std::string str_out = "\"";
	str_out += str;
	
	// std::string::const_iterator iter = str.begin();
	// while (iter != str.end())
	// {
	// 	char chr = *iter;

	// 	if (chr == '"' || chr == '\\' || chr == '/')
	// 	{
	// 		str_out += '\\';
	// 		str_out += chr;
	// 	}
	// 	else if (chr == '\b')
	// 	{
	// 		str_out += "\\b";
	// 	}
	// 	else if (chr == '\f')
	// 	{
	// 		str_out += "\\f";
	// 	}
	// 	else if (chr == '\n')
	// 	{
	// 		str_out += "\\n";
	// 	}
	// 	else if (chr == '\r')
	// 	{
	// 		str_out += "\\r";
	// 	}
	// 	else if (chr == '\t')
	// 	{
	// 		str_out += "\\t";
	// 	}
	// 	else if (chr < ' ')
	// 	{
	// 		str_out += "\\u";
	// 		for (int i = 0; i < 4; i++)
	// 		{
	// 			int value = (chr >> 12) & 0xf;
	// 			if (value >= 0 && value <= 9)
	// 				str_out += (char)('0' + value);
	// 			else if (value >= 10 && value <= 15)
	// 				str_out += (char)('A' + (value - 10));
	// 			chr <<= 4;
	// 		}
	// 	}
	// 	else
	// 	{
	// 		str_out += chr;
	// 	}
		
	// 	iter++;
	// }
	
	
	str_out += "\"";
	return str_out;
}



JSON::JSON()
{
}

/**
 * Parses a complete JSON encoded string (UNICODE input version)
 *
 * @access public
 *
 * @param char* data The JSON text
 *
 * @return JSONValue* Returns a JSON Value representing the root, or NULL on error
 */
JSONValue *JSON::Parse(const char *data)
{
	// Skip any preceding whitespace, end of data = no JSON = fail
	if (!SkipWhitespace(&data)) {
		//cout << "jp a\n";
		return NULL;
	}
	

	// We need the start of a value here now...
	JSONValue *value = JSONValue::Parse(&data);
	if (value == NULL) {
		//cout << "jp b\n";
		return NULL;
	}
	
	// Can be white space now and should be at the end of the string then...
	// if (SkipWhitespace(&data))
	// {
		
	// 	cout << "jp c\n";
	// 	delete value;
	// 	return NULL;
	// }
	
	
	//cout << "jp d\n";
	
	// We're now at the end of the string
	return value;
}

/**
 * Turns the passed in JSONValue into a JSON encode string
 *
 * @access public
 *
 * @param JSONValue* value The root value
 *
 * @return std::string Returns a JSON encoded string representation of the given value
 */
std::string JSON::Stringify(const JSONValue *value)
{
	if (value != NULL)
		return value->Stringify();
	else
		return "";
}

/**
 * Skips over any whitespace characters (space, tab, \r or \n) defined by the JSON spec
 *
 * @access protected
 *
 * @param char** data Pointer to a char* that contains the JSON text
 *
 * @return bool Returns true if there is more data, or false if the end of the text was reached
 */
bool JSON::SkipWhitespace(const char **data)
{
	while (**data != 0 && (**data == ' ' || **data == '\t' || **data == '\r' || **data == '\n'))
		(*data)++;
	
	return **data != 0;
}

/**
 * Extracts a JSON String as defined by the spec - "<some chars>"
 * Any escaped characters are swapped out for their unescaped values
 *
 * @access protected
 *
 * @param char** data Pointer to a char* that contains the JSON text
 * @param std::string& str Reference to a std::string to receive the extracted string
 *
 * @return bool Returns true on success, false on failure
 */
bool JSON::ExtractString(const char **data, std::string &str)
{
	str = "";
	
	while (**data != 0)
	{
		// Save the char so we can change it if need be
		char next_char = **data;
		
		// Escaping something?
		if (next_char == '\\')
		{
			// Move over the escape char
			(*data)++;
			
			// Deal with the escaped char
			switch (**data)
			{
				case '"': next_char = '"'; break;
				case '\\': next_char = '\\'; break;
				case '/': next_char = '/'; break;
				case 'b': next_char = '\b'; break;
				case 'f': next_char = '\f'; break;
				case 'n': next_char = '\n'; break;
				case 'r': next_char = '\r'; break;
				case 't': next_char = '\t'; break;
				case 'u':
				{
					// We need 5 chars (4 hex + the 'u') or its not valid
					if (!simplejson_wcsnlen(*data, 5))
						return false;
					
					// Deal with the chars
					next_char = 0;
					for (int i = 0; i < 4; i++)
					{
						// Do it first to move off the 'u' and leave us on the
						// final hex digit as we move on by one later on
						(*data)++;
						
						next_char <<= 4;
						
						// Parse the hex digit
						if (**data >= '0' && **data <= '9')
							next_char |= (**data - '0');
						else if (**data >= 'A' && **data <= 'F')
							next_char |= (10 + (**data - 'A'));
						else if (**data >= 'a' && **data <= 'f')
							next_char |= (10 + (**data - 'a'));
						else
						{
							// Invalid hex digit = invalid JSON
							return false;
						}
					}
					break;
				}
				
				// By the spec, only the above cases are allowed
				default:
					return false;
			}
		}
		
		// End of the string?
		else if (next_char == '"')
		{
			(*data)++;
			str.reserve(); // Remove unused capacity
			return true;
		}
		
		// Disallowed char?
		else if (next_char < ' ' && next_char != '\t')
		{
			// SPEC Violation: Allow tabs due to real world cases
			return false;
		}
		
		// Add the next char
		str += next_char;
		
		// Move on
		(*data)++;
	}
	
	// If we're here, the string ended incorrectly
	return false;
}

/**
 * Parses some text as though it is an integer
 *
 * @access protected
 *
 * @param char** data Pointer to a char* that contains the JSON text
 *
 * @return double Returns the double value of the number found
 */
double JSON::ParseInt(const char **data)
{
	double integer = 0;
	while (**data != 0 && **data >= '0' && **data <= '9')
		integer = integer * 10 + (*(*data)++ - '0');
	
	return integer;
}

/**
 * Parses some text as though it is a decimal
 *
 * @access protected
 *
 * @param char** data Pointer to a char* that contains the JSON text
 *
 * @return double Returns the double value of the decimal found
 */
double JSON::ParseDecimal(const char **data)
{
	double decimal = 0.0;
  double factor = 0.1;
	while (**data != 0 && **data >= '0' && **data <= '9')
  {
    int digit = (*(*data)++ - '0');
		decimal = decimal + digit * factor;
    factor *= 0.1;
  }
	return decimal;
}




 
/*
LodePNG version 20130831

Copyright (c) 2005-2013 Lode Vandevenne

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

    3. This notice may not be removed or altered from any source
    distribution.
*/

#ifndef LODEPNG_H
#define LODEPNG_H



/*
The following #defines are used to create code sections. They can be disabled
to disable code sections, which can give faster compile time and smaller binary.
The "NO_COMPILE" defines are designed to be used to pass as defines to the
compiler command to disable them without modifying this header, e.g.
-DLODEPNG_NO_COMPILE_ZLIB for gcc.
*/
/*deflate & zlib. If disabled, you must specify alternative zlib functions in
the custom_zlib field of the compress and decompress settings*/
#ifndef LODEPNG_NO_COMPILE_ZLIB
#define LODEPNG_COMPILE_ZLIB
#endif
/*png encoder and png decoder*/
#ifndef LODEPNG_NO_COMPILE_PNG
#define LODEPNG_COMPILE_PNG
#endif
/*deflate&zlib decoder and png decoder*/
#ifndef LODEPNG_NO_COMPILE_DECODER
#define LODEPNG_COMPILE_DECODER
#endif
/*deflate&zlib encoder and png encoder*/
#ifndef LODEPNG_NO_COMPILE_ENCODER
#define LODEPNG_COMPILE_ENCODER
#endif
/*the optional built in harddisk file loading and saving functions*/
#ifndef LODEPNG_NO_COMPILE_DISK
#define LODEPNG_COMPILE_DISK
#endif
/*support for chunks other than IHDR, IDAT, PLTE, tRNS, IEND: ancillary and unknown chunks*/
#ifndef LODEPNG_NO_COMPILE_ANCILLARY_CHUNKS
#define LODEPNG_COMPILE_ANCILLARY_CHUNKS
#endif
/*ability to convert error numerical codes to English text string*/
#ifndef LODEPNG_NO_COMPILE_ERROR_TEXT
#define LODEPNG_COMPILE_ERROR_TEXT
#endif
/*Compile the default allocators (C's free, malloc and realloc). If you disable this,
you can define the functions lodepng_free, lodepng_malloc and lodepng_realloc in your
source files with custom allocators.*/
#ifndef LODEPNG_NO_COMPILE_ALLOCATORS
#define LODEPNG_COMPILE_ALLOCATORS
#endif
/*compile the C++ version (you can disable the C++ wrapper here even when compiling for C++)*/

#define LODEPNG_NO_COMPILE_CPP

#ifdef LODEPNG_COMPILE_PNG
/*The PNG color types (also used for raw).*/
typedef enum LodePNGColorType
{
  LCT_GREY = 0, /*greyscale: 1,2,4,8,16 bit*/
  LCT_RGB = 2, /*RGB: 8,16 bit*/
  LCT_PALETTE = 3, /*palette: 1,2,4,8 bit*/
  LCT_GREY_ALPHA = 4, /*greyscale with alpha: 8,16 bit*/
  LCT_RGBA = 6 /*RGB with alpha: 8,16 bit*/
} LodePNGColorType;

#ifdef LODEPNG_COMPILE_DECODER
/*
Converts PNG data in memory to raw pixel data.
out: Output parameter. Pointer to buffer that will contain the raw pixel data.
     After decoding, its size is w * h * (bytes per pixel) bytes larger than
     initially. Bytes per pixel depends on colortype and bitdepth.
     Must be freed after usage with free(*out).
     Note: for 16-bit per channel colors, uses big endian format like PNG does.
w: Output parameter. Pointer to width of pixel data.
h: Output parameter. Pointer to height of pixel data.
in: Memory buffer with the PNG file.
insize: size of the in buffer.
colortype: the desired color type for the raw output image. See explanation on PNG color types.
bitdepth: the desired bit depth for the raw output image. See explanation on PNG color types.
Return value: LodePNG error code (0 means no error).
*/
unsigned lodepng_decode_memory(unsigned char** out, unsigned* w, unsigned* h,
                               const unsigned char* in, size_t insize,
                               LodePNGColorType colortype, unsigned bitdepth);

/*Same as lodepng_decode_memory, but always decodes to 32-bit RGBA raw image*/
unsigned lodepng_decode32(unsigned char** out, unsigned* w, unsigned* h,
                          const unsigned char* in, size_t insize);

/*Same as lodepng_decode_memory, but always decodes to 24-bit RGB raw image*/
unsigned lodepng_decode24(unsigned char** out, unsigned* w, unsigned* h,
                          const unsigned char* in, size_t insize);

#ifdef LODEPNG_COMPILE_DISK
/*
Load PNG from disk, from file with given name.
Same as the other decode functions, but instead takes a filename as input.
*/
unsigned lodepng_decode_file(unsigned char** out, unsigned* w, unsigned* h,
                             const char* filename,
                             LodePNGColorType colortype, unsigned bitdepth);

/*Same as lodepng_decode_file, but always decodes to 32-bit RGBA raw image.*/
unsigned lodepng_decode32_file(unsigned char** out, unsigned* w, unsigned* h,
                               const char* filename);

/*Same as lodepng_decode_file, but always decodes to 24-bit RGB raw image.*/
unsigned lodepng_decode24_file(unsigned char** out, unsigned* w, unsigned* h,
                               const char* filename);
#endif /*LODEPNG_COMPILE_DISK*/
#endif /*LODEPNG_COMPILE_DECODER*/


#ifdef LODEPNG_COMPILE_ENCODER
/*
Converts raw pixel data into a PNG image in memory. The colortype and bitdepth
  of the output PNG image cannot be chosen, they are automatically determined
  by the colortype, bitdepth and content of the input pixel data.
  Note: for 16-bit per channel colors, needs big endian format like PNG does.
out: Output parameter. Pointer to buffer that will contain the PNG image data.
     Must be freed after usage with free(*out).
outsize: Output parameter. Pointer to the size in bytes of the out buffer.
image: The raw pixel data to encode. The size of this buffer should be
       w * h * (bytes per pixel), bytes per pixel depends on colortype and bitdepth.
w: width of the raw pixel data in pixels.
h: height of the raw pixel data in pixels.
colortype: the color type of the raw input image. See explanation on PNG color types.
bitdepth: the bit depth of the raw input image. See explanation on PNG color types.
Return value: LodePNG error code (0 means no error).
*/
unsigned lodepng_encode_memory(unsigned char** out, size_t* outsize,
                               const unsigned char* image, unsigned w, unsigned h,
                               LodePNGColorType colortype, unsigned bitdepth);

/*Same as lodepng_encode_memory, but always encodes from 32-bit RGBA raw image.*/
unsigned lodepng_encode32(unsigned char** out, size_t* outsize,
                          const unsigned char* image, unsigned w, unsigned h);

/*Same as lodepng_encode_memory, but always encodes from 24-bit RGB raw image.*/
unsigned lodepng_encode24(unsigned char** out, size_t* outsize,
                          const unsigned char* image, unsigned w, unsigned h);

#ifdef LODEPNG_COMPILE_DISK
/*
Converts raw pixel data into a PNG file on disk.
Same as the other encode functions, but instead takes a filename as output.
NOTE: This overwrites existing files without warning!
*/
unsigned lodepng_encode_file(const char* filename,
                             const unsigned char* image, unsigned w, unsigned h,
                             LodePNGColorType colortype, unsigned bitdepth);

/*Same as lodepng_encode_file, but always encodes from 32-bit RGBA raw image.*/
unsigned lodepng_encode32_file(const char* filename,
                               const unsigned char* image, unsigned w, unsigned h);

/*Same as lodepng_encode_file, but always encodes from 24-bit RGB raw image.*/
unsigned lodepng_encode24_file(const char* filename,
                               const unsigned char* image, unsigned w, unsigned h);
#endif /*LODEPNG_COMPILE_DISK*/
#endif /*LODEPNG_COMPILE_ENCODER*/


#endif /*LODEPNG_COMPILE_PNG*/

#ifdef LODEPNG_COMPILE_ERROR_TEXT
/*Returns an English description of the numerical error code.*/
const char* lodepng_error_text(unsigned code);
#endif /*LODEPNG_COMPILE_ERROR_TEXT*/

#ifdef LODEPNG_COMPILE_DECODER
/*Settings for zlib decompression*/
typedef struct LodePNGDecompressSettings LodePNGDecompressSettings;
struct LodePNGDecompressSettings
{
  unsigned ignore_adler32; /*if 1, continue and don't give an error message if the Adler32 checksum is corrupted*/

  /*use custom zlib decoder instead of built in one (default: null)*/
  unsigned (*custom_zlib)(unsigned char**, size_t*,
                          const unsigned char*, size_t,
                          const LodePNGDecompressSettings*);
  /*use custom deflate decoder instead of built in one (default: null)
  if custom_zlib is used, custom_deflate is ignored since only the built in
  zlib function will call custom_deflate*/
  unsigned (*custom_inflate)(unsigned char**, size_t*,
                             const unsigned char*, size_t,
                             const LodePNGDecompressSettings*);

  void* custom_context; /*optional custom settings for custom functions*/
};

extern const LodePNGDecompressSettings lodepng_default_decompress_settings;
void lodepng_decompress_settings_init(LodePNGDecompressSettings* settings);
#endif /*LODEPNG_COMPILE_DECODER*/

#ifdef LODEPNG_COMPILE_ENCODER
/*
Settings for zlib compression. Tweaking these settings tweaks the balance
between speed and compression ratio.
*/
typedef struct LodePNGCompressSettings LodePNGCompressSettings;
struct LodePNGCompressSettings /*deflate = compress*/
{
  /*LZ77 related settings*/
  unsigned btype; /*the block type for LZ (0, 1, 2 or 3, see zlib standard). Should be 2 for proper compression.*/
  unsigned use_lz77; /*whether or not to use LZ77. Should be 1 for proper compression.*/
  unsigned windowsize; /*the maximum is 32768, higher gives more compression but is slower. Typical value: 2048.*/
  unsigned minmatch; /*mininum lz77 length. 3 is normally best, 6 can be better for some PNGs. Default: 0*/
  unsigned nicematch; /*stop searching if >= this length found. Set to 258 for best compression. Default: 128*/
  unsigned lazymatching; /*use lazy matching: better compression but a bit slower. Default: true*/

  /*use custom zlib encoder instead of built in one (default: null)*/
  unsigned (*custom_zlib)(unsigned char**, size_t*,
                          const unsigned char*, size_t,
                          const LodePNGCompressSettings*);
  /*use custom deflate encoder instead of built in one (default: null)
  if custom_zlib is used, custom_deflate is ignored since only the built in
  zlib function will call custom_deflate*/
  unsigned (*custom_deflate)(unsigned char**, size_t*,
                             const unsigned char*, size_t,
                             const LodePNGCompressSettings*);

  void* custom_context; /*optional custom settings for custom functions*/
};

extern const LodePNGCompressSettings lodepng_default_compress_settings;
void lodepng_compress_settings_init(LodePNGCompressSettings* settings);
#endif /*LODEPNG_COMPILE_ENCODER*/

#ifdef LODEPNG_COMPILE_PNG
/*
Color mode of an image. Contains all information required to decode the pixel
bits to RGBA colors. This information is the same as used in the PNG file
format, and is used both for PNG and raw image data in LodePNG.
*/
typedef struct LodePNGColorMode
{
  /*header (IHDR)*/
  LodePNGColorType colortype; /*color type, see PNG standard or documentation further in this header file*/
  unsigned bitdepth;  /*bits per sample, see PNG standard or documentation further in this header file*/

  /*
  palette (PLTE and tRNS)

  Dynamically allocated with the colors of the palette, including alpha.
  When encoding a PNG, to store your colors in the palette of the LodePNGColorMode, first use
  lodepng_palette_clear, then for each color use lodepng_palette_add.
  If you encode an image without alpha with palette, don't forget to put value 255 in each A byte of the palette.

  When decoding, by default you can ignore this palette, since LodePNG already
  fills the palette colors in the pixels of the raw RGBA output.

  The palette is only supported for color type 3.
  */
  unsigned char* palette; /*palette in RGBARGBA... order. When allocated, must be either 0, or have size 1024*/
  size_t palettesize; /*palette size in number of colors (amount of bytes is 4 * palettesize)*/

  /*
  transparent color key (tRNS)

  This color uses the same bit depth as the bitdepth value in this struct, which can be 1-bit to 16-bit.
  For greyscale PNGs, r, g and b will all 3 be set to the same.

  When decoding, by default you can ignore this information, since LodePNG sets
  pixels with this key to transparent already in the raw RGBA output.

  The color key is only supported for color types 0 and 2.
  */
  unsigned key_defined; /*is a transparent color key given? 0 = false, 1 = true*/
  unsigned key_r;       /*red/greyscale component of color key*/
  unsigned key_g;       /*green component of color key*/
  unsigned key_b;       /*blue component of color key*/
} LodePNGColorMode;

/*init, cleanup and copy functions to use with this struct*/
void lodepng_color_mode_init(LodePNGColorMode* info);
void lodepng_color_mode_cleanup(LodePNGColorMode* info);
/*return value is error code (0 means no error)*/
unsigned lodepng_color_mode_copy(LodePNGColorMode* dest, const LodePNGColorMode* source);

void lodepng_palette_clear(LodePNGColorMode* info);
/*add 1 color to the palette*/
unsigned lodepng_palette_add(LodePNGColorMode* info,
                             unsigned char r, unsigned char g, unsigned char b, unsigned char a);

/*get the total amount of bits per pixel, based on colortype and bitdepth in the struct*/
unsigned lodepng_get_bpp(const LodePNGColorMode* info);
/*get the amount of color channels used, based on colortype in the struct.
If a palette is used, it counts as 1 channel.*/
unsigned lodepng_get_channels(const LodePNGColorMode* info);
/*is it a greyscale type? (only colortype 0 or 4)*/
unsigned lodepng_is_greyscale_type(const LodePNGColorMode* info);
/*has it got an alpha channel? (only colortype 2 or 6)*/
unsigned lodepng_is_alpha_type(const LodePNGColorMode* info);
/*has it got a palette? (only colortype 3)*/
unsigned lodepng_is_palette_type(const LodePNGColorMode* info);
/*only returns true if there is a palette and there is a value in the palette with alpha < 255.
Loops through the palette to check this.*/
unsigned lodepng_has_palette_alpha(const LodePNGColorMode* info);
/*
Check if the given color info indicates the possibility of having non-opaque pixels in the PNG image.
Returns true if the image can have translucent or invisible pixels (it still be opaque if it doesn't use such pixels).
Returns false if the image can only have opaque pixels.
In detail, it returns true only if it's a color type with alpha, or has a palette with non-opaque values,
or if "key_defined" is true.
*/
unsigned lodepng_can_have_alpha(const LodePNGColorMode* info);
/*Returns the byte size of a raw image buffer with given width, height and color mode*/
size_t lodepng_get_raw_size(unsigned w, unsigned h, const LodePNGColorMode* color);

#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
/*The information of a Time chunk in PNG.*/
typedef struct LodePNGTime
{
  unsigned year;    /*2 bytes used (0-65535)*/
  unsigned month;   /*1-12*/
  unsigned day;     /*1-31*/
  unsigned hour;    /*0-23*/
  unsigned minute;  /*0-59*/
  unsigned second;  /*0-60 (to allow for leap seconds)*/
} LodePNGTime;
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/

/*Information about the PNG image, except pixels, width and height.*/
typedef struct LodePNGInfo
{
  /*header (IHDR), palette (PLTE) and transparency (tRNS) chunks*/
  unsigned compression_method;/*compression method of the original file. Always 0.*/
  unsigned filter_method;     /*filter method of the original file*/
  unsigned interlace_method;  /*interlace method of the original file*/
  LodePNGColorMode color;     /*color type and bits, palette and transparency of the PNG file*/

#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
  /*
  suggested background color chunk (bKGD)
  This color uses the same color mode as the PNG (except alpha channel), which can be 1-bit to 16-bit.

  For greyscale PNGs, r, g and b will all 3 be set to the same. When encoding
  the encoder writes the red one. For palette PNGs: When decoding, the RGB value
  will be stored, not a palette index. But when encoding, specify the index of
  the palette in background_r, the other two are then ignored.

  The decoder does not use this background color to edit the color of pixels.
  */
  unsigned background_defined; /*is a suggested background color given?*/
  unsigned background_r;       /*red component of suggested background color*/
  unsigned background_g;       /*green component of suggested background color*/
  unsigned background_b;       /*blue component of suggested background color*/

  /*
  non-international text chunks (tEXt and zTXt)

  The char** arrays each contain num strings. The actual messages are in
  text_strings, while text_keys are keywords that give a short description what
  the actual text represents, e.g. Title, Author, Description, or anything else.

  A keyword is minimum 1 character and maximum 79 characters long. It's
  discouraged to use a single line length longer than 79 characters for texts.

  Don't allocate these text buffers yourself. Use the init/cleanup functions
  correctly and use lodepng_add_text and lodepng_clear_text.
  */
  size_t text_num; /*the amount of texts in these char** buffers (there may be more texts in itext)*/
  char** text_keys; /*the keyword of a text chunk (e.g. "Comment")*/
  char** text_strings; /*the actual text*/

  /*
  international text chunks (iTXt)
  Similar to the non-international text chunks, but with additional strings
  "langtags" and "transkeys".
  */
  size_t itext_num; /*the amount of international texts in this PNG*/
  char** itext_keys; /*the English keyword of the text chunk (e.g. "Comment")*/
  char** itext_langtags; /*language tag for this text's language, ISO/IEC 646 string, e.g. ISO 639 language tag*/
  char** itext_transkeys; /*keyword translated to the international language - UTF-8 string*/
  char** itext_strings; /*the actual international text - UTF-8 string*/

  /*time chunk (tIME)*/
  unsigned time_defined; /*set to 1 to make the encoder generate a tIME chunk*/
  LodePNGTime time;

  /*phys chunk (pHYs)*/
  unsigned phys_defined; /*if 0, there is no pHYs chunk and the values below are undefined, if 1 else there is one*/
  unsigned phys_x; /*pixels per unit in x direction*/
  unsigned phys_y; /*pixels per unit in y direction*/
  unsigned phys_unit; /*may be 0 (unknown unit) or 1 (metre)*/

  /*
  unknown chunks
  There are 3 buffers, one for each position in the PNG where unknown chunks can appear
  each buffer contains all unknown chunks for that position consecutively
  The 3 buffers are the unknown chunks between certain critical chunks:
  0: IHDR-PLTE, 1: PLTE-IDAT, 2: IDAT-IEND
  Do not allocate or traverse this data yourself. Use the chunk traversing functions declared
  later, such as lodepng_chunk_next and lodepng_chunk_append, to read/write this struct.
  */
  unsigned char* unknown_chunks_data[3];
  size_t unknown_chunks_size[3]; /*size in bytes of the unknown chunks, given for protection*/
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
} LodePNGInfo;

/*init, cleanup and copy functions to use with this struct*/
void lodepng_info_init(LodePNGInfo* info);
void lodepng_info_cleanup(LodePNGInfo* info);
/*return value is error code (0 means no error)*/
unsigned lodepng_info_copy(LodePNGInfo* dest, const LodePNGInfo* source);

#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
void lodepng_clear_text(LodePNGInfo* info); /*use this to clear the texts again after you filled them in*/
unsigned lodepng_add_text(LodePNGInfo* info, const char* key, const char* str); /*push back both texts at once*/

void lodepng_clear_itext(LodePNGInfo* info); /*use this to clear the itexts again after you filled them in*/
unsigned lodepng_add_itext(LodePNGInfo* info, const char* key, const char* langtag,
                           const char* transkey, const char* str); /*push back the 4 texts of 1 chunk at once*/
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/

/*
Converts raw buffer from one color type to another color type, based on
LodePNGColorMode structs to describe the input and output color type.
See the reference manual at the end of this header file to see which color conversions are supported.
return value = LodePNG error code (0 if all went ok, an error if the conversion isn't supported)
The out buffer must have size (w * h * bpp + 7) / 8, where bpp is the bits per pixel
of the output color type (lodepng_get_bpp)
The fix_png value works as described in struct LodePNGDecoderSettings.
Note: for 16-bit per channel colors, uses big endian format like PNG does.
*/
unsigned lodepng_convert(unsigned char* out, const unsigned char* in,
                         LodePNGColorMode* mode_out, LodePNGColorMode* mode_in,
                         unsigned w, unsigned h, unsigned fix_png);


#ifdef LODEPNG_COMPILE_DECODER
/*
Settings for the decoder. This contains settings for the PNG and the Zlib
decoder, but not the Info settings from the Info structs.
*/
typedef struct LodePNGDecoderSettings
{
  LodePNGDecompressSettings zlibsettings; /*in here is the setting to ignore Adler32 checksums*/

  unsigned ignore_crc; /*ignore CRC checksums*/
  /*
  The fix_png setting, if 1, makes the decoder tolerant towards some PNG images
  that do not correctly follow the PNG specification. This only supports errors
  that are fixable, were found in images that are actually used on the web, and
  are silently tolerated by other decoders as well. Currently only one such fix
  is implemented: if a palette index is out of bounds given the palette size,
  interpret it as opaque black.
  By default this value is 0, which makes it stop with an error on such images.
  */
  unsigned fix_png;
  unsigned color_convert; /*whether to convert the PNG to the color type you want. Default: yes*/

#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
  unsigned read_text_chunks; /*if false but remember_unknown_chunks is true, they're stored in the unknown chunks*/
  /*store all bytes from unknown chunks in the LodePNGInfo (off by default, useful for a png editor)*/
  unsigned remember_unknown_chunks;
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
} LodePNGDecoderSettings;

void lodepng_decoder_settings_init(LodePNGDecoderSettings* settings);
#endif /*LODEPNG_COMPILE_DECODER*/

#ifdef LODEPNG_COMPILE_ENCODER
/*automatically use color type with less bits per pixel if losslessly possible. Default: AUTO*/
typedef enum LodePNGFilterStrategy
{
  /*every filter at zero*/
  LFS_ZERO,
  /*Use filter that gives minumum sum, as described in the official PNG filter heuristic.*/
  LFS_MINSUM,
  /*Use the filter type that gives smallest Shannon entropy for this scanline. Depending
  on the image, this is better or worse than minsum.*/
  LFS_ENTROPY,
  /*
  Brute-force-search PNG filters by compressing each filter for each scanline.
  Experimental, very slow, and only rarely gives better compression than MINSUM.
  */
  LFS_BRUTE_FORCE,
  /*use predefined_filters buffer: you specify the filter type for each scanline*/
  LFS_PREDEFINED
} LodePNGFilterStrategy;

/*automatically use color type with less bits per pixel if losslessly possible. Default: LAC_AUTO*/
typedef enum LodePNGAutoConvert
{
  LAC_NO, /*use color type user requested*/
  LAC_ALPHA, /*use color type user requested, but if only opaque pixels and RGBA or grey+alpha, use RGB or grey*/
  LAC_AUTO, /*use PNG color type that can losslessly represent the uncompressed image the smallest possible*/
  /*
  like AUTO, but do not choose 1, 2 or 4 bit per pixel types.
  sometimes a PNG image compresses worse if less than 8 bits per pixels.
  */
  LAC_AUTO_NO_NIBBLES,
  /*
  like AUTO, but never choose palette color type. For small images, encoding
  the palette may take more bytes than what is gained. Note that AUTO also
  already prevents encoding the palette for extremely small images, but that may
  not be sufficient because due to the compression it cannot predict when to
  switch.
  */
  LAC_AUTO_NO_PALETTE,
  LAC_AUTO_NO_NIBBLES_NO_PALETTE
} LodePNGAutoConvert;


/*Settings for the encoder.*/
typedef struct LodePNGEncoderSettings
{
  LodePNGCompressSettings zlibsettings; /*settings for the zlib encoder, such as window size, ...*/

  LodePNGAutoConvert auto_convert; /*how to automatically choose output PNG color type, if at all*/

  /*If true, follows the official PNG heuristic: if the PNG uses a palette or lower than
  8 bit depth, set all filters to zero. Otherwise use the filter_strategy. Note that to
  completely follow the official PNG heuristic, filter_palette_zero must be true and
  filter_strategy must be LFS_MINSUM*/
  unsigned filter_palette_zero;
  /*Which filter strategy to use when not using zeroes due to filter_palette_zero.
  Set filter_palette_zero to 0 to ensure always using your chosen strategy. Default: LFS_MINSUM*/
  LodePNGFilterStrategy filter_strategy;
  /*used if filter_strategy is LFS_PREDEFINED. In that case, this must point to a buffer with
  the same length as the amount of scanlines in the image, and each value must <= 5. You
  have to cleanup this buffer, LodePNG will never free it. Don't forget that filter_palette_zero
  must be set to 0 to ensure this is also used on palette or low bitdepth images.*/
  unsigned char* predefined_filters;

  /*force creating a PLTE chunk if colortype is 2 or 6 (= a suggested palette).
  If colortype is 3, PLTE is _always_ created.*/
  unsigned force_palette;
#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
  /*add LodePNG identifier and version as a text chunk, for debugging*/
  unsigned add_id;
  /*encode text chunks as zTXt chunks instead of tEXt chunks, and use compression in iTXt chunks*/
  unsigned text_compression;
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
} LodePNGEncoderSettings;

void lodepng_encoder_settings_init(LodePNGEncoderSettings* settings);
#endif /*LODEPNG_COMPILE_ENCODER*/


#if defined(LODEPNG_COMPILE_DECODER) || defined(LODEPNG_COMPILE_ENCODER)
/*The settings, state and information for extended encoding and decoding.*/
typedef struct LodePNGState
{
#ifdef LODEPNG_COMPILE_DECODER
  LodePNGDecoderSettings decoder; /*the decoding settings*/
#endif /*LODEPNG_COMPILE_DECODER*/
#ifdef LODEPNG_COMPILE_ENCODER
  LodePNGEncoderSettings encoder; /*the encoding settings*/
#endif /*LODEPNG_COMPILE_ENCODER*/
  LodePNGColorMode info_raw; /*specifies the format in which you would like to get the raw pixel buffer*/
  LodePNGInfo info_png; /*info of the PNG image obtained after decoding*/
  unsigned error;

} LodePNGState;

/*init, cleanup and copy functions to use with this struct*/
void lodepng_state_init(LodePNGState* state);
void lodepng_state_cleanup(LodePNGState* state);
void lodepng_state_copy(LodePNGState* dest, const LodePNGState* source);
#endif /* defined(LODEPNG_COMPILE_DECODER) || defined(LODEPNG_COMPILE_ENCODER) */

#ifdef LODEPNG_COMPILE_DECODER
/*
Same as lodepng_decode_memory, but uses a LodePNGState to allow custom settings and
getting much more information about the PNG image and color mode.
*/
unsigned lodepng_decode(unsigned char** out, unsigned* w, unsigned* h,
                        LodePNGState* state,
                        const unsigned char* in, size_t insize);

/*
Read the PNG header, but not the actual data. This returns only the information
that is in the header chunk of the PNG, such as width, height and color type. The
information is placed in the info_png field of the LodePNGState.
*/
unsigned lodepng_inspect(unsigned* w, unsigned* h,
                         LodePNGState* state,
                         const unsigned char* in, size_t insize);
#endif /*LODEPNG_COMPILE_DECODER*/


#ifdef LODEPNG_COMPILE_ENCODER
/*This function allocates the out buffer with standard malloc and stores the size in *outsize.*/
unsigned lodepng_encode(unsigned char** out, size_t* outsize,
                        const unsigned char* image, unsigned w, unsigned h,
                        LodePNGState* state);
#endif /*LODEPNG_COMPILE_ENCODER*/

/*
The lodepng_chunk functions are normally not needed, except to traverse the
unknown chunks stored in the LodePNGInfo struct, or add new ones to it.
It also allows traversing the chunks of an encoded PNG file yourself.

PNG standard chunk naming conventions:
First byte: uppercase = critical, lowercase = ancillary
Second byte: uppercase = public, lowercase = private
Third byte: must be uppercase
Fourth byte: uppercase = unsafe to copy, lowercase = safe to copy
*/

/*get the length of the data of the chunk. Total chunk length has 12 bytes more.*/
unsigned lodepng_chunk_length(const unsigned char* chunk);

/*puts the 4-byte type in null terminated string*/
void lodepng_chunk_type(char type[5], const unsigned char* chunk);

/*check if the type is the given type*/
unsigned char lodepng_chunk_type_equals(const unsigned char* chunk, const char* type);

/*0: it's one of the critical chunk types, 1: it's an ancillary chunk (see PNG standard)*/
unsigned char lodepng_chunk_ancillary(const unsigned char* chunk);

/*0: public, 1: private (see PNG standard)*/
unsigned char lodepng_chunk_private(const unsigned char* chunk);

/*0: the chunk is unsafe to copy, 1: the chunk is safe to copy (see PNG standard)*/
unsigned char lodepng_chunk_safetocopy(const unsigned char* chunk);

/*get pointer to the data of the chunk, where the input points to the header of the chunk*/
unsigned char* lodepng_chunk_data(unsigned char* chunk);
const unsigned char* lodepng_chunk_data_const(const unsigned char* chunk);

/*returns 0 if the crc is correct, 1 if it's incorrect (0 for OK as usual!)*/
unsigned lodepng_chunk_check_crc(const unsigned char* chunk);

/*generates the correct CRC from the data and puts it in the last 4 bytes of the chunk*/
void lodepng_chunk_generate_crc(unsigned char* chunk);

/*iterate to next chunks. don't use on IEND chunk, as there is no next chunk then*/
unsigned char* lodepng_chunk_next(unsigned char* chunk);
const unsigned char* lodepng_chunk_next_const(const unsigned char* chunk);

/*
Appends chunk to the data in out. The given chunk should already have its chunk header.
The out variable and outlength are updated to reflect the new reallocated buffer.
Returns error code (0 if it went ok)
*/
unsigned lodepng_chunk_append(unsigned char** out, size_t* outlength, const unsigned char* chunk);

/*
Appends new chunk to out. The chunk to append is given by giving its length, type
and data separately. The type is a 4-letter string.
The out variable and outlength are updated to reflect the new reallocated buffer.
Returne error code (0 if it went ok)
*/
unsigned lodepng_chunk_create(unsigned char** out, size_t* outlength, unsigned length,
                              const char* type, const unsigned char* data);


/*Calculate CRC32 of buffer*/
unsigned lodepng_crc32(const unsigned char* buf, size_t len);
#endif /*LODEPNG_COMPILE_PNG*/


#ifdef LODEPNG_COMPILE_ZLIB
/*
This zlib part can be used independently to zlib compress and decompress a
buffer. It cannot be used to create gzip files however, and it only supports the
part of zlib that is required for PNG, it does not support dictionaries.
*/

#ifdef LODEPNG_COMPILE_DECODER
/*Inflate a buffer. Inflate is the decompression step of deflate. Out buffer must be freed after use.*/
unsigned lodepng_inflate(unsigned char** out, size_t* outsize,
                         const unsigned char* in, size_t insize,
                         const LodePNGDecompressSettings* settings);

/*
Decompresses Zlib data. Reallocates the out buffer and appends the data. The
data must be according to the zlib specification.
Either, *out must be NULL and *outsize must be 0, or, *out must be a valid
buffer and *outsize its size in bytes. out must be freed by user after usage.
*/
unsigned lodepng_zlib_decompress(unsigned char** out, size_t* outsize,
                                 const unsigned char* in, size_t insize,
                                 const LodePNGDecompressSettings* settings);
#endif /*LODEPNG_COMPILE_DECODER*/

#ifdef LODEPNG_COMPILE_ENCODER
/*
Compresses data with Zlib. Reallocates the out buffer and appends the data.
Zlib adds a small header and trailer around the deflate data.
The data is output in the format of the zlib specification.
Either, *out must be NULL and *outsize must be 0, or, *out must be a valid
buffer and *outsize its size in bytes. out must be freed by user after usage.
*/
unsigned lodepng_zlib_compress(unsigned char** out, size_t* outsize,
                               const unsigned char* in, size_t insize,
                               const LodePNGCompressSettings* settings);

/*
Find length-limited Huffman code for given frequencies. This function is in the
public interface only for tests, it's used internally by lodepng_deflate.
*/
unsigned lodepng_huffman_code_lengths(unsigned* lengths, const unsigned* frequencies,
                                      size_t numcodes, unsigned maxbitlen);

/*Compress a buffer with deflate. See RFC 1951. Out buffer must be freed after use.*/
unsigned lodepng_deflate(unsigned char** out, size_t* outsize,
                         const unsigned char* in, size_t insize,
                         const LodePNGCompressSettings* settings);

#endif /*LODEPNG_COMPILE_ENCODER*/
#endif /*LODEPNG_COMPILE_ZLIB*/

#ifdef LODEPNG_COMPILE_DISK
/*
Load a file from disk into buffer. The function allocates the out buffer, and
after usage you should free it.
out: output parameter, contains pointer to loaded buffer.
outsize: output parameter, size of the allocated out buffer
filename: the path to the file to load
return value: error code (0 means ok)
*/
unsigned lodepng_load_file(unsigned char** out, size_t* outsize, const char* filename);

/*
Save a file from buffer to disk. Warning, if it exists, this function overwrites
the file without warning!
buffer: the buffer to write
buffersize: size of the buffer to write
filename: the path to the file to save to
return value: error code (0 means ok)
*/
unsigned lodepng_save_file(const unsigned char* buffer, size_t buffersize, const char* filename);
#endif /*LODEPNG_COMPILE_DISK*/


/*
TODO:
[.] test if there are no memory leaks or security exploits - done a lot but needs to be checked often
[.] check compatibility with vareous compilers  - done but needs to be redone for every newer version
[X] converting color to 16-bit per channel types
[ ] read all public PNG chunk types (but never let the color profile and gamma ones touch RGB values)
[ ] make sure encoder generates no chunks with size > (2^31)-1
[ ] partial decoding (stream processing)
[X] let the "isFullyOpaque" function check color keys and transparent palettes too
[X] better name for the variables "codes", "codesD", "codelengthcodes", "clcl" and "lldl"
[ ] don't stop decoding on errors like 69, 57, 58 (make warnings)
[ ] make option to choose if the raw image with non multiple of 8 bits per scanline should have padding bits or not
[ ] let the C++ wrapper catch exceptions coming from the standard library and return LodePNG error codes
*/

#endif /*LODEPNG_H inclusion guard*/

/*
LodePNG version 20130831

Copyright (c) 2005-2013 Lode Vandevenne

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

    3. This notice may not be removed or altered from any source
    distribution.
*/

/*
The manual and changelog are in the header file "lodepng.h"
Rename this file to lodepng.cpp to use it for C++, or to lodepng.c to use it for C.
*/



#define VERSION_STRING "20130831"

/*
This source file is built up in the following large parts. The code sections
with the "LODEPNG_COMPILE_" #defines divide this up further in an intermixed way.
-Tools for C and common code for PNG and Zlib
-C Code for Zlib (huffman, deflate, ...)
-C Code for PNG (file format chunks, adam7, PNG filters, color conversions, ...)
-The C++ wrapper around all of the above
*/

/*The malloc, realloc and free functions defined here with "lodepng_" in front
of the name, so that you can easily change them to others related to your
platform if needed. Everything else in the code calls these. Pass
-DLODEPNG_NO_COMPILE_ALLOCATORS to the compiler, or comment out
#define LODEPNG_COMPILE_ALLOCATORS in the header, to disable the ones here and
define them in your own project's source files without needing to change
lodepng source code. Don't forget to remove "static" if you copypaste them
from here.*/

#ifdef LODEPNG_COMPILE_ALLOCATORS
static void* lodepng_malloc(size_t size)
{
  return malloc(size);
}

static void* lodepng_realloc(void* ptr, size_t new_size)
{
  return realloc(ptr, new_size);
}

static void lodepng_free(void* ptr)
{
  free(ptr);
}
#else /*LODEPNG_COMPILE_ALLOCATORS*/
void* lodepng_malloc(size_t size);
void* lodepng_realloc(void* ptr, size_t new_size);
void lodepng_free(void* ptr);
#endif /*LODEPNG_COMPILE_ALLOCATORS*/

/* ////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */
/* // Tools for C, and common code for PNG and Zlib.                       // */
/* ////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */

/*
Often in case of an error a value is assigned to a variable and then it breaks
out of a loop (to go to the cleanup phase of a function). This macro does that.
It makes the error handling code shorter and more readable.

Example: if(!uivector_resizev(&frequencies_ll, 286, 0)) ERROR_BREAK(83);
*/
#define CERROR_BREAK(errorvar, code)\
{\
  errorvar = code;\
  break;\
}

/*version of CERROR_BREAK that assumes the common case where the error variable is named "error"*/
#define ERROR_BREAK(code) CERROR_BREAK(error, code)

/*Set error var to the error code, and return it.*/
#define CERROR_RETURN_ERROR(errorvar, code)\
{\
  errorvar = code;\
  return code;\
}

/*Try the code, if it returns error, also return the error.*/
#define CERROR_TRY_RETURN(call)\
{\
  unsigned error = call;\
  if(error) return error;\
}

/*
About uivector, ucvector and string:
-All of them wrap dynamic arrays or text strings in a similar way.
-LodePNG was originally written in C++. The vectors replace the std::vectors that were used in the C++ version.
-The string tools are made to avoid problems with compilers that declare things like strncat as deprecated.
-They're not used in the interface, only internally in this file as static functions.
-As with many other structs in this file, the init and cleanup functions serve as ctor and dtor.
*/

#ifdef LODEPNG_COMPILE_ZLIB
/*dynamic vector of unsigned ints*/
typedef struct uivector
{
  unsigned* data;
  size_t size; /*size in number of unsigned longs*/
  size_t allocsize; /*allocated size in bytes*/
} uivector;

static void uivector_cleanup(void* p)
{
  ((uivector*)p)->size = ((uivector*)p)->allocsize = 0;
  lodepng_free(((uivector*)p)->data);
  ((uivector*)p)->data = NULL;
}

/*returns 1 if success, 0 if failure ==> nothing done*/
static unsigned uivector_resize(uivector* p, size_t size)
{
  if(size * sizeof(unsigned) > p->allocsize)
  {
    size_t newsize = size * sizeof(unsigned) * 2;
    void* data = lodepng_realloc(p->data, newsize);
    if(data)
    {
      p->allocsize = newsize;
      p->data = (unsigned*)data;
      p->size = size;
    }
    else return 0;
  }
  else p->size = size;
  return 1;
}

/*resize and give all new elements the value*/
static unsigned uivector_resizev(uivector* p, size_t size, unsigned value)
{
  size_t oldsize = p->size, i;
  if(!uivector_resize(p, size)) return 0;
  for(i = oldsize; i < size; i++) p->data[i] = value;
  return 1;
}

static void uivector_init(uivector* p)
{
  p->data = NULL;
  p->size = p->allocsize = 0;
}

#ifdef LODEPNG_COMPILE_ENCODER
/*returns 1 if success, 0 if failure ==> nothing done*/
static unsigned uivector_push_back(uivector* p, unsigned c)
{
  if(!uivector_resize(p, p->size + 1)) return 0;
  p->data[p->size - 1] = c;
  return 1;
}

/*copy q to p, returns 1 if success, 0 if failure ==> nothing done*/
static unsigned uivector_copy(uivector* p, const uivector* q)
{
  size_t i;
  if(!uivector_resize(p, q->size)) return 0;
  for(i = 0; i < q->size; i++) p->data[i] = q->data[i];
  return 1;
}

static void uivector_swap(uivector* p, uivector* q)
{
  size_t tmp;
  unsigned* tmpp;
  tmp = p->size; p->size = q->size; q->size = tmp;
  tmp = p->allocsize; p->allocsize = q->allocsize; q->allocsize = tmp;
  tmpp = p->data; p->data = q->data; q->data = tmpp;
}
#endif /*LODEPNG_COMPILE_ENCODER*/
#endif /*LODEPNG_COMPILE_ZLIB*/

/* /////////////////////////////////////////////////////////////////////////// */

/*dynamic vector of unsigned chars*/
typedef struct ucvector
{
  unsigned char* data;
  size_t size; /*used size*/
  size_t allocsize; /*allocated size*/
} ucvector;

/*returns 1 if success, 0 if failure ==> nothing done*/
static unsigned ucvector_resize(ucvector* p, size_t size)
{
  if(size * sizeof(unsigned char) > p->allocsize)
  {
    size_t newsize = size * sizeof(unsigned char) * 2;
    void* data = lodepng_realloc(p->data, newsize);
    if(data)
    {
      p->allocsize = newsize;
      p->data = (unsigned char*)data;
      p->size = size;
    }
    else return 0; /*error: not enough memory*/
  }
  else p->size = size;
  return 1;
}

#ifdef LODEPNG_COMPILE_PNG

static void ucvector_cleanup(void* p)
{
  ((ucvector*)p)->size = ((ucvector*)p)->allocsize = 0;
  lodepng_free(((ucvector*)p)->data);
  ((ucvector*)p)->data = NULL;
}

static void ucvector_init(ucvector* p)
{
  p->data = NULL;
  p->size = p->allocsize = 0;
}

#ifdef LODEPNG_COMPILE_DECODER
/*resize and give all new elements the value*/
static unsigned ucvector_resizev(ucvector* p, size_t size, unsigned char value)
{
  size_t oldsize = p->size, i;
  if(!ucvector_resize(p, size)) return 0;
  for(i = oldsize; i < size; i++) p->data[i] = value;
  return 1;
}
#endif /*LODEPNG_COMPILE_DECODER*/
#endif /*LODEPNG_COMPILE_PNG*/

#ifdef LODEPNG_COMPILE_ZLIB
/*you can both convert from vector to buffer&size and vica versa. If you use
init_buffer to take over a buffer and size, it is not needed to use cleanup*/
static void ucvector_init_buffer(ucvector* p, unsigned char* buffer, size_t size)
{
  p->data = buffer;
  p->allocsize = p->size = size;
}
#endif /*LODEPNG_COMPILE_ZLIB*/

#if (defined(LODEPNG_COMPILE_PNG) && defined(LODEPNG_COMPILE_ANCILLARY_CHUNKS)) || defined(LODEPNG_COMPILE_ENCODER)
/*returns 1 if success, 0 if failure ==> nothing done*/
static unsigned ucvector_push_back(ucvector* p, unsigned char c)
{
  if(!ucvector_resize(p, p->size + 1)) return 0;
  p->data[p->size - 1] = c;
  return 1;
}
#endif /*defined(LODEPNG_COMPILE_PNG) || defined(LODEPNG_COMPILE_ENCODER)*/


/* ////////////////////////////////////////////////////////////////////////// */

#ifdef LODEPNG_COMPILE_PNG
#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
/*returns 1 if success, 0 if failure ==> nothing done*/
static unsigned string_resize(char** out, size_t size)
{
  char* data = (char*)lodepng_realloc(*out, size + 1);
  if(data)
  {
    data[size] = 0; /*null termination char*/
    *out = data;
  }
  return data != 0;
}

/*init a {char*, size_t} pair for use as string*/
static void string_init(char** out)
{
  *out = NULL;
  string_resize(out, 0);
}

/*free the above pair again*/
static void string_cleanup(char** out)
{
  lodepng_free(*out);
  *out = NULL;
}

static void string_set(char** out, const char* in)
{
  size_t insize = strlen(in), i = 0;
  if(string_resize(out, insize))
  {
    for(i = 0; i < insize; i++)
    {
      (*out)[i] = in[i];
    }
  }
}
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
#endif /*LODEPNG_COMPILE_PNG*/

/* ////////////////////////////////////////////////////////////////////////// */

unsigned lodepng_read32bitInt(const unsigned char* buffer)
{
  return (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
}

#if defined(LODEPNG_COMPILE_PNG) || defined(LODEPNG_COMPILE_ENCODER)
/*buffer must have at least 4 allocated bytes available*/
static void lodepng_set32bitInt(unsigned char* buffer, unsigned value)
{
  buffer[0] = (unsigned char)((value >> 24) & 0xff);
  buffer[1] = (unsigned char)((value >> 16) & 0xff);
  buffer[2] = (unsigned char)((value >>  8) & 0xff);
  buffer[3] = (unsigned char)((value      ) & 0xff);
}
#endif /*defined(LODEPNG_COMPILE_PNG) || defined(LODEPNG_COMPILE_ENCODER)*/

#ifdef LODEPNG_COMPILE_ENCODER
static void lodepng_add32bitInt(ucvector* buffer, unsigned value)
{
  ucvector_resize(buffer, buffer->size + 4); /*todo: give error if resize failed*/
  lodepng_set32bitInt(&buffer->data[buffer->size - 4], value);
}
#endif /*LODEPNG_COMPILE_ENCODER*/

/* ////////////////////////////////////////////////////////////////////////// */
/* / File IO                                                                / */
/* ////////////////////////////////////////////////////////////////////////// */

#ifdef LODEPNG_COMPILE_DISK

unsigned lodepng_load_file(unsigned char** out, size_t* outsize, const char* filename)
{
  FILE* file;
  long size;

  /*provide some proper output values if error will happen*/
  *out = 0;
  *outsize = 0;

  file = fopen(filename, "rb");
  if(!file) return 78;

  /*get filesize:*/
  fseek(file , 0 , SEEK_END);
  size = ftell(file);
  rewind(file);

  /*read contents of the file into the vector*/
  *outsize = 0;
  *out = (unsigned char*)lodepng_malloc((size_t)size);
  if(size && (*out)) (*outsize) = fread(*out, 1, (size_t)size, file);

  fclose(file);
  if(!(*out) && size) return 83; /*the above malloc failed*/
  return 0;
}

/*write given buffer to the file, overwriting the file, it doesn't append to it.*/
unsigned lodepng_save_file(const unsigned char* buffer, size_t buffersize, const char* filename)
{
  FILE* file;
  file = fopen(filename, "wb" );
  if(!file) return 79;
  fwrite((char*)buffer , 1 , buffersize, file);
  fclose(file);
  return 0;
}

#endif /*LODEPNG_COMPILE_DISK*/

/* ////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */
/* // End of common code and tools. Begin of Zlib related code.            // */
/* ////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */

#ifdef LODEPNG_COMPILE_ZLIB
#ifdef LODEPNG_COMPILE_ENCODER
/*TODO: this ignores potential out of memory errors*/
static void addBitToStream(size_t* bitpointer, ucvector* bitstream, unsigned char bit)
{
  /*add a new byte at the end*/
  if((*bitpointer) % 8 == 0) ucvector_push_back(bitstream, (unsigned char)0);
  /*earlier bit of huffman code is in a lesser significant bit of an earlier byte*/
  (bitstream->data[bitstream->size - 1]) |= (bit << ((*bitpointer) & 0x7));
  (*bitpointer)++;
}

static void addBitsToStream(size_t* bitpointer, ucvector* bitstream, unsigned value, size_t nbits)
{
  size_t i;
  for(i = 0; i < nbits; i++) addBitToStream(bitpointer, bitstream, (unsigned char)((value >> i) & 1));
}

static void addBitsToStreamReversed(size_t* bitpointer, ucvector* bitstream, unsigned value, size_t nbits)
{
  size_t i;
  for(i = 0; i < nbits; i++) addBitToStream(bitpointer, bitstream, (unsigned char)((value >> (nbits - 1 - i)) & 1));
}
#endif /*LODEPNG_COMPILE_ENCODER*/

#ifdef LODEPNG_COMPILE_DECODER

#define READBIT(bitpointer, bitstream) ((bitstream[bitpointer >> 3] >> (bitpointer & 0x7)) & (unsigned char)1)

static unsigned char readBitFromStream(size_t* bitpointer, const unsigned char* bitstream)
{
  unsigned char result = (unsigned char)(READBIT(*bitpointer, bitstream));
  (*bitpointer)++;
  return result;
}

static unsigned readBitsFromStream(size_t* bitpointer, const unsigned char* bitstream, size_t nbits)
{
  unsigned result = 0, i;
  for(i = 0; i < nbits; i++)
  {
    result += ((unsigned)READBIT(*bitpointer, bitstream)) << i;
    (*bitpointer)++;
  }
  return result;
}
#endif /*LODEPNG_COMPILE_DECODER*/

/* ////////////////////////////////////////////////////////////////////////// */
/* / Deflate - Huffman                                                      / */
/* ////////////////////////////////////////////////////////////////////////// */

#define FIRST_LENGTH_CODE_INDEX 257
#define LAST_LENGTH_CODE_INDEX 285
/*256 literals, the end code, some length codes, and 2 unused codes*/
#define NUM_DEFLATE_CODE_SYMBOLS 288
/*the distance codes have their own symbols, 30 used, 2 unused*/
#define NUM_DISTANCE_SYMBOLS 32
/*the code length codes. 0-15: code lengths, 16: copy previous 3-6 times, 17: 3-10 zeros, 18: 11-138 zeros*/
#define NUM_CODE_LENGTH_CODES 19

/*the base lengths represented by codes 257-285*/
static const unsigned LENGTHBASE[29]
  = {3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59,
     67, 83, 99, 115, 131, 163, 195, 227, 258};

/*the extra bits used by codes 257-285 (added to base length)*/
static const unsigned LENGTHEXTRA[29]
  = {0, 0, 0, 0, 0, 0, 0,  0,  1,  1,  1,  1,  2,  2,  2,  2,  3,  3,  3,  3,
      4,  4,  4,   4,   5,   5,   5,   5,   0};

/*the base backwards distances (the bits of distance codes appear after length codes and use their own huffman tree)*/
static const unsigned DISTANCEBASE[30]
  = {1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513,
     769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577};

/*the extra bits of backwards distances (added to base)*/
static const unsigned DISTANCEEXTRA[30]
  = {0, 0, 0, 0, 1, 1, 2,  2,  3,  3,  4,  4,  5,  5,   6,   6,   7,   7,   8,
       8,    9,    9,   10,   10,   11,   11,   12,    12,    13,    13};

/*the order in which "code length alphabet code lengths" are stored, out of this
the huffman tree of the dynamic huffman tree lengths is generated*/
static const unsigned CLCL_ORDER[NUM_CODE_LENGTH_CODES]
  = {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};

/* ////////////////////////////////////////////////////////////////////////// */

/*
Huffman tree struct, containing multiple representations of the tree
*/
typedef struct HuffmanTree
{
  unsigned* tree2d;
  unsigned* tree1d;
  unsigned* lengths; /*the lengths of the codes of the 1d-tree*/
  unsigned maxbitlen; /*maximum number of bits a single code can get*/
  unsigned numcodes; /*number of symbols in the alphabet = number of codes*/
} HuffmanTree;

/*function used for debug purposes to draw the tree in ascii art with C++*/
/*
static void HuffmanTree_draw(HuffmanTree* tree)
{
  std::cout << "tree. length: " << tree->numcodes << " maxbitlen: " << tree->maxbitlen << std::endl;
  for(size_t i = 0; i < tree->tree1d.size; i++)
  {
    if(tree->lengths.data[i])
      std::cout << i << " " << tree->tree1d.data[i] << " " << tree->lengths.data[i] << std::endl;
  }
  std::cout << std::endl;
}*/

static void HuffmanTree_init(HuffmanTree* tree)
{
  tree->tree2d = 0;
  tree->tree1d = 0;
  tree->lengths = 0;
}

static void HuffmanTree_cleanup(HuffmanTree* tree)
{
  lodepng_free(tree->tree2d);
  lodepng_free(tree->tree1d);
  lodepng_free(tree->lengths);
}

/*the tree representation used by the decoder. return value is error*/
static unsigned HuffmanTree_make2DTree(HuffmanTree* tree)
{
  unsigned nodefilled = 0; /*up to which node it is filled*/
  unsigned treepos = 0; /*position in the tree (1 of the numcodes columns)*/
  unsigned n, i;

  tree->tree2d = (unsigned*)lodepng_malloc(tree->numcodes * 2 * sizeof(unsigned));
  if(!tree->tree2d) return 83; /*alloc fail*/

  /*
  convert tree1d[] to tree2d[][]. In the 2D array, a value of 32767 means
  uninited, a value >= numcodes is an address to another bit, a value < numcodes
  is a code. The 2 rows are the 2 possible bit values (0 or 1), there are as
  many columns as codes - 1.
  A good huffmann tree has N * 2 - 1 nodes, of which N - 1 are internal nodes.
  Here, the internal nodes are stored (what their 0 and 1 option point to).
  There is only memory for such good tree currently, if there are more nodes
  (due to too long length codes), error 55 will happen
  */
  for(n = 0; n < tree->numcodes * 2; n++)
  {
    tree->tree2d[n] = 32767; /*32767 here means the tree2d isn't filled there yet*/
  }

  for(n = 0; n < tree->numcodes; n++) /*the codes*/
  {
    for(i = 0; i < tree->lengths[n]; i++) /*the bits for this code*/
    {
      unsigned char bit = (unsigned char)((tree->tree1d[n] >> (tree->lengths[n] - i - 1)) & 1);
      if(treepos > tree->numcodes - 2) return 55; /*oversubscribed, see comment in lodepng_error_text*/
      if(tree->tree2d[2 * treepos + bit] == 32767) /*not yet filled in*/
      {
        if(i + 1 == tree->lengths[n]) /*last bit*/
        {
          tree->tree2d[2 * treepos + bit] = n; /*put the current code in it*/
          treepos = 0;
        }
        else
        {
          /*put address of the next step in here, first that address has to be found of course
          (it's just nodefilled + 1)...*/
          nodefilled++;
          /*addresses encoded with numcodes added to it*/
          tree->tree2d[2 * treepos + bit] = nodefilled + tree->numcodes;
          treepos = nodefilled;
        }
      }
      else treepos = tree->tree2d[2 * treepos + bit] - tree->numcodes;
    }
  }

  for(n = 0;  n < tree->numcodes * 2; n++)
  {
    if(tree->tree2d[n] == 32767) tree->tree2d[n] = 0; /*remove possible remaining 32767's*/
  }

  return 0;
}

/*
Second step for the ...makeFromLengths and ...makeFromFrequencies functions.
numcodes, lengths and maxbitlen must already be filled in correctly. return
value is error.
*/
static unsigned HuffmanTree_makeFromLengths2(HuffmanTree* tree)
{
  uivector blcount;
  uivector nextcode;
  unsigned bits, n, error = 0;

  uivector_init(&blcount);
  uivector_init(&nextcode);

  tree->tree1d = (unsigned*)lodepng_malloc(tree->numcodes * sizeof(unsigned));
  if(!tree->tree1d) error = 83; /*alloc fail*/

  if(!uivector_resizev(&blcount, tree->maxbitlen + 1, 0)
  || !uivector_resizev(&nextcode, tree->maxbitlen + 1, 0))
    error = 83; /*alloc fail*/

  if(!error)
  {
    /*step 1: count number of instances of each code length*/
    for(bits = 0; bits < tree->numcodes; bits++) blcount.data[tree->lengths[bits]]++;
    /*step 2: generate the nextcode values*/
    for(bits = 1; bits <= tree->maxbitlen; bits++)
    {
      nextcode.data[bits] = (nextcode.data[bits - 1] + blcount.data[bits - 1]) << 1;
    }
    /*step 3: generate all the codes*/
    for(n = 0; n < tree->numcodes; n++)
    {
      if(tree->lengths[n] != 0) tree->tree1d[n] = nextcode.data[tree->lengths[n]]++;
    }
  }

  uivector_cleanup(&blcount);
  uivector_cleanup(&nextcode);

  if(!error) return HuffmanTree_make2DTree(tree);
  else return error;
}

/*
given the code lengths (as stored in the PNG file), generate the tree as defined
by Deflate. maxbitlen is the maximum bits that a code in the tree can have.
return value is error.
*/
static unsigned HuffmanTree_makeFromLengths(HuffmanTree* tree, const unsigned* bitlen,
                                            size_t numcodes, unsigned maxbitlen)
{
  unsigned i;
  tree->lengths = (unsigned*)lodepng_malloc(numcodes * sizeof(unsigned));
  if(!tree->lengths) return 83; /*alloc fail*/
  for(i = 0; i < numcodes; i++) tree->lengths[i] = bitlen[i];
  tree->numcodes = (unsigned)numcodes; /*number of symbols*/
  tree->maxbitlen = maxbitlen;
  return HuffmanTree_makeFromLengths2(tree);
}

#ifdef LODEPNG_COMPILE_ENCODER

/*
A coin, this is the terminology used for the package-merge algorithm and the
coin collector's problem. This is used to generate the huffman tree.
A coin can be multiple coins (when they're merged)
*/
typedef struct Coin
{
  uivector symbols;
  float weight; /*the sum of all weights in this coin*/
} Coin;

static void coin_init(Coin* c)
{
  uivector_init(&c->symbols);
}

/*argument c is void* so that this dtor can be given as function pointer to the vector resize function*/
static void coin_cleanup(void* c)
{
  uivector_cleanup(&((Coin*)c)->symbols);
}

static void coin_copy(Coin* c1, const Coin* c2)
{
  c1->weight = c2->weight;
  uivector_copy(&c1->symbols, &c2->symbols);
}

static void add_coins(Coin* c1, const Coin* c2)
{
  size_t i;
  for(i = 0; i < c2->symbols.size; i++) uivector_push_back(&c1->symbols, c2->symbols.data[i]);
  c1->weight += c2->weight;
}

static void init_coins(Coin* coins, size_t num)
{
  size_t i;
  for(i = 0; i < num; i++) coin_init(&coins[i]);
}

static void cleanup_coins(Coin* coins, size_t num)
{
  size_t i;
  for(i = 0; i < num; i++) coin_cleanup(&coins[i]);
}

/*
This uses a simple combsort to sort the data. This function is not critical for
overall encoding speed and the data amount isn't that large.
*/
static void sort_coins(Coin* data, size_t amount)
{
  size_t gap = amount;
  unsigned char swapped = 0;
  while((gap > 1) || swapped)
  {
    size_t i;
    gap = (gap * 10) / 13; /*shrink factor 1.3*/
    if(gap == 9 || gap == 10) gap = 11; /*combsort11*/
    if(gap < 1) gap = 1;
    swapped = 0;
    for(i = 0; i < amount - gap; i++)
    {
      size_t j = i + gap;
      if(data[j].weight < data[i].weight)
      {
        float temp = data[j].weight; data[j].weight = data[i].weight; data[i].weight = temp;
        uivector_swap(&data[i].symbols, &data[j].symbols);
        swapped = 1;
      }
    }
  }
}

static unsigned append_symbol_coins(Coin* coins, const unsigned* frequencies, unsigned numcodes, size_t sum)
{
  unsigned i;
  unsigned j = 0; /*index of present symbols*/
  for(i = 0; i < numcodes; i++)
  {
    if(frequencies[i] != 0) /*only include symbols that are present*/
    {
      coins[j].weight = frequencies[i] / (float)sum;
      uivector_push_back(&coins[j].symbols, i);
      j++;
    }
  }
  return 0;
}

unsigned lodepng_huffman_code_lengths(unsigned* lengths, const unsigned* frequencies,
                                      size_t numcodes, unsigned maxbitlen)
{
  unsigned i, j;
  size_t sum = 0, numpresent = 0;
  unsigned error = 0;
  Coin* coins; /*the coins of the currently calculated row*/
  Coin* prev_row; /*the previous row of coins*/
  unsigned numcoins;
  unsigned coinmem;

  if(numcodes == 0) return 80; /*error: a tree of 0 symbols is not supposed to be made*/

  for(i = 0; i < numcodes; i++)
  {
    if(frequencies[i] > 0)
    {
      numpresent++;
      sum += frequencies[i];
    }
  }

  for(i = 0; i < numcodes; i++) lengths[i] = 0;

  /*ensure at least two present symbols. There should be at least one symbol
  according to RFC 1951 section 3.2.7. To decoders incorrectly require two. To
  make these work as well ensure there are at least two symbols. The
  Package-Merge code below also doesn't work correctly if there's only one
  symbol, it'd give it the theoritical 0 bits but in practice zlib wants 1 bit*/
  if(numpresent == 0)
  {
    lengths[0] = lengths[1] = 1; /*note that for RFC 1951 section 3.2.7, only lengths[0] = 1 is needed*/
  }
  else if(numpresent == 1)
  {
    for(i = 0; i < numcodes; i++)
    {
      if(frequencies[i])
      {
        lengths[i] = 1;
        lengths[i == 0 ? 1 : 0] = 1;
        break;
      }
    }
  }
  else
  {
    /*Package-Merge algorithm represented by coin collector's problem
    For every symbol, maxbitlen coins will be created*/

    coinmem = numpresent * 2; /*max amount of coins needed with the current algo*/
    coins = (Coin*)lodepng_malloc(sizeof(Coin) * coinmem);
    prev_row = (Coin*)lodepng_malloc(sizeof(Coin) * coinmem);
    if(!coins || !prev_row)
    {
      lodepng_free(coins);
      lodepng_free(prev_row);
      return 83; /*alloc fail*/
    }
    init_coins(coins, coinmem);
    init_coins(prev_row, coinmem);

    /*first row, lowest denominator*/
    error = append_symbol_coins(coins, frequencies, numcodes, sum);
    numcoins = numpresent;
    sort_coins(coins, numcoins);
    if(!error)
    {
      unsigned numprev = 0;
      for(j = 1; j <= maxbitlen && !error; j++) /*each of the remaining rows*/
      {
        unsigned tempnum;
        Coin* tempcoins;
        /*swap prev_row and coins, and their amounts*/
        tempcoins = prev_row; prev_row = coins; coins = tempcoins;
        tempnum = numprev; numprev = numcoins; numcoins = tempnum;

        cleanup_coins(coins, numcoins);
        init_coins(coins, numcoins);

        numcoins = 0;

        /*fill in the merged coins of the previous row*/
        for(i = 0; i + 1 < numprev; i += 2)
        {
          /*merge prev_row[i] and prev_row[i + 1] into new coin*/
          Coin* coin = &coins[numcoins++];
          coin_copy(coin, &prev_row[i]);
          add_coins(coin, &prev_row[i + 1]);
        }
        /*fill in all the original symbols again*/
        if(j < maxbitlen)
        {
          error = append_symbol_coins(coins + numcoins, frequencies, numcodes, sum);
          numcoins += numpresent;
        }
        sort_coins(coins, numcoins);
      }
    }

    if(!error)
    {
      /*calculate the lenghts of each symbol, as the amount of times a coin of each symbol is used*/
      for(i = 0; i < numpresent - 1; i++)
      {
        Coin* coin = &coins[i];
        for(j = 0; j < coin->symbols.size; j++) lengths[coin->symbols.data[j]]++;
      }
    }

    cleanup_coins(coins, coinmem);
    lodepng_free(coins);
    cleanup_coins(prev_row, coinmem);
    lodepng_free(prev_row);
  }

  return error;
}

/*Create the Huffman tree given the symbol frequencies*/
static unsigned HuffmanTree_makeFromFrequencies(HuffmanTree* tree, const unsigned* frequencies,
                                                size_t mincodes, size_t numcodes, unsigned maxbitlen)
{
  unsigned error = 0;
  while(!frequencies[numcodes - 1] && numcodes > mincodes) numcodes--; /*trim zeroes*/
  tree->maxbitlen = maxbitlen;
  tree->numcodes = (unsigned)numcodes; /*number of symbols*/
  tree->lengths = (unsigned*)lodepng_realloc(tree->lengths, numcodes * sizeof(unsigned));
  if(!tree->lengths) return 83; /*alloc fail*/
  /*initialize all lengths to 0*/
  memset(tree->lengths, 0, numcodes * sizeof(unsigned));

  error = lodepng_huffman_code_lengths(tree->lengths, frequencies, numcodes, maxbitlen);
  if(!error) error = HuffmanTree_makeFromLengths2(tree);
  return error;
}

static unsigned HuffmanTree_getCode(const HuffmanTree* tree, unsigned index)
{
  return tree->tree1d[index];
}

static unsigned HuffmanTree_getLength(const HuffmanTree* tree, unsigned index)
{
  return tree->lengths[index];
}
#endif /*LODEPNG_COMPILE_ENCODER*/

/*get the literal and length code tree of a deflated block with fixed tree, as per the deflate specification*/
static unsigned generateFixedLitLenTree(HuffmanTree* tree)
{
  unsigned i, error = 0;
  unsigned* bitlen = (unsigned*)lodepng_malloc(NUM_DEFLATE_CODE_SYMBOLS * sizeof(unsigned));
  if(!bitlen) return 83; /*alloc fail*/

  /*288 possible codes: 0-255=literals, 256=endcode, 257-285=lengthcodes, 286-287=unused*/
  for(i =   0; i <= 143; i++) bitlen[i] = 8;
  for(i = 144; i <= 255; i++) bitlen[i] = 9;
  for(i = 256; i <= 279; i++) bitlen[i] = 7;
  for(i = 280; i <= 287; i++) bitlen[i] = 8;

  error = HuffmanTree_makeFromLengths(tree, bitlen, NUM_DEFLATE_CODE_SYMBOLS, 15);

  lodepng_free(bitlen);
  return error;
}

/*get the distance code tree of a deflated block with fixed tree, as specified in the deflate specification*/
static unsigned generateFixedDistanceTree(HuffmanTree* tree)
{
  unsigned i, error = 0;
  unsigned* bitlen = (unsigned*)lodepng_malloc(NUM_DISTANCE_SYMBOLS * sizeof(unsigned));
  if(!bitlen) return 83; /*alloc fail*/

  /*there are 32 distance codes, but 30-31 are unused*/
  for(i = 0; i < NUM_DISTANCE_SYMBOLS; i++) bitlen[i] = 5;
  error = HuffmanTree_makeFromLengths(tree, bitlen, NUM_DISTANCE_SYMBOLS, 15);

  lodepng_free(bitlen);
  return error;
}

#ifdef LODEPNG_COMPILE_DECODER

/*
returns the code, or (unsigned)(-1) if error happened
inbitlength is the length of the complete buffer, in bits (so its byte length times 8)
*/
static unsigned huffmanDecodeSymbol(const unsigned char* in, size_t* bp,
                                    const HuffmanTree* codetree, size_t inbitlength)
{
  unsigned treepos = 0, ct;
  for(;;)
  {
    if(*bp >= inbitlength) return (unsigned)(-1); /*error: end of input memory reached without endcode*/
    /*
    decode the symbol from the tree. The "readBitFromStream" code is inlined in
    the expression below because this is the biggest bottleneck while decoding
    */
    ct = codetree->tree2d[(treepos << 1) + READBIT(*bp, in)];
    (*bp)++;
    if(ct < codetree->numcodes) return ct; /*the symbol is decoded, return it*/
    else treepos = ct - codetree->numcodes; /*symbol not yet decoded, instead move tree position*/

    if(treepos >= codetree->numcodes) return (unsigned)(-1); /*error: it appeared outside the codetree*/
  }
}
#endif /*LODEPNG_COMPILE_DECODER*/

#ifdef LODEPNG_COMPILE_DECODER

/* ////////////////////////////////////////////////////////////////////////// */
/* / Inflator (Decompressor)                                                / */
/* ////////////////////////////////////////////////////////////////////////// */

/*get the tree of a deflated block with fixed tree, as specified in the deflate specification*/
static void getTreeInflateFixed(HuffmanTree* tree_ll, HuffmanTree* tree_d)
{
  /*TODO: check for out of memory errors*/
  generateFixedLitLenTree(tree_ll);
  generateFixedDistanceTree(tree_d);
}

/*get the tree of a deflated block with dynamic tree, the tree itself is also Huffman compressed with a known tree*/
static unsigned getTreeInflateDynamic(HuffmanTree* tree_ll, HuffmanTree* tree_d,
                                      const unsigned char* in, size_t* bp, size_t inlength)
{
  /*make sure that length values that aren't filled in will be 0, or a wrong tree will be generated*/
  unsigned error = 0;
  unsigned n, HLIT, HDIST, HCLEN, i;
  size_t inbitlength = inlength * 8;

  /*see comments in deflateDynamic for explanation of the context and these variables, it is analogous*/
  unsigned* bitlen_ll = 0; /*lit,len code lengths*/
  unsigned* bitlen_d = 0; /*dist code lengths*/
  /*code length code lengths ("clcl"), the bit lengths of the huffman tree used to compress bitlen_ll and bitlen_d*/
  unsigned* bitlen_cl = 0;
  HuffmanTree tree_cl; /*the code tree for code length codes (the huffman tree for compressed huffman trees)*/

  if((*bp) >> 3 >= inlength - 2) return 49; /*error: the bit pointer is or will go past the memory*/

  /*number of literal/length codes + 257. Unlike the spec, the value 257 is added to it here already*/
  HLIT =  readBitsFromStream(bp, in, 5) + 257;
  /*number of distance codes. Unlike the spec, the value 1 is added to it here already*/
  HDIST = readBitsFromStream(bp, in, 5) + 1;
  /*number of code length codes. Unlike the spec, the value 4 is added to it here already*/
  HCLEN = readBitsFromStream(bp, in, 4) + 4;

  HuffmanTree_init(&tree_cl);

  while(!error)
  {
    /*read the code length codes out of 3 * (amount of code length codes) bits*/

    bitlen_cl = (unsigned*)lodepng_malloc(NUM_CODE_LENGTH_CODES * sizeof(unsigned));
    if(!bitlen_cl) ERROR_BREAK(83 /*alloc fail*/);

    for(i = 0; i < NUM_CODE_LENGTH_CODES; i++)
    {
      if(i < HCLEN) bitlen_cl[CLCL_ORDER[i]] = readBitsFromStream(bp, in, 3);
      else bitlen_cl[CLCL_ORDER[i]] = 0; /*if not, it must stay 0*/
    }

    error = HuffmanTree_makeFromLengths(&tree_cl, bitlen_cl, NUM_CODE_LENGTH_CODES, 7);
    if(error) break;

    /*now we can use this tree to read the lengths for the tree that this function will return*/
    bitlen_ll = (unsigned*)lodepng_malloc(NUM_DEFLATE_CODE_SYMBOLS * sizeof(unsigned));
    bitlen_d = (unsigned*)lodepng_malloc(NUM_DISTANCE_SYMBOLS * sizeof(unsigned));
    if(!bitlen_ll || !bitlen_d) ERROR_BREAK(83 /*alloc fail*/);
    for(i = 0; i < NUM_DEFLATE_CODE_SYMBOLS; i++) bitlen_ll[i] = 0;
    for(i = 0; i < NUM_DISTANCE_SYMBOLS; i++) bitlen_d[i] = 0;

    /*i is the current symbol we're reading in the part that contains the code lengths of lit/len and dist codes*/
    i = 0;
    while(i < HLIT + HDIST)
    {
      unsigned code = huffmanDecodeSymbol(in, bp, &tree_cl, inbitlength);
      if(code <= 15) /*a length code*/
      {
        if(i < HLIT) bitlen_ll[i] = code;
        else bitlen_d[i - HLIT] = code;
        i++;
      }
      else if(code == 16) /*repeat previous*/
      {
        unsigned replength = 3; /*read in the 2 bits that indicate repeat length (3-6)*/
        unsigned value; /*set value to the previous code*/

        if(*bp >= inbitlength) ERROR_BREAK(50); /*error, bit pointer jumps past memory*/
        if (i == 0) ERROR_BREAK(54); /*can't repeat previous if i is 0*/

        replength += readBitsFromStream(bp, in, 2);

        if(i < HLIT + 1) value = bitlen_ll[i - 1];
        else value = bitlen_d[i - HLIT - 1];
        /*repeat this value in the next lengths*/
        for(n = 0; n < replength; n++)
        {
          if(i >= HLIT + HDIST) ERROR_BREAK(13); /*error: i is larger than the amount of codes*/
          if(i < HLIT) bitlen_ll[i] = value;
          else bitlen_d[i - HLIT] = value;
          i++;
        }
      }
      else if(code == 17) /*repeat "0" 3-10 times*/
      {
        unsigned replength = 3; /*read in the bits that indicate repeat length*/
        if(*bp >= inbitlength) ERROR_BREAK(50); /*error, bit pointer jumps past memory*/

        replength += readBitsFromStream(bp, in, 3);

        /*repeat this value in the next lengths*/
        for(n = 0; n < replength; n++)
        {
          if(i >= HLIT + HDIST) ERROR_BREAK(14); /*error: i is larger than the amount of codes*/

          if(i < HLIT) bitlen_ll[i] = 0;
          else bitlen_d[i - HLIT] = 0;
          i++;
        }
      }
      else if(code == 18) /*repeat "0" 11-138 times*/
      {
        unsigned replength = 11; /*read in the bits that indicate repeat length*/
        if(*bp >= inbitlength) ERROR_BREAK(50); /*error, bit pointer jumps past memory*/

        replength += readBitsFromStream(bp, in, 7);

        /*repeat this value in the next lengths*/
        for(n = 0; n < replength; n++)
        {
          if(i >= HLIT + HDIST) ERROR_BREAK(15); /*error: i is larger than the amount of codes*/

          if(i < HLIT) bitlen_ll[i] = 0;
          else bitlen_d[i - HLIT] = 0;
          i++;
        }
      }
      else /*if(code == (unsigned)(-1))*/ /*huffmanDecodeSymbol returns (unsigned)(-1) in case of error*/
      {
        if(code == (unsigned)(-1))
        {
          /*return error code 10 or 11 depending on the situation that happened in huffmanDecodeSymbol
          (10=no endcode, 11=wrong jump outside of tree)*/
          error = (*bp) > inbitlength ? 10 : 11;
        }
        else error = 16; /*unexisting code, this can never happen*/
        break;
      }
    }
    if(error) break;

    if(bitlen_ll[256] == 0) ERROR_BREAK(64); /*the length of the end code 256 must be larger than 0*/

    /*now we've finally got HLIT and HDIST, so generate the code trees, and the function is done*/
    error = HuffmanTree_makeFromLengths(tree_ll, bitlen_ll, NUM_DEFLATE_CODE_SYMBOLS, 15);
    if(error) break;
    error = HuffmanTree_makeFromLengths(tree_d, bitlen_d, NUM_DISTANCE_SYMBOLS, 15);

    break; /*end of error-while*/
  }

  lodepng_free(bitlen_cl);
  lodepng_free(bitlen_ll);
  lodepng_free(bitlen_d);
  HuffmanTree_cleanup(&tree_cl);

  return error;
}

/*inflate a block with dynamic of fixed Huffman tree*/
static unsigned inflateHuffmanBlock(ucvector* out, const unsigned char* in, size_t* bp,
                                    size_t* pos, size_t inlength, unsigned btype)
{
  unsigned error = 0;
  HuffmanTree tree_ll; /*the huffman tree for literal and length codes*/
  HuffmanTree tree_d; /*the huffman tree for distance codes*/
  size_t inbitlength = inlength * 8;

  HuffmanTree_init(&tree_ll);
  HuffmanTree_init(&tree_d);

  if(btype == 1) getTreeInflateFixed(&tree_ll, &tree_d);
  else if(btype == 2) error = getTreeInflateDynamic(&tree_ll, &tree_d, in, bp, inlength);

  while(!error) /*decode all symbols until end reached, breaks at end code*/
  {
    /*code_ll is literal, length or end code*/
    unsigned code_ll = huffmanDecodeSymbol(in, bp, &tree_ll, inbitlength);
    if(code_ll <= 255) /*literal symbol*/
    {
      if((*pos) >= out->size)
      {
        /*reserve more room at once*/
        if(!ucvector_resize(out, ((*pos) + 1) * 2)) ERROR_BREAK(83 /*alloc fail*/);
      }
      out->data[(*pos)] = (unsigned char)(code_ll);
      (*pos)++;
    }
    else if(code_ll >= FIRST_LENGTH_CODE_INDEX && code_ll <= LAST_LENGTH_CODE_INDEX) /*length code*/
    {
      unsigned code_d, distance;
      unsigned numextrabits_l, numextrabits_d; /*extra bits for length and distance*/
      size_t start, forward, backward, length;

      /*part 1: get length base*/
      length = LENGTHBASE[code_ll - FIRST_LENGTH_CODE_INDEX];

      /*part 2: get extra bits and add the value of that to length*/
      numextrabits_l = LENGTHEXTRA[code_ll - FIRST_LENGTH_CODE_INDEX];
      if(*bp >= inbitlength) ERROR_BREAK(51); /*error, bit pointer will jump past memory*/
      length += readBitsFromStream(bp, in, numextrabits_l);

      /*part 3: get distance code*/
      code_d = huffmanDecodeSymbol(in, bp, &tree_d, inbitlength);
      if(code_d > 29)
      {
        if(code_ll == (unsigned)(-1)) /*huffmanDecodeSymbol returns (unsigned)(-1) in case of error*/
        {
          /*return error code 10 or 11 depending on the situation that happened in huffmanDecodeSymbol
          (10=no endcode, 11=wrong jump outside of tree)*/
          error = (*bp) > inlength * 8 ? 10 : 11;
        }
        else error = 18; /*error: invalid distance code (30-31 are never used)*/
        break;
      }
      distance = DISTANCEBASE[code_d];

      /*part 4: get extra bits from distance*/
      numextrabits_d = DISTANCEEXTRA[code_d];
      if(*bp >= inbitlength) ERROR_BREAK(51); /*error, bit pointer will jump past memory*/

      distance += readBitsFromStream(bp, in, numextrabits_d);

      /*part 5: fill in all the out[n] values based on the length and dist*/
      start = (*pos);
      if(distance > start) ERROR_BREAK(52); /*too long backward distance*/
      backward = start - distance;
      if((*pos) + length >= out->size)
      {
        /*reserve more room at once*/
        if(!ucvector_resize(out, ((*pos) + length) * 2)) ERROR_BREAK(83 /*alloc fail*/);
      }

      for(forward = 0; forward < length; forward++)
      {
        out->data[(*pos)] = out->data[backward];
        (*pos)++;
        backward++;
        if(backward >= start) backward = start - distance;
      }
    }
    else if(code_ll == 256)
    {
      break; /*end code, break the loop*/
    }
    else /*if(code == (unsigned)(-1))*/ /*huffmanDecodeSymbol returns (unsigned)(-1) in case of error*/
    {
      /*return error code 10 or 11 depending on the situation that happened in huffmanDecodeSymbol
      (10=no endcode, 11=wrong jump outside of tree)*/
      error = (*bp) > inlength * 8 ? 10 : 11;
      break;
    }
  }

  HuffmanTree_cleanup(&tree_ll);
  HuffmanTree_cleanup(&tree_d);

  return error;
}

static unsigned inflateNoCompression(ucvector* out, const unsigned char* in, size_t* bp, size_t* pos, size_t inlength)
{
  /*go to first boundary of byte*/
  size_t p;
  unsigned LEN, NLEN, n, error = 0;
  while(((*bp) & 0x7) != 0) (*bp)++;
  p = (*bp) / 8; /*byte position*/

  /*read LEN (2 bytes) and NLEN (2 bytes)*/
  if(p >= inlength - 4) return 52; /*error, bit pointer will jump past memory*/
  LEN = in[p] + 256 * in[p + 1]; p += 2;
  NLEN = in[p] + 256 * in[p + 1]; p += 2;

  /*check if 16-bit NLEN is really the one's complement of LEN*/
  if(LEN + NLEN != 65535) return 21; /*error: NLEN is not one's complement of LEN*/

  if((*pos) + LEN >= out->size)
  {
    if(!ucvector_resize(out, (*pos) + LEN)) return 83; /*alloc fail*/
  }

  /*read the literal data: LEN bytes are now stored in the out buffer*/
  if(p + LEN > inlength) return 23; /*error: reading outside of in buffer*/
  for(n = 0; n < LEN; n++) out->data[(*pos)++] = in[p++];

  (*bp) = p * 8;

  return error;
}

static unsigned lodepng_inflatev(ucvector* out,
                                 const unsigned char* in, size_t insize,
                                 const LodePNGDecompressSettings* settings)
{
  /*bit pointer in the "in" data, current byte is bp >> 3, current bit is bp & 0x7 (from lsb to msb of the byte)*/
  size_t bp = 0;
  unsigned BFINAL = 0;
  size_t pos = 0; /*byte position in the out buffer*/

  unsigned error = 0;

  (void)settings;

  while(!BFINAL)
  {
    unsigned BTYPE;
    if(bp + 2 >= insize * 8) return 52; /*error, bit pointer will jump past memory*/
    BFINAL = readBitFromStream(&bp, in);
    BTYPE = 1 * readBitFromStream(&bp, in);
    BTYPE += 2 * readBitFromStream(&bp, in);

    if(BTYPE == 3) return 20; /*error: invalid BTYPE*/
    else if(BTYPE == 0) error = inflateNoCompression(out, in, &bp, &pos, insize); /*no compression*/
    else error = inflateHuffmanBlock(out, in, &bp, &pos, insize, BTYPE); /*compression, BTYPE 01 or 10*/

    if(error) return error;
  }

  /*Only now we know the true size of out, resize it to that*/
  if(!ucvector_resize(out, pos)) error = 83; /*alloc fail*/

  return error;
}

unsigned lodepng_inflate(unsigned char** out, size_t* outsize,
                         const unsigned char* in, size_t insize,
                         const LodePNGDecompressSettings* settings)
{
  unsigned error;
  ucvector v;
  ucvector_init_buffer(&v, *out, *outsize);
  error = lodepng_inflatev(&v, in, insize, settings);
  *out = v.data;
  *outsize = v.size;
  return error;
}

static unsigned inflate(unsigned char** out, size_t* outsize,
                        const unsigned char* in, size_t insize,
                        const LodePNGDecompressSettings* settings)
{
  if(settings->custom_inflate)
  {
    return settings->custom_inflate(out, outsize, in, insize, settings);
  }
  else
  {
    return lodepng_inflate(out, outsize, in, insize, settings);
  }
}

#endif /*LODEPNG_COMPILE_DECODER*/

#ifdef LODEPNG_COMPILE_ENCODER

/* ////////////////////////////////////////////////////////////////////////// */
/* / Deflator (Compressor)                                                  / */
/* ////////////////////////////////////////////////////////////////////////// */

static const size_t MAX_SUPPORTED_DEFLATE_LENGTH = 258;

/*bitlen is the size in bits of the code*/
static void addHuffmanSymbol(size_t* bp, ucvector* compressed, unsigned code, unsigned bitlen)
{
  addBitsToStreamReversed(bp, compressed, code, bitlen);
}

/*search the index in the array, that has the largest value smaller than or equal to the given value,
given array must be sorted (if no value is smaller, it returns the size of the given array)*/
static size_t searchCodeIndex(const unsigned* array, size_t array_size, size_t value)
{
  /*linear search implementation*/
  /*for(size_t i = 1; i < array_size; i++) if(array[i] > value) return i - 1;
  return array_size - 1;*/

  /*binary search implementation (not that much faster) (precondition: array_size > 0)*/
  size_t left  = 1;
  size_t right = array_size - 1;
  while(left <= right)
  {
    size_t mid = (left + right) / 2;
    if(array[mid] <= value) left = mid + 1; /*the value to find is more to the right*/
    else if(array[mid - 1] > value) right = mid - 1; /*the value to find is more to the left*/
    else return mid - 1;
  }
  return array_size - 1;
}

static void addLengthDistance(uivector* values, size_t length, size_t distance)
{
  /*values in encoded vector are those used by deflate:
  0-255: literal bytes
  256: end
  257-285: length/distance pair (length code, followed by extra length bits, distance code, extra distance bits)
  286-287: invalid*/

  unsigned length_code = (unsigned)searchCodeIndex(LENGTHBASE, 29, length);
  unsigned extra_length = (unsigned)(length - LENGTHBASE[length_code]);
  unsigned dist_code = (unsigned)searchCodeIndex(DISTANCEBASE, 30, distance);
  unsigned extra_distance = (unsigned)(distance - DISTANCEBASE[dist_code]);

  uivector_push_back(values, length_code + FIRST_LENGTH_CODE_INDEX);
  uivector_push_back(values, extra_length);
  uivector_push_back(values, dist_code);
  uivector_push_back(values, extra_distance);
}

static const unsigned HASH_NUM_VALUES = 65536;
static const unsigned HASH_NUM_CHARACTERS = 3;
static const unsigned HASH_SHIFT = 2;
/*
The HASH_NUM_CHARACTERS value is used to make encoding faster by using longer
sequences to generate a hash value from the stream bytes. Setting it to 3
gives exactly the same compression as the brute force method, since deflate's
run length encoding starts with lengths of 3. Setting it to higher values,
like 6, can make the encoding faster (not always though!), but will cause the
encoding to miss any length between 3 and this value, so that the compression
may be worse (but this can vary too depending on the image, sometimes it is
even a bit better instead).
The HASH_NUM_VALUES is the amount of unique possible hash values that
combinations of bytes can give, the higher it is the more memory is needed, but
if it's too low the advantage of hashing is gone.
*/

typedef struct Hash
{
  int* head; /*hash value to head circular pos*/
  int* val; /*circular pos to hash value*/
  /*circular pos to prev circular pos*/
  unsigned short* chain;
  unsigned short* zeros;
} Hash;

static unsigned hash_init(Hash* hash, unsigned windowsize)
{
  unsigned i;
  hash->head = (int*)lodepng_malloc(sizeof(int) * HASH_NUM_VALUES);
  hash->val = (int*)lodepng_malloc(sizeof(int) * windowsize);
  hash->chain = (unsigned short*)lodepng_malloc(sizeof(unsigned short) * windowsize);
  hash->zeros = (unsigned short*)lodepng_malloc(sizeof(unsigned short) * windowsize);

  if(!hash->head || !hash->val || !hash->chain || !hash->zeros) return 83; /*alloc fail*/

  /*initialize hash table*/
  for(i = 0; i < HASH_NUM_VALUES; i++) hash->head[i] = -1;
  for(i = 0; i < windowsize; i++) hash->val[i] = -1;
  for(i = 0; i < windowsize; i++) hash->chain[i] = i; /*same value as index indicates uninitialized*/

  return 0;
}

static void hash_cleanup(Hash* hash)
{
  lodepng_free(hash->head);
  lodepng_free(hash->val);
  lodepng_free(hash->chain);
  lodepng_free(hash->zeros);
}

static unsigned getHash(const unsigned char* data, size_t size, size_t pos)
{
  unsigned result = 0;
  size_t amount, i;
  if(pos >= size) return 0;
  amount = HASH_NUM_CHARACTERS;
  if(pos + amount >= size) amount = size - pos;
  for(i = 0; i < amount; i++) result ^= (data[pos + i] << (i * HASH_SHIFT));
  return result % HASH_NUM_VALUES;
}

static unsigned countZeros(const unsigned char* data, size_t size, size_t pos)
{
  const unsigned char* start = data + pos;
  const unsigned char* end = start + MAX_SUPPORTED_DEFLATE_LENGTH;
  if(end > data + size) end = data + size;
  data = start;
  while (data != end && *data == 0) data++;
  /*subtracting two addresses returned as 32-bit number (max value is MAX_SUPPORTED_DEFLATE_LENGTH)*/
  return (unsigned)(data - start);
}

static void updateHashChain(Hash* hash, size_t pos, int hashval, unsigned windowsize)
{
  unsigned wpos = pos % windowsize;
  hash->val[wpos] = hashval;
  if(hash->head[hashval] != -1) hash->chain[wpos] = hash->head[hashval];
  hash->head[hashval] = wpos;
}

/*
LZ77-encode the data. Return value is error code. The input are raw bytes, the output
is in the form of unsigned integers with codes representing for example literal bytes, or
length/distance pairs.
It uses a hash table technique to let it encode faster. When doing LZ77 encoding, a
sliding window (of windowsize) is used, and all past bytes in that window can be used as
the "dictionary". A brute force search through all possible distances would be slow, and
this hash technique is one out of several ways to speed this up.
*/
static unsigned encodeLZ77(uivector* out, Hash* hash,
                           const unsigned char* in, size_t inpos, size_t insize, unsigned windowsize,
                           unsigned minmatch, unsigned nicematch, unsigned lazymatching)
{
  unsigned short numzeros = 0;
  int usezeros = windowsize >= 8192; /*for small window size, the 'max chain length' optimization does a better job*/
  unsigned pos, i, error = 0;
  /*for large window lengths, assume the user wants no compression loss. Otherwise, max hash chain length speedup.*/
  unsigned maxchainlength = windowsize >= 8192 ? windowsize : windowsize / 8;
  unsigned maxlazymatch = windowsize >= 8192 ? MAX_SUPPORTED_DEFLATE_LENGTH : 64;

  if(!error)
  {
    unsigned offset; /*the offset represents the distance in LZ77 terminology*/
    unsigned length;
    unsigned lazy = 0;
    unsigned lazylength = 0, lazyoffset = 0;
    unsigned hashval;
    unsigned current_offset, current_length;
    const unsigned char *lastptr, *foreptr, *backptr;
    unsigned short hashpos, prevpos;

    for(pos = inpos; pos < insize; pos++)
    {
      size_t wpos = pos % windowsize; /*position for in 'circular' hash buffers*/

      hashval = getHash(in, insize, pos);
      updateHashChain(hash, pos, hashval, windowsize);

      if(usezeros && hashval == 0)
      {
        numzeros = countZeros(in, insize, pos);
        hash->zeros[wpos] = numzeros;
      }

      /*the length and offset found for the current position*/
      length = 0;
      offset = 0;

      prevpos = hash->head[hashval];
      hashpos = hash->chain[prevpos];

      lastptr = &in[insize < pos + MAX_SUPPORTED_DEFLATE_LENGTH ? insize : pos + MAX_SUPPORTED_DEFLATE_LENGTH];

      /*search for the longest string*/
      if(hash->val[wpos] == (int)hashval)
      {
        unsigned chainlength = 0;
        for(;;)
        {
          /*stop when went completely around the circular buffer*/
          if(prevpos < wpos && hashpos > prevpos && hashpos <= wpos) break;
          if(prevpos > wpos && (hashpos <= wpos || hashpos > prevpos)) break;
          if(chainlength++ >= maxchainlength) break;

          current_offset = hashpos <= wpos ? wpos - hashpos : wpos - hashpos + windowsize;
          if(current_offset > 0)
          {
            /*test the next characters*/
            foreptr = &in[pos];
            backptr = &in[pos - current_offset];

            /*common case in PNGs is lots of zeros. Quickly skip over them as a speedup*/
            if(usezeros && hashval == 0 && hash->val[hashpos] == 0 /*hashval[hashpos] may be out of date*/)
            {
              unsigned short skip = hash->zeros[hashpos];
              if(skip > numzeros) skip = numzeros;
              backptr += skip;
              foreptr += skip;
            }

            /* multiple checks at once per array bounds check */
            while(foreptr != lastptr && *backptr == *foreptr) /*maximum supported length by deflate is max length*/
            {
              ++backptr;
              ++foreptr;
            }
            current_length = (unsigned)(foreptr - &in[pos]);

            if(current_length > length)
            {
              length = current_length; /*the longest length*/
              offset = current_offset; /*the offset that is related to this longest length*/
              /*jump out once a length of max length is found (speed gain)*/
              if(current_length >= nicematch || current_length == MAX_SUPPORTED_DEFLATE_LENGTH) break;
            }
          }

          if(hashpos == hash->chain[hashpos]) break;

          prevpos = hashpos;
          hashpos = hash->chain[hashpos];
        }
      }

      if(lazymatching)
      {
        if(!lazy && length >= 3 && length <= maxlazymatch && length < MAX_SUPPORTED_DEFLATE_LENGTH)
        {
          lazy = 1;
          lazylength = length;
          lazyoffset = offset;
          continue; /*try the next byte*/
        }
        if(lazy)
        {
          lazy = 0;
          if(pos == 0) ERROR_BREAK(81);
          if(length > lazylength + 1)
          {
            /*push the previous character as literal*/
            if(!uivector_push_back(out, in[pos - 1])) ERROR_BREAK(83 /*alloc fail*/);
          }
          else
          {
            length = lazylength;
            offset = lazyoffset;
            hash->head[hashval] = -1; /*the same hashchain update will be done, this ensures no wrong alteration*/
            pos--;
          }
        }
      }
      if(length >= 3 && offset > windowsize) ERROR_BREAK(86 /*too big (or overflown negative) offset*/);

      /**encode it as length/distance pair or literal value**/
      if(length < 3) /*only lengths of 3 or higher are supported as length/distance pair*/
      {
        if(!uivector_push_back(out, in[pos])) ERROR_BREAK(83 /*alloc fail*/);
      }
      else if(length < minmatch || (length == 3 && offset > 4096))
      {
        /*compensate for the fact that longer offsets have more extra bits, a
        length of only 3 may be not worth it then*/
        if(!uivector_push_back(out, in[pos])) ERROR_BREAK(83 /*alloc fail*/);
      }
      else
      {
        addLengthDistance(out, length, offset);
        for(i = 1; i < length; i++)
        {
          pos++;
          hashval = getHash(in, insize, pos);
          updateHashChain(hash, pos, hashval, windowsize);
          if(usezeros && hashval == 0)
          {
            hash->zeros[pos % windowsize] = countZeros(in, insize, pos);
          }
        }
      }

    } /*end of the loop through each character of input*/
  } /*end of "if(!error)"*/

  return error;
}

/* /////////////////////////////////////////////////////////////////////////// */

static unsigned deflateNoCompression(ucvector* out, const unsigned char* data, size_t datasize)
{
  /*non compressed deflate block data: 1 bit BFINAL,2 bits BTYPE,(5 bits): it jumps to start of next byte,
  2 bytes LEN, 2 bytes NLEN, LEN bytes literal DATA*/

  size_t i, j, numdeflateblocks = (datasize + 65534) / 65535;
  unsigned datapos = 0;
  for(i = 0; i < numdeflateblocks; i++)
  {
    unsigned BFINAL, BTYPE, LEN, NLEN;
    unsigned char firstbyte;

    BFINAL = (i == numdeflateblocks - 1);
    BTYPE = 0;

    firstbyte = (unsigned char)(BFINAL + ((BTYPE & 1) << 1) + ((BTYPE & 2) << 1));
    ucvector_push_back(out, firstbyte);

    LEN = 65535;
    if(datasize - datapos < 65535) LEN = (unsigned)datasize - datapos;
    NLEN = 65535 - LEN;

    ucvector_push_back(out, (unsigned char)(LEN % 256));
    ucvector_push_back(out, (unsigned char)(LEN / 256));
    ucvector_push_back(out, (unsigned char)(NLEN % 256));
    ucvector_push_back(out, (unsigned char)(NLEN / 256));

    /*Decompressed data*/
    for(j = 0; j < 65535 && datapos < datasize; j++)
    {
      ucvector_push_back(out, data[datapos++]);
    }
  }

  return 0;
}

/*
write the lz77-encoded data, which has lit, len and dist codes, to compressed stream using huffman trees.
tree_ll: the tree for lit and len codes.
tree_d: the tree for distance codes.
*/
static void writeLZ77data(size_t* bp, ucvector* out, const uivector* lz77_encoded,
                          const HuffmanTree* tree_ll, const HuffmanTree* tree_d)
{
  size_t i = 0;
  for(i = 0; i < lz77_encoded->size; i++)
  {
    unsigned val = lz77_encoded->data[i];
    addHuffmanSymbol(bp, out, HuffmanTree_getCode(tree_ll, val), HuffmanTree_getLength(tree_ll, val));
    if(val > 256) /*for a length code, 3 more things have to be added*/
    {
      unsigned length_index = val - FIRST_LENGTH_CODE_INDEX;
      unsigned n_length_extra_bits = LENGTHEXTRA[length_index];
      unsigned length_extra_bits = lz77_encoded->data[++i];

      unsigned distance_code = lz77_encoded->data[++i];

      unsigned distance_index = distance_code;
      unsigned n_distance_extra_bits = DISTANCEEXTRA[distance_index];
      unsigned distance_extra_bits = lz77_encoded->data[++i];

      addBitsToStream(bp, out, length_extra_bits, n_length_extra_bits);
      addHuffmanSymbol(bp, out, HuffmanTree_getCode(tree_d, distance_code),
                       HuffmanTree_getLength(tree_d, distance_code));
      addBitsToStream(bp, out, distance_extra_bits, n_distance_extra_bits);
    }
  }
}

/*Deflate for a block of type "dynamic", that is, with freely, optimally, created huffman trees*/
static unsigned deflateDynamic(ucvector* out, size_t* bp, Hash* hash,
                               const unsigned char* data, size_t datapos, size_t dataend,
                               const LodePNGCompressSettings* settings, int final)
{
  unsigned error = 0;

  /*
  A block is compressed as follows: The PNG data is lz77 encoded, resulting in
  literal bytes and length/distance pairs. This is then huffman compressed with
  two huffman trees. One huffman tree is used for the lit and len values ("ll"),
  another huffman tree is used for the dist values ("d"). These two trees are
  stored using their code lengths, and to compress even more these code lengths
  are also run-length encoded and huffman compressed. This gives a huffman tree
  of code lengths "cl". The code lenghts used to describe this third tree are
  the code length code lengths ("clcl").
  */

  /*The lz77 encoded data, represented with integers since there will also be length and distance codes in it*/
  uivector lz77_encoded;
  HuffmanTree tree_ll; /*tree for lit,len values*/
  HuffmanTree tree_d; /*tree for distance codes*/
  HuffmanTree tree_cl; /*tree for encoding the code lengths representing tree_ll and tree_d*/
  uivector frequencies_ll; /*frequency of lit,len codes*/
  uivector frequencies_d; /*frequency of dist codes*/
  uivector frequencies_cl; /*frequency of code length codes*/
  uivector bitlen_lld; /*lit,len,dist code lenghts (int bits), literally (without repeat codes).*/
  uivector bitlen_lld_e; /*bitlen_lld encoded with repeat codes (this is a rudemtary run length compression)*/
  /*bitlen_cl is the code length code lengths ("clcl"). The bit lengths of codes to represent tree_cl
  (these are written as is in the file, it would be crazy to compress these using yet another huffman
  tree that needs to be represented by yet another set of code lengths)*/
  uivector bitlen_cl;
  size_t datasize = dataend - datapos;

  /*
  Due to the huffman compression of huffman tree representations ("two levels"), there are some anologies:
  bitlen_lld is to tree_cl what data is to tree_ll and tree_d.
  bitlen_lld_e is to bitlen_lld what lz77_encoded is to data.
  bitlen_cl is to bitlen_lld_e what bitlen_lld is to lz77_encoded.
  */

  unsigned BFINAL = final;
  size_t numcodes_ll, numcodes_d, i;
  unsigned HLIT, HDIST, HCLEN;

  uivector_init(&lz77_encoded);
  HuffmanTree_init(&tree_ll);
  HuffmanTree_init(&tree_d);
  HuffmanTree_init(&tree_cl);
  uivector_init(&frequencies_ll);
  uivector_init(&frequencies_d);
  uivector_init(&frequencies_cl);
  uivector_init(&bitlen_lld);
  uivector_init(&bitlen_lld_e);
  uivector_init(&bitlen_cl);

  /*This while loop never loops due to a break at the end, it is here to
  allow breaking out of it to the cleanup phase on error conditions.*/
  while(!error)
  {
    if(settings->use_lz77)
    {
      error = encodeLZ77(&lz77_encoded, hash, data, datapos, dataend, settings->windowsize,
                         settings->minmatch, settings->nicematch, settings->lazymatching);
      if(error) break;
    }
    else
    {
      if(!uivector_resize(&lz77_encoded, datasize)) ERROR_BREAK(83 /*alloc fail*/);
      for(i = datapos; i < dataend; i++) lz77_encoded.data[i] = data[i]; /*no LZ77, but still will be Huffman compressed*/
    }

    if(!uivector_resizev(&frequencies_ll, 286, 0)) ERROR_BREAK(83 /*alloc fail*/);
    if(!uivector_resizev(&frequencies_d, 30, 0)) ERROR_BREAK(83 /*alloc fail*/);

    /*Count the frequencies of lit, len and dist codes*/
    for(i = 0; i < lz77_encoded.size; i++)
    {
      unsigned symbol = lz77_encoded.data[i];
      frequencies_ll.data[symbol]++;
      if(symbol > 256)
      {
        unsigned dist = lz77_encoded.data[i + 2];
        frequencies_d.data[dist]++;
        i += 3;
      }
    }
    frequencies_ll.data[256] = 1; /*there will be exactly 1 end code, at the end of the block*/

    /*Make both huffman trees, one for the lit and len codes, one for the dist codes*/
    error = HuffmanTree_makeFromFrequencies(&tree_ll, frequencies_ll.data, 257, frequencies_ll.size, 15);
    if(error) break;
    /*2, not 1, is chosen for mincodes: some buggy PNG decoders require at least 2 symbols in the dist tree*/
    error = HuffmanTree_makeFromFrequencies(&tree_d, frequencies_d.data, 2, frequencies_d.size, 15);
    if(error) break;

    numcodes_ll = tree_ll.numcodes; if(numcodes_ll > 286) numcodes_ll = 286;
    numcodes_d = tree_d.numcodes; if(numcodes_d > 30) numcodes_d = 30;
    /*store the code lengths of both generated trees in bitlen_lld*/
    for(i = 0; i < numcodes_ll; i++) uivector_push_back(&bitlen_lld, HuffmanTree_getLength(&tree_ll, (unsigned)i));
    for(i = 0; i < numcodes_d; i++) uivector_push_back(&bitlen_lld, HuffmanTree_getLength(&tree_d, (unsigned)i));

    /*run-length compress bitlen_ldd into bitlen_lld_e by using repeat codes 16 (copy length 3-6 times),
    17 (3-10 zeroes), 18 (11-138 zeroes)*/
    for(i = 0; i < (unsigned)bitlen_lld.size; i++)
    {
      unsigned j = 0; /*amount of repititions*/
      while(i + j + 1 < (unsigned)bitlen_lld.size && bitlen_lld.data[i + j + 1] == bitlen_lld.data[i]) j++;

      if(bitlen_lld.data[i] == 0 && j >= 2) /*repeat code for zeroes*/
      {
        j++; /*include the first zero*/
        if(j <= 10) /*repeat code 17 supports max 10 zeroes*/
        {
          uivector_push_back(&bitlen_lld_e, 17);
          uivector_push_back(&bitlen_lld_e, j - 3);
        }
        else /*repeat code 18 supports max 138 zeroes*/
        {
          if(j > 138) j = 138;
          uivector_push_back(&bitlen_lld_e, 18);
          uivector_push_back(&bitlen_lld_e, j - 11);
        }
        i += (j - 1);
      }
      else if(j >= 3) /*repeat code for value other than zero*/
      {
        size_t k;
        unsigned num = j / 6, rest = j % 6;
        uivector_push_back(&bitlen_lld_e, bitlen_lld.data[i]);
        for(k = 0; k < num; k++)
        {
          uivector_push_back(&bitlen_lld_e, 16);
          uivector_push_back(&bitlen_lld_e, 6 - 3);
        }
        if(rest >= 3)
        {
          uivector_push_back(&bitlen_lld_e, 16);
          uivector_push_back(&bitlen_lld_e, rest - 3);
        }
        else j -= rest;
        i += j;
      }
      else /*too short to benefit from repeat code*/
      {
        uivector_push_back(&bitlen_lld_e, bitlen_lld.data[i]);
      }
    }

    /*generate tree_cl, the huffmantree of huffmantrees*/

    if(!uivector_resizev(&frequencies_cl, NUM_CODE_LENGTH_CODES, 0)) ERROR_BREAK(83 /*alloc fail*/);
    for(i = 0; i < bitlen_lld_e.size; i++)
    {
      frequencies_cl.data[bitlen_lld_e.data[i]]++;
      /*after a repeat code come the bits that specify the number of repetitions,
      those don't need to be in the frequencies_cl calculation*/
      if(bitlen_lld_e.data[i] >= 16) i++;
    }

    error = HuffmanTree_makeFromFrequencies(&tree_cl, frequencies_cl.data,
                                            frequencies_cl.size, frequencies_cl.size, 7);
    if(error) break;

    if(!uivector_resize(&bitlen_cl, tree_cl.numcodes)) ERROR_BREAK(83 /*alloc fail*/);
    for(i = 0; i < tree_cl.numcodes; i++)
    {
      /*lenghts of code length tree is in the order as specified by deflate*/
      bitlen_cl.data[i] = HuffmanTree_getLength(&tree_cl, CLCL_ORDER[i]);
    }
    while(bitlen_cl.data[bitlen_cl.size - 1] == 0 && bitlen_cl.size > 4)
    {
      /*remove zeros at the end, but minimum size must be 4*/
      if(!uivector_resize(&bitlen_cl, bitlen_cl.size - 1)) ERROR_BREAK(83 /*alloc fail*/);
    }
    if(error) break;

    /*
    Write everything into the output

    After the BFINAL and BTYPE, the dynamic block consists out of the following:
    - 5 bits HLIT, 5 bits HDIST, 4 bits HCLEN
    - (HCLEN+4)*3 bits code lengths of code length alphabet
    - HLIT + 257 code lenghts of lit/length alphabet (encoded using the code length
      alphabet, + possible repetition codes 16, 17, 18)
    - HDIST + 1 code lengths of distance alphabet (encoded using the code length
      alphabet, + possible repetition codes 16, 17, 18)
    - compressed data
    - 256 (end code)
    */

    /*Write block type*/
    addBitToStream(bp, out, BFINAL);
    addBitToStream(bp, out, 0); /*first bit of BTYPE "dynamic"*/
    addBitToStream(bp, out, 1); /*second bit of BTYPE "dynamic"*/

    /*write the HLIT, HDIST and HCLEN values*/
    HLIT = (unsigned)(numcodes_ll - 257);
    HDIST = (unsigned)(numcodes_d - 1);
    HCLEN = (unsigned)bitlen_cl.size - 4;
    /*trim zeroes for HCLEN. HLIT and HDIST were already trimmed at tree creation*/
    while(!bitlen_cl.data[HCLEN + 4 - 1] && HCLEN > 0) HCLEN--;
    addBitsToStream(bp, out, HLIT, 5);
    addBitsToStream(bp, out, HDIST, 5);
    addBitsToStream(bp, out, HCLEN, 4);

    /*write the code lenghts of the code length alphabet*/
    for(i = 0; i < HCLEN + 4; i++) addBitsToStream(bp, out, bitlen_cl.data[i], 3);

    /*write the lenghts of the lit/len AND the dist alphabet*/
    for(i = 0; i < bitlen_lld_e.size; i++)
    {
      addHuffmanSymbol(bp, out, HuffmanTree_getCode(&tree_cl, bitlen_lld_e.data[i]),
                       HuffmanTree_getLength(&tree_cl, bitlen_lld_e.data[i]));
      /*extra bits of repeat codes*/
      if(bitlen_lld_e.data[i] == 16) addBitsToStream(bp, out, bitlen_lld_e.data[++i], 2);
      else if(bitlen_lld_e.data[i] == 17) addBitsToStream(bp, out, bitlen_lld_e.data[++i], 3);
      else if(bitlen_lld_e.data[i] == 18) addBitsToStream(bp, out, bitlen_lld_e.data[++i], 7);
    }

    /*write the compressed data symbols*/
    writeLZ77data(bp, out, &lz77_encoded, &tree_ll, &tree_d);
    /*error: the length of the end code 256 must be larger than 0*/
    if(HuffmanTree_getLength(&tree_ll, 256) == 0) ERROR_BREAK(64);

    /*write the end code*/
    addHuffmanSymbol(bp, out, HuffmanTree_getCode(&tree_ll, 256), HuffmanTree_getLength(&tree_ll, 256));

    break; /*end of error-while*/
  }

  /*cleanup*/
  uivector_cleanup(&lz77_encoded);
  HuffmanTree_cleanup(&tree_ll);
  HuffmanTree_cleanup(&tree_d);
  HuffmanTree_cleanup(&tree_cl);
  uivector_cleanup(&frequencies_ll);
  uivector_cleanup(&frequencies_d);
  uivector_cleanup(&frequencies_cl);
  uivector_cleanup(&bitlen_lld_e);
  uivector_cleanup(&bitlen_lld);
  uivector_cleanup(&bitlen_cl);

  return error;
}

static unsigned deflateFixed(ucvector* out, size_t* bp, Hash* hash,
                             const unsigned char* data,
                             size_t datapos, size_t dataend,
                             const LodePNGCompressSettings* settings, int final)
{
  HuffmanTree tree_ll; /*tree for literal values and length codes*/
  HuffmanTree tree_d; /*tree for distance codes*/

  unsigned BFINAL = final;
  unsigned error = 0;
  size_t i;

  HuffmanTree_init(&tree_ll);
  HuffmanTree_init(&tree_d);

  generateFixedLitLenTree(&tree_ll);
  generateFixedDistanceTree(&tree_d);

  addBitToStream(bp, out, BFINAL);
  addBitToStream(bp, out, 1); /*first bit of BTYPE*/
  addBitToStream(bp, out, 0); /*second bit of BTYPE*/

  if(settings->use_lz77) /*LZ77 encoded*/
  {
    uivector lz77_encoded;
    uivector_init(&lz77_encoded);
    error = encodeLZ77(&lz77_encoded, hash, data, datapos, dataend, settings->windowsize,
                       settings->minmatch, settings->nicematch, settings->lazymatching);
    if(!error) writeLZ77data(bp, out, &lz77_encoded, &tree_ll, &tree_d);
    uivector_cleanup(&lz77_encoded);
  }
  else /*no LZ77, but still will be Huffman compressed*/
  {
    for(i = datapos; i < dataend; i++)
    {
      addHuffmanSymbol(bp, out, HuffmanTree_getCode(&tree_ll, data[i]), HuffmanTree_getLength(&tree_ll, data[i]));
    }
  }
  /*add END code*/
  if(!error) addHuffmanSymbol(bp, out, HuffmanTree_getCode(&tree_ll, 256), HuffmanTree_getLength(&tree_ll, 256));

  /*cleanup*/
  HuffmanTree_cleanup(&tree_ll);
  HuffmanTree_cleanup(&tree_d);

  return error;
}

static unsigned lodepng_deflatev(ucvector* out, const unsigned char* in, size_t insize,
                                 const LodePNGCompressSettings* settings)
{
  unsigned error = 0;
  size_t i, blocksize, numdeflateblocks;
  size_t bp = 0; /*the bit pointer*/
  Hash hash;

  if(settings->btype > 2) return 61;
  else if(settings->btype == 0) return deflateNoCompression(out, in, insize);
  else if(settings->btype == 1) blocksize = insize;
  else /*if(settings->btype == 2)*/
  {
    blocksize = insize / 8 + 8;
    if(blocksize < 65535) blocksize = 65535;
  }

  numdeflateblocks = (insize + blocksize - 1) / blocksize;
  if(numdeflateblocks == 0) numdeflateblocks = 1;

  error = hash_init(&hash, settings->windowsize);
  if(error) return error;

  for(i = 0; i < numdeflateblocks && !error; i++)
  {
    int final = i == numdeflateblocks - 1;
    size_t start = i * blocksize;
    size_t end = start + blocksize;
    if(end > insize) end = insize;

    if(settings->btype == 1) error = deflateFixed(out, &bp, &hash, in, start, end, settings, final);
    else if(settings->btype == 2) error = deflateDynamic(out, &bp, &hash, in, start, end, settings, final);
  }

  hash_cleanup(&hash);

  return error;
}

unsigned lodepng_deflate(unsigned char** out, size_t* outsize,
                         const unsigned char* in, size_t insize,
                         const LodePNGCompressSettings* settings)
{
  unsigned error;
  ucvector v;
  ucvector_init_buffer(&v, *out, *outsize);
  error = lodepng_deflatev(&v, in, insize, settings);
  *out = v.data;
  *outsize = v.size;
  return error;
}

static unsigned deflate(unsigned char** out, size_t* outsize,
                        const unsigned char* in, size_t insize,
                        const LodePNGCompressSettings* settings)
{
  if(settings->custom_deflate)
  {
    return settings->custom_deflate(out, outsize, in, insize, settings);
  }
  else
  {
    return lodepng_deflate(out, outsize, in, insize, settings);
  }
}

#endif /*LODEPNG_COMPILE_DECODER*/

/* ////////////////////////////////////////////////////////////////////////// */
/* / Adler32                                                                  */
/* ////////////////////////////////////////////////////////////////////////// */

static unsigned update_adler32(unsigned adler, const unsigned char* data, unsigned len)
{
   unsigned s1 = adler & 0xffff;
   unsigned s2 = (adler >> 16) & 0xffff;

  while(len > 0)
  {
    /*at least 5550 sums can be done before the sums overflow, saving a lot of module divisions*/
    unsigned amount = len > 5550 ? 5550 : len;
    len -= amount;
    while(amount > 0)
    {
      s1 += (*data++);
      s2 += s1;
      amount--;
    }
    s1 %= 65521;
    s2 %= 65521;
  }

  return (s2 << 16) | s1;
}

/*Return the adler32 of the bytes data[0..len-1]*/
static unsigned adler32(const unsigned char* data, unsigned len)
{
  return update_adler32(1L, data, len);
}

/* ////////////////////////////////////////////////////////////////////////// */
/* / Zlib                                                                   / */
/* ////////////////////////////////////////////////////////////////////////// */

#ifdef LODEPNG_COMPILE_DECODER

unsigned lodepng_zlib_decompress(unsigned char** out, size_t* outsize, const unsigned char* in,
                                 size_t insize, const LodePNGDecompressSettings* settings)
{
  unsigned error = 0;
  unsigned CM, CINFO, FDICT;

  if(insize < 2) return 53; /*error, size of zlib data too small*/
  /*read information from zlib header*/
  if((in[0] * 256 + in[1]) % 31 != 0)
  {
    /*error: 256 * in[0] + in[1] must be a multiple of 31, the FCHECK value is supposed to be made that way*/
    return 24;
  }

  CM = in[0] & 15;
  CINFO = (in[0] >> 4) & 15;
  /*FCHECK = in[1] & 31;*/ /*FCHECK is already tested above*/
  FDICT = (in[1] >> 5) & 1;
  /*FLEVEL = (in[1] >> 6) & 3;*/ /*FLEVEL is not used here*/

  if(CM != 8 || CINFO > 7)
  {
    /*error: only compression method 8: inflate with sliding window of 32k is supported by the PNG spec*/
    return 25;
  }
  if(FDICT != 0)
  {
    /*error: the specification of PNG says about the zlib stream:
      "The additional flags shall not specify a preset dictionary."*/
    return 26;
  }

  error = inflate(out, outsize, in + 2, insize - 2, settings);
  if(error) return error;

  if(!settings->ignore_adler32)
  {
    unsigned ADLER32 = lodepng_read32bitInt(&in[insize - 4]);
    unsigned checksum = adler32(*out, (unsigned)(*outsize));
    if(checksum != ADLER32) return 58; /*error, adler checksum not correct, data must be corrupted*/
  }

  return 0; /*no error*/
}

static unsigned zlib_decompress(unsigned char** out, size_t* outsize, const unsigned char* in,
                                size_t insize, const LodePNGDecompressSettings* settings)
{
  if(settings->custom_zlib)
    return settings->custom_zlib(out, outsize, in, insize, settings);
  else
    return lodepng_zlib_decompress(out, outsize, in, insize, settings);
}

#endif /*LODEPNG_COMPILE_DECODER*/

#ifdef LODEPNG_COMPILE_ENCODER

unsigned lodepng_zlib_compress(unsigned char** out, size_t* outsize, const unsigned char* in,
                               size_t insize, const LodePNGCompressSettings* settings)
{
  /*initially, *out must be NULL and outsize 0, if you just give some random *out
  that's pointing to a non allocated buffer, this'll crash*/
  ucvector outv;
  size_t i;
  unsigned error;
  unsigned char* deflatedata = 0;
  size_t deflatesize = 0;

  unsigned ADLER32;
  /*zlib data: 1 byte CMF (CM+CINFO), 1 byte FLG, deflate data, 4 byte ADLER32 checksum of the Decompressed data*/
  unsigned CMF = 120; /*0b01111000: CM 8, CINFO 7. With CINFO 7, any window size up to 32768 can be used.*/
  unsigned FLEVEL = 0;
  unsigned FDICT = 0;
  unsigned CMFFLG = 256 * CMF + FDICT * 32 + FLEVEL * 64;
  unsigned FCHECK = 31 - CMFFLG % 31;
  CMFFLG += FCHECK;

  /*ucvector-controlled version of the output buffer, for dynamic array*/
  ucvector_init_buffer(&outv, *out, *outsize);

  ucvector_push_back(&outv, (unsigned char)(CMFFLG / 256));
  ucvector_push_back(&outv, (unsigned char)(CMFFLG % 256));

  error = deflate(&deflatedata, &deflatesize, in, insize, settings);

  if(!error)
  {
    ADLER32 = adler32(in, (unsigned)insize);
    for(i = 0; i < deflatesize; i++) ucvector_push_back(&outv, deflatedata[i]);
    lodepng_free(deflatedata);
    lodepng_add32bitInt(&outv, ADLER32);
  }

  *out = outv.data;
  *outsize = outv.size;

  return error;
}

/* compress using the default or custom zlib function */
static unsigned zlib_compress(unsigned char** out, size_t* outsize, const unsigned char* in,
                              size_t insize, const LodePNGCompressSettings* settings)
{
  if(settings->custom_zlib)
  {
    return settings->custom_zlib(out, outsize, in, insize, settings);
  }
  else
  {
    return lodepng_zlib_compress(out, outsize, in, insize, settings);
  }
}

#endif /*LODEPNG_COMPILE_ENCODER*/

#else /*no LODEPNG_COMPILE_ZLIB*/

#ifdef LODEPNG_COMPILE_DECODER
static unsigned zlib_decompress(unsigned char** out, size_t* outsize, const unsigned char* in,
                                size_t insize, const LodePNGDecompressSettings* settings)
{
  if (!settings->custom_zlib) return 87; /*no custom zlib function provided */
  return settings->custom_zlib(out, outsize, in, insize, settings);
}
#endif /*LODEPNG_COMPILE_DECODER*/
#ifdef LODEPNG_COMPILE_ENCODER
static unsigned zlib_compress(unsigned char** out, size_t* outsize, const unsigned char* in,
                              size_t insize, const LodePNGCompressSettings* settings)
{
  if (!settings->custom_zlib) return 87; /*no custom zlib function provided */
  return settings->custom_zlib(out, outsize, in, insize, settings);
}
#endif /*LODEPNG_COMPILE_ENCODER*/

#endif /*LODEPNG_COMPILE_ZLIB*/

/* ////////////////////////////////////////////////////////////////////////// */

#ifdef LODEPNG_COMPILE_ENCODER

/*this is a good tradeoff between speed and compression ratio*/
#define DEFAULT_WINDOWSIZE 2048

void lodepng_compress_settings_init(LodePNGCompressSettings* settings)
{
  /*compress with dynamic huffman tree (not in the mathematical sense, just not the predefined one)*/
  settings->btype = 2;
  settings->use_lz77 = 1;
  settings->windowsize = DEFAULT_WINDOWSIZE;
  settings->minmatch = 3;
  settings->nicematch = 128;
  settings->lazymatching = 1;

  settings->custom_zlib = 0;
  settings->custom_deflate = 0;
  settings->custom_context = 0;
}

const LodePNGCompressSettings lodepng_default_compress_settings = {2, 1, DEFAULT_WINDOWSIZE, 3, 128, 1, 0, 0, 0};


#endif /*LODEPNG_COMPILE_ENCODER*/

#ifdef LODEPNG_COMPILE_DECODER

void lodepng_decompress_settings_init(LodePNGDecompressSettings* settings)
{
  settings->ignore_adler32 = 0;

  settings->custom_zlib = 0;
  settings->custom_inflate = 0;
  settings->custom_context = 0;
}

const LodePNGDecompressSettings lodepng_default_decompress_settings = {0, 0, 0, 0};

#endif /*LODEPNG_COMPILE_DECODER*/

/* ////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */
/* // End of Zlib related code. Begin of PNG related code.                 // */
/* ////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */

#ifdef LODEPNG_COMPILE_PNG

/* ////////////////////////////////////////////////////////////////////////// */
/* / CRC32                                                                  / */
/* ////////////////////////////////////////////////////////////////////////// */

/* CRC polynomial: 0xedb88320 */
static unsigned lodepng_crc32_table[256] = {
           0u, 1996959894u, 3993919788u, 2567524794u,  124634137u, 1886057615u, 3915621685u, 2657392035u,
   249268274u, 2044508324u, 3772115230u, 2547177864u,  162941995u, 2125561021u, 3887607047u, 2428444049u,
   498536548u, 1789927666u, 4089016648u, 2227061214u,  450548861u, 1843258603u, 4107580753u, 2211677639u,
   325883990u, 1684777152u, 4251122042u, 2321926636u,  335633487u, 1661365465u, 4195302755u, 2366115317u,
   997073096u, 1281953886u, 3579855332u, 2724688242u, 1006888145u, 1258607687u, 3524101629u, 2768942443u,
   901097722u, 1119000684u, 3686517206u, 2898065728u,  853044451u, 1172266101u, 3705015759u, 2882616665u,
   651767980u, 1373503546u, 3369554304u, 3218104598u,  565507253u, 1454621731u, 3485111705u, 3099436303u,
   671266974u, 1594198024u, 3322730930u, 2970347812u,  795835527u, 1483230225u, 3244367275u, 3060149565u,
  1994146192u,   31158534u, 2563907772u, 4023717930u, 1907459465u,  112637215u, 2680153253u, 3904427059u,
  2013776290u,  251722036u, 2517215374u, 3775830040u, 2137656763u,  141376813u, 2439277719u, 3865271297u,
  1802195444u,  476864866u, 2238001368u, 4066508878u, 1812370925u,  453092731u, 2181625025u, 4111451223u,
  1706088902u,  314042704u, 2344532202u, 4240017532u, 1658658271u,  366619977u, 2362670323u, 4224994405u,
  1303535960u,  984961486u, 2747007092u, 3569037538u, 1256170817u, 1037604311u, 2765210733u, 3554079995u,
  1131014506u,  879679996u, 2909243462u, 3663771856u, 1141124467u,  855842277u, 2852801631u, 3708648649u,
  1342533948u,  654459306u, 3188396048u, 3373015174u, 1466479909u,  544179635u, 3110523913u, 3462522015u,
  1591671054u,  702138776u, 2966460450u, 3352799412u, 1504918807u,  783551873u, 3082640443u, 3233442989u,
  3988292384u, 2596254646u,   62317068u, 1957810842u, 3939845945u, 2647816111u,   81470997u, 1943803523u,
  3814918930u, 2489596804u,  225274430u, 2053790376u, 3826175755u, 2466906013u,  167816743u, 2097651377u,
  4027552580u, 2265490386u,  503444072u, 1762050814u, 4150417245u, 2154129355u,  426522225u, 1852507879u,
  4275313526u, 2312317920u,  282753626u, 1742555852u, 4189708143u, 2394877945u,  397917763u, 1622183637u,
  3604390888u, 2714866558u,  953729732u, 1340076626u, 3518719985u, 2797360999u, 1068828381u, 1219638859u,
  3624741850u, 2936675148u,  906185462u, 1090812512u, 3747672003u, 2825379669u,  829329135u, 1181335161u,
  3412177804u, 3160834842u,  628085408u, 1382605366u, 3423369109u, 3138078467u,  570562233u, 1426400815u,
  3317316542u, 2998733608u,  733239954u, 1555261956u, 3268935591u, 3050360625u,  752459403u, 1541320221u,
  2607071920u, 3965973030u, 1969922972u,   40735498u, 2617837225u, 3943577151u, 1913087877u,   83908371u,
  2512341634u, 3803740692u, 2075208622u,  213261112u, 2463272603u, 3855990285u, 2094854071u,  198958881u,
  2262029012u, 4057260610u, 1759359992u,  534414190u, 2176718541u, 4139329115u, 1873836001u,  414664567u,
  2282248934u, 4279200368u, 1711684554u,  285281116u, 2405801727u, 4167216745u, 1634467795u,  376229701u,
  2685067896u, 3608007406u, 1308918612u,  956543938u, 2808555105u, 3495958263u, 1231636301u, 1047427035u,
  2932959818u, 3654703836u, 1088359270u,  936918000u, 2847714899u, 3736837829u, 1202900863u,  817233897u,
  3183342108u, 3401237130u, 1404277552u,  615818150u, 3134207493u, 3453421203u, 1423857449u,  601450431u,
  3009837614u, 3294710456u, 1567103746u,  711928724u, 3020668471u, 3272380065u, 1510334235u,  755167117u
};

/*Return the CRC of the bytes buf[0..len-1].*/
unsigned lodepng_crc32(const unsigned char* buf, size_t len)
{
  unsigned c = 0xffffffffL;
  size_t n;

  for(n = 0; n < len; n++)
  {
    c = lodepng_crc32_table[(c ^ buf[n]) & 0xff] ^ (c >> 8);
  }
  return c ^ 0xffffffffL;
}

/* ////////////////////////////////////////////////////////////////////////// */
/* / Reading and writing single bits and bytes from/to stream for LodePNG   / */
/* ////////////////////////////////////////////////////////////////////////// */

static unsigned char readBitFromReversedStream(size_t* bitpointer, const unsigned char* bitstream)
{
  unsigned char result = (unsigned char)((bitstream[(*bitpointer) >> 3] >> (7 - ((*bitpointer) & 0x7))) & 1);
  (*bitpointer)++;
  return result;
}

static unsigned readBitsFromReversedStream(size_t* bitpointer, const unsigned char* bitstream, size_t nbits)
{
  unsigned result = 0;
  size_t i;
  for(i = nbits - 1; i < nbits; i--)
  {
    result += (unsigned)readBitFromReversedStream(bitpointer, bitstream) << i;
  }
  return result;
}

#ifdef LODEPNG_COMPILE_DECODER
static void setBitOfReversedStream0(size_t* bitpointer, unsigned char* bitstream, unsigned char bit)
{
  /*the current bit in bitstream must be 0 for this to work*/
  if(bit)
  {
    /*earlier bit of huffman code is in a lesser significant bit of an earlier byte*/
    bitstream[(*bitpointer) >> 3] |= (bit << (7 - ((*bitpointer) & 0x7)));
  }
  (*bitpointer)++;
}
#endif /*LODEPNG_COMPILE_DECODER*/

static void setBitOfReversedStream(size_t* bitpointer, unsigned char* bitstream, unsigned char bit)
{
  /*the current bit in bitstream may be 0 or 1 for this to work*/
  if(bit == 0) bitstream[(*bitpointer) >> 3] &=  (unsigned char)(~(1 << (7 - ((*bitpointer) & 0x7))));
  else         bitstream[(*bitpointer) >> 3] |=  (1 << (7 - ((*bitpointer) & 0x7)));
  (*bitpointer)++;
}

/* ////////////////////////////////////////////////////////////////////////// */
/* / PNG chunks                                                             / */
/* ////////////////////////////////////////////////////////////////////////// */

unsigned lodepng_chunk_length(const unsigned char* chunk)
{
  return lodepng_read32bitInt(&chunk[0]);
}

void lodepng_chunk_type(char type[5], const unsigned char* chunk)
{
  unsigned i;
  for(i = 0; i < 4; i++) type[i] = chunk[4 + i];
  type[4] = 0; /*null termination char*/
}

unsigned char lodepng_chunk_type_equals(const unsigned char* chunk, const char* type)
{
  if(strlen(type) != 4) return 0;
  return (chunk[4] == type[0] && chunk[5] == type[1] && chunk[6] == type[2] && chunk[7] == type[3]);
}

unsigned char lodepng_chunk_ancillary(const unsigned char* chunk)
{
  return((chunk[4] & 32) != 0);
}

unsigned char lodepng_chunk_private(const unsigned char* chunk)
{
  return((chunk[6] & 32) != 0);
}

unsigned char lodepng_chunk_safetocopy(const unsigned char* chunk)
{
  return((chunk[7] & 32) != 0);
}

unsigned char* lodepng_chunk_data(unsigned char* chunk)
{
  return &chunk[8];
}

const unsigned char* lodepng_chunk_data_const(const unsigned char* chunk)
{
  return &chunk[8];
}

unsigned lodepng_chunk_check_crc(const unsigned char* chunk)
{
  unsigned length = lodepng_chunk_length(chunk);
  unsigned CRC = lodepng_read32bitInt(&chunk[length + 8]);
  /*the CRC is taken of the data and the 4 chunk type letters, not the length*/
  unsigned checksum = lodepng_crc32(&chunk[4], length + 4);
  if(CRC != checksum) return 1;
  else return 0;
}

void lodepng_chunk_generate_crc(unsigned char* chunk)
{
  unsigned length = lodepng_chunk_length(chunk);
  unsigned CRC = lodepng_crc32(&chunk[4], length + 4);
  lodepng_set32bitInt(chunk + 8 + length, CRC);
}

unsigned char* lodepng_chunk_next(unsigned char* chunk)
{
  unsigned total_chunk_length = lodepng_chunk_length(chunk) + 12;
  return &chunk[total_chunk_length];
}

const unsigned char* lodepng_chunk_next_const(const unsigned char* chunk)
{
  unsigned total_chunk_length = lodepng_chunk_length(chunk) + 12;
  return &chunk[total_chunk_length];
}

unsigned lodepng_chunk_append(unsigned char** out, size_t* outlength, const unsigned char* chunk)
{
  unsigned i;
  unsigned total_chunk_length = lodepng_chunk_length(chunk) + 12;
  unsigned char *chunk_start, *new_buffer;
  size_t new_length = (*outlength) + total_chunk_length;
  if(new_length < total_chunk_length || new_length < (*outlength)) return 77; /*integer overflow happened*/

  new_buffer = (unsigned char*)lodepng_realloc(*out, new_length);
  if(!new_buffer) return 83; /*alloc fail*/
  (*out) = new_buffer;
  (*outlength) = new_length;
  chunk_start = &(*out)[new_length - total_chunk_length];

  for(i = 0; i < total_chunk_length; i++) chunk_start[i] = chunk[i];

  return 0;
}

unsigned lodepng_chunk_create(unsigned char** out, size_t* outlength, unsigned length,
                              const char* type, const unsigned char* data)
{
  unsigned i;
  unsigned char *chunk, *new_buffer;
  size_t new_length = (*outlength) + length + 12;
  if(new_length < length + 12 || new_length < (*outlength)) return 77; /*integer overflow happened*/
  new_buffer = (unsigned char*)lodepng_realloc(*out, new_length);
  if(!new_buffer) return 83; /*alloc fail*/
  (*out) = new_buffer;
  (*outlength) = new_length;
  chunk = &(*out)[(*outlength) - length - 12];

  /*1: length*/
  lodepng_set32bitInt(chunk, (unsigned)length);

  /*2: chunk name (4 letters)*/
  chunk[4] = type[0];
  chunk[5] = type[1];
  chunk[6] = type[2];
  chunk[7] = type[3];

  /*3: the data*/
  for(i = 0; i < length; i++) chunk[8 + i] = data[i];

  /*4: CRC (of the chunkname characters and the data)*/
  lodepng_chunk_generate_crc(chunk);

  return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
/* / Color types and such                                                   / */
/* ////////////////////////////////////////////////////////////////////////// */

/*return type is a LodePNG error code*/
static unsigned checkColorValidity(LodePNGColorType colortype, unsigned bd) /*bd = bitdepth*/
{
  switch(colortype)
  {
    case 0: if(!(bd == 1 || bd == 2 || bd == 4 || bd == 8 || bd == 16)) return 37; break; /*grey*/
    case 2: if(!(                                 bd == 8 || bd == 16)) return 37; break; /*RGB*/
    case 3: if(!(bd == 1 || bd == 2 || bd == 4 || bd == 8            )) return 37; break; /*palette*/
    case 4: if(!(                                 bd == 8 || bd == 16)) return 37; break; /*grey + alpha*/
    case 6: if(!(                                 bd == 8 || bd == 16)) return 37; break; /*RGBA*/
    default: return 31;
  }
  return 0; /*allowed color type / bits combination*/
}

static unsigned getNumColorChannels(LodePNGColorType colortype)
{
  switch(colortype)
  {
    case 0: return 1; /*grey*/
    case 2: return 3; /*RGB*/
    case 3: return 1; /*palette*/
    case 4: return 2; /*grey + alpha*/
    case 6: return 4; /*RGBA*/
  }
  return 0; /*unexisting color type*/
}

static unsigned lodepng_get_bpp_lct(LodePNGColorType colortype, unsigned bitdepth)
{
  /*bits per pixel is amount of channels * bits per channel*/
  return getNumColorChannels(colortype) * bitdepth;
}

/* ////////////////////////////////////////////////////////////////////////// */

void lodepng_color_mode_init(LodePNGColorMode* info)
{
  info->key_defined = 0;
  info->key_r = info->key_g = info->key_b = 0;
  info->colortype = LCT_RGBA;
  info->bitdepth = 8;
  info->palette = 0;
  info->palettesize = 0;
}

void lodepng_color_mode_cleanup(LodePNGColorMode* info)
{
  lodepng_palette_clear(info);
}

unsigned lodepng_color_mode_copy(LodePNGColorMode* dest, const LodePNGColorMode* source)
{
  size_t i;
  lodepng_color_mode_cleanup(dest);
  *dest = *source;
  if(source->palette)
  {
    dest->palette = (unsigned char*)lodepng_malloc(1024);
    if(!dest->palette && source->palettesize) return 83; /*alloc fail*/
    for(i = 0; i < source->palettesize * 4; i++) dest->palette[i] = source->palette[i];
  }
  return 0;
}

static int lodepng_color_mode_equal(const LodePNGColorMode* a, const LodePNGColorMode* b)
{
  size_t i;
  if(a->colortype != b->colortype) return 0;
  if(a->bitdepth != b->bitdepth) return 0;
  if(a->key_defined != b->key_defined) return 0;
  if(a->key_defined)
  {
    if(a->key_r != b->key_r) return 0;
    if(a->key_g != b->key_g) return 0;
    if(a->key_b != b->key_b) return 0;
  }
  if(a->palettesize != b->palettesize) return 0;
  for(i = 0; i < a->palettesize * 4; i++)
  {
    if(a->palette[i] != b->palette[i]) return 0;
  }
  return 1;
}

void lodepng_palette_clear(LodePNGColorMode* info)
{
  if(info->palette) lodepng_free(info->palette);
  info->palette = 0;
  info->palettesize = 0;
}

unsigned lodepng_palette_add(LodePNGColorMode* info,
                             unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
  unsigned char* data;
  /*the same resize technique as C++ std::vectors is used, and here it's made so that for a palette with
  the max of 256 colors, it'll have the exact alloc size*/
  if(!info->palette) /*allocate palette if empty*/
  {
    /*room for 256 colors with 4 bytes each*/
    data = (unsigned char*)lodepng_realloc(info->palette, 1024);
    if(!data) return 83; /*alloc fail*/
    else info->palette = data;
  }
  info->palette[4 * info->palettesize + 0] = r;
  info->palette[4 * info->palettesize + 1] = g;
  info->palette[4 * info->palettesize + 2] = b;
  info->palette[4 * info->palettesize + 3] = a;
  info->palettesize++;
  return 0;
}

unsigned lodepng_get_bpp(const LodePNGColorMode* info)
{
  /*calculate bits per pixel out of colortype and bitdepth*/
  return lodepng_get_bpp_lct(info->colortype, info->bitdepth);
}

unsigned lodepng_get_channels(const LodePNGColorMode* info)
{
  return getNumColorChannels(info->colortype);
}

unsigned lodepng_is_greyscale_type(const LodePNGColorMode* info)
{
  return info->colortype == LCT_GREY || info->colortype == LCT_GREY_ALPHA;
}

unsigned lodepng_is_alpha_type(const LodePNGColorMode* info)
{
  return (info->colortype & 4) != 0; /*4 or 6*/
}

unsigned lodepng_is_palette_type(const LodePNGColorMode* info)
{
  return info->colortype == LCT_PALETTE;
}

unsigned lodepng_has_palette_alpha(const LodePNGColorMode* info)
{
  size_t i;
  for(i = 0; i < info->palettesize; i++)
  {
    if(info->palette[i * 4 + 3] < 255) return 1;
  }
  return 0;
}

unsigned lodepng_can_have_alpha(const LodePNGColorMode* info)
{
  return info->key_defined
      || lodepng_is_alpha_type(info)
      || lodepng_has_palette_alpha(info);
}

size_t lodepng_get_raw_size(unsigned w, unsigned h, const LodePNGColorMode* color)
{
  return (w * h * lodepng_get_bpp(color) + 7) / 8;
}

size_t lodepng_get_raw_size_lct(unsigned w, unsigned h, LodePNGColorType colortype, unsigned bitdepth)
{
  return (w * h * lodepng_get_bpp_lct(colortype, bitdepth) + 7) / 8;
}

#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS

static void LodePNGUnknownChunks_init(LodePNGInfo* info)
{
  unsigned i;
  for(i = 0; i < 3; i++) info->unknown_chunks_data[i] = 0;
  for(i = 0; i < 3; i++) info->unknown_chunks_size[i] = 0;
}

static void LodePNGUnknownChunks_cleanup(LodePNGInfo* info)
{
  unsigned i;
  for(i = 0; i < 3; i++) lodepng_free(info->unknown_chunks_data[i]);
}

static unsigned LodePNGUnknownChunks_copy(LodePNGInfo* dest, const LodePNGInfo* src)
{
  unsigned i;

  LodePNGUnknownChunks_cleanup(dest);

  for(i = 0; i < 3; i++)
  {
    size_t j;
    dest->unknown_chunks_size[i] = src->unknown_chunks_size[i];
    dest->unknown_chunks_data[i] = (unsigned char*)lodepng_malloc(src->unknown_chunks_size[i]);
    if(!dest->unknown_chunks_data[i] && dest->unknown_chunks_size[i]) return 83; /*alloc fail*/
    for(j = 0; j < src->unknown_chunks_size[i]; j++)
    {
      dest->unknown_chunks_data[i][j] = src->unknown_chunks_data[i][j];
    }
  }

  return 0;
}

/******************************************************************************/

static void LodePNGText_init(LodePNGInfo* info)
{
  info->text_num = 0;
  info->text_keys = NULL;
  info->text_strings = NULL;
}

static void LodePNGText_cleanup(LodePNGInfo* info)
{
  size_t i;
  for(i = 0; i < info->text_num; i++)
  {
    string_cleanup(&info->text_keys[i]);
    string_cleanup(&info->text_strings[i]);
  }
  lodepng_free(info->text_keys);
  lodepng_free(info->text_strings);
}

static unsigned LodePNGText_copy(LodePNGInfo* dest, const LodePNGInfo* source)
{
  size_t i = 0;
  dest->text_keys = 0;
  dest->text_strings = 0;
  dest->text_num = 0;
  for(i = 0; i < source->text_num; i++)
  {
    CERROR_TRY_RETURN(lodepng_add_text(dest, source->text_keys[i], source->text_strings[i]));
  }
  return 0;
}

void lodepng_clear_text(LodePNGInfo* info)
{
  LodePNGText_cleanup(info);
}

unsigned lodepng_add_text(LodePNGInfo* info, const char* key, const char* str)
{
  char** new_keys = (char**)(lodepng_realloc(info->text_keys, sizeof(char*) * (info->text_num + 1)));
  char** new_strings = (char**)(lodepng_realloc(info->text_strings, sizeof(char*) * (info->text_num + 1)));
  if(!new_keys || !new_strings)
  {
    lodepng_free(new_keys);
    lodepng_free(new_strings);
    return 83; /*alloc fail*/
  }

  info->text_num++;
  info->text_keys = new_keys;
  info->text_strings = new_strings;

  string_init(&info->text_keys[info->text_num - 1]);
  string_set(&info->text_keys[info->text_num - 1], key);

  string_init(&info->text_strings[info->text_num - 1]);
  string_set(&info->text_strings[info->text_num - 1], str);

  return 0;
}

/******************************************************************************/

static void LodePNGIText_init(LodePNGInfo* info)
{
  info->itext_num = 0;
  info->itext_keys = NULL;
  info->itext_langtags = NULL;
  info->itext_transkeys = NULL;
  info->itext_strings = NULL;
}

static void LodePNGIText_cleanup(LodePNGInfo* info)
{
  size_t i;
  for(i = 0; i < info->itext_num; i++)
  {
    string_cleanup(&info->itext_keys[i]);
    string_cleanup(&info->itext_langtags[i]);
    string_cleanup(&info->itext_transkeys[i]);
    string_cleanup(&info->itext_strings[i]);
  }
  lodepng_free(info->itext_keys);
  lodepng_free(info->itext_langtags);
  lodepng_free(info->itext_transkeys);
  lodepng_free(info->itext_strings);
}

static unsigned LodePNGIText_copy(LodePNGInfo* dest, const LodePNGInfo* source)
{
  size_t i = 0;
  dest->itext_keys = 0;
  dest->itext_langtags = 0;
  dest->itext_transkeys = 0;
  dest->itext_strings = 0;
  dest->itext_num = 0;
  for(i = 0; i < source->itext_num; i++)
  {
    CERROR_TRY_RETURN(lodepng_add_itext(dest, source->itext_keys[i], source->itext_langtags[i],
                                        source->itext_transkeys[i], source->itext_strings[i]));
  }
  return 0;
}

void lodepng_clear_itext(LodePNGInfo* info)
{
  LodePNGIText_cleanup(info);
}

unsigned lodepng_add_itext(LodePNGInfo* info, const char* key, const char* langtag,
                           const char* transkey, const char* str)
{
  char** new_keys = (char**)(lodepng_realloc(info->itext_keys, sizeof(char*) * (info->itext_num + 1)));
  char** new_langtags = (char**)(lodepng_realloc(info->itext_langtags, sizeof(char*) * (info->itext_num + 1)));
  char** new_transkeys = (char**)(lodepng_realloc(info->itext_transkeys, sizeof(char*) * (info->itext_num + 1)));
  char** new_strings = (char**)(lodepng_realloc(info->itext_strings, sizeof(char*) * (info->itext_num + 1)));
  if(!new_keys || !new_langtags || !new_transkeys || !new_strings)
  {
    lodepng_free(new_keys);
    lodepng_free(new_langtags);
    lodepng_free(new_transkeys);
    lodepng_free(new_strings);
    return 83; /*alloc fail*/
  }

  info->itext_num++;
  info->itext_keys = new_keys;
  info->itext_langtags = new_langtags;
  info->itext_transkeys = new_transkeys;
  info->itext_strings = new_strings;

  string_init(&info->itext_keys[info->itext_num - 1]);
  string_set(&info->itext_keys[info->itext_num - 1], key);

  string_init(&info->itext_langtags[info->itext_num - 1]);
  string_set(&info->itext_langtags[info->itext_num - 1], langtag);

  string_init(&info->itext_transkeys[info->itext_num - 1]);
  string_set(&info->itext_transkeys[info->itext_num - 1], transkey);

  string_init(&info->itext_strings[info->itext_num - 1]);
  string_set(&info->itext_strings[info->itext_num - 1], str);

  return 0;
}
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/

void lodepng_info_init(LodePNGInfo* info)
{
  lodepng_color_mode_init(&info->color);
  info->interlace_method = 0;
  info->compression_method = 0;
  info->filter_method = 0;
#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
  info->background_defined = 0;
  info->background_r = info->background_g = info->background_b = 0;

  LodePNGText_init(info);
  LodePNGIText_init(info);

  info->time_defined = 0;
  info->phys_defined = 0;

  LodePNGUnknownChunks_init(info);
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
}

void lodepng_info_cleanup(LodePNGInfo* info)
{
  lodepng_color_mode_cleanup(&info->color);
#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
  LodePNGText_cleanup(info);
  LodePNGIText_cleanup(info);

  LodePNGUnknownChunks_cleanup(info);
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
}

unsigned lodepng_info_copy(LodePNGInfo* dest, const LodePNGInfo* source)
{
  lodepng_info_cleanup(dest);
  *dest = *source;
  lodepng_color_mode_init(&dest->color);
  CERROR_TRY_RETURN(lodepng_color_mode_copy(&dest->color, &source->color));

#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
  CERROR_TRY_RETURN(LodePNGText_copy(dest, source));
  CERROR_TRY_RETURN(LodePNGIText_copy(dest, source));

  LodePNGUnknownChunks_init(dest);
  CERROR_TRY_RETURN(LodePNGUnknownChunks_copy(dest, source));
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
  return 0;
}

void lodepng_info_swap(LodePNGInfo* a, LodePNGInfo* b)
{
  LodePNGInfo temp = *a;
  *a = *b;
  *b = temp;
}

/* ////////////////////////////////////////////////////////////////////////// */

/*index: bitgroup index, bits: bitgroup size(1, 2 or 4, in: bitgroup value, out: octet array to add bits to*/
static void addColorBits(unsigned char* out, size_t index, unsigned bits, unsigned in)
{
  /*p = the partial index in the byte, e.g. with 4 palettebits it is 0 for first half or 1 for second half*/
  unsigned p = index % (8 / bits);
  in &= (1 << bits) - 1; /*filter out any other bits of the input value*/
  in = in << (bits * (8 / bits - p - 1));
  if(p == 0) out[index * bits / 8] = in;
  else out[index * bits / 8] |= in;
}

typedef struct ColorTree ColorTree;

/*
One node of a color tree
This is the data structure used to count the number of unique colors and to get a palette
index for a color. It's like an octree, but because the alpha channel is used too, each
node has 16 instead of 8 children.
*/
struct ColorTree
{
  ColorTree* children[16]; /*up to 16 pointers to ColorTree of next level*/
  int index; /*the payload. Only has a meaningful value if this is in the last level*/
};

static void color_tree_init(ColorTree* tree)
{
  int i;
  for(i = 0; i < 16; i++) tree->children[i] = 0;
  tree->index = -1;
}

static void color_tree_cleanup(ColorTree* tree)
{
  int i;
  for(i = 0; i < 16; i++)
  {
    if(tree->children[i])
    {
      color_tree_cleanup(tree->children[i]);
      lodepng_free(tree->children[i]);
    }
  }
}

/*returns -1 if color not present, its index otherwise*/
static int color_tree_get(ColorTree* tree, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
  int bit = 0;
  for(bit = 0; bit < 8; bit++)
  {
    int i = 8 * ((r >> bit) & 1) + 4 * ((g >> bit) & 1) + 2 * ((b >> bit) & 1) + 1 * ((a >> bit) & 1);
    if(!tree->children[i]) return -1;
    else tree = tree->children[i];
  }
  return tree ? tree->index : -1;
}

#ifdef LODEPNG_COMPILE_ENCODER
static int color_tree_has(ColorTree* tree, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
  return color_tree_get(tree, r, g, b, a) >= 0;
}
#endif /*LODEPNG_COMPILE_ENCODER*/

/*color is not allowed to already exist.
Index should be >= 0 (it's signed to be compatible with using -1 for "doesn't exist")*/
static void color_tree_add(ColorTree* tree,
                           unsigned char r, unsigned char g, unsigned char b, unsigned char a, int index)
{
  int bit;
  for(bit = 0; bit < 8; bit++)
  {
    int i = 8 * ((r >> bit) & 1) + 4 * ((g >> bit) & 1) + 2 * ((b >> bit) & 1) + 1 * ((a >> bit) & 1);
    if(!tree->children[i])
    {
      tree->children[i] = (ColorTree*)lodepng_malloc(sizeof(ColorTree));
      color_tree_init(tree->children[i]);
    }
    tree = tree->children[i];
  }
  tree->index = index;
}

/*put a pixel, given its RGBA color, into image of any color type*/
static unsigned rgba8ToPixel(unsigned char* out, size_t i,
                             const LodePNGColorMode* mode, ColorTree* tree /*for palette*/,
                             unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
  if(mode->colortype == LCT_GREY)
  {
    unsigned char grey = r; /*((unsigned short)r + g + b) / 3*/;
    if(mode->bitdepth == 8) out[i] = grey;
    else if(mode->bitdepth == 16) out[i * 2 + 0] = out[i * 2 + 1] = grey;
    else
    {
      /*take the most significant bits of grey*/
      grey = (grey >> (8 - mode->bitdepth)) & ((1 << mode->bitdepth) - 1);
      addColorBits(out, i, mode->bitdepth, grey);
    }
  }
  else if(mode->colortype == LCT_RGB)
  {
    if(mode->bitdepth == 8)
    {
      out[i * 3 + 0] = r;
      out[i * 3 + 1] = g;
      out[i * 3 + 2] = b;
    }
    else
    {
      out[i * 6 + 0] = out[i * 6 + 1] = r;
      out[i * 6 + 2] = out[i * 6 + 3] = g;
      out[i * 6 + 4] = out[i * 6 + 5] = b;
    }
  }
  else if(mode->colortype == LCT_PALETTE)
  {
    int index = color_tree_get(tree, r, g, b, a);
    if(index < 0) return 82; /*color not in palette*/
    if(mode->bitdepth == 8) out[i] = index;
    else addColorBits(out, i, mode->bitdepth, index);
  }
  else if(mode->colortype == LCT_GREY_ALPHA)
  {
    unsigned char grey = r; /*((unsigned short)r + g + b) / 3*/;
    if(mode->bitdepth == 8)
    {
      out[i * 2 + 0] = grey;
      out[i * 2 + 1] = a;
    }
    else if(mode->bitdepth == 16)
    {
      out[i * 4 + 0] = out[i * 4 + 1] = grey;
      out[i * 4 + 2] = out[i * 4 + 3] = a;
    }
  }
  else if(mode->colortype == LCT_RGBA)
  {
    if(mode->bitdepth == 8)
    {
      out[i * 4 + 0] = r;
      out[i * 4 + 1] = g;
      out[i * 4 + 2] = b;
      out[i * 4 + 3] = a;
    }
    else
    {
      out[i * 8 + 0] = out[i * 8 + 1] = r;
      out[i * 8 + 2] = out[i * 8 + 3] = g;
      out[i * 8 + 4] = out[i * 8 + 5] = b;
      out[i * 8 + 6] = out[i * 8 + 7] = a;
    }
  }

  return 0; /*no error*/
}

/*put a pixel, given its RGBA16 color, into image of any color 16-bitdepth type*/
static unsigned rgba16ToPixel(unsigned char* out, size_t i,
                              const LodePNGColorMode* mode,
                              unsigned short r, unsigned short g, unsigned short b, unsigned short a)
{
  if(mode->bitdepth != 16) return 85; /*must be 16 for this function*/
  if(mode->colortype == LCT_GREY)
  {
    unsigned short grey = r; /*((unsigned)r + g + b) / 3*/;
    out[i * 2 + 0] = (grey >> 8) & 255;
    out[i * 2 + 1] = grey & 255;
  }
  else if(mode->colortype == LCT_RGB)
  {
    out[i * 6 + 0] = (r >> 8) & 255;
    out[i * 6 + 1] = r & 255;
    out[i * 6 + 2] = (g >> 8) & 255;
    out[i * 6 + 3] = g & 255;
    out[i * 6 + 4] = (b >> 8) & 255;
    out[i * 6 + 5] = b & 255;
  }
  else if(mode->colortype == LCT_GREY_ALPHA)
  {
    unsigned short grey = r; /*((unsigned)r + g + b) / 3*/;
    out[i * 4 + 0] = (grey >> 8) & 255;
    out[i * 4 + 1] = grey & 255;
    out[i * 4 + 2] = (a >> 8) & 255;
    out[i * 4 + 3] = a & 255;
  }
  else if(mode->colortype == LCT_RGBA)
  {
    out[i * 8 + 0] = (r >> 8) & 255;
    out[i * 8 + 1] = r & 255;
    out[i * 8 + 2] = (g >> 8) & 255;
    out[i * 8 + 3] = g & 255;
    out[i * 8 + 4] = (b >> 8) & 255;
    out[i * 8 + 5] = b & 255;
    out[i * 8 + 6] = (a >> 8) & 255;
    out[i * 8 + 7] = a & 255;
  }

  return 0; /*no error*/
}

/*Get RGBA8 color of pixel with index i (y * width + x) from the raw image with given color type.*/
static unsigned getPixelColorRGBA8(unsigned char* r, unsigned char* g,
                                   unsigned char* b, unsigned char* a,
                                   const unsigned char* in, size_t i,
                                   const LodePNGColorMode* mode,
                                   unsigned fix_png)
{
  if(mode->colortype == LCT_GREY)
  {
    if(mode->bitdepth == 8)
    {
      *r = *g = *b = in[i];
      if(mode->key_defined && *r == mode->key_r) *a = 0;
      else *a = 255;
    }
    else if(mode->bitdepth == 16)
    {
      *r = *g = *b = in[i * 2 + 0];
      if(mode->key_defined && 256U * in[i * 2 + 0] + in[i * 2 + 1] == mode->key_r) *a = 0;
      else *a = 255;
    }
    else
    {
      unsigned highest = ((1U << mode->bitdepth) - 1U); /*highest possible value for this bit depth*/
      size_t j = i * mode->bitdepth;
      unsigned value = readBitsFromReversedStream(&j, in, mode->bitdepth);
      *r = *g = *b = (value * 255) / highest;
      if(mode->key_defined && value == mode->key_r) *a = 0;
      else *a = 255;
    }
  }
  else if(mode->colortype == LCT_RGB)
  {
    if(mode->bitdepth == 8)
    {
      *r = in[i * 3 + 0]; *g = in[i * 3 + 1]; *b = in[i * 3 + 2];
      if(mode->key_defined && *r == mode->key_r && *g == mode->key_g && *b == mode->key_b) *a = 0;
      else *a = 255;
    }
    else
    {
      *r = in[i * 6 + 0];
      *g = in[i * 6 + 2];
      *b = in[i * 6 + 4];
      if(mode->key_defined && 256U * in[i * 6 + 0] + in[i * 6 + 1] == mode->key_r
         && 256U * in[i * 6 + 2] + in[i * 6 + 3] == mode->key_g
         && 256U * in[i * 6 + 4] + in[i * 6 + 5] == mode->key_b) *a = 0;
      else *a = 255;
    }
  }
  else if(mode->colortype == LCT_PALETTE)
  {
    unsigned index;
    if(mode->bitdepth == 8) index = in[i];
    else
    {
      size_t j = i * mode->bitdepth;
      index = readBitsFromReversedStream(&j, in, mode->bitdepth);
    }

    if(index >= mode->palettesize)
    {
      /*This is an error according to the PNG spec, but fix_png can ignore it*/
      if(!fix_png) return (mode->bitdepth == 8 ? 46 : 47); /*index out of palette*/
      *r = *g = *b = 0;
      *a = 255;
    }
    else
    {
      *r = mode->palette[index * 4 + 0];
      *g = mode->palette[index * 4 + 1];
      *b = mode->palette[index * 4 + 2];
      *a = mode->palette[index * 4 + 3];
    }
  }
  else if(mode->colortype == LCT_GREY_ALPHA)
  {
    if(mode->bitdepth == 8)
    {
      *r = *g = *b = in[i * 2 + 0];
      *a = in[i * 2 + 1];
    }
    else
    {
      *r = *g = *b = in[i * 4 + 0];
      *a = in[i * 4 + 2];
    }
  }
  else if(mode->colortype == LCT_RGBA)
  {
    if(mode->bitdepth == 8)
    {
      *r = in[i * 4 + 0];
      *g = in[i * 4 + 1];
      *b = in[i * 4 + 2];
      *a = in[i * 4 + 3];
    }
    else
    {
      *r = in[i * 8 + 0];
      *g = in[i * 8 + 2];
      *b = in[i * 8 + 4];
      *a = in[i * 8 + 6];
    }
  }

  return 0; /*no error*/
}

/*Similar to getPixelColorRGBA8, but with all the for loops inside of the color
mode test cases, optimized to convert the colors much faster, when converting
to RGBA or RGB with 8 bit per cannel. buffer must be RGBA or RGB output with
enough memory, if has_alpha is true the output is RGBA. mode has the color mode
of the input buffer.*/
static unsigned getPixelColorsRGBA8(unsigned char* buffer, size_t numpixels,
                                    unsigned has_alpha, const unsigned char* in,
                                    const LodePNGColorMode* mode,
                                    unsigned fix_png)
{
  unsigned num_channels = has_alpha ? 4 : 3;
  size_t i;
  if(mode->colortype == LCT_GREY)
  {
    if(mode->bitdepth == 8)
    {
      for(i = 0; i < numpixels; i++, buffer += num_channels)
      {
        buffer[0] = buffer[1] = buffer[2] = in[i];
        if(has_alpha) buffer[3] = mode->key_defined && in[i] == mode->key_r ? 0 : 255;
      }
    }
    else if(mode->bitdepth == 16)
    {
      for(i = 0; i < numpixels; i++, buffer += num_channels)
      {
        buffer[0] = buffer[1] = buffer[2] = in[i * 2];
        if(has_alpha) buffer[3] = mode->key_defined && 256U * in[i * 2 + 0] + in[i * 2 + 1] == mode->key_r ? 0 : 255;
      }
    }
    else
    {
      unsigned highest = ((1U << mode->bitdepth) - 1U); /*highest possible value for this bit depth*/
      size_t j = 0;
      for(i = 0; i < numpixels; i++, buffer += num_channels)
      {
        unsigned value = readBitsFromReversedStream(&j, in, mode->bitdepth);
        buffer[0] = buffer[1] = buffer[2] = (value * 255) / highest;
        if(has_alpha) buffer[3] = mode->key_defined && value == mode->key_r ? 0 : 255;
      }
    }
  }
  else if(mode->colortype == LCT_RGB)
  {
    if(mode->bitdepth == 8)
    {
      for(i = 0; i < numpixels; i++, buffer += num_channels)
      {
        buffer[0] = in[i * 3 + 0];
        buffer[1] = in[i * 3 + 1];
        buffer[2] = in[i * 3 + 2];
        if(has_alpha) buffer[3] = mode->key_defined && buffer[0] == mode->key_r
           && buffer[1]== mode->key_g && buffer[2] == mode->key_b ? 0 : 255;
      }
    }
    else
    {
      for(i = 0; i < numpixels; i++, buffer += num_channels)
      {
        buffer[0] = in[i * 6 + 0];
        buffer[1] = in[i * 6 + 2];
        buffer[2] = in[i * 6 + 4];
        if(has_alpha) buffer[3] = mode->key_defined
           && 256U * in[i * 6 + 0] + in[i * 6 + 1] == mode->key_r
           && 256U * in[i * 6 + 2] + in[i * 6 + 3] == mode->key_g
           && 256U * in[i * 6 + 4] + in[i * 6 + 5] == mode->key_b ? 0 : 255;
      }
    }
  }
  else if(mode->colortype == LCT_PALETTE)
  {
    unsigned index;
    size_t j = 0;
    for(i = 0; i < numpixels; i++, buffer += num_channels)
    {
      if(mode->bitdepth == 8) index = in[i];
      else index = readBitsFromReversedStream(&j, in, mode->bitdepth);

      if(index >= mode->palettesize)
      {
        /*This is an error according to the PNG spec, but fix_png can ignore it*/
        if(!fix_png) return (mode->bitdepth == 8 ? 46 : 47); /*index out of palette*/
        buffer[0] = buffer[1] = buffer[2] = 0;
        if(has_alpha) buffer[3] = 255;
      }
      else
      {
        buffer[0] = mode->palette[index * 4 + 0];
        buffer[1] = mode->palette[index * 4 + 1];
        buffer[2] = mode->palette[index * 4 + 2];
        if(has_alpha) buffer[3] = mode->palette[index * 4 + 3];
      }
    }
  }
  else if(mode->colortype == LCT_GREY_ALPHA)
  {
    if(mode->bitdepth == 8)
    {
      for(i = 0; i < numpixels; i++, buffer += num_channels)
      {
        buffer[0] = buffer[1] = buffer[2] = in[i * 2 + 0];
        if(has_alpha) buffer[3] = in[i * 2 + 1];
      }
    }
    else
    {
      for(i = 0; i < numpixels; i++, buffer += num_channels)
      {
        buffer[0] = buffer[1] = buffer[2] = in[i * 4 + 0];
        if(has_alpha) buffer[3] = in[i * 4 + 2];
      }
    }
  }
  else if(mode->colortype == LCT_RGBA)
  {
    if(mode->bitdepth == 8)
    {
      for(i = 0; i < numpixels; i++, buffer += num_channels)
      {
        buffer[0] = in[i * 4 + 0];
        buffer[1] = in[i * 4 + 1];
        buffer[2] = in[i * 4 + 2];
        if(has_alpha) buffer[3] = in[i * 4 + 3];
      }
    }
    else
    {
      for(i = 0; i < numpixels; i++, buffer += num_channels)
      {
        buffer[0] = in[i * 8 + 0];
        buffer[1] = in[i * 8 + 2];
        buffer[2] = in[i * 8 + 4];
        if(has_alpha) buffer[3] = in[i * 8 + 6];
      }
    }
  }

  return 0; /*no error*/
}

/*Get RGBA16 color of pixel with index i (y * width + x) from the raw image with
given color type, but the given color type must be 16-bit itself.*/
static unsigned getPixelColorRGBA16(unsigned short* r, unsigned short* g, unsigned short* b, unsigned short* a,
                                    const unsigned char* in, size_t i, const LodePNGColorMode* mode)
{
  if(mode->bitdepth != 16) return 85; /*error: this function only supports 16-bit input*/

  if(mode->colortype == LCT_GREY)
  {
    *r = *g = *b = 256 * in[i * 2 + 0] + in[i * 2 + 1];
    if(mode->key_defined && 256U * in[i * 2 + 0] + in[i * 2 + 1] == mode->key_r) *a = 0;
    else *a = 65535;
  }
  else if(mode->colortype == LCT_RGB)
  {
    *r = 256 * in[i * 6 + 0] + in[i * 6 + 1];
    *g = 256 * in[i * 6 + 2] + in[i * 6 + 3];
    *b = 256 * in[i * 6 + 4] + in[i * 6 + 5];
    if(mode->key_defined && 256U * in[i * 6 + 0] + in[i * 6 + 1] == mode->key_r
       && 256U * in[i * 6 + 2] + in[i * 6 + 3] == mode->key_g
       && 256U * in[i * 6 + 4] + in[i * 6 + 5] == mode->key_b) *a = 0;
    else *a = 65535;
  }
  else if(mode->colortype == LCT_GREY_ALPHA)
  {
    *r = *g = *b = 256 * in[i * 4 + 0] + in[i * 4 + 1];
    *a = 256 * in[i * 4 + 2] + in[i * 4 + 3];
  }
  else if(mode->colortype == LCT_RGBA)
  {
    *r = 256 * in[i * 8 + 0] + in[i * 8 + 1];
    *g = 256 * in[i * 8 + 2] + in[i * 8 + 3];
    *b = 256 * in[i * 8 + 4] + in[i * 8 + 5];
    *a = 256 * in[i * 8 + 6] + in[i * 8 + 7];
  }
  else return 85; /*error: this function only supports 16-bit input, not palettes*/

  return 0; /*no error*/
}

/*
converts from any color type to 24-bit or 32-bit (later maybe more supported). return value = LodePNG error code
the out buffer must have (w * h * bpp + 7) / 8 bytes, where bpp is the bits per pixel of the output color type
(lodepng_get_bpp) for < 8 bpp images, there may _not_ be padding bits at the end of scanlines.
*/
unsigned lodepng_convert(unsigned char* out, const unsigned char* in,
                         LodePNGColorMode* mode_out, LodePNGColorMode* mode_in,
                         unsigned w, unsigned h, unsigned fix_png)
{
  unsigned error = 0;
  size_t i;
  ColorTree tree;
  size_t numpixels = w * h;

  if(lodepng_color_mode_equal(mode_out, mode_in))
  {
    size_t numbytes = lodepng_get_raw_size(w, h, mode_in);
    for(i = 0; i < numbytes; i++) out[i] = in[i];
    return error;
  }

  if(mode_out->colortype == LCT_PALETTE)
  {
    size_t palsize = 1 << mode_out->bitdepth;
    if(mode_out->palettesize < palsize) palsize = mode_out->palettesize;
    color_tree_init(&tree);
    for(i = 0; i < palsize; i++)
    {
      unsigned char* p = &mode_out->palette[i * 4];
      color_tree_add(&tree, p[0], p[1], p[2], p[3], i);
    }
  }

  if(mode_in->bitdepth == 16 && mode_out->bitdepth == 16)
  {
    for(i = 0; i < numpixels; i++)
    {
      unsigned short r = 0, g = 0, b = 0, a = 0;
      error = getPixelColorRGBA16(&r, &g, &b, &a, in, i, mode_in);
      if(error) break;
      error = rgba16ToPixel(out, i, mode_out, r, g, b, a);
      if(error) break;
    }
  }
  else if(mode_out->bitdepth == 8 && mode_out->colortype == LCT_RGBA)
  {
    error = getPixelColorsRGBA8(out, numpixels, 1, in, mode_in, fix_png);
  }
  else if(mode_out->bitdepth == 8 && mode_out->colortype == LCT_RGB)
  {
    error = getPixelColorsRGBA8(out, numpixels, 0, in, mode_in, fix_png);
  }
  else
  {
    unsigned char r = 0, g = 0, b = 0, a = 0;
    for(i = 0; i < numpixels; i++)
    {
      error = getPixelColorRGBA8(&r, &g, &b, &a, in, i, mode_in, fix_png);
      if(error) break;
      error = rgba8ToPixel(out, i, mode_out, &tree, r, g, b, a);
      if(error) break;
    }
  }

  if(mode_out->colortype == LCT_PALETTE)
  {
    color_tree_cleanup(&tree);
  }

  return error;
}

#ifdef LODEPNG_COMPILE_ENCODER

typedef struct ColorProfile
{
  unsigned char sixteenbit; /*needs more than 8 bits per channel*/
  unsigned char sixteenbit_done;


  unsigned char colored; /*not greyscale*/
  unsigned char colored_done;

  unsigned char key; /*a color key is required, or more*/
  unsigned short key_r; /*these values are always in 16-bit bitdepth in the profile*/
  unsigned short key_g;
  unsigned short key_b;
  unsigned char alpha; /*alpha channel, or alpha palette, required*/
  unsigned char alpha_done;

  unsigned numcolors;
  ColorTree tree; /*for listing the counted colors, up to 256*/
  unsigned char* palette; /*size 1024. Remember up to the first 256 RGBA colors*/
  unsigned maxnumcolors; /*if more than that amount counted*/
  unsigned char numcolors_done;

  unsigned greybits; /*amount of bits required for greyscale (1, 2, 4, 8). Does not take 16 bit into account.*/
  unsigned char greybits_done;

} ColorProfile;

static void color_profile_init(ColorProfile* profile, LodePNGColorMode* mode)
{
  profile->sixteenbit = 0;
  profile->sixteenbit_done = mode->bitdepth == 16 ? 0 : 1;

  profile->colored = 0;
  profile->colored_done = lodepng_is_greyscale_type(mode) ? 1 : 0;

  profile->key = 0;
  profile->alpha = 0;
  profile->alpha_done = lodepng_can_have_alpha(mode) ? 0 : 1;

  profile->numcolors = 0;
  color_tree_init(&profile->tree);
  profile->palette = (unsigned char*)lodepng_malloc(1024);
  profile->maxnumcolors = 257;
  if(lodepng_get_bpp(mode) <= 8)
  {
    int bpp = lodepng_get_bpp(mode);
    profile->maxnumcolors = bpp == 1 ? 2 : (bpp == 2 ? 4 : (bpp == 4 ? 16 : 256));
  }
  profile->numcolors_done = 0;

  profile->greybits = 1;
  profile->greybits_done = lodepng_get_bpp(mode) == 1 ? 1 : 0;
}

static void color_profile_cleanup(ColorProfile* profile)
{
  color_tree_cleanup(&profile->tree);
  lodepng_free(profile->palette);
}

/*function used for debug purposes with C++*/
/*void printColorProfile(ColorProfile* p)
{
  std::cout << "sixteenbit: " << (int)p->sixteenbit << std::endl;
  std::cout << "sixteenbit_done: " << (int)p->sixteenbit_done << std::endl;
  std::cout << "colored: " << (int)p->colored << std::endl;
  std::cout << "colored_done: " << (int)p->colored_done << std::endl;
  std::cout << "key: " << (int)p->key << std::endl;
  std::cout << "key_r: " << (int)p->key_r << std::endl;
  std::cout << "key_g: " << (int)p->key_g << std::endl;
  std::cout << "key_b: " << (int)p->key_b << std::endl;
  std::cout << "alpha: " << (int)p->alpha << std::endl;
  std::cout << "alpha_done: " << (int)p->alpha_done << std::endl;
  std::cout << "numcolors: " << (int)p->numcolors << std::endl;
  std::cout << "maxnumcolors: " << (int)p->maxnumcolors << std::endl;
  std::cout << "numcolors_done: " << (int)p->numcolors_done << std::endl;
  std::cout << "greybits: " << (int)p->greybits << std::endl;
  std::cout << "greybits_done: " << (int)p->greybits_done << std::endl;
}*/

/*Returns how many bits needed to represent given value (max 8 bit)*/
unsigned getValueRequiredBits(unsigned short value)
{
  if(value == 0 || value == 255) return 1;
  /*The scaling of 2-bit and 4-bit values uses multiples of 85 and 17*/
  if(value % 17 == 0) return value % 85 == 0 ? 2 : 4;
  return 8;
}

/*profile must already have been inited with mode.
It's ok to set some parameters of profile to done already.*/
static unsigned get_color_profile(ColorProfile* profile,
                                  const unsigned char* in,
                                  size_t numpixels /*must be full image size, for certain filesize based choices*/,
                                  LodePNGColorMode* mode,
                                  unsigned fix_png)
{
  unsigned error = 0;
  size_t i;

  if(mode->bitdepth == 16)
  {
    for(i = 0; i < numpixels; i++)
    {
      unsigned short r, g, b, a;
      error = getPixelColorRGBA16(&r, &g, &b, &a, in, i, mode);
      if(error) break;

      /*a color is considered good for 8-bit if the first byte and the second byte are equal,
        (so if it's divisible through 257), NOT necessarily if the second byte is 0*/
      if(!profile->sixteenbit_done
          && (((r & 255) != ((r >> 8) & 255))
           || ((g & 255) != ((g >> 8) & 255))
           || ((b & 255) != ((b >> 8) & 255))))
      {
        profile->sixteenbit = 1;
        profile->sixteenbit_done = 1;
        profile->greybits_done = 1; /*greybits is not applicable anymore at 16-bit*/
        profile->numcolors_done = 1; /*counting colors no longer useful, palette doesn't support 16-bit*/
      }

      if(!profile->colored_done && (r != g || r != b))
      {
        profile->colored = 1;
        profile->colored_done = 1;
        profile->greybits_done = 1; /*greybits is not applicable anymore*/
      }

      if(!profile->alpha_done && a != 65535)
      {
        /*only use color key if numpixels large enough to justify tRNS chunk size*/
        if(a == 0 && numpixels > 16 && !(profile->key && (r != profile->key_r || g != profile->key_g || b != profile->key_b)))
        {
          if(!profile->alpha && !profile->key)
          {
            profile->key = 1;
            profile->key_r = r;
            profile->key_g = g;
            profile->key_b = b;
          }
        }
        else
        {
          profile->alpha = 1;
          profile->alpha_done = 1;
          profile->greybits_done = 1; /*greybits is not applicable anymore*/
        }
      }

      /* Color key cannot be used if an opaque pixel also has that RGB color. */
      if(!profile->alpha_done && a == 65535 && profile->key
          && r == profile->key_r && g == profile->key_g && b == profile->key_b)
      {
          profile->alpha = 1;
          profile->alpha_done = 1;
          profile->greybits_done = 1; /*greybits is not applicable anymore*/
      }

      if(!profile->greybits_done)
      {
        /*assuming 8-bit r, this test does not care about 16-bit*/
        unsigned bits = getValueRequiredBits(r);
        if(bits > profile->greybits) profile->greybits = bits;
        if(profile->greybits >= 8) profile->greybits_done = 1;
      }

      if(!profile->numcolors_done)
      {
        /*assuming 8-bit rgba, this test does not care about 16-bit*/
        if(!color_tree_has(&profile->tree, (unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a))
        {
          color_tree_add(&profile->tree, (unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a,
            profile->numcolors);
          if(profile->numcolors < 256)
          {
            unsigned char* p = profile->palette;
            unsigned i = profile->numcolors;
            p[i * 4 + 0] = (unsigned char)r;
            p[i * 4 + 1] = (unsigned char)g;
            p[i * 4 + 2] = (unsigned char)b;
            p[i * 4 + 3] = (unsigned char)a;
          }
          profile->numcolors++;
          if(profile->numcolors >= profile->maxnumcolors) profile->numcolors_done = 1;
        }
      }

      if(profile->alpha_done && profile->numcolors_done
      && profile->colored_done && profile->sixteenbit_done && profile->greybits_done)
      {
        break;
      }
    };
  }
  else /* < 16-bit */
  {
    for(i = 0; i < numpixels; i++)
    {
      unsigned char r = 0, g = 0, b = 0, a = 0;
      error = getPixelColorRGBA8(&r, &g, &b, &a, in, i, mode, fix_png);
      if(error) break;

      if(!profile->colored_done && (r != g || r != b))
      {
        profile->colored = 1;
        profile->colored_done = 1;
        profile->greybits_done = 1; /*greybits is not applicable anymore*/
      }

      if(!profile->alpha_done && a != 255)
      {
        if(a == 0 && !(profile->key && (r != profile->key_r || g != profile->key_g || b != profile->key_b)))
        {
          if(!profile->key)
          {
            profile->key = 1;
            profile->key_r = r;
            profile->key_g = g;
            profile->key_b = b;
          }
        }
        else
        {
          profile->alpha = 1;
          profile->alpha_done = 1;
          profile->greybits_done = 1; /*greybits is not applicable anymore*/
        }
      }

      /* Color key cannot be used if an opaque pixel also has that RGB color. */
      if(!profile->alpha_done && a == 255 && profile->key
          && r == profile->key_r && g == profile->key_g && b == profile->key_b)
      {
          profile->alpha = 1;
          profile->alpha_done = 1;
          profile->greybits_done = 1; /*greybits is not applicable anymore*/
      }

      if(!profile->greybits_done)
      {
        unsigned bits = getValueRequiredBits(r);
        if(bits > profile->greybits) profile->greybits = bits;
        if(profile->greybits >= 8) profile->greybits_done = 1;
      }

      if(!profile->numcolors_done)
      {
        if(!color_tree_has(&profile->tree, r, g, b, a))
        {

          color_tree_add(&profile->tree, r, g, b, a, profile->numcolors);
          if(profile->numcolors < 256)
          {
            unsigned char* p = profile->palette;
            unsigned i = profile->numcolors;
            p[i * 4 + 0] = r;
            p[i * 4 + 1] = g;
            p[i * 4 + 2] = b;
            p[i * 4 + 3] = a;
          }
          profile->numcolors++;
          if(profile->numcolors >= profile->maxnumcolors) profile->numcolors_done = 1;
        }
      }

      if(profile->alpha_done && profile->numcolors_done && profile->colored_done && profile->greybits_done)
      {
        break;
      }
    };
  }

  /*make the profile's key always 16-bit for consistency*/
  if(mode->bitdepth < 16)
  {
    /*repeat each byte twice*/
    profile->key_r *= 257;
    profile->key_g *= 257;
    profile->key_b *= 257;
  }

  return error;
}

static void setColorKeyFrom16bit(LodePNGColorMode* mode_out, unsigned r, unsigned g, unsigned b, unsigned bitdepth)
{
  unsigned mask = (1 << bitdepth) - 1;
  mode_out->key_defined = 1;
  mode_out->key_r = r & mask;
  mode_out->key_g = g & mask;
  mode_out->key_b = b & mask;
}

/*updates values of mode with a potentially smaller color model. mode_out should
contain the user chosen color model, but will be overwritten with the new chosen one.*/
static unsigned doAutoChooseColor(LodePNGColorMode* mode_out,
                                  const unsigned char* image, unsigned w, unsigned h, LodePNGColorMode* mode_in,
                                  LodePNGAutoConvert auto_convert)
{
  ColorProfile profile;
  unsigned error = 0;
  int no_nibbles = auto_convert == LAC_AUTO_NO_NIBBLES || auto_convert == LAC_AUTO_NO_NIBBLES_NO_PALETTE;
  int no_palette = auto_convert == LAC_AUTO_NO_PALETTE || auto_convert == LAC_AUTO_NO_NIBBLES_NO_PALETTE;

  if(auto_convert == LAC_ALPHA)
  {
    if(mode_out->colortype != LCT_RGBA && mode_out->colortype != LCT_GREY_ALPHA) return 0;
  }

  color_profile_init(&profile, mode_in);
  if(auto_convert == LAC_ALPHA)
  {
    profile.colored_done = 1;
    profile.greybits_done = 1;
    profile.numcolors_done = 1;
    profile.sixteenbit_done = 1;
  }
  error = get_color_profile(&profile, image, w * h, mode_in, 0 /*fix_png*/);
  if(!error && auto_convert == LAC_ALPHA)
  {
    if(!profile.alpha)
    {
      mode_out->colortype = (mode_out->colortype == LCT_RGBA ? LCT_RGB : LCT_GREY);
      if(profile.key) setColorKeyFrom16bit(mode_out, profile.key_r, profile.key_g, profile.key_b, mode_out->bitdepth);
    }
  }
  else if(!error && auto_convert != LAC_ALPHA)
  {
    mode_out->key_defined = 0;

    if(profile.sixteenbit)
    {
      mode_out->bitdepth = 16;
      if(profile.alpha)
      {
        mode_out->colortype = profile.colored ? LCT_RGBA : LCT_GREY_ALPHA;
      }
      else
      {
        mode_out->colortype = profile.colored ? LCT_RGB : LCT_GREY;
        if(profile.key) setColorKeyFrom16bit(mode_out, profile.key_r, profile.key_g, profile.key_b, mode_out->bitdepth);
      }
    }
    else /*less than 16 bits per channel*/
    {
      /*don't add palette overhead if image hasn't got a lot of pixels*/
      unsigned n = profile.numcolors;
      int palette_ok = !no_palette && n <= 256 && (n * 2 < w * h);
      unsigned palettebits = n <= 2 ? 1 : (n <= 4 ? 2 : (n <= 16 ? 4 : 8));
      int grey_ok = !profile.colored && !profile.alpha; /*grey without alpha, with potentially low bits*/
      if(palette_ok || grey_ok)
      {
        if(!palette_ok || (grey_ok && profile.greybits <= palettebits))
        {
          unsigned grey = profile.key_r;
          mode_out->colortype = LCT_GREY;
          mode_out->bitdepth = profile.greybits;
          if(profile.key) setColorKeyFrom16bit(mode_out, grey, grey, grey, mode_out->bitdepth);
        }
        else
        {
          /*fill in the palette*/
          unsigned i;
          unsigned char* p = profile.palette;
          /*remove potential earlier palette*/
          lodepng_palette_clear(mode_out);
          for(i = 0; i < profile.numcolors; i++)
          {
            error = lodepng_palette_add(mode_out, p[i * 4 + 0], p[i * 4 + 1], p[i * 4 + 2], p[i * 4 + 3]);
            if(error) break;
          }

          mode_out->colortype = LCT_PALETTE;
          mode_out->bitdepth = palettebits;
        }
      }
      else /*8-bit per channel*/
      {
        mode_out->bitdepth = 8;
        if(profile.alpha)
        {
          mode_out->colortype = profile.colored ? LCT_RGBA : LCT_GREY_ALPHA;
        }
        else
        {
          mode_out->colortype = profile.colored ? LCT_RGB : LCT_GREY /*LCT_GREY normally won't occur, already done earlier*/;
          if(profile.key) setColorKeyFrom16bit(mode_out, profile.key_r, profile.key_g, profile.key_b, mode_out->bitdepth);
        }
      }
    }
  }

  color_profile_cleanup(&profile);

  if(mode_out->colortype == LCT_PALETTE && mode_in->palettesize == mode_out->palettesize)
  {
    /*In this case keep the palette order of the input, so that the user can choose an optimal one*/
    size_t i;
    for(i = 0; i < mode_in->palettesize * 4; i++)
    {
      mode_out->palette[i] = mode_in->palette[i];
    }
  }

  if(no_nibbles && mode_out->bitdepth < 8)
  {
    /*palette can keep its small amount of colors, as long as no indices use it*/
    mode_out->bitdepth = 8;
  }

  return error;
}

#endif /* #ifdef LODEPNG_COMPILE_ENCODER */

/*
Paeth predicter, used by PNG filter type 4
The parameters are of type short, but should come from unsigned chars, the shorts
are only needed to make the paeth calculation correct.
*/
static unsigned char paethPredictor(short a, short b, short c)
{
  short pa = abs(b - c);
  short pb = abs(a - c);
  short pc = abs(a + b - c - c);

  if(pc < pa && pc < pb) return (unsigned char)c;
  else if(pb < pa) return (unsigned char)b;
  else return (unsigned char)a;
}

/*shared values used by multiple Adam7 related functions*/

static const unsigned ADAM7_IX[7] = { 0, 4, 0, 2, 0, 1, 0 }; /*x start values*/
static const unsigned ADAM7_IY[7] = { 0, 0, 4, 0, 2, 0, 1 }; /*y start values*/
static const unsigned ADAM7_DX[7] = { 8, 8, 4, 4, 2, 2, 1 }; /*x delta values*/
static const unsigned ADAM7_DY[7] = { 8, 8, 8, 4, 4, 2, 2 }; /*y delta values*/

/*
Outputs various dimensions and positions in the image related to the Adam7 reduced images.
passw: output containing the width of the 7 passes
passh: output containing the height of the 7 passes
filter_passstart: output containing the index of the start and end of each
 reduced image with filter bytes
padded_passstart output containing the index of the start and end of each
 reduced image when without filter bytes but with padded scanlines
passstart: output containing the index of the start and end of each reduced
 image without padding between scanlines, but still padding between the images
w, h: width and height of non-interlaced image
bpp: bits per pixel
"padded" is only relevant if bpp is less than 8 and a scanline or image does not
 end at a full byte
*/
static void Adam7_getpassvalues(unsigned passw[7], unsigned passh[7], size_t filter_passstart[8],
                                size_t padded_passstart[8], size_t passstart[8], unsigned w, unsigned h, unsigned bpp)
{
  /*the passstart values have 8 values: the 8th one indicates the byte after the end of the 7th (= last) pass*/
  unsigned i;

  /*calculate width and height in pixels of each pass*/
  for(i = 0; i < 7; i++)
  {
    passw[i] = (w + ADAM7_DX[i] - ADAM7_IX[i] - 1) / ADAM7_DX[i];
    passh[i] = (h + ADAM7_DY[i] - ADAM7_IY[i] - 1) / ADAM7_DY[i];
    if(passw[i] == 0) passh[i] = 0;
    if(passh[i] == 0) passw[i] = 0;
  }

  filter_passstart[0] = padded_passstart[0] = passstart[0] = 0;
  for(i = 0; i < 7; i++)
  {
    /*if passw[i] is 0, it's 0 bytes, not 1 (no filtertype-byte)*/
    filter_passstart[i + 1] = filter_passstart[i]
                            + ((passw[i] && passh[i]) ? passh[i] * (1 + (passw[i] * bpp + 7) / 8) : 0);
    /*bits padded if needed to fill full byte at end of each scanline*/
    padded_passstart[i + 1] = padded_passstart[i] + passh[i] * ((passw[i] * bpp + 7) / 8);
    /*only padded at end of reduced image*/
    passstart[i + 1] = passstart[i] + (passh[i] * passw[i] * bpp + 7) / 8;
  }
}

#ifdef LODEPNG_COMPILE_DECODER

/* ////////////////////////////////////////////////////////////////////////// */
/* / PNG Decoder                                                            / */
/* ////////////////////////////////////////////////////////////////////////// */

/*read the information from the header and store it in the LodePNGInfo. return value is error*/
unsigned lodepng_inspect(unsigned* w, unsigned* h, LodePNGState* state,
                         const unsigned char* in, size_t insize)
{
  LodePNGInfo* info = &state->info_png;
  if(insize == 0 || in == 0)
  {
    CERROR_RETURN_ERROR(state->error, 48); /*error: the given data is empty*/
  }
  if(insize < 29)
  {
    CERROR_RETURN_ERROR(state->error, 27); /*error: the data length is smaller than the length of a PNG header*/
  }

  /*when decoding a new PNG image, make sure all parameters created after previous decoding are reset*/
  lodepng_info_cleanup(info);
  lodepng_info_init(info);

  if(in[0] != 137 || in[1] != 80 || in[2] != 78 || in[3] != 71
     || in[4] != 13 || in[5] != 10 || in[6] != 26 || in[7] != 10)
  {
    CERROR_RETURN_ERROR(state->error, 28); /*error: the first 8 bytes are not the correct PNG signature*/
  }
  if(in[12] != 'I' || in[13] != 'H' || in[14] != 'D' || in[15] != 'R')
  {
    CERROR_RETURN_ERROR(state->error, 29); /*error: it doesn't start with a IHDR chunk!*/
  }

  /*read the values given in the header*/
  *w = lodepng_read32bitInt(&in[16]);
  *h = lodepng_read32bitInt(&in[20]);
  info->color.bitdepth = in[24];
  info->color.colortype = (LodePNGColorType)in[25];
  info->compression_method = in[26];
  info->filter_method = in[27];
  info->interlace_method = in[28];

  if(!state->decoder.ignore_crc)
  {
    unsigned CRC = lodepng_read32bitInt(&in[29]);
    unsigned checksum = lodepng_crc32(&in[12], 17);
    if(CRC != checksum)
    {
      CERROR_RETURN_ERROR(state->error, 57); /*invalid CRC*/
    }
  }

  /*error: only compression method 0 is allowed in the specification*/
  if(info->compression_method != 0) CERROR_RETURN_ERROR(state->error, 32);
  /*error: only filter method 0 is allowed in the specification*/
  if(info->filter_method != 0) CERROR_RETURN_ERROR(state->error, 33);
  /*error: only interlace methods 0 and 1 exist in the specification*/
  if(info->interlace_method > 1) CERROR_RETURN_ERROR(state->error, 34);

  state->error = checkColorValidity(info->color.colortype, info->color.bitdepth);
  return state->error;
}

static unsigned unfilterScanline(unsigned char* recon, const unsigned char* scanline, const unsigned char* precon,
                                 size_t bytewidth, unsigned char filterType, size_t length)
{
  /*
  For PNG filter method 0
  unfilter a PNG image scanline by scanline. when the pixels are smaller than 1 byte,
  the filter works byte per byte (bytewidth = 1)
  precon is the previous unfiltered scanline, recon the result, scanline the current one
  the incoming scanlines do NOT include the filtertype byte, that one is given in the parameter filterType instead
  recon and scanline MAY be the same memory address! precon must be disjoint.
  */

  size_t i;
  switch(filterType)
  {
    case 0:
      for(i = 0; i < length; i++) recon[i] = scanline[i];
      break;
    case 1:
      for(i = 0; i < bytewidth; i++) recon[i] = scanline[i];
      for(i = bytewidth; i < length; i++) recon[i] = scanline[i] + recon[i - bytewidth];
      break;
    case 2:
      if(precon)
      {
        for(i = 0; i < length; i++) recon[i] = scanline[i] + precon[i];
      }
      else
      {
        for(i = 0; i < length; i++) recon[i] = scanline[i];
      }
      break;
    case 3:
      if(precon)
      {
        for(i = 0; i < bytewidth; i++) recon[i] = scanline[i] + precon[i] / 2;
        for(i = bytewidth; i < length; i++) recon[i] = scanline[i] + ((recon[i - bytewidth] + precon[i]) / 2);
      }
      else
      {
        for(i = 0; i < bytewidth; i++) recon[i] = scanline[i];
        for(i = bytewidth; i < length; i++) recon[i] = scanline[i] + recon[i - bytewidth] / 2;
      }
      break;
    case 4:
      if(precon)
      {
        for(i = 0; i < bytewidth; i++)
        {
          recon[i] = (scanline[i] + precon[i]); /*paethPredictor(0, precon[i], 0) is always precon[i]*/
        }
        for(i = bytewidth; i < length; i++)
        {
          recon[i] = (scanline[i] + paethPredictor(recon[i - bytewidth], precon[i], precon[i - bytewidth]));
        }
      }
      else
      {
        for(i = 0; i < bytewidth; i++)
        {
          recon[i] = scanline[i];
        }
        for(i = bytewidth; i < length; i++)
        {
          /*paethPredictor(recon[i - bytewidth], 0, 0) is always recon[i - bytewidth]*/
          recon[i] = (scanline[i] + recon[i - bytewidth]);
        }
      }
      break;
    default: return 36; /*error: unexisting filter type given*/
  }
  return 0;
}

static unsigned unfilter(unsigned char* out, const unsigned char* in, unsigned w, unsigned h, unsigned bpp)
{
  /*
  For PNG filter method 0
  this function unfilters a single image (e.g. without interlacing this is called once, with Adam7 seven times)
  out must have enough bytes allocated already, in must have the scanlines + 1 filtertype byte per scanline
  w and h are image dimensions or dimensions of reduced image, bpp is bits per pixel
  in and out are allowed to be the same memory address (but aren't the same size since in has the extra filter bytes)
  */

  unsigned y;
  unsigned char* prevline = 0;

  /*bytewidth is used for filtering, is 1 when bpp < 8, number of bytes per pixel otherwise*/
  size_t bytewidth = (bpp + 7) / 8;
  size_t linebytes = (w * bpp + 7) / 8;

  for(y = 0; y < h; y++)
  {
    size_t outindex = linebytes * y;
    size_t inindex = (1 + linebytes) * y; /*the extra filterbyte added to each row*/
    unsigned char filterType = in[inindex];

    CERROR_TRY_RETURN(unfilterScanline(&out[outindex], &in[inindex + 1], prevline, bytewidth, filterType, linebytes));

    prevline = &out[outindex];
  }

  return 0;
}

/*
in: Adam7 interlaced image, with no padding bits between scanlines, but between
 reduced images so that each reduced image starts at a byte.
out: the same pixels, but re-ordered so that they're now a non-interlaced image with size w*h
bpp: bits per pixel
out has the following size in bits: w * h * bpp.
in is possibly bigger due to padding bits between reduced images.
out must be big enough AND must be 0 everywhere if bpp < 8 in the current implementation
(because that's likely a little bit faster)
NOTE: comments about padding bits are only relevant if bpp < 8
*/
static void Adam7_deinterlace(unsigned char* out, const unsigned char* in, unsigned w, unsigned h, unsigned bpp)
{
  unsigned passw[7], passh[7];
  size_t filter_passstart[8], padded_passstart[8], passstart[8];
  unsigned i;

  Adam7_getpassvalues(passw, passh, filter_passstart, padded_passstart, passstart, w, h, bpp);

  if(bpp >= 8)
  {
    for(i = 0; i < 7; i++)
    {
      unsigned x, y, b;
      size_t bytewidth = bpp / 8;
      for(y = 0; y < passh[i]; y++)
      for(x = 0; x < passw[i]; x++)
      {
        size_t pixelinstart = passstart[i] + (y * passw[i] + x) * bytewidth;
        size_t pixeloutstart = ((ADAM7_IY[i] + y * ADAM7_DY[i]) * w + ADAM7_IX[i] + x * ADAM7_DX[i]) * bytewidth;
        for(b = 0; b < bytewidth; b++)
        {
          out[pixeloutstart + b] = in[pixelinstart + b];
        }
      }
    }
  }
  else /*bpp < 8: Adam7 with pixels < 8 bit is a bit trickier: with bit pointers*/
  {
    for(i = 0; i < 7; i++)
    {
      unsigned x, y, b;
      unsigned ilinebits = bpp * passw[i];
      unsigned olinebits = bpp * w;
      size_t obp, ibp; /*bit pointers (for out and in buffer)*/
      for(y = 0; y < passh[i]; y++)
      for(x = 0; x < passw[i]; x++)
      {
        ibp = (8 * passstart[i]) + (y * ilinebits + x * bpp);
        obp = (ADAM7_IY[i] + y * ADAM7_DY[i]) * olinebits + (ADAM7_IX[i] + x * ADAM7_DX[i]) * bpp;
        for(b = 0; b < bpp; b++)
        {
          unsigned char bit = readBitFromReversedStream(&ibp, in);
          /*note that this function assumes the out buffer is completely 0, use setBitOfReversedStream otherwise*/
          setBitOfReversedStream0(&obp, out, bit);
        }
      }
    }
  }
}

static void removePaddingBits(unsigned char* out, const unsigned char* in,
                              size_t olinebits, size_t ilinebits, unsigned h)
{
  /*
  After filtering there are still padding bits if scanlines have non multiple of 8 bit amounts. They need
  to be removed (except at last scanline of (Adam7-reduced) image) before working with pure image buffers
  for the Adam7 code, the color convert code and the output to the user.
  in and out are allowed to be the same buffer, in may also be higher but still overlapping; in must
  have >= ilinebits*h bits, out must have >= olinebits*h bits, olinebits must be <= ilinebits
  also used to move bits after earlier such operations happened, e.g. in a sequence of reduced images from Adam7
  only useful if (ilinebits - olinebits) is a value in the range 1..7
  */
  unsigned y;
  size_t diff = ilinebits - olinebits;
  size_t ibp = 0, obp = 0; /*input and output bit pointers*/
  for(y = 0; y < h; y++)
  {
    size_t x;
    for(x = 0; x < olinebits; x++)
    {
      unsigned char bit = readBitFromReversedStream(&ibp, in);
      setBitOfReversedStream(&obp, out, bit);
    }
    ibp += diff;
  }
}

/*out must be buffer big enough to contain full image, and in must contain the full decompressed data from
the IDAT chunks (with filter index bytes and possible padding bits)
return value is error*/
static unsigned postProcessScanlines(unsigned char* out, unsigned char* in,
                                     unsigned w, unsigned h, const LodePNGInfo* info_png)
{
  /*
  This function converts the filtered-padded-interlaced data into pure 2D image buffer with the PNG's colortype.
  Steps:
  *) if no Adam7: 1) unfilter 2) remove padding bits (= posible extra bits per scanline if bpp < 8)
  *) if adam7: 1) 7x unfilter 2) 7x remove padding bits 3) Adam7_deinterlace
  NOTE: the in buffer will be overwritten with intermediate data!
  */
  unsigned bpp = lodepng_get_bpp(&info_png->color);
  if(bpp == 0) return 31; /*error: invalid colortype*/

  if(info_png->interlace_method == 0)
  {
    if(bpp < 8 && w * bpp != ((w * bpp + 7) / 8) * 8)
    {
      CERROR_TRY_RETURN(unfilter(in, in, w, h, bpp));
      removePaddingBits(out, in, w * bpp, ((w * bpp + 7) / 8) * 8, h);
    }
    /*we can immediatly filter into the out buffer, no other steps needed*/
    else CERROR_TRY_RETURN(unfilter(out, in, w, h, bpp));
  }
  else /*interlace_method is 1 (Adam7)*/
  {
    unsigned passw[7], passh[7]; size_t filter_passstart[8], padded_passstart[8], passstart[8];
    unsigned i;

    Adam7_getpassvalues(passw, passh, filter_passstart, padded_passstart, passstart, w, h, bpp);

    for(i = 0; i < 7; i++)
    {
      CERROR_TRY_RETURN(unfilter(&in[padded_passstart[i]], &in[filter_passstart[i]], passw[i], passh[i], bpp));
      /*TODO: possible efficiency improvement: if in this reduced image the bits fit nicely in 1 scanline,
      move bytes instead of bits or move not at all*/
      if(bpp < 8)
      {
        /*remove padding bits in scanlines; after this there still may be padding
        bits between the different reduced images: each reduced image still starts nicely at a byte*/
        removePaddingBits(&in[passstart[i]], &in[padded_passstart[i]], passw[i] * bpp,
                          ((passw[i] * bpp + 7) / 8) * 8, passh[i]);
      }
    }

    Adam7_deinterlace(out, in, w, h, bpp);
  }

  return 0;
}

static unsigned readChunk_PLTE(LodePNGColorMode* color, const unsigned char* data, size_t chunkLength)
{
  unsigned pos = 0, i;
  if(color->palette) lodepng_free(color->palette);
  color->palettesize = chunkLength / 3;
  color->palette = (unsigned char*)lodepng_malloc(4 * color->palettesize);
  if(!color->palette && color->palettesize)
  {
    color->palettesize = 0;
    return 83; /*alloc fail*/
  }
  if(color->palettesize > 256) return 38; /*error: palette too big*/

  for(i = 0; i < color->palettesize; i++)
  {
    color->palette[4 * i + 0] = data[pos++]; /*R*/
    color->palette[4 * i + 1] = data[pos++]; /*G*/
    color->palette[4 * i + 2] = data[pos++]; /*B*/
    color->palette[4 * i + 3] = 255; /*alpha*/
  }

  return 0; /* OK */
}

static unsigned readChunk_tRNS(LodePNGColorMode* color, const unsigned char* data, size_t chunkLength)
{
  unsigned i;
  if(color->colortype == LCT_PALETTE)
  {
    /*error: more alpha values given than there are palette entries*/
    if(chunkLength > color->palettesize) return 38;

    for(i = 0; i < chunkLength; i++) color->palette[4 * i + 3] = data[i];
  }
  else if(color->colortype == LCT_GREY)
  {
    /*error: this chunk must be 2 bytes for greyscale image*/
    if(chunkLength != 2) return 30;

    color->key_defined = 1;
    color->key_r = color->key_g = color->key_b = 256 * data[0] + data[1];
  }
  else if(color->colortype == LCT_RGB)
  {
    /*error: this chunk must be 6 bytes for RGB image*/
    if(chunkLength != 6) return 41;

    color->key_defined = 1;
    color->key_r = 256 * data[0] + data[1];
    color->key_g = 256 * data[2] + data[3];
    color->key_b = 256 * data[4] + data[5];
  }
  else return 42; /*error: tRNS chunk not allowed for other color models*/

  return 0; /* OK */
}


#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
/*background color chunk (bKGD)*/
static unsigned readChunk_bKGD(LodePNGInfo* info, const unsigned char* data, size_t chunkLength)
{
  if(info->color.colortype == LCT_PALETTE)
  {
    /*error: this chunk must be 1 byte for indexed color image*/
    if(chunkLength != 1) return 43;

    info->background_defined = 1;
    info->background_r = info->background_g = info->background_b = data[0];
  }
  else if(info->color.colortype == LCT_GREY || info->color.colortype == LCT_GREY_ALPHA)
  {
    /*error: this chunk must be 2 bytes for greyscale image*/
    if(chunkLength != 2) return 44;

    info->background_defined = 1;
    info->background_r = info->background_g = info->background_b
                                 = 256 * data[0] + data[1];
  }
  else if(info->color.colortype == LCT_RGB || info->color.colortype == LCT_RGBA)
  {
    /*error: this chunk must be 6 bytes for greyscale image*/
    if(chunkLength != 6) return 45;

    info->background_defined = 1;
    info->background_r = 256 * data[0] + data[1];
    info->background_g = 256 * data[2] + data[3];
    info->background_b = 256 * data[4] + data[5];
  }

  return 0; /* OK */
}

/*text chunk (tEXt)*/
static unsigned readChunk_tEXt(LodePNGInfo* info, const unsigned char* data, size_t chunkLength)
{
  unsigned error = 0;
  char *key = 0, *str = 0;
  unsigned i;

  while(!error) /*not really a while loop, only used to break on error*/
  {
    unsigned length, string2_begin;

    length = 0;
    while(length < chunkLength && data[length] != 0) length++;
    /*even though it's not allowed by the standard, no error is thrown if
    there's no null termination char, if the text is empty*/
    if(length < 1 || length > 79) CERROR_BREAK(error, 89); /*keyword too short or long*/

    key = (char*)lodepng_malloc(length + 1);
    if(!key) CERROR_BREAK(error, 83); /*alloc fail*/

    key[length] = 0;
    for(i = 0; i < length; i++) key[i] = data[i];

    string2_begin = length + 1; /*skip keyword null terminator*/

    length = chunkLength < string2_begin ? 0 : chunkLength - string2_begin;
    str = (char*)lodepng_malloc(length + 1);
    if(!str) CERROR_BREAK(error, 83); /*alloc fail*/

    str[length] = 0;
    for(i = 0; i < length; i++) str[i] = data[string2_begin + i];

    error = lodepng_add_text(info, key, str);

    break;
  }

  lodepng_free(key);
  lodepng_free(str);

  return error;
}

/*compressed text chunk (zTXt)*/
static unsigned readChunk_zTXt(LodePNGInfo* info, const LodePNGDecompressSettings* zlibsettings,
                               const unsigned char* data, size_t chunkLength)
{
  unsigned error = 0;
  unsigned i;

  unsigned length, string2_begin;
  char *key = 0;
  ucvector decoded;

  ucvector_init(&decoded);

  while(!error) /*not really a while loop, only used to break on error*/
  {
    for(length = 0; length < chunkLength && data[length] != 0; length++) ;
    if(length + 2 >= chunkLength) CERROR_BREAK(error, 75); /*no null termination, corrupt?*/
    if(length < 1 || length > 79) CERROR_BREAK(error, 89); /*keyword too short or long*/

    key = (char*)lodepng_malloc(length + 1);
    if(!key) CERROR_BREAK(error, 83); /*alloc fail*/

    key[length] = 0;
    for(i = 0; i < length; i++) key[i] = data[i];

    if(data[length + 1] != 0) CERROR_BREAK(error, 72); /*the 0 byte indicating compression must be 0*/

    string2_begin = length + 2;
    if(string2_begin > chunkLength) CERROR_BREAK(error, 75); /*no null termination, corrupt?*/

    length = chunkLength - string2_begin;
    /*will fail if zlib error, e.g. if length is too small*/
    error = zlib_decompress(&decoded.data, &decoded.size,
                            (unsigned char*)(&data[string2_begin]),
                            length, zlibsettings);
    if(error) break;
    ucvector_push_back(&decoded, 0);

    error = lodepng_add_text(info, key, (char*)decoded.data);

    break;
  }

  lodepng_free(key);
  ucvector_cleanup(&decoded);

  return error;
}

/*international text chunk (iTXt)*/
static unsigned readChunk_iTXt(LodePNGInfo* info, const LodePNGDecompressSettings* zlibsettings,
                               const unsigned char* data, size_t chunkLength)
{
  unsigned error = 0;
  unsigned i;

  unsigned length, begin, compressed;
  char *key = 0, *langtag = 0, *transkey = 0;
  ucvector decoded;
  ucvector_init(&decoded);

  while(!error) /*not really a while loop, only used to break on error*/
  {
    /*Quick check if the chunk length isn't too small. Even without check
    it'd still fail with other error checks below if it's too short. This just gives a different error code.*/
    if(chunkLength < 5) CERROR_BREAK(error, 30); /*iTXt chunk too short*/

    /*read the key*/
    for(length = 0; length < chunkLength && data[length] != 0; length++) ;
    if(length + 3 >= chunkLength) CERROR_BREAK(error, 75); /*no null termination char, corrupt?*/
    if(length < 1 || length > 79) CERROR_BREAK(error, 89); /*keyword too short or long*/

    key = (char*)lodepng_malloc(length + 1);
    if(!key) CERROR_BREAK(error, 83); /*alloc fail*/

    key[length] = 0;
    for(i = 0; i < length; i++) key[i] = data[i];

    /*read the compression method*/
    compressed = data[length + 1];
    if(data[length + 2] != 0) CERROR_BREAK(error, 72); /*the 0 byte indicating compression must be 0*/

    /*even though it's not allowed by the standard, no error is thrown if
    there's no null termination char, if the text is empty for the next 3 texts*/

    /*read the langtag*/
    begin = length + 3;
    length = 0;
    for(i = begin; i < chunkLength && data[i] != 0; i++) length++;

    langtag = (char*)lodepng_malloc(length + 1);
    if(!langtag) CERROR_BREAK(error, 83); /*alloc fail*/

    langtag[length] = 0;
    for(i = 0; i < length; i++) langtag[i] = data[begin + i];

    /*read the transkey*/
    begin += length + 1;
    length = 0;
    for(i = begin; i < chunkLength && data[i] != 0; i++) length++;

    transkey = (char*)lodepng_malloc(length + 1);
    if(!transkey) CERROR_BREAK(error, 83); /*alloc fail*/

    transkey[length] = 0;
    for(i = 0; i < length; i++) transkey[i] = data[begin + i];

    /*read the actual text*/
    begin += length + 1;

    length = chunkLength < begin ? 0 : chunkLength - begin;

    if(compressed)
    {
      /*will fail if zlib error, e.g. if length is too small*/
      error = zlib_decompress(&decoded.data, &decoded.size,
                              (unsigned char*)(&data[begin]),
                              length, zlibsettings);
      if(error) break;
      if(decoded.allocsize < decoded.size) decoded.allocsize = decoded.size;
      ucvector_push_back(&decoded, 0);
    }
    else
    {
      if(!ucvector_resize(&decoded, length + 1)) CERROR_BREAK(error, 83 /*alloc fail*/);

      decoded.data[length] = 0;
      for(i = 0; i < length; i++) decoded.data[i] = data[begin + i];
    }

    error = lodepng_add_itext(info, key, langtag, transkey, (char*)decoded.data);

    break;
  }

  lodepng_free(key);
  lodepng_free(langtag);
  lodepng_free(transkey);
  ucvector_cleanup(&decoded);

  return error;
}

static unsigned readChunk_tIME(LodePNGInfo* info, const unsigned char* data, size_t chunkLength)
{
  if(chunkLength != 7) return 73; /*invalid tIME chunk size*/

  info->time_defined = 1;
  info->time.year = 256 * data[0] + data[+ 1];
  info->time.month = data[2];
  info->time.day = data[3];
  info->time.hour = data[4];
  info->time.minute = data[5];
  info->time.second = data[6];

  return 0; /* OK */
}

static unsigned readChunk_pHYs(LodePNGInfo* info, const unsigned char* data, size_t chunkLength)
{
  if(chunkLength != 9) return 74; /*invalid pHYs chunk size*/

  info->phys_defined = 1;
  info->phys_x = 16777216 * data[0] + 65536 * data[1] + 256 * data[2] + data[3];
  info->phys_y = 16777216 * data[4] + 65536 * data[5] + 256 * data[6] + data[7];
  info->phys_unit = data[8];

  return 0; /* OK */
}
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/

/*read a PNG, the result will be in the same color type as the PNG (hence "generic")*/
static void decodeGeneric(unsigned char** out, unsigned* w, unsigned* h,
                          LodePNGState* state,
                          const unsigned char* in, size_t insize)
{
  unsigned char IEND = 0;
  const unsigned char* chunk;
  size_t i;
  ucvector idat; /*the data from idat chunks*/

  /*for unknown chunk order*/
  unsigned unknown = 0;
#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
  unsigned critical_pos = 1; /*1 = after IHDR, 2 = after PLTE, 3 = after IDAT*/
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/

  /*provide some proper output values if error will happen*/
  //*out = 0;

  state->error = lodepng_inspect(w, h, state, in, insize); /*reads header and resets other parameters in state->info_png*/
  if(state->error) return;

  ucvector_init(&idat);
  chunk = &in[33]; /*first byte of the first chunk after the header*/

  /*loop through the chunks, ignoring unknown chunks and stopping at IEND chunk.
  IDAT data is put at the start of the in buffer*/
  while(!IEND && !state->error)
  {
    unsigned chunkLength;
    const unsigned char* data; /*the data in the chunk*/

    /*error: size of the in buffer too small to contain next chunk*/
    if((size_t)((chunk - in) + 12) > insize || chunk < in) CERROR_BREAK(state->error, 30);

    /*length of the data of the chunk, excluding the length bytes, chunk type and CRC bytes*/
    chunkLength = lodepng_chunk_length(chunk);
    /*error: chunk length larger than the max PNG chunk size*/
    if(chunkLength > 2147483647) CERROR_BREAK(state->error, 63);

    if((size_t)((chunk - in) + chunkLength + 12) > insize || (chunk + chunkLength + 12) < in)
    {
      CERROR_BREAK(state->error, 64); /*error: size of the in buffer too small to contain next chunk*/
    }

    data = lodepng_chunk_data_const(chunk);

    /*IDAT chunk, containing compressed image data*/
    if(lodepng_chunk_type_equals(chunk, "IDAT"))
    {
      size_t oldsize = idat.size;
      if(!ucvector_resize(&idat, oldsize + chunkLength)) CERROR_BREAK(state->error, 83 /*alloc fail*/);
      for(i = 0; i < chunkLength; i++) idat.data[oldsize + i] = data[i];
#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
      critical_pos = 3;
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
    }
    /*IEND chunk*/
    else if(lodepng_chunk_type_equals(chunk, "IEND"))
    {
      IEND = 1;
    }
    /*palette chunk (PLTE)*/
    else if(lodepng_chunk_type_equals(chunk, "PLTE"))
    {
      state->error = readChunk_PLTE(&state->info_png.color, data, chunkLength);
      if(state->error) break;
#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
      critical_pos = 2;
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
    }
    /*palette transparency chunk (tRNS)*/
    else if(lodepng_chunk_type_equals(chunk, "tRNS"))
    {
      state->error = readChunk_tRNS(&state->info_png.color, data, chunkLength);
      if(state->error) break;
    }
#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
    /*background color chunk (bKGD)*/
    else if(lodepng_chunk_type_equals(chunk, "bKGD"))
    {
      state->error = readChunk_bKGD(&state->info_png, data, chunkLength);
      if(state->error) break;
    }
    /*text chunk (tEXt)*/
    else if(lodepng_chunk_type_equals(chunk, "tEXt"))
    {
      if(state->decoder.read_text_chunks)
      {
        state->error = readChunk_tEXt(&state->info_png, data, chunkLength);
        if(state->error) break;
      }
    }
    /*compressed text chunk (zTXt)*/
    else if(lodepng_chunk_type_equals(chunk, "zTXt"))
    {
      if(state->decoder.read_text_chunks)
      {
        state->error = readChunk_zTXt(&state->info_png, &state->decoder.zlibsettings, data, chunkLength);
        if(state->error) break;
      }
    }
    /*international text chunk (iTXt)*/
    else if(lodepng_chunk_type_equals(chunk, "iTXt"))
    {
      if(state->decoder.read_text_chunks)
      {
        state->error = readChunk_iTXt(&state->info_png, &state->decoder.zlibsettings, data, chunkLength);
        if(state->error) break;
      }
    }
    else if(lodepng_chunk_type_equals(chunk, "tIME"))
    {
      state->error = readChunk_tIME(&state->info_png, data, chunkLength);
      if(state->error) break;
    }
    else if(lodepng_chunk_type_equals(chunk, "pHYs"))
    {
      state->error = readChunk_pHYs(&state->info_png, data, chunkLength);
      if(state->error) break;
    }
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
    else /*it's not an implemented chunk type, so ignore it: skip over the data*/
    {
      /*error: unknown critical chunk (5th bit of first byte of chunk type is 0)*/
      if(!lodepng_chunk_ancillary(chunk)) CERROR_BREAK(state->error, 69);

      unknown = 1;
#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
      if(state->decoder.remember_unknown_chunks)
      {
        state->error = lodepng_chunk_append(&state->info_png.unknown_chunks_data[critical_pos - 1],
                                            &state->info_png.unknown_chunks_size[critical_pos - 1], chunk);
        if(state->error) break;
      }
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
    }

    if(!state->decoder.ignore_crc && !unknown) /*check CRC if wanted, only on known chunk types*/
    {
      if(lodepng_chunk_check_crc(chunk)) CERROR_BREAK(state->error, 57); /*invalid CRC*/
    }

    if(!IEND) chunk = lodepng_chunk_next_const(chunk);
  }

  if(!state->error)
  {
    ucvector scanlines;
    ucvector_init(&scanlines);

    /*maximum final image length is already reserved in the vector's length - this is not really necessary*/
    if(!ucvector_resize(&scanlines, lodepng_get_raw_size(*w, *h, &state->info_png.color) + *h))
    {
      state->error = 83; /*alloc fail*/
    }
    if(!state->error)
    {
      /*decompress with the Zlib decompressor*/
      state->error = zlib_decompress(&scanlines.data, &scanlines.size, idat.data,
                                     idat.size, &state->decoder.zlibsettings);
    }

    if(!state->error)
    {

      /*
      ucvector outv;
      ucvector_init(&outv);
      if(!ucvector_resizev(&outv,
          lodepng_get_raw_size(*w, *h, &state->info_png.color), 0)  ){
          state->error = 83; //alloc fail
      }
      if(!state->error) {
        state->error = postProcessScanlines(outv.data, scanlines.data, *w, *h, &state->info_png);
      }
      //*out = outv.data;
      */
      state->error = postProcessScanlines(*out, scanlines.data, *w, *h, &state->info_png);
    }
    ucvector_cleanup(&scanlines);
  }

  ucvector_cleanup(&idat);
}

unsigned lodepng_decode(unsigned char** out, unsigned* w, unsigned* h,
                        LodePNGState* state,
                        const unsigned char* in, size_t insize)
{
  //*out = 0;
  decodeGeneric(out, w, h, state, in, insize);
  if(state->error) return state->error;
  if(!state->decoder.color_convert || lodepng_color_mode_equal(&state->info_raw, &state->info_png.color))
  {
    /*same color type, no copying or converting of data needed*/
    /*store the info_png color settings on the info_raw so that the info_raw still reflects what colortype
    the raw image has to the end user*/
    if(!state->decoder.color_convert)
    {
      state->error = lodepng_color_mode_copy(&state->info_raw, &state->info_png.color);
      if(state->error) return state->error;
    }
  }
  else
  {
    /*color conversion needed; sort of copy of the data*/
    unsigned char* data = *out;
    size_t outsize;

    /*TODO: check if this works according to the statement in the documentation: "The converter can convert
    from greyscale input color type, to 8-bit greyscale or greyscale with alpha"*/
    if(!(state->info_raw.colortype == LCT_RGB || state->info_raw.colortype == LCT_RGBA)
       && !(state->info_raw.bitdepth == 8))
    {
      return 56; /*unsupported color mode conversion*/
    }

    outsize = lodepng_get_raw_size(*w, *h, &state->info_raw);
    //*out = (unsigned char*)lodepng_malloc(outsize);
    if(!(*out))
    {
      state->error = 83; /*alloc fail*/
    }
    else state->error = lodepng_convert(*out, data, &state->info_raw, &state->info_png.color, *w, *h, state->decoder.fix_png);
    lodepng_free(data);
  }
  return state->error;
}

unsigned lodepng_decode_memory(unsigned char** out, unsigned* w, unsigned* h, const unsigned char* in,
                               size_t insize, LodePNGColorType colortype, unsigned bitdepth)
{
  unsigned error;
  LodePNGState state;
  lodepng_state_init(&state);
  state.info_raw.colortype = colortype;
  state.info_raw.bitdepth = bitdepth;
  error = lodepng_decode(out, w, h, &state, in, insize);
  lodepng_state_cleanup(&state);
  return error;
}

unsigned lodepng_decode32(unsigned char** out, unsigned* w, unsigned* h, const unsigned char* in, size_t insize)
{
  return lodepng_decode_memory(out, w, h, in, insize, LCT_RGBA, 8);
}

unsigned lodepng_decode24(unsigned char** out, unsigned* w, unsigned* h, const unsigned char* in, size_t insize)
{
  return lodepng_decode_memory(out, w, h, in, insize, LCT_RGB, 8);
}

#ifdef LODEPNG_COMPILE_DISK
unsigned lodepng_decode_file(unsigned char** out, unsigned* w, unsigned* h, const char* filename,
                             LodePNGColorType colortype, unsigned bitdepth)
{
  unsigned char* buffer;
  size_t buffersize;
  unsigned error;
  error = lodepng_load_file(&buffer, &buffersize, filename);
  if(!error) error = lodepng_decode_memory(out, w, h, buffer, buffersize, colortype, bitdepth);
  lodepng_free(buffer);
  return error;
}

unsigned lodepng_decode32_file(unsigned char** out, unsigned* w, unsigned* h, const char* filename)
{
  return lodepng_decode_file(out, w, h, filename, LCT_RGBA, 8);
}

unsigned lodepng_decode24_file(unsigned char** out, unsigned* w, unsigned* h, const char* filename)
{
  return lodepng_decode_file(out, w, h, filename, LCT_RGB, 8);
}
#endif /*LODEPNG_COMPILE_DISK*/

void lodepng_decoder_settings_init(LodePNGDecoderSettings* settings)
{
  settings->color_convert = 1;
#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
  settings->read_text_chunks = 1;
  settings->remember_unknown_chunks = 0;
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
  settings->ignore_crc = 0;
  settings->fix_png = 0;
  lodepng_decompress_settings_init(&settings->zlibsettings);
}

#endif /*LODEPNG_COMPILE_DECODER*/

#if defined(LODEPNG_COMPILE_DECODER) || defined(LODEPNG_COMPILE_ENCODER)

void lodepng_state_init(LodePNGState* state)
{
#ifdef LODEPNG_COMPILE_DECODER
  lodepng_decoder_settings_init(&state->decoder);
#endif /*LODEPNG_COMPILE_DECODER*/
#ifdef LODEPNG_COMPILE_ENCODER
  lodepng_encoder_settings_init(&state->encoder);
#endif /*LODEPNG_COMPILE_ENCODER*/
  lodepng_color_mode_init(&state->info_raw);
  lodepng_info_init(&state->info_png);
  state->error = 1;
}

void lodepng_state_cleanup(LodePNGState* state)
{
  lodepng_color_mode_cleanup(&state->info_raw);
  lodepng_info_cleanup(&state->info_png);
}

void lodepng_state_copy(LodePNGState* dest, const LodePNGState* source)
{
  lodepng_state_cleanup(dest);
  *dest = *source;
  lodepng_color_mode_init(&dest->info_raw);
  lodepng_info_init(&dest->info_png);
  dest->error = lodepng_color_mode_copy(&dest->info_raw, &source->info_raw); if(dest->error) return;
  dest->error = lodepng_info_copy(&dest->info_png, &source->info_png); if(dest->error) return;
}

#endif /* defined(LODEPNG_COMPILE_DECODER) || defined(LODEPNG_COMPILE_ENCODER) */

#ifdef LODEPNG_COMPILE_ENCODER

/* ////////////////////////////////////////////////////////////////////////// */
/* / PNG Encoder                                                            / */
/* ////////////////////////////////////////////////////////////////////////// */

/*chunkName must be string of 4 characters*/
static unsigned addChunk(ucvector* out, const char* chunkName, const unsigned char* data, size_t length)
{
  CERROR_TRY_RETURN(lodepng_chunk_create(&out->data, &out->size, (unsigned)length, chunkName, data));
  out->allocsize = out->size; /*fix the allocsize again*/
  return 0;
}

static void writeSignature(ucvector* out)
{
  /*8 bytes PNG signature, aka the magic bytes*/
  ucvector_push_back(out, 137);
  ucvector_push_back(out, 80);
  ucvector_push_back(out, 78);
  ucvector_push_back(out, 71);
  ucvector_push_back(out, 13);
  ucvector_push_back(out, 10);
  ucvector_push_back(out, 26);
  ucvector_push_back(out, 10);
}

static unsigned addChunk_IHDR(ucvector* out, unsigned w, unsigned h,
                              LodePNGColorType colortype, unsigned bitdepth, unsigned interlace_method)
{
  unsigned error = 0;
  ucvector header;
  ucvector_init(&header);

  lodepng_add32bitInt(&header, w); /*width*/
  lodepng_add32bitInt(&header, h); /*height*/
  ucvector_push_back(&header, (unsigned char)bitdepth); /*bit depth*/
  ucvector_push_back(&header, (unsigned char)colortype); /*color type*/
  ucvector_push_back(&header, 0); /*compression method*/
  ucvector_push_back(&header, 0); /*filter method*/
  ucvector_push_back(&header, interlace_method); /*interlace method*/

  error = addChunk(out, "IHDR", header.data, header.size);
  ucvector_cleanup(&header);

  return error;
}

static unsigned addChunk_PLTE(ucvector* out, const LodePNGColorMode* info)
{
  unsigned error = 0;
  size_t i;
  ucvector PLTE;
  ucvector_init(&PLTE);
  for(i = 0; i < info->palettesize * 4; i++)
  {
    /*add all channels except alpha channel*/
    if(i % 4 != 3) ucvector_push_back(&PLTE, info->palette[i]);
  }
  error = addChunk(out, "PLTE", PLTE.data, PLTE.size);
  ucvector_cleanup(&PLTE);

  return error;
}

static unsigned addChunk_tRNS(ucvector* out, const LodePNGColorMode* info)
{
  unsigned error = 0;
  size_t i;
  ucvector tRNS;
  ucvector_init(&tRNS);
  if(info->colortype == LCT_PALETTE)
  {
    size_t amount = info->palettesize;
    /*the tail of palette values that all have 255 as alpha, does not have to be encoded*/
    for(i = info->palettesize; i > 0; i--)
    {
      if(info->palette[4 * (i - 1) + 3] == 255) amount--;
      else break;
    }
    /*add only alpha channel*/
    for(i = 0; i < amount; i++) ucvector_push_back(&tRNS, info->palette[4 * i + 3]);
  }
  else if(info->colortype == LCT_GREY)
  {
    if(info->key_defined)
    {
      ucvector_push_back(&tRNS, (unsigned char)(info->key_r / 256));
      ucvector_push_back(&tRNS, (unsigned char)(info->key_r % 256));
    }
  }
  else if(info->colortype == LCT_RGB)
  {
    if(info->key_defined)
    {
      ucvector_push_back(&tRNS, (unsigned char)(info->key_r / 256));
      ucvector_push_back(&tRNS, (unsigned char)(info->key_r % 256));
      ucvector_push_back(&tRNS, (unsigned char)(info->key_g / 256));
      ucvector_push_back(&tRNS, (unsigned char)(info->key_g % 256));
      ucvector_push_back(&tRNS, (unsigned char)(info->key_b / 256));
      ucvector_push_back(&tRNS, (unsigned char)(info->key_b % 256));
    }
  }

  error = addChunk(out, "tRNS", tRNS.data, tRNS.size);
  ucvector_cleanup(&tRNS);

  return error;
}

static unsigned addChunk_IDAT(ucvector* out, const unsigned char* data, size_t datasize,
                              LodePNGCompressSettings* zlibsettings)
{
  ucvector zlibdata;
  unsigned error = 0;

  /*compress with the Zlib compressor*/
  ucvector_init(&zlibdata);
  error = zlib_compress(&zlibdata.data, &zlibdata.size, data, datasize, zlibsettings);
  if(!error) error = addChunk(out, "IDAT", zlibdata.data, zlibdata.size);
  ucvector_cleanup(&zlibdata);

  return error;
}

static unsigned addChunk_IEND(ucvector* out)
{
  unsigned error = 0;
  error = addChunk(out, "IEND", 0, 0);
  return error;
}

#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS

static unsigned addChunk_tEXt(ucvector* out, const char* keyword, const char* textstring)
{
  unsigned error = 0;
  size_t i;
  ucvector text;
  ucvector_init(&text);
  for(i = 0; keyword[i] != 0; i++) ucvector_push_back(&text, (unsigned char)keyword[i]);
  if(i < 1 || i > 79) return 89; /*error: invalid keyword size*/
  ucvector_push_back(&text, 0); /*0 termination char*/
  for(i = 0; textstring[i] != 0; i++) ucvector_push_back(&text, (unsigned char)textstring[i]);
  error = addChunk(out, "tEXt", text.data, text.size);
  ucvector_cleanup(&text);

  return error;
}

static unsigned addChunk_zTXt(ucvector* out, const char* keyword, const char* textstring,
                              LodePNGCompressSettings* zlibsettings)
{
  unsigned error = 0;
  ucvector data, compressed;
  size_t i, textsize = strlen(textstring);

  ucvector_init(&data);
  ucvector_init(&compressed);
  for(i = 0; keyword[i] != 0; i++) ucvector_push_back(&data, (unsigned char)keyword[i]);
  if(i < 1 || i > 79) return 89; /*error: invalid keyword size*/
  ucvector_push_back(&data, 0); /*0 termination char*/
  ucvector_push_back(&data, 0); /*compression method: 0*/

  error = zlib_compress(&compressed.data, &compressed.size,
                        (unsigned char*)textstring, textsize, zlibsettings);
  if(!error)
  {
    for(i = 0; i < compressed.size; i++) ucvector_push_back(&data, compressed.data[i]);
    error = addChunk(out, "zTXt", data.data, data.size);
  }

  ucvector_cleanup(&compressed);
  ucvector_cleanup(&data);
  return error;
}

static unsigned addChunk_iTXt(ucvector* out, unsigned compressed, const char* keyword, const char* langtag,
                              const char* transkey, const char* textstring, LodePNGCompressSettings* zlibsettings)
{
  unsigned error = 0;
  ucvector data;
  size_t i, textsize = strlen(textstring);

  ucvector_init(&data);

  for(i = 0; keyword[i] != 0; i++) ucvector_push_back(&data, (unsigned char)keyword[i]);
  if(i < 1 || i > 79) return 89; /*error: invalid keyword size*/
  ucvector_push_back(&data, 0); /*null termination char*/
  ucvector_push_back(&data, compressed ? 1 : 0); /*compression flag*/
  ucvector_push_back(&data, 0); /*compression method*/
  for(i = 0; langtag[i] != 0; i++) ucvector_push_back(&data, (unsigned char)langtag[i]);
  ucvector_push_back(&data, 0); /*null termination char*/
  for(i = 0; transkey[i] != 0; i++) ucvector_push_back(&data, (unsigned char)transkey[i]);
  ucvector_push_back(&data, 0); /*null termination char*/

  if(compressed)
  {
    ucvector compressed_data;
    ucvector_init(&compressed_data);
    error = zlib_compress(&compressed_data.data, &compressed_data.size,
                          (unsigned char*)textstring, textsize, zlibsettings);
    if(!error)
    {
      for(i = 0; i < compressed_data.size; i++) ucvector_push_back(&data, compressed_data.data[i]);
    }
    ucvector_cleanup(&compressed_data);
  }
  else /*not compressed*/
  {
    for(i = 0; textstring[i] != 0; i++) ucvector_push_back(&data, (unsigned char)textstring[i]);
  }

  if(!error) error = addChunk(out, "iTXt", data.data, data.size);
  ucvector_cleanup(&data);
  return error;
}

static unsigned addChunk_bKGD(ucvector* out, const LodePNGInfo* info)
{
  unsigned error = 0;
  ucvector bKGD;
  ucvector_init(&bKGD);
  if(info->color.colortype == LCT_GREY || info->color.colortype == LCT_GREY_ALPHA)
  {
    ucvector_push_back(&bKGD, (unsigned char)(info->background_r / 256));
    ucvector_push_back(&bKGD, (unsigned char)(info->background_r % 256));
  }
  else if(info->color.colortype == LCT_RGB || info->color.colortype == LCT_RGBA)
  {
    ucvector_push_back(&bKGD, (unsigned char)(info->background_r / 256));
    ucvector_push_back(&bKGD, (unsigned char)(info->background_r % 256));
    ucvector_push_back(&bKGD, (unsigned char)(info->background_g / 256));
    ucvector_push_back(&bKGD, (unsigned char)(info->background_g % 256));
    ucvector_push_back(&bKGD, (unsigned char)(info->background_b / 256));
    ucvector_push_back(&bKGD, (unsigned char)(info->background_b % 256));
  }
  else if(info->color.colortype == LCT_PALETTE)
  {
    ucvector_push_back(&bKGD, (unsigned char)(info->background_r % 256)); /*palette index*/
  }

  error = addChunk(out, "bKGD", bKGD.data, bKGD.size);
  ucvector_cleanup(&bKGD);

  return error;
}

static unsigned addChunk_tIME(ucvector* out, const LodePNGTime* time)
{
  unsigned error = 0;
  unsigned char* data = (unsigned char*)lodepng_malloc(7);
  if(!data) return 83; /*alloc fail*/
  data[0] = (unsigned char)(time->year / 256);
  data[1] = (unsigned char)(time->year % 256);
  data[2] = time->month;
  data[3] = time->day;
  data[4] = time->hour;
  data[5] = time->minute;
  data[6] = time->second;
  error = addChunk(out, "tIME", data, 7);
  lodepng_free(data);
  return error;
}

static unsigned addChunk_pHYs(ucvector* out, const LodePNGInfo* info)
{
  unsigned error = 0;
  ucvector data;
  ucvector_init(&data);

  lodepng_add32bitInt(&data, info->phys_x);
  lodepng_add32bitInt(&data, info->phys_y);
  ucvector_push_back(&data, info->phys_unit);

  error = addChunk(out, "pHYs", data.data, data.size);
  ucvector_cleanup(&data);

  return error;
}

#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/

static void filterScanline(unsigned char* out, const unsigned char* scanline, const unsigned char* prevline,
                           size_t length, size_t bytewidth, unsigned char filterType)
{
  size_t i;
  switch(filterType)
  {
    case 0: /*None*/
      for(i = 0; i < length; i++) out[i] = scanline[i];
      break;
    case 1: /*Sub*/
      if(prevline)
      {
        for(i = 0; i < bytewidth; i++) out[i] = scanline[i];
        for(i = bytewidth; i < length; i++) out[i] = scanline[i] - scanline[i - bytewidth];
      }
      else
      {
        for(i = 0; i < bytewidth; i++) out[i] = scanline[i];
        for(i = bytewidth; i < length; i++) out[i] = scanline[i] - scanline[i - bytewidth];
      }
      break;
    case 2: /*Up*/
      if(prevline)
      {
        for(i = 0; i < length; i++) out[i] = scanline[i] - prevline[i];
      }
      else
      {
        for(i = 0; i < length; i++) out[i] = scanline[i];
      }
      break;
    case 3: /*Average*/
      if(prevline)
      {
        for(i = 0; i < bytewidth; i++) out[i] = scanline[i] - prevline[i] / 2;
        for(i = bytewidth; i < length; i++) out[i] = scanline[i] - ((scanline[i - bytewidth] + prevline[i]) / 2);
      }
      else
      {
        for(i = 0; i < bytewidth; i++) out[i] = scanline[i];
        for(i = bytewidth; i < length; i++) out[i] = scanline[i] - scanline[i - bytewidth] / 2;
      }
      break;
    case 4: /*Paeth*/
      if(prevline)
      {
        /*paethPredictor(0, prevline[i], 0) is always prevline[i]*/
        for(i = 0; i < bytewidth; i++) out[i] = (scanline[i] - prevline[i]);
        for(i = bytewidth; i < length; i++)
        {
          out[i] = (scanline[i] - paethPredictor(scanline[i - bytewidth], prevline[i], prevline[i - bytewidth]));
        }
      }
      else
      {
        for(i = 0; i < bytewidth; i++) out[i] = scanline[i];
        /*paethPredictor(scanline[i - bytewidth], 0, 0) is always scanline[i - bytewidth]*/
        for(i = bytewidth; i < length; i++) out[i] = (scanline[i] - scanline[i - bytewidth]);
      }
      break;
    default: return; /*unexisting filter type given*/
  }
}

/* log2 approximation. A slight bit faster than std::log. */
static float flog2(float f)
{
  float result = 0;
  while(f > 32) { result += 4; f /= 16; }
  while(f > 2) { result++; f /= 2; }
  return result + 1.442695f * (f * f * f / 3 - 3 * f * f / 2 + 3 * f - 1.83333f);
}

static unsigned filter(unsigned char* out, const unsigned char* in, unsigned w, unsigned h,
                       const LodePNGColorMode* info, const LodePNGEncoderSettings* settings)
{
  /*
  For PNG filter method 0
  out must be a buffer with as size: h + (w * h * bpp + 7) / 8, because there are
  the scanlines with 1 extra byte per scanline
  */

  unsigned bpp = lodepng_get_bpp(info);
  /*the width of a scanline in bytes, not including the filter type*/
  size_t linebytes = (w * bpp + 7) / 8;
  /*bytewidth is used for filtering, is 1 when bpp < 8, number of bytes per pixel otherwise*/
  size_t bytewidth = (bpp + 7) / 8;
  const unsigned char* prevline = 0;
  unsigned x, y;
  unsigned error = 0;
  LodePNGFilterStrategy strategy = settings->filter_strategy;

  /*
  There is a heuristic called the minimum sum of absolute differences heuristic, suggested by the PNG standard:
   *  If the image type is Palette, or the bit depth is smaller than 8, then do not filter the image (i.e.
      use fixed filtering, with the filter None).
   * (The other case) If the image type is Grayscale or RGB (with or without Alpha), and the bit depth is
     not smaller than 8, then use adaptive filtering heuristic as follows: independently for each row, apply
     all five filters and select the filter that produces the smallest sum of absolute values per row.
  This heuristic is used if filter strategy is LFS_MINSUM and filter_palette_zero is true.

  If filter_palette_zero is true and filter_strategy is not LFS_MINSUM, the above heuristic is followed,
  but for "the other case", whatever strategy filter_strategy is set to instead of the minimum sum
  heuristic is used.
  */
  if(settings->filter_palette_zero &&
     (info->colortype == LCT_PALETTE || info->bitdepth < 8)) strategy = LFS_ZERO;

  if(bpp == 0) return 31; /*error: invalid color type*/

  if(strategy == LFS_ZERO)
  {
    for(y = 0; y < h; y++)
    {
      size_t outindex = (1 + linebytes) * y; /*the extra filterbyte added to each row*/
      size_t inindex = linebytes * y;
      out[outindex] = 0; /*filter type byte*/
      filterScanline(&out[outindex + 1], &in[inindex], prevline, linebytes, bytewidth, 0);
      prevline = &in[inindex];
    }
  }
  else if(strategy == LFS_MINSUM)
  {
    /*adaptive filtering*/
    size_t sum[5];
    ucvector attempt[5]; /*five filtering attempts, one for each filter type*/
    size_t smallest = 0;
    unsigned type, bestType = 0;

    for(type = 0; type < 5; type++)
    {
      ucvector_init(&attempt[type]);
      if(!ucvector_resize(&attempt[type], linebytes)) return 83; /*alloc fail*/
    }

    if(!error)
    {
      for(y = 0; y < h; y++)
      {
        /*try the 5 filter types*/
        for(type = 0; type < 5; type++)
        {
          filterScanline(attempt[type].data, &in[y * linebytes], prevline, linebytes, bytewidth, type);

          /*calculate the sum of the result*/
          sum[type] = 0;
          if(type == 0)
          {
            for(x = 0; x < linebytes; x++) sum[type] += (unsigned char)(attempt[type].data[x]);
          }
          else
          {
            for(x = 0; x < linebytes; x++)
            {
              /*For differences, each byte should be treated as signed, values above 127 are negative
              (converted to signed char). Filtertype 0 isn't a difference though, so use unsigned there.
              This means filtertype 0 is almost never chosen, but that is justified.*/
              signed char s = (signed char)(attempt[type].data[x]);
              sum[type] += s < 0 ? -s : s;
            }
          }

          /*check if this is smallest sum (or if type == 0 it's the first case so always store the values)*/
          if(type == 0 || sum[type] < smallest)
          {
            bestType = type;
            smallest = sum[type];
          }
        }

        prevline = &in[y * linebytes];

        /*now fill the out values*/
        out[y * (linebytes + 1)] = bestType; /*the first byte of a scanline will be the filter type*/
        for(x = 0; x < linebytes; x++) out[y * (linebytes + 1) + 1 + x] = attempt[bestType].data[x];
      }
    }

    for(type = 0; type < 5; type++) ucvector_cleanup(&attempt[type]);
  }
  else if(strategy == LFS_ENTROPY)
  {
    float sum[5];
    ucvector attempt[5]; /*five filtering attempts, one for each filter type*/
    float smallest = 0;
    unsigned type, bestType = 0;
    unsigned count[256];

    for(type = 0; type < 5; type++)
    {
      ucvector_init(&attempt[type]);
      if(!ucvector_resize(&attempt[type], linebytes)) return 83; /*alloc fail*/
    }

    for(y = 0; y < h; y++)
    {
      /*try the 5 filter types*/
      for(type = 0; type < 5; type++)
      {
        filterScanline(attempt[type].data, &in[y * linebytes], prevline, linebytes, bytewidth, type);
        for(x = 0; x < 256; x++) count[x] = 0;
        for(x = 0; x < linebytes; x++) count[attempt[type].data[x]]++;
        count[type]++; /*the filter type itself is part of the scanline*/
        sum[type] = 0;
        for(x = 0; x < 256; x++)
        {
          float p = count[x] / (float)(linebytes + 1);
          sum[type] += count[x] == 0 ? 0 : flog2(1 / p) * p;
        }
        /*check if this is smallest sum (or if type == 0 it's the first case so always store the values)*/
        if(type == 0 || sum[type] < smallest)
        {
          bestType = type;
          smallest = sum[type];
        }
      }

      prevline = &in[y * linebytes];

      /*now fill the out values*/
      out[y * (linebytes + 1)] = bestType; /*the first byte of a scanline will be the filter type*/
      for(x = 0; x < linebytes; x++) out[y * (linebytes + 1) + 1 + x] = attempt[bestType].data[x];
    }

    for(type = 0; type < 5; type++) ucvector_cleanup(&attempt[type]);
  }
  else if(strategy == LFS_PREDEFINED)
  {
    for(y = 0; y < h; y++)
    {
      size_t outindex = (1 + linebytes) * y; /*the extra filterbyte added to each row*/
      size_t inindex = linebytes * y;
      unsigned type = settings->predefined_filters[y];
      out[outindex] = type; /*filter type byte*/
      filterScanline(&out[outindex + 1], &in[inindex], prevline, linebytes, bytewidth, type);
      prevline = &in[inindex];
    }
  }
  else if(strategy == LFS_BRUTE_FORCE)
  {
    /*brute force filter chooser.
    deflate the scanline after every filter attempt to see which one deflates best.
    This is very slow and gives only slightly smaller, sometimes even larger, result*/
    size_t size[5];
    ucvector attempt[5]; /*five filtering attempts, one for each filter type*/
    size_t smallest = 0;
    unsigned type = 0, bestType = 0;
    unsigned char* dummy;
    LodePNGCompressSettings zlibsettings = settings->zlibsettings;
    /*use fixed tree on the attempts so that the tree is not adapted to the filtertype on purpose,
    to simulate the true case where the tree is the same for the whole image. Sometimes it gives
    better result with dynamic tree anyway. Using the fixed tree sometimes gives worse, but in rare
    cases better compression. It does make this a bit less slow, so it's worth doing this.*/
    zlibsettings.btype = 1;
    /*a custom encoder likely doesn't read the btype setting and is optimized for complete PNG
    images only, so disable it*/
    zlibsettings.custom_zlib = 0;
    zlibsettings.custom_deflate = 0;
    for(type = 0; type < 5; type++)
    {
      ucvector_init(&attempt[type]);
      ucvector_resize(&attempt[type], linebytes); /*todo: give error if resize failed*/
    }
    for(y = 0; y < h; y++) /*try the 5 filter types*/
    {
      for(type = 0; type < 5; type++)
      {
        unsigned testsize = attempt[type].size;
        /*if(testsize > 8) testsize /= 8;*/ /*it already works good enough by testing a part of the row*/

        filterScanline(attempt[type].data, &in[y * linebytes], prevline, linebytes, bytewidth, type);
        size[type] = 0;
        dummy = 0;
        zlib_compress(&dummy, &size[type], attempt[type].data, testsize, &zlibsettings);
        lodepng_free(dummy);
        /*check if this is smallest size (or if type == 0 it's the first case so always store the values)*/
        if(type == 0 || size[type] < smallest)
        {
          bestType = type;
          smallest = size[type];
        }
      }
      prevline = &in[y * linebytes];
      out[y * (linebytes + 1)] = bestType; /*the first byte of a scanline will be the filter type*/
      for(x = 0; x < linebytes; x++) out[y * (linebytes + 1) + 1 + x] = attempt[bestType].data[x];
    }
    for(type = 0; type < 5; type++) ucvector_cleanup(&attempt[type]);
  }
  else return 88; /* unknown filter strategy */

  return error;
}

static void addPaddingBits(unsigned char* out, const unsigned char* in,
                           size_t olinebits, size_t ilinebits, unsigned h)
{
  /*The opposite of the removePaddingBits function
  olinebits must be >= ilinebits*/
  unsigned y;
  size_t diff = olinebits - ilinebits;
  size_t obp = 0, ibp = 0; /*bit pointers*/
  for(y = 0; y < h; y++)
  {
    size_t x;
    for(x = 0; x < ilinebits; x++)
    {
      unsigned char bit = readBitFromReversedStream(&ibp, in);
      setBitOfReversedStream(&obp, out, bit);
    }
    /*obp += diff; --> no, fill in some value in the padding bits too, to avoid
    "Use of uninitialised value of size ###" warning from valgrind*/
    for(x = 0; x < diff; x++) setBitOfReversedStream(&obp, out, 0);
  }
}

/*
in: non-interlaced image with size w*h
out: the same pixels, but re-ordered according to PNG's Adam7 interlacing, with
 no padding bits between scanlines, but between reduced images so that each
 reduced image starts at a byte.
bpp: bits per pixel
there are no padding bits, not between scanlines, not between reduced images
in has the following size in bits: w * h * bpp.
out is possibly bigger due to padding bits between reduced images
NOTE: comments about padding bits are only relevant if bpp < 8
*/
static void Adam7_interlace(unsigned char* out, const unsigned char* in, unsigned w, unsigned h, unsigned bpp)
{
  unsigned passw[7], passh[7];
  size_t filter_passstart[8], padded_passstart[8], passstart[8];
  unsigned i;

  Adam7_getpassvalues(passw, passh, filter_passstart, padded_passstart, passstart, w, h, bpp);

  if(bpp >= 8)
  {
    for(i = 0; i < 7; i++)
    {
      unsigned x, y, b;
      size_t bytewidth = bpp / 8;
      for(y = 0; y < passh[i]; y++)
      for(x = 0; x < passw[i]; x++)
      {
        size_t pixelinstart = ((ADAM7_IY[i] + y * ADAM7_DY[i]) * w + ADAM7_IX[i] + x * ADAM7_DX[i]) * bytewidth;
        size_t pixeloutstart = passstart[i] + (y * passw[i] + x) * bytewidth;
        for(b = 0; b < bytewidth; b++)
        {
          out[pixeloutstart + b] = in[pixelinstart + b];
        }
      }
    }
  }
  else /*bpp < 8: Adam7 with pixels < 8 bit is a bit trickier: with bit pointers*/
  {
    for(i = 0; i < 7; i++)
    {
      unsigned x, y, b;
      unsigned ilinebits = bpp * passw[i];
      unsigned olinebits = bpp * w;
      size_t obp, ibp; /*bit pointers (for out and in buffer)*/
      for(y = 0; y < passh[i]; y++)
      for(x = 0; x < passw[i]; x++)
      {
        ibp = (ADAM7_IY[i] + y * ADAM7_DY[i]) * olinebits + (ADAM7_IX[i] + x * ADAM7_DX[i]) * bpp;
        obp = (8 * passstart[i]) + (y * ilinebits + x * bpp);
        for(b = 0; b < bpp; b++)
        {
          unsigned char bit = readBitFromReversedStream(&ibp, in);
          setBitOfReversedStream(&obp, out, bit);
        }
      }
    }
  }
}

/*out must be buffer big enough to contain uncompressed IDAT chunk data, and in must contain the full image.
return value is error**/
static unsigned preProcessScanlines(unsigned char** out, size_t* outsize, const unsigned char* in,
                                    unsigned w, unsigned h,
                                    const LodePNGInfo* info_png, const LodePNGEncoderSettings* settings)
{
  /*
  This function converts the pure 2D image with the PNG's colortype, into filtered-padded-interlaced data. Steps:
  *) if no Adam7: 1) add padding bits (= posible extra bits per scanline if bpp < 8) 2) filter
  *) if adam7: 1) Adam7_interlace 2) 7x add padding bits 3) 7x filter
  */
  unsigned bpp = lodepng_get_bpp(&info_png->color);
  unsigned error = 0;

  if(info_png->interlace_method == 0)
  {
    *outsize = h + (h * ((w * bpp + 7) / 8)); /*image size plus an extra byte per scanline + possible padding bits*/
    //*out = (unsigned char*)lodepng_malloc(*outsize);
    if(!(*out) && (*outsize)) error = 83; /*alloc fail*/

    if(!error)
    {
      /*non multiple of 8 bits per scanline, padding bits needed per scanline*/
      if(bpp < 8 && w * bpp != ((w * bpp + 7) / 8) * 8)
      {
        unsigned char* padded = (unsigned char*)lodepng_malloc(h * ((w * bpp + 7) / 8));
        if(!padded) error = 83; /*alloc fail*/
        if(!error)
        {
          addPaddingBits(padded, in, ((w * bpp + 7) / 8) * 8, w * bpp, h);
          error = filter(*out, padded, w, h, &info_png->color, settings);
        }
        lodepng_free(padded);
      }
      else
      {
        /*we can immediatly filter into the out buffer, no other steps needed*/
        error = filter(*out, in, w, h, &info_png->color, settings);
      }
    }
  }
  else /*interlace_method is 1 (Adam7)*/
  {
    unsigned passw[7], passh[7];
    size_t filter_passstart[8], padded_passstart[8], passstart[8];
    unsigned char* adam7;

    Adam7_getpassvalues(passw, passh, filter_passstart, padded_passstart, passstart, w, h, bpp);

    *outsize = filter_passstart[7]; /*image size plus an extra byte per scanline + possible padding bits*/
    //*out = (unsigned char*)lodepng_malloc(*outsize);
    if(!(*out)) error = 83; /*alloc fail*/

    adam7 = (unsigned char*)lodepng_malloc(passstart[7]);
    if(!adam7 && passstart[7]) error = 83; /*alloc fail*/

    if(!error)
    {
      unsigned i;

      Adam7_interlace(adam7, in, w, h, bpp);
      for(i = 0; i < 7; i++)
      {
        if(bpp < 8)
        {
          unsigned char* padded = (unsigned char*)lodepng_malloc(padded_passstart[i + 1] - padded_passstart[i]);
          if(!padded) ERROR_BREAK(83); /*alloc fail*/
          addPaddingBits(padded, &adam7[passstart[i]],
                         ((passw[i] * bpp + 7) / 8) * 8, passw[i] * bpp, passh[i]);
          error = filter(&(*out)[filter_passstart[i]], padded,
                         passw[i], passh[i], &info_png->color, settings);
          lodepng_free(padded);
        }
        else
        {
          error = filter(&(*out)[filter_passstart[i]], &adam7[padded_passstart[i]],
                         passw[i], passh[i], &info_png->color, settings);
        }

        if(error) break;
      }
    }

    lodepng_free(adam7);
  }

  return error;
}

/*
palette must have 4 * palettesize bytes allocated, and given in format RGBARGBARGBARGBA...
returns 0 if the palette is opaque,
returns 1 if the palette has a single color with alpha 0 ==> color key
returns 2 if the palette is semi-translucent.
*/
static unsigned getPaletteTranslucency(const unsigned char* palette, size_t palettesize)
{
  size_t i, key = 0;
  unsigned r = 0, g = 0, b = 0; /*the value of the color with alpha 0, so long as color keying is possible*/
  for(i = 0; i < palettesize; i++)
  {
    if(!key && palette[4 * i + 3] == 0)
    {
      r = palette[4 * i + 0]; g = palette[4 * i + 1]; b = palette[4 * i + 2];
      key = 1;
      i = (size_t)(-1); /*restart from beginning, to detect earlier opaque colors with key's value*/
    }
    else if(palette[4 * i + 3] != 255) return 2;
    /*when key, no opaque RGB may have key's RGB*/
    else if(key && r == palette[i * 4 + 0] && g == palette[i * 4 + 1] && b == palette[i * 4 + 2]) return 2;
  }
  return key;
}

#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
static unsigned addUnknownChunks(ucvector* out, unsigned char* data, size_t datasize)
{
  unsigned char* inchunk = data;
  while((size_t)(inchunk - data) < datasize)
  {
    CERROR_TRY_RETURN(lodepng_chunk_append(&out->data, &out->size, inchunk));
    out->allocsize = out->size; /*fix the allocsize again*/
    inchunk = lodepng_chunk_next(inchunk);
  }
  return 0;
}
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/

unsigned lodepng_encode(unsigned char** out, size_t* outsize,
                        const unsigned char* image, unsigned w, unsigned h,
                        LodePNGState* state)
{
  LodePNGInfo info;
  ucvector outv;
  unsigned char* data = 0; /*uncompressed version of the IDAT chunk data*/
  size_t datasize = 0;

  /*provide some proper output values if error will happen*/
  *out = 0;
  *outsize = 0;
  state->error = 0;

  lodepng_info_init(&info);
  lodepng_info_copy(&info, &state->info_png);

  if((info.color.colortype == LCT_PALETTE || state->encoder.force_palette)
      && (info.color.palettesize == 0 || info.color.palettesize > 256))
  {
    state->error = 68; /*invalid palette size, it is only allowed to be 1-256*/
    return state->error;
  }

  if(state->encoder.auto_convert != LAC_NO)
  {
    state->error = doAutoChooseColor(&info.color, image, w, h, &state->info_raw,
                                     state->encoder.auto_convert);
  }
  if(state->error) return state->error;

  if(state->encoder.zlibsettings.windowsize > 32768)
  {
    CERROR_RETURN_ERROR(state->error, 60); /*error: windowsize larger than allowed*/
  }
  if(state->encoder.zlibsettings.btype > 2)
  {
    CERROR_RETURN_ERROR(state->error, 61); /*error: unexisting btype*/
  }
  if(state->info_png.interlace_method > 1)
  {
    CERROR_RETURN_ERROR(state->error, 71); /*error: unexisting interlace mode*/
  }

  state->error = checkColorValidity(info.color.colortype, info.color.bitdepth);
  if(state->error) return state->error; /*error: unexisting color type given*/
  state->error = checkColorValidity(state->info_raw.colortype, state->info_raw.bitdepth);
  if(state->error) return state->error; /*error: unexisting color type given*/

  if(!lodepng_color_mode_equal(&state->info_raw, &info.color))
  {
    unsigned char* converted;
    size_t size = (w * h * lodepng_get_bpp(&info.color) + 7) / 8;

    converted = (unsigned char*)lodepng_malloc(size);
    if(!converted && size) state->error = 83; /*alloc fail*/
    if(!state->error)
    {
      state->error = lodepng_convert(converted, image, &info.color, &state->info_raw, w, h, 0 /*fix_png*/);
    }
    if(!state->error) preProcessScanlines(&data, &datasize, converted, w, h, &info, &state->encoder);
    lodepng_free(converted);
  }
  else preProcessScanlines(&data, &datasize, image, w, h, &info, &state->encoder);

  ucvector_init(&outv);
  while(!state->error) /*while only executed once, to break on error*/
  {
#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
    size_t i;
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
    /*write signature and chunks*/
    writeSignature(&outv);
    /*IHDR*/
    addChunk_IHDR(&outv, w, h, info.color.colortype, info.color.bitdepth, info.interlace_method);
#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
    /*unknown chunks between IHDR and PLTE*/
    if(info.unknown_chunks_data[0])
    {
      state->error = addUnknownChunks(&outv, info.unknown_chunks_data[0], info.unknown_chunks_size[0]);
      if(state->error) break;
    }
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
    /*PLTE*/
    if(info.color.colortype == LCT_PALETTE)
    {
      addChunk_PLTE(&outv, &info.color);
    }
    if(state->encoder.force_palette && (info.color.colortype == LCT_RGB || info.color.colortype == LCT_RGBA))
    {
      addChunk_PLTE(&outv, &info.color);
    }
    /*tRNS*/
    if(info.color.colortype == LCT_PALETTE && getPaletteTranslucency(info.color.palette, info.color.palettesize) != 0)
    {
      addChunk_tRNS(&outv, &info.color);
    }
    if((info.color.colortype == LCT_GREY || info.color.colortype == LCT_RGB) && info.color.key_defined)
    {
      addChunk_tRNS(&outv, &info.color);
    }
#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
    /*bKGD (must come between PLTE and the IDAt chunks*/
    if(info.background_defined) addChunk_bKGD(&outv, &info);
    /*pHYs (must come before the IDAT chunks)*/
    if(info.phys_defined) addChunk_pHYs(&outv, &info);

    /*unknown chunks between PLTE and IDAT*/
    if(info.unknown_chunks_data[1])
    {
      state->error = addUnknownChunks(&outv, info.unknown_chunks_data[1], info.unknown_chunks_size[1]);
      if(state->error) break;
    }
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
    /*IDAT (multiple IDAT chunks must be consecutive)*/
    state->error = addChunk_IDAT(&outv, data, datasize, &state->encoder.zlibsettings);
    if(state->error) break;
#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
    /*tIME*/
    if(info.time_defined) addChunk_tIME(&outv, &info.time);
    /*tEXt and/or zTXt*/
    for(i = 0; i < info.text_num; i++)
    {
      if(strlen(info.text_keys[i]) > 79)
      {
        state->error = 66; /*text chunk too large*/
        break;
      }
      if(strlen(info.text_keys[i]) < 1)
      {
        state->error = 67; /*text chunk too small*/
        break;
      }
      if(state->encoder.text_compression)
        addChunk_zTXt(&outv, info.text_keys[i], info.text_strings[i], &state->encoder.zlibsettings);
      else
        addChunk_tEXt(&outv, info.text_keys[i], info.text_strings[i]);
    }
    /*LodePNG version id in text chunk*/
    if(state->encoder.add_id)
    {
      unsigned alread_added_id_text = 0;
      for(i = 0; i < info.text_num; i++)
      {
        if(!strcmp(info.text_keys[i], "LodePNG"))
        {
          alread_added_id_text = 1;
          break;
        }
      }
      if(alread_added_id_text == 0)
        addChunk_tEXt(&outv, "LodePNG", VERSION_STRING); /*it's shorter as tEXt than as zTXt chunk*/
    }
    /*iTXt*/
    for(i = 0; i < info.itext_num; i++)
    {
      if(strlen(info.itext_keys[i]) > 79)
      {
        state->error = 66; /*text chunk too large*/
        break;
      }
      if(strlen(info.itext_keys[i]) < 1)
      {
        state->error = 67; /*text chunk too small*/
        break;
      }
      addChunk_iTXt(&outv, state->encoder.text_compression,
                    info.itext_keys[i], info.itext_langtags[i], info.itext_transkeys[i], info.itext_strings[i],
                    &state->encoder.zlibsettings);
    }

    /*unknown chunks between IDAT and IEND*/
    if(info.unknown_chunks_data[2])
    {
      state->error = addUnknownChunks(&outv, info.unknown_chunks_data[2], info.unknown_chunks_size[2]);
      if(state->error) break;
    }
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
    /*IEND*/
    addChunk_IEND(&outv);

    break; /*this isn't really a while loop; no error happened so break out now!*/
  }

  lodepng_info_cleanup(&info);
  lodepng_free(data);
  /*instead of cleaning the vector up, give it to the output*/
  *out = outv.data;
  *outsize = outv.size;

  return state->error;
}

unsigned lodepng_encode_memory(unsigned char** out, size_t* outsize, const unsigned char* image,
                               unsigned w, unsigned h, LodePNGColorType colortype, unsigned bitdepth)
{
  unsigned error;
  LodePNGState state;
  lodepng_state_init(&state);
  state.info_raw.colortype = colortype;
  state.info_raw.bitdepth = bitdepth;
  state.info_png.color.colortype = colortype;
  state.info_png.color.bitdepth = bitdepth;
  lodepng_encode(out, outsize, image, w, h, &state);
  error = state.error;
  lodepng_state_cleanup(&state);
  return error;
}

unsigned lodepng_encode32(unsigned char** out, size_t* outsize, const unsigned char* image, unsigned w, unsigned h)
{
  return lodepng_encode_memory(out, outsize, image, w, h, LCT_RGBA, 8);
}

unsigned lodepng_encode24(unsigned char** out, size_t* outsize, const unsigned char* image, unsigned w, unsigned h)
{
  return lodepng_encode_memory(out, outsize, image, w, h, LCT_RGB, 8);
}

#ifdef LODEPNG_COMPILE_DISK
unsigned lodepng_encode_file(const char* filename, const unsigned char* image, unsigned w, unsigned h,
                             LodePNGColorType colortype, unsigned bitdepth)
{
  unsigned char* buffer;
  size_t buffersize;
  unsigned error = lodepng_encode_memory(&buffer, &buffersize, image, w, h, colortype, bitdepth);
  if(!error) error = lodepng_save_file(buffer, buffersize, filename);
  lodepng_free(buffer);
  return error;
}

unsigned lodepng_encode32_file(const char* filename, const unsigned char* image, unsigned w, unsigned h)
{
  return lodepng_encode_file(filename, image, w, h, LCT_RGBA, 8);
}

unsigned lodepng_encode24_file(const char* filename, const unsigned char* image, unsigned w, unsigned h)
{
  return lodepng_encode_file(filename, image, w, h, LCT_RGB, 8);
}
#endif /*LODEPNG_COMPILE_DISK*/

void lodepng_encoder_settings_init(LodePNGEncoderSettings* settings)
{
  lodepng_compress_settings_init(&settings->zlibsettings);
  settings->filter_palette_zero = 1;
  settings->filter_strategy = LFS_MINSUM;
  settings->auto_convert = LAC_AUTO;
  settings->force_palette = 0;
  settings->predefined_filters = 0;
#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
  settings->add_id = 0;
  settings->text_compression = 1;
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
}

#endif /*LODEPNG_COMPILE_ENCODER*/
#endif /*LODEPNG_COMPILE_PNG*/

#ifdef LODEPNG_COMPILE_ERROR_TEXT
/*
This returns the description of a numerical error code in English. This is also
the documentation of all the error codes.
*/
const char* lodepng_error_text(unsigned code)
{
  switch(code)
  {
    case 0: return "no error, everything went ok";
    case 1: return "nothing done yet"; /*the Encoder/Decoder has done nothing yet, error checking makes no sense yet*/
    case 10: return "end of input memory reached without huffman end code"; /*while huffman decoding*/
    case 11: return "error in code tree made it jump outside of huffman tree"; /*while huffman decoding*/
    case 13: return "problem while processing dynamic deflate block";
    case 14: return "problem while processing dynamic deflate block";
    case 15: return "problem while processing dynamic deflate block";
    case 16: return "unexisting code while processing dynamic deflate block";
    case 17: return "end of out buffer memory reached while inflating";
    case 18: return "invalid distance code while inflating";
    case 19: return "end of out buffer memory reached while inflating";
    case 20: return "invalid deflate block BTYPE encountered while decoding";
    case 21: return "NLEN is not ones complement of LEN in a deflate block";
     /*end of out buffer memory reached while inflating:
     This can happen if the inflated deflate data is longer than the amount of bytes required to fill up
     all the pixels of the image, given the color depth and image dimensions. Something that doesn't
     happen in a normal, well encoded, PNG image.*/
    case 22: return "end of out buffer memory reached while inflating";
    case 23: return "end of in buffer memory reached while inflating";
    case 24: return "invalid FCHECK in zlib header";
    case 25: return "invalid compression method in zlib header";
    case 26: return "FDICT encountered in zlib header while it's not used for PNG";
    case 27: return "PNG file is smaller than a PNG header";
    /*Checks the magic file header, the first 8 bytes of the PNG file*/
    case 28: return "incorrect PNG signature, it's no PNG or corrupted";
    case 29: return "first chunk is not the header chunk";
    case 30: return "chunk length too large, chunk broken off at end of file";
    case 31: return "illegal PNG color type or bpp";
    case 32: return "illegal PNG compression method";
    case 33: return "illegal PNG filter method";
    case 34: return "illegal PNG interlace method";
    case 35: return "chunk length of a chunk is too large or the chunk too small";
    case 36: return "illegal PNG filter type encountered";
    case 37: return "illegal bit depth for this color type given";
    case 38: return "the palette is too big"; /*more than 256 colors*/
    case 39: return "more palette alpha values given in tRNS chunk than there are colors in the palette";
    case 40: return "tRNS chunk has wrong size for greyscale image";
    case 41: return "tRNS chunk has wrong size for RGB image";
    case 42: return "tRNS chunk appeared while it was not allowed for this color type";
    case 43: return "bKGD chunk has wrong size for palette image";
    case 44: return "bKGD chunk has wrong size for greyscale image";
    case 45: return "bKGD chunk has wrong size for RGB image";
    /*Is the palette too small?*/
    case 46: return "a value in indexed image is larger than the palette size (bitdepth = 8)";
    /*Is the palette too small?*/
    case 47: return "a value in indexed image is larger than the palette size (bitdepth < 8)";
    /*the input data is empty, maybe a PNG file doesn't exist or is in the wrong path*/
    case 48: return "empty input or file doesn't exist";
    case 49: return "jumped past memory while generating dynamic huffman tree";
    case 50: return "jumped past memory while generating dynamic huffman tree";
    case 51: return "jumped past memory while inflating huffman block";
    case 52: return "jumped past memory while inflating";
    case 53: return "size of zlib data too small";
    case 54: return "repeat symbol in tree while there was no value symbol yet";
    /*jumped past tree while generating huffman tree, this could be when the
    tree will have more leaves than symbols after generating it out of the
    given lenghts. They call this an oversubscribed dynamic bit lengths tree in zlib.*/
    case 55: return "jumped past tree while generating huffman tree";
    case 56: return "given output image colortype or bitdepth not supported for color conversion";
    case 57: return "invalid CRC encountered (checking CRC can be disabled)";
    case 58: return "invalid ADLER32 encountered (checking ADLER32 can be disabled)";
    case 59: return "requested color conversion not supported";
    case 60: return "invalid window size given in the settings of the encoder (must be 0-32768)";
    case 61: return "invalid BTYPE given in the settings of the encoder (only 0, 1 and 2 are allowed)";
    /*LodePNG leaves the choice of RGB to greyscale conversion formula to the user.*/
    case 62: return "conversion from color to greyscale not supported";
    case 63: return "length of a chunk too long, max allowed for PNG is 2147483647 bytes per chunk"; /*(2^31-1)*/
    /*this would result in the inability of a deflated block to ever contain an end code. It must be at least 1.*/
    case 64: return "the length of the END symbol 256 in the Huffman tree is 0";
    case 66: return "the length of a text chunk keyword given to the encoder is longer than the maximum of 79 bytes";
    case 67: return "the length of a text chunk keyword given to the encoder is smaller than the minimum of 1 byte";
    case 68: return "tried to encode a PLTE chunk with a palette that has less than 1 or more than 256 colors";
    case 69: return "unknown chunk type with 'critical' flag encountered by the decoder";
    case 71: return "unexisting interlace mode given to encoder (must be 0 or 1)";
    case 72: return "while decoding, unexisting compression method encountering in zTXt or iTXt chunk (it must be 0)";
    case 73: return "invalid tIME chunk size";
    case 74: return "invalid pHYs chunk size";
    /*length could be wrong, or data chopped off*/
    case 75: return "no null termination char found while decoding text chunk";
    case 76: return "iTXt chunk too short to contain required bytes";
    case 77: return "integer overflow in buffer size";
    case 78: return "failed to open file for reading"; /*file doesn't exist or couldn't be opened for reading*/
    case 79: return "failed to open file for writing";
    case 80: return "tried creating a tree of 0 symbols";
    case 81: return "lazy matching at pos 0 is impossible";
    case 82: return "color conversion to palette requested while a color isn't in palette";
    case 83: return "memory allocation failed";
    case 84: return "given image too small to contain all pixels to be encoded";
    case 85: return "internal color conversion bug";
    case 86: return "impossible offset in lz77 encoding (internal bug)";
    case 87: return "must provide custom zlib function pointer if LODEPNG_COMPILE_ZLIB is not defined";
    case 88: return "invalid filter strategy given for LodePNGEncoderSettings.filter_strategy";
    case 89: return "text chunk keyword too short or long: must have size 1-79";
  }
  return "unknown error code";
}
#endif /*LODEPNG_COMPILE_ERROR_TEXT*/



 
int traceLevel = 0; int popCount = 0;

std::string i__s(int i) {
	return std::to_string(i);
}
std::string fi__s(float f) {
	int i = f;
	return std::to_string(i);
}
std::string f__s(float f) {
	return std::to_string(f);
}


union hex_converter{
	float f_val;
	unsigned int u_val;
};
float hexToFloat(std::string* s) {
	union hex_converter hc;
	hc.u_val = (uint)strtoul(s->c_str(), NULL, 16);
	return hc.f_val;
}






std::string floatToHex( float f )
{
	// static_assert( std::numeric_limits<float>::is_iec559,
	// "native float must be an IEEE float" ) ;

	union {
		float fval;
		uint ival;
	};
	fval = f;

	std::ostringstream stm;
	stm << std::hex << std::uppercase << ival;

	return stm.str();
}

// // return 1 on error
// char FLOAT_TO_HEX_BUF[32];
// string floatToHex(float x) {
//   sprintf(FLOAT_TO_HEX_BUF, "0x%lx", (unsigned long) x);
  
//   return string(FLOAT_TO_HEX_BUF);
  
// }



std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while(getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}
std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	return split(s, delim, elems);
}




bool pairIsEqual(intPair a, intPair b) {
	return ( (a.v0 == b.v0) && (a.v1 == b.v1)  );
}
bool pairIsNeg(intPair a) {
	return ( (a.v0 == -1) && (a.v1 == -1)  );
}

float quickDis(float x1, float y1, float x2, float y2) {
	//return abs(x1-x2) + abs(y1-y2);//
	return sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
}

float coordDis(coordAndIndex* c1, coordAndIndex* c2) {
	//return abs(x1-x2) + abs(y1-y2);//

	float d1 = c1->x-c2->x;
	float d2 = c1->y-c2->y;
	return sqrt( d1*d1 + d2*d2 );
}


void bubbleSortF(floatAndIndex* num, int numLength)
{
	int i, j, flag = 1;

	floatAndIndex fiTemp;

	for(i = 1; (i <= numLength) && flag; i++) {
		flag = 0;
		for (j=0; j < (numLength -1); j++) {
			if (num[j+1].value < num[j].value) { // ascending order simply changes to <
				fiTemp = num[j];
				num[j] = num[j+1];
				num[j+1] = fiTemp;
				flag = 1;
			}
		}
	}
}





std::string intToString(int i) {
	std::string s;
	std::stringstream out;
	out << i;
	s = out.str();
	return s;
}
std::string floatToString(float f) {
	std::string s;
	std::stringstream out;
	out << f;
	s = out.str();
	return s;
}






//////////


void doTraceND(std::string traceVal0 = "", std::string traceVal1 = "",std::string traceVal2 = "",std::string traceVal3 = "",std::string traceVal4 = "",std::string traceVal5 = "", std::string traceVal6 = "",std::string traceVal7 = "",std::string traceVal8 = "",std::string traceVal9 = "",std::string traceVal10 = "") {
	
	int i;
	
	for (i = 0; i < traceLevel; i++) {
		std::cout << "|  ";
	}
	
	std::cout << traceVal0 << " " << traceVal1 << " " << traceVal2 << " " << traceVal3 << " " << traceVal4 << " " << traceVal5 << " " << traceVal6 << " " << traceVal7 << " " << traceVal8 << " " << traceVal9 << " " << traceVal10 << std::endl << std::flush;
	
}
void doTraceVecND(std::string traceVal0, FIVector4 *fv) {
	
	doTraceND(traceVal0, " ", f__s(fv->getFX()), " ", f__s(fv->getFY()), " ", f__s(fv->getFZ())  );
	
}

void pushTraceND(std::string traceVal0 = "", std::string traceVal1 = "",std::string traceVal2 = "",std::string traceVal3 = "",std::string traceVal4 = "",std::string traceVal5 = "", std::string traceVal6 = "",std::string traceVal7 = "",std::string traceVal8 = "",std::string traceVal9 = "",std::string traceVal10 = "") {
	
	doTraceND(traceVal0,traceVal1,traceVal2,traceVal3,traceVal4,traceVal5,traceVal6,traceVal7,traceVal8,traceVal9,traceVal10);
	traceLevel++;
	popCount=0;
	

	
}
void popTraceND() {
	
	traceLevel--;
	popCount++;
	if (popCount >= 2) {
		doTraceND("END");
	}
	
}

//////////




// void doTrace(std::string traceVal0 = "", std::string traceVal1 = "",std::string traceVal2 = "",std::string traceVal3 = "",std::string traceVal4 = "",std::string traceVal5 = "", std::string traceVal6 = "",std::string traceVal7 = "",std::string traceVal8 = "",std::string traceVal9 = "",std::string traceVal10 = "") {
// 	#ifdef DEBUG_MODE
// 	int i;
	
// 	for (i = 0; i < traceLevel; i++) {
// 		std::cout << "|  ";
// 	}
	
// 	std::cout << traceVal0 << " " << traceVal1 << " " << traceVal2 << " " << traceVal3 << " " << traceVal4 << " " << traceVal5 << " " << traceVal6 << " " << traceVal7 << " " << traceVal8 << " " << traceVal9 << " " << traceVal10 << std::endl << std::flush;
// 	#endif
// }
// void doTraceVec(std::string traceVal0, FIVector4 *fv) {
// 	#ifdef DEBUG_MODE
// 	doTrace(traceVal0, " ", f__s(fv->getFX()), " ", f__s(fv->getFY()), " ", f__s(fv->getFZ())  );
// 	#endif
// }

// void pushTrace(std::string traceVal0 = "", std::string traceVal1 = "",std::string traceVal2 = "",std::string traceVal3 = "",std::string traceVal4 = "",std::string traceVal5 = "", std::string traceVal6 = "",std::string traceVal7 = "",std::string traceVal8 = "",std::string traceVal9 = "",std::string traceVal10 = "") {
// 	#ifdef DEBUG_MODE
// 	doTrace(traceVal0,traceVal1,traceVal2,traceVal3,traceVal4,traceVal5,traceVal6,traceVal7,traceVal8,traceVal9,traceVal10);
// 	traceLevel++;
// 	popCount=0;
// 	#endif

	
// }
// void popTrace() {
// 	#ifdef DEBUG_MODE
// 	traceLevel--;
// 	popCount++;
// 	if (popCount >= 2) {
// 		doTrace("END");
// 	}
// 	#endif
// }



void doTrace(std::string traceVal0 = "", std::string traceVal1 = "",std::string traceVal2 = "",std::string traceVal3 = "",std::string traceVal4 = "",std::string traceVal5 = "", std::string traceVal6 = "",std::string traceVal7 = "",std::string traceVal8 = "",std::string traceVal9 = "",std::string traceVal10 = "") {
	int i;

	if (TRACE_ON) {
		for (i = 0; i < traceLevel; i++) {
			std::cout << "|  ";
		}
		
		std::cout << traceVal0 << " " << traceVal1 << " " << traceVal2 << " " << traceVal3 << " " << traceVal4 << " " << traceVal5 << " " << traceVal6 << " " << traceVal7 << " " << traceVal8 << " " << traceVal9 << " " << traceVal10 << std::endl << std::flush;
	}
	
	
}
void doTraceVec(std::string traceVal0, FIVector4 *fv) {
	if (TRACE_ON) {
		doTrace(traceVal0, " ", f__s(fv->getFX()), " ", f__s(fv->getFY()), " ", f__s(fv->getFZ())  );
	}
	
	
}

void pushTrace(std::string traceVal0 = "", std::string traceVal1 = "",std::string traceVal2 = "",std::string traceVal3 = "",std::string traceVal4 = "",std::string traceVal5 = "", std::string traceVal6 = "",std::string traceVal7 = "",std::string traceVal8 = "",std::string traceVal9 = "",std::string traceVal10 = "") {
	
	if (TRACE_ON) {
		doTrace(traceVal0,traceVal1,traceVal2,traceVal3,traceVal4,traceVal5,traceVal6,traceVal7,traceVal8,traceVal9,traceVal10);
			traceLevel++;
			popCount=0;
	}
	
}
void popTrace() {
	
	if (TRACE_ON) {
		traceLevel--;
		popCount++;
		if (popCount >= 2) {
			doTrace("END");
		}
	}

	
	
}



 


class UniformBuffer {
public:

	

	

	// GLchar* names[] =
	// {
	// 	"SurfaceColor",
	// 	"WarmColor",
	// 	"CoolColor",
	// 	"DiffuseWarm",
	// 	"DiffuseCool"
	// };

	int uniPosition;

	GLuint bufferId, uniformBlockIndex, index, progId;
	GLsizei uniformBlockSize;
	GLint singleSize, offset;
	GLfloat* uniData;

	// GLfloat colors[] = 
	// {
	// 	0.45,0.45,1,1,
	// 	0.45,0.45,1,1,
	// 	0.75,0.75,0.75,1,
	// 	0.0,0.0,1.0,1,
	// 	0.0,1.0,0.0,1
	// };


	bool wasUpdated;
	bool wasInit;
	
	UniformBuffer() {
		wasInit = false;
		uniData = NULL;
	}

	void init(GLuint _progId, int bufNameInd)
	{

		wasInit = true;
		uniPosition = 0;
		wasUpdated = false;
		progId = _progId;
		uniData = NULL;


		//Update the uniforms using ARB_uniform_buffer_object
		glGenBuffers(1, &bufferId);


		
		//There's only one uniform block here, the 'colors0' uniform block. 
		//It contains the color info for the gooch shader.
		uniformBlockIndex = glGetUniformBlockIndex(
			progId,
			BUF_NAMES[bufNameInd]//bufName.c_str()//"colors0"
		);

		
		//We need to get the uniform block's size in order to back it with the
		//appropriate buffer
		glGetActiveUniformBlockiv(
			progId,
			uniformBlockIndex,
			GL_UNIFORM_BLOCK_DATA_SIZE,
			&uniformBlockSize
		);

		doTraceND("uniformBlockSize: ", i__s(uniformBlockSize));


		if (uniData != NULL) {
			delete[] uniData;
			uniData = NULL;
		}

		uniData = new GLfloat[uniformBlockSize/4];


		
		//Create UBO.
		glBindBuffer(
			GL_UNIFORM_BUFFER,
			bufferId
		);
		glBufferData(
			GL_UNIFORM_BUFFER,
			uniformBlockSize,
			NULL,
			GL_STATIC_DRAW//GL_DYNAMIC_DRAW
		);

		//Now we attach the buffer to UBO binding point 0...
		glBindBufferBase(
			GL_UNIFORM_BUFFER,
			0,
			bufferId
		);
		//And associate the uniform block to this binding point.
		glUniformBlockBinding(
			progId,
			uniformBlockIndex,
			0
		);


		//To update a single uniform in a uniform block, we need to get its
		//offset into the buffer.
		
		//glGetUniformIndices(progId, 1, &names[2], &index);
		//glGetActiveUniformsiv(progId, 1, &index, GL_UNIFORM_OFFSET, &offset);
		//glGetActiveUniformsiv(progId, 1, &index, GL_UNIFORM_SIZE, &singleSize);

	    
	}

	void updateUniformBlock(int numFloats) {

		int datSize = uniformBlockSize;

		if (numFloats < 0) {

		}
		else {
			datSize = numFloats*4;
		}



		if (wasUpdated) {

		}
		else {
			glBindBuffer(GL_UNIFORM_BUFFER, bufferId);
			//We can use BufferData to upload our data to the shader,
			//since we know it's in the std140 layout
			//each float is 4 bytes
			glBufferData(GL_UNIFORM_BUFFER, datSize, uniData, GL_DYNAMIC_DRAW);
			//With a non-standard layout, we'd use BufferSubData for each uniform.
			//glBufferSubData(GL_UNIFORM_BUFFER, offset, singleSize, &uniData[8]);
			
			wasUpdated = true;
		}

		

	}

	void beginUniformBlock() {
		uniPosition = 0;
	}

	void invalidateUniformBlock() {
		wasUpdated = false;
	}
	bool wasUpdatedUniformBlock() {
		return wasUpdated;
	}

	~UniformBuffer() {

		if (wasInit) {
			if (uniData) {
				delete[] uniData;
				uniData = NULL;
			}
			glDeleteBuffers(1,&bufferId);
		}
		

	}


};








 
class Timer
{
public:
    Timer(){
        #ifdef WIN32
            QueryPerformanceFrequency(&frequency);
            startCount.QuadPart = 0;
            endCount.QuadPart = 0;
        #else
            startCount.tv_sec = startCount.tv_usec = 0;
            endCount.tv_sec = endCount.tv_usec = 0;
        #endif

            stopped = 0;
            startTimeInMicroSec = 0;
            endTimeInMicroSec = 0;
        }
    ~Timer() {

    }

    void   start() {
        stopped = 0; // reset stop flag
        #ifdef WIN32
        QueryPerformanceCounter(&startCount);
        #else
        gettimeofday(&startCount, NULL);
        #endif
    }
    void   stop() {
        stopped = 1; // set timer stopped flag

        #ifdef WIN32
        QueryPerformanceCounter(&endCount);
        #else
        gettimeofday(&endCount, NULL);
        #endif
    }
    double getElapsedTime() {
        return this->getElapsedTimeInSec();
    }
    double getElapsedTimeInSec() {
        return this->getElapsedTimeInMicroSec() * 0.000001;
    }

    double getElapsedTimeInMilliSec() {
        return this->getElapsedTimeInMicroSec() * 0.001;
    }

    double getElapsedTimeInMicroSec() {
        #ifdef WIN32
        if(!stopped) {
            QueryPerformanceCounter(&endCount);
        }

        startTimeInMicroSec = startCount.QuadPart * (1000000.0 / frequency.QuadPart);
        endTimeInMicroSec = endCount.QuadPart * (1000000.0 / frequency.QuadPart);
        #else
        if(!stopped) {
            gettimeofday(&endCount, NULL);
        }

        startTimeInMicroSec = (startCount.tv_sec * 1000000.0) + startCount.tv_usec;
        endTimeInMicroSec = (endCount.tv_sec * 1000000.0) + endCount.tv_usec;
        #endif

        return endTimeInMicroSec - startTimeInMicroSec;
    }



protected:


private:
    double startTimeInMicroSec;                 // starting time in micro-second
    double endTimeInMicroSec;                   // ending time in micro-second
    int    stopped;                             // stop flag 
#ifdef WIN32
    LARGE_INTEGER frequency;                    // ticks per second
    LARGE_INTEGER startCount;                   //
    LARGE_INTEGER endCount;                     //
#else
    timeval startCount;                         //
    timeval endCount;                           //
#endif
}; 


// Multi-octave Simplex noise - multiple noise values are combined.
float simplexNoise( const float, const float, const float, const float, const float );
float simplexNoise( const float, const float, const float, const float, const float, const float );
float simplexNoise( const float, const float, const float, const float, const float, const float, const float );


// Multi-octave Scaled Simplex noise - the result will be between the two parameters passed.
float simplexScaledNoise( const float, const float, const float, const float, const float, const float, const float );
float simplexScaledNoise( const float, const float, const float, const float, const float, const float, const float, const float );
float simplexScaledNoise( const float, const float, const float, const float, const float, const float, const float, const float, const float );

// Scaled Raw Simplex noise - the result will be between the two parameters passed.
float simplexScaledRawNoise( const float, const float, const float, const float );
float simplexScaledRawNoise( const float, const float, const float, const float, const float );
float simplexScaledRawNoise( const float, const float, const float, const float, const float, const float );


// Raw Simplex noise - a single noise value.
float simplexRawNoise( const float, const float );
float simplexRawNoise( const float, const float, const float );
float simplexRawNoise( const float, const float, const float, const float );


int fastfloor( const float x ) { return x > 0 ? (int) x : (int) x - 1; }
float dot( const int* g, const float x, const float y ) { return g[0]*x + g[1]*y; }
float dot( const int* g, const float x, const float y, const float z ) { return g[0]*x + g[1]*y + g[2]*z; }
float dot( const int* g, const float x, const float y, const float z, const float w ) { return g[0]*x + g[1]*y + g[2]*z + g[3]*w; }




// The gradients are the midpoints of the vertices of a cube.
static const int grad3[12][3] = {
	{1,1,0}, {-1,1,0}, {1,-1,0}, {-1,-1,0},
	{1,0,1}, {-1,0,1}, {1,0,-1}, {-1,0,-1},
	{0,1,1}, {0,-1,1}, {0,1,-1}, {0,-1,-1}
};


// The gradients are the midpoints of the vertices of a hypercube.
static const int grad4[32][4]= {
	{0,1,1,1},  {0,1,1,-1},  {0,1,-1,1},  {0,1,-1,-1},
	{0,-1,1,1}, {0,-1,1,-1}, {0,-1,-1,1}, {0,-1,-1,-1},
	{1,0,1,1},  {1,0,1,-1},  {1,0,-1,1},  {1,0,-1,-1},
	{-1,0,1,1}, {-1,0,1,-1}, {-1,0,-1,1}, {-1,0,-1,-1},
	{1,1,0,1},  {1,1,0,-1},  {1,-1,0,1},  {1,-1,0,-1},
	{-1,1,0,1}, {-1,1,0,-1}, {-1,-1,0,1}, {-1,-1,0,-1},
	{1,1,1,0},  {1,1,-1,0},  {1,-1,1,0},  {1,-1,-1,0},
	{-1,1,1,0}, {-1,1,-1,0}, {-1,-1,1,0}, {-1,-1,-1,0}
};


// Permutation table.  The same list is repeated twice.
static const int perm[512] = {
	151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
	8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
	35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,74,165,71,
	134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
	55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,187,208, 89,
	18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,64,52,217,226,
	250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,
	189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,153,101,155,167,43,
	172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,112,104,218,246,97,
	228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,235,249,14,239,
	107,49,192,214,31,181,199,106,157,184,84,204,176,115,121,50,45,127,4,150,254,
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,

	151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
	8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
	35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,74,165,71,
	134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
	55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,187,208, 89,
	18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,64,52,217,226,
	250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,
	189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,153,101,155,167,43,
	172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,112,104,218,246,97,
	228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,235,249,14,239,
	107,49,192,214,31,181,199,106,157,184,84,204,176,115,121,50,45,127,4,150,254,
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};


// A lookup table to traverse the simplex around a given point in 4D.
static const int simplex[64][4] = {
	{0,1,2,3},{0,1,3,2},{0,0,0,0},{0,2,3,1},{0,0,0,0},{0,0,0,0},{0,0,0,0},{1,2,3,0},
	{0,2,1,3},{0,0,0,0},{0,3,1,2},{0,3,2,1},{0,0,0,0},{0,0,0,0},{0,0,0,0},{1,3,2,0},
	{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},
	{1,2,0,3},{0,0,0,0},{1,3,0,2},{0,0,0,0},{0,0,0,0},{0,0,0,0},{2,3,0,1},{2,3,1,0},
	{1,0,2,3},{1,0,3,2},{0,0,0,0},{0,0,0,0},{0,0,0,0},{2,0,3,1},{0,0,0,0},{2,1,3,0},
	{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},
	{2,0,1,3},{0,0,0,0},{0,0,0,0},{0,0,0,0},{3,0,1,2},{3,0,2,1},{0,0,0,0},{3,1,2,0},
	{2,1,0,3},{0,0,0,0},{0,0,0,0},{0,0,0,0},{3,1,0,2},{0,0,0,0},{3,2,0,1},{3,2,1,0}
};


// 2D Multi-octave Simplex noise.
//
// For each octave, a higher frequency/lower amplitude function will be added to the original.
// The higher the persistence [0-1], the more of each succeeding octave will be added.
float simplexNoise( const float octaves, const float persistence, const float scale, const float x, const float y ) {
	float total = 0;
	float frequency = scale;
	float amplitude = 1;

	// We have to keep track of the largest possible amplitude,
	// because each octave adds more, and we need a value in [-1, 1].
	float maxAmplitude = 0;

	for( int i=0; i < octaves; i++ ) {
		total += simplexRawNoise( x * frequency, y * frequency ) * amplitude;

		frequency *= 2;
		maxAmplitude += amplitude;
		amplitude *= persistence;
	}

	return total / maxAmplitude;
}


// 3D Multi-octave Simplex noise.
//
// For each octave, a higher frequency/lower amplitude function will be added to the original.
// The higher the persistence [0-1], the more of each succeeding octave will be added.
float simplexNoise( const float octaves, const float persistence, const float scale, const float x, const float y, const float z ) {
	float total = 0;
	float frequency = scale;
	float amplitude = 1;

	// We have to keep track of the largest possible amplitude,
	// because each octave adds more, and we need a value in [-1, 1].
	float maxAmplitude = 0;

	for( int i=0; i < octaves; i++ ) {
		total += simplexRawNoise( x * frequency, y * frequency, z * frequency ) * amplitude;

		frequency *= 2;
		maxAmplitude += amplitude;
		amplitude *= persistence;
	}

	return total / maxAmplitude;
}


// 4D Multi-octave Simplex noise.
//
// For each octave, a higher frequency/lower amplitude function will be added to the original.
// The higher the persistence [0-1], the more of each succeeding octave will be added.
float simplexNoise( const float octaves, const float persistence, const float scale, const float x, const float y, const float z, const float w ) {
	float total = 0;
	float frequency = scale;
	float amplitude = 1;

	// We have to keep track of the largest possible amplitude,
	// because each octave adds more, and we need a value in [-1, 1].
	float maxAmplitude = 0;

	for( int i=0; i < octaves; i++ ) {
		total += simplexRawNoise( x * frequency, y * frequency, z * frequency, w * frequency ) * amplitude;

		frequency *= 2;
		maxAmplitude += amplitude;
		amplitude *= persistence;
	}

	return total / maxAmplitude;
}



// 2D Scaled Multi-octave Simplex noise.
//
// Returned value will be between loBound and hiBound.
float simplexScaledNoise( const float octaves, const float persistence, const float scale, const float loBound, const float hiBound, const float x, const float y ) {
	return simplexNoise(octaves, persistence, scale, x, y) * (hiBound - loBound) / 2 + (hiBound + loBound) / 2;
}


// 3D Scaled Multi-octave Simplex noise.
//
// Returned value will be between loBound and hiBound.
float simplexScaledNoise( const float octaves, const float persistence, const float scale, const float loBound, const float hiBound, const float x, const float y, const float z ) {
	return simplexNoise(octaves, persistence, scale, x, y, z) * (hiBound - loBound) / 2 + (hiBound + loBound) / 2;
}

// 4D Scaled Multi-octave Simplex noise.
//
// Returned value will be between loBound and hiBound.
float simplexScaledNoise( const float octaves, const float persistence, const float scale, const float loBound, const float hiBound, const float x, const float y, const float z, const float w ) {
	return simplexNoise(octaves, persistence, scale, x, y, z, w) * (hiBound - loBound) / 2 + (hiBound + loBound) / 2;
}



// 2D Scaled Simplex raw noise.
//
// Returned value will be between loBound and hiBound.
float simplexScaledRawNoise( const float loBound, const float hiBound, const float x, const float y ) {
	return simplexRawNoise(x, y) * (hiBound - loBound) / 2 + (hiBound + loBound) / 2;
}


// 3D Scaled Simplex raw noise.
//
// Returned value will be between loBound and hiBound.
float simplexScaledRawNoise( const float loBound, const float hiBound, const float x, const float y, const float z ) {
	return simplexRawNoise(x, y, z) * (hiBound - loBound) / 2 + (hiBound + loBound) / 2;
}

// 4D Scaled Simplex raw noise.
//
// Returned value will be between loBound and hiBound.
float simplexScaledRawNoise( const float loBound, const float hiBound, const float x, const float y, const float z, const float w ) {
	return simplexRawNoise(x, y, z, w) * (hiBound - loBound) / 2 + (hiBound + loBound) / 2;
}



// 2D raw Simplex noise
float simplexRawNoise( const float x, const float y ) {
	// Noise contributions from the three corners
	float n0, n1, n2;

	// Skew the input space to determine which simplex cell we're in
	float F2 = 0.5 * (sqrtf(3.0) - 1.0);
	// Hairy factor for 2D
	float s = (x + y) * F2;
	int i = fastfloor( x + s );
	int j = fastfloor( y + s );

	float G2 = (3.0 - sqrtf(3.0)) / 6.0;
	float t = (i + j) * G2;
	// Unskew the cell origin back to (x,y) space
	float X0 = i-t;
	float Y0 = j-t;
	// The x,y distances from the cell origin
	float x0 = x-X0;
	float y0 = y-Y0;

	// For the 2D case, the simplex shape is an equilateral triangle.
	// Determine which simplex we are in.
	int i1, j1; // Offsets for second (middle) corner of simplex in (i,j) coords
	if(x0>y0) {i1=1; j1=0;} // lower triangle, XY order: (0,0)->(1,0)->(1,1)
	else {i1=0; j1=1;} // upper triangle, YX order: (0,0)->(0,1)->(1,1)

	// A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
	// a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
	// c = (3-sqrt(3))/6
	float x1 = x0 - i1 + G2; // Offsets for middle corner in (x,y) unskewed coords
	float y1 = y0 - j1 + G2;
	float x2 = x0 - 1.0 + 2.0 * G2; // Offsets for last corner in (x,y) unskewed coords
	float y2 = y0 - 1.0 + 2.0 * G2;

	// Work out the hashed gradient indices of the three simplex corners
	int ii = i & 255;
	int jj = j & 255;
	int gi0 = perm[ii+perm[jj]] % 12;
	int gi1 = perm[ii+i1+perm[jj+j1]] % 12;
	int gi2 = perm[ii+1+perm[jj+1]] % 12;

	// Calculate the contribution from the three corners
	float t0 = 0.5 - x0*x0-y0*y0;
	if(t0<0) n0 = 0.0;
	else {
	t0 *= t0;
	n0 = t0 * t0 * dot(grad3[gi0], x0, y0); // (x,y) of grad3 used for 2D gradient
	}

	float t1 = 0.5 - x1*x1-y1*y1;
	if(t1<0) n1 = 0.0;
	else {
	t1 *= t1;
	n1 = t1 * t1 * dot(grad3[gi1], x1, y1);
	}

	float t2 = 0.5 - x2*x2-y2*y2;
	if(t2<0) n2 = 0.0;
	else {
	t2 *= t2;
	n2 = t2 * t2 * dot(grad3[gi2], x2, y2);
	}

	// Add contributions from each corner to get the final noise value.
	// The result is scaled to return values in the interval [-1,1].
	return 70.0 * (n0 + n1 + n2);
}


// 3D raw Simplex noise
float simplexRawNoise( const float x, const float y, const float z ) {
	float n0, n1, n2, n3; // Noise contributions from the four corners

	// Skew the input space to determine which simplex cell we're in
	float F3 = 1.0/3.0;
	float s = (x+y+z)*F3; // Very nice and simple skew factor for 3D
	int i = fastfloor(x+s);
	int j = fastfloor(y+s);
	int k = fastfloor(z+s);

	float G3 = 1.0/6.0; // Very nice and simple unskew factor, too
	float t = (i+j+k)*G3;
	float X0 = i-t; // Unskew the cell origin back to (x,y,z) space
	float Y0 = j-t;
	float Z0 = k-t;
	float x0 = x-X0; // The x,y,z distances from the cell origin
	float y0 = y-Y0;
	float z0 = z-Z0;

	// For the 3D case, the simplex shape is a slightly irregular tetrahedron.
	// Determine which simplex we are in.
	int i1, j1, k1; // Offsets for second corner of simplex in (i,j,k) coords
	int i2, j2, k2; // Offsets for third corner of simplex in (i,j,k) coords

	if(x0>=y0) {
	if(y0>=z0)
	{ i1=1; j1=0; k1=0; i2=1; j2=1; k2=0; } // X Y Z order
	else if(x0>=z0) { i1=1; j1=0; k1=0; i2=1; j2=0; k2=1; } // X Z Y order
	else { i1=0; j1=0; k1=1; i2=1; j2=0; k2=1; } // Z X Y order
	}
	else { // x0<y0
	if(y0<z0) { i1=0; j1=0; k1=1; i2=0; j2=1; k2=1; } // Z Y X order
	else if(x0<z0) { i1=0; j1=1; k1=0; i2=0; j2=1; k2=1; } // Y Z X order
	else { i1=0; j1=1; k1=0; i2=1; j2=1; k2=0; } // Y X Z order
	}

	// A step of (1,0,0) in (i,j,k) means a step of (1-c,-c,-c) in (x,y,z),
	// a step of (0,1,0) in (i,j,k) means a step of (-c,1-c,-c) in (x,y,z), and
	// a step of (0,0,1) in (i,j,k) means a step of (-c,-c,1-c) in (x,y,z), where
	// c = 1/6.
	float x1 = x0 - i1 + G3; // Offsets for second corner in (x,y,z) coords
	float y1 = y0 - j1 + G3;
	float z1 = z0 - k1 + G3;
	float x2 = x0 - i2 + 2.0*G3; // Offsets for third corner in (x,y,z) coords
	float y2 = y0 - j2 + 2.0*G3;
	float z2 = z0 - k2 + 2.0*G3;
	float x3 = x0 - 1.0 + 3.0*G3; // Offsets for last corner in (x,y,z) coords
	float y3 = y0 - 1.0 + 3.0*G3;
	float z3 = z0 - 1.0 + 3.0*G3;

	// Work out the hashed gradient indices of the four simplex corners
	int ii = i & 255;
	int jj = j & 255;
	int kk = k & 255;
	int gi0 = perm[ii+perm[jj+perm[kk]]] % 12;
	int gi1 = perm[ii+i1+perm[jj+j1+perm[kk+k1]]] % 12;
	int gi2 = perm[ii+i2+perm[jj+j2+perm[kk+k2]]] % 12;
	int gi3 = perm[ii+1+perm[jj+1+perm[kk+1]]] % 12;

	// Calculate the contribution from the four corners
	float t0 = 0.6 - x0*x0 - y0*y0 - z0*z0;
	if(t0<0) n0 = 0.0;
	else {
	t0 *= t0;
	n0 = t0 * t0 * dot(grad3[gi0], x0, y0, z0);
	}

	float t1 = 0.6 - x1*x1 - y1*y1 - z1*z1;
	if(t1<0) n1 = 0.0;
	else {
	t1 *= t1;
	n1 = t1 * t1 * dot(grad3[gi1], x1, y1, z1);
	}

	float t2 = 0.6 - x2*x2 - y2*y2 - z2*z2;
	if(t2<0) n2 = 0.0;
	else {
	t2 *= t2;
	n2 = t2 * t2 * dot(grad3[gi2], x2, y2, z2);
	}

	float t3 = 0.6 - x3*x3 - y3*y3 - z3*z3;
	if(t3<0) n3 = 0.0;
	else {
	t3 *= t3;
	n3 = t3 * t3 * dot(grad3[gi3], x3, y3, z3);
	}

	// Add contributions from each corner to get the final noise value.
	// The result is scaled to stay just inside [-1,1]
	return 32.0*(n0 + n1 + n2 + n3);
}


// 4D raw Simplex noise
float simplexRawNoise( const float x, const float y, const float z, const float w ) {
	// The skewing and unskewing factors are hairy again for the 4D case
	float F4 = (sqrtf(5.0)-1.0)/4.0;
	float G4 = (5.0-sqrtf(5.0))/20.0;
	float n0, n1, n2, n3, n4; // Noise contributions from the five corners

	// Skew the (x,y,z,w) space to determine which cell of 24 simplices we're in
	float s = (x + y + z + w) * F4; // Factor for 4D skewing
	int i = fastfloor(x + s);
	int j = fastfloor(y + s);
	int k = fastfloor(z + s);
	int l = fastfloor(w + s);
	float t = (i + j + k + l) * G4; // Factor for 4D unskewing
	float X0 = i - t; // Unskew the cell origin back to (x,y,z,w) space
	float Y0 = j - t;
	float Z0 = k - t;
	float W0 = l - t;

	float x0 = x - X0; // The x,y,z,w distances from the cell origin
	float y0 = y - Y0;
	float z0 = z - Z0;
	float w0 = w - W0;

	// For the 4D case, the simplex is a 4D shape I won't even try to describe.
	// To find out which of the 24 possible simplices we're in, we need to
	// determine the magnitude ordering of x0, y0, z0 and w0.
	// The method below is a good way of finding the ordering of x,y,z,w and
	// then find the correct traversal order for the simplex we're in.
	// First, six pair-wise comparisons are performed between each possible pair
	// of the four coordinates, and the results are used to add up binary bits
	// for an integer index.
	int c1 = (x0 > y0) ? 32 : 0;
	int c2 = (x0 > z0) ? 16 : 0;
	int c3 = (y0 > z0) ? 8 : 0;
	int c4 = (x0 > w0) ? 4 : 0;
	int c5 = (y0 > w0) ? 2 : 0;
	int c6 = (z0 > w0) ? 1 : 0;
	int c = c1 + c2 + c3 + c4 + c5 + c6;

	int i1, j1, k1, l1; // The integer offsets for the second simplex corner
	int i2, j2, k2, l2; // The integer offsets for the third simplex corner
	int i3, j3, k3, l3; // The integer offsets for the fourth simplex corner

	// simplex[c] is a 4-vector with the numbers 0, 1, 2 and 3 in some order.
	// Many values of c will never occur, since e.g. x>y>z>w makes x<z, y<w and x<w
	// impossible. Only the 24 indices which have non-zero entries make any sense.
	// We use a thresholding to set the coordinates in turn from the largest magnitude.
	// The number 3 in the "simplex" array is at the position of the largest coordinate.
	i1 = simplex[c][0]>=3 ? 1 : 0;
	j1 = simplex[c][1]>=3 ? 1 : 0;
	k1 = simplex[c][2]>=3 ? 1 : 0;
	l1 = simplex[c][3]>=3 ? 1 : 0;
	// The number 2 in the "simplex" array is at the second largest coordinate.
	i2 = simplex[c][0]>=2 ? 1 : 0;
	j2 = simplex[c][1]>=2 ? 1 : 0;
	k2 = simplex[c][2]>=2 ? 1 : 0;
	l2 = simplex[c][3]>=2 ? 1 : 0;
	// The number 1 in the "simplex" array is at the second smallest coordinate.
	i3 = simplex[c][0]>=1 ? 1 : 0;
	j3 = simplex[c][1]>=1 ? 1 : 0;
	k3 = simplex[c][2]>=1 ? 1 : 0;
	l3 = simplex[c][3]>=1 ? 1 : 0;
	// The fifth corner has all coordinate offsets = 1, so no need to look that up.

	float x1 = x0 - i1 + G4; // Offsets for second corner in (x,y,z,w) coords
	float y1 = y0 - j1 + G4;
	float z1 = z0 - k1 + G4;
	float w1 = w0 - l1 + G4;
	float x2 = x0 - i2 + 2.0*G4; // Offsets for third corner in (x,y,z,w) coords
	float y2 = y0 - j2 + 2.0*G4;
	float z2 = z0 - k2 + 2.0*G4;
	float w2 = w0 - l2 + 2.0*G4;
	float x3 = x0 - i3 + 3.0*G4; // Offsets for fourth corner in (x,y,z,w) coords
	float y3 = y0 - j3 + 3.0*G4;
	float z3 = z0 - k3 + 3.0*G4;
	float w3 = w0 - l3 + 3.0*G4;
	float x4 = x0 - 1.0 + 4.0*G4; // Offsets for last corner in (x,y,z,w) coords
	float y4 = y0 - 1.0 + 4.0*G4;
	float z4 = z0 - 1.0 + 4.0*G4;
	float w4 = w0 - 1.0 + 4.0*G4;

	// Work out the hashed gradient indices of the five simplex corners
	int ii = i & 255;
	int jj = j & 255;
	int kk = k & 255;
	int ll = l & 255;
	int gi0 = perm[ii+perm[jj+perm[kk+perm[ll]]]] % 32;
	int gi1 = perm[ii+i1+perm[jj+j1+perm[kk+k1+perm[ll+l1]]]] % 32;
	int gi2 = perm[ii+i2+perm[jj+j2+perm[kk+k2+perm[ll+l2]]]] % 32;
	int gi3 = perm[ii+i3+perm[jj+j3+perm[kk+k3+perm[ll+l3]]]] % 32;
	int gi4 = perm[ii+1+perm[jj+1+perm[kk+1+perm[ll+1]]]] % 32;

	// Calculate the contribution from the five corners
	float t0 = 0.6 - x0*x0 - y0*y0 - z0*z0 - w0*w0;
	if(t0<0) n0 = 0.0;
	else {
	t0 *= t0;
	n0 = t0 * t0 * dot(grad4[gi0], x0, y0, z0, w0);
	}

	float t1 = 0.6 - x1*x1 - y1*y1 - z1*z1 - w1*w1;
	if(t1<0) n1 = 0.0;
	else {
	t1 *= t1;
	n1 = t1 * t1 * dot(grad4[gi1], x1, y1, z1, w1);
	}

	float t2 = 0.6 - x2*x2 - y2*y2 - z2*z2 - w2*w2;
	if(t2<0) n2 = 0.0;
	else {
	t2 *= t2;
	n2 = t2 * t2 * dot(grad4[gi2], x2, y2, z2, w2);
	}

	float t3 = 0.6 - x3*x3 - y3*y3 - z3*z3 - w3*w3;
	if(t3<0) n3 = 0.0;
	else {
	t3 *= t3;
	n3 = t3 * t3 * dot(grad4[gi3], x3, y3, z3, w3);
	}

	float t4 = 0.6 - x4*x4 - y4*y4 - z4*z4 - w4*w4;
	if(t4<0) n4 = 0.0;
	else {
	t4 *= t4;
	n4 = t4 * t4 * dot(grad4[gi4], x4, y4, z4, w4);
	}

	// Sum up and scale the result to cover the range [-1,1]
	return 27.0 * (n0 + n1 + n2 + n3 + n4);
}
 


//Converts a four-character array to an integer, using little-endian form
int toInt(const char* bytes) {
	return (int)(((unsigned char)bytes[3] << 24) |
				 ((unsigned char)bytes[2] << 16) |
				 ((unsigned char)bytes[1] << 8) |
				 (unsigned char)bytes[0]);
}

//Converts a two-character array to a short, using little-endian form
short toShort(const char* bytes) {
	return (short)(((unsigned char)bytes[1] << 8) |
				   (unsigned char)bytes[0]);
}

//Reads the next four bytes as an integer, using little-endian form
int readInt(ifstream &input) {
	char buffer[4];
	input.read(buffer, 4);
	return toInt(buffer);
}

//Reads the next two bytes as a short, using little-endian form
short readShort(ifstream &input) {
	char buffer[2];
	input.read(buffer, 2);
	return toShort(buffer);
}



//Just like auto_ptr, but for arrays
template<class T>
class auto_array {
	private:
		T* array;
		mutable bool isReleased;
	public:
		explicit auto_array(T* array_ = NULL) :
			array(array_), isReleased(false) {
		}
		
		auto_array(const auto_array<T> &aarray) {
			array = aarray.array;
			isReleased = aarray.isReleased;
			aarray.isReleased = true;
		}
		
		~auto_array() {
			if (!isReleased && array != NULL) {
				delete[] array;
			}
		}
		
		T* get() const {
			return array;
		}
		
		T &operator*() const {
			return *array;
		}
		
		void operator=(const auto_array<T> &aarray) {
			if (!isReleased && array != NULL) {
				delete[] array;
			}
			array = aarray.array;
			isReleased = aarray.isReleased;
			aarray.isReleased = true;
		}
		
		T* operator->() const {
			return array;
		}
		
		T* release() {
			isReleased = true;
			return array;
		}
		
		void reset(T* array_ = NULL) {
			if (!isReleased && array != NULL) {
				delete[] array;
			}
			array = array_;
		}
		
		T* operator+(int i) {
			return array + i;
		}
		
		T &operator[](int i) {
			return array[i];
		}
};

//Represents an image
class Image {
public:
		
	/* An array of the form (R1, G1, B1, R2, G2, B2, ...) indicating the
	 * color of each pixel in image.  Color components range from 0 to 255.
	 * The array starts the bottom-left pixel, then moves right to the end
	 * of the row, then moves up to the next column, and so on.  This is the
	 * format in which OpenGL likes images.
	 */
	unsigned char* pixels;
	int width;
	int height;
	GLuint tid;

	int getValue(int x, int y, int c) {
		return pixels[3 * (width * y + x) + c];
	}

	void setValue(int x, int y, int c, int v) {
		pixels[3 * (width * y + x) + c] = v;
	}

	void setAllValues(int c, int v) {
		
		int i;
		int j;

		for (j = 0; j < height; j++) {
			for (i = 0; i < width; i++) {
				pixels[3 * (width * j + i) + c] = v;
			}
		}
		
	}

	Image(unsigned char* ps, int w, int h) : pixels(ps), width(w), height(h) {
		
	}

	~Image() {
		delete[] pixels;
	}

	void getTextureId(GLenum filterType) {
		
		glGenTextures(1, &tid);
		glBindTexture(GL_TEXTURE_2D, tid);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterType);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterType);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D,
					 0,
					 GL_RGB,
					 width, height,
					 0,
					 GL_RGB,
					 GL_UNSIGNED_BYTE,
					 pixels);
	}


};


Image* loadBMP(string fnString) {
	const char* filename = fnString.c_str();
	ifstream input;
	input.open(filename, ifstream::binary);
	assert(!input.fail() || !"Could not find file");
	char buffer[2];
	input.read(buffer, 2);
	assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
	input.ignore(8);
	int dataOffset = readInt(input);
	
	//Read the header
	int headerSize = readInt(input);
	int width;
	int height;
	switch(headerSize) {
		case 40:
			//V3
			width = readInt(input);
			height = readInt(input);
			input.ignore(2);
			assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
			assert(readShort(input) == 0 || !"Image is compressed");
			break;
		case 12:
			//OS/2 V1
			width = readShort(input);
			height = readShort(input);
			input.ignore(2);
			assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
			break;
		case 64:
			//OS/2 V2
			assert(!"Can't load OS/2 V2 bitmaps");
			break;
		case 108:
			//Windows V4
			assert(!"Can't load Windows V4 bitmaps");
			break;
		case 124:
			//Windows V5
			assert(!"Can't load Windows V5 bitmaps");
			break;
		default:
			assert(!"Unknown bitmap format");
	}
	
	//Read the data
	int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
	int size = bytesPerRow * height;
	auto_array<char> pixels(new char[size]);
	input.seekg(dataOffset, ios_base::beg);
	input.read(pixels.get(), size);
	
	//Get the data into the right format
	auto_array<unsigned char> pixels2(new unsigned char[width * height * 3]);

	
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			for(int c = 0; c < 3; c++) {
				pixels2[3 * (width * y + x) + c] =
					pixels[bytesPerRow * y + 3 * x + (2 - c)];
			}
		}
	}
	
	input.close();
	return new Image(pixels2.release(), width, height);
}

 
class FBOWrapper
{
public:

	uint color_tex;

	//uint color_buf;
	//uint depth_buf;
	uint slot;
	int width;
	int height;
	int bytesPerChannel;
	int numMips;
	bool hasMipMap;
	//bool hasDepth;


	GLint internalFormat;

	uint *pixelsUINT;
	unsigned char *pixelsChar;
	unsigned char **pixelsCharMippedMin;
	unsigned char **pixelsCharMippedMax;
	unsigned char **pixelsCharMippedAvg;
	int *mipWidths;

	float *pixelsFloat;
	bool isFloat;

	FBOWrapper() {}
	~FBOWrapper() {}
	int init(
		int _width,
		int _height,
		int _bytesPerChannel,
		int _slot,
		int filterEnum,
		int clampEnum,
		bool isMultisample = false
	) {
		width = _width;
		height = _height;
		bytesPerChannel = _bytesPerChannel;
		//hasDepth = _hasDepth;

		pixelsCharMippedMin = NULL;
		pixelsCharMippedMax = NULL;
		pixelsCharMippedAvg = NULL;

		int w = width;
		int h = height;
		int num_samples = 4;
		numMips = 0;

		isFloat = false;

		pixelsChar = NULL;
		pixelsFloat = NULL;


		slot = GL_COLOR_ATTACHMENT0_EXT;

		switch (_slot) {
		case 0:
			slot = GL_COLOR_ATTACHMENT0_EXT;
			break;
		case 1:
			slot = GL_COLOR_ATTACHMENT1_EXT;
			break;
		case 2:
			slot = GL_COLOR_ATTACHMENT2_EXT;
			break;
		case 3:
			slot = GL_COLOR_ATTACHMENT3_EXT;
			break;
		case 4:
			slot = GL_COLOR_ATTACHMENT4_EXT;
			break;
		case 5:
			slot = GL_COLOR_ATTACHMENT5_EXT;
			break;
		case 6:
			slot = GL_COLOR_ATTACHMENT6_EXT;
			break;
		case 7:
			slot = GL_COLOR_ATTACHMENT7_EXT;
			break;
		}


		if (isMultisample) {
			glGenTextures(1, &color_tex);
			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, color_tex);
			glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, filterEnum);
			glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, filterEnum);
			glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_S, clampEnum);
			glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_T, clampEnum);

			switch (bytesPerChannel) {
			case 1:
				internalFormat = GL_RGBA8;
				
				break;
			case 2:
				internalFormat = GL_RGBA16;
				
				break;
			case 4:
				internalFormat = GL_RGBA32F;
				isFloat = true;

				break;
			}
			
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, num_samples, internalFormat, w, h, false );
			glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, slot, GL_TEXTURE_2D_MULTISAMPLE, color_tex, 0);
			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
		}
		else {
			glGenTextures(1, &color_tex);
			glBindTexture(GL_TEXTURE_2D, color_tex);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterEnum);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterEnum);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, clampEnum);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, clampEnum);

			switch (bytesPerChannel) {
			case 1:
				internalFormat = GL_RGBA8;
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

				break;
			case 2:
				internalFormat = GL_RGBA16;
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, w, h, 0, GL_RGBA, GL_UNSIGNED_SHORT, 0);

				break;
			case 4:
				internalFormat = GL_RGBA32F;
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, w, h, 0, GL_RGBA, GL_FLOAT, 0);
				isFloat = true;

				break;
			}

			glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, slot, GL_TEXTURE_2D, color_tex, 0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		
		
		
		
		
	TOT_GPU_MEM_USAGE += ((float)(w * h * bytesPerChannel * 4)) / (1024.0f * 1024.0f);

	return 1;





		//
		/*
		if (hasDepth) {
		  glGenRenderbuffersEXT(1, &depth_rb);
		  glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depth_rb);
		  glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, w, h);
		  glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depth_rb);
		}
		*/


		//

	}


	void cpuToGPU() {

		if (pixelsChar == NULL) {
			doTrace("error: null pointer pixelsChar");
			return;
		}

		switch (bytesPerChannel) {
		case 1:

			glBindTexture(GL_TEXTURE_2D, color_tex);
			/*
			glTexSubImage2D(
			  GL_TEXTURE_2D,
			  0,

			  0,
			  0,
			  width,
			  height,

			  GL_RGBA,
			  GL_UNSIGNED_BYTE,
			  pixelsChar
			 );
			 */


			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelsChar);

			glBindTexture(GL_TEXTURE_2D, 0);

			break;
		case 2:
			doTrace("TODO: implement 16 bit");
			break;
		case 4:
			doTrace("TODO: implement 32 bit");
			break;
		}



	}



	void getPixelAtF(FIVector4 *fv, int x, int y) {

		if (isFloat) {


			if ( (pixelsFloat == NULL) ) {
				getPixels();
			}

			//a
			//b
			//g
			//r

			fv->setFX(pixelsFloat[ (x + y * width) * 4 + 0 ]);
			fv->setFY(pixelsFloat[ (x + y * width) * 4 + 1 ]);
			fv->setFZ(pixelsFloat[ (x + y * width) * 4 + 2 ]);
			fv->setFW(pixelsFloat[ (x + y * width) * 4 + 3 ]);

		}
		else {
			doTrace("Attempted to call getPixelAtF on char buffer.");
		}

	}

	void setAllPixels(int channel, int value) {
		int i;
		int j;
		int x;
		int y;

		for (j = 0; j < height; j++) {
			for (i = 0; i < width; i++) {
				x = i;
				y = j;
				pixelsChar[ (x + y * width) * 4 + channel ] = value;
			}
		}
	}

	void setPixelAtC(int x, int y, int channel, unsigned char value) {
		pixelsChar[ (x + y * width) * 4 + channel ] = value;
	}


	int getIndex(int xs, int ys) {
		int x = xs;
		int y = ys;

		while (x < 0) {
			x += width;
		}
		while (y < 0) {
			y += height;
		}

		x = x % width;
		y = y % height;

		return x + y * width;
	}

	void setPixelAtWrapped(int xs, int ys, int channel, int val) {

		int x = xs;
		int y = ys;

		while (x < 0) {
			x += width;
		}
		while (y < 0) {
			y += height;
		}

		x = x % width;
		y = y % height;

		int ind = x + y * width;

		pixelsChar[ind * 4 + channel] = val;
	}

	int getPixelAtWrapped(int xs, int ys, int channel) {

		int x = xs;
		int y = ys;

		while (x < 0) {
			x += width;
		}
		while (y < 0) {
			y += height;
		}

		x = x % width;
		y = y % height;

		int ind = x + y * width;

		return pixelsChar[ind * 4 + channel];
	}

	int getPixelAtIndex(int ind, int channel) {
		return pixelsChar[ind * 4 + channel];
	}
	void setPixelAtIndex(int ind, int channel, int val) {
		pixelsChar[ind * 4 + channel] = val;
	}
	void orPixelAtIndex(int ind, int channel, int val) {
		pixelsChar[ind * 4 + channel] |= val;
	}
	void andPixelAtIndex(int ind, int channel, int val) {
		pixelsChar[ind * 4 + channel] &= val;
	}

	int getPixelAtC(int x, int y, int channel) {

		if (!isFloat) {
			if ( (pixelsChar == NULL) ) {
				getPixels();
			}

			return (int)pixelsChar[ (x + y * width) * 4 + channel ];

		}
		else {
			doTrace("Attempted to call getPixelAtC on float buffer.");
			return 0;
		}

	}

	float getPixelAtLinear(float xf, float yf, int channel) {
		int x[2];
		int y[2];

		x[0] = floor(xf);
		y[0] = floor(yf);
		x[1] = x[0] + 1;
		y[1] = y[0] + 1;

		float percX = xf - x[0];
		float percY = yf - y[0];
		float percXI = 1.0f - percX;
		float percYI = 1.0f - percY;


		float v0, v1;
		float v2, v3;

		int i;

		for (i = 0; i < 2; i++) {

			while (x[i] < 0) {
				x[i] += width;
			}
			while (y[i] < 0) {
				y[i] += height;
			}

			x[i] = x[i] % width;
			y[i] = y[i] % height;
		}

		v0 = getPixelAtC(x[0], y[0], channel) / 255.0f;
		v1 = getPixelAtC(x[1], y[0], channel) / 255.0f;
		v2 = getPixelAtC(x[0], y[1], channel) / 255.0f;
		v3 = getPixelAtC(x[1], y[1], channel) / 255.0f;

		float vFinal = (v0 * percXI + v1 * percX) * percYI + (v2 * percXI + v3 * percX) * percY;

		return vFinal;

	}


	int getMipVal(
		int x,
		int y,
		int mipLev,
		int channel,
		int minMaxAvg,
		int val = -1,
		int ox = 0,
		int oy = 0
	) {

		int w = mipWidths[mipLev];
		int curWidth = mipWidths[mipLev];
		int mipPitch = 1 << mipLev;
		int xv;
		int yv;

		float t1;
		float t2;
		float t3;

		xv = intDiv(x * curWidth, mipWidths[0]) + ox;
		yv = intDiv(y * curWidth, mipWidths[0]) + oy;

		// if (x < 0) {
		//  t1 = -x*curWidth;
		//  t2 = mipWidths[0];
		//  t3 = -ceil(t1/t2);
		//  xv = t3 + ox;

		// }
		// else {
		//  xv = ((x*curWidth)/mipWidths[0]) + ox;
		// }

		// if (y < 0) {
		//  t1 = -y*curWidth;
		//  t2 = mipWidths[0];
		//  t3 = -ceil(t1/t2);
		//  yv = t3 + oy;
		// }
		// else {
		//  yv = ((y*curWidth)/mipWidths[0]) + oy;
		// }




		while (xv < 0) {
			xv += curWidth;
		}
		while (xv >= curWidth) {
			xv -= curWidth;
		}
		while (yv < 0) {
			yv += curWidth;
		}
		while (yv >= curWidth) {
			yv -= curWidth;
		}

		int ind = xv + yv * curWidth;
		int res = 0;
		int resInd = (ind) * 4 + channel;

		if (val != -1) {
			switch (minMaxAvg) {
			case 0:
				(pixelsCharMippedMin[mipLev][resInd]) = val;
				break;
			case 1:
				(pixelsCharMippedMax[mipLev][resInd]) = val;
				break;
			case 2:
				(pixelsCharMippedAvg[mipLev][resInd]) = val;
				break;
			}
		}

		switch (minMaxAvg) {
		case 0:
			res = (int) (pixelsCharMippedMin[mipLev][resInd]);
			break;
		case 1:
			res = (int) (pixelsCharMippedMax[mipLev][resInd]);
			break;
		case 2:
			res = (int) (pixelsCharMippedAvg[mipLev][resInd]);
			break;
		}



		return res;

	}

	int getMipAtIndex(int ind, int mipLev, int channel, int minMaxAvg) {
		int res = 0;
		int resInd = ind * 4 + channel;

		switch (minMaxAvg) {
		case 0:
			res = (int) (pixelsCharMippedMin[mipLev][resInd]);
			break;
		case 1:
			res = (int) (pixelsCharMippedMax[mipLev][resInd]);
			break;
		case 2:
			res = (int) (pixelsCharMippedAvg[mipLev][resInd]);
			break;
		}

		return res;
	}

	int getMipInd(int x, int y, int mipLev) {
		int w = mipWidths[mipLev];

		return ((x * mipWidths[mipLev]) / mipWidths[0]) + ((y * mipWidths[mipLev]) / mipWidths[0]) * mipWidths[mipLev];
	}

	void updateMips() {

		int i;
		int j;
		int k;
		int m;

		int ind, ind0, ind1, ind2, ind3;

		int mRead;
		int mWrite;

		if (pixelsCharMippedAvg == NULL) {
			doTrace("Error: no mip maps, first call getPixels()");
			return;
		}
		else {
			for (m = 0; m < numMips - 1; m++) {

				mRead = m;
				mWrite = m + 1;

				for (k = 0; k < 4; k++) {

					for (i = 0; i < mipWidths[mWrite]; i++) {
						for (j = 0; j < mipWidths[mWrite]; j++) {

							ind = (i + j * mipWidths[mWrite]) * 4 + k;

							ind0 = ( (i * 2 + 0) + (j * 2 + 0) * mipWidths[mRead] ) * 4 + k; //
							ind1 = ( (i * 2 + 1) + (j * 2 + 0) * mipWidths[mRead] ) * 4 + k; //
							ind2 = ( (i * 2 + 0) + (j * 2 + 1) * mipWidths[mRead] ) * 4 + k; //
							ind3 = ( (i * 2 + 1) + (j * 2 + 1) * mipWidths[mRead] ) * 4 + k; //

							pixelsCharMippedAvg[ mWrite ][ ind ] = (
									pixelsCharMippedAvg[ mRead ][ind0] +
									pixelsCharMippedAvg[ mRead ][ind1] +
									pixelsCharMippedAvg[ mRead ][ind2] +
									pixelsCharMippedAvg[ mRead ][ind3]
																										 ) / 4;

							pixelsCharMippedMin[ mWrite ][ ind ] = min(
									min(
										pixelsCharMippedMin[ mRead ][ind0],
										pixelsCharMippedMin[ mRead ][ind1]
									),
									min(
										pixelsCharMippedMin[ mRead ][ind2],
										pixelsCharMippedMin[ mRead ][ind3]
									)
																										 );

							pixelsCharMippedMax[ mWrite ][ ind ] = max(
									max(
										pixelsCharMippedMax[ mRead ][ind0],
										pixelsCharMippedMax[ mRead ][ind1]
									),
									max(
										pixelsCharMippedMax[ mRead ][ind2],
										pixelsCharMippedMax[ mRead ][ind3]
									)
																										 );




						}
					}

				}
			}
		}
	}


	void getPixelsFast() {



		glBindTexture(GL_TEXTURE_2D, color_tex);
		GLint numBytes = 0;
		int totalWidth;
		int curBytes;

		numBytes = width * height;

		if (pixelsUINT == NULL) {
			pixelsUINT = new uint[numBytes];
		}
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelsUINT);
		glBindTexture(GL_TEXTURE_2D, 0);

	}
	
	// assumed that remoteBuffer is allocated
	void getPixelsFastRemote(uint* remoteBuffer) {


		glBindTexture(GL_TEXTURE_2D, color_tex);
		GLint numBytes = 0;
		int totalWidth;
		int curBytes;
		numBytes = width * height;
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, remoteBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);

	}


	void getPixels(bool _hasMipMap = false) {



		glBindTexture(GL_TEXTURE_2D, color_tex);
		GLint numBytes = 0;

		int targetlevel = 0;
		int index;
		int i;
		int totalWidth;
		int curBytes;

		//GLint intForm;
		//glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPONENTS, &intForm); // get internal format type of GL texture


		switch (internalFormat) // determine what type GL texture has...
		{
		case GL_RGB:
			numBytes = width * height * 3;
			break;
		case GL_RGBA:
			numBytes = width * height * 4;
			break;
		case GL_RGBA8:
			numBytes = width * height * 4;
			break;
			//case GL_RGBA16:
			//
			//break;
		case GL_RGBA32F:
			numBytes = width * height * 4 * 4;
			break;

		default:
			doTrace("Unsupported Format Type");
			return;
			break;
		}

		if (numBytes) {

			if (isFloat) {

				if (pixelsFloat == NULL) {
					pixelsFloat = new float[numBytes];//(float*)malloc(numBytes);
				}

				glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, pixelsFloat);
			}
			else {

				if (pixelsChar == NULL) {
					pixelsChar = new unsigned char[numBytes];


					if (_hasMipMap) {

						hasMipMap = _hasMipMap;

					}


					index = width;
					if (index == 0) {
						doTrace("Error: width of 0");
						return;
					}
					else {
						while (index >>= 1) {
							++targetlevel;
						}
						numMips = targetlevel;

					}

					pixelsCharMippedAvg = new unsigned char*[numMips];
					pixelsCharMippedMax = new unsigned char*[numMips];
					pixelsCharMippedMin = new unsigned char*[numMips];
					mipWidths = new int[numMips];


					pixelsCharMippedAvg[0] = pixelsChar;
					pixelsCharMippedMax[0] = pixelsChar;
					pixelsCharMippedMin[0] = pixelsChar;

					mipWidths[0] = width;

					if (hasMipMap) {

						totalWidth = width / 2;
						curBytes = numBytes / 2;

						for (i = 1; i < numMips; i++) {
							pixelsCharMippedMin[i] = new unsigned char[curBytes];
							pixelsCharMippedMax[i] = new unsigned char[curBytes];
							pixelsCharMippedAvg[i] = new unsigned char[curBytes];
							mipWidths[i] = totalWidth;

							totalWidth = totalWidth / 2;
							curBytes = curBytes / 2;
						}
					}

				}
				glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelsChar);
			}


		}

		glBindTexture(GL_TEXTURE_2D, 0);


	}


};


class FBOSet
{
public:
	int numBufs;
	int width;
	int height;
	int bytesPerChannel;

	uint depth_rb;

	GLuint mFBO;

	FBOWrapper *fbos;

	bool hasDepth;

	FBOSet() {}
	~FBOSet() {}

	FBOWrapper *getFBOWrapper(int offset) {
		return &(fbos[offset]);
	}

	void init(
		int _numBufs,
		int _width,
		int _height,
		int _bytesPerChannel,
		bool _hasDepth,
		int filterEnum = GL_NEAREST,
		int clampEnum = GL_CLAMP_TO_EDGE,
		bool isMultisample = false
	) {
		int i;

		hasDepth = _hasDepth;

		numBufs = _numBufs;
		height = _height;
		width = _width;
		bytesPerChannel = _bytesPerChannel;

		fbos = new FBOWrapper[numBufs];


		glGenFramebuffersEXT(1, &mFBO);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mFBO);

		for (i = 0; i < numBufs; i++) {
			fbos[i].init(width, height, bytesPerChannel, i, filterEnum, clampEnum, isMultisample);
		}


		if (hasDepth) {
			glGenRenderbuffersEXT(1, &depth_rb);
			glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depth_rb);
			glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, width, height);
			glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depth_rb);
		}


		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	}
	void bind(int doClear) {

		//setWH(width, height);

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mFBO);

		GLenum buffers[] = {GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_COLOR_ATTACHMENT2_EXT, GL_COLOR_ATTACHMENT3_EXT, GL_COLOR_ATTACHMENT4_EXT};
		glDrawBuffers(numBufs, buffers);

		if (doClear) {
			glClearColor(0.0, 0.0, 0.0, 0.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

	}
	void copyFromMem(int ind, unsigned char *dat) {

		//glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mFBO);

		glBindTexture(GL_TEXTURE_2D, fbos[ind].color_tex);

		//glTexSubImage2D(GLenum target​, GLint level​, GLint xoffset​, GLint yoffset​, GLsizei width​, GLsizei height​, GLenum format​, GLenum type​, const GLvoid * data​);

		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, dat);
		//glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, fbos[ind].slot, GL_TEXTURE_2D, fbos[ind].color_tex, 0);
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);

		//glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	}
};

 

// class WebSocketRequestHandler;
// class WebSocketServer;
// class RequestHandlerFactory;
class GameGeom;
class Singleton;
class Shader;
class GameSound;
class GameMusic;
class FontWrapper;
class UIComponent;
class GameGUI;
class GameEntNode;
class GameEnt;
class GamePlantNode;
class GamePlant;
class GameBlock;
class GamePageHolder;
class GamePage;
class GameWorld;
class PooledResource;
class PoolManager;
class PoolPageManager;
 
// f00293_gamesound.e
//

#ifndef LZZ_f00293_gamesound_e
#define LZZ_f00293_gamesound_e
#define LZZ_INLINE inline
class GameSound
{
public:
  sf::SoundBuffer buffer;
  sf::Sound sound;
  GameSound ();
  void init (string path);
  void setPitch (float val);
  void setPositionAndMinDis (float x, float y, float z, float w);
  void setLoop (bool val);
  void stop ();
  void play (float volume = 1.0f);
};
#undef LZZ_INLINE
#endif
// f00294_gamemusic.e
//

#ifndef LZZ_f00294_gamemusic_e
#define LZZ_f00294_gamemusic_e
#define LZZ_INLINE inline
class GameMusic
{
public:
  sf::Music sound;
  float volume;
  GameMusic ();
  void init (string path);
  void setLoop (bool val);
  void stop ();
  void setVolume (float _volume = 1.0f);
  void play (float _volume = 1.0f);
};
#undef LZZ_INLINE
#endif
// f00295_gamegeom.e
//

#ifndef LZZ_f00295_gamegeom_e
#define LZZ_f00295_gamegeom_e
#define LZZ_INLINE inline
class GameGeom
{
private:
  FIVector4 boundsMinInPixels;
  FIVector4 boundsMaxInPixels;
  FIVector4 visMinInPixels;
  FIVector4 visMaxInPixels;
public:
  FIVector4 (geomParams) [E_GP_LENGTH];
  FIVector4 anchorPointInPixels;
  FIVector4 moveMinInPixels;
  FIVector4 moveMaxInPixels;
  GameLight * light;
  bool visible;
  bool hasAnchor;
  bool isToggled;
  int rotDir;
  int minRot;
  int maxRot;
  int curRot;
  int buildingType;
  int id;
  int globalId;
  GameGeom ();
  void init (int _id);
  FIVector4 tempVec1;
  FIVector4 tempVec2;
  FIVector4 tempVec3;
  FIVector4 * getBoundsMinInPixels ();
  FIVector4 * getBoundsMaxInPixels ();
  FIVector4 * getVisMinInPixels ();
  FIVector4 * getVisMaxInPixels ();
  FIVector4 * getBoundsMinInPixelsT ();
  FIVector4 * getBoundsMaxInPixelsT ();
  FIVector4 * getVisMinInPixelsT ();
  FIVector4 * getVisMaxInPixelsT ();
  int getClampedRot ();
  void rotate (int mod, bool ignoreConstraints);
  void initBounds (int _buildingType, int _id, int _globalId, int alignBottomMiddleTop, float _zOffset, FIVector4 * p1, FIVector4 * p2, FIVector4 * rad, FIVector4 * _cornerDisInPixels, FIVector4 * _visInsetFromMin, FIVector4 * _visInsetFromMax, FIVector4 * _powerVals, FIVector4 * _powerVals2, FIVector4 * _thickVals, FIVector4 * _matParams, FIVector4 * _centerPoint, FIVector4 * _anchorPoint, int _minRot, int _maxRot);
  void initLines (int _buildingType, int _id, int _globalId, float scale, FIVector4 * _offset, FIVector4 * _orgVec, FIVector4 * _tanVec, FIVector4 * _bitVec, FIVector4 * _norVec, FIVector4 * _radVec0, FIVector4 * _radVec1, FIVector4 * _radVecScale0, FIVector4 * _radVecScale1, FIVector4 * _matParams);
  void initTree (int _buildingType, int _id, int _globalId, FIVector4 * p0, FIVector4 * p1, FIVector4 * p2, float radP0, float radP1, float sphereRad, FIVector4 * _matParams);
  void toggleTransform ();
  void applyTransform (int rotMod, bool ignoreConstraints);
  void initAnchorPoint (FIVector4 * _anchorPointInPixels, int _minRot, int _maxRot);
};
#undef LZZ_INLINE
#endif
// f00300_singleton.e
//

#ifndef LZZ_f00300_singleton_e
#define LZZ_f00300_singleton_e
#define LZZ_INLINE inline
class Singleton
{
public:
  struct UIQuad
  {
    fBoundingBox hitBounds;
    CharStruct * cs;
    int fontId;
  };
  struct UICont
  {
    UIComponent * uiComp;
    UIQuad bg;
    std::vector <UIQuad> charVec;
  };
  struct JSONStruct
  {
    JSONValue * jv;
  };
  struct UICStruct
  {
    UIComponent * uic;
    int nodeId;
  };
  struct CompareStruct
  {
    bool operator () (string const & first, string const & second);
  };
  CompareStruct compareStruct;
  typedef map <string, UICStruct>::iterator itUICStruct;
  E_OBJ activeObject;
  E_OBJ tempObj;
  int mouseState;
  eProgramState programState;
  eProgramAction (progActionsDown) [E_PS_SIZE * 256];
  eProgramAction (progActionsUp) [E_PS_SIZE * 256];
  float scrollDiv;
  float masterVolume;
  float ambientVolume;
  float guiVolume;
  float musicVolume;
  float fxVolume;
  bool (isInteractiveGeom) [E_CT_LENGTH];
  bool pathfindingOn;
  bool isMacro;
  bool entOn;
  bool autoScroll;
  bool cavesOn;
  bool bakeParamsOn;
  bool dragging;
  bool mouseMoved;
  bool changingGenVal;
  bool readyForRestart;
  bool forceRestart;
  bool hitGUI;
  bool guiLock;
  bool guiDirty;
  bool guiOn;
  bool mirrorOn;
  bool applyToChildren;
  bool bShiftOld;
  bool bCtrlOld;
  bool bCtrl;
  bool bShift;
  bool tiltChanged;
  bool testOn;
  bool emptyVDNotReady;
  bool radiosityOn;
  bool updateLock;
  bool isFullScreen;
  bool changesMade;
  bool mapInvalid;
  bool bufferInvalid;
  bool wsBufferInvalid;
  bool forceGetPD;
  bool mouseLeftDown;
  bool mouseRightDown;
  bool pboSupported;
  bool notQuit;
  bool timerNotSet;
  bool lbDown;
  bool abDown;
  bool rbDown;
  bool mbDown;
  bool isZooming;
  bool isPanning;
  bool isBare;
  bool showMap;
  bool traceOn;
  bool waterOn;
  bool treesOn;
  bool firstRun;
  bool rotOn;
  int maxLayerOver;
  int holderMod;
  float fHolderMod;
  int holderResolution;
  int visPageSizeInUnits;
  int bufferedPageSizeInUnits;
  int unitSizeInPixels;
  int holdersPerLot;
  int pixelsPerLot;
  int pixelsPerMeter;
  int visPageSizeInPixels;
  int holderSizeInPixels;
  int currentStep;
  int maxLayers;
  int maxChangesInPages;
  int maxChangesInHolders;
  int baseW;
  int baseH;
  int scaleFactor;
  int numDynLights;
  int iNumSteps;
  int curEntId;
  int metersPerLot;
  int extraRad;
  int defaultWinW;
  int defaultWinH;
  int guiWinW;
  int guiWinH;
  int shadersAreLoaded;
  int readyToRecompile;
  int lastPosX;
  int lastPosY;
  int frameCount;
  int maxHInPages;
  int maxWInPages;
  int minWInPages;
  int screenWidth;
  int screenHeight;
  int mouseMovingSize;
  int mouseMovingLoc;
  int mouseMovingStepsBack;
  int mouseCount;
  int lastMouseX;
  int lastMouseY;
  int voroSize;
  int geomCounter;
  int lightCounter;
  int charState;
  int skipFrames;
  float msPerFrame;
  int metersPerNodeXY;
  int terDataVisPitchXY;
  int terDataBufPitchXY;
  int terDataBufPitchScaledXY;
  int metersPerNodeZ;
  int terDataVisPitchZ;
  int terDataBufPitchZ;
  int terDataBufPitchScaledZ;
  int terDataBufAmount;
  int terDataVisSize;
  int terDataBufSize;
  int terDataTexScale;
  int terDataBufSizeScaled;
  uint * terDataScaled;
  int iNodeDivsPerLot;
  int selGeomListInd;
  int holderSizeInPages;
  uint volGenFBOX;
  uint palWidth;
  uint palHeight;
  uint blockShift;
  float fogOn;
  float gridOn;
  float mapSampScale;
  float curBrushRad;
  float timeOfDay;
  float targetTimeOfDay;
  float gridSizeInPixels;
  float origWinW;
  float origWinH;
  float guiX;
  float guiY;
  float tiltAmount;
  float currentFBOResolutionX;
  float currentFBOResolutionY;
  float mouseX;
  float mouseY;
  float mouseXUp;
  float mouseYUp;
  float cameraZoom;
  float targetZoom;
  float curTime;
  float lastTime;
  float myDelta;
  float mdTime;
  float muTime;
  float bufferMult;
  float holderSizeMB;
  float bestNodeDis;
  float * paramArr;
  float * voroArr;
  float * matCountArr;
  float * paramArrMap;
  int * geomIdArr;
  double curMS;
  GameEntNode * bestNode;
  GameEntNode * selectedNode;
  GameEntNode * lastSelNode;
  GameEntNode * activeNode;
  FIVector4 cameraPosAdjusted;
  FIVector4 baseScrollPos;
  FIVector4 worldSizeInPixels;
  FIVector4 mouseUpPD;
  FIVector4 mouseDownPD;
  FIVector4 mouseMovePD;
  FIVector4 geomPD;
  FIVector4 tempVec1;
  FIVector4 tempVec2;
  FIVector4 tempVec3;
  FIVector4 worldSizeInTerData;
  FIVector4 worldSizeInUnits;
  FIVector4 worldSizeInPages;
  FIVector4 worldSizeInLots;
  FIVector4 worldSizeInMeters;
  FIVector4 worldSizeInHolders;
  FIVector4 worldSizeInBlocks;
  FIVector4 (moveNodes) [2];
  FIVector4 (voroVecArr) [125];
  floatAndIndex (indexArr) [125];
  FIVector4 mouseStart;
  FIVector4 mouseEnd;
  FIVector4 mapFreqs;
  FIVector4 mapAmps;
  FIVector4 * mouseMoving;
  FIVector4 mouseVel;
  FIVector4 bufferDim;
  FIVector4 bufferDimTarg;
  FIVector4 bufferDimHalf;
  FIVector4 bufferModDim;
  FIVector4 origin;
  FIVector4 lastModXYZ;
  FIVector4 panMod;
  FIVector4 dMod;
  FIVector4 modXYZ;
  std::vector <UICont*> (guiLayers) [MAX_UI_LAYERS];
  std::vector <RotationInfo> rotMatStack;
  std::vector <DynObject *> dynObjects;
  std::vector <GameGeom *> selGeomList;
  PathHolder charPathHolder;
  PathHolder splitPathHolder;
  float floorHeightInMeters;
  float roofHeightInMeters;
  float wallRadInMeters;
  int metersPerHolder;
  int metersPerPage;
  int unitsPerMeter;
  int blockSizeInLots;
  int blockSizeInMeters;
  int blockSizeInHolders;
  int blockSizeInPages;
  int blockSizeInPixels;
  Image * imageHM0;
  Image * imageHM1;
  Image * cloudImage;
  GameGeom * highlightedGeom;
  GameGeom * selectedGeom;
  GameGeom * curGeom;
  GamePlant * (gamePlants) [E_PT_LENGTH/2];
  Shader * curShaderPtr;
  string curShader;
  string allText;
  string stringBuf;
  string curCallback;
  string (cbDataStrings) [10];
  string guiSaveLoc;
  PoolManager * gpuPool;
  PoolManager * entityPool;
  vector <string> shaderStrings;
  vector <string> shaderTextureIds;
  map <string, Shader*> shaderMap;
  map <string, UICStruct> compMap;
  map <string, FBOSet> fboMap;
  FBOSet (vgFBOArr) [MAX_VG_FBOS];
  GLuint volId;
  GLuint volIdLinear;
  GLuint volIdEmpty;
  GLuint volIdEmptyLinear;
  GLuint volGenId;
  GLuint volTris;
  GLuint sliceTris;
  uint * lookup2to3;
  unsigned char * resultImage;
  charArr nullBuffer;
  charArr lastImageBuffer;
  charArr lastJSONBuffer;
  charArr lastJSONBufferGUI;
  JSONValue * rootObjJS;
  JSONValue * guiRootJS;
  Timer myTimer;
  Timer scrollTimer;
  GameWorld * gw;
  float (lightArr) [MAX_LIGHTS * 16];
  int numLights;
  bool multiLights;
  int * rbStack;
  int * rbHeightStack;
  TerTexture (terTextures) [MAX_TER_TEX];
  GameEnt * testHuman;
  GameGUI * mainGUI;
  FontWrapper * (fontWrappers) [EFW_LENGTH];
  GameMusic * (music) [EML_LENGTH];
  map <string, GameSound> soundMap;
  map <string, StyleSheet> styleSheetMap;
  map <string, JSONStruct> internalJSON;
  Singleton ();
  void init (int _defaultWinW, int _defaultWinH, int _scaleFactor);
  void prepSound (string soundName);
  void playSoundPosAndPitch (string soundName, FIVector4 * listenerPos, FIVector4 * soundPos, float variance = 0.0f, float volume = 1.0f);
  void playSound (string soundName, float volume = 1.0f);
  void playSoundEvent (char const * eventName, bool suppress = false);
  void dispatchEvent (int button, int state, float x, float y, UIComponent * comp, bool automated = false, bool preventRefresh = false);
  StyleSheet * getNewStyleSheet (string ssName);
  void initStyleSheet ();
  int requestTerIndex (int requestingBlockId);
  static void qNormalizeAngle (int & angle);
  void perspectiveProjection ();
  void orthographicProjection ();
  ~ Singleton ();
  void setProgAction (eProgramState ps, unsigned char kc, eProgramAction pa, bool isDown);
  void setProgActionAll (unsigned char kc, eProgramAction pa, bool isDown);
  void drawCrossHairs (FIVector4 originVec, float radius);
  void drawLine (FIVector4 * p0, FIVector4 * p1);
  void drawCubeCentered (FIVector4 * originVec, float radius);
  void drawBoxUp (FIVector4 originVec, float radiusX, float radiusY, float diamZ);
  void drawBox (FIVector4 * minVec, FIVector4 * maxVec, int faceFlag = 2);
  void createVTListTilt ();
  void createVTList ();
  void doShaderRefresh (bool doBake);
  void setMatrices (int w, int h);
  void setWH (int w, int h);
  void sampleFBODirect (FBOSet * fbos, int offset = 0);
  void unsampleFBODirect (FBOSet * fbos, int offset = 0);
  void bindFBODirect (FBOSet * fbos, int doClear = 1);
  void sampleFBO (string fboName, int offset = 0, int swapFlag = -1);
  void unsampleFBO (string fboName, int offset = 0, int swapFlag = -1);
  FBOSet * getFBOSet (string fboName);
  FBOWrapper * getFBOWrapper (string fboName, int offset);
  void copyFBO (string src, string dest, int num = 0);
  void copyFBO2 (string src, string dest);
  void bindFBO (string fboName, int swapFlag = -1);
  void unbindFBO ();
  void bindShader (string shaderName);
  void unbindShader ();
  void setShaderArrayfVec3 (string paramName, float * x, int count);
  void setShaderArrayfVec4 (string paramName, float * x, int count);
  void setShaderArray (string paramName, float * x, int count);
  void setShaderFloat (string paramName, float x);
  void setShaderInt (string paramName, int x);
  void setShaderfVec2 (string paramName, FIVector4 * v);
  void setShaderVec2 (string paramName, float x, float y);
  void setShaderVec3 (string paramName, float x, float y, float z);
  void setShaderfVec3 (string paramName, FIVector4 * v);
  void setShaderVec4 (string paramName, float x, float y, float z, float w);
  void setShaderfVec4 (string paramName, FIVector4 * v);
  void setShaderFloatUB (string paramName, float x);
  void setShaderfVec4UB (string paramName, FIVector4 * v);
  void updateUniformBlock (int ubIndex, int ubDataSize = -1);
  void invalidateUniformBlock (int ubIndex);
  void beginUniformBlock (int ubIndex);
  bool wasUpdatedUniformBlock (int ubIndex);
  void setShaderTexture (int multitexNumber, uint texId);
  void setShaderTexture3D (int multitexNumber, uint texId);
  bool shiftDown ();
  bool ctrlDown ();
  bool altDown ();
  void drawQuadBounds (float fx1, float fy1, float fx2, float fy2, float fz);
  void drawFSQuad (float zoom);
  void drawFSQuadOffset (float xOff, float yOff, float zoom);
  void drawFBO (string fboName, int ind, float zoom, int swapFlag = -1);
  void drawFBOOffsetDirect (FBOSet * fbos, int ind, float xOff, float yOff, float zoom);
  void drawFBOOffset (string fboName, int ind, float xOff, float yOff, float zoom);
  float getTerHeightScaled (float val);
  float getSLNormalized ();
  float getSLInPixels ();
  float getHeightAtPixelPos (float x, float y, bool dd = false);
  void syncObjects (FIVector4 * bp);
  void moveCamera (FIVector4 * pModXYZ);
  GameEntNode * getMirroredNode (GameEntNode * curNode);
  void applyNodeChanges (GameEntNode * _curNode, float dx, float dy);
  void moveObject (float dx, float dy, float zoom);
  void updateMultiLights ();
  void toggleFullScreen ();
  void restartGen (bool instantRefresh, bool clearEverything);
  void setObjToElevationBase (FIVector4 * obj);
  void setCameraToElevationBase ();
  void setCameraToElevation ();
  void processSpecialKeys (int key, int _x, int _y);
  void updateCS ();
  void processKey (unsigned char key, int _x, int _y, bool isPressed);
  void keyboardUp (unsigned char key, int _x, int _y);
  void keyboardDown (unsigned char key, int _x, int _y);
  void runReport ();
  void getPixData (FIVector4 * toVector, int _xv, int _yv, int bufNum = 0, bool forceGet = false);
  GameGeom * findNearestGeom (FIVector4 * testPoint, bool createList = false, bool onlyInteractive = false);
  void mouseMove (int _x, int _y);
  void makeDirty ();
  void setSelNode (GameEntNode * newNode);
  void worldToScreenBase (FIVector4 * sc, FIVector4 * wc, bool doDiv = true);
  void worldToScreen (FIVector4 * sc, FIVector4 * wc, bool centerIsOrigin = false);
  void mouseClick (int button, int state, int _x, int _y);
  void resetActiveNode ();
  void updateNearestEntNode (bool setActive, FIVector4 * mousePosWS);
  void findNearestEntNode (GameEntNode * curNode, FIVector4 * mousePosSS);
  void processB64 (charArr * sourceBuffer, charArr * saveBuffer);
  bool processJSONFromString (string * sourceBuffer, JSONValue * * destObj);
  bool processJSON (charArr * sourceBuffer, charArr * saveBuffer, JSONValue * * destObj);
  bool loadJSON (string path, JSONValue * * destObj);
  void setGUIText (string key, string stringValue, float floatValue = 0.0f, bool applyVal = false, bool applyString = true);
  float getGUIValue (string key);
  void setGUIValue (string key, float floatValue, bool dispatchEvent = false, bool preventRefresh = false);
  void loadGUIValues (bool applyValues = false);
  void saveGUIValues ();
  void updateGUI ();
  void loadGUI ();
  void loadAllData ();
  void saveAllData ();
  bool loadFile (string fnString, charArr * dest);
  bool saveFileString (string fileName, string * source);
  bool saveFile (char * fileName, charArr * source);
  void updateAmbientSounds ();
  void frameUpdate ();
  void display ();
  void reshape (int w, int h);
  void idleFunc ();
};
#undef LZZ_INLINE
#endif
// f00305_shader.e
//

#ifndef LZZ_f00305_shader_e
#define LZZ_f00305_shader_e
#define LZZ_INLINE inline
class Shader
{
private:
  unsigned int shader_id;
  unsigned int shader_vp;
  unsigned int shader_fp;
public:
  int curUBIndex;
  map <string, float> paramMap;
  map <string, float> paramMapTemp;
  vector <string> paramVec;
  vector <UniformBuffer> uniVec;
  Singleton * singleton;
  Shader (Singleton * _singleton);
  static char * textFileRead (char const * fileName);
  static void validateShader (GLuint shader, char const * file = 0);
  static int validateProgram (GLuint program);
  int countOc (string * src, string testStr);
  void init (string _shaderFile, bool doBake);
  ~ Shader ();
  unsigned int id ();
  void bind ();
  void updateUniformBlock (int ubIndex, int ubDataSize);
  void invalidateUniformBlock (int ubIndex);
  void beginUniformBlock (int ubIndex);
  bool wasUpdatedUniformBlock (int ubIndex);
  void unbind ();
  void setTexture (GLchar const * name, int texUnit, int texId);
  void setVec (GLchar const * name, GLfloat const * vecData, int vecSize);
  void setVecString (string name, GLfloat const * vecData, int vecSize);
  void setShaderArrayfVec4 (string paramName, float * x, int count);
  void setShaderArrayfVec3 (string paramName, float * x, int count);
  void setShaderArray (string paramName, float * x, int count);
  void setShaderFloat (string paramName, float x);
  void setShaderVec2 (string paramName, float x, float y);
  void setShaderVec3 (string paramName, float x, float y, float z);
  void setShaderVec4 (string paramName, float x, float y, float z, float w);
  void setShaderInt (string paramName, int x);
  void setShaderfVec2 (string paramName, FIVector4 * f);
  void setShaderfVec3 (string paramName, FIVector4 * f);
  void setShaderfVec4 (string paramName, FIVector4 * f);
  void setShaderFloatUB (string paramName, float x);
  void setShaderfVec4UB (string paramName, FIVector4 * f);
};
#undef LZZ_INLINE
#endif
// f00310_pooledresource.e
//

#ifndef LZZ_f00310_pooledresource_e
#define LZZ_f00310_pooledresource_e
#define LZZ_INLINE inline
class PooledResource
{
private:
  FBOSet * (fboSet) [MAX_LAYERS];
  uint * (cpuSet) [MAX_LAYERS];
public:
  intPair usedById;
  bool isCPU;
  Singleton * singleton;
  PooledResource ();
  FBOSet * getFBOS (int fboNum);
  void init (Singleton * _singleton, bool _isCPU, int _sizeX, int _sizeY);
};
#undef LZZ_INLINE
#endif
// f00315_poolmanager.e
//

#ifndef LZZ_f00315_poolmanager_e
#define LZZ_f00315_poolmanager_e
#define LZZ_INLINE inline
class PoolManager
{
public:
  int poolItemsCreated;
  bool isCPU;
  list <int> holderPoolIds;
  vector <intPair> orderedIds;
  vector <PooledResource *> holderPoolItems;
  Singleton * singleton;
  GameWorld * gw;
  bool isEntity;
  int sizeX;
  int sizeY;
  PoolManager ();
  void init (Singleton * _singleton, bool _isEntity, bool _isCPU, int _sizeX, int _sizeY);
  float getMaxMem ();
  float getTotMemUsed ();
  void reorderIds ();
  int findFurthestHolderId ();
  int requestPoolId (int blockId, int holderId);
};
#undef LZZ_INLINE
#endif
// f00316_poolpagemanager.e
//

#ifndef LZZ_f00316_poolpagemanager_e
#define LZZ_f00316_poolpagemanager_e
#define LZZ_INLINE inline
class PoolPageManager
{
public:
  PoolPageManager ();
};
#undef LZZ_INLINE
#endif
// f00320_fontwrapper.e
//

#ifndef LZZ_f00320_fontwrapper_e
#define LZZ_f00320_fontwrapper_e
#define LZZ_INLINE inline
class FontWrapper
{
public:
  Singleton * singleton;
  charArr lastJSONBuffer;
  JSONValue * jsRoot;
  Image * fontImage;
  float ascender;
  float descender;
  float fontHeight;
  float maxWidth;
  float fontScale;
  float additionalOffset;
  bool isIcons;
  CharStruct (charVals) [4096];
  FontWrapper ();
  void init (Singleton * _singleton, string fontName, bool _isIcons, float _fontScale, float _additionalOffset = 0.0f);
};
#undef LZZ_INLINE
#endif
// f00325_uicomponent.e
//

#ifndef LZZ_f00325_uicomponent_e
#define LZZ_f00325_uicomponent_e
#define LZZ_INLINE inline
class UIComponent
{
private:
  UIComponent * parent;
  float value;
public:
  Singleton * singleton;
  Singleton::UIQuad thisUIQuad;
  Singleton::UICont thisUICont;
  string uid;
  string ss;
  string text;
  string label;
  int parentId;
  int nodeId;
  int index;
  int fillDir;
  int layer;
  int hoverType;
  int guiClass;
  Singleton::UIQuad * curQuad;
  bool foundParent;
  bool visible;
  iVector2 align;
  JSONValue * jvNodeNoTemplate;
  fVector2 scrollMaskY;
  fVector2 dragStart;
  fVector2 lastDrag;
  fVector2 dragOffset;
  fVector2 totOffset;
  fVector2 targScrollOffset;
  fVector2 scrollOffset;
  fVector2 floatOffset;
  fVector2 originPos;
  fVector2 resultDimInPixels;
  fVector2 textDimInPixels;
  fVector2 minDimInPixels;
  fVector2 maxDimInPixels;
  fVector2 fillRatioDim;
  FontWrapper * curFont;
  FontWrapper * curFontIcons;
  bool dragging;
  bool contOnStack;
  bool overChild;
  bool overSelf;
  bool singleLine;
  bool hasBackground;
  bool mouseOver;
  bool mouseDown;
  bool wasHit;
  bool isDirty;
  bool isFloating;
  float divisions;
  float paddingInPixels;
  float borderInPixels;
  float marginInPixels;
  float spaceForCharsInPixels;
  iVector2 spacing;
  std::vector <string> lineVec;
  std::vector < std::vector<string> > wordVec;
  std::vector <float> linePitchVec;
  fBoundingBox hitBounds;
  StyleSheetResult resSS;
  std::vector <UIComponent> children;
  std::vector <UIComponent> floatingChildren;
  UIComponent * curComp;
  UIComponent ();
  void init (Singleton * _singleton, int _parentId, int _nodeId, int _index, JSONValue * _jvNodeNoTemplate, string _label, string _uid, string _ss, int _guiClass = E_GT_HOLDER, float _divisions = 0.0f, bool _hasBackground = true, bool _singleLine = true, float _fillRatioX = 0.0f, float _fillRatioY = 0.0f, int _fillDir = E_FILL_HORIZONTAL, int _alignX = E_ALIGNH_LEFT, int _alignY = E_ALIGNV_TOP, float _value = 0.0f, int _layer = 0, int _hoverType = E_HT_NORMAL, float _maxDimInPixelsX = 0.0f, float _maxDimInPixelsY = 0.0f, bool _isFloating = false);
  float getDimYClamped (float val);
  float getResultDimYClamped ();
  float getMinDimYClamped ();
  void setValue (float _value, bool doEventDispatch = false, bool preventRefresh = false);
  float getValue ();
  UIComponent * getParent ();
  UIComponent * findNodeByString (string _uid);
  UIComponent * findNodeById (int id);
  float getMinWidth ();
  float getMinHeight ();
  UIComponent * addChild (int _parentId, int _nodeId, string * stringVals, float * floatVals, bool _isFloating, JSONValue * _jvNodeNoTemplate);
  void setOrigPos ();
  void applyHeight ();
  void applyWidth ();
  void gatherDirty (vector <UIComponent*> * dirtyVec);
  void clearDirty ();
  void layout ();
  void updateOffset ();
  void updateValue (float x, float y);
  void runReport ();
  void clearOver ();
  bool findMaxLayer (float x, float y, float xTransformed, float yTransformed);
  void testOver (float x, float y);
  bool testHit (int button, int state, float x, float y);
  UIComponent * getHighestCont (UIComponent * curNode, int genCount);
  void setText (string _text);
  void updateVecs ();
  void renderAll ();
  void updateSS ();
  float getLineOffset (int lineCount);
  float lengthOfWord (int i, int j, bool isIcon);
  int maxCharsForWord (int i, int j);
  void renderText (bool getDimensions);
};
#undef LZZ_INLINE
#endif
// f00330_gamegui.e
//

#ifndef LZZ_f00330_gamegui_e
#define LZZ_f00330_gamegui_e
#define LZZ_INLINE inline
class GameGUI
{
private:
public:
  Singleton * singleton;
  UIComponent * baseComp;
  JSONValue * jvRoot;
  JSONValue * jvTemplates;
  JSONValue * jvSounds;
  bool isReady;
  bool isLoaded;
  fVector2 mouseTrans;
  int nodeCount;
  vector <UIComponent*> dirtyVec;
  string (tempStrings) [10];
  GameGUI ();
  void init (Singleton * _singleton);
  void getJVNodeByString (JSONValue * rootNode, JSONValue * * resultNode, string stringToSplit);
  UIComponent * findNodeById (int _id);
  bool compChildStr (string childStr);
  void addChildFromJSON (JSONValue * jv, UIComponent * curParent, bool isFloating = false);
  void guiFromJSON (JSONValue * jv);
  void doRefresh ();
  void testOver (int x, int y);
  bool testHit (int button, int state, int x, int y);
  UIComponent * findNodeByString (string _uid);
  void renderCharAt (UIComponent * uiComp, CharStruct * cs, FontWrapper * activeFont, float px, float py, float shadowOffset);
  void renderQuad (UIComponent * uiComp, fBoundingBox fbb, float shadowOffset);
  void runReport ();
  void renderGUI (float newZoom, int activeFBO);
};
LZZ_INLINE bool GameGUI::compChildStr (string childStr)
                                                  {
		return tempStrings[E_GDS_CHILD_TYPE].compare(childStr) == 0;
	}
#undef LZZ_INLINE
#endif
// f00338_gameentnode.e
//

#ifndef LZZ_f00338_gameentnode_e
#define LZZ_f00338_gameentnode_e
#define LZZ_INLINE inline
class GameEntNode
{
private:
public:
  float rotThe;
  float rotPhi;
  float rotRho;
  float material;
  float boneLengthHalf;
  static float const multiplier;
  FIVector4 * readTBN;
  FIVector4 * writeTBN;
  FIVector4 (tbnBase) [3];
  FIVector4 (tbnBaseTrans) [3];
  FIVector4 (tbnRotA) [3];
  FIVector4 (tbnRotB) [3];
  FIVector4 (tbnRotC) [3];
  FIVector4 (tbnTrans) [3];
  FIVector4 tbnRadInMeters0;
  FIVector4 tbnRadInMeters1;
  FIVector4 tbnRadScale0;
  FIVector4 tbnRadScale1;
  float boneLengthScale;
  FIVector4 (orgTrans) [3];
  int nodeName;
  GameEntNode * parent;
  std::vector <GameEntNode*> children;
  GameEntNode (GameEntNode * _parent, int _nodeName, float _boneLength, float _tanLengthInMeters, float _bitLengthInMeters, float _norLengthInMeters, float _tanX, float _tanY, float _tanZ, float _bitX, float _bitY, float _bitZ, float _norX, float _norY, float _norZ);
  GameEntNode * addChild (int _nodeName, float _boneLength, float _tanLengthInMeters, float _bitLengthInMeters, float _norLengthInMeters, float _tanX, float _tanY, float _tanZ, float _bitX, float _bitY, float _bitZ, float _norX, float _norY, float _norZ);
  GameEntNode * getNode (int _nodeName);
  void doTransform (Singleton * singleton);
};
#undef LZZ_INLINE
#endif
// f00339_gameent.e
//

#ifndef LZZ_f00339_gameent_e
#define LZZ_f00339_gameent_e
#define LZZ_INLINE inline
class GameEnt
{
public:
  Singleton * singleton;
  GamePageHolder * gph;
  GameEntNode * baseNode;
  FIVector4 basePosition;
  float defVecLength;
  float gv (float * vals);
  GameEnt ();
  void init (Singleton * _singleton);
  void initHuman ();
};
#undef LZZ_INLINE
#endif
// f00340_gameplantnode.e
//

#ifndef LZZ_f00340_gameplantnode_e
#define LZZ_f00340_gameplantnode_e
#define LZZ_INLINE inline
class GamePlantNode
{
public:
  FIVector4 begPoint;
  FIVector4 endPoint;
  FIVector4 tangent;
  FIVector4 baseShoot;
  float shootLength;
  float begThickness;
  float endThickness;
  float midThickness;
  float sphereRad;
  FIVector4 startEndWidth;
  FIVector4 upVec;
  GamePlantNode * parent;
  GamePlantNode * children;
  int maxChildren;
  int numChildren;
  GamePlantNode ();
  void updateTangent (float angleInRadians);
  void init (GamePlantNode * _parent, int _maxChildren, int _numChildren);
};
#undef LZZ_INLINE
#endif
// f00341_gameplant.e
//

#ifndef LZZ_f00341_gameplant_e
#define LZZ_f00341_gameplant_e
#define LZZ_INLINE inline
class GamePlant
{
public:
  Singleton * singleton;
  FIVector4 origin;
  FIVector4 tempv0;
  FIVector4 tempv1;
  FIVector4 tempv2;
  FIVector4 tempv3;
  FIVector4 rootVec;
  FIVector4 trunkVec;
  GamePlantNode * trunkNode;
  GamePlantNode * rootsNode;
  PlantRules * rootRules;
  PlantRules * trunkRules;
  static PlantRules (allPlantRules) [E_PT_LENGTH];
  static void initAllPlants (Singleton * _singleton);
  float gv (float * vals);
  GamePlant ();
  void init (Singleton * _singleton, PlantRules * _rootRules, PlantRules * _trunkRules, FIVector4 * _origin);
  void initBase (PlantRules * rules, GamePlantNode * curNode, FIVector4 * baseVec);
  void applyRules (PlantRules * rules, GamePlantNode * curParent, int curGen, int maxGen, float totLength, float maxLength);
};
#undef LZZ_INLINE
#endif
// f00350_gamepage.e
//

#ifndef LZZ_f00350_gamepage_e
#define LZZ_f00350_gamepage_e
#define LZZ_INLINE inline
class GamePage
{
private:
  uint * volData;
  uint * volDataLinear;
public:
  Singleton * singleton;
  int thisPageId;
  int terRes;
  int bufferedPageSizeInUnits;
  FIVector4 offsetInUnits;
  FIVector4 offsetInPages;
  FIVector4 offsetInPagesLocal;
  float pageDepth;
  int iVolumeSize;
  bool hasSolids;
  bool hasTrans;
  bool hasGeom;
  bool hasLines;
  bool hasTerrain;
  bool hasWater;
  bool hasWindow;
  bool hasTree;
  bool isDirty;
  int voroCount;
  bool volDataModified;
  bool isRendering;
  bool isEntity;
  int paramsPerEntry;
  int numEntries;
  int totParams;
  int maxEntries;
  bool threadRunning;
  float unitSizeInPixels;
  GameWorld * gw;
  FIVector4 worldMinVisInPixels;
  FIVector4 worldMaxVisInPixels;
  FIVector4 worldMinBufInPixels;
  FIVector4 worldMaxBufInPixels;
  FIVector4 centerPosition;
  FIVector4 scaleAndOffset;
  FIVector4 worldUnitMin;
  FIVector4 worldUnitMax;
  FIVector4 voroSize;
  FIVector4 curPos;
  FIVector4 randNum;
  FIVector4 testNum;
  FIVector4 newPos;
  FIVector4 tempVec1;
  FIVector4 tempVec2;
  GamePageHolder * parentGPH;
  GameBlock * parentBlock;
  GamePage ();
  void init (Singleton * _singleton, GamePageHolder * _parentGPH, int _thisPageId, int offsetX, int offsetY, int offsetZ, int oxLoc, int oyLoc, int ozLoc, bool _isEntity = false);
  uint * getVolData ();
  uint * getVolDataLinear ();
  void copyToTexture (bool isForEmptyVD);
  void setFalse ();
  void addEntityGeom (bool justTesting);
  void addGeom (bool justTesting);
  void getVoroPoints ();
  void generateVolume (bool dd = false);
  void getCoords ();
  ~ GamePage ();
};
#undef LZZ_INLINE
#endif
// f00351_gamepageholder.e
//

#ifndef LZZ_f00351_gamepageholder_e
#define LZZ_f00351_gamepageholder_e
#define LZZ_INLINE inline
class GamePageHolder
{
public:
  int iPageDataVolume;
  int holderSizeInPages;
  int usingPoolId;
  int blockId;
  int holderId;
  bool hasTrans;
  bool hasSolids;
  bool childrenDirty;
  std::vector <GameGeom *> entityGeom;
  int entityGeomCounter;
  FIVector4 offsetInHolders;
  FIVector4 gphMinInPixels;
  FIVector4 gphMaxInPixels;
  FIVector4 gphCenInPixels;
  FIVector4 offsetInBlocks;
  FIVector4 origOffset;
  FIVector4 tempVec;
  FIVector4 tempVec2;
  PooledResource * gpuRes;
  Singleton * singleton;
  std::vector <intPair> containsGeomIds;
  GamePage * * pageData;
  bool readyForClear;
  bool isEntity;
  float holderSizeInPixels;
  float halfHolderSizeInPixels;
  GamePageHolder ();
  void init (Singleton * _singleton, int _blockId, int _holderId, int trueX, int trueY, int trueZ, bool _isEntity = false);
  GamePage * getPageAtCoordsLocal (int x, int y, int z, bool createOnNull = false);
  void refreshGeom ();
  void clearSet ();
  int passiveRefresh ();
  void refreshChildren (bool refreshImmediate, bool clearEverything = false, bool refreshUnderground = false);
  void addNewGeom (int _curBT, int _curAlign, float _baseOffset, FIVector4 * _p1, FIVector4 * _p2, FIVector4 * _rad, FIVector4 * _cornerRad, FIVector4 * _visInsetFromMin, FIVector4 * _visInsetFromMax, FIVector4 * _powerVals, FIVector4 * _powerVals2, FIVector4 * _thickVals, FIVector4 * _matParams, FIVector4 * _centerPoint, FIVector4 * _anchorPoint, int _minRot, int _maxRot);
  void addNewLinesGeom (GameEntNode * curNode, float scale);
  void fetchEntityGeom ();
  void fetchGeom ();
  void unbindGPUResources ();
};
#undef LZZ_INLINE
#endif
// f00352_gameblock.e
//

#ifndef LZZ_f00352_gameblock_e
#define LZZ_f00352_gameblock_e
#define LZZ_INLINE inline
class GameBlock
{
public:
  Singleton * singleton;
  int blockId;
  int blockSizeInHolders;
  int blockSizeInLots;
  int localGeomCounter;
  int lightCounter;
  int terDataBufAmount;
  bool forceUpdate;
  float (trilin) [8];
  int terDataVisPitchXY;
  float fTerDataVisPitchXY;
  int terDataBufPitchXY;
  int terDataBufPitchScaledXY;
  int terDataVisPitchZ;
  float fTerDataVisPitchZ;
  int terDataBufPitchZ;
  int terDataBufPitchScaledZ;
  int terDataTexScale;
  int terDataVisSize;
  int terDataBufSize;
  int blockSizeInPixels;
  int iHolderSize;
  int maxFloors;
  float fBlockSizeInPixels;
  int (dirModX) [6];
  int (dirModY) [6];
  int (dirModZ) [6];
  int (opDir) [6];
  float pixelsPerMeter;
  float floorHeightInMeters;
  float floorHeight;
  float roofHeight;
  bool (isBuilding) [E_CT_LENGTH];
  bool (isRoad) [E_CT_LENGTH];
  bool (isRoom) [E_CT_LENGTH];
  bool (isBase) [E_CT_LENGTH];
  bool (isTraversable) [E_CT_LENGTH];
  int (ctClasses) [E_CT_LENGTH];
  int (layerHash) [E_CT_LENGTH];
  FIVector4 anchorPoint;
  FIVector4 moveMinInPixels;
  FIVector4 moveMaxInPixels;
  FIVector4 p1;
  FIVector4 p2;
  FIVector4 newP1;
  FIVector4 newP2;
  FIVector4 rad;
  FIVector4 visInsetFromMin;
  FIVector4 visInsetFromMax;
  FIVector4 cornerRad;
  FIVector4 thickVals;
  FIVector4 powerVals;
  FIVector4 powerVals2;
  FIVector4 matParams;
  FIVector4 centerPoint;
  FIVector4 lightVec;
  FIVector4 offsetInBlocks;
  FIVector4 offsetInBlocksWrapped;
  FIVector4 origin;
  FIVector4 blockMinBufInPixels;
  FIVector4 blockMaxBufInPixels;
  FIVector4 tempVec;
  FIVector4 tempVec2;
  FIVector4 tempVec3;
  FIVector4 tempVec4;
  FIVector4 tempVecB;
  FIVector4 tempVecB2;
  FIVector4 tempVecB3;
  std::vector <GameGeom *> gameGeom;
  std::vector <GameLight *> gameLights;
  GameWorld * gw;
  GamePageHolder * * holderData;
  BuildingNode * buildingData;
  MapNode * mapData;
  uint * terData;
  BuildingCon * curCon;
  GameBlock ();
  void init (Singleton * _singleton, int _blockId, int _x, int _y, int _xw, int _yw);
  int getNodeIndexClamped (int _x, int _y, int _z);
  int getNodeIndex (int x, int y, int z, int bufAmount);
  int touchesPlanarBN (int x, int y, int z, int buildingType, int bufAmount);
  int touchesPlanarClass (int x, int y, int z, int classType, int bufAmount);
  bool isLCorner (int x, int y, int z, int classType, bool includeSingle);
  void applyWingValues (int _x1, int _y1, int _z1, int _x2, int _y2, int _z2, int cnum, bool isWingBeg, bool isWingEnd, float multiplier);
  void addPlantNodes (GamePlantNode * curPlantNode, FIVector4 * orig, float scale);
  void addNewGeom (int _curBT, int _curAlign, float _baseOffset, FIVector4 * _p1, FIVector4 * _p2, FIVector4 * _rad, FIVector4 * _cornerRad, FIVector4 * _visInsetFromMin, FIVector4 * _visInsetFromMax, FIVector4 * _powerVals, FIVector4 * _powerVals2, FIVector4 * _thickVals, FIVector4 * _matParams, FIVector4 * _centerPoint, FIVector4 * _anchorPoint, int _minRot, int _maxRot);
  void connectNodes (int _x1, int _y1, int _z1, int _x2, int _y2, int _z2, int ct, int id = -1, int _heightDelta = 0, int _direction = 0, float _wallRadInMeters = -1.0f, unsigned int _nodeFlags = 0);
  int getMapNodeIndex (int x, int y, int bufAmount);
  int touchesMap (int x, int y, int buildingType, int bufAmount);
  int touchesWithinRadMap (int x, int y, int buildingType, int rad, int bufAmount);
  int touches2Map (int x, int y, int buildingType, int bufAmount);
  void connectMapNodes (int _x1, int _y1, int _x2, int _y2, int buildingType, int id, int bufAmount);
  int getAdjustedHeightInHolders (int xInHolders, int yInHolders);
  float fIsNearTerrain (FIVector4 * worldMinVisInPixels);
  void refreshHoldersInArea (FIVector4 * worldPos);
  void modifyTerrain (FIVector4 * worldPos, bool doSub);
  int isNearTerrain (FIVector4 * worldPosInPix);
  int findNearestNode (FIVector4 * worldPositionInPixelsIn, FIVector4 * posInNodesOut, FIVector4 * posInPixelsOut);
  void nodeIndexToWorldSpaceInPixels (int ind, FIVector4 * posInPixelsOut);
  bool hasTerrainBelow (int i, int j, int k, int conDir, bool bothEnds);
  bool hasRoomBelow (int i, int j, int k, int conDir);
  bool isSupportedBelow (int i, int j, int k, int conDir, bool bothEnds);
  bool touchesRoomOnLevel (int i, int j, int k);
  bool touchesBaseOnLevel (int i, int j, int k, int layer);
  bool buildingAbove (int x, int y, int z);
  int copyTerToTexture ();
  void makeMazeUG ();
};
#undef LZZ_INLINE
#endif
// f00380_gameworld.e
//

#ifndef LZZ_f00380_gameworld_e
#define LZZ_f00380_gameworld_e
#define LZZ_INLINE inline
class GameWorld
{
public:
  int numProvinces;
  int seaLevel;
  int seaSlack;
  int pageCount;
  int mapSwapFlag;
  int visPageSizeInUnits;
  int blockSizeInHolders;
  int iBlockSize;
  int renderMethod;
  int iBufferSize;
  int maxThreads;
  int availThreads;
  int visPageSizeInPixels;
  int holderSizeInPages;
  int lightCount;
  int MIN_MIP;
  int MAX_MIP;
  int AVG_MIP;
  int blockMip;
  int hmChannel;
  int idChannel;
  int densityChannel;
  int blockChannel;
  int curLoadRadius;
  int stChannel;
  int btChannel;
  int pathChannel;
  int houseChannel;
  int * curDiagram;
  int * provinceGrid;
  int * provinceX;
  int * provinceY;
  bool procResultAccum;
  bool doDrawFBO;
  bool lastProcResult;
  bool mapLockOn;
  bool foundPath;
  float mapStep;
  float mapTrans;
  float newZoom;
  int (dirFlags) [4];
  int (dirFlagsOp) [4];
  int (dirFlagsO) [4];
  int (dirFlagsOpO) [4];
  int (dirModX) [6];
  int (dirModY) [6];
  int (dirModZ) [6];
  int (opDir) [4];
  GameLight * (activeLights) [MAX_EVAL_LIGHTS];
  int dirFlagClear;
  int visFlag;
  int visFlagO;
  int activeFBO;
  bool noiseGenerated;
  std::vector <coordAndIndex> roadCoords;
  std::vector <GamePageHolder *> holdersToRefresh;
  vector <int> ocThreads;
  FIVector4 lScreenCoords;
  FIVector4 cScreenCoords;
  FIVector4 worldSizeInPages;
  FIVector4 worldSizeInHolders;
  FIVector4 worldSizeInBlocks;
  FIVector4 geomMin;
  FIVector4 geomMax;
  FIVector4 camPagePos;
  FIVector4 camHolderPos;
  FIVector4 cutHolderPos;
  FIVector4 camBlockPos;
  FIVector4 camTerPos;
  FIVector4 iPixelWorldCoords;
  FIVector4 pagePos;
  FIVector4 unitPos;
  FIVector4 lastUnitPos;
  FIVector4 lastPagePos;
  FIVector4 tempVec1;
  FIVector4 tempVec2;
  FIVector4 tempVec3;
  FIVector4 (blockPos) [2];
  FIVector4 (nodePos) [2];
  FIVector4 (nodePosInPixels) [2];
  PathNode (blockAndIndexPath) [2];
  PathNode (blockAndIndexSplitPath) [2];
  FIVector4 (lineSeg) [2];
  PathHolder * finalPath;
  int (nodeInd) [2];
  GameBlock * (blockRef) [2];
  FIVector4 minLRInPixels;
  FIVector4 maxLRInPixels;
  FIVector4 minLRInHolders;
  FIVector4 maxLRInHolders;
  FIVector4 minv;
  FIVector4 maxv;
  FIVector4 tempVec;
  FIVector4 unitPosMin;
  FIVector4 unitPosMax;
  FIVector4 unitPosCenter;
  FIVector4 startBounds;
  FIVector4 endBounds;
  FIVector4 * fogPos;
  FIVector4 * cutPos;
  FIVector4 * lightPos;
  FIVector4 * globLightPos;
  FIVector4 lightPosBase;
  FIVector4 * cameraPos;
  FIVector4 * curBoxPos;
  FIVector4 tv0;
  FIVector4 tv1;
  FIVector4 tv2;
  FIVector4 tv3;
  FIVector4 tv4;
  FIVector4 tv5;
  Singleton * singleton;
  GameBlock * * blockData;
  FBOWrapper * curFBO;
  FBOWrapper * curFBO2;
  GameWorld ();
  void init (Singleton * _singleton);
  GameBlock * getBlockAtCoords (int xInBlocks, int yInBlocks, bool createOnNull = false);
  GamePageHolder * getHolderAtCoords (int x, int y, int z, bool createOnNull = false);
  uint getTerDataAtCoords (int x, int y, int z);
  GamePageHolder * getHolderAtId (intPair id);
  GameBlock * getBlockAtId (int id);
  GamePage * getPageAtIndex (int ind);
  GamePage * getPageAtCoords (int x, int y, int z, bool createOnNull = false);
  bool checkBounds (int k, int km);
  void update ();
  bool procPages ();
  bool addHolderToRefresh (GamePageHolder * toAdd);
  int getHoldersInGeom (GameGeom * gg);
  void refreshHoldersInList (bool doImmediate, bool clearEverything);
  void actionOnHolders (int action, bool instantRefresh = false, bool clearEverything = false);
  void drawHolder (GamePageHolder * gp, int curLayer, float xoff, float yoff, float zoff);
  void combineHolders ();
  void combineBuffers ();
  void transformEnt (GameEnt * curEnt);
  void drawEnt (GameEnt * curEnt, bool drawAll);
  void drawNodeEnt (GameEntNode * curNode, FIVector4 * basePosition, float scale, int drawMode, bool drawAll);
  void clearVisitedPaths (PathHolder * pathHolder);
  void clearPathList (PathHolder * pathHolder);
  float getIdealPathLength (PathNode * blockAndIndex);
  int findAIPathRBT (PathHolder * pathHolder, PathNode * blockAndIndex, float _pathSlack);
  void drawPathLine (PathHolder * curPath, int r, int g, int b, float lw, float zoff);
  void drawAIPath (PathHolder * pathHolder, PathHolder * splitPathHolder);
  void renderGeom ();
  void modifyUnit (FIVector4 * fPixelWorldCoordsBase, E_BRUSH brushAction);
  void renderWorldSpaceGPU ();
  void getWorldSpaceBuffer (int bufNum = 0);
  float weighPath (float x1, float y1, float x2, float y2, float rad, bool doSet, bool isOcean);
  float findBestPath (float x1, float y1, float x2, float y2, int generation, int roadIndex, bool doSet, bool isOcean);
  void initMap ();
  void drawMap ();
  void doBlur (string fboName);
  void updateLights ();
  void postProcess ();
  ~ GameWorld ();
};
#undef LZZ_INLINE
#endif
 
// f00293_gamesound.h
//

#include "f00293_gamesound.e"
#define LZZ_INLINE inline
GameSound::GameSound ()
                            {
			
		}
void GameSound::init (string path)
                                       {
			if (!buffer.loadFromFile(path)) {
				cout << "error loading sound";
				return;
			}
			
			sound.setBuffer(buffer);
			
		}
void GameSound::setPitch (float val)
                                         {
			sound.setPitch(val);
		}
void GameSound::setPositionAndMinDis (float x, float y, float z, float w)
                  {
			sound.setMinDistance(w);
			sound.setPosition(x,y,z);
		}
void GameSound::setLoop (bool val)
                                       {
			sound.setLoop(val);
		}
void GameSound::stop ()
                            {
			
		}
void GameSound::play (float volume)
                {
			int intVol = volume*100.0f;
			
			sound.setVolume(intVol);
			sound.play();
			
		}
#undef LZZ_INLINE
 
// f00294_gamemusic.h
//

#include "f00294_gamemusic.e"
#define LZZ_INLINE inline
GameMusic::GameMusic ()
                            {
			
		}
void GameMusic::init (string path)
                                       {
			if ( !sound.openFromFile(path) ) {
				cout << "error loading music";
				return;
			}
			
		}
void GameMusic::setLoop (bool val)
                                       {
			sound.setLoop(val);
		}
void GameMusic::stop ()
                            {
			sound.stop();
		}
void GameMusic::setVolume (float _volume)
                                                   {
			volume = _volume;
			int intVol = _volume*100.0f;
			sound.setVolume(intVol);
		}
void GameMusic::play (float _volume)
                {
			setVolume(_volume);
			sound.play();
		}
#undef LZZ_INLINE
 
// f00295_gamegeom.h
//

#include "f00295_gamegeom.e"
#define LZZ_INLINE inline
GameGeom::GameGeom ()
                   {
		light = NULL;
	}
void GameGeom::init (int _id)
                           {
		id = _id;
	}
FIVector4 * GameGeom::getBoundsMinInPixels ()
                                          {
		return &boundsMinInPixels;
	}
FIVector4 * GameGeom::getBoundsMaxInPixels ()
                                          {
		return &boundsMaxInPixels;
	}
FIVector4 * GameGeom::getVisMinInPixels ()
                                       {
		return &visMinInPixels;
	}
FIVector4 * GameGeom::getVisMaxInPixels ()
                                       {
		return &visMaxInPixels;
	}
FIVector4 * GameGeom::getBoundsMinInPixelsT ()
                                           {
		return &geomParams[E_GP_BOUNDSMININPIXELST];
	}
FIVector4 * GameGeom::getBoundsMaxInPixelsT ()
                                           {
		return &geomParams[E_GP_BOUNDSMAXINPIXELST];
	}
FIVector4 * GameGeom::getVisMinInPixelsT ()
                                        {
		// TODO: make this more efficient and use pixelsPerMeter

		// tempVec1.copyFrom(&geomParams[E_GP_VISMININPIXELST]);
		// tempVec1.addXYZ(pixelsPerMeter);
		// return &tempVec1;

		return &geomParams[E_GP_VISMININPIXELST];
	}
FIVector4 * GameGeom::getVisMaxInPixelsT ()
                                        {
		return &geomParams[E_GP_VISMAXINPIXELST];
	}
int GameGeom::getClampedRot ()
                            {
		int tempRot = curRot;
		while (tempRot < 0) {
			tempRot += 4;
		}
		while (tempRot > 3) {
			tempRot -= 4;
		}

		return tempRot;
	}
void GameGeom::rotate (int mod, bool ignoreConstraints)
                                                     {

		if (hasAnchor) {
			curRot += mod;


			if (ignoreConstraints) {
				if (curRot > 3) {
					curRot = 0;
				}
				if (curRot < 0) {
					curRot = 3;
				}
			}
			else {
				if (curRot > maxRot) {
					curRot = maxRot - 1;
					rotDir *= -1;
				}
				if (curRot < minRot) {
					curRot = minRot + 1;
					rotDir *= -1;

				}

			}


		}
		else {
			cout << "Attemped to rotate without anchor.\n";
		}


	}
void GameGeom::initBounds (int _buildingType, int _id, int _globalId, int alignBottomMiddleTop, float _zOffset, FIVector4 * p1, FIVector4 * p2, FIVector4 * rad, FIVector4 * _cornerDisInPixels, FIVector4 * _visInsetFromMin, FIVector4 * _visInsetFromMax, FIVector4 * _powerVals, FIVector4 * _powerVals2, FIVector4 * _thickVals, FIVector4 * _matParams, FIVector4 * _centerPoint, FIVector4 * _anchorPoint, int _minRot, int _maxRot)
          {
		buildingType = _buildingType;
		id = _id;
		globalId = _globalId;
		float temp;
		float zOffset = _zOffset;
		
		isToggled = false;

		curRot = 0;
		rotDir = 1;
		visible = true;
		hasAnchor = false;

		anchorPointInPixels.setFXYZ(0.0f, 0.0f, 0.0f);


		boundsMinInPixels.setFXYZRef(p1);
		boundsMaxInPixels.setFXYZRef(p2);

		FIVector4::normalizeBounds(&boundsMinInPixels, &boundsMaxInPixels);




		boundsMinInPixels.addXYZRef(rad, -1.0f);
		boundsMaxInPixels.addXYZRef(rad, 1.0f);

		switch (alignBottomMiddleTop) {

		case E_ALIGN_BOTTOM: // bottom _@_
			zOffset += (rad->getFZ() - _visInsetFromMin->getFZ());
			break;
		case E_ALIGN_MIDDLE: // middle -@-
			zOffset += 0.0f;
			break;
			//               ___
		case E_ALIGN_TOP: // top  @
			zOffset += -(rad->getFZ() - _visInsetFromMax->getFZ());
			break;


		}

		boundsMinInPixels.addXYZ(0.0f, 0.0f, zOffset);
		boundsMaxInPixels.addXYZ(0.0f, 0.0f, zOffset);


		visMinInPixels.setFXYZRef(&boundsMinInPixels);
		visMaxInPixels.setFXYZRef(&boundsMaxInPixels);

		visMinInPixels.addXYZRef(_visInsetFromMin, 1.0f);
		visMaxInPixels.addXYZRef(_visInsetFromMax, -1.0f);

		geomParams[E_GP_CORNERDISINPIXELS].setFXYZRef(_cornerDisInPixels);
		geomParams[E_GP_POWERVALS].setFXYZRef(_powerVals);
		geomParams[E_GP_POWERVALS2].setFXYZRef(_powerVals2);
		geomParams[E_GP_THICKVALS].setFXYZRef(_thickVals);
		geomParams[E_GP_MATPARAMS].setFXYZRef(_matParams);
		geomParams[E_GP_CENTERPOINT].setFXYZRef(_centerPoint);

		moveMinInPixels.setFXYZRef(&boundsMinInPixels);
		moveMaxInPixels.setFXYZRef(&boundsMaxInPixels);

		geomParams[E_GP_BOUNDSMININPIXELST].setFXYZRef(&boundsMinInPixels);
		geomParams[E_GP_BOUNDSMAXINPIXELST].setFXYZRef(&boundsMaxInPixels);
		geomParams[E_GP_VISMININPIXELST].setFXYZRef(&visMinInPixels);
		geomParams[E_GP_VISMAXINPIXELST].setFXYZRef(&visMaxInPixels);


		if (_minRot != _maxRot) {
			initAnchorPoint(_anchorPoint, _minRot, _maxRot);
		}

	}
void GameGeom::initLines (int _buildingType, int _id, int _globalId, float scale, FIVector4 * _offset, FIVector4 * _orgVec, FIVector4 * _tanVec, FIVector4 * _bitVec, FIVector4 * _norVec, FIVector4 * _radVec0, FIVector4 * _radVec1, FIVector4 * _radVecScale0, FIVector4 * _radVecScale1, FIVector4 * _matParams)
          {
		buildingType = _buildingType;
		id = _id;
		globalId = _globalId;
		float temp;
		float radMax;
		
		

		curRot = 0;
		rotDir = 1;
		visible = true;
		hasAnchor = false;

		anchorPointInPixels.setFXYZ(0.0f, 0.0f, 0.0f);

		tempVec1.setFXYZRef(_orgVec);
		tempVec2.setFXYZRef(_radVec0);
		tempVec3.setFXYZRef(_radVec1);
		
		tempVec2.multXYZ(_radVecScale0);
		tempVec3.multXYZ(_radVecScale1);
		
		tempVec1.multXYZ(scale);
		tempVec2.multXYZ(scale);
		tempVec3.multXYZ(scale);
		
		tempVec1.addXYZRef(_offset);
		

		boundsMinInPixels.setFXYZRef(&tempVec1);
		boundsMaxInPixels.setFXYZRef(&tempVec1);
		
		boundsMinInPixels.addXYZRef(_tanVec,-1.0);
		boundsMaxInPixels.addXYZRef(_tanVec);
		
		FIVector4::normalizeBounds(&boundsMinInPixels, &boundsMaxInPixels);

		radMax = max(
			max(
				max(tempVec2[0], tempVec2[1]),
				max(tempVec3[0], tempVec3[1])
			),
			max(tempVec2[2], tempVec3[2])
		);
		
		boundsMinInPixels.addXYZ(-radMax);
		boundsMaxInPixels.addXYZ(radMax);

		visMinInPixels.setFXYZRef(&boundsMinInPixels);
		visMaxInPixels.setFXYZRef(&boundsMaxInPixels);

		moveMinInPixels.setFXYZRef(&boundsMinInPixels);
		moveMaxInPixels.setFXYZRef(&boundsMaxInPixels);




		geomParams[E_AP_ORG].setFXYZRef(&tempVec1);
		geomParams[E_AP_TAN].setFXYZRef(_tanVec);
		geomParams[E_AP_BIT].setFXYZRef(_bitVec);
		geomParams[E_AP_NOR].setFXYZRef(_norVec);
		geomParams[E_AP_RAD0].setFXYZRef(&tempVec2);
		geomParams[E_AP_RAD1].setFXYZRef(&tempVec3);
		geomParams[E_AP_MATPARAMS].setFXYZRef(_matParams);
		geomParams[E_AP_VISMININPIXELST].setFXYZRef(&visMinInPixels);
		geomParams[E_AP_VISMAXINPIXELST].setFXYZRef(&visMaxInPixels);


	}
void GameGeom::initTree (int _buildingType, int _id, int _globalId, FIVector4 * p0, FIVector4 * p1, FIVector4 * p2, float radP0, float radP1, float sphereRad, FIVector4 * _matParams)
          {
		buildingType = _buildingType;
		id = _id;
		globalId = _globalId;
		float temp;

		float radMax = max(max(radP0, radP1), sphereRad);

		curRot = 0;
		rotDir = 1;
		visible = true;
		hasAnchor = false;

		anchorPointInPixels.setFXYZ(0.0f, 0.0f, 0.0f);


		boundsMinInPixels.setFXYZRef(p0);
		boundsMaxInPixels.setFXYZRef(p1);

		//boundsMinInPixels.addXYZ(-radMax);
		//boundsMaxInPixels.addXYZ(radMax);

		FIVector4::normalizeBounds(&boundsMinInPixels, &boundsMaxInPixels);

		FIVector4::growBoundary(&boundsMinInPixels, &boundsMaxInPixels, p2, p2);

		boundsMinInPixels.addXYZ(-radMax);
		boundsMaxInPixels.addXYZ(radMax);



		visMinInPixels.setFXYZRef(&boundsMinInPixels);
		visMaxInPixels.setFXYZRef(&boundsMaxInPixels);

		//visMinInPixels.addXYZRef(_visInsetFromMin, 1.0f);
		//visMaxInPixels.addXYZRef(_visInsetFromMax, -1.0f);

		// geomParams[E_GP_CORNERDISINPIXELS].setFXYZRef(_cornerDisInPixels);
		// geomParams[E_GP_POWERVALS].setFXYZRef(_powerVals);
		// geomParams[E_GP_POWERVALS2].setFXYZRef(_powerVals2);


		geomParams[E_TP_P0].setFXYZRef(p0);
		geomParams[E_TP_P1].setFXYZRef(p1);
		geomParams[E_TP_P2].setFXYZRef(p2);
		geomParams[E_TP_THICKVALS].setFXYZ(radP0, radP1, sphereRad);


		geomParams[E_TP_MATPARAMS].setFXYZRef(_matParams);


		moveMinInPixels.setFXYZRef(&boundsMinInPixels);
		moveMaxInPixels.setFXYZRef(&boundsMaxInPixels);

		// geomParams[E_GP_BOUNDSMININPIXELST].setFXYZRef(&boundsMinInPixels);
		// geomParams[E_GP_BOUNDSMAXINPIXELST].setFXYZRef(&boundsMaxInPixels);
		geomParams[E_TP_VISMININPIXELST].setFXYZRef(&visMinInPixels);
		geomParams[E_TP_VISMAXINPIXELST].setFXYZRef(&visMaxInPixels);


	}
void GameGeom::toggleTransform ()
                               {
		isToggled = !isToggled;
		applyTransform(rotDir, false);
	}
void GameGeom::applyTransform (int rotMod, bool ignoreConstraints)
                                                                {

		rotate(rotMod, ignoreConstraints);

		geomParams[E_GP_BOUNDSMININPIXELST].setFXYZRef(&boundsMinInPixels);
		geomParams[E_GP_BOUNDSMAXINPIXELST].setFXYZRef(&boundsMaxInPixels);
		geomParams[E_GP_VISMININPIXELST].setFXYZRef(&visMinInPixels);
		geomParams[E_GP_VISMAXINPIXELST].setFXYZRef(&visMaxInPixels);

		geomParams[E_GP_BOUNDSMININPIXELST].addXYZRef(&anchorPointInPixels, -1.0f);
		geomParams[E_GP_BOUNDSMAXINPIXELST].addXYZRef(&anchorPointInPixels, -1.0f);
		geomParams[E_GP_VISMININPIXELST].addXYZRef(&anchorPointInPixels, -1.0f);
		geomParams[E_GP_VISMAXINPIXELST].addXYZRef(&anchorPointInPixels, -1.0f);

		geomParams[E_GP_BOUNDSMININPIXELST].rotate90(getClampedRot());
		geomParams[E_GP_BOUNDSMAXINPIXELST].rotate90(getClampedRot());
		geomParams[E_GP_VISMININPIXELST].rotate90(getClampedRot());
		geomParams[E_GP_VISMAXINPIXELST].rotate90(getClampedRot());

		geomParams[E_GP_BOUNDSMININPIXELST].addXYZRef(&anchorPointInPixels, 1.0f);
		geomParams[E_GP_BOUNDSMAXINPIXELST].addXYZRef(&anchorPointInPixels, 1.0f);
		geomParams[E_GP_VISMININPIXELST].addXYZRef(&anchorPointInPixels, 1.0f);
		geomParams[E_GP_VISMAXINPIXELST].addXYZRef(&anchorPointInPixels, 1.0f);

		FIVector4::normalizeBounds(&geomParams[E_GP_BOUNDSMININPIXELST], &geomParams[E_GP_BOUNDSMAXINPIXELST]);
		FIVector4::normalizeBounds(&geomParams[E_GP_VISMININPIXELST], &geomParams[E_GP_VISMAXINPIXELST]);

		FIVector4::growBoundary(&moveMinInPixels, &moveMaxInPixels, &geomParams[E_GP_VISMININPIXELST], &geomParams[E_GP_VISMAXINPIXELST]);
	}
void GameGeom::initAnchorPoint (FIVector4 * _anchorPointInPixels, int _minRot, int _maxRot)
                                                                                        {

		int i;


		hasAnchor = true;
		anchorPointInPixels.setFXYZRef(_anchorPointInPixels);
		minRot = _minRot;
		maxRot = _maxRot;

		for (i = 0; i < 4; i++) {
			applyTransform(1, true);
		}

	}
#undef LZZ_INLINE
 
// f00300_singleton.h
//

#include "f00300_singleton.e"
#define LZZ_INLINE inline
bool Singleton::CompareStruct::operator () (string const & first, string const & second)
                                                                       {
	        return first.compare(second) < 0;//first.size() < second.size();
	    }
Singleton::Singleton ()
        {
		
		fboMap.clear();
		shaderMap.clear();
		soundMap.clear();
		styleSheetMap.clear();
		
		
		
		mainGUI = NULL;
		volTris = NULL;
		sliceTris = NULL;
		gw = NULL;
		#ifdef USE_POCO
		myWS = NULL;
		#endif
	}
void Singleton::init (int _defaultWinW, int _defaultWinH, int _scaleFactor)
          {

		pushTrace("Singleton init");
		int i;
		int j;
		
		internalJSON["shaderParams"].jv = NULL;
		
		for (i = 0; i < EML_LENGTH; i++) {
			music[i] = new GameMusic();
			music[i]->init("../data/music/"+musicStrings[i]+".ogg");
			music[i]->setLoop(true);
		}
		
		
		for (i = 0; i < E_CT_LENGTH; i++) {
			isInteractiveGeom[i] = false;
		}
		
		isInteractiveGeom[E_CT_WINDOW] = true;
		isInteractiveGeom[E_CT_DOOR] = true;
		isInteractiveGeom[E_CT_LANTERN] = true;
		
		pathfindingOn = false;
		isMacro = false;
		entOn = false;
		autoScroll = false;
		cavesOn = false;
		bakeParamsOn = true;
		dragging = false;
		mouseMoved = false;
		forceRestart = false;
		changingGenVal = false;
		readyForRestart = false;
		hitGUI = false;
		guiLock = false;
		guiDirty = true;
		
		
		activeNode = NULL;
		selectedNode = NULL;
		lastSelNode = NULL;
		
		curEntId = 0;
		charState = E_CHAR_STATE_RENDERED;
		
		rootObjJS = NULL;
		guiRootJS = NULL;
		highlightedGeom = NULL;
		selectedGeom = NULL;
		rbStack = NULL;
		rbHeightStack = NULL;

		multiLights = false;
		numDynLights = E_OBJ_LENGTH - E_OBJ_LIGHT0;
		updateMultiLights();

		maxLayerOver = -1;

		iNumSteps = 64;
		currentStep = 0;

		srand(time(NULL));

		timeOfDay = 1.0f;
		targetTimeOfDay = 1.0f;
		
		guiSaveLoc = "../cdat/saves/save0/compMap.txt";

		//invItems = loadBMP("../data/invitems.bmp");
		imageHM0 = loadBMP("../data/hm0.bmp");
		imageHM1 = loadBMP("../data/hm1.bmp");
		cloudImage = loadBMP("../data/clouds.bmp");

		//invItems->getTextureId(GL_NEAREST);
		imageHM0->getTextureId(GL_NEAREST);
		imageHM1->getTextureId(GL_NEAREST);
		cloudImage->getTextureId(GL_LINEAR);

		selGeomListInd = 0;

		mapSampScale = 0.5f;
		curMS = 0.0;
		//renderCount = 1.0;
		int newPitch = (imageHM0->width) * mapSampScale; //*2;

		numLights = MAX_LIGHTS;//min(MAX_LIGHTS,E_OBJ_LENGTH-E_OBJ_LIGHT0);


		//////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////


		initStyleSheet();

		
		masterVolume = 0.0f;
		ambientVolume = 0.0f;
		guiVolume = 0.0f;
		musicVolume = 0.0f;
		fxVolume = 0.0f;

		applyToChildren = false;
		mirrorOn = true;
		guiOn = false;
		bCtrlOld = false;
		bShiftOld = false;
		bCtrl = false;
		bShift = false;
		tiltChanged = false;
		emptyVDNotReady = true;
		firstRun = true;
		waterOn = true;
		treesOn = true;
		rotOn = false;

		maxLayers = MAX_LAYERS;

		// Resolution Dependent

		volGenFBOX = 128; // MAX OF 128, DO NOT CHANGE THIS VALUE

		
		
		
		
		/////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////
		
				
		// IMPORTANT: Maximum height must be less than 2^16, max world pitch must be less than 2^32
		
		// todo:
		
		// realtime cutaway based on green cube position
		// character editor load from json
		// floating trees
		// stacked lots?
		
		
		
		// qqqqqq
		
		// WAS DOING:
		// undo destruction
		
		// adjust camera for better loading, ray cast from cam pos to find nearest
		// chunk to load
		// flood fill from there until it hits blank chunk and stop
		
		
		
		int bufferDiv = 2;
		int curProfile;
		
		scrollDiv = 2.0;
		
		msPerFrame = 8.0;
		
		
		//curProfile = E_PP_ENTITY;
		curProfile = 999;//E_PP_SCROLLING;

		switch (curProfile) {
			
			case E_PP_TILTING:
				skipFrames = 1;
				maxChangesInPages = 1;
				maxChangesInHolders = 8; 
				
				maxHInPages = 2;
				maxWInPages = 4;
				minWInPages = 1;
				
				

				pixelsPerMeter = 64;
				metersPerPage = 8;
				metersPerHolder = 8;
				holderMod = 8;
			break;
			
			
			case E_PP_FAST_LOWRES:
				skipFrames = 1;
				maxChangesInPages = 1;
				maxChangesInHolders = 8; 
				
				maxHInPages = 1;
				maxWInPages = 2;
				minWInPages = 1;
				
				

				pixelsPerMeter = 128;
				metersPerPage = 4;
				metersPerHolder = 4;
				holderMod = 4;
			
			case E_PP_SCROLLING:
				skipFrames = 1;
				maxChangesInPages = 8;
				maxChangesInHolders = 2; 
				
				maxHInPages = 2;
				maxWInPages = 4;
				minWInPages = 1;
				
				

				pixelsPerMeter = 128;
				metersPerPage = 4;
				metersPerHolder = 16;
				holderMod = 4;
			break;
			case E_PP_ENTITY:
				skipFrames = 1;
				maxChangesInPages = 1;
				maxChangesInHolders = 4; 
				
				maxHInPages = 2;
				maxWInPages = 4;
				minWInPages = 1;

				pixelsPerMeter = 128;
				metersPerPage = 4;
				metersPerHolder = 4;
				holderMod = 4;
			break;
			
			case E_PP_TERRAIN_MODIFICATION:
				skipFrames = 1;
				maxChangesInPages = 1;
				maxChangesInHolders = 1; 
				
				maxHInPages = 2;
				maxWInPages = 3;
				minWInPages = 1;

				pixelsPerMeter = 128;
				metersPerPage = 4;
				metersPerHolder = 8;
				holderMod = 4;
			break;
			case E_PP_FAST_MODIFICATION:
				skipFrames = 1;
				maxChangesInPages = 1;
				maxChangesInHolders = 1; 
				
				maxHInPages = 2;
				maxWInPages = 3;
				minWInPages = 1;

				pixelsPerMeter = 128;
				metersPerPage = 4;
				metersPerHolder = 4;
				holderMod = 8;
			break;
			case E_PP_HIGHQUALITY:
				skipFrames = 1;
				maxChangesInPages = 4;
				maxChangesInHolders = 1; 
				
				maxHInPages = 2;
				maxWInPages = 4;
				minWInPages = 1;

				pixelsPerMeter = 128;
				metersPerPage = 4;
				metersPerHolder = 16;
				holderMod = 2;
			break;
			default:
				skipFrames = 1;
				maxChangesInPages = 1;
				maxChangesInHolders = 8;
				
				maxHInPages = 2;
				maxWInPages = 4;
				minWInPages = 1;

				pixelsPerMeter = 128;
				metersPerPage = 4;
				metersPerHolder = 16;
				holderMod = 4;
			break;
		}
		
		

		
		

		
		// This var determines how high the z val can go,
		// but also increases load times for each block
		
		metersPerLot = 64; // adjust this to make lots bigger
		
		metersPerNodeXY = 16;
		metersPerNodeZ = 8;
		blockSizeInLots = 4;
		unitsPerMeter = 4; // ONE UNIT == ONE METER
		

		worldSizeInLots.setIXYZ(newPitch, newPitch, blockSizeInLots);
		worldSizeInMeters.copyIntMult(&worldSizeInLots, metersPerLot);
		blockSizeInMeters = blockSizeInLots * metersPerLot;
		holderSizeInPages = metersPerHolder / metersPerPage;
		holdersPerLot = metersPerLot / metersPerHolder;
		visPageSizeInUnits = metersPerPage * unitsPerMeter;
		bufferMult = 1.25f;
		bufferedPageSizeInUnits = visPageSizeInUnits * bufferMult;
		worldSizeInHolders.copyIntMult(&worldSizeInLots, holdersPerLot);
		blockSizeInHolders = blockSizeInLots * holdersPerLot;
		blockSizeInPages = blockSizeInHolders * holderSizeInPages;
		worldSizeInBlocks.copyIntDiv(&worldSizeInHolders, blockSizeInHolders);
		worldSizeInPages.copyIntMult(&worldSizeInHolders, holderSizeInPages);
		worldSizeInUnits.copyIntMult(&worldSizeInPages, visPageSizeInUnits);
		
		
		

		pixelsPerLot = pixelsPerMeter * metersPerLot;
		unitSizeInPixels = pixelsPerMeter / unitsPerMeter;
		blockSizeInPixels = pixelsPerMeter * blockSizeInMeters;
		worldSizeInPixels.copyIntMult(&worldSizeInMeters, pixelsPerMeter);
		
		visPageSizeInPixels = pixelsPerMeter * metersPerPage;
		holderSizeInPixels = pixelsPerMeter * metersPerHolder;
		
		
		// pageResolution = visPageSizeInPixels;//512; // height of one page in pixels
		
		
		fHolderMod = (float)holderMod;
		holderResolution = holderSizeInPixels/holderMod;
		
		
		
		
		
		
		
		
		
		
		terDataTexScale = 1;
		//if (pixelsPerMeter >= 128) {
			terDataTexScale = 2;
		//}
		
		terDataVisPitchXY = blockSizeInMeters / metersPerNodeXY;
		iNodeDivsPerLot = terDataVisPitchXY / blockSizeInLots;
		terDataBufAmount = iNodeDivsPerLot; // pad with one extra lot
		
		floorHeightInMeters = (float)metersPerNodeZ;
		roofHeightInMeters = ((float)metersPerNodeXY)/4.0f;
		wallRadInMeters = ((float)metersPerNodeXY)/4.0f;
		
		
		terDataBufPitchXY = terDataVisPitchXY + terDataBufAmount * 2;
		terDataBufPitchScaledXY = terDataBufPitchXY * terDataTexScale;
		
		terDataVisPitchZ = blockSizeInMeters / metersPerNodeZ;
		terDataBufPitchZ = terDataVisPitchZ + terDataBufAmount * 2;
		terDataBufPitchScaledZ = terDataBufPitchZ * terDataTexScale;

		terDataVisSize = terDataVisPitchXY * terDataVisPitchXY * terDataVisPitchZ;
		terDataBufSize = terDataBufPitchXY * terDataBufPitchXY * terDataBufPitchZ;
		terDataBufSizeScaled = terDataBufPitchScaledXY * terDataBufPitchScaledXY * terDataBufPitchScaledZ;


		terDataScaled = new uint[terDataBufSizeScaled];
		rbStack = new int[terDataBufSize];
		rbHeightStack = new int[terDataBufSize];


		worldSizeInTerData.setIXYZ(
			worldSizeInBlocks.getIX()*terDataVisPitchXY,
			worldSizeInBlocks.getIY()*terDataVisPitchXY,
			worldSizeInBlocks.getIZ()*terDataVisPitchZ
		);
		


		
		tiltAmount = 0.5f;


		
		blockShift = intLogB2(blockSizeInHolders * blockSizeInHolders * blockSizeInHolders);
		holderSizeMB = ( ((float)MAX_LAYERS) * 2.0f * 4.0f * (float)(holderResolution * holderResolution)) / (1024.0f * 1024.0f);








		cout << "\n\n\n\n\n\n";



		// cout << "terDataBufPitchXY: " << terDataBufPitchXY << "\n";
		// cout << "terDataBufPitchZ: " << terDataBufPitchXY << "\n";
		// cout << "terDataVisPitchXY: " << terDataBufPitchXY << "\n";
		// cout << "terDataVisPitchZ: " << terDataBufPitchXY << "\n";
		
		
		cout << "blockSizeInHolders: " << blockSizeInHolders << "\n";
		cout << "blockSizeInPixels: " << blockSizeInPixels << "\n";
		cout << "terDataBufPitchScaledXY " << terDataBufPitchScaledXY << "\n";
		cout << "maxChangesInHolders: " << maxChangesInHolders << "\n";
		cout << "volGenFBOX: " << volGenFBOX << "\n";
		cout << "volGenFBOY: " << volGenFBOX *volGenFBOX << "\n";
		cout << "visPageSizeInPixels: " << visPageSizeInPixels << "\n";
		cout << "holderSizeInPixels: " << holderSizeInPixels << "\n";
		cout << "bufferMult: " << bufferMult << "\n";
		cout << "metersPerLot: " << metersPerLot << "\n";
		cout << "pixelsPerMeter: " << pixelsPerMeter << "\n";
		cout << "unitsPerMeter: " << unitsPerMeter << "\n";
		cout << "blockSizeInLots: " << blockSizeInLots << "\n";
		cout << "pixelsPerUnit: " << unitSizeInPixels << "\n";
		cout << "unitsPerLot: " << metersPerLot*unitsPerMeter << "\n";
		cout << "pixelsPerLot: " << pixelsPerLot << "\n";
		cout << "holderSizeInPages: " << holderSizeInPages << "\n";
		cout << "holdersPerLot: " << holdersPerLot << "\n";
		cout << "visPageSizeInUnits: " << visPageSizeInUnits << "\n";
		cout << "unitSizeInPixels: " << unitSizeInPixels << "\n";


		doTraceVecND("worldSizeInBlocks: ", &worldSizeInBlocks);
		doTraceVecND("worldSizeInLots: ", &worldSizeInLots);
		doTraceVecND("worldSizeInHolders: ", &worldSizeInHolders);
		doTraceVecND("worldSizeInPages: ", &worldSizeInPages);
		doTraceVecND("worldSizeInTerData: ", &worldSizeInTerData);

		GLint glQuery;
		glGetIntegerv(GL_MAX_UNIFORM_LOCATIONS, &glQuery);
		cout << "MAX_UNIFORMS: " << glQuery << "\n";

		cout << "\n\n\n\n\n\n";


		voroSize = 32;
		mapFreqs.setFXYZW(1.0f, 16.0f, 32.0f, 64.0f);
		mapAmps.setFXYZW(1.0f, 8.0f/16.0f, 2.0f/16.0f, 1.0f/16.0f); //0.0f, 0.0f, 0.0f);//


		gridSizeInPixels = pixelsPerMeter;



		//////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////
		radiosityOn = true;
		testOn = false;
		updateLock = false;
		traceOn = false;
		gridOn = 0.0f;
		fogOn = 1.0f;
		geomCounter = 0;
		lightCounter = 0;



		int ccr = 0;
		int ccg = 0;
		int ccb = 0;

		doTraceVecND("worldSizeInPixels: ", &worldSizeInPixels);






		glGenTextures(1, &volId);
		glGenTextures(1, &volIdLinear);
		glGenTextures(1, &volIdEmpty);
		glGenTextures(1, &volIdEmptyLinear);

		int curFilter;

		for (i = 0; i < MAX_TER_TEX; i++)
		{

			terTextures[i].usedByBlockId = -1;
			terTextures[i].alreadyBound = false;


			// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, w, h, 0, GL_RGBA, GL_FLOAT, 0);

			glGenTextures(1, &(terTextures[i].texId));
			glBindTexture(GL_TEXTURE_3D, terTextures[i].texId);
			glTexImage3D(
				GL_TEXTURE_3D,
				0,
				GL_RGBA,
				terDataBufPitchScaledXY,
				terDataBufPitchScaledXY,
				terDataBufPitchScaledZ,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				0
			);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_BORDER_COLOR, 0);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glBindTexture(GL_TEXTURE_3D, 0);

			TOT_GPU_MEM_USAGE += ((float)(terDataBufSizeScaled * 4)) / (1024.0f * 1024.0f);
		}



		for (i = 0; i < 4; i++)
		{
			switch (i)
			{
			case 0:
				glBindTexture(GL_TEXTURE_3D, volId);
				break;
			case 1:
				glBindTexture(GL_TEXTURE_3D, volIdEmpty);
				break;
			case 2:
				glBindTexture(GL_TEXTURE_3D, volIdLinear);
				break;
			case 3:
				glBindTexture(GL_TEXTURE_3D, volIdEmptyLinear);
				break;
			}
			if (i < 2)
			{
				curFilter = GL_NEAREST;
			}
			else
			{
				curFilter = GL_LINEAR;
			}

			glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, bufferedPageSizeInUnits, bufferedPageSizeInUnits, bufferedPageSizeInUnits, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, curFilter);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, curFilter);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_BORDER_COLOR, 0);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glBindTexture(GL_TEXTURE_3D, 0);
		}


		geomIdArr = new int[1024];
		paramArr = new float[4096];
		voroArr = new float[27 * 4];
		matCountArr = new float[256];
		paramArrMap = new float[4096];




		showMap = true;



		lastImageBuffer.data = NULL;
		lastImageBuffer.size = 0;

		lastJSONBuffer.data = NULL;
		lastJSONBuffer.size = 0;
		
		lastJSONBufferGUI.data = NULL;
		lastJSONBufferGUI.size = 0;
		

		nullBuffer.data = new char[1];
		nullBuffer.data[0] = '\0';
		nullBuffer.size = 0;



		palWidth = 256;
		palHeight = 256;

		resultImage = new unsigned char[palWidth * palHeight * 4];

		mouseMovingSize = 100;
		mouseMovingLoc = 0;
		mouseCount = 0;
		mouseMovingStepsBack = 20;
		mouseMoving = new FIVector4[mouseMovingSize];

		#ifdef USE_POCO
		myWS = _myWS;
		#endif
		

		

		isZooming = false;
		isPanning = false;
		isBare = true;




		defaultWinW = _defaultWinW / _scaleFactor;
		defaultWinH = _defaultWinH / _scaleFactor;
		scaleFactor = _scaleFactor;
		
		guiWinW = _defaultWinW / UI_SCALE_FACTOR;
		guiWinH = _defaultWinH / UI_SCALE_FACTOR;

		origWinW = _defaultWinW;
		origWinH = _defaultWinH;

		curBrushRad = 4.0f;

		mouseState = E_MOUSE_STATE_MOVE;








		wsBufferInvalid = true;

		bufferDim.setIXY(defaultWinW, defaultWinH);
		bufferDimTarg.setIXY(defaultWinW, defaultWinH);
		
		bufferDimHalf.setIXY(defaultWinW / 2, defaultWinH / 2);
		bufferModDim.copyIntMult(&bufferDim,holderMod);

		myTimer.start();
		//fpsTimer.start();

		//grassState = E_GRASS_STATE_OFF;

		activeObject = E_OBJ_CAMERA;

		extraRad = 0;
		lastTime = 0.0;







		mbDown = false;
		lbDown = false;
		rbDown = false;
		abDown = false;



		isFullScreen = false;
		shadersAreLoaded = 0;
		readyToRecompile = 0;

		programState = E_PS_IN_GAME;


		for (i = 0; i < E_OBJ_LENGTH; i++)
		{
			dynObjects.push_back(new DynObject());
		}

		dynObjects[E_OBJ_CAMERA]->init(0, 0, worldSizeInPixels.getIZ() / 2, 0, 0, 0, false, false, NULL, 4.0f );

		for (i = E_OBJ_LIGHT0; i < E_OBJ_LENGTH; i++)
		{

			j = i - E_OBJ_LIGHT0;

			switch (j)
			{
			case 0:
				ccr = 255;
				ccg = 255;
				ccb = 255;
				break;

			case 1:
				ccr = 255;
				ccg = 0;
				ccb = 0;

				break;

			case 2:
				ccr = 255;
				ccg = 128;
				ccb = 0;

				break;

			case 3:
				ccr = 0;
				ccg = 255;
				ccb = 0;

				break;

			case 4:
				ccr = 0;
				ccg = 128;
				ccb = 255;

				break;
			case 5:
				ccr = 128;
				ccg = 0;
				ccb = 255;

				break;
			}

			dynObjects[i]->init(4096*4 + i * 256, 4096*4 + i * 256, 4096*4, ccr, ccg, ccb,     true, true, &(dynObjects[E_OBJ_CAMERA]->pos), 64.0f );



		}

		dynObjects[E_OBJ_FOG]->init(-1024*2, -1024*2, -1024/2,   0, 0, 255,     true, true, &(dynObjects[E_OBJ_CAMERA]->pos), 64.0f );
		dynObjects[E_OBJ_CUTAWAY]->init(4096*4 - 256, 4096*4 - 256 + 2048, 4096*4,   0, 255, 0,     true, true, &(dynObjects[E_OBJ_CAMERA]->pos), 64.0f );
		dynObjects[E_OBJ_HUMAN]->init(0, 1024/2, 0,   0, 255, 255,     true, true, &(dynObjects[E_OBJ_CAMERA]->pos), 64.0f );

		// dynObjects[E_OBJ_P0]->init(512-256,1024-256,2048,   128,0,0,    true, true, &(dynObjects[E_OBJ_CAMERA]->pos), 64.0f );
		// dynObjects[E_OBJ_P1]->init(512,1024,2048,      255,0,0,  true, true, &(dynObjects[E_OBJ_CAMERA]->pos), 64.0f );
		// dynObjects[E_OBJ_P2]->init(1024,512,2048,      0,255,255,  true, true, &(dynObjects[E_OBJ_CAMERA]->pos), 64.0f );


		cameraZoom = 1.0f;
		targetZoom = 1.0f;

		mouseX = 0.0f;
		mouseY = 0.0f;
		mouseXUp = 0.0f;
		mouseYUp = 0.0f;






		//// GL WIDGET START ////

		frameCount = 0;
		changesMade = false;
		forceGetPD = false;
		bufferInvalid = false;
		mapInvalid = true;
		notQuit = true;
		timerNotSet = true;
		screenWidth = defaultWinW;
		screenHeight = defaultWinH;
		mouseLeftDown = mouseRightDown = false;
		mouseX = mouseY = 0;
		myDelta = 0.0f;



		//gm = new GameMap();
		orthographicProjection();
		//// GL WIDGET END ////



		glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // 4-byte pixel alignment
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_BLEND);
		//glEnable(GL_BLEND);

		
		
		
		shaderStrings.push_back("GUIShader");
		shaderStrings.push_back("RoadShader");
		shaderStrings.push_back("SkeletonShader");
		shaderStrings.push_back("DilateShader");
		shaderStrings.push_back("TerrainMix");
		shaderStrings.push_back("Simplex2D");
		shaderStrings.push_back("TopoShader");
		shaderStrings.push_back("TCShader");
		shaderStrings.push_back("TCShader2");
		shaderStrings.push_back("WaveHeightShader");
		shaderStrings.push_back("WaterShader");
		shaderStrings.push_back("WaterShaderCombine");
		shaderStrings.push_back("CopyShader");
		shaderStrings.push_back("CopyShader2");
		shaderStrings.push_back("NoiseShader");
		shaderStrings.push_back("MapBorderShader");
		shaderStrings.push_back("WorldSpaceShader");
		shaderStrings.push_back("BlitShader");
		shaderStrings.push_back("BlitParentShader");
		shaderStrings.push_back("PreLightingShader");
		shaderStrings.push_back("BlurShader");
		shaderStrings.push_back("HBlurShader");
		shaderStrings.push_back("VBlurShader");
		shaderStrings.push_back("DownScaleShader");
		shaderStrings.push_back("RadiosityShader");
		shaderStrings.push_back("RadiosityCombineShader");
		shaderStrings.push_back("FogShader");
		shaderStrings.push_back("GeomShader");
		shaderStrings.push_back("CombineShader");
		shaderStrings.push_back("GenerateVolume");
		shaderStrings.push_back("GenerateVolumeEnt");
		shaderStrings.push_back("RenderVolume");


		std::sort(shaderStrings.begin(), shaderStrings.end(), compareStruct);
		stringBuf.reserve(shaderStrings.size()*256);


		shaderTextureIds.push_back("Texture0");
		shaderTextureIds.push_back("Texture1");
		shaderTextureIds.push_back("Texture2");
		shaderTextureIds.push_back("Texture3");
		shaderTextureIds.push_back("Texture4");
		shaderTextureIds.push_back("Texture5");
		shaderTextureIds.push_back("Texture6");
		shaderTextureIds.push_back("Texture7");
		shaderTextureIds.push_back("Texture8");
		shaderTextureIds.push_back("Texture9");
		shaderTextureIds.push_back("Texture10");
		shaderTextureIds.push_back("Texture11");
		shaderTextureIds.push_back("Texture12");
		shaderTextureIds.push_back("Texture13");
		shaderTextureIds.push_back("Texture14");
		shaderTextureIds.push_back("Texture15");

		//setupLookups();

		for (i = 0; i < shaderStrings.size(); i++)
		{
			shaderMap.insert(  pair<string, Shader*>(shaderStrings[i], new Shader(this))  );
		}
		doShaderRefresh(false);
		
		int faceDim = 256;
		
		
		for (i = 0; i < MAX_VG_FBOS; i++) {
			vgFBOArr[i].init(1, volGenFBOX, volGenFBOX * volGenFBOX, 1, false);
		}
		
		
		
		
		
		
		/* (
				int _numBufs,
				int _width,
				int _height,
				int _bytesPerChannel,
				bool _hasDepth,
				int filterEnum = GL_NEAREST,
				int clampEnum = GL_CLAMP_TO_EDGE,
				bool isMultisample = false
		)*/
		
		
		
		
		//GL_LINEAR
		fboMap["worldSpaceFBO"].init(4, bufferDim.getIX(), bufferDim.getIY(), 4, false, GL_NEAREST);
		fboMap["worldSpaceWavesFBO"].init(1, bufferDim.getIX(), bufferDim.getIY(), 4, false, GL_NEAREST);
		
		//fboMap["worldSpaceBlurFBO0"].init(1, bufferDim.getIX()/2, bufferDim.getIY()/2, 4, false, GL_LINEAR);
		//fboMap["worldSpaceBlurFBO1"].init(1, bufferDim.getIX()/2, bufferDim.getIY()/2, 4, false, GL_LINEAR);
		
		fboMap["frontFaceFBO"].init(1, faceDim, faceDim, 4, false, GL_NEAREST);
		fboMap["backFaceFBO"].init(1, faceDim, faceDim, 4, false, GL_NEAREST);
		fboMap["frontFaceMapFBO"].init(1, bufferDim.getIX(), bufferDim.getIY(), 4, false, GL_NEAREST);
		fboMap["backFaceMapFBO"].init(1, bufferDim.getIX(), bufferDim.getIY(), 4, false, GL_NEAREST);
		fboMap["palFBO"].init(1, palWidth, palHeight, 1, false, GL_LINEAR);
		
		fboMap["pagesFBO"].init(2, bufferDimTarg.getIX(), bufferDimTarg.getIY(), 1, false);
		fboMap["waterFBO"].init(2, bufferDimTarg.getIX(), bufferDimTarg.getIY(), 1, false);
		fboMap["pages2FBO"].init(2, bufferDimTarg.getIX(), bufferDimTarg.getIY(), 1, false);
		fboMap["water2FBO"].init(2, bufferDimTarg.getIX(), bufferDimTarg.getIY(), 1, false);
		fboMap["pages3FBO"].init(2, bufferDimTarg.getIX(), bufferDimTarg.getIY(), 1, false);
		fboMap["water3FBO"].init(2, bufferDimTarg.getIX(), bufferDimTarg.getIY(), 1, false);
		fboMap["geomFBO"].init(2, bufferDimTarg.getIX(), bufferDimTarg.getIY(), 1, true);
		fboMap["combineFBO"].init(2, bufferDimTarg.getIX(), bufferDimTarg.getIY(), 1, false);
		fboMap["combineFBOWithWater"].init(2, bufferDimTarg.getIX(), bufferDimTarg.getIY(), 1, false);
		
		fboMap["noiseFBO"].init(1, bufferDim.getIX(), bufferDim.getIY(), 1, false, GL_NEAREST, GL_REPEAT);
		fboMap["guiFBO"].init(1, guiWinW, guiWinH, 1, false, GL_LINEAR);
		fboMap["resultFBO0"].init(1, bufferDim.getIX(), bufferDim.getIY(), 1, false, GL_NEAREST);
		fboMap["resultFBO1"].init(1, bufferDim.getIX(), bufferDim.getIY(), 1, false, GL_NEAREST);
		//fboMap["volGenFBO0"].init(1, volGenFBOX, volGenFBOX * volGenFBOX, 1, false);
		//fboMap["volGenFBO1"].init(1, volGenFBOX, volGenFBOX * volGenFBOX, 1, false);
		fboMap["waveFBO"].init(1, bufferDim.getIX(), bufferDim.getIY(), 1, false, GL_LINEAR);
		fboMap["swapFBOLin0"].init(1, bufferDim.getIX(), bufferDim.getIY(), 1, false, GL_LINEAR);
		fboMap["swapFBOLin1"].init(1, bufferDim.getIX(), bufferDim.getIY(), 1, false, GL_LINEAR);
		fboMap["swapFBOBLin0"].init(1, bufferDim.getIX() / bufferDiv, bufferDim.getIY() / bufferDiv, 1, false, GL_LINEAR);
		fboMap["swapFBOBLin1"].init(1, bufferDim.getIX() / bufferDiv, bufferDim.getIY() / bufferDiv, 1, false, GL_LINEAR);
		fboMap["swapFBOLinHalf0"].init(1, bufferDim.getIX() / bufferDiv, bufferDim.getIY() / bufferDiv, 1, false, GL_LINEAR);
		fboMap["swapFBOLinHalf1"].init(1, bufferDim.getIX() / bufferDiv, bufferDim.getIY() / bufferDiv, 1, false, GL_LINEAR);
		fboMap["cityFBO"].init(1, newPitch, newPitch, 1, false, GL_NEAREST, GL_REPEAT);
		fboMap["hmFBO"].init(1, newPitch, newPitch, 1, false, GL_NEAREST, GL_REPEAT);
		fboMap["hmFBOLinear"].init(1, newPitch, newPitch, 1, false, GL_LINEAR, GL_REPEAT);
		fboMap["simplexFBO"].init(1, newPitch, newPitch, 1, false, GL_LINEAR, GL_REPEAT);
		fboMap["swapFBO0"].init(1, newPitch, newPitch, 1, false, GL_NEAREST, GL_REPEAT);
		fboMap["swapFBO1"].init(1, newPitch, newPitch, 1, false, GL_NEAREST, GL_REPEAT);


		
		createVTListTilt();



		fontWrappers[EFW_ICONS] = new FontWrapper();
		fontWrappers[EFW_ICONS]->init(this, "icons", true, 2.0f, 0.0f);
		
		fontWrappers[EFW_TEXT] = new FontWrapper();
		fontWrappers[EFW_TEXT]->init(this, "arial_regular_24", false, 1.0f);

		mainGUI = new GameGUI();
		mainGUI->init(this);


		loadAllData();

		GamePlant::initAllPlants(this);
		for (i = 0; i < E_PT_LENGTH/2; i++) {
			gamePlants[i] = new GamePlant();
		}


		gw = new GameWorld();
		
		gpuPool = new PoolManager();
		entityPool = new PoolManager();
		//gpuPagePool = new PoolPageManager();
		//entityPagePool = new PoolPageManager();
		
		
		gpuPool->init(this,false,false,holderResolution,holderResolution);
		entityPool->init(this,true,false,holderResolution,holderResolution);
		
		
		
		testHuman = new GameEnt();
		testHuman->init(this);
		
		gw->init(this);
		gw->initMap();
			
		
		music[EML_BIRDSONG0]->play();
		music[EML_CRICKETS0]->play();
		music[EML_OCEANWAVES0]->play();
		
		
		loadGUI();
		loadGUIValues();
		
		if (bakeParamsOn) {
			doShaderRefresh(true);
		}
		

		doTraceND("GW DONE");


		popTrace();



	}
void Singleton::prepSound (string soundName)
                                         {
		if (soundMap.find( soundName ) == soundMap.end()) {
			soundMap.insert( pair<string, GameSound>(soundName, GameSound()) );
			soundMap[soundName].init("../data/sounds/"+soundName+".wav");
		}
	}
void Singleton::playSoundPosAndPitch (string soundName, FIVector4 * listenerPos, FIVector4 * soundPos, float variance, float volume)
          {
		
		
		FIVector4 res;
		
		prepSound(soundName);
		
		res.setFXYZRef(soundPos);
		res.addXYZRef(listenerPos,-1.0f);
		
		soundMap[soundName].setPitch(
			(fGenRand()-0.5f)*2.0*variance + 1.0f
		);
		
		soundMap[soundName].setPositionAndMinDis(
			res.getFX(),
			res.getFY(),
			res.getFZ(),
			32.0f*pixelsPerMeter
		);
		soundMap[soundName].play(volume*fxVolume*masterVolume);
	}
void Singleton::playSound (string soundName, float volume)
                                                            {
		prepSound(soundName);
		soundMap[soundName].play(volume);
	}
void Singleton::playSoundEvent (char const * eventName, bool suppress)
                                                                          {
		
		if (suppress) {
			return;
		}
		
		string tempString;
		float volume;
		
		if (mainGUI != NULL) {
			if (mainGUI->isReady) {
				tempString = mainGUI->jvSounds->Child(eventName)->Child("name")->string_value;
				volume = mainGUI->jvSounds->Child(eventName)->Child("vol")->number_value;
				
				if (tempString.size() > 0) {
					playSound( tempString, masterVolume*volume*guiVolume );
				}
			}
		}
		
		
		
		
		
		
	}
void Singleton::dispatchEvent (int button, int state, float x, float y, UIComponent * comp, bool automated, bool preventRefresh)
          {
		
		changingGenVal = false;
		
		// if (guiLock) {
		// 	return;
		// }
		
		int i;
		int cbDataCount;
		JSONValue* cbData = NULL;
		
		bool doSPUpdate = false;
		bool mouseUpEvent = false;
		
		float curValue = comp->getValue();
		
		switch (comp->guiClass) {
			case E_GT_SLIDER:
			case E_GT_BUTTON:
			case E_GT_RADIO:
			
				switch(button) {
					case GLUT_NO_BUTTON:
					
						
						
						switch(state) {
							case GLUT_OVER:
								playSoundEvent("mouseOver",automated);
							break;
							case GLUT_OUT:
								playSoundEvent("mouseOut",automated);
							break;
							case GLUT_CHANGING:
								
								doSPUpdate = true;
							break;
						}
						
					break;
					case GLUT_LEFT_BUTTON:
						if (state == GLUT_DOWN) {
							playSoundEvent("mouseDown",automated);
						}
						else {
							playSoundEvent("mouseUp",automated);
							doSPUpdate = true;
							mouseUpEvent = true;
						}
					break;
					
				}
			
				
			break;	
		}
		
		
		if (comp->uid.compare("$options.sound.masterVolume") == 0) {
			masterVolume = curValue;
		}
		else if (comp->uid.compare("$options.sound.ambientVolume") == 0) {
			ambientVolume = curValue;
		}
		else if (comp->uid.compare("$options.sound.guiVolume") == 0) {
			guiVolume = curValue;
		}
		else if (comp->uid.compare("$options.sound.musicVolume") == 0) {
			musicVolume = curValue;
		}
		else if (comp->uid.compare("$options.sound.fxVolume") == 0) {
			fxVolume = curValue;
		}
		else if (comp->uid.compare("$charEdit.entOn") == 0) {
			entOn = curValue != 0.0f;
		}
		else if (comp->uid.compare("$charEdit.pathfindingOn") == 0) {
			pathfindingOn = curValue != 0.0f;
		}
		else if (comp->uid.compare("$charEdit.mirrorOn") == 0) {
			mirrorOn = curValue != 0.0f;
		}
		else if (comp->uid.compare("$charEdit.applyToChildren") == 0) {
			applyToChildren = curValue != 0.0f;
		}
		
		
		if (comp->jvNodeNoTemplate != NULL) {
			if (comp->jvNodeNoTemplate->HasChild("callback")) {
				curCallback = comp->jvNodeNoTemplate->Child("callback")->string_value;
				
				if (comp->jvNodeNoTemplate->HasChild("callbackData")) {
					
					cbData = comp->jvNodeNoTemplate->Child("callbackData");
				
					// cbDataCount = cbData->CountChildren();
					// for (i = 0; i < cbDataCount; i++) {
					// 	cbDataStrings[i] = cbData->Child(i)->string_value;
					// }
				
				}
				
				if (doSPUpdate) {
					if (curCallback.compare("updateShaderParam") == 0) {
						
						if (cbData != NULL) {
							cbDataStrings[0] = cbData->Child("shaderName")->string_value;
							cbDataStrings[1] = cbData->Child("paramName")->string_value;
							
							
							
							shaderMap[cbDataStrings[0]]->paramMap[cbDataStrings[1]] = curValue;
							
							if (
								(cbDataStrings[0].compare("GenerateVolume") == 0)	||
								(cbDataStrings[0].compare("RenderVolume") == 0)
							) {
								
								if (preventRefresh) {
									
								}
								else {
									if (mouseUpEvent) {
										forceRestart = true;
										readyForRestart = true;
									}
									else {
										changingGenVal = true;
										if (mouseMoved) {
											
											readyForRestart = true;
										}
									}
								}
								
								
								
							}
							
							
						}
					}
				}
				
				
			}
		}
		
		
		if (mouseMoved) {
			mouseMoved = false;
		}
	}
StyleSheet * Singleton::getNewStyleSheet (string ssName)
                                                    {
		styleSheetMap[ssName].init();
		return &(styleSheetMap[ssName]);
	}
void Singleton::initStyleSheet ()
                              {
		
		
		StyleSheet* mainSS = getNewStyleSheet("defaultSS");
		StyleSheetState* curState = &(mainSS->compStates[E_COMP_UP]);
		
		
		
		curState->setVal(E_SS_BGCOL0_R, 0.2f, 0.15f, 0.1f, 1.0f);
		curState->setVal(E_SS_BGCOL1_R, 0.1f, 0.075f, 0.05f, 0.5f);
		curState->setVal(E_SS_FGCOL0_R, 0.0f, 0.0f, 0.0f, 0.0f);
		curState->setVal(E_SS_FGCOL1_R, 0.0f, 0.0f, 0.0f, 0.0f);
		curState->setVal(E_SS_TGCOL0_R, 1.0f, 0.75f, 0.0f, 1.0f);
		curState->setVal(E_SS_TGCOL1_R, 1.0f, 0.25f, 0.0f, 0.5f);
		curState->setVal(E_SS_BGCOLTEXT0_R, 0.0f, 0.0f, 0.0f, 0.0f);
		curState->setVal(E_SS_BGCOLTEXT1_R, 0.0f, 0.0f, 0.0f, 0.0f);
		curState->setVal(E_SS_FGCOLTEXT0_R, 1.0f, 1.0f, 1.0f, 1.0f);
		curState->setVal(E_SS_FGCOLTEXT1_R, 1.0f, 0.8f, 0.7f, 1.0f);
		curState->setVal(E_SS_BDCOL_R, 1.0f, 1.0f, 1.0f, 0.5f);

		curState->props[E_SS_PADDING] = 4.0f;
		curState->props[E_SS_BORDER] = 1.0f;
		curState->props[E_SS_MARGIN] = 4.0f;
		curState->props[E_SS_CORNERRAD] = 4.0f;
		curState->props[E_SS_ROUNDNESS] = 1.0f;

		mainSS->compStates[E_COMP_OVER].copyFrom(& (mainSS->compStates[E_COMP_UP]) );
		mainSS->compStates[E_COMP_DOWN].copyFrom(& (mainSS->compStates[E_COMP_UP]) );

		
		
		curState = &(mainSS->compStates[E_COMP_OVER]);
		
		
		curState->setVal(E_SS_FGCOLTEXT0_R, 1.0f, 1.0f, 1.0f, 1.0f);
		curState->setVal(E_SS_FGCOLTEXT1_R, 1.0f, 1.0f, 1.0f, 1.0f);
		curState->props[E_SS_BDCOL_A] = 1.0f;
		
		curState->setVal(E_SS_BGCOL0_R, 0.1f, 0.075f, 0.05f, 1.0);
		curState->setVal(E_SS_BGCOL1_R, 0.05f, 0.025f, 0.0125f, 0.5);
		
		
		
		curState = &(mainSS->compStates[E_COMP_DOWN]);
		
		
		curState->setVal(E_SS_FGCOLTEXT0_R, 1.0f, 0.8f, 0.7f, 1.0f);
		curState->setVal(E_SS_FGCOLTEXT1_R, 1.0f, 1.0f, 1.0f, 1.0f);
		curState->props[E_SS_BDCOL_A] = 1.0f;
		curState->props[E_SS_BORDER] = 2.0f;

		curState->setVal(E_SS_BGCOL0_R, 0.05f, 0.025f, 0.0125f, 0.5f);	
		curState->setVal(E_SS_BGCOL1_R, 0.1f, 0.075f, 0.05f, 1.0f);	
		
		
		
		StyleSheet* tooltipSS = getNewStyleSheet("tooltipSS");
		tooltipSS->copyFrom(mainSS);
		
		curState = &(tooltipSS->compStates[E_COMP_UP]);
		curState->setVal(E_SS_BGCOL0_R, 0.0f, 0.0f, 0.0f, 1.0f);
		curState->setVal(E_SS_BGCOL1_R, 0.0f, 0.0f, 0.0f, 1.0f);
		curState->setVal(E_SS_FGCOLTEXT0_R, 1.0f, 0.75f, 0.0f, 1.0f);
		curState->setVal(E_SS_FGCOLTEXT1_R, 1.0f, 0.75f, 0.0f, 1.0f);
		curState->setVal(E_SS_BDCOL_R, 1.0f, 0.75f, 0.0f, 1.0f);
		tooltipSS->compStates[E_COMP_OVER].copyFrom(& (tooltipSS->compStates[E_COMP_UP]) );
		tooltipSS->compStates[E_COMP_DOWN].copyFrom(& (tooltipSS->compStates[E_COMP_UP]) );

		curState = &(tooltipSS->compStates[E_COMP_OVER]);
		curState = &(tooltipSS->compStates[E_COMP_DOWN]);
		
		
		
		
		StyleSheet* headerSS = getNewStyleSheet("headerSS");
		headerSS->copyFrom(mainSS);
		
		curState = &(headerSS->compStates[E_COMP_UP]);
		curState->setVal(E_SS_BGCOL0_R, 0.0f, 0.2f, 0.5f, 1.0f);
		curState->setVal(E_SS_BGCOL1_R, 0.0f, 0.4f, 0.8f, 0.5f);
		curState->setVal(E_SS_FGCOLTEXT0_R, 1.0f, 0.75f, 0.0f, 1.0f);
		curState->setVal(E_SS_FGCOLTEXT1_R, 1.0f, 0.75f, 0.0f, 1.0f);
		curState->setVal(E_SS_BDCOL_R, 1.0f, 0.75f, 0.0f, 1.0f);
		headerSS->compStates[E_COMP_OVER].copyFrom(& (headerSS->compStates[E_COMP_UP]) );
		headerSS->compStates[E_COMP_DOWN].copyFrom(& (headerSS->compStates[E_COMP_UP]) );

		curState = &(headerSS->compStates[E_COMP_OVER]);
		curState = &(headerSS->compStates[E_COMP_DOWN]);
		
		
		
	}
int Singleton::requestTerIndex (int requestingBlockId)
        {


		int i;

		bool foundFree = false;

		float bestDis;
		float testDis;
		int bestInd = 0;

		GameBlock *curBlock;

		// find if blockId already in use
		for (i = 0; i < MAX_TER_TEX; i++)
		{
			if (terTextures[i].usedByBlockId == requestingBlockId)
			{
				return i;
			}
		}

		// find if any blockIds not in use
		for (i = 0; i < MAX_TER_TEX; i++)
		{
			if (terTextures[i].usedByBlockId == -1)
			{
				bestInd = i;
				foundFree = true;
				break;
			}
		}

		if (foundFree)
		{

		}
		else
		{

			// find furthest blockId
			for (i = 0; i < MAX_TER_TEX; i++)
			{

				curBlock = gw->getBlockAtId(terTextures[i].usedByBlockId);
				testDis = curBlock->offsetInBlocks.distance(&(gw->camBlockPos));

				if (i == 0)
				{
					bestInd = 0;
					bestDis = testDis;
				}
				else
				{
					if (testDis > bestDis)
					{
						bestDis = testDis;
						bestInd = i;
					}
				}

			}

		}

		terTextures[bestInd].usedByBlockId = requestingBlockId;
		terTextures[bestInd].alreadyBound = false;
		return bestInd;


	}
void Singleton::qNormalizeAngle (int & angle)
        {
		while (angle < 0)
		{
			angle += 360 * 16;
		}
		while (angle > 360 * 16)
		{
			angle -= 360 * 16;
		}
	}
void Singleton::perspectiveProjection ()
        {
		float aspect = 1.0;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-aspect, +aspect, -1.0, +1.0, 4.0, 15.0);
		glMatrixMode(GL_MODELVIEW);
	}
void Singleton::orthographicProjection ()
        {

		glMatrixMode (GL_MODELVIEW);
		glLoadIdentity ();
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();

	}
Singleton::~ Singleton ()
        {
		if (gw)
		{
			delete gw;
		}
	}
void Singleton::setProgAction (eProgramState ps, unsigned char kc, eProgramAction pa, bool isDown)
        {

		if (isDown)
		{
			progActionsDown[ps * 256 + kc] = pa;
		}
		else
		{
			progActionsUp[ps * 256 + kc] = pa;
		}
	}
void Singleton::setProgActionAll (unsigned char kc, eProgramAction pa, bool isDown)
        {
		int i;

		for (i = 0; i < E_PS_SIZE; i++)
		{
			setProgAction((eProgramState)i, kc, pa, isDown);
		}

	}
void Singleton::drawCrossHairs (FIVector4 originVec, float radius)
        {
		FIVector4 minV;
		FIVector4 maxV;

		float xm;
		float ym;
		float zm;

		float maxRad = 4096.0f;

		int i;
		for (i = 0; i < 3; i++)
		{

			switch (i)
			{
			case 0:
				xm = maxRad;
				ym = radius;
				zm = radius;
				break;
			case 1:
				xm = radius;
				ym = maxRad;
				zm = radius;
				break;
			case 2:
				xm = radius;
				ym = radius;
				zm = maxRad;
				break;
			}

			minV.setFXYZ(
				originVec.getFX() - xm,
				originVec.getFY() - ym,
				originVec.getFZ() - zm
			);

			maxV.setFXYZ(
				originVec.getFX() + xm,
				originVec.getFY() + ym,
				originVec.getFZ() + zm
			);

			drawBox(&minV, &maxV);
		}


	}
void Singleton::drawLine (FIVector4 * p0, FIVector4 * p1)
        {
		

		glBegin(GL_LINES);
		glMultiTexCoord3f(GL_TEXTURE0, 0.0f, 0.0f, 0.0f);
		glVertex3f(p0->getFX(), p0->getFY(), p0->getFZ());
		glMultiTexCoord3f(GL_TEXTURE0, 0.0f, 0.0f, 1.0f);
		glVertex3f(p1->getFX(), p1->getFY(), p1->getFZ());
		glEnd();
	}
void Singleton::drawCubeCentered (FIVector4 * originVec, float radius)
        {
		FIVector4 minV;
		FIVector4 maxV;

		minV.setFXYZ(
			originVec->getFX() - radius,
			originVec->getFY() - radius,
			originVec->getFZ() - radius
		);

		maxV.setFXYZ(
			originVec->getFX() + radius,
			originVec->getFY() + radius,
			originVec->getFZ() + radius
		);

		drawBox(&minV, &maxV);
	}
void Singleton::drawBoxUp (FIVector4 originVec, float radiusX, float radiusY, float diamZ)
        {
		FIVector4 minV;
		FIVector4 maxV;

		minV.setFXYZ(
			originVec.getFX() - radiusX,
			originVec.getFY() - radiusY,
			originVec.getFZ()
		);

		maxV.setFXYZ(
			originVec.getFX() + radiusX,
			originVec.getFY() + radiusY,
			originVec.getFZ() + diamZ
		);

		drawBox(&minV, &maxV);
	}
void Singleton::drawBox (FIVector4 * minVec, FIVector4 * maxVec, int faceFlag)
        {


		float minX = minVec->getFX();
		float minY = minVec->getFY();
		float minZ = minVec->getFZ();

		float maxX = maxVec->getFX();
		float maxY = maxVec->getFY();
		float maxZ = maxVec->getFZ();


		bool drawFront = false;
		bool drawBack = false;
		
		switch(faceFlag) {
			case 0:
				drawBack = true;
			break;
			case 1:
				drawFront = true;
			break;
			case 2:
				drawBack = true;
				drawFront = true;
			break;
		}

		glBegin(GL_QUADS);


		if (drawFront) {
			// front
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, -1.0f, 1.0f);
			glVertex3f(minX, minY, maxZ);
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, -1.0f, 1.0f);
			glVertex3f(maxX, minY, maxZ);
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, 1.0f, 1.0f);
			glVertex3f(maxX, maxY, maxZ);
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, 1.0f, 1.0f);
			glVertex3f(minX, maxY, maxZ);
			// right
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, -1.0f, 1.0f);
			glVertex3f(maxX, minY, maxZ);
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, -1.0f, -1.0f);
			glVertex3f(maxX, minY, minZ);
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, 1.0f, -1.0f);
			glVertex3f(maxX, maxY, minZ);
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, 1.0f, 1.0f);
			glVertex3f(maxX, maxY, maxZ);
			// top
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, 1.0f, 1.0f);
			glVertex3f(minX, maxY, maxZ);
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, 1.0f, 1.0f);
			glVertex3f(maxX, maxY, maxZ);
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, 1.0f, -1.0f);
			glVertex3f(maxX, maxY, minZ);
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, 1.0f, -1.0f);
			glVertex3f(minX, maxY, minZ);
		}
		
		
		if (drawBack) {
			// back
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, -1.0f, -1.0f);
			glVertex3f(minX, minY, minZ);
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, -1.0f, -1.0f);
			glVertex3f(maxX, minY, minZ);
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, 1.0f, -1.0f);
			glVertex3f(maxX, maxY, minZ);
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, 1.0f, -1.0f);
			glVertex3f(minX, maxY, minZ);
			// left
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, -1.0f, 1.0f);
			glVertex3f(minX, minY, maxZ);
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, -1.0f, -1.0f);
			glVertex3f(minX, minY, minZ);
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, 1.0f, -1.0f);
			glVertex3f(minX, maxY, minZ);
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, 1.0f, 1.0f);
			glVertex3f(minX, maxY, maxZ);
			// bottom
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, -1.0f, 1.0f);
			glVertex3f(minX, minY, maxZ);
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, -1.0f, 1.0f);
			glVertex3f(maxX, minY, maxZ);
			glMultiTexCoord3f(GL_TEXTURE0, 1.0f, -1.0f, -1.0f);
			glVertex3f(maxX, minY, minZ);
			glMultiTexCoord3f(GL_TEXTURE0, -1.0f, -1.0f, -1.0f);
			glVertex3f(minX, minY, minZ);
		}
		
		
		
		
		



		glEnd();
	}
void Singleton::createVTListTilt ()
        {

		int i;
		int j;

		FIVector4 *cameraPos = &(dynObjects[E_OBJ_CAMERA]->pos);

		//volTris = glGenLists(1);

		float halfTilt = tiltAmount/2.0f;
		
		float halfTiltUp = 0.5f + halfTilt;
		float halfTiltDn = 0.5f - halfTilt;

		float texMin = 0.0f;
		float texMax = 1.0f;

		float fx1 = -1.0f;
		float fy2 = -1.0f;
		float fx2 = 1.0f;
		float fy1 = 1.0f;

		float centerX = (fx1 + fx2) / 2.0f;
		//float centerY = (fy1 + fy2) / 2.0f;

		float fy25 = fy1 * halfTiltUp + fy2 * halfTiltDn;
		float fy75 = fy1 * halfTiltDn + fy2 * halfTiltUp;

		float coordsX[8];
		float coordsY[8];

		coordsX[0] = centerX;
		coordsY[0] = fy1 * tiltAmount + fy2 * (1.0-tiltAmount);//centerY; // back face center

		coordsX[1] = centerX;
		coordsY[1] = fy1;

		coordsX[2] = fx2;
		coordsY[2] = fy25;

		coordsX[3] = fx2;
		coordsY[3] = fy75;

		coordsX[4] = centerX;
		coordsY[4] = fy2;

		coordsX[5] = fx1;
		coordsY[5] = fy75;

		coordsX[6] = fx1;
		coordsY[6] = fy25;

		coordsX[7] = coordsX[1];
		coordsY[7] = coordsY[1];

		float backfaceX[8];
		float backfaceY[8];
		float backfaceZ[8];



		backfaceX[0] = texMin;
		backfaceY[0] = texMin;
		backfaceZ[0] = texMin;
		backfaceX[1] = texMin;
		backfaceY[1] = texMin;
		backfaceZ[1] = texMax;
		backfaceX[2] = texMax;
		backfaceY[2] = texMin;
		backfaceZ[2] = texMax;
		backfaceX[3] = texMax;
		backfaceY[3] = texMin;
		backfaceZ[3] = texMin;
		backfaceX[4] = texMax;
		backfaceY[4] = texMax;
		backfaceZ[4] = texMin;
		backfaceX[5] = texMin;
		backfaceY[5] = texMax;
		backfaceZ[5] = texMin;
		backfaceX[6] = texMin;
		backfaceY[6] = texMax;
		backfaceZ[6] = texMax;
		backfaceX[7] = backfaceX[1];
		backfaceY[7] = backfaceY[1];
		backfaceZ[7] = backfaceZ[1];


		//glNewList(volTris, GL_COMPILE);
		
		
		// string s = floatToHex(64.33f);
		// float tempv = hexToFloat(s.c_str());
		// cout << "\n\n\nfloatToHex: " << s << "\n";
		// cout << "\n\n\nhexToFloat: " << tempv << "\n";
		
		

		for (j = 0; j < 2; j++) {
			
			bindShader("TCShader");
			
			if (j == 0) {
				bindFBO("frontFaceFBO");
			}
			else {
				coordsY[0] = fy2 * tiltAmount + fy1 * (1.0-tiltAmount);
				bindFBO("backFaceFBO");
			}
			
			
			
			glBegin(GL_TRIANGLE_FAN);
			glNormal3f(0, 0, 1);
			for (i = 0; i < 8; i++)
			{

				if (j == 0) { // front faces
					if (i == 0)
					{
						glMultiTexCoord3f( GL_TEXTURE0, 1.0f, 1.0f, 1.0f);
					}
					else
					{
						glMultiTexCoord3f( GL_TEXTURE0, backfaceX[i], backfaceY[i], backfaceZ[i]);
					}
				}
				else { // back faces
					glMultiTexCoord3f( GL_TEXTURE0, backfaceX[i], backfaceY[i], backfaceZ[i]);
				}
				

				glVertex3f(coordsX[i], coordsY[i], 0.0f);
			}
			glEnd();
			
			
			
			unbindFBO();
			unbindShader();
			
		}
		
		
		
		tempVec1.setFXYZ(
			cameraPos->getFX() - worldSizeInPixels.getFX() / 2.0f,
			cameraPos->getFY() - worldSizeInPixels.getFY() / 2.0f,
			0.0f
		);
		tempVec2.setFXYZ(
			cameraPos->getFX() + worldSizeInPixels.getFX() / 2.0f,
			cameraPos->getFY() + worldSizeInPixels.getFY() / 2.0f,
			worldSizeInPixels.getFZ()*1.0f // TODO: SHOULD BE NO MULTIPLER HERE
		);
		
		for (j = 0; j < 2; j++) {
			
			bindShader("TCShader2");
			
			if (j == 0) {
				bindFBO("backFaceMapFBO");
			}
			else {
				bindFBO("frontFaceMapFBO");
			}
			
			setShaderFloat("fHolderMod", fHolderMod);
			setShaderFloat("tiltAmount", tiltAmount);
			setShaderFloat("cameraZoom", cameraZoom);
			setShaderfVec2("bufferDim", &(bufferDim));
			setShaderfVec3("cameraPos", cameraPos);
			
			drawBox(&tempVec1,&tempVec2,j);

			unbindFBO();
			unbindShader();
			
		}
		
		

		


		//glEndList();
	}
void Singleton::createVTList ()
        {

		volTris = glGenLists(1);


		float texMin = 0.0f;
		float texMax = 1.0f;

		float fx1 = -1.0f;
		float fy2 = -1.0f;
		float fx2 = 1.0f;
		float fy1 = 1.0f;

		float centerX = (fx1 + fx2) / 2.0f;
		float centerY = (fy1 + fy2) / 2.0f;

		float fy25 = fy1 * 0.75f + fy2 * 0.25f;
		float fy75 = fy1 * 0.25f + fy2 * 0.75f;

		float coordsX[8];
		float coordsY[8];

		coordsX[0] = centerX;
		coordsY[0] = centerY;

		coordsX[1] = centerX;
		coordsY[1] = fy1;

		coordsX[2] = fx2;
		coordsY[2] = fy25;

		coordsX[3] = fx2;
		coordsY[3] = fy75;

		coordsX[4] = centerX;
		coordsY[4] = fy2;

		coordsX[5] = fx1;
		coordsY[5] = fy75;

		coordsX[6] = fx1;
		coordsY[6] = fy25;

		coordsX[7] = coordsX[1];
		coordsY[7] = coordsY[1];

		float backfaceX[8];
		float backfaceY[8];
		float backfaceZ[8];



		backfaceX[0] = texMin;
		backfaceY[0] = texMin;
		backfaceZ[0] = texMin;
		backfaceX[1] = texMin;
		backfaceY[1] = texMin;
		backfaceZ[1] = texMax;
		backfaceX[2] = texMax;
		backfaceY[2] = texMin;
		backfaceZ[2] = texMax;
		backfaceX[3] = texMax;
		backfaceY[3] = texMin;
		backfaceZ[3] = texMin;
		backfaceX[4] = texMax;
		backfaceY[4] = texMax;
		backfaceZ[4] = texMin;
		backfaceX[5] = texMin;
		backfaceY[5] = texMax;
		backfaceZ[5] = texMin;
		backfaceX[6] = texMin;
		backfaceY[6] = texMax;
		backfaceZ[6] = texMax;
		backfaceX[7] = backfaceX[1];
		backfaceY[7] = backfaceY[1];
		backfaceZ[7] = backfaceZ[1];


		glNewList(volTris, GL_COMPILE);

		glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0, 0, 1);

		int i;

		for (i = 0; i < 8; i++)
		{

			//glColor4f(backfaceX[i], backfaceY[i], backfaceZ[i], 1.0f);

			glMultiTexCoord3f( GL_TEXTURE0, backfaceX[i], backfaceY[i], backfaceZ[i]);

			if (i == 0)
			{
				//glColor4f((backfaceX[i]+1.0f)/2.0f, (backfaceY[i]+1.0f)/2.0f, (backfaceZ[i]+1.0f)/2.0f, 1.0f);
				glMultiTexCoord3f( GL_TEXTURE1, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				glMultiTexCoord3f( GL_TEXTURE1, backfaceX[i], backfaceY[i], backfaceZ[i]);
			}

			glVertex3f(coordsX[i], coordsY[i], 0.0f);
		}

		glEnd();


		glEndList();
	}
void Singleton::doShaderRefresh (bool doBake)
        {

		LAST_COMPILE_ERROR = false;

		readyToRecompile = 0;

		int i;
		int j;
		
		Shader* curShader;


		for (i = 0; i < shaderStrings.size(); i++) {
			shaderMap[ shaderStrings[i] ]->init( "../src/glsl/" + shaderStrings[i] + ".c", doBake);
		}
		shadersAreLoaded = 1;
		readyToRecompile = 1;
		
		if (LAST_COMPILE_ERROR) {
			
		}
		else {
			
			// load saved data (if exists)
			// merge saved data with existing data (if exists)
			// save merged data to saved data
			
			
			stringBuf = "{\n\t\"params\":[\n";
			
			
			
			for (i = 0; i < shaderStrings.size(); i++) {
				curShader = shaderMap[ shaderStrings[i] ];
				
				std::sort(curShader->paramVec.begin(), curShader->paramVec.end(), compareStruct);
				
				for (j = 0; j < curShader->paramVec.size(); j++) {
					stringBuf.append("\t\t{");
					stringBuf.append("\"shaderName\":\""+shaderStrings[i]+"\",");
					stringBuf.append("\"paramName\":\""+curShader->paramVec[j]+"\",");
					stringBuf.append("\"uid\":\"$shaderParams."+shaderStrings[i]+"."+curShader->paramVec[j]+"\"");
					stringBuf.append("},\n");
				}
			}
			
			stringBuf[stringBuf.size()-2] = ' ';
			
			
			stringBuf.append("\t]\n}\n\n");
			
			// this should automatically clear the key
			// and deallocate existing entries
			//internalJSON.insertValue("shaderParams", JSON::Parse(stringBuf.c_str()));
			
			processJSONFromString(
				&stringBuf,
				&(internalJSON["shaderParams"].jv)
			);
			
			// cout << "stringBuf:\n\n";
			// cout << stringBuf;
			
			
		}
		

	}
void Singleton::setMatrices (int w, int h)
        {

		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity ();
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();

	}
void Singleton::setWH (int w, int h)
        {

		baseW = w;
		baseH = h;
	}
void Singleton::sampleFBODirect (FBOSet * fbos, int offset)
        {
		int i;
		if (shadersAreLoaded)
		{
			for (i = 0; i < fbos->numBufs; i++)
			{
				setShaderTexture(i + offset, fbos->fbos[i].color_tex);
			}
		}
	}
void Singleton::unsampleFBODirect (FBOSet * fbos, int offset)
        {
		int i;
		if (shadersAreLoaded)
		{
			for (i = fbos->numBufs - 1; i >= 0; i--)
			{
				setShaderTexture(i + offset, 0);
			}
		}
	}
void Singleton::bindFBODirect (FBOSet * fbos, int doClear)
        {
		setMatrices(fbos->width, fbos->height);
		fbos->bind(doClear);
		currentFBOResolutionX = fbos->width;
		currentFBOResolutionY = fbos->height;
	}
void Singleton::sampleFBO (string fboName, int offset, int swapFlag)
        {
		FBOSet *fbos;

		if (swapFlag == -1)
		{
			fbos = &(fboMap[fboName]);
		}
		else
		{

			if (swapFlag == 0)
			{
				fbos = &(fboMap[fboName + "0"]);
			}
			else
			{
				fbos = &(fboMap[fboName + "1"]);
			}

		}

		if (fbos)
		{
			sampleFBODirect(fbos, offset);
		}
		else
		{
			doTrace("sampleFBO: Invalid FBO Name");
		}


	}
void Singleton::unsampleFBO (string fboName, int offset, int swapFlag)
        {

		FBOSet *fbos;

		if (swapFlag == -1)
		{
			fbos = &(fboMap[fboName]);
		}
		else
		{

			if (swapFlag == 0)
			{
				fbos = &(fboMap[fboName + "0"]);
			}
			else
			{
				fbos = &(fboMap[fboName + "1"]);
			}

		}

		if (fbos)
		{
			unsampleFBODirect(fbos, offset);
		}
		else
		{
			doTrace("unsampleFBO: Invalid FBO Name");
		}

	}
FBOSet * Singleton::getFBOSet (string fboName)
        {
		return &(fboMap[fboName]);
	}
FBOWrapper * Singleton::getFBOWrapper (string fboName, int offset)
        {
		FBOSet *fbos = &(fboMap[fboName]);
		return fbos->getFBOWrapper(offset);
	}
void Singleton::copyFBO (string src, string dest, int num)
        {
		bindShader("CopyShader");
		bindFBO(dest);
		//sampleFBO(src, 0);
		setShaderTexture(0, getFBOWrapper(src,num)->color_tex);
		drawFSQuad(1.0f);
		unsampleFBO(src, 0);
		unbindFBO();
		unbindShader();
	}
void Singleton::copyFBO2 (string src, string dest)
        {
		bindShader("CopyShader2");
		bindFBO(dest);
		sampleFBO(src, 0);
		drawFSQuad(1.0f);
		unsampleFBO(src, 0);
		unbindFBO();
		unbindShader();
	}
void Singleton::bindFBO (string fboName, int swapFlag)
        {

		FBOSet *fbos;

		if (swapFlag == -1)
		{
			fbos = &(fboMap[fboName]);
		}
		else
		{

			if (swapFlag == 0)
			{
				fbos = &(fboMap[fboName + "1"]);
			}
			else
			{
				fbos = &(fboMap[fboName + "0"]);
			}

		}

		if (fbos)
		{
			bindFBODirect(fbos);
		}
		else
		{
			doTrace("bindFBO: Invalid FBO Name");
		}


	}
void Singleton::unbindFBO ()
        {
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		setMatrices(baseW, baseH);

	}
void Singleton::bindShader (string shaderName)
        {
		
		int i;
		int totSize;

		if (shadersAreLoaded)
		{
			curShader = shaderName;
			curShaderPtr = shaderMap[curShader];
			curShaderPtr->bind();
			
			totSize = curShaderPtr->paramVec.size();
			
			if (bakeParamsOn) {
				
			}
			else {
				for (i = 0; i < totSize; i++) {
					setShaderFloat(
						curShaderPtr->paramVec[i],
						curShaderPtr->paramMap[curShaderPtr->paramVec[i]]
					);
				}
			}
			
		}

	}
void Singleton::unbindShader ()
        {
		if (shadersAreLoaded)
		{
			curShaderPtr->unbind();
		}
	}
void Singleton::setShaderArrayfVec3 (string paramName, float * x, int count)
        {
		curShaderPtr->setShaderArrayfVec3(paramName, x, count);
	}
void Singleton::setShaderArrayfVec4 (string paramName, float * x, int count)
        {
		curShaderPtr->setShaderArrayfVec4(paramName, x, count);
	}
void Singleton::setShaderArray (string paramName, float * x, int count)
        {
		curShaderPtr->setShaderArray(paramName, x, count);
	}
void Singleton::setShaderFloat (string paramName, float x)
        {
		curShaderPtr->setShaderFloat(paramName, x);
	}
void Singleton::setShaderInt (string paramName, int x)
        {
		curShaderPtr->setShaderInt(paramName, x);
	}
void Singleton::setShaderfVec2 (string paramName, FIVector4 * v)
        {
		curShaderPtr->setShaderfVec2(paramName, v);
	}
void Singleton::setShaderVec2 (string paramName, float x, float y)
        {
		curShaderPtr->setShaderVec2(paramName, x, y);
	}
void Singleton::setShaderVec3 (string paramName, float x, float y, float z)
        {
		curShaderPtr->setShaderVec3(paramName, x, y, z);
	}
void Singleton::setShaderfVec3 (string paramName, FIVector4 * v)
        {
		curShaderPtr->setShaderfVec3(paramName, v);
	}
void Singleton::setShaderVec4 (string paramName, float x, float y, float z, float w)
        {
		curShaderPtr->setShaderVec4(paramName, x, y, z, w);
	}
void Singleton::setShaderfVec4 (string paramName, FIVector4 * v)
        {
		curShaderPtr->setShaderfVec4(paramName, v);
	}
void Singleton::setShaderFloatUB (string paramName, float x)
        {
		curShaderPtr->setShaderFloatUB(paramName, x);
	}
void Singleton::setShaderfVec4UB (string paramName, FIVector4 * v)
        {
		curShaderPtr->setShaderfVec4UB(paramName, v);
	}
void Singleton::updateUniformBlock (int ubIndex, int ubDataSize)
        {
		curShaderPtr->updateUniformBlock(ubIndex, ubDataSize);
	}
void Singleton::invalidateUniformBlock (int ubIndex)
        {
		curShaderPtr->invalidateUniformBlock(ubIndex);
	}
void Singleton::beginUniformBlock (int ubIndex)
        {
		curShaderPtr->beginUniformBlock(ubIndex);
	}
bool Singleton::wasUpdatedUniformBlock (int ubIndex)
        {

		return curShaderPtr->wasUpdatedUniformBlock(ubIndex);

	}
void Singleton::setShaderTexture (int multitexNumber, uint texId)
        {
		if (shadersAreLoaded)
		{
			glActiveTexture(GL_TEXTURE0 + multitexNumber);
			glBindTexture(GL_TEXTURE_2D, texId);
			curShaderPtr->setShaderInt(shaderTextureIds[multitexNumber] , multitexNumber);
		}
	}
void Singleton::setShaderTexture3D (int multitexNumber, uint texId)
        {
		if (shadersAreLoaded)
		{
			glActiveTexture(GL_TEXTURE0 + multitexNumber);
			glBindTexture(GL_TEXTURE_3D, texId);
			curShaderPtr->setShaderInt(shaderTextureIds[multitexNumber], multitexNumber);
		}
	}
bool Singleton::shiftDown ()
        {
		return (bool)(glutGetModifiers()&GLUT_ACTIVE_SHIFT);
	}
bool Singleton::ctrlDown ()
        {
		return (bool)(glutGetModifiers()&GLUT_ACTIVE_CTRL);
	}
bool Singleton::altDown ()
        {
		return (bool)(glutGetModifiers()&GLUT_ACTIVE_ALT);
	}
void Singleton::drawQuadBounds (float fx1, float fy1, float fx2, float fy2, float fz)
        {
		glColor4f(1, 1, 1, 1);
		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(fx1, fy1, fz);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(fx2, fy1, fz);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(fx2, fy2, fz);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(fx1, fy2, fz);

		glEnd();
	}
void Singleton::drawFSQuad (float zoom)
        {
		drawFSQuadOffset(0.0f, 0.0f, zoom);
	}
void Singleton::drawFSQuadOffset (float xOff, float yOff, float zoom)
        {
		float fx1 = (xOff - 1.0f) * zoom;
		float fy1 = (yOff - 1.0f) * zoom;
		float fx2 = (xOff + 1.0f) * zoom;
		float fy2 = (yOff + 1.0f) * zoom;

		glColor4f(1, 1, 1, 1);
		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(fx1, fy1, 0.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(fx2, fy1, 0.0f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(fx2, fy2, 0.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(fx1, fy2, 0.0f);

		glEnd();
	}
void Singleton::drawFBO (string fboName, int ind, float zoom, int swapFlag)
        {
		if (swapFlag == -1)
		{
			drawFBOOffset(fboName, ind, 0.0f, 0.0f, zoom);
		}
		else
		{
			if (swapFlag == 0)
			{
				drawFBOOffset(fboName + "1", ind, 0.0f, 0.0f, zoom);
			}
			else
			{
				drawFBOOffset(fboName + "0", ind, 0.0f, 0.0f, zoom);
			}

		}
	}
void Singleton::drawFBOOffsetDirect (FBOSet * fbos, int ind, float xOff, float yOff, float zoom)
        {

		glBindTexture(GL_TEXTURE_2D, fbos->fbos[ind].color_tex);
		//glClearColor(0.2,0.2,0.2,0.0);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		drawFSQuadOffset(xOff, yOff, zoom);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
void Singleton::drawFBOOffset (string fboName, int ind, float xOff, float yOff, float zoom)
        {
		FBOSet *fbos = &(fboMap[fboName]);

		if (fbos)
		{
			drawFBOOffsetDirect(fbos, ind, xOff, yOff, zoom);
		}
		else
		{
			doTrace("drawFBOOffsetDirect: Invalid FBO Name");
		}

	}
float Singleton::getTerHeightScaled (float val)
        {
		return mixf(0.125f,0.875f,val)*worldSizeInPixels.getFZ();
		
	}
float Singleton::getSLNormalized ()
        {
		return (((float)gw->seaLevel) / 255.0f);
	}
float Singleton::getSLInPixels ()
        {
		return getSLNormalized()*worldSizeInPixels.getFZ() + 2.5f*pixelsPerMeter;
	}
float Singleton::getHeightAtPixelPos (float x, float y, bool dd)
        {
		FBOWrapper *fbow;
		float xc;
		float yc;

		int channel = 0;

		float testHeight;
		
		float v0;
		float v1;
		float v2;
		float v3;
		
		if (mapInvalid)
		{

			cout << "mapInvalid\n";
			return 0.0f;

		}
		else
		{
			FBOWrapper *fbow = getFBOWrapper("hmFBO", 0);

			xc = (x / worldSizeInPixels.getFX()) * ((float)fbow->width);
			yc = (y / worldSizeInPixels.getFY()) * ((float)fbow->height);

			v0 = fbow->getPixelAtLinear((xc * mapFreqs.getFX()), (yc * mapFreqs.getFX()), channel);
			v1 = fbow->getPixelAtLinear((xc * mapFreqs.getFY()), (yc * mapFreqs.getFY()), channel);
			v2 = fbow->getPixelAtLinear((xc * mapFreqs.getFZ()), (yc * mapFreqs.getFZ()), channel);
			v3 = fbow->getPixelAtLinear((xc * mapFreqs.getFW()), (yc * mapFreqs.getFW()), channel);


			if (dd) {
				//cout << "hmvals: " << v0 << ", " << v1 << ", " << v2 << ", " << v3 << "\n";
			}
			

			testHeight = 
				  v0 * mapAmps.getFX()
				+ v1 * mapAmps.getFY()
				+ v2 * mapAmps.getFZ()
				+ v3 * mapAmps.getFW()
				
				- v1 * mapAmps.getFY()*0.5f
				- v2 * mapAmps.getFZ()*0.5f
				- v3 * mapAmps.getFW()*0.5f
				
			;
			
			if (dd) {
				//cout << "testHeight " << testHeight << "\n";
			}

			testHeight = clampf(testHeight,0.0f,1.0f);

			return getTerHeightScaled(testHeight);



		}



	}
void Singleton::syncObjects (FIVector4 * bp)
                                        {
		int i;
		
		for (i = 1; i < E_OBJ_LENGTH; i++)
		{

			if (dynObjects[i]->isRelative)
			{
				dynObjects[i]->pos.copyFrom(bp);
				dynObjects[i]->pos.addXYZRef( &(dynObjects[i]->posRel) );
			}

		}
	}
void Singleton::moveCamera (FIVector4 * pModXYZ)
        {
		
		int i;
		FIVector4 *cameraPos = &(dynObjects[E_OBJ_CAMERA]->pos);
		
		gw->curLoadRadius = minWInPages;
		
		// cout << "curHeight: " <<
		// 	getHeightAtPixelPos(cameraPos->getFX(), cameraPos->getFY(), true)/worldSizeInPixels.getFZ() << "\n";
		
		
		wsBufferInvalid = true;

		cameraPos->addXYZRef(pModXYZ);


		pModXYZ->setFZ(0.0f);

		if (cameraPos->getFX() > worldSizeInPixels.getFX() / 2.0)
		{
			cameraPos->setFX( cameraPos->getFX() - worldSizeInPixels.getFX() );
		}
		if (cameraPos->getFX() < -worldSizeInPixels.getFX() / 2.0)
		{
			cameraPos->setFX( cameraPos->getFX() + worldSizeInPixels.getFX() );
		}
		if (cameraPos->getFY() > worldSizeInPixels.getFY() / 2.0)
		{
			cameraPos->setFY( cameraPos->getFY() - worldSizeInPixels.getFY() );
		}
		if (cameraPos->getFY() < -worldSizeInPixels.getFY() / 2.0)
		{
			cameraPos->setFY( cameraPos->getFY() + worldSizeInPixels.getFY() );
		}



		syncObjects(cameraPos);

		isPanning = true;
	}
GameEntNode * Singleton::getMirroredNode (GameEntNode * curNode)
                                                           {
		if ((curNode->nodeName < E_BONE_C_BEG)&&mirrorOn) {
			if (curNode->nodeName <= E_BONE_L_END) {
				return testHuman->baseNode->getNode(
					curNode->nodeName+(E_BONE_R_BEG-E_BONE_L_BEG)
				);
			}
			else {
				return testHuman->baseNode->getNode(
					curNode->nodeName-(E_BONE_R_BEG-E_BONE_L_BEG)
				);
			}
		}
		else {
			return NULL;
		}
		
	}
void Singleton::applyNodeChanges (GameEntNode * _curNode, float dx, float dy)
                                                                         {
		
		GameEntNode* curNode = _curNode;
		
		int i;
		int j;
		int k;
		
		float xm = 0.0f;
		float ym = 0.0f;
		float zm = 0.0f;
		
		float dirMod = 1.0f;
		
		if (
			(curNode->nodeName < E_BONE_C_BEG) &&
			(mirrorOn)
		) {
			j = 2;
		}
		else {
			j = 1;
		}
		
		for (i = 0; i < j; i++) {
			
			
			if (i == 1) {
				curNode = getMirroredNode(curNode);
				
				dirMod = -1.0f;
			}
			
			
			if (abDown) {
				makeDirty();
			}
			
			xm = dx/50.0f;
			ym = dy/50.0f;
			
			if (shiftDown()) { // || altDown()
								
				if (lbDown) {
					curNode->tbnRadScale0.addXYZ(0.0f,xm,ym);
				}
				if (rbDown) {
					curNode->tbnRadScale1.addXYZ(0.0f,xm,ym);
				}
				if (mbDown) {
					curNode->boneLengthScale += ym;
				}
			}
			else {
				
				if (lbDown) {
					curNode->rotThe += dirMod*ym;
				}
				if (rbDown) {
					curNode->rotRho += dirMod*ym;
				}
				if (mbDown) {
					curNode->rotPhi += dirMod*ym;
				}
				
				
			}
			
			if (applyToChildren) {
				for (k = 0; k < curNode->children.size(); k++) {
					applyNodeChanges(curNode->children[k], dx, dy);
				}
			}
			
			
		}
			
		
	}
void Singleton::moveObject (float dx, float dy, float zoom)
        {

		int i;
		int j;
		
		
		
		GameEntNode* curNode;

		float tilt = tiltAmount;
		float itilt = (1.0-tiltAmount);

		modXYZ.setFXYZ(0.0f,0.0f,0.0f);

		float dxZoom = dx * fHolderMod / zoom;
		float dyZoom = dy * fHolderMod / zoom;

		

		//float grassWidth;
		//float grassHeight;

		bool doDefault = false;
		
		
		
		
		float tileWidth = 1.0;
		float tileHeight = itilt;

		



		if (abDown)
		{
			// if (rbDown || (shiftDown() ) )
			// {
			// 	modXYZ.setFZ(  dyZoom );
			// 	modXYZ.setFX( -(0.0f + dxZoom / 2.0f) );
			// 	modXYZ.setFY( -(0.0f - dxZoom / 2.0f) );

			// }
			// else
			// {
			// 	modXYZ.setFX( -(dyZoom + dxZoom / 2.0f) );
			// 	modXYZ.setFY( -(dyZoom - dxZoom / 2.0f) );
			// }
			
			
			// screen to world
			
			if (rbDown || (shiftDown() ) )
			{
				modXYZ.setFZ(  dyZoom*1.0/tilt );
				modXYZ.setFX( -(0.0f + dxZoom) );
				modXYZ.setFY( -(0.0f - dxZoom) );

			}
			else
			{
				
				//iX = (((ScreenX) / tileWidth) - ((ScreenY) / tileHeight));
				//iY = (((ScreenX) / tileWidth) + ((ScreenY) / tileHeight));
				
				
				modXYZ.setFX( -(dyZoom*1.0/itilt + 1.0*dxZoom) );
				modXYZ.setFY( -(dyZoom*1.0/itilt - 1.0*dxZoom) );
				
			}
			

			lastModXYZ.addXYZRef(&modXYZ);




		}
		
		
		if (
			(entOn) && 
			(activeNode != NULL)
		) {
				
			applyNodeChanges(activeNode, dx, dy);
			
		}
		else {
			if (shiftDown())
			{
				
				
				if ((mouseState == E_MOUSE_STATE_BRUSH)&&lbDown)
				{
					curBrushRad -= modXYZ.getFZ() / 50.0f;

					if (curBrushRad < 0.0f)
					{
						curBrushRad = 0.0f;
					}
				}
				else
				{
					
					if (rbDown) {
						tiltAmount -=  modXYZ.getFZ()*zoom / 500.0f;
						
						tiltAmount = clampf(tiltAmount, 0.125f, 0.75f);
						
						tiltChanged = true;
						changesMade = true;
					}
					
				}

			}
			else
			{
				if (mouseState == E_MOUSE_STATE_BRUSH)
				{
					doDefault = true;
				}
				else
				{

					if (activeObject == E_OBJ_CAMERA)
					{
						doDefault = true;
					}
					else
					{
						dynObjects[activeObject]->posRel.addXYZRef(&modXYZ, -1.0f);
						dynObjects[activeObject]->pos.addXYZRef(&modXYZ, -1.0f);
					}
				}

				if (doDefault)
				{
					moveCamera(&modXYZ);
				}
				


			}
		}
		


		






	}
void Singleton::updateMultiLights ()
        {
		if (multiLights)
		{
			numDynLights = E_OBJ_LENGTH - E_OBJ_LIGHT0;
		}
		else
		{
			numDynLights = 1;
		}
	}
void Singleton::toggleFullScreen ()
        {
		isFullScreen = !isFullScreen;
		if (isFullScreen)
		{
			glutFullScreen();
		}
		else
		{
			glutPositionWindow(250, 50);
		}
	}
void Singleton::restartGen (bool instantRefresh, bool clearEverything)
                                                                   {
		
		
	
		gw->curLoadRadius = minWInPages;
		gw->actionOnHolders(E_HOLDER_ACTION_RESET, instantRefresh, clearEverything);
		bufferInvalid = true;
		changesMade = true;
		
		
	}
void Singleton::setObjToElevationBase (FIVector4 * obj)
                                                   {
		
		obj->setFZ(
			getHeightAtPixelPos(obj->getFX(), obj->getFY())
		);

	}
void Singleton::setCameraToElevationBase ()
                                        {
		FIVector4 *cameraPos = &(dynObjects[E_OBJ_CAMERA]->pos);

		setObjToElevationBase(cameraPos);
	}
void Singleton::setCameraToElevation ()
        {
		setCameraToElevationBase();
		
		bufferInvalid = true;
		changesMade = true;
		wsBufferInvalid = true;
	}
void Singleton::processSpecialKeys (int key, int _x, int _y)
        {

		int x = _x / scaleFactor;
		int y = _y / scaleFactor;

		switch (key)
		{
		case GLUT_KEY_F1 :

			break;
		case GLUT_KEY_F2 :

			break;
		case GLUT_KEY_F3 :

			break;
		}
	}
void Singleton::updateCS ()
                        {
		if (
			(bCtrl != bCtrlOld) ||
			(bShift != bShiftOld)
		) {
			forceGetPD = true;
			wsBufferInvalid = true;
			bufferInvalid = true;
			changesMade = true;
		}
		bCtrlOld = bCtrl;
		bShiftOld = bShift;
	}
void Singleton::processKey (unsigned char key, int _x, int _y, bool isPressed)
        {

		int x = _x / scaleFactor;
		int y = _y / scaleFactor;
	}
void Singleton::keyboardUp (unsigned char key, int _x, int _y)
        {

		GameEntNode* curNode;
		
		int x = _x / scaleFactor;
		int y = _y / scaleFactor;

		int holderCount;

		changesMade = false;

		
		bShift = shiftDown();
		bCtrl = ctrlDown();
		updateCS();


		if (key == 17) {
			glutDestroyWindow(glutGetWindow());
		}

		switch (key) {

		case 's':
				isMacro = !isMacro;
				
				//mirrorOn = !mirrorOn;
				cout << "isMacro: " << isMacro << "\n";
			break;


		// case '9':
		// 	saveAllData();
		// 	cout << "data saved\n";
		// break;
		
		case 19: //ctrl-s
			saveGUIValues();
			//cout << "Use s key in web editor to save\n";
			break;

		case 15: //ctrl-o
			//loadAllData();
			loadGUIValues();

			break;

		case '[':
			iNumSteps /= 2;
			if (iNumSteps < 16)
			{
				iNumSteps = 16;
			}
			doTraceND("iNumSteps: ", i__s(iNumSteps));
			bufferInvalid = true;
			break;
		case ']':
			iNumSteps *= 2;
			if (iNumSteps > 256)
			{
				iNumSteps = 256;
			}
			doTraceND("iNumSteps: ", i__s(iNumSteps));
			bufferInvalid = true;
			break;


		case 'e':
			setCameraToElevation();
			break;
			
		case 'q':
			// charState++;
			// if (charState > E_CHAR_STATE_RENDERED) {
			// 	charState = 0;
			// }
		
			autoScroll = !autoScroll;
			
			if (autoScroll) {
				scrollTimer.start();
				baseScrollPos.copyFrom(&(dynObjects[E_OBJ_CAMERA]->pos));
			}
			
			
			break;

		case 'w':
			resetActiveNode();
		break;
		case 'W':
			changesMade = true;
			maxWInPages++;
			break;
		case 'Q':
			changesMade = true;
			maxWInPages--;
			if (maxWInPages < 1)
			{
				maxWInPages = 1;
			}
			break;

		case 27: // esc
			std::exit(0);
			break;

		case 'b':
		
			bakeParamsOn = !bakeParamsOn;
			cout << "bakeParamsOn: " << bakeParamsOn << "\n";
			doShaderRefresh(bakeParamsOn);
			
			
			
		
			//radiosityOn = !radiosityOn;
			break;


		case 'R':
		
			//loadGUIValues(false);
			doShaderRefresh(bakeParamsOn);
			loadGUI();
			loadGUIValues();
			bufferInvalid = true;
		break;
		case 'r':
			doShaderRefresh(bakeParamsOn);
			
			bufferInvalid = true;

			cout << "Shaders Refreshed\n";
			
			break;
			
		case 'j':
			doShaderRefresh(bakeParamsOn);
			bufferInvalid = true;			
			mapInvalid = true;
			gw->initMap();
		break;

		case 'G':
			gridOn = 1.0 - gridOn;
			cout << "Grid On: " << gridOn << "\n";
			bufferInvalid = true;
			changesMade = true;
			break;


		case 'g':
		
			mouseState++;

			if (mouseState == E_MOUSE_STATE_LENGTH)
			{
				mouseState = 0;
			}
			
			cout << mouseStateStrings[mouseState] << "\n";

			bufferInvalid = true;
			changesMade = true;
			wsBufferInvalid = true;
			forceGetPD = true;
		
			
		break;
		
		case 'l':

			multiLights = !multiLights;
			updateMultiLights();


			bufferInvalid = true;
			changesMade = true;
			forceGetPD = true;

			break;


		case 'p':
			//cout << "curZoom " << cameraZoom << "\n";
			toggleFullScreen();
			break;

		case 'd':
			targetTimeOfDay = 1.0f-targetTimeOfDay;
			// targetTimeOfDay += 0.5;
			
			// if (targetTimeOfDay > 1.0) {
			// 	targetTimeOfDay = 0.0;
			// }
			
			break;

		case 'h':
			waterOn = !waterOn;

			if (MAX_LAYERS == 1)
			{
				waterOn = false;
			}


			bufferInvalid = true;
			changesMade = true;

			cout << "waterOn " << waterOn << "\n";
			break;

		case 't':

			// tiltAmount += 0.25f;
			
			// if (tiltAmount > 0.75f) {
			// 	tiltAmount = 0.25f;
			// }
			
			// createVTListTilt();
			
			// cout << "tiltAmount: " << tiltAmount << "\n";
			
			// restartGen(false, true);


			testOn = !testOn;

			//testOn = !testOn;
			//cout << "testOn " << testOn << "\n";

			//treesOn = !treesOn;
			//traceOn = true;
			break;
		case 'o':
			rotOn = !rotOn;
			break;

		case '\t':
		
			if (guiOn) {
				playSoundEvent("hideGUI");
			}
		
			if (!guiOn) {
				
				// todo: in the future don't reload the gui every time
				// just for testing right now
				// if (mainGUI->isLoaded) {
				// 
				// }
				// else {
				// 	loadGUI()
				// }
				
			}
			guiOn = !guiOn;
			
			if (guiOn) {
				playSoundEvent("showGUI");
			}
			
			bufferInvalid = true;
			break;

		case ' ':
			selGeomListInd++;
			if (selGeomListInd >= selGeomList.size()) {
				selGeomListInd = 0;
			}
			if (selGeomList.size() > 0) {
				selectedGeom = selGeomList[selGeomListInd];
			}
			
		break;

		case 'c':
			doShaderRefresh(bakeParamsOn);
			restartGen(false, true);
			break;
		

		case 'f':
			fogOn = 1.0 - fogOn;
			bufferInvalid = true;
			changesMade = true;
			cout << "fog on " << fogOn << "\n";
			break;

		case 'm':

			tiltAmount = 0.5f;
			targetZoom = 1.0f; 
			runReport();
			

			break;

		
		case 'A':
			changesMade = true;
			maxHInPages++;
			break;
		case 'Z':
			changesMade = true;
			maxHInPages--;
			if (maxHInPages < 1)
			{
				maxHInPages = 1;
			}
			break;

		case 'a':
			// selectedNode->material += 1.0f;
			// curNode = getMirroredNode(selectedNode);
			// if (curNode != NULL) {
			// 	curNode->material += 1.0f;
			// }
			// makeDirty();
		break;
		case 'z':
			// selectedNode->material -= 1.0f;
			// curNode = getMirroredNode(selectedNode);
			// if (curNode != NULL) {
			// 	curNode->material -= 1.0f;
			// }
			// makeDirty();
			
		break;

		case 'v':
			if (selectedGeom == NULL)
			{

			}
			else
			{
				selectedGeom->visible = !(selectedGeom->visible);

				holderCount = gw->getHoldersInGeom(selectedGeom);
				gw->refreshHoldersInList(true, true); //holderCount <= 12
				gw->holdersToRefresh.clear();

				bufferInvalid = true;
				changesMade = true;



			}
			break;



		default:

			break;
		}


	}
void Singleton::keyboardDown (unsigned char key, int _x, int _y)
        {
		
		
		bShift = shiftDown();
		bCtrl = ctrlDown();
		updateCS();

		int x = _x / scaleFactor;
		int y = _y / scaleFactor;
	}
void Singleton::runReport ()
                         {
		
		mainGUI->runReport();
		cout << "zoom " << cameraZoom << "\n";
		cout << "lightCount: " << gw->lightCount << "\n";
		cout << "TOT GPU MEM USED (MB): " << TOT_GPU_MEM_USAGE << "\n";
		cout << "HolderSize (MB): " << holderSizeMB << "\n";
		cout << "Num GPU Holders: " << gpuPool->holderPoolItems.size() << "\n";
		cout << "GPU Pooled MB Used: " << ((float)gpuPool->holderPoolItems.size())*holderSizeMB << "\n";
	}
void Singleton::getPixData (FIVector4 * toVector, int _xv, int _yv, int bufNum, bool forceGet)
        {

		FBOWrapper *fbow;
		int newX;
		int newY;
		
		float xv = _xv;
		float yv = _yv;


		if (wsBufferInvalid || forceGet)
		{
			gw->getWorldSpaceBuffer(bufNum);
		}

		
		//xv = (xv - bufferDimHalf.getFX());
		//yv = (yv - bufferDimHalf.getFY());

		if (cameraZoom > 1.0)
		{
			newX = bufferDimHalf.getFX() + (xv - bufferDimHalf.getFX())/cameraZoom;
			newY = bufferDimHalf.getFY() + (yv - bufferDimHalf.getFY())/cameraZoom;
		}
		else
		{
			newX = clamp(xv, 0, bufferDim.getIX() - 1);
			newY = clamp(yv, 0, bufferDim.getIY() - 1);
		}



		fbow = getFBOWrapper("worldSpaceFBO", bufNum);
		fbow->getPixelAtF(toVector, newX, (bufferDim.getIY() - 1) - newY);
	}
GameGeom * Singleton::findNearestGeom (FIVector4 * testPoint, bool createList, bool onlyInteractive)
        {
		GameBlock *curBlock;

		int i;
		int j;
		int k;
		int ii;
		int jj;
		
		int curInd = 0;
		float bestDis;
		float curDis;
		
		bool doProc = false;
		
		if (createList) {
			selGeomList.clear();
			selGeomListInd = 0;
		}

		bestDis = 99999.0f;
		GameGeom *resGeom = NULL;

		for (j = -1; j <= 1; j++)
		{
			for (i = -1; i <= 1; i++)
			{
				ii = i + gw->camBlockPos.getIX();
				jj = j + gw->camBlockPos.getIY();

				curBlock = gw->getBlockAtCoords(ii, jj, false);

				if (curBlock == NULL)
				{

				}
				else
				{
					for (k = 0; k < curBlock->gameGeom.size(); k++)
					{
						if (
							testPoint->inBoundsXYZSlack(
								curBlock->gameGeom[k]->getVisMinInPixelsT(),
								curBlock->gameGeom[k]->getVisMaxInPixelsT(),
								0.0625*pixelsPerMeter
							)
						)
						{
							
							if (createList) {
								selGeomList.push_back(curBlock->gameGeom[k]);
								curInd++;
							}
							
							curDis = 
							abs(curBlock->gameGeom[k]->getVisMaxInPixelsT()->getFX()-testPoint->getFX()) +
							abs(curBlock->gameGeom[k]->getVisMaxInPixelsT()->getFY()-testPoint->getFY()) +
							abs(curBlock->gameGeom[k]->getVisMaxInPixelsT()->getFZ()-testPoint->getFZ());
							
							//curBlock->gameGeom[k]->getVisMinInPixelsT()->distance(testPoint) +
							//curBlock->gameGeom[k]->getVisMaxInPixelsT()->distance(testPoint);

							if (curBlock->gameGeom[k]->visible) {
								
							}
							else {
								curDis *= 16.0f;
							}

							if (onlyInteractive) {
								doProc = isInteractiveGeom[curBlock->gameGeom[k]->buildingType];
							}
							else {
								doProc = true;
							}

							if (
								(curDis < bestDis) &&
								doProc
							)
							{
								bestDis = curDis;
								resGeom = curBlock->gameGeom[k];
								selGeomListInd = curInd-1;
							}

						}
					}
				}
			}
		}

		return resGeom;
	}
void Singleton::mouseMove (int _x, int _y)
        {

		mouseMoved = true;

		int x = _x / scaleFactor;
		int y = _y / scaleFactor;

		int dx = x - lastPosX;
		int dy = y - lastPosY;

		guiX = _x/UI_SCALE_FACTOR;
		guiY = _y/UI_SCALE_FACTOR;

		bShift = shiftDown();
		bCtrl = ctrlDown();
		updateCS();

		lastMouseX = x;
		lastMouseY = y;

		
		

		mouseXUp = x;
		mouseYUp = y;

		

		
		if (tiltChanged) {
			tiltChanged = false;
			createVTListTilt();
			readyForRestart = true;
			//restartGen(false, false);
		}

		if (abDown)
		{
			moveObject((float)dx, (float)dy, cameraZoom);
		}
		else
		{

			getPixData(&mouseMovePD, x, y);


			

			// if (
			// 	mouseState != E_MOUSE_STATE_MOVE
			// )	{

				gw->modifyUnit(&mouseMovePD, E_BRUSH_MOVE);
			//}
			
			


			//////////////

			if (entOn) {
				updateNearestEntNode(false, &mouseMovePD);
			}
			else {
				activeNode = NULL;
				setSelNode(NULL);
			}
			

			highlightedGeom = findNearestGeom(&mouseMovePD);
			


			//////////////


		}

		lastPosX = x;
		lastPosY = y;

		if ( (x >= 0) && (y >= 0) && (x < baseW) && (y < baseH) )
		{
			bufferInvalid = true;

			if (abDown)
			{
				changesMade = true;
			}
		}
	}
void Singleton::makeDirty ()
                         {
		testHuman->gph->childrenDirty = true;
	}
void Singleton::setSelNode (GameEntNode * newNode)
                                              {
		
		selectedNode = newNode;
		if (selectedNode != lastSelNode) {
			makeDirty();
		}
		lastSelNode = newNode;
		
	}
void Singleton::worldToScreenBase (FIVector4 * sc, FIVector4 * wc, bool doDiv)
                                                                                 {
		/*
		Screen -> Isometric space equations
		iX = (((ScreenX) / tileWidth) - ((ScreenY) / tileHeight));
		iY = (((ScreenX) / tileWidth) + ((ScreenY) / tileHeight));

		Isometric -> Screen space equations
		ScreenX = (iX + iY) * tileWidth / 2;
		ScreenY = (iY - iX) * tileHeight / 2;

		Assuming the isometric coordinating system goes as this: http://i.imgur.com/aUM4g.png

		*/
		
		float tilt = tiltAmount;
		float itilt = 1.0-tiltAmount;
		
		// float x1 = (wc->getFX() - wc->getFY())/2.0;
		// float y1 = (-wc->getFX() + -wc->getFY() + wc->getFZ());
		
				
		float x1 = (wc->getFX() - wc->getFY());
		//float y1 = (-(wc->getFX() / 2.0f) + -(wc->getFY() / 2.0f) + wc->getFZ());
		float y1 = (-itilt*wc->getFX() + -itilt*wc->getFY() + (tilt)*2.0f*wc->getFZ());
		
		if (doDiv) {
			x1 /= fHolderMod;
			y1 /= fHolderMod;
		}
		
		
		sc->setFX(x1);
		sc->setFY(y1);
	}
void Singleton::worldToScreen (FIVector4 * sc, FIVector4 * wc, bool centerIsOrigin)
        {
		
		FIVector4 *cameraPos = &(dynObjects[E_OBJ_CAMERA]->pos);
		dMod.copyFrom(wc);
		dMod.addXYZRef(cameraPos, -1.0);
		
		worldToScreenBase(sc, &dMod, false);
		float x1 = sc->getFX();
		float y1 = sc->getFY();
		
		
		float myZoom = std::min(1.0f, cameraZoom);
		x1 = x1 * (myZoom) / bufferModDim.getFX();
		y1 = y1 * (myZoom) / bufferModDim.getFY();

		if (centerIsOrigin)
		{

		}
		else
		{
			x1 = (x1 + 1.0) / 2.0;
			y1 = (y1 + 1.0) / 2.0;
		}
		
		


		sc->setFX(x1);
		sc->setFY(y1);
	}
void Singleton::mouseClick (int button, int state, int _x, int _y)
        {


		FIVector4 *cameraPos = &(dynObjects[E_OBJ_CAMERA]->pos);

		int x = _x / scaleFactor;
		int y = _y / scaleFactor;

		lastPosX = x;
		lastPosY = y;
		
		guiX = _x/UI_SCALE_FACTOR;
		guiY = _y/UI_SCALE_FACTOR;

		GameBlock *curBlock;

		int res;
		int i;
		int j;
		int k;
		int ii;
		int jj;
		int bestInd;
		float bestDis;
		float curDis;

		float wheelDelta = 0.0f;
		bool mbClicked = false;
		bool rbClicked = false;
		bool lbClicked = false;

		int mouseMovingStart;

		FIVector4 testVec;
		FIVector4 oneVec;
		oneVec.setFXYZ(1.0f, 1.0f, 1.0f);
		oneVec.normalize();

		
		hitGUI = false;
		
		if ((mainGUI != NULL)&&guiOn) {
			if (mainGUI->isReady) {
				hitGUI = mainGUI->testHit(button, state, guiX, guiY);
			}
		}
		

		if (hitGUI)
		{
			bufferInvalid = true;
			return;
		}
		

		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			lbDown = (state == GLUT_DOWN);
			lbClicked = (state == GLUT_UP);

			break;
		case GLUT_RIGHT_BUTTON:
			rbDown = (state == GLUT_DOWN);
			rbClicked = (state == GLUT_UP);

			break;
		case GLUT_MIDDLE_BUTTON:
			mbDown = (state == GLUT_DOWN);
			mbClicked = (state == GLUT_UP);

			break;

		case 3: // wheel up
			wheelDelta = 1.0f / 20.0f;
			//changesMade = true;
			break;

		case 4: // wheel down
			wheelDelta = -1.0f / 20.0f;
			//changesMade = true;
			break;
		}

		abDown = lbDown || rbDown || mbDown;
		


		if (rbClicked)
		{
			
			if (tiltChanged) {
				tiltChanged = false;
				createVTListTilt();
				restartGen(false, true);
				
				//readyForRestart = true;
			}
			
			if (lbDown)
			{

			}
			else
			{
				isPanning = false;
			}

		}
		if (lbClicked)
		{
			
			
			
			if (rbDown)
			{

			}
			else
			{
				isPanning = false;
			}

		}





		if (state == GLUT_DOWN)
		{
			mouseVel.setFXY(0.0f, 0.0f);
		}

		if (rbClicked || lbClicked)
		{




			if (abDown)
			{

			}
			else
			{

				muTime = myTimer.getElapsedTimeInMilliSec();

				mouseEnd.setIXY(x, y);
				//mouseVel.copyFrom(&mouseEnd);
				//mouseVel.addXYZRef(&mouseMoving, -1.0f);

				if ( (activeObject == E_OBJ_CAMERA) && (muTime - mdTime > 300.0f) )
				{
					mouseMovingStart = (mouseMovingLoc - min(mouseMovingStepsBack, mouseCount) + mouseMovingSize) % mouseMovingSize;


					if (mouseCount > 0)
					{
						mouseVel.copyFrom( &(mouseMoving[mouseMovingLoc]) );
						mouseVel.addXYZRef( &(mouseMoving[mouseMovingStart]), -1.0f);
					}


				}




				/*
				mouseMovingSize = 100;
				mouseMovingLoc = 0;
				mouseCount = 0;
				mouseMovingStepsBack = 10;
				*/

				lastModXYZ.normalize();


				//mouseVel.multXYZ( clampf(1.0f-(muTime-mdTime)/1000.0f, 0.1f, 1.0f)/cameraZoom );

				if (shiftDown())
				{

				}
				else
				{




					activeObject = E_OBJ_CAMERA;
					wsBufferInvalid = true;
					getPixData(&mouseUpPD, x, y);


					
					
					
					if (mouseState == E_MOUSE_STATE_PICKING) {
						selectedGeom = findNearestGeom(
							&mouseUpPD,
							true,
							false
						);
					}
					else {
						selectedGeom = findNearestGeom(
							&mouseUpPD,
							false,
							true
						);
					}

					if (
						(selectedGeom == NULL) ||
						(mouseState == E_MOUSE_STATE_PICKING) ||
						(mouseState == E_MOUSE_STATE_BRUSH)
					)	{

					}
					else
					{

						switch (selectedGeom->buildingType)
						{
						case E_CT_DOOR:
						case E_CT_WINDOW:
							
							
						
							
						
							gw->getHoldersInGeom(selectedGeom);
							selectedGeom->toggleTransform();
							gw->getHoldersInGeom(selectedGeom);
							gw->refreshHoldersInList(true, true); //holderCount <= 12
							gw->holdersToRefresh.clear();
							
							if (selectedGeom->isToggled) {
								// open
								switch (selectedGeom->buildingType)
								{
									case E_CT_DOOR:
										playSoundPosAndPitch(
											"open3",
											cameraPos,
											selectedGeom->getVisMinInPixelsT(),
											0.3f
										);
									break;
									case E_CT_WINDOW:
										playSoundPosAndPitch(
											"open1",
											cameraPos,
											selectedGeom->getVisMinInPixelsT(),
											0.3f
										);
									break;
								}
							}
							else {
								// close
								
								switch (selectedGeom->buildingType)
								{
									case E_CT_DOOR:
										playSoundPosAndPitch(
											"close2",
											cameraPos,
											selectedGeom->getVisMinInPixelsT(),
											0.3f
										);
									break;
									case E_CT_WINDOW:
										playSoundPosAndPitch(
											"close1",
											cameraPos,
											selectedGeom->getVisMinInPixelsT(),
											0.3f
										);
									break;
								}
							}
							

							bufferInvalid = true;
							changesMade = true;
							wsBufferInvalid = true;
							break;

						case E_CT_LANTERN:
							selectedGeom->light->isOn = !(selectedGeom->light->isOn);
							playSoundPosAndPitch(
								"castinet0",
								cameraPos,
								selectedGeom->getVisMinInPixelsT(),
								0.3f
							);
							
							doTraceND("");
							doTraceND("CUR LIGHT DIS ", f__s(selectedGeom->light->screenDistance));
							doTraceND("");
							for (i = 0; i < gw->lightCount; i++)
							{
							 	doTraceND("LIGHT DIS ", f__s(gw->activeLights[i]->screenDistance));
							}
							doTraceND("");
							doTraceND("");

							gw->updateLights();
							break;

						}

					}






					if ( mouseEnd.distance(&mouseStart) > 30.0 )
					{

					}
					else
					{
						
						if (pathfindingOn) {
							if (lbClicked) {
								
								if (currentStep == 2) {
									currentStep = 0;
									moveNodes[0].setFXYZ(0.0,0.0,0.0);
									moveNodes[1].setFXYZ(0.0,0.0,0.0);
								}
								else {
									moveNodes[currentStep].copyFrom(&(gw->lastUnitPos));
									currentStep++;
								}
							}
						}
						else {
							switch (mouseState) {
								case E_MOUSE_STATE_BRUSH:
									
									if (lbClicked)
									{
										gw->modifyUnit(&mouseUpPD, E_BRUSH_ADD);
									}
									else
									{
										gw->modifyUnit(&mouseUpPD, E_BRUSH_SUB);
									}

									forceGetPD = true;

								break;
							}
						}
						
						
						
					}

				}


			}


		}
		else
		{
			if (abDown)
			{

				if (rbDown && lbDown)
				{

				}
				else
				{


					lastModXYZ.setFXYZ(0.0f, 0.0f, 0.0f);

					mouseMovingLoc = 0;
					mouseCount = 0;
					mdTime = myTimer.getElapsedTimeInMilliSec();
					mouseStart.setIXY(x, y);

					getPixData(&mouseDownPD, x, y);










					activeObject = E_OBJ_CAMERA;
					
					
					
					
					if (bCtrl) {
						if (mouseDownPD.getFW() != 0.0) {
							// find nearest dyn object
							
							cout << "OBJECT ID " << mouseDownPD.getFW() << "\n";
							

							bestInd = mouseDownPD.getFW();
							
							if ((bestInd >= E_OBJ_LENGTH)||(bestInd <= 0)) {
								
							}
							else {
								activeObject = (E_OBJ)(bestInd);
							}
							
							//bestDis = 99999.0f;
							
							//getPixData(&geomPD, x, y, 2, true);
							//doTraceVecND("GEOM PD ", &geomPD);
							
							//worldToScreenBase(&tempVec1, &mouseDownPD);
							
							// for (i = 1; i < dynObjects.size(); i++)
							// {


							// 	//worldToScreenBase(&tempVec2, &(dynObjects[i]->pos));

							// 	curDis = geomPD.distance(&(dynObjects[i]->pos));


							// 	if (curDis < bestDis)
							// 	{
							// 		bestDis = curDis;
							// 		bestInd = i;
							// 	}
							// }

							
						}
					}
					else {
						
						if (entOn) {
							updateNearestEntNode(true, &mouseDownPD);
						}
						
					}
					
					
					
				}


			}
		}



		


		if ( (button == 3) || (button == 4) ) {
			
			myDelta += wheelDelta;
			targetZoom = pow(2.0, myDelta);
			isZooming = true;

		}

		if (x >= 0 && y >= 0 && x < baseW && y < baseH)
		{
			bufferInvalid = true;
		}

	}
void Singleton::resetActiveNode ()
                               {
		
		GameEntNode* curNode = NULL;
		
		if (selectedNode == NULL) {
			curNode = lastSelNode;
		}
		else {
			curNode = selectedNode;
		}
		
		if (curNode != NULL) {
			curNode->rotThe = 0.0f;
			curNode->rotPhi = 0.0f;
			curNode->rotRho = 0.0f;
			
			curNode->tbnRadScale0.setFXYZ(1.0f,1.0f,1.0f);
			curNode->tbnRadScale1.setFXYZ(1.0f,1.0f,1.0f);
			makeDirty();
		}
	}
void Singleton::updateNearestEntNode (bool setActive, FIVector4 * mousePosWS)
                                                                         {
		// tempVec3.setFXYZRef(mousePosWS);
		// tempVec3.addXYZRef(&(testHuman->basePosition),-1.0f);
		
		worldToScreenBase(&tempVec1, mousePosWS);
		
		bestNode = NULL;
		bestNodeDis = 99999.0f;
		findNearestEntNode(
			testHuman->baseNode,
			&tempVec1
		);
		
		if (bestNodeDis >= 1.0f*pixelsPerMeter) {
			bestNode = NULL;
			activeNode = NULL;
			setSelNode(NULL);
		}
		
		if (bestNode != NULL) {
			
			setSelNode(bestNode);
			if (setActive) {
				activeNode = bestNode;				
			}
		}
	}
void Singleton::findNearestEntNode (GameEntNode * curNode, FIVector4 * mousePosSS)
          {
		
		tempVec3.setFXYZRef(&(curNode->orgTrans[1]));
		tempVec3.multXYZ(pixelsPerMeter);
		tempVec3.addXYZRef(&(testHuman->basePosition));
		
		worldToScreenBase(&tempVec2, &tempVec3);
		float curDis = mousePosSS->distanceXY(&tempVec2);
		
		if (curDis < bestNodeDis) {
			bestNodeDis = curDis;
			bestNode = curNode;
		}
		
		int i;
		
		for (i = 0; i < curNode->children.size(); i++) {
			findNearestEntNode(curNode->children[i],mousePosSS);
		}
		
	}
void Singleton::processB64 (charArr * sourceBuffer, charArr * saveBuffer)
        {

		char *buf = sourceBuffer->data;
		int len = sourceBuffer->size;

		if (saveBuffer != &nullBuffer)
		{
			if (saveBuffer->data != NULL)
			{
				delete[] saveBuffer->data;
				saveBuffer->data = NULL;
			}
			saveBuffer->data = new char[len];
			strncpy(saveBuffer->data, buf, len);
			saveBuffer->size = len;
		}


		FBOSet *fbos = &(fboMap["palFBO"]);


		//unsigned char* resultImage = new unsigned char[256*256*4];

		membuf inBuffer(sourceBuffer->data, sourceBuffer->data + sourceBuffer->size);
		std::istream myIS(&inBuffer);
		
		
#ifdef USE_POCO
		Poco::Base64Decoder b64in(myIS);
		std::ostringstream oss;
		oss << b64in.rdbuf();
		std::string strConst = oss.str();
#else
		std::string sbString = string(sourceBuffer->data, sourceBuffer->size);
		std::string strConst = base64_decode(sbString);
#endif
		
		
		const char *inString = strConst.c_str();
		
		
		
		


		lodepng_decode32(&resultImage, &palWidth, &palHeight, (unsigned char *)inString, strConst.size() );

		fbos->copyFromMem(0, resultImage);

	}
bool Singleton::processJSONFromString (string * sourceBuffer, JSONValue * * destObj)
          {
		if (*destObj != NULL)
		{
			delete *destObj;
			*destObj = NULL;
		}
		
		*destObj = JSON::Parse(sourceBuffer->c_str());

		if (*destObj == NULL)
		{
			doTraceND("Invalid JSON\n\n");
			cout << sourceBuffer << "\n\n";
			return false;
		}
		else
		{
			doTraceND("\nValid JSON\n");
			return true;
		}
		
	}
bool Singleton::processJSON (charArr * sourceBuffer, charArr * saveBuffer, JSONValue * * destObj)
          {
		
		if (*destObj != NULL)
		{
			delete *destObj;
			*destObj = NULL;
		}

		//doTraceND("destObj is now NULL");
		

		//doTraceND("processJSON()");

		char *buf = sourceBuffer->data;
		int len = sourceBuffer->size;
		//JSONValue *jsonVal = NULL;

		if (saveBuffer != &nullBuffer)
		{
			if (saveBuffer->data != NULL)
			{
				delete[] saveBuffer->data;
				saveBuffer->data = NULL;
			}
			saveBuffer->data = new char[len];
			strncpy(saveBuffer->data, buf, len);
			saveBuffer->size = len;
		}

		//doTraceND("Begin JSON::Parse()");

		if (buf == NULL)
		{
			//doTraceND("buf is NULL");
			return false;
		}
		else
		{
			//doTraceND("buf is not NULL");
			*destObj = JSON::Parse(buf);
		}


		//doTraceND("End JSON::Parse()");


		if (*destObj == NULL)
		{
			doTraceND("Invalid JSON\n\n");
			return false;
		}
		else
		{
			doTraceND("\nValid JSON\n");
			return true;
		}


	}
bool Singleton::loadJSON (string path, JSONValue * * destObj)
          {
		
		bool res = false;
		
		charArr dest;
		dest.data = NULL;
		dest.size = 0;
		
		if ( loadFile(path, &dest) )
		{
			if (processJSON(&dest, &nullBuffer, destObj)) {
				res = true;
			}
			else {
				res = false;
			}
		}
		else {
			res = false;
		}
		
		
		if (dest.data != NULL)
		{
			delete[] dest.data;
			dest.data = NULL;
		}
		
		return res;
		
	}
void Singleton::setGUIText (string key, string stringValue, float floatValue, bool applyVal, bool applyString)
          {
		UICStruct* curComp;
		if (compMap.find( key ) == compMap.end()) {
			// invalid key
		}
		else {
			curComp = &(compMap[key]);
			
			if (
				(curComp->uic == NULL) ||
				(curComp->nodeId < 0)	
			) {
				// component was deleted
			}
			else {
				if (applyString) {
					curComp->uic->setText(stringValue);
				}
				if (applyVal) {
					curComp->uic->setValue(floatValue);
				}
				
			}
		}
	}
float Singleton::getGUIValue (string key)
                                      {
		UICStruct* curComp;
		if (compMap.find( key ) == compMap.end()) {
			// invalid key
		}
		else {
			curComp = &(compMap[key]);
			
			if (
				(curComp->uic == NULL) ||
				(curComp->nodeId < 0)	
			) {
				// component was deleted
			}
			else {
				return curComp->uic->getValue();
			}
		}
		
		return 0.0;
	}
void Singleton::setGUIValue (string key, float floatValue, bool dispatchEvent, bool preventRefresh)
          {
		UICStruct* curComp;
		
		if (compMap.find( key ) == compMap.end()) {
			// invalid key
		}
		else {
			curComp = &(compMap[key]);
			
			if (
				(curComp->uic == NULL) ||
				(curComp->nodeId < 0)	
			) {
				// component was deleted
			}
			else {
				curComp->uic->setValue(floatValue,dispatchEvent,preventRefresh);
			}
		}
	}
void Singleton::loadGUIValues (bool applyValues)
                                                     {
		
		cout << "Loading GUI Values\n";
		
		int i;
		
		charArr dest;
		dest.data = NULL;
		dest.size = 0;
		
		UICStruct* curComp;
		
		string loadBuf;
		vector<string> splitStrings;
		if ( loadFile(guiSaveLoc, &dest) )
		{
			loadBuf = string(dest.data);
			splitStrings = split(loadBuf, '^');
			
			for (i = 0; i < splitStrings.size(); i += 2) {
				
				setGUIValue(
					splitStrings[i],
					hexToFloat( &(splitStrings[i+1]) ),
					true,
					true
				);
				
				if (applyValues) {
					
				}
				else {
					
				}
				
			}
			
		}
		else {
			cout << "Unable to load GUI Values\n";
			
		}
		
		if (dest.data != NULL)
		{
			delete[] dest.data;
			dest.data = NULL;
		}
		
		cout << "End Loading GUI Values\n";
	}
void Singleton::saveGUIValues ()
                             {
		
		cout << "Saving GUI Values\n";
		
		stringBuf = "";
		
		for(itUICStruct iterator = compMap.begin(); iterator != compMap.end(); iterator++) {
				
				if (
					(iterator->second.uic == NULL) ||
					(iterator->second.nodeId < 0)
				) {
					
				}
				else {
					if (iterator->first[0] ==  '$') {
						stringBuf.append(
							iterator->first + "^" + floatToHex(iterator->second.uic->getValue()) + "^"
						);
					}
					
					
				}
				
		    // iterator->first = key
		    // iterator->second = value
		}
		
		saveFileString(guiSaveLoc,&stringBuf);
		
		cout << "End Saving GUI Values\n";
	}
void Singleton::updateGUI ()
                         {
		
		float chunkMem;
		float fbMem;
		
		
		
		int mvPerPage = (volGenFBOX*volGenFBOX*volGenFBOX)/(1024*1024);
		
		float voxelsGen = PAGE_COUNT*mvPerPage;
		
		string maxGPUMString = " / " + fi__s(MAX_GPU_MEM);
		
		if (frameCount%120 == 0) {
			
			chunkMem = ((float)gpuPool->holderPoolItems.size())*holderSizeMB;
			fbMem = TOT_GPU_MEM_USAGE - chunkMem;
			
			
			setGUIText("debug.fbMem", "Frame Buffer Mem Used: " + fi__s(fbMem) + maxGPUMString, fbMem/MAX_GPU_MEM, true );
			setGUIText("debug.chunkMem", "Chunk Mem Used: " + fi__s(chunkMem) + maxGPUMString, chunkMem/MAX_GPU_MEM, true );
			setGUIText("debug.totMem", "Total Mem Used: " + fi__s(TOT_GPU_MEM_USAGE) + maxGPUMString, TOT_GPU_MEM_USAGE/MAX_GPU_MEM, true );
			setGUIText("debug.chunksGen", "Voxels Generated (In Millions!): " + fi__s(voxelsGen) );
			 
		}
		
	}
void Singleton::loadGUI ()
                       {
		
		
		for(itUICStruct iterator = compMap.begin(); iterator != compMap.end(); iterator++) {
				iterator->second.uic = NULL;
				iterator->second.nodeId = -1;
		    // iterator->first = key
		    // iterator->second = value
		}
		
		
		if (
			loadJSON("../cdat/lastJSONBufferGUI.js", &guiRootJS)
		) {
			mainGUI->guiFromJSON(
				guiRootJS
			);
		
			for(itUICStruct iterator = compMap.begin(); iterator != compMap.end(); iterator++) {
					
					
					if (iterator->second.nodeId != -1) {
						iterator->second.uic = mainGUI->findNodeById(iterator->second.nodeId);
					}
			}
		
		}
		
		
		
		//testTT = mainGUI->findNodeByString("testTT");
		
		bufferInvalid = true;
	}
void Singleton::loadAllData ()
        {
		if ( loadFile("../cdat/lastJSONBuffer.js", &lastJSONBuffer) )
		{
			processJSON(&lastJSONBuffer, &nullBuffer, &rootObjJS);
		}

		if ( loadFile("../cdat/lastImageBuffer.txt", &lastImageBuffer) )
		{
			processB64(&lastImageBuffer, &nullBuffer);
		}

		bufferInvalid = true;
	}
void Singleton::saveAllData ()
        {
		
		
		saveFile("../cdat/lastJSONBuffer.js", &lastJSONBuffer);
		saveFile("../cdat/lastImageBuffer.txt", &lastImageBuffer);
		
		cout << "All Data Saved\n";
	}
bool Singleton::loadFile (string fnString, charArr * dest)
        {
		
		const char* fileName = fnString.c_str();
		
		doTraceND("Loading: ", fileName);

		if (dest == NULL)
		{
			doTraceND("Null Data");
			return false;
		}

		std::ifstream infile (fileName, std::ifstream::in);


		if ( ! infile.is_open() )
		{
			doTraceND("Could Not Open File For Loading");
			return false;
		}

		// get size of file
		infile.seekg (0, infile.end);
		long size = (long)infile.tellg();
		infile.seekg (0, infile.beg);


		dest->size = size;

		if (dest->data != NULL)
		{
			delete[] dest->data;
			dest->data = NULL;
		}

		dest->data = new char[size+1];

		// read content of infile
		infile.read (dest->data, size);

		if ( infile.bad() )
		{
			doTraceND("Could Not Load From File");
			infile.close();
			return false;
		}

		infile.close();
		
		dest->data[size] = '\0';

		doTraceND("Load Successful");

		return true;
	}
bool Singleton::saveFileString (string fileName, string * source)
        {

		if (source == NULL)
		{
			doTraceND("Null Data");
			return false;
		}

		std::ofstream outfile (fileName.c_str(), std::ofstream::out);

		if ( ! outfile.is_open() )
		{
			doTraceND("Could Not Open File For Saving");
			return false;
		}

		outfile.write(source->c_str(), source->size());

		if ( outfile.bad() )
		{
			doTraceND("Could Not Save To File");
			outfile.close();
			return false;
		}

		outfile.close();

		doTraceND("Save Successful");

		return true;
	}
bool Singleton::saveFile (char * fileName, charArr * source)
        {

		if (source->data == NULL)
		{
			doTraceND("Null Data");
			return false;
		}

		std::ofstream outfile (fileName, std::ofstream::out);

		if ( ! outfile.is_open() )
		{
			doTraceND("Could Not Open File For Saving");
			return false;
		}

		outfile.write (source->data, source->size);

		if ( outfile.bad() )
		{
			doTraceND("Could Not Save To File");
			outfile.close();
			return false;
		}

		outfile.close();

		doTraceND("Save Successful");

		return true;
	}
void Singleton::updateAmbientSounds ()
                                   {
		FIVector4 *cameraPos = &(dynObjects[E_OBJ_CAMERA]->pos);
		
		int i;
		int j;
		
		int maxRad = 2.0f;
		
		float avgHeight = 0.0f;
		float tot = 0.0f;
		
		for (i = -maxRad; i <= maxRad; i++) {
			for (j = -maxRad; j <= maxRad; j++) {
				avgHeight += getHeightAtPixelPos(
					cameraPos->getFX() + i*32.0f*pixelsPerMeter,
					cameraPos->getFY() + j*32.0f*pixelsPerMeter
				);
				tot += 1.0f;
			}
		}
		
		float terHeight = avgHeight/tot;
		
		float seaHeight = getSLInPixels();
		
		float heightDif = clampf((terHeight-seaHeight)/(16.0*pixelsPerMeter), 0.0, 1.0);
		
		music[EML_BIRDSONG0]->setVolume(masterVolume*ambientVolume*timeOfDay*heightDif);
		music[EML_CRICKETS0]->setVolume(masterVolume*ambientVolume*(1.0f-timeOfDay)*heightDif);
		music[EML_OCEANWAVES0]->setVolume(masterVolume*ambientVolume*(1.0f-heightDif));
		
	}
void Singleton::frameUpdate ()
                           {
		
		
		
		float hs = holderSizeInPixels;
		
		FIVector4 *cameraPos = &(dynObjects[E_OBJ_CAMERA]->pos);
		float scrollAmount = 0.0f;
		
		updateAmbientSounds();
		if ((mainGUI != NULL)&&guiOn) {
			if (mainGUI->isReady) {
				//mainGUI->testOver(guiX, guiY);
			}
			
		}
		
		
		if (autoScroll) {
			changesMade = true;
			cameraPos->copyFrom(&baseScrollPos);
			scrollAmount = scrollTimer.getElapsedTimeInMilliSec()/scrollDiv;
			cameraPos->addXYZ(-scrollAmount,-scrollAmount,0.0f);
			
			// cameraPosAdjusted.copyFrom(cameraPos);
			// setObjToElevationBase(&cameraPosAdjusted);
			// cameraPos->addXYZ(16.0*pixelsPerMeter,16.0*pixelsPerMeter,0.0f);
			//syncObjects(&cameraPosAdjusted);
			
			syncObjects(cameraPos);
			
			
			
			if (gw->curLoadRadius == maxWInPages) {
				gw->curLoadRadius = minWInPages;
			}
			
		}
		else {
			if (
				(
					readyForRestart &&
					(guiLock == false) &&
					(gw->curLoadRadius > minWInPages)	
				)
				||
				forceRestart
			) {
				
				if (forceRestart) {
					forceRestart = false;			
				}
				readyForRestart = false;
				guiLock = true;
				restartGen(false, false);
				guiLock = false;
				
			}
			
			updateGUI();
		}
		
		
		
		
		gw->update();
		
		
		
		
		TRACE_ON = false;
		changesMade = false;
		bufferInvalid = false;
		
		frameCount++;
	}
void Singleton::display ()
        {

		curTime = myTimer.getElapsedTimeInMilliSec();

		float elTime = curTime - lastTime;
		float dz;
		float fMouseVel;

#ifdef USE_POCO
		if (myWS == NULL)
		{

		}
		else
		{

			if (myWS->dataReady)
			{

				if (myWS->isJSON)
				{
					if ( processJSON( &(myWS->recBuffer), &lastJSONBuffer, &rootObjJS ) )
					{
						saveAllData();

					}
				}
				else
				{
					processB64(  &(myWS->recBuffer), &lastImageBuffer );

				}

				bufferInvalid = true;

				myWS->dataReady = false;
				myWS->isWorking = false;
			}
		}
#else
		//processB64NoPoco();
#endif

		



		if (abs(timeOfDay - targetTimeOfDay) > 0.001)
		{
			bufferInvalid = true;
			changesMade = true;
		}


		if (elTime >= ( msPerFrame  )  ) { // / ((float)skipFrames)

			if (firstRun)
			{
				
			}
			else
			{
				if ( (frameCount % 120) == 0)
				{
					gw->updateLights();
					bufferInvalid = true;
					changesMade = true;
				}
			}




			lastTime = curTime;


			timeOfDay += (targetTimeOfDay - timeOfDay) / 8.0;


			mouseMovingLoc = (mouseMovingLoc + 1) % mouseMovingSize;
			mouseCount++;
			mouseMoving[mouseMovingLoc].setIXY(lastMouseX, lastMouseY);



			lastModXYZ.multXYZ(0.95f);

			mouseVel.multXYZ(0.95f);

			fMouseVel = mouseVel.distance(&origin);

			// if ( fMouseVel < 2.0f ) {
			//  mouseVel.setFXY(0.0f,0.0f);
			//  isPanning = false;
			// }
			// else {
			//  isPanning = true;


			//  panMod.copyFrom(&lastModXYZ);
			//  panMod.multXYZ(fMouseVel/16.0f);
			//  moveCamera(&panMod);
			// }


			dz = (targetZoom - cameraZoom) / (4.0f);

			/*
			if (abs(dz) < 0.0001) {
			  dz = 0.0f;
			}
			*/

			/*
			if (cameraZoom > 8.0f) {
			  cameraZoom = 8.0f;
			}
			if (cameraZoom < 1.0f/8.0f) {
			  cameraZoom = 1.0f/8.0f;
			}
			*/

			//curMS = fpsTimer.getElapsedTimeInMilliSec() / renderCount;

			cameraZoom += dz;
			

			if ( ( abs(dz) / cameraZoom < 0.001 ) && (isZooming))
			{
				isZooming = false;
				wsBufferInvalid = true;
				bufferInvalid = true;
				changesMade = true;
			}
			else
			{
				if (isZooming)
				{
					bufferInvalid = true;
					changesMade = true;
				}

			}
			

			if (shadersAreLoaded)
			{

				if (traceOn)
				{
					traceOn = false;
					TRACE_ON = true;
				}
				if (updateLock)
				{

				}
				else
				{
					frameUpdate();
				}
			}

			
		}

		if (firstRun)
		{
			//toggleFullScreen();
		}

		firstRun = false;

		//doTrace( "POSSIBLE ERROR: " , i__s(glGetError()) , "\n" );

	}
void Singleton::reshape (int w, int h)
        {

		setWH(w, h);

		screenWidth = w;
		screenHeight = h;

		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
		glMatrixMode(GL_MODELVIEW);
		orthographicProjection();


		setMatrices(baseW, baseH);
	}
void Singleton::idleFunc ()
        {

	}
#undef LZZ_INLINE
 
// f00305_shader.h
//

#include "f00305_shader.e"
#define LZZ_INLINE inline
Shader::Shader (Singleton * _singleton)
                                      {
		singleton = _singleton;
		curUBIndex = 0;
	}
char * Shader::textFileRead (char const * fileName)
                                                        {
		
		char* text = "";
		bool failed = true;
	    
		if (fileName != NULL) {
	        FILE *file = fopen(fileName, "rt");
	        
			if (file != NULL) {
	            fseek(file, 0, SEEK_END);
	            int count = ftell(file);
	            rewind(file);
	            
				if (count > 0) {
					text = new char[(count + 1)];
					//(char*)malloc(sizeof(char) * (count + 1));
					count = fread(text, sizeof(char), count, file);
					text[count] = '\0';
					failed = false;
				}
				fclose(file);
			}
		}

		if (failed) {
			doTraceND("FAILED TO READ FILE: ", fileName);
		}
		else {
			//doTrace("READ FILE: ", fileName);
		}
		
		
		return text;
	}
void Shader::validateShader (GLuint shader, char const * file)
                                                                        {
		//pushTrace("validateShader(", file, ")");
		
		const unsigned int BUFFER_SIZE = 512;
		char buffer[BUFFER_SIZE];
		memset(buffer, 0, BUFFER_SIZE);
		GLsizei length = 0;
	    
		glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer);
		if (length > 0) {
			doTraceND("Shader " , i__s(shader) , " (" , (file?file:"") , ") compile error: " , buffer);
			LAST_COMPILE_ERROR = true;
		}
		//popTrace();


	}
int Shader::validateProgram (GLuint program)
                                                   {
		//pushTrace("validateProgram()");
		
		const unsigned int BUFFER_SIZE = 512;
		char buffer[BUFFER_SIZE];
		memset(buffer, 0, BUFFER_SIZE);
		GLsizei length = 0;
	    
		memset(buffer, 0, BUFFER_SIZE);
		glGetProgramInfoLog(program, BUFFER_SIZE, &length, buffer);
		if (length > 0) {
			doTraceND( "Program " , i__s(program) , " link error: " , buffer);
			LAST_COMPILE_ERROR = true;
			//popTrace();
			return 0;
		}
	    
		glValidateProgram(program);
		GLint status;
		glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
		if (status == GL_FALSE) {
			doTraceND( "Error validating shader " , i__s(program));
			LAST_COMPILE_ERROR = true;
			//popTrace();
			return 0;
		}
		
		//popTrace();
		return 1;
		
	}
int Shader::countOc (string * src, string testStr)
                                                 {
		int totCount = 0;
		int bInd = 0;
		bool dc = true;
		int fnd = 0;
		
		while (dc) {
			fnd = src->find(testStr, bInd);
			if (fnd != std::string::npos) {
				bInd = fnd+1;
				dc = true;
				totCount++;
			}
			else {
				dc = false;
			}
		}
		
		return totCount;
	}
void Shader::init (string _shaderFile, bool doBake)
                                                   {
		
		
		
		const char* shaderFile = _shaderFile.c_str();
		
		uniVec.clear();
		paramVec.clear();
		paramMapTemp.clear();
		
		shader_vp = glCreateShader(GL_VERTEX_SHADER);
		shader_fp = glCreateShader(GL_FRAGMENT_SHADER);
	    
	    
		std::size_t found;
		std::size_t found2;
		std::size_t found3;

		int baseIndex;
		int uniCount = 0;
		int dolCount = 0;
		
		
		vector<string> allTextStringSplit;

		bool doCont;
		
		string paramName;

		int i;

		const char* allText = textFileRead(shaderFile);


		if (allText == NULL) {
			doTraceND( "Error: Either vertex shader or fragment shader file not found." );
			LAST_COMPILE_ERROR = true;
		}
		else {
			
				string allTextString(allText);
				
				
				

				//
				
				dolCount = countOc(&allTextString,"$");

				if (dolCount == 2) {
					
					uniCount = countOc(&allTextString,"ublock");


					baseIndex = 0;
					doCont = true;
					while (doCont) {
						found = allTextString.find('@', baseIndex);
						if (found != std::string::npos) {
							
							
							baseIndex = found+1;
							allTextString[found] = ' ';
							
							found3 = allTextString.find(' ', baseIndex);
							found2 = allTextString.find('@', baseIndex);
							
							if (found2 != std::string::npos) {
								
								if ( 
									((found2-found) > 32) || // max var length of 32
									(found3 < found2) // found a space between the delimitters
								) { 
									//baseIndex = found+1; // already set
								}
								else {
									baseIndex = found2+1;
									allTextString[found2] = ' ';
									
									paramName = allTextString.substr(found + 1, (found2-found)-1);
									
									if (paramMapTemp.find( paramName ) == paramMapTemp.end()) {
										paramMapTemp[paramName] = 0.0f;
										paramVec.push_back(paramName);
										
										if (paramMap.find( paramName ) == paramMap.end()) {
											paramMap[paramName] = 0.0f;
										}
										
										//cout << "paramName --" << paramName << "--\n";
										
									}
								}
								
								
								
								doCont = true;
							}
							else {
								doCont = false;
							}
							
							
						}
						else {
							doCont = false;
						}
					}
					
					
					
					allTextStringSplit = split(allTextString, '$');
					
					allTextStringSplit[0].append("\n");
					
					if (doBake) {
						for (i = 0; i < paramVec.size(); i++) {
							allTextStringSplit[0].append("const float ");
							allTextStringSplit[0].append(paramVec[i]);
							allTextStringSplit[0].append("=");
							allTextStringSplit[0].append(f__s(paramMap[paramVec[i]]));
							allTextStringSplit[0].append(";\n");
						}
					}
					else {
						for (i = 0; i < paramVec.size(); i++) {
							allTextStringSplit[0].append("uniform float ");
							allTextStringSplit[0].append(paramVec[i]);
							allTextStringSplit[0].append(";\n");
						}
					}
					
					

					string vertStr = allTextStringSplit[0] + allTextStringSplit[1];
					string fragStr = allTextStringSplit[0] + allTextStringSplit[2];

					const GLchar* vertCS = new char[vertStr.length() + 1];
					const GLchar* fragCS = new char[fragStr.length() + 1];

					std::strcpy((GLchar*)vertCS,vertStr.c_str());
					std::strcpy((GLchar*)fragCS,fragStr.c_str());


			    	glShaderSource(shader_vp, 1, &(vertCS), 0);
					glShaderSource(shader_fp, 1, &(fragCS), 0);
				    
					glCompileShader(shader_vp);
					validateShader(shader_vp, shaderFile);
					glCompileShader(shader_fp);
					validateShader(shader_fp, shaderFile);



					shader_id = glCreateProgram();
					glAttachShader(shader_id, shader_fp);
					glAttachShader(shader_id, shader_vp);
					glLinkProgram(shader_id);
					validateProgram(shader_id);

					delete [] vertCS;
					delete [] fragCS;


					for (i = 0; i < uniCount; i++) {
						uniVec.push_back(UniformBuffer());
						uniVec.back().init(shader_id, i);
					}


				}
				else {
					LAST_COMPILE_ERROR = true;
					doTraceND( "Error: " , shaderFile , "does not contain proper amount of splits ($)\n" );
				}
				
				
				delete[] allText;
			  
		}
		
		
		//popTrace();
		
	}
Shader::~ Shader ()
                  {

		uniVec.clear();

		//pushTrace("~Shader()");
		glDetachShader(shader_id, shader_fp);
		glDetachShader(shader_id, shader_vp);
		glDeleteShader(shader_fp);
		glDeleteShader(shader_vp);
		glDeleteProgram(shader_id);
		//popTrace();
	}
unsigned int Shader::id ()
                          {
		//pushTrace("id()");
		return shader_id;
		//popTrace();
	}
void Shader::bind ()
                    {
		//pushTrace("bind()");
		glUseProgram(shader_id);
		//popTrace();
	}
void Shader::updateUniformBlock (int ubIndex, int ubDataSize)
                                                             {
		uniVec[ubIndex].updateUniformBlock(ubDataSize);
	}
void Shader::invalidateUniformBlock (int ubIndex)
                                                 {
		uniVec[ubIndex].invalidateUniformBlock();
	}
void Shader::beginUniformBlock (int ubIndex)
                                            {
		curUBIndex = ubIndex;
		uniVec[ubIndex].beginUniformBlock();
	}
bool Shader::wasUpdatedUniformBlock (int ubIndex)
                                                 {

		if (uniVec.size() > ubIndex) {
			return uniVec[ubIndex].wasUpdatedUniformBlock();
		}
		else {
			return true;
		}

		
	}
void Shader::unbind ()
                      {
		//pushTrace("unbind()");
		glUseProgram(0);
		//popTrace();
	}
void Shader::setTexture (GLchar const * name, int texUnit, int texId)
                                                                    {
		GLint baseImageLoc = glGetUniformLocation(shader_id, name);

		glUniform1i(baseImageLoc, texUnit); //Texture unit 0 is for base images.
		
		//When rendering an objectwith this program.
		glActiveTexture(GL_TEXTURE0 + texUnit);
		glBindTexture(GL_TEXTURE_2D, texId);
	}
void Shader::setVec (GLchar const * name, GLfloat const * vecData, int vecSize)
                                                                             {
		
		GLint loc = glGetUniformLocation(shader_id, name);
		
		switch (vecSize) {
			case 0:
				doTraceND( "Error: vecSize of 0 in setVec" );
			break;
			case 1:
				glUniform1fv(loc, 1, vecData);
			break;
			case 2:
				glUniform2fv(loc, 1, vecData);
			break;
			case 3:
				glUniform3fv(loc, 1, vecData);
			break;
			case 4:
				glUniform4fv(loc, 1, vecData);
			break;
		}
	}
void Shader::setVecString (string name, GLfloat const * vecData, int vecSize)
                                                                            {
		
		GLint loc = glGetUniformLocation(shader_id, name.c_str());
		
		switch (vecSize) {
			case 0:
				doTraceND( "Error: vecSize of 0 in setVec" );
			break;
			case 1:
				glUniform1fv(loc, 1, vecData);
			break;
			case 2:
				glUniform2fv(loc, 1, vecData);
			break;
			case 3:
				glUniform3fv(loc, 1, vecData);
			break;
			case 4:
				glUniform4fv(loc, 1, vecData);
			break;
		}
	}
void Shader::setShaderArrayfVec4 (string paramName, float * x, int count)
                                                                        {
		GLint loc = glGetUniformLocation(shader_id, paramName.c_str());
		glUniform4fv(loc, count, x);
	}
void Shader::setShaderArrayfVec3 (string paramName, float * x, int count)
                                                                        {
		GLint loc = glGetUniformLocation(shader_id, paramName.c_str());
		glUniform3fv(loc, count, x);
	}
void Shader::setShaderArray (string paramName, float * x, int count)
                                                                   {
		GLint loc = glGetUniformLocation(shader_id, paramName.c_str());
		glUniform1fv(loc, count, x);
	}
void Shader::setShaderFloat (string paramName, float x)
                                                       {
		GLint loc = glGetUniformLocation(shader_id, paramName.c_str());
		glUniform1f(loc,x);
	}
void Shader::setShaderVec2 (string paramName, float x, float y)
                                                               {
		GLint loc = glGetUniformLocation(shader_id, paramName.c_str());
		glUniform2f(loc,x,y);
	}
void Shader::setShaderVec3 (string paramName, float x, float y, float z)
                                                                        {
		GLint loc = glGetUniformLocation(shader_id, paramName.c_str());
		glUniform3f(loc,x,y,z);
	}
void Shader::setShaderVec4 (string paramName, float x, float y, float z, float w)
                                                                                 {
		GLint loc = glGetUniformLocation(shader_id, paramName.c_str());
		glUniform4f(loc,x,y,z,w);
	}
void Shader::setShaderInt (string paramName, int x)
                                                   {
		GLint loc = glGetUniformLocation(shader_id, paramName.c_str());
		glUniform1i(loc,x);
	}
void Shader::setShaderfVec2 (string paramName, FIVector4 * f)
                                                            {
		GLint loc = glGetUniformLocation(shader_id, paramName.c_str());
		glUniform2f(loc,f->getFX(),f->getFY());
	}
void Shader::setShaderfVec3 (string paramName, FIVector4 * f)
                                                            {
		GLint loc = glGetUniformLocation(shader_id, paramName.c_str());
		glUniform3f(loc,f->getFX(),f->getFY(),f->getFZ());
	}
void Shader::setShaderfVec4 (string paramName, FIVector4 * f)
                                                            {
		GLint loc = glGetUniformLocation(shader_id, paramName.c_str());
		glUniform4f(loc,f->getFX(),f->getFY(),f->getFZ(),f->getFW());
	}
void Shader::setShaderFloatUB (string paramName, float x)
                                                         {
		int cp = uniVec[curUBIndex].uniPosition;

		uniVec[curUBIndex].uniData[cp] = x;
		uniVec[curUBIndex].uniPosition += 1;
	}
void Shader::setShaderfVec4UB (string paramName, FIVector4 * f)
                                                              {

		int cp = uniVec[curUBIndex].uniPosition;

		uniVec[curUBIndex].uniData[cp+0] = f->getFX();
		uniVec[curUBIndex].uniData[cp+1] = f->getFY();
		uniVec[curUBIndex].uniData[cp+2] = f->getFZ();
		uniVec[curUBIndex].uniData[cp+3] = f->getFW();
		uniVec[curUBIndex].uniPosition += 4;
	}
#undef LZZ_INLINE
 
// f00310_pooledresource.h
//

#include "f00310_pooledresource.e"
#define LZZ_INLINE inline
PooledResource::PooledResource ()
                         {
		int i;

		for (i = 0; i < MAX_LAYERS; i++) {
			fboSet[i] = NULL;
		}
		
	}
FBOSet * PooledResource::getFBOS (int fboNum)
                                    {
		return fboSet[fboNum];
	}
void PooledResource::init (Singleton * _singleton, bool _isCPU, int _sizeX, int _sizeY)
          {

		singleton = _singleton;
		isCPU = _isCPU;
		usedById.v0 = -1;
		usedById.v1 = -1;

		int i;

		if (isCPU) {
			for (i = 0; i < MAX_LAYERS; i++) {
				cpuSet[i] = new uint[
					_sizeX *
					_sizeY
				];
			}
		}
		else {
			for (i = 0; i < MAX_LAYERS; i++) {
				fboSet[i] = new FBOSet();
			}

			for (i = 0; i < MAX_LAYERS; i++) {
				fboSet[i]->init(
					2,
					_sizeX,
					_sizeY,
					1,
					false //has depth
				);
			}
		}

		

		

	}
#undef LZZ_INLINE
 
// f00315_poolmanager.h
//

#include "f00315_poolmanager.e"
#define LZZ_INLINE inline
PoolManager::PoolManager ()
                      {
		
	}
void PoolManager::init (Singleton * _singleton, bool _isEntity, bool _isCPU, int _sizeX, int _sizeY)
          {
		isEntity = _isEntity;
		poolItemsCreated = 0;
		isCPU = _isCPU;
		singleton = _singleton;
		gw = singleton->gw;
		sizeX = _sizeX;
		sizeY = _sizeY;
	}
float PoolManager::getMaxMem ()
                          {
		if (isCPU) {
			return MAX_CPU_MEM;
		}
		else {
			
			if (isEntity) {
				// TODO: FIX THIS
				return MAX_GPU_MEM*20.0f;
			}
			else {
				return MAX_GPU_MEM;
			}
			
			
		}
	}
float PoolManager::getTotMemUsed ()
                              {
		if (isCPU) {
			return TOT_CPU_MEM_USAGE;
		}
		else {
			return TOT_GPU_MEM_USAGE;
		}
	}
void PoolManager::reorderIds ()
        {
		int i;
		int j;

		int oidSize =  orderedIds.size();
		int oidSizeM1 =  oidSize - 1;

		intPair id0;
		intPair id1;

		int tempId;

		int tot0;
		int tot1;

		bool doSwap;

		GamePageHolder *gp0;
		GamePageHolder *gp1;

		for (i = 0; i < oidSizeM1; i++)
		{
			for (j = i + 1; j < oidSize; j++ )
			{

				id0 = orderedIds[i];
				id1 = orderedIds[j];

				if ( pairIsNeg(id0) || pairIsNeg(id1))
				{

				}
				else
				{

					gp0 = gw->getHolderAtId(id0);
					gp1 = gw->getHolderAtId(id1);

					if (gp0 == NULL || gp1 == NULL)
					{

					}
					else
					{
						tot0 = gp0->offsetInHolders.getFZ();
						tot1 = gp1->offsetInHolders.getFZ();

						if (tot0 == tot1)
						{
							tot0 = gp0->offsetInHolders.getFY();
							tot1 = gp1->offsetInHolders.getFY();

							if (tot0 == tot1)
							{
								tot1 = gp1->offsetInHolders.getFX();
								tot0 = gp0->offsetInHolders.getFX();

								if (tot0 == tot1)
								{
									doSwap = false;
								}
								else
								{
									doSwap = tot0 > tot1;
								}
							}
							else
							{
								doSwap = tot0 > tot1;
							}
						}
						else
						{
							doSwap = tot0 > tot1;
						}

						if (doSwap)
						{
							orderedIds[i] = id1;
							orderedIds[j] = id0;
						}


					}
				}


			}
		}
	}
int PoolManager::findFurthestHolderId ()
        {


		int longestInd = 0;
		int i;

		float longestDis = 0.0f;
		float testDis;

		FIVector4 tempVec;

		GamePageHolder *gp;
		GamePageHolder *bestGP = NULL;

		for (i = 0; i < holderPoolItems.size(); i++)
		{
			gp = gw->getHolderAtId(holderPoolItems[i]->usedById);

			if (gp == NULL)
			{

			}
			else
			{

				tempVec.copyFrom(&(gw->camHolderPos));
				gp->offsetInHolders.wrapDistance(&tempVec, singleton->worldSizeInHolders.getIX());
				testDis = gp->offsetInHolders.distance( &(tempVec) );

				if (testDis > longestDis)
				{
					longestDis = testDis;
					longestInd = i;
					bestGP = gp;
				}
			}
		}

		return longestInd;
	}
int PoolManager::requestPoolId (int blockId, int holderId)
        {


		int toFreeId;
		intPair usedById;

		int i;


		if (
			(getTotMemUsed() < getMaxMem()) &&
			(
				(orderedIds.size() < MAX_HOLDERS) ||
				(MAX_HOLDERS <= 0)
			)
		)
		{
			holderPoolItems.push_back( new PooledResource() );
			holderPoolItems.back()->init(singleton, isCPU, sizeX, sizeY);

			toFreeId = poolItemsCreated;
			holderPoolIds.push_front(toFreeId);
			orderedIds.push_back(intPair());
			orderedIds.back().v0 = blockId;
			orderedIds.back().v1 = holderId;
			poolItemsCreated++;

		}
		else
		{
			toFreeId = findFurthestHolderId();//holderPoolIds.back();
			usedById = holderPoolItems[toFreeId]->usedById;

			GamePageHolder *consumingHolder;

			if ( pairIsNeg(usedById) )
			{
				// this pooledItem is already free

			}
			else
			{
				// free this pooledItem from the holder that is consuming it and give it to the requesting holder

				consumingHolder = gw->getHolderAtId(usedById);

				if (consumingHolder == NULL)
				{
					// holder was deleted already
				}
				else
				{
					consumingHolder->unbindGPUResources();
				}


			}



			for (i = 0; i < orderedIds.size(); i++)
			{
				if ( pairIsEqual(orderedIds[i], usedById) )
				{
					orderedIds[i].v0 = blockId;
					orderedIds[i].v1 = holderId;
					break;
				}
			}


			holderPoolIds.remove(toFreeId);
			holderPoolIds.push_front(toFreeId);
		}


		holderPoolItems[toFreeId]->usedById.v0 = blockId;
		holderPoolItems[toFreeId]->usedById.v1 = holderId;

		reorderIds();

		return toFreeId;

	}
#undef LZZ_INLINE
 
// f00316_poolpagemanager.h
//

#include "f00316_poolpagemanager.e"
#define LZZ_INLINE inline
PoolPageManager::PoolPageManager ()
                          {
		
	}
#undef LZZ_INLINE
 
// f00320_fontwrapper.h
//

#include "f00320_fontwrapper.e"
#define LZZ_INLINE inline
FontWrapper::FontWrapper ()
                      {
		
	}
void FontWrapper::init (Singleton * _singleton, string fontName, bool _isIcons, float _fontScale, float _additionalOffset)
          {
		
		int counter;
		int i;
		int j;
		int ind;
		
		additionalOffset = _additionalOffset;
		fontScale = _fontScale;
		isIcons = _isIcons;
		
		JSONValue *cn;
		JSONValue *cc;
		
		singleton = _singleton;
		lastJSONBuffer.data = NULL;
		lastJSONBuffer.size = 0;
		
		cout << "\n\n\nFONT LOAD\n\n\n";
		
    jsRoot = nullptr;
		fontImage = loadBMP("../data/fonts/"+fontName+".bmp");
		if (isIcons) {
			fontImage->getTextureId(GL_NEAREST);
		}
		else {
			fontImage->getTextureId(GL_LINEAR);
		}
		
		
		maxWidth = 0.0f;
		counter = 0;
		
		if (isIcons) {
			maxWidth = 16.0f;
			ascender = 0.0f;
			descender = -15.0f+additionalOffset;
			fontHeight = 16.0f;
			
			
			for (j = 0; j < fontImage->height/16; j++) {
				for (i = 0; i < fontImage->width/16; i++) {
					charVals[counter].consumedW = 16.0f;
					charVals[counter].consumedH = 16.0f;
					charVals[counter].offsetX = 0.0f;
					charVals[counter].offsetY = 0.0f;
					charVals[counter].sampX = i*16;
					charVals[counter].sampY = j*16;
					charVals[counter].sampW = 16.0f;
					charVals[counter].sampH = 16.0f;
					
					counter++;
				}
			}
			
		}
		else {
			if ( singleton->loadFile("../data/fonts/"+fontName+".js", &lastJSONBuffer) )
			{
				if (singleton->processJSON(&lastJSONBuffer, &(singleton->nullBuffer), &jsRoot)) {
					
					ascender = jsRoot->Child("metrics")->Child("ascender")->number_value;
					descender = jsRoot->Child("metrics")->Child("descender")->number_value;
					fontHeight = jsRoot->Child("metrics")->Child("height")->number_value;
					
					cn = jsRoot->Child("chars");
					
					
					for (i = 32; i <= 126; i++) {
						ind = i-32;
						cc = cn->Child(ind);
						
						charVals[i].consumedH = fontHeight;
						charVals[i].consumedW = cc->Child("width")->number_value;
						
						charVals[i].offsetX = cc->Child("ox")->number_value;
						charVals[i].offsetY = cc->Child("oy")->number_value;
						
						charVals[i].sampX = cc->Child("x")->number_value;
						charVals[i].sampY = cc->Child("y")->number_value;
						charVals[i].sampW = cc->Child("w")->number_value;
						charVals[i].sampH = cc->Child("h")->number_value;
						
						if (charVals[i].consumedW > maxWidth) {
							maxWidth = charVals[i].consumedW;
						}
					}
					
					
					
				}
			}
		}
		
		
		
		
	}
#undef LZZ_INLINE
 
// f00325_uicomponent.h
//

#include "f00325_uicomponent.e"
#define LZZ_INLINE inline
UIComponent::UIComponent ()
                      {
		
	}
void UIComponent::init (Singleton * _singleton, int _parentId, int _nodeId, int _index, JSONValue * _jvNodeNoTemplate, string _label, string _uid, string _ss, int _guiClass, float _divisions, bool _hasBackground, bool _singleLine, float _fillRatioX, float _fillRatioY, int _fillDir, int _alignX, int _alignY, float _value, int _layer, int _hoverType, float _maxDimInPixelsX, float _maxDimInPixelsY, bool _isFloating)
          {

		parent = NULL;
		foundParent = false;
		contOnStack = false;

		singleton = _singleton;
		parentId = _parentId;
		nodeId = _nodeId;
		
		
		
		jvNodeNoTemplate = _jvNodeNoTemplate;
		
		layer = _layer;
		hoverType = _hoverType;
		isFloating = _isFloating;
		
		ss = _ss;
		label = _label;
		text = label;
		
		uid = _uid;
		index = _index;
		
		if (uid.size() > 0) {
			singleton->compMap[uid].nodeId = nodeId;
		}
		
		
		
		maxDimInPixels.x = _maxDimInPixelsX;
		maxDimInPixels.y = _maxDimInPixelsY;
		
		
		
		guiClass = _guiClass;
		//guiId = _guiId;
		
		
		dragging = false;
		overSelf = false;
		overChild = false;
		isDirty = true;
		visible = (hoverType == E_HT_NORMAL);
		
		hasBackground = _hasBackground;
		fillRatioDim.x = _fillRatioX;
		fillRatioDim.y = _fillRatioY;

		singleLine = _singleLine;
		
		
		curFont = singleton->fontWrappers[EFW_TEXT];
		curFontIcons = singleton->fontWrappers[EFW_ICONS];
		
		wasHit = false;
		value = _value;
		divisions = _divisions;

		mouseDown = false;
		mouseOver = false;

		resSS.init(&(singleton->styleSheetMap[ss]));
		
		
		paddingInPixels = resSS.baseSS->compStates[E_COMP_UP].props[E_SS_PADDING];
		borderInPixels = resSS.baseSS->compStates[E_COMP_UP].props[E_SS_BORDER];
		marginInPixels = resSS.baseSS->compStates[E_COMP_UP].props[E_SS_MARGIN];
		
		
		/////////////////
		
		totOffset.x = 0.0f;
		totOffset.y = 0.0f;
		
		
		targScrollOffset.x = 0.0f;
		targScrollOffset.y = 0.0f;
		
		scrollOffset.x = 0.0f;
		scrollOffset.y = 0.0f;
		
		scrollMaskY.x = 0.0;
		scrollMaskY.y = 0.0;
		
		dragStart.x = 0.0f;
		dragStart.y = 0.0f;
		
		lastDrag.x = 0.0f;
		lastDrag.y = 0.0f;
		
		dragOffset.x = 0.0f;
		dragOffset.y = 0.0f;
		
		floatOffset.x = 0.0f;
		floatOffset.y = 0.0f;
		
		originPos.x = 0.0f;
		originPos.y = 0.0f;
		spaceForCharsInPixels = 200.0f;
		
		/////////////////


		hitBounds.xMin = 0.0f;
		hitBounds.xMax = 0.0f;
		hitBounds.yMin = 0.0f;
		hitBounds.yMax = 0.0f;


		align.x = _alignX;
		align.y = _alignY;
		fillDir = _fillDir;
		
		spacing.x = 0.0f;
		spacing.y = 0.0f;

		
		if (isFloating) {
			resultDimInPixels.x = singleton->guiWinW;
			resultDimInPixels.y = singleton->guiWinH;
			originPos.x = 0.0;
			originPos.y = 0.0;
		}
		
		
	}
float UIComponent::getDimYClamped (float val)
                                        {
		if (maxDimInPixels.y == 0) {
			return val;
		}
		else {
			return min(maxDimInPixels.y, val);
		}
	}
float UIComponent::getResultDimYClamped ()
                                     {
		if (maxDimInPixels.y == 0) {
			return resultDimInPixels.y;
		}
		else {
			return min(maxDimInPixels.y, resultDimInPixels.y);
		}
	}
float UIComponent::getMinDimYClamped ()
                                  {
		if (maxDimInPixels.y == 0) {
			return minDimInPixels.y;
		}
		else {
			return min(maxDimInPixels.y, minDimInPixels.y);
		}
	}
void UIComponent::setValue (float _value, bool doEventDispatch, bool preventRefresh)
                                                                                               {
		value = _value;
		if (doEventDispatch) {
			singleton->dispatchEvent(GLUT_LEFT_BUTTON, GLUT_UP, 0, 0, this, true, preventRefresh);
		}
	}
float UIComponent::getValue ()
                         {
		return value;
	}
UIComponent * UIComponent::getParent ()
                                 {
		if (foundParent) {
			
		}
		else {
			// todo: replace with root or id
			parent = singleton->mainGUI->baseComp->findNodeById(parentId);
			foundParent = true;
		}
		
		return parent;
	}
UIComponent * UIComponent::findNodeByString (string _uid)
                                                   {
		int i;
		
		if (_uid.compare(uid) == 0) {
			return this;
		}
		
		for (i = 0; i < children.size(); i++) {
			if (children[i].findNodeByString(_uid) != NULL) {
				return children[i].findNodeByString(_uid);
			}
		}
		
		for (i = 0; i < floatingChildren.size(); i++) {
			if (floatingChildren[i].findNodeByString(_uid) != NULL) {
				return floatingChildren[i].findNodeByString(_uid);
			}
		}
		
		return NULL;
	}
UIComponent * UIComponent::findNodeById (int id)
                                          {
		int i;
		
		if (nodeId == id) {
			return this;
		}
		
		for (i = 0; i < children.size(); i++) {
			if (children[i].findNodeById(id) != NULL) {
				return children[i].findNodeById(id);
			}
		}
		
		for (i = 0; i < floatingChildren.size(); i++) {
			if (floatingChildren[i].findNodeById(id) != NULL) {
				return floatingChildren[i].findNodeById(id);
			}
		}
		
		return NULL;
	}
float UIComponent::getMinWidth ()
                            {
		int i;
		
		updateVecs();
		
		if (singleLine) {
			spaceForCharsInPixels = 99999.0f;
			renderText(true);
			
		}
		else {
			textDimInPixels.x = 0;
			textDimInPixels.y = 0;
		}
		
		
		
		float curMW = (marginInPixels+borderInPixels+paddingInPixels)*2.0f + 
			textDimInPixels.x;
		
		
		float totMW = 0.0f;
		float tempMW = 0.0f;
		
		for (i = 0; i < children.size(); i++) {
			
			tempMW = children[i].getMinWidth();
			
			if (fillDir == E_FILL_HORIZONTAL) {
				totMW += tempMW;
			}
			else {
				totMW = max(totMW,tempMW);
			}
		}
		
		for (i = 0; i < floatingChildren.size(); i++) {
			floatingChildren[i].getMinWidth();
		}
		
		
		curMW += totMW;
		
		minDimInPixels.x = curMW;
		
		return curMW;
		
	}
float UIComponent::getMinHeight ()
                             {
		int i;
		
		if (!singleLine) {
			spaceForCharsInPixels = resultDimInPixels.x;
			renderText(true);
		}
		else {
			// already determined
		}
		
		
		
		float curMH = (marginInPixels+borderInPixels+paddingInPixels)*2.0f + 
			textDimInPixels.y;
		
		float totMH = 0.0f;
		float tempMH = 0.0f;
		
		
		for (i = 0; i < children.size(); i++) {
			
			tempMH = children[i].getMinHeight();
			
			if (fillDir == E_FILL_HORIZONTAL) {
				
				totMH = max(totMH,tempMH);
			}
			else {
				totMH += tempMH;
			}
		}
		
		
		for (i = 0; i < floatingChildren.size(); i++) {
			floatingChildren[i].getMinHeight();
		}
		
		curMH += totMH;
		
		minDimInPixels.y = curMH;
		
		return getDimYClamped(curMH);//curMH; //getDimYClamped(curMH)
		
	}
UIComponent * UIComponent::addChild (int _parentId, int _nodeId, string * stringVals, float * floatVals, bool _isFloating, JSONValue * _jvNodeNoTemplate)
          {
		
		UIComponent tempComp;
		
		int childCount = 0;
		
		if (_isFloating) {
			floatingChildren.push_back(tempComp);
			curComp = &(floatingChildren.back());
			childCount = floatingChildren.size()-1;
			
			
		}
		else {
			children.push_back(tempComp);
			curComp = &(children.back());
			childCount = children.size()-1;
		}
		
		
		
		
		
		curComp->init(
			singleton,
			_parentId,
			_nodeId,
			childCount,
			
			_jvNodeNoTemplate,
			
			stringVals[E_GST_LABEL],
			stringVals[E_GST_UID],
			stringVals[E_GST_SS],
			
			floatVals[E_GFT_TYPE],
			floatVals[E_GFT_DIVISIONS],
			floatVals[E_GFT_HASBACKGROUND],
			floatVals[E_GFT_SINGLELINE],
			floatVals[E_GFT_FILLRATIOX],
			floatVals[E_GFT_FILLRATIOY],
			floatVals[E_GFT_FILLDIR],
			floatVals[E_GFT_ALIGNX],
			floatVals[E_GFT_ALIGNY],
			floatVals[E_GFT_VALUE],
			floatVals[E_GFT_LAYER],
			floatVals[E_GFT_HOVERTYPE],
			floatVals[E_GFT_MAXDIMX],
			floatVals[E_GFT_MAXDIMY],
			_isFloating
		);
		
		//return curComp;
		
		if (_isFloating) {
			return &(floatingChildren.back());
		}
		else {
			return &(children.back());
		}
		
	}
void UIComponent::setOrigPos ()
                          {
		
		int i;
		
		fVector2 curPos = originPos;
		
		
		
		
		fVector2 availSpaceDim = resultDimInPixels;
		fVector2 totVals;
		
		totVals.x = 0.0f;
		totVals.y = 0.0f;
		
		for (i = 0; i < children.size(); i++) {
			
			if (fillDir == E_FILL_HORIZONTAL) {
				totVals.x += children[i].resultDimInPixels.x;
				totVals.y = max(totVals.y,children[i].resultDimInPixels.y); //getResultDimYClamped()
			}
			else {
				totVals.y += children[i].resultDimInPixels.y; //getResultDimYClamped()
				totVals.x = max(totVals.x,children[i].resultDimInPixels.x);
			}
			
			
		}
		
		availSpaceDim.x -= totVals.x;
		availSpaceDim.y -= totVals.y;
		
		switch (align.x) {
			case E_ALIGNH_LEFT:
				curPos.x += marginInPixels + borderInPixels + paddingInPixels;
			break;
			case E_ALIGNH_CENTER:
				curPos.x += availSpaceDim.x/2.0f;
			break;
			case E_ALIGNH_RIGHT:
				curPos.x += availSpaceDim.x;
				curPos.x -= marginInPixels + borderInPixels + paddingInPixels;
			break;
		}
		
		switch (align.y) {
			case E_ALIGNV_TOP:
				curPos.y += marginInPixels + borderInPixels + paddingInPixels;
			break;
			case E_ALIGNV_MIDDLE:
				curPos.y += availSpaceDim.y/2.0f;
			break;
			case E_ALIGNV_BOTTOM:
				curPos.y += availSpaceDim.y;
				curPos.y -= marginInPixels + borderInPixels + paddingInPixels;
			break;
		}
		
		if (fillDir == E_FILL_HORIZONTAL) {
			for (i = 0; i < children.size(); i++) {
				children[i].originPos.x = curPos.x;
				children[i].originPos.y = curPos.y;
				curPos.x += children[i].resultDimInPixels.x;
			}
		}
		else {
			for (i = 0; i < children.size(); i++) {
				children[i].originPos.x = curPos.x;
				children[i].originPos.y = curPos.y;
				curPos.y += children[i].resultDimInPixels.y; //getResultDimYClamped()
			}
		}
		
		
		for (i = 0; i < children.size(); i++) {
			children[i].setOrigPos();
		}
		
		
		for (i = 0; i < floatingChildren.size(); i++) {
			floatingChildren[i].setOrigPos();
		}
		
	}
void UIComponent::applyHeight ()
                           {
		fVector2 totalRatios;
		totalRatios.x = 0.0f;
		totalRatios.y = 0.0f;
		float availSpace = resultDimInPixels.y - (marginInPixels+borderInPixels+paddingInPixels)*2.0f; //getResultDimYClamped()
		int i;
		
		

		for (i = 0; i < children.size(); i++) {
			totalRatios.y += children[i].fillRatioDim.y;
			if (fillDir == E_FILL_HORIZONTAL) {
				
			}
			else {
				availSpace -= children[i].minDimInPixels.y;//minDimInPixels.y;//getMinDimYClamped();
			}
		}
		
		availSpace = max(availSpace,0.0f);
		
		
		if (totalRatios.y == 0.0f) {
			totalRatios.y = 1.0f;
		}
		
		
		for (i = 0; i < children.size(); i++) {
			
			if (fillDir == E_FILL_HORIZONTAL) {
				
				if (children[i].fillRatioDim.y == 0.0f) {
					children[i].resultDimInPixels.y = children[i].minDimInPixels.y;//minDimInPixels.y; //getMinDimYClamped();
				}
				else {
					
					
					children[i].resultDimInPixels.y = availSpace;
				}
			}
			else {
				children[i].resultDimInPixels.y =
					children[i].minDimInPixels.y + //minDimInPixels.y + //getMinDimYClamped() +
					(availSpace*children[i].fillRatioDim.y)/totalRatios.y;	
				
			}
		}
		
		for (i = 0; i < children.size(); i++) {
			children[i].applyHeight();	
		}
		
		for (i = 0; i < floatingChildren.size(); i++) {
			floatingChildren[i].applyHeight();
		}
		
	}
void UIComponent::applyWidth ()
                          {
		
		fVector2 totalRatios;
		totalRatios.x = 0.0f;
		totalRatios.y = 0.0f;
		float availSpace = resultDimInPixels.x - (marginInPixels+borderInPixels+paddingInPixels)*2.0f;
		int i;
		

		for (i = 0; i < children.size(); i++) {
			totalRatios.x += children[i].fillRatioDim.x;
			if (fillDir == E_FILL_HORIZONTAL) {
				availSpace -= children[i].minDimInPixels.x;
			}
			else {
				
			}
		}		
		availSpace = max(availSpace,0.0f);
		
		if (totalRatios.x == 0.0f) {
			totalRatios.x = 1.0f;
		}
		
		
		for (i = 0; i < children.size(); i++) {
			
			if (fillDir == E_FILL_HORIZONTAL) {
				
				
				
				children[i].resultDimInPixels.x =
					children[i].minDimInPixels.x +
					(availSpace*children[i].fillRatioDim.x)/totalRatios.x;	
			}
			else {
				
				if (children[i].fillRatioDim.x == 0.0f) {
					children[i].resultDimInPixels.x = children[i].minDimInPixels.x;
				}
				else {
					children[i].resultDimInPixels.x = availSpace;
				}
			}
					
		}
		
		
		for (i = 0; i < children.size(); i++) {
			children[i].applyWidth();	
		}
		
		for (i = 0; i < floatingChildren.size(); i++) {
			floatingChildren[i].applyWidth();
		}
		
	}
void UIComponent::gatherDirty (vector <UIComponent*> * dirtyVec)
                                                          {
		
		int i;
		
		if (isDirty) {
			dirtyVec->push_back(this);
		}
		else {
			for (i = 0; i < children.size(); i++) {
				children[i].gatherDirty(dirtyVec);
			}
			for (i = 0; i < floatingChildren.size(); i++) {
				floatingChildren[i].gatherDirty(dirtyVec);
			}
		}
		
	}
void UIComponent::clearDirty ()
                          {
		
		int i;
		
		isDirty = false;
		
		for (i = 0; i < children.size(); i++) {
			children[i].clearDirty();
		}
		for (i = 0; i < floatingChildren.size(); i++) {
			floatingChildren[i].clearDirty();
		}
	}
void UIComponent::layout ()
                      {
		
		int i;
		
		
		// if (isDirty) {
		// 	isDirty = false;
		// }
		// else {
		// 	return;
		// }
		
		
		
		getMinWidth();
		applyWidth();
		getMinHeight();
		applyHeight();
		setOrigPos();
		
		
		
	}
void UIComponent::updateOffset ()
                            {
		totOffset.x = floatOffset.x + dragOffset.x + scrollOffset.x;
		totOffset.y = floatOffset.y + dragOffset.y + scrollOffset.y;
		return;
	}
void UIComponent::updateValue (float x, float y)
                                           {
		
		
		
		float hoverBuffer = 4.0f;
		float tempValue;
		
		UIComponent* curParent = getParent();
		
		
		UIComponent* highestCont;
		
		if (dragging) {
			highestCont = getHighestCont(this, 0);
			
			if (highestCont->floatingChildren.size() > 0) {
				highestCont = &(highestCont->floatingChildren[0]);
			}
			
			highestCont->dragOffset.x = lastDrag.x + (x - dragStart.x);
			highestCont->dragOffset.y = lastDrag.y + (y - dragStart.y);
			
		}
		
		if ( (hoverType == E_HT_ONSELECTED) || (curParent == NULL) ) {
			
		}
		else {
			dragOffset = curParent->dragOffset;			
		}
		
		
		if ((maxDimInPixels.y == 0)&&(curParent != NULL)) {
			scrollOffset.y = curParent->scrollOffset.y;
		}
		else {
			scrollOffset.y += (targScrollOffset.y-scrollOffset.y)/16.0f;
			
		}
		
		
		
		
		
		
		
		
		
		
		switch (hoverType) {
			case E_HT_NORMAL:
				if (curParent != NULL) {
					floatOffset = curParent->floatOffset;
					visible = curParent->visible;
					
					
				}
			break;
			case E_HT_TOOLTIP:
			case E_HT_TOOLTIP_VALUE:
				//curParent->floatOffset.x + 
				floatOffset.x = x + hoverBuffer - dragOffset.x; 
				floatOffset.y = curParent->floatOffset.y + curParent->originPos.y + curParent->resultDimInPixels.y + hoverBuffer; //getResultDimYClamped()
				visible = curParent->overSelf;
				
				if ((hoverType == E_HT_TOOLTIP_VALUE)&&visible) {
					
					children[0].setText(f__s(curParent->value));
				}
				
			break;
			case E_HT_ONSELECTED:
				//curParent->floatOffset.x + 
				floatOffset.x = curParent->totOffset.x + curParent->originPos.x + curParent->resultDimInPixels.x;
				floatOffset.y = curParent->totOffset.y + curParent->originPos.y;
				visible = (curParent->value == 1.0f)&&(curParent->visible);
			break;
						
		}
		
		updateOffset();
		
		
		
		
		if ((maxDimInPixels.y == 0)&&(curParent != NULL)) {
			scrollMaskY = curParent->scrollMaskY;
		}
		else {
			scrollMaskY.x = originPos.y + marginInPixels;
			scrollMaskY.y = originPos.y +  getResultDimYClamped() - marginInPixels; //getResultDimYClamped()
			
			scrollMaskY.x += totOffset.y-scrollOffset.y;
			scrollMaskY.y += totOffset.y-scrollOffset.y;
			
			scrollMaskY.x /= singleton->guiWinH;
			scrollMaskY.y /= singleton->guiWinH;
			scrollMaskY.x = ((1.0f-scrollMaskY.x) - 0.5f)*2.0f;
			scrollMaskY.y = ((1.0f-scrollMaskY.y) - 0.5f)*2.0f;			
		}
		
		
		
		
		
		float hbxMin = hitBounds.xMin + totOffset.x;
		float hbxMax = hitBounds.xMax + totOffset.x;
		
		if (wasHit&&(guiClass == E_GT_SLIDER)) {
			
			if (divisions == 1.0f) {
				// toggle button, do nothing
			}
			else {
				tempValue = clampfZO((x-hbxMin)/(hbxMax-hbxMin));
				if (divisions == 0.0f) {
					setValue(
						tempValue
					);
				}
				else {
					
					setValue(
						floor(tempValue*divisions)/divisions
					);
				}
				
			}
		}
	}
void UIComponent::runReport ()
                         {
		
		int i;
		
		//cout << overSelf << " " << text << "\n";
				
		for (i = 0; i < children.size(); i++) {
			children[i].runReport();
		}
		for (i = 0; i < floatingChildren.size(); i++) {
			floatingChildren[i].runReport();
		}
	}
void UIComponent::clearOver ()
                         {
		int i;
		overSelf = false;
		
		for (i = 0; i < children.size(); i++) {
			children[i].clearOver();
		}
		for (i = 0; i < floatingChildren.size(); i++) {
			floatingChildren[i].clearOver();
		}
		
	}
bool UIComponent::findMaxLayer (float x, float y, float xTransformed, float yTransformed)
                                                                                    {
		
		
		int i;

		overSelf = (
			(x < (hitBounds.xMax+totOffset.x)) &&
			(x > (hitBounds.xMin+totOffset.x)) &&
			(y < (hitBounds.yMax+totOffset.y)) &&
			(y > (hitBounds.yMin+totOffset.y))
		) && visible;
		
		
		if (maxDimInPixels.y == 0) {
			
		}
		else {
			if (
				(yTransformed > scrollMaskY.x) || 
				(yTransformed < scrollMaskY.y)
			) {
				overSelf = false;
				overChild = false;
				return false;
			}
		}
		
		
		
		
		
		
		
		overChild = false;
		
		for (i = 0; i < children.size(); i++) {
			overChild = overChild||children[i].findMaxLayer(x,y,xTransformed,yTransformed);
		}
		for (i = 0; i < floatingChildren.size(); i++) {
			overChild = overChild||floatingChildren[i].findMaxLayer(x,y,xTransformed,yTransformed);
		}
		
		if (
			overSelf &&
			visible &&
			hasBackground &&
			(!overChild) &&
			(layer >= singleton->maxLayerOver)
		) {
			singleton->maxLayerOver = layer;
		}
		
		return overSelf;
	}
void UIComponent::testOver (float x, float y)
                                        {
		
		int i;
		
		bool lastOver = mouseOver;
		
		for (i = 0; i < children.size(); i++) {
			children[i].testOver(x,y);
		}
		for (i = 0; i < floatingChildren.size(); i++) {
			floatingChildren[i].testOver(x,y);
		}
		
		mouseOver = 
			overSelf &&
			visible &&
			hasBackground &&
			(!overChild) &&
			(layer >= singleton->maxLayerOver);
		
		
		if ((mouseOver != lastOver)&&(!(singleton->dragging))) {
			if (mouseOver) {
				singleton->dispatchEvent(
					GLUT_NO_BUTTON,
					GLUT_OVER,
					x,
					y,
					this
				);
				
				
			}
			else {
				singleton->dispatchEvent(
					GLUT_NO_BUTTON,
					GLUT_OUT,
					x,
					y,
					this
				);
			}
		}
		else {
			if (wasHit&&(guiClass == E_GT_SLIDER)) {
				
				if (divisions == 1.0f) {
					// toggle button, do nothing
				}
				else {
					singleton->dispatchEvent(
						GLUT_NO_BUTTON,
						GLUT_CHANGING,
						x,
						y,
						this
					);
				}
			}
		}
		
		
		
		updateValue(x, y);

	}
bool UIComponent::testHit (int button, int state, float x, float y)
                                                              {
		
		float wheelDelta = 0.0f;
		
		
		UIComponent* curParent = getParent();
		
		int i;
		bool hitChild = false;
		float lastValue = value;
		float tempValue;
		
		
		
		
		if (button == GLUT_LEFT_BUTTON) {
			if (state == GLUT_DOWN) { // MOUSE DOWN
				if (mouseOver) {
					
					if (visible) {
						
						
						cout << "minDimInPixels.x " << minDimInPixels.x << "\n";
						cout << "minDimInPixels.y " << minDimInPixels.y << "\n";
						cout << "maxDimInPixels.x " << maxDimInPixels.x << "\n";
						cout << "maxDimInPixels.y " << maxDimInPixels.y << "\n";
						cout << "resultDimInPixels.x " << resultDimInPixels.x << "\n";
						cout << "resultDimInPixels.y " << resultDimInPixels.y << "\n";
						
						cout << "resultDimInPixelsClamped.y " << getResultDimYClamped() << "\n";
						cout << "minDimInPixelsClamped.y " << getMinDimYClamped() << "\n\n\n";
						
						
						
						if (guiClass != E_GT_HOLDER) {
							wasHit = true;
						}
						
						dragging = (guiClass == E_GT_MENUBAR);
						if (dragging) {
							singleton->dragging = true;
						}
						
						dragStart.x = x;
						dragStart.y = y;
						
					}
					
					
				}

				mouseDown = true;
			}
			else { // MOUSE UP
				
				
				if (dragging) {
					lastDrag.x += (x - dragStart.x);
					lastDrag.y += (y - dragStart.y);
				}
				dragging = false;
				singleton->dragging = false;
				
				if (mouseOver&&wasHit) {
					
					switch (guiClass) {
						case E_GT_HOLDER:
							
						break;
						case E_GT_SLIDER:
							if (divisions == 1.0f) {
								setValue(1.0f-value);
							}
						break;
						case E_GT_BUTTON:
							
						break;
						case E_GT_RADIO:
							
							tempValue = 1.0f-value;
							
							if (singleton->bShift) {
								
							}
							else {
								for (i = 0; i < curParent->children.size(); i++) {
									if (curParent->children[i].guiClass == E_GT_RADIO) {
										curParent->children[i].setValue(0.0f);
									}
								}
							}
							
							setValue(tempValue);
							
						break;
					}
					
				}


				mouseDown = false;
			}
		}
		else {
				if ( (button == 3) || (button == 4) ) {
					
					
					if (visible && overSelf) {
						if (maxDimInPixels.y != 0) {
							
							if (button == 3) {
								wheelDelta = 1.0f;
								// wheel up
							}
							else {
								wheelDelta = -1.0f;
								// wheel down
							}
							
							
							targScrollOffset.y += wheelDelta*20.0f;
							
							targScrollOffset.y = clampf(targScrollOffset.y, -(resultDimInPixels.y-maxDimInPixels.y), 0.0f);
							
							return true;
						}	
					}
					
					
				}
		}

		updateValue(x, y);
		
		for (i = 0; i < children.size(); i++) {
			hitChild = hitChild||children[i].testHit(button, state, x, y);
		}
		
		for (i = 0; i < floatingChildren.size(); i++) {
			hitChild = hitChild||floatingChildren[i].testHit(button, state, x, y);
		}
		
		
		if ( (!hitChild)&&(mouseOver) ) {
			// deepest node
			
			singleton->dispatchEvent(button, state, x, y, this);
		}
		
		bool finalRes = wasHit||hitChild;
		if ((state == GLUT_UP)) { //&&(wheelDelta==0.0f)
			wasHit = false;
		}
		

		return finalRes;
	}
UIComponent * UIComponent::getHighestCont (UIComponent * curNode, int genCount)
                                                                        {
		UIComponent* curParent = curNode->getParent();
		
		if (
			(curParent == NULL) || 
			(
				(genCount > 0) &&
				(curNode->floatingChildren.size() > 0)
			)
			
		) {
			return curNode;
		}
		else {
			return getHighestCont(curParent, genCount+1);
		}
		
	}
void UIComponent::setText (string _text)
                                   {
		
		UIComponent* highestCont;
		
		if (_text.compare(text) == 0) {
			// text unchanged, do nothing
		}
		else {
			text = _text;
			
			highestCont = getHighestCont(this, 0);
			highestCont->isDirty = true;
			singleton->guiDirty = true;
			
		}
		
		
	}
void UIComponent::updateVecs ()
                          {
		
		
		
		lineVec.clear();
		wordVec.clear();

		lineVec = split(text, '\n');

		int i;
		int j;

		for (i = 0; i < lineVec.size(); i++) {
			wordVec.push_back(std::vector<string>());
			wordVec[i] = split(lineVec[i], ' ');
		}
		
	}
void UIComponent::renderAll ()
                         {
		int i;
		
		renderText(false);
		
		for (i = 0; i < children.size(); i++) {
			children[i].renderAll();
		}
		for (i = 0; i < floatingChildren.size(); i++) {
			floatingChildren[i].renderAll();
		}
	}
void UIComponent::updateSS ()
                        {
		int i;
		
		resSS.update(mouseOver, mouseDown);
		
		for (i = 0; i < children.size(); i++) {
			children[i].updateSS();
		}
		for (i = 0; i < floatingChildren.size(); i++) {
			floatingChildren[i].updateSS();
		}
		
	}
float UIComponent::getLineOffset (int lineCount)
                                           {
		
		switch (align.x) {
			case E_ALIGNH_LEFT:
				return 0.0f;
			break;
			case E_ALIGNH_CENTER:
				return (resultDimInPixels.x - (linePitchVec[lineCount]+(marginInPixels+borderInPixels+paddingInPixels)*2.0f) )/2.0f;
			break;
			case E_ALIGNH_RIGHT:
				return (
					resultDimInPixels.x -
					(
						(linePitchVec[lineCount]) +
						(marginInPixels+borderInPixels+paddingInPixels)
					)
				);
			break;
			default:
				return 0.0f;
			break;
		}
		
		
	}
float UIComponent::lengthOfWord (int i, int j, bool isIcon)
                                                      {
		int numChars = wordVec[i][j].size();
		int k;
		float tot = 0.0f;
		
		if (isIcon) {
			return curFontIcons->maxWidth;
		}
		
		for (k = 0; k < numChars; k++) {
			tot += curFont->charVals[ wordVec[i][j][k] ].consumedW*curFont->fontScale;
		}
		
		return tot;
		
	}
int UIComponent::maxCharsForWord (int i, int j)
                                          {
		int numChars = wordVec[i][j].size();
		
		float tot = 0.0f;
		
		int k = 0;
		while (
			(tot < spaceForCharsInPixels) &&
			(k < wordVec[i][j].size())
		) {
			tot += curFont->charVals[ wordVec[i][j][k] ].consumedW;
			k++;
		}
		
		return k;
	}
void UIComponent::renderText (bool getDimensions)
                                            {
		
		
		
		int curSize = 0;
		int i;
		int j;
		int k;
		int curChar;
		int lineCount = 0;
		
		bool isRendering = !getDimensions;
		bool isIcon = false;

		fVector2 caretPos;
		fVector2 offsetPos;
		
		float vspace = resultDimInPixels.y - textDimInPixels.y; //getResultDimYClamped()
		
		
		
		caretPos.x = 0.0f;
		caretPos.y = 0.0f;
		
		if (getDimensions) {
			linePitchVec.clear();
		}
		else {
			offsetPos.x = originPos.x + marginInPixels + borderInPixels + paddingInPixels;
			
			switch (align.y) {
				case E_ALIGNV_TOP:
					offsetPos.y = originPos.y + marginInPixels + borderInPixels + paddingInPixels;
				break;
				case E_ALIGNV_MIDDLE:
					offsetPos.y = originPos.y + vspace/2.0f;
					
				break;
				case E_ALIGNV_BOTTOM:
					offsetPos.y = originPos.y + vspace - (marginInPixels + borderInPixels + paddingInPixels);
				break;
			}
		}
		
		
		float maxCaretPos = 0;

		//float charCount = 0;

		float maxSize;

		if (isRendering) {
			hitBounds.xMin = originPos.x + marginInPixels;
			hitBounds.xMax = originPos.x + resultDimInPixels.x - marginInPixels;
			hitBounds.yMin = originPos.y + marginInPixels;
			hitBounds.yMax = originPos.y + resultDimInPixels.y - marginInPixels; //getResultDimYClamped()
			
			
			if (contOnStack) {
				
			}
			else {
				contOnStack = true;
				singleton->guiLayers[layer].push_back(&thisUICont);
				//thisUICont.locked = false;
			}
			
			
			if (thisUICont.charVec.size() > 0) {
				thisUICont.charVec.clear();
			}
			
			
			
			thisUICont.uiComp = this;
			thisUICont.bg.hitBounds = hitBounds;
			thisUICont.bg.cs = NULL;
			thisUICont.bg.fontId = -1;
			
			if (hasBackground) {
				thisUICont.bg.fontId = 0;
			}
			
		}

		//lines
		for (i = 0; i < wordVec.size(); i++) {
			
			caretPos.x = 0.0f;
			if (isRendering) {
				caretPos.x += getLineOffset(lineCount);
			}
			lineCount++;

			//words in line
			for (j = 0; j < wordVec[i].size(); j++) {
				curSize = wordVec[i][j].size();
				isIcon = (wordVec[i][j][curSize-1] == '&') && (curSize >= 2);
				
				//if word won't fit, increment line
				if ( (caretPos.x + lengthOfWord(i,j,isIcon)) + curFont->maxWidth >= spaceForCharsInPixels ) {
					//charCount = 0;
					
					if (getDimensions) {
						linePitchVec.push_back(caretPos.x);
					}
					maxCaretPos = max(caretPos.x, maxCaretPos);
					caretPos.x = 0.0f;
					if (isRendering) {
						caretPos.x += getLineOffset(lineCount);
					}
					
					lineCount++;
					caretPos.y += (curFont->fontHeight*curFont->fontScale + spacing.y);
				}
				
				
				
				
				if (isIcon) {
					// is an icon
					
					curChar = atoi(wordVec[i][j].c_str());
					
					if (isRendering) {
						thisUICont.charVec.push_back(Singleton::UIQuad());
						curQuad = &(thisUICont.charVec.back());
						curQuad->cs = &(curFontIcons->charVals[ curChar ]);
						curQuad->fontId = EFW_ICONS;
						curQuad->hitBounds.xMin = caretPos.x+offsetPos.x;
						curQuad->hitBounds.yMin = caretPos.y+offsetPos.y;
					}
					
					
					
					caretPos.x += curFontIcons->maxWidth*curFontIcons->fontScale;
					
					
					
					// renderCharAt(
					// 	&(curFontIcons->charVals[ curChar ]),
					// 	curFontIcons,
					// 	caretPos.x+offsetPos.x,
					// 	caretPos.y+offsetPos.y
					// );
					
				}
				else {
					// is characters
					
					//if word won't fit on line, limit chars
					maxSize = maxCharsForWord(i,j);
					
					for (k = 0; k < maxSize; k++) {
						curChar = wordVec[i][j][k];
						if (isRendering) {
							
							thisUICont.charVec.push_back(Singleton::UIQuad());
							curQuad = &(thisUICont.charVec.back());
							curQuad->fontId = EFW_TEXT;
							curQuad->cs = &(curFont->charVals[ curChar ]);
							curQuad->hitBounds.xMin = caretPos.x+offsetPos.x;
							curQuad->hitBounds.yMin = caretPos.y+offsetPos.y;
							
							// renderCharAt(
							// 	&(curFont->charVals[ curChar ]),
							// 	curFont,
							// 	caretPos.x+offsetPos.x,
							// 	caretPos.y+offsetPos.y
							// );
						}
						caretPos.x += (curFont->charVals[ curChar ].consumedW*curFont->fontScale + spacing.x);
						//charCount++;
					}
	
				}
				
				//chars in word
				
				
				
				// render a space
				
				curChar = ' ';
				if (
					//(i == wordVec.size()-1) && 
					(j == wordVec[i].size()-1)
				) {
					//end of line, no space
				}
				else {
					if (caretPos.x + curFont->maxWidth*curFont->fontScale < spaceForCharsInPixels) {
						
						if (isRendering) {
							
							thisUICont.charVec.push_back(Singleton::UIQuad());
							curQuad = &(thisUICont.charVec.back());
							curQuad->fontId = EFW_TEXT;
							curQuad->cs = &(curFont->charVals[ curChar ]);
							curQuad->hitBounds.xMin = caretPos.x+offsetPos.x;
							curQuad->hitBounds.yMin = caretPos.y+offsetPos.y;
							
							// renderCharAt(
							// 	&(curFont->charVals[ curChar ]),
							// 	curFont,
							// 	caretPos.x+offsetPos.x,
							// 	caretPos.y+offsetPos.y
							// );
						}
						
						caretPos.x += (curFont->charVals[ curChar ].consumedW*curFont->fontScale + spacing.x);
						// /charCount++;
						
					} 
				}
				

			}
			//charCount = 0;
			
			if (getDimensions) {
				linePitchVec.push_back(caretPos.x);
			}
			
			maxCaretPos = max(caretPos.x, maxCaretPos);
			caretPos.y += (curFont->fontHeight*curFont->fontScale + spacing.y);

		}

		if (getDimensions) {
			textDimInPixels.x = maxCaretPos - spacing.x;
			textDimInPixels.y = caretPos.y - spacing.y;
		}
		

	}
#undef LZZ_INLINE
 
// f00330_gamegui.h
//

#include "f00330_gamegui.e"
#define LZZ_INLINE inline
GameGUI::GameGUI ()
                  {
		
	}
void GameGUI::init (Singleton * _singleton)
                                         {

		singleton = _singleton;
		isReady = false;
		isLoaded = false;
		
		nodeCount = 0;
		baseComp = new UIComponent();
		baseComp->init(
			singleton,
			-1,
			nodeCount,
			0,
			
			NULL,
			
			"",
			"",
			"defaultSS",

			E_GT_HOLDER,
			0.0f,
			false
		);
		nodeCount++;
		
		
		baseComp->resultDimInPixels.x = singleton->guiWinW;
		baseComp->resultDimInPixels.y = singleton->guiWinH;
		
		
	}
void GameGUI::getJVNodeByString (JSONValue * rootNode, JSONValue * * resultNode, string stringToSplit)
                                                                                                  {
		cout << "getJVNodeByString(" << stringToSplit <<  ")\n";
			
		int i;
		*resultNode = rootNode;
		
		
		vector<string> splitStrings = split(stringToSplit, '.');
		
		for (i = 0; i < splitStrings.size(); i++) {
			cout << splitStrings[i] << "\n";
			
			if ( (*resultNode)->HasChild(splitStrings[i]) ) {
				*resultNode = (*resultNode)->Child(splitStrings[i]);
			}
			else {
				*resultNode = NULL;
				return;
			}
			
		}
		
	}
UIComponent * GameGUI::findNodeById (int _id)
                                           {
		return baseComp->findNodeById(_id);
	}
void GameGUI::addChildFromJSON (JSONValue * jv, UIComponent * curParent, bool isFloating)
          {
		int i;
		int j;
		int curIcon = 0;
		
		JSONValue* curTempl = NULL;
		
		
	
		if (
			jv->HasChild("template")
		) {
			if (
				jvTemplates->HasChild(jv->Child("template")->string_value)
			) {
				
				curTempl = jvTemplates->Child(jv->Child("template")->string_value);
			}
			else {
				cout << "invalid template \n";// << jv->Child("template")->string_value << "\n";
			}
		}
		
		
		for (i = 0; i < E_GST_LENGTH; i++) {
			guiStringValues[i] = "";
		}
		for (i = 0; i < E_GFT_LENGTH; i++) {
			guiFloatValues[i] = 0.0f;
		}
		
		guiFloatValues[E_GFT_HASBACKGROUND] = 1.0;
		guiFloatValues[E_GFT_SINGLELINE] = 1.0;
		guiStringValues[E_GST_SS] = "defaultSS";
		
		
		for (j = 0; j < 2; j++) {
			if (curTempl != NULL) {
				for (i = 0; i < E_GST_LENGTH; i++) {
					if (
						curTempl->HasChild(guiStringTypes[i])
					) {
						guiStringValues[i] = curTempl->Child(guiStringTypes[i])->string_value;
					}
				}
				for (i = 0; i < E_GFT_LENGTH; i++) {
					if (
						curTempl->HasChild(guiFloatTypes[i])
					) {
						guiFloatValues[i] = curTempl->Child(guiFloatTypes[i])->number_value;
					}
				}
			}
			curTempl = jv;
		}
		
		
		guiFloatValues[E_GFT_LAYER] = max(guiFloatValues[E_GFT_LAYER],(float)(curParent->layer));
		
		UIComponent* newParent = curParent->addChild(
			curParent->nodeId,
			nodeCount,
			guiStringValues,
			guiFloatValues,
			isFloating,
			jv
		);
		nodeCount++;
		
		
		int numChildren = 0;
		int numFloatingChildren = 0;
		int numDataChildren = 0;
		int numFilters = 0;
		JSONValue* jvChildren = NULL;
		JSONValue* jvFloatingChildren = NULL;
		JSONValue* jvChildTemplate = NULL;
		JSONValue* jvFilter = NULL;
		JSONValue* curFilter = NULL;
		
		JSONValue* jvData = NULL;
		JSONValue* jvDataRoot = NULL;
		JSONValue* curData = NULL;
		
		
		if (jv->HasChild("children")) {
			jvChildren = jv->Child("children");
			numChildren = jvChildren->CountChildren();
		}
		for (i = 0; i < numChildren; i++) {
			addChildFromJSON(jvChildren->Child(i),newParent, false);
		}
		
		
		if (jv->HasChild("floatingChildren")) {
			jvFloatingChildren = jv->Child("floatingChildren");
			numFloatingChildren = jvFloatingChildren->CountChildren();
		}
		for (i = 0; i < numFloatingChildren; i++) {
			addChildFromJSON(jvFloatingChildren->Child(i),newParent,true);
		}
		
		
		bool doProc = false;
		bool isInternal = false;
		int totCount = 0;
		E_GUI_CHILD_TYPES curCT = E_GCT_LENGTH;;
		
		
		if (jv->HasChild("childType")) {
			tempStrings[E_GDS_CHILD_TYPE] = jv->Child("childType")->string_value;
			
			
			if (jv->HasChild("isInternal")) {
				if (jv->Child("isInternal")->number_value != 0 ) {
					// use an internally generated JSON node
					isInternal = true;
				}
				else {
					// todo: load JSON file
				}
			}
			
			if (jv->HasChild("whereAllEqual")) {
				jvFilter = jv->Child("whereAllEqual");
				numFilters = jvFilter->CountChildren();
			}
			else {
				jvFilter = NULL;
				numFilters = 0;
			}
				
			
			
			if (jv->HasChild("dataSource")) {
				tempStrings[E_GDS_DATA_SOURCE] = jv->Child("dataSource")->string_value;
				
				if (isInternal) {
					if (jv->HasChild("dataFile")) {
						tempStrings[E_GDS_DATA_FILE] = jv->Child("dataFile")->string_value;
						jvDataRoot = (singleton->internalJSON[tempStrings[E_GDS_DATA_FILE]]).jv;
					}
					
					
				}
				else {
					jvDataRoot = jvRoot;
				}
				
				if (jvDataRoot != NULL) {
					getJVNodeByString(jvDataRoot, &jvData, tempStrings[E_GDS_DATA_SOURCE]);
					
					numDataChildren = jvData->CountChildren();
					if (jv->HasChild("childTemplate")) {
						jvChildTemplate = jv->Child("childTemplate");
					}
				}
			}
			
			
			if ((jvData != NULL)&&(jvChildTemplate != NULL)) {
				
				
				if (compChildStr("inventoryItem")) {
					curCT = E_GCT_INV_ITEM;
				}
				if (compChildStr("shaderParams")) {
					curCT = E_GCT_SHADER_PARAM;
				}
				
				//////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////
				
				
				
				
				for (i = 0; i < numDataChildren; i++) {
					
					curData = jvData->Child(i);
					
					doProc = true;
					if (jvFilter != NULL) {
						
						
						for (j = 0; j < numFilters; j++) {
							curFilter = jvFilter->Child(j);
							
							if ( curData->Child(curFilter->Child(0)->string_value)->IsNumber() ) {
								if (
									curData->Child(curFilter->Child(0)->string_value)->number_value !=
									curFilter->Child(1)->number_value
								) {
									doProc = false;
								}
							}
							else {
								// todo: string support
							}
						}
						
						
					}
					
					if (doProc) {
						switch (curCT) {
							case E_GCT_INV_ITEM:
								tempStrings[E_GDS_CHILD_NAME] = curData->Child("name")->string_value;
								
								curIcon = jvRoot->
									Child("itemDefs")->
									Child(tempStrings[E_GDS_CHILD_NAME])->
									Child("iconNum")->
									number_value;
								
								jvChildTemplate->
									Child("floatingChildren")->
									Child(0)->
									Child("children")->
									Child(0)->
									Child("label")->
									string_value = 
										jvRoot->
										Child("itemDefs")->
										Child(tempStrings[E_GDS_CHILD_NAME])->
										Child("class")->
										string_value;
								
								tempStrings[E_GDS_MATERIAL] = curData->Child("mat")->string_value;
								if (tempStrings[E_GDS_MATERIAL].compare("none") == 0) {
									tempStrings[E_GDS_MATERIAL] = "";
								}
								
								jvChildTemplate->Child("label")->string_value = 
									i__s(curIcon) +
									"& " +
									tempStrings[E_GDS_MATERIAL] +
									" " +
									tempStrings[E_GDS_CHILD_NAME];
							break;
							case E_GCT_SHADER_PARAM:
									
								jvChildTemplate->Child("label")->string_value = 
									curData->Child("shaderName")->string_value +
									"." +
									curData->Child("paramName")->string_value;
								
								jvChildTemplate->Child("uid")->string_value = curData->Child("uid")->string_value;
									
								jvChildTemplate->Child("callbackData")->Child("shaderName")->string_value = 
									curData->Child("shaderName")->string_value;
								jvChildTemplate->Child("callbackData")->Child("paramName")->string_value = 
									curData->Child("paramName")->string_value;
									
							break;
							case E_GCT_LENGTH:
								
							break;
						}
						
						
						
						
						
						// copy template to new child
						jv->Child("children")->array_value.push_back(
							JSON::Parse(jvChildTemplate->Stringify().c_str())
						);
						
						
						//PROBLEM
						
						addChildFromJSON(jv->Child("children")->Child(totCount),newParent,false); //jvChildTemplate //jv->Child("children")->Child(i)
						
						totCount++;
						
						
					}
					
					
				
				}
			}
			
			
			
			
			
			
		}
		
		
	}
void GameGUI::guiFromJSON (JSONValue * jv)
                                        {
		
		isLoaded = false;
		isReady = false;
		
		
		int i;
		
		nodeCount = 1;
		baseComp->children.clear();
		baseComp->floatingChildren.clear();
		
		
		for (i = 0; i < MAX_UI_LAYERS; i++) {
			singleton->guiLayers[i].clear();
		}
		
		jvRoot = jv;
		jvTemplates = jv->Child("templates");
		jvSounds = jv->Child("sounds");
		
		
		addChildFromJSON(
			jv->Child(jv->Child("curMenu")->string_value), //"inventoryMenu" "shaderParamMenu"
			baseComp,
			false
		);
		
		baseComp->isDirty = true;
		isReady = true;
		isLoaded = true;
	}
void GameGUI::doRefresh ()
                         {
		
		int i;
		
		//if (singleton->guiDirty) {
			
			//cout << "guiDirty\n";
			
			singleton->guiDirty = false;
			dirtyVec.clear();
			baseComp->gatherDirty(&dirtyVec);
			baseComp->clearDirty();
			
			for (i = 0; i < dirtyVec.size(); i++) {
				dirtyVec[i]->layout();
			}
			
			//dirtyVec.clear();
			baseComp->renderAll();
		//}
		
		
	}
void GameGUI::testOver (int x, int y)
                                    {
		singleton->maxLayerOver = -1;
		
		
		mouseTrans.x = x;
		mouseTrans.y = y;		
		mouseTrans.x /= singleton->guiWinW;
		mouseTrans.y /= singleton->guiWinH;
		mouseTrans.x = ((1.0f-mouseTrans.x) - 0.5f)*2.0f;
		mouseTrans.y = ((1.0f-mouseTrans.y) - 0.5f)*2.0f;		
		
		
		baseComp->clearOver();
		baseComp->findMaxLayer(x, y, mouseTrans.x, mouseTrans.y);
		baseComp->testOver(x, y);
	}
bool GameGUI::testHit (int button, int state, int x, int y)
                                                          {
		return baseComp->testHit(button, state, x, y);
	}
UIComponent * GameGUI::findNodeByString (string _uid)
                                                   {
		return baseComp->findNodeByString(_uid);
	}
void GameGUI::renderCharAt (UIComponent * uiComp, CharStruct * cs, FontWrapper * activeFont, float px, float py, float shadowOffset)
          {
		
		StyleSheetResult* resSS = &(uiComp->resSS);
		
		float sampX = cs->sampX;
		float sampY = cs->sampY;
		float sampW = cs->sampW;
		float sampH = cs->sampH;
		float offsetX = (cs->offsetX)*activeFont->fontScale;
		float offsetY = ((activeFont->fontHeight - cs->offsetY) + activeFont->descender)*activeFont->fontScale;
		float sourceW = activeFont->fontImage->width;
		float sourceH = activeFont->fontImage->height;
		
		fBoundingBox destPos;
		fBoundingBox srcPos;
		
		

		destPos.xMin = (px+offsetX)+uiComp->totOffset.x;
		destPos.yMin = (py+offsetY)+uiComp->totOffset.y+shadowOffset;
		destPos.xMax = (px+offsetX+sampW*activeFont->fontScale)+uiComp->totOffset.x;
		destPos.yMax = (py+offsetY+sampH*activeFont->fontScale)+uiComp->totOffset.y+shadowOffset;
		
		srcPos.xMin = (sampX)/sourceW;
		srcPos.yMin = (sourceH-(sampY+sampH))/sourceH;
		srcPos.xMax = (sampX+sampW)/sourceW;
		srcPos.yMax = ( sourceH-sampY )/sourceH;
		
		

		float x0 = destPos.xMin/singleton->guiWinW;
		float x1 = destPos.xMax/singleton->guiWinW;
		float y0 = destPos.yMin/singleton->guiWinH;
		float y1 = destPos.yMax/singleton->guiWinH;

		x0 = (x0-0.5f)*2.0f;
		x1 = (x1-0.5f)*2.0f;
		y0 = ((1.0f-y0) - 0.5f)*2.0f;
		y1 = ((1.0f-y1) - 0.5f)*2.0f;

		float iconVal = 0.0;
		if (activeFont->isIcons) {
			iconVal = 1.0f;
		}
		
		
		
		
		//dimensions
		glMultiTexCoord4f(1, sampW, sampH, 0.0f, 0.0f);

		glMultiTexCoord4f(4, 1.0f, 1.0f, 1.0f, 1.0f);
		glMultiTexCoord4f(5, iconVal, shadowOffset, uiComp->scrollMaskY.x, uiComp->scrollMaskY.y);
		//border color
		glMultiTexCoord4f(6, 1.0f, 1.0f, 1.0f, 1.0f);
		//misc
		glMultiTexCoord4f(7, 0.0f, 0.0f, 0.0f, 0.0f);
		

		glMultiTexCoord4f(2, resSS->props[E_SS_BGCOLTEXT1_R], resSS->props[E_SS_BGCOLTEXT1_G], resSS->props[E_SS_BGCOLTEXT1_B], resSS->props[E_SS_BGCOLTEXT1_A]);
		glMultiTexCoord4f(3, resSS->props[E_SS_FGCOLTEXT1_R], resSS->props[E_SS_FGCOLTEXT1_G], resSS->props[E_SS_FGCOLTEXT1_B], resSS->props[E_SS_FGCOLTEXT1_A]);
		
		
		glMultiTexCoord4f(0, srcPos.xMin, srcPos.yMin, 0.0f, 1.0f);
		glVertex3f (  x0, y1, -1.0f );
		glMultiTexCoord4f(0, srcPos.xMax, srcPos.yMin, 1.0f, 1.0f);
		glVertex3f (  x1, y1, -1.0f );

		glMultiTexCoord4f(2, resSS->props[E_SS_BGCOLTEXT0_R], resSS->props[E_SS_BGCOLTEXT0_G], resSS->props[E_SS_BGCOLTEXT0_B], resSS->props[E_SS_BGCOLTEXT0_A]);
		glMultiTexCoord4f(3, resSS->props[E_SS_FGCOLTEXT0_R], resSS->props[E_SS_FGCOLTEXT0_G], resSS->props[E_SS_FGCOLTEXT0_B], resSS->props[E_SS_FGCOLTEXT0_A]);		

		glMultiTexCoord4f(0, srcPos.xMax, srcPos.yMax, 1.0f, 0.0f);
		glVertex3f (  x1, y0, -1.0f );
		glMultiTexCoord4f(0, srcPos.xMin, srcPos.yMax, 0.0f, 0.0f);
		glVertex3f (  x0, y0, -1.0f );

	}
void GameGUI::renderQuad (UIComponent * uiComp, fBoundingBox fbb, float shadowOffset)
          {

		StyleSheetResult* resSS = &(uiComp->resSS);
		
		
		
		
		
		
		
		
		
		float x0 = (fbb.xMin+uiComp->totOffset.x)/singleton->guiWinW;
		float x1 = (fbb.xMax+uiComp->totOffset.x)/singleton->guiWinW;
		float y0 = (fbb.yMin+uiComp->totOffset.y+shadowOffset)/singleton->guiWinH;
		float y1 = (fbb.yMax+uiComp->totOffset.y+shadowOffset)/singleton->guiWinH;

		x0 = (x0-0.5f)*2.0f;
		x1 = (x1-0.5f)*2.0f;
		y0 = ((1.0f-y0) - 0.5f)*2.0f;
		y1 = ((1.0f-y1) - 0.5f)*2.0f;

		
		//dimensions
		glMultiTexCoord4f(1, fbb.xMax-fbb.xMin, fbb.yMax-fbb.yMin, resSS->props[E_SS_BORDER], resSS->props[E_SS_CORNERRAD]);

		glMultiTexCoord4f(5, 0.0f, shadowOffset, uiComp->scrollMaskY.x, uiComp->scrollMaskY.y);
		
		//border color
		glMultiTexCoord4f(6, resSS->props[E_SS_BDCOL_R], resSS->props[E_SS_BDCOL_G], resSS->props[E_SS_BDCOL_B], resSS->props[E_SS_BDCOL_A]);
		//misc
		glMultiTexCoord4f(7, resSS->props[E_SS_ROUNDNESS], uiComp->getValue(), 1.0f, 1.0f);


		//bg
		glMultiTexCoord4f(2, resSS->props[E_SS_BGCOL1_R], resSS->props[E_SS_BGCOL1_G], resSS->props[E_SS_BGCOL1_B], resSS->props[E_SS_BGCOL1_A]);
		//fg
		glMultiTexCoord4f(3, resSS->props[E_SS_FGCOL1_R], resSS->props[E_SS_FGCOL1_G], resSS->props[E_SS_FGCOL1_B], resSS->props[E_SS_FGCOL1_A]);
		//tg
		glMultiTexCoord4f(4, resSS->props[E_SS_TGCOL1_R], resSS->props[E_SS_TGCOL1_G], resSS->props[E_SS_TGCOL1_B], resSS->props[E_SS_TGCOL1_A]);
		
		
		glMultiTexCoord4f(0, 0.0f, 0.0f, 0.0f, 1.0f);
		glVertex3f (  x0, y1, -1.0f );
		glMultiTexCoord4f(0, 0.0f, 0.0f, 1.0f, 1.0f);
		glVertex3f (  x1, y1, -1.0f );

		//bg
		glMultiTexCoord4f(2, resSS->props[E_SS_BGCOL0_R], resSS->props[E_SS_BGCOL0_G], resSS->props[E_SS_BGCOL0_B], resSS->props[E_SS_BGCOL0_A]);
		//fg
		glMultiTexCoord4f(3, resSS->props[E_SS_FGCOL0_R], resSS->props[E_SS_FGCOL0_G], resSS->props[E_SS_FGCOL0_B], resSS->props[E_SS_FGCOL0_A]);
		//tg
		glMultiTexCoord4f(4, resSS->props[E_SS_TGCOL0_R], resSS->props[E_SS_TGCOL0_G], resSS->props[E_SS_TGCOL0_B], resSS->props[E_SS_TGCOL0_A]);

		glMultiTexCoord4f(0, 0.0f, 0.0f, 1.0f, 0.0f);
		glVertex3f (  x1, y0, -1.0f );
		glMultiTexCoord4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
		glVertex3f (  x0, y0, -1.0f );


	}
void GameGUI::runReport ()
                         {
		baseComp->runReport();
	}
void GameGUI::renderGUI (float newZoom, int activeFBO)
                                                     {
		
		
		int i;
		
		int j;
		int k;
		int m;
		int n;
		
		int maxLoop = 0;
		
		float shadowOffset = 0.0;
		
		testOver(singleton->guiX,singleton->guiY);
		doRefresh();
		

		Singleton::UICont* curCont = NULL;
		
		
		
		baseComp->updateSS();
		

		singleton->bindFBO("guiFBO");
		singleton->drawFBO("resultFBO", 0, newZoom, activeFBO);
		
		glEnable (GL_BLEND);

		singleton->bindShader("GUIShader");
		singleton->setShaderTexture(0,singleton->fontWrappers[EFW_TEXT]->fontImage->tid);
		singleton->setShaderTexture(1,singleton->fontWrappers[EFW_ICONS]->fontImage->tid);
		singleton->sampleFBO("swapFBOBLin0", 2);
		
		for (i = 0; i < 2; i++) {
			
			
			if (i == 0) {
				maxLoop = 1;
			}
			else {
				maxLoop = 2;
			}
			
			singleton->setShaderFloat("passNum", i);
			singleton->setShaderFloat("zoom", singleton->cameraZoom);
			singleton->setShaderVec2("resolution", singleton->currentFBOResolutionX, singleton->currentFBOResolutionY);
			
			glBegin (GL_QUADS);
				//baseComp->renderAll(i == 0);
			
				for (j = 0; j < MAX_UI_LAYERS; j++) {
					for (k = 0; k < singleton->guiLayers[j].size(); k++) {
						
						curCont = (singleton->guiLayers[j][k]);
						
						if (curCont->uiComp->visible) {
							
							for (m = 0; m < maxLoop; m++) {
								
								shadowOffset = ((1-m)*i)*4.0f;
								
								
								// only shadow text
								if (shadowOffset == 0.0f) {
									
									
									if (curCont->bg.fontId > -1) {
										renderQuad(
											curCont->uiComp,
											curCont->bg.hitBounds,
											shadowOffset
										);
									}
									
									
								}
								
								if (i == 0) {
									// don't render text in first pass
								}
								else {
								
									if (false) { //curCont->locked) {
										// busy updating characters
									}
									else {
										for (n = 0; n < curCont->charVec.size(); n++) {
											renderCharAt(
												curCont->uiComp,
												curCont->charVec[n].cs,
												singleton->fontWrappers[curCont->charVec[n].fontId],
												curCont->charVec[n].hitBounds.xMin,
												curCont->charVec[n].hitBounds.yMin,
												shadowOffset
											);
										}
									}
									
									
									
									
								}	
								
								
								
							}
							
							
							
							
							
						}
						
						
						
						
						
					}
				}
			
			glEnd ();
		}
		
		
		singleton->unsampleFBO("swapFBOBLin0", 2);
		singleton->setShaderTexture(1,0);
		singleton->setShaderTexture(0,0);
		singleton->unbindShader();
		
		singleton->unbindFBO();
		
		glDisable(GL_BLEND);
		
		singleton->drawFBO("guiFBO", 0, 1.0f);
		
	}
#undef LZZ_INLINE
 
// f00338_gameentnode.h
//

#include "f00338_gameentnode.e"
#define LZZ_INLINE inline
float const GameEntNode::multiplier = 2.0f;
GameEntNode::GameEntNode (GameEntNode * _parent, int _nodeName, float _boneLength, float _tanLengthInMeters, float _bitLengthInMeters, float _norLengthInMeters, float _tanX, float _tanY, float _tanZ, float _bitX, float _bitY, float _bitZ, float _norX, float _norY, float _norZ)
          {
		
		
		
		material = 8.0;
		
		parent = _parent;
		nodeName = _nodeName;
		
		rotThe = 0.0f;
		rotPhi = 0.0f;
		rotRho = 0.0f;

		

		boneLengthHalf = _boneLength*0.5f*multiplier;

		tbnRadInMeters0.setFXYZ(
			_tanLengthInMeters*multiplier,
			_bitLengthInMeters*multiplier,
			_norLengthInMeters*multiplier
		);
		tbnRadInMeters1.setFXYZRef(&tbnRadInMeters0);
		tbnRadScale0.setFXYZ(1.0f,1.0f,1.0f);
		tbnRadScale1.setFXYZ(1.0f,1.0f,1.0f);
		boneLengthScale = 1.0f;
		
		
		(tbnBase[0]).setFXYZ(_tanX,_tanY,_tanZ);
		(tbnBase[1]).setFXYZ(_bitX,_bitY,_bitZ);
		(tbnBase[2]).setFXYZ(_norX,_norY,_norZ);
		(tbnBase[0]).normalize();
		(tbnBase[1]).normalize();
		(tbnBase[2]).normalize();
		
		// FIVector4::cross(&(tbnBase[2]),&(tbnBase[0]),&(tbnBase[1]));
		// (tbnBase[2]).normalize();
	}
GameEntNode * GameEntNode::addChild (int _nodeName, float _boneLength, float _tanLengthInMeters, float _bitLengthInMeters, float _norLengthInMeters, float _tanX, float _tanY, float _tanZ, float _bitX, float _bitY, float _bitZ, float _norX, float _norY, float _norZ)
          {
		
		//if (_nodeName >= E_BONE_C_END) {
		//	cout << "nodeName: " << _nodeName << "\n";
		//}
		
		children.push_back(
			new GameEntNode(
				this,
				
				_nodeName,
				_boneLength,
				_tanLengthInMeters,
				_bitLengthInMeters,
				_norLengthInMeters,
				
				_tanX, _tanY, _tanZ,
				_bitX, _bitY, _bitZ,
				_norX, _norY, _norZ
			)
		);
		
		return children.back();
	}
GameEntNode * GameEntNode::getNode (int _nodeName)
                                            {
		int i;
		
		// cout << "getNode("<< _nodeName << "): " << nodeName << "\n";
		
		
		if (nodeName == _nodeName) {
			return this;
		}
		
		for (i = 0; i < children.size(); i++) {
			
			if (children[i]->getNode(_nodeName) != NULL) {
				return children[i]->getNode(_nodeName);
			}
		}
		
		return NULL;
	}
void GameEntNode::doTransform (Singleton * singleton)
          {
		
		int i;
		int j;
		int popCount = 0;
		int modCount;
		
		//cout << "doTransform: " << boneStrings[nodeName] << "\n"; 
		
		
		// void doRotation(
		// 	FIVector4 *output,
		// 	FIVector4 *input,
		// 	FIVector4 *axis,
		// 	float angle
		// )
		
		
		// start
		if (parent == NULL) {
			orgTrans[0].setFXYZ(0.0f,0.0f,0.0f);
		}
		else {
			orgTrans[0].setFXYZRef(&(parent->orgTrans[2]));
		}
		
		
		
		for (i = 0; i < 3; i++) {
			tbnBaseTrans[i].copyFrom(&(tbnBase[i]));
			//tbnBaseTrans[i].addXYZRef(&(orgTrans[0]));
		}
		
		
		readTBN = tbnBaseTrans;
		writeTBN = tbnRotA;
		
		
		// if (rotRho != 0.0f) {
		// 	singleton->rotStack.push_back(readTBN[2]);
		// 	singleton->rotStack.back().setFW(rotRho);
		// 	singleton->transStack.push_back(orgTrans[0]);
		// 	popCount++;
		// }
		// if (rotThe != 0.0f) {
		// 	singleton->rotStack.push_back(readTBN[1]);
		// 	singleton->rotStack.back().setFW(rotThe);
		// 	singleton->transStack.push_back(orgTrans[0]);
		// 	popCount++;
		// }
		// if (rotPhi != 0.0f) {
		// 	singleton->rotStack.push_back(readTBN[0]);
		// 	singleton->rotStack.back().setFW(rotPhi);
		// 	singleton->transStack.push_back(orgTrans[0]);			
		// 	popCount++;
		// }
		
		
		/*
		void doRotationTBN(
			FIVector4 *output,
			FIVector4 *input,
			FIVector4 *axisAngle,
			FIVector4 *parentOffset,
			FIVector4 *baseOffset
		)
		*/
		
		
		
		
		
		
		modCount = 0;
		
		
		
		
		
		
		
		
		
		
		
		
		// if (rotRho != 0.0f) {
		// 	singleton->rotStack.push_back(readTBN[2]);
		// 	singleton->rotStack.back().setFW(rotRho);
		// 	singleton->transStack.push_back(orgTrans[0]);
			
			
			
		// 	axisRotationInstance.doRotationTBN(
		// 		writeTBN, // write
		// 		readTBN, // read
		// 		&(singleton->rotStack.back()),
		// 		&(singleton->transStack.back()),
		// 		&(orgTrans[0])
		// 	);
		// 	if ((modCount%2) == 0) {
		// 		readTBN = tbnRotA;
		// 		writeTBN = tbnRotB;
		// 	}
		// 	else {
		// 		readTBN = tbnRotB;
		// 		writeTBN = tbnRotA;
		// 	}
		// 	modCount++;
			
		// 	popCount++;
		// }
		// if (rotThe != 0.0f) {
		// 	singleton->rotStack.push_back(readTBN[1]);
		// 	singleton->rotStack.back().setFW(rotThe);
		// 	singleton->transStack.push_back(orgTrans[0]);
			
		// 	axisRotationInstance.doRotationTBN(
		// 		writeTBN, // write
		// 		readTBN, // read
		// 		&(singleton->rotStack.back()),
		// 		&(singleton->transStack.back()),
		// 		&(orgTrans[0])
		// 	);
		// 	if ((modCount%2) == 0) {
		// 		readTBN = tbnRotA;
		// 		writeTBN = tbnRotB;
		// 	}
		// 	else {
		// 		readTBN = tbnRotB;
		// 		writeTBN = tbnRotA;
		// 	}
		// 	modCount++;
			
		// 	popCount++;
		// }
		// if (rotPhi != 0.0f) {
		// 	singleton->rotStack.push_back(readTBN[0]);
		// 	singleton->rotStack.back().setFW(rotPhi);
		// 	singleton->transStack.push_back(orgTrans[0]);
			
		// 	axisRotationInstance.doRotationTBN(
		// 		writeTBN, // write
		// 		readTBN, // read
		// 		&(singleton->rotStack.back()),
		// 		&(singleton->transStack.back()),
		// 		&(orgTrans[0])
		// 	);
		// 	if ((modCount%2) == 0) {
		// 		readTBN = tbnRotA;
		// 		writeTBN = tbnRotB;
		// 	}
		// 	else {
		// 		readTBN = tbnRotB;
		// 		writeTBN = tbnRotA;
		// 	}
		// 	modCount++;
			
		// 	popCount++;
		// }
		
		
		
		
		
		if (rotRho != 0.0f) {
			singleton->rotMatStack.push_back(RotationInfo());
			singleton->rotMatStack.back().basePoint.copyFrom(&(orgTrans[0]));
			singleton->rotMatStack.back().axisAngle.copyFrom(&(readTBN[2]));
			singleton->rotMatStack.back().axisAngle.setFW(rotRho);
			axisRotationInstance.buildRotMatrix(&(singleton->rotMatStack.back()));
			
			popCount++;
		}
		if (rotThe != 0.0f) {
			singleton->rotMatStack.push_back(RotationInfo());
			singleton->rotMatStack.back().basePoint.copyFrom(&(orgTrans[0]));
			singleton->rotMatStack.back().axisAngle.copyFrom(&(readTBN[1]));
			singleton->rotMatStack.back().axisAngle.setFW(rotThe);
			axisRotationInstance.buildRotMatrix(&(singleton->rotMatStack.back()));
			popCount++;
		}
		if (rotPhi != 0.0f) {
			singleton->rotMatStack.push_back(RotationInfo());
			singleton->rotMatStack.back().basePoint.copyFrom(&(orgTrans[0]));
			singleton->rotMatStack.back().axisAngle.copyFrom(&(readTBN[0]));
			singleton->rotMatStack.back().axisAngle.setFW(rotPhi);
			axisRotationInstance.buildRotMatrix(&(singleton->rotMatStack.back()));
			popCount++;
		}
		
		
		for (i = singleton->rotMatStack.size()-(1); i >= 0; i--) {
			
			// axisRotationInstance.doRotationTBN(
			// 	writeTBN, // write
			// 	readTBN, // read
			// 	&(singleton->rotStack[i]), //axisAngle
			// 	&(singleton->transStack[i]), //parentOffset
			// 	&(orgTrans[0]) //baseOffset
			// );
			
			
			
			axisRotationInstance.applyRotation(
				writeTBN,
				readTBN,
				&(singleton->rotMatStack[i])
			);
			
			if ((modCount%2) == 0) {
				readTBN = tbnRotA;
				writeTBN = tbnRotB;
			}
			else {
				readTBN = tbnRotB;
				writeTBN = tbnRotA;
			}
			
			
			modCount++;
			
		}
		
		
		for (j = 0; j < 3; j++) {
			tbnRotC[j].setFXYZRef(&( readTBN[j] ));
			//tbnRotC[j].addXYZRef(&(orgTrans[0]),-1.0f);
			tbnRotC[j].normalize();
		}
		
		
		// middle
		orgTrans[1].setFXYZRef(&(tbnRotC[0]));
		orgTrans[1].multXYZ(boneLengthHalf*boneLengthScale);
		orgTrans[1].addXYZRef(&(orgTrans[0]));
		
		// end
		orgTrans[2].setFXYZRef(&(tbnRotC[0]));
		orgTrans[2].multXYZ(boneLengthHalf*boneLengthScale*2.0f);
		orgTrans[2].addXYZRef(&(orgTrans[0]));
		
		for (i = 0; i < 3; i++) {
			(tbnTrans[i]).setFXYZRef(&(tbnRotC[i]));
			(tbnTrans[i]).multXYZ(tbnRadInMeters0[i]*tbnRadScale0[i]);
			(tbnTrans[i]).addXYZRef(&(orgTrans[1]));
		}
		
		
		
		for (i = 0; i < children.size(); i++) {
			children[i]->doTransform(singleton);
		}
		
		
		for (i = 0; i < popCount; i++) {
			singleton->rotMatStack.pop_back();
			//singleton->transStack.pop_back();
			//singleton->rotStack.pop_back();
		}
		
	}
#undef LZZ_INLINE
 
// f00339_gameent.h
//

#include "f00339_gameent.e"
#define LZZ_INLINE inline
float GameEnt::gv (float * vals)
                              {
		float lerp = fGenRand();
		return vals[0]*lerp + vals[1]*(1.0f-lerp);
	}
GameEnt::GameEnt ()
                  {
		defVecLength = 0.05f;
	}
void GameEnt::init (Singleton * _singleton)
          {
		singleton = _singleton;

		baseNode = new GameEntNode(
			NULL,
			E_BONE_C_BASE,
			0.5f,
			defVecLength, defVecLength, defVecLength,
			
			0.0f, 1.0f, 0.0f,			
			1.0f, 0.0f, 0.0f,
			0.0f,0.0f,1.0f
		);
		
		initHuman();
		
		gph = new GamePageHolder();
		gph->init(
			singleton,
			
			singleton->curEntId,
			0,
			
			0,
			0,
			0,
			
			true
		);
		
		singleton->curEntId++;
		
		
	}
void GameEnt::initHuman ()
                         {
		
		int i;
		int j;
		int lrMod;
		
		float dirMod = 1.0f;
		
		GameEntNode* curNode;
		curNode = baseNode;
		
		

		float numSpineSegs = E_BONE_C_SKULL-E_BONE_C_SPINE0;
		
		for (i = E_BONE_C_SPINE0; i < E_BONE_C_SKULL; i++) {
			curNode = curNode->addChild(
				i,
				0.75f/numSpineSegs,
				defVecLength, defVecLength, defVecLength,
				0.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,
				1.0f,0.0f,0.0f
				
			);
		}
		
		curNode = curNode->addChild(
			E_BONE_C_SKULL,
			0.25f, 
			defVecLength, defVecLength, defVecLength,
			0.0f,0.0f,1.0f,
			0.0f,1.0f,0.0f,
			1.0f,0.0f,0.0f
		);
		
		
		for (j = 0; j < 2; j++) {
			
			if (j == 0) { // left limbs
				lrMod = 0;
				dirMod = 1.0f;
			}
			else { // right limbs
				lrMod = E_BONE_R_BEG - E_BONE_L_BEG;
				dirMod = -1.0f;
			}
			
			curNode = baseNode->getNode(E_BONE_C_SKULL-2);
			
			
			curNode = curNode->addChild(
				E_BONE_L_SHOULDER + lrMod,
				0.20f, 
				defVecLength, defVecLength, defVecLength,
				dirMod*1.0f,0.0f,0.0f,
				0.0f,1.0f,0.0f,
				0.0f,0.0f,1.0f
			);
			curNode = curNode->addChild(
				E_BONE_L_UPPERARM + lrMod,
				0.25f, 
				defVecLength, defVecLength, defVecLength,
				dirMod*1.0f,0.0f,0.0f,
				0.0f,1.0f,0.0f,
				0.0f,0.0f,1.0f
			);
			curNode = curNode->addChild(
				E_BONE_L_LOWERARM + lrMod,
				0.25f, 
				defVecLength, defVecLength, defVecLength,
				dirMod*1.0f,0.0f,0.0f,
				0.0f,1.0f,0.0f,
				0.0f,0.0f,1.0f
			);
			curNode = curNode->addChild(
				E_BONE_L_METACARPALS + lrMod,
				0.1f, 
				defVecLength, defVecLength, defVecLength,
				dirMod*1.0f,0.0f,0.0f,
				0.0f,1.0f,0.0f,
				0.0f,0.0f,1.0f
			);
			
			
			curNode = baseNode;
			
			curNode = curNode->addChild(
				E_BONE_L_HIP + lrMod,
				0.1f, 
				defVecLength, defVecLength, defVecLength,
				dirMod*1.0f,0.0f,0.0f,
				0.0f,1.0f,0.0f,
				0.0f,0.0f,1.0f
			);
			curNode = curNode->addChild(
				E_BONE_L_UPPERLEG + lrMod,
				0.45f, 
				defVecLength, defVecLength, defVecLength,
				0.0f,0.0f,-1.0f,
				0.0f,1.0f,0.0f,
				dirMod*1.0f,0.0f,0.0f
			);
			curNode = curNode->addChild(
				E_BONE_L_LOWERLEG + lrMod,
				0.45f, 
				defVecLength, defVecLength, defVecLength,
				0.0f,0.0f,-1.0f,
				0.0f,1.0f,0.0f,
				dirMod*1.0f,0.0f,0.0f
			);
			curNode = curNode->addChild(
				E_BONE_L_TALUS + lrMod,
				0.2f, 
				defVecLength, defVecLength, defVecLength,
				0.0f,1.0f,0.0f,
				dirMod*1.0f,0.0f,0.0f,
				0.0f,0.0f,1.0f
			);
			
		}
		
		
		baseNode->doTransform(singleton);
		
	}
#undef LZZ_INLINE
 
// f00340_gameplantnode.h
//

#include "f00340_gameplantnode.e"
#define LZZ_INLINE inline
GamePlantNode::GamePlantNode ()
                        {
		sphereRad = 0.0f;
		parent = NULL;
		children = NULL;
		upVec.setFXYZ(0.0f,0.0f,1.0f);
	}
void GamePlantNode::updateTangent (float angleInRadians)
                                                 {
		tangent.setFXYZRef(&endPoint);
		tangent.addXYZRef(&begPoint,-1.0f);
		tangent.normalize();
		baseShoot.setFXYZRef(&tangent);
		baseShoot.rotate(angleInRadians, E_PLANE_XZ);
		baseShoot.normalize();

		shootLength = begPoint.distance(&endPoint);

		// ctrPoint.copyFrom(&begPoint);
		// if (parent == NULL) {
		// 	ctrPoint.addXYZRef(&endPoint);
		// 	ctrPoint.multXYZ(0.5f);
		// }
		// else {
		// 	ctrPoint.addXYZRef(&(parent->tangent), shootLength/2.0f);
		// }
		

	}
void GamePlantNode::init (GamePlantNode * _parent, int _maxChildren, int _numChildren)
          {
		parent = _parent;
		
		maxChildren = _maxChildren;	
		numChildren = _numChildren;

		sphereRad = 0.0f;

		if (maxChildren > 0) {

			if (children == NULL) {
				children = new GamePlantNode[maxChildren];
			}
			else {

			}

			
		}
		
	}
#undef LZZ_INLINE
 
// f00341_gameplant.h
//

#include "f00341_gameplant.e"
#define LZZ_INLINE inline
PlantRules (GamePlant::allPlantRules) [E_PT_LENGTH];
void GamePlant::initAllPlants (Singleton * _singleton)
                                                         {
		int i;
		int j;


		float pi = 3.14159;

		PlantRules* pr;

		pr = &(allPlantRules[E_PT_OAK_TRUNK]);
		pr->numChildren[0] = 2.0f;
		pr->numChildren[1] = 5.0f;
		pr->divergenceAngleV[0] = pi/3.0f;
		pr->divergenceAngleV[1] = pi/6.0f;
		pr->begThickness = 1.0f;
		pr->endThickness = 0.4f;
		pr->sphereGen = 2.0f;
		pr->sphereRad = 6.0f;
		pr->numGenerations = 2.0f;
		pr->angleUniformityU = 0.75f;
		pr->isInit = 0.0;
		pr->curLength[0] = 6.0f;
		pr->curLength[1] = 8.0f;
		pr->curLength[2] = 8.0f;
		pr->curLength[3] = 8.5f;
		pr->curLength[4] = 8.5f;
		pr->curLength[5] = 8.5f;
		pr->curLength[6] = 1.0f;
		pr->curLength[7] = 1.0f;
		pr->curLength[8] = 0.75f;

		pr = &(allPlantRules[E_PT_OAK_ROOTS]);
		pr->numChildren[0] = 2.0f;
		pr->numChildren[1] = 5.0f;
		pr->divergenceAngleV[0] = pi/8.0f;
		pr->divergenceAngleV[1] = pi/8.0f;
		pr->begThickness = 1.0f;
		pr->endThickness = 0.0f;
		pr->sphereGen = -1.0f;
		pr->sphereRad = 0.0f;		
		pr->numGenerations = 4.0f;
		pr->angleUniformityU = 0.75f;
		pr->isInit = 0.0;
		pr->curLength[0] = 6.0f;
		pr->curLength[1] = 8.0f;
		pr->curLength[2] = 8.0f;
		pr->curLength[3] = 8.5f;
		pr->curLength[4] = 8.5f;
		pr->curLength[5] = 8.5f;
		pr->curLength[6] = 1.5f;
		pr->curLength[7] = 1.0f;
		pr->curLength[8] = 0.75f;
		
		
		pr = &(allPlantRules[E_PT_OAK2_TRUNK]);
		pr->numChildren[0] = 2.0f;
		pr->numChildren[1] = 5.0f;
		pr->divergenceAngleV[0] = pi/3.0f;
		pr->divergenceAngleV[1] = pi/4.0f;
		pr->begThickness = 1.0f;
		pr->endThickness = 0.2f;
		pr->sphereGen = 2.0f;
		pr->sphereRad = 6.0f;
		pr->numGenerations = 2.0f;
		pr->angleUniformityU = 0.75f;
		pr->isInit = 0.0;
		pr->curLength[0] = 6.0f;
		pr->curLength[1] = 8.0f;
		pr->curLength[2] = 8.0f;
		pr->curLength[3] = 8.5f;
		pr->curLength[4] = 8.5f;
		pr->curLength[5] = 1.5f;
		pr->curLength[6] = 1.0f;
		pr->curLength[7] = 1.0f;
		pr->curLength[8] = 0.75f;

		pr = &(allPlantRules[E_PT_OAK2_ROOTS]);
		pr->numChildren[0] = 2.0f;
		pr->numChildren[1] = 3.0f;
		pr->divergenceAngleV[0] = pi/8.0f;
		pr->divergenceAngleV[1] = pi/8.0f;
		pr->begThickness = 1.0f;
		pr->endThickness = 0.0f;
		pr->sphereGen = -1.0f;
		pr->sphereRad = 0.0f;
		pr->numGenerations = 2.0f;
		pr->angleUniformityU = 0.75f;
		pr->isInit = 0.0;
		pr->curLength[0] = 6.0f;
		pr->curLength[1] = 8.0f;
		pr->curLength[2] = 8.0f;
		pr->curLength[3] = 8.5f;
		pr->curLength[4] = 8.5f;
		pr->curLength[5] = 2.0f;
		pr->curLength[6] = 1.5f;
		pr->curLength[7] = 1.0f;
		pr->curLength[8] = 0.75f;





		pr = &(allPlantRules[E_PT_BARE_OAK_TRUNK]);
		pr->numChildren[0] = 2.0f;
		pr->numChildren[1] = 5.0f;
		pr->divergenceAngleV[0] = pi/3.0f;
		pr->divergenceAngleV[1] = pi/4.0f;
		pr->begThickness = 1.0f;
		pr->endThickness = 0.2f;
		pr->sphereGen = -1.0f;
		pr->sphereRad = 0.0f;
		pr->numGenerations = 4.0f;
		pr->angleUniformityU = 0.75f;
		pr->isInit = 0.0;
		pr->curLength[0] = 6.0f;
		pr->curLength[1] = 4.0f;
		pr->curLength[2] = 6.0f;
		pr->curLength[3] = 4.5f;
		pr->curLength[4] = 4.5f;
		pr->curLength[5] = 1.5f;
		pr->curLength[6] = 1.0f;
		pr->curLength[7] = 1.0f;
		pr->curLength[8] = 0.75f;

		pr = &(allPlantRules[E_PT_BARE_OAK_ROOTS]);
		pr->numChildren[0] = 2.0f;
		pr->numChildren[1] = 5.0f;
		pr->divergenceAngleV[0] = pi/8.0f;
		pr->divergenceAngleV[1] = pi/8.0f;
		pr->begThickness = 1.0f;
		pr->endThickness = 0.0f;
		pr->sphereGen = -1.0f;
		pr->sphereRad = 0.0f;
		pr->numGenerations = 4.0f;
		pr->angleUniformityU = 0.75f;
		pr->isInit = 0.0;
		pr->curLength[0] = 6.0f;
		pr->curLength[1] = 8.0f;
		pr->curLength[2] = 8.0f;
		pr->curLength[3] = 8.5f;
		pr->curLength[4] = 8.5f;
		pr->curLength[5] = 8.5f;
		pr->curLength[6] = 1.5f;
		pr->curLength[7] = 1.0f;
		pr->curLength[8] = 0.75f;
		

		


		
		for (i = 0; i < E_PT_LENGTH; i++) {
			if (allPlantRules[i].isInit == 0.0f) {



				allPlantRules[i].begThickness *= _singleton->pixelsPerMeter;
				allPlantRules[i].endThickness *= _singleton->pixelsPerMeter;
				for (j = 0; j < MAX_PLANT_GEN; j++) {
					allPlantRules[i].curLength[j] *= _singleton->pixelsPerMeter;
				}

				

			}
		}
	}
float GamePlant::gv (float * vals)
                              {
		float lerp = fGenRand();
		return vals[0]*lerp + vals[1]*(1.0f-lerp);
	}
GamePlant::GamePlant ()
                    {
		trunkNode = NULL;
		rootsNode = NULL;
	}
void GamePlant::init (Singleton * _singleton, PlantRules * _rootRules, PlantRules * _trunkRules, FIVector4 * _origin)
          {
		singleton = _singleton;
		rootRules = _rootRules;
		trunkRules = _trunkRules;
		origin.setFXYZRef(_origin);

		trunkVec.setFXYZ(fGenRand()*0.1f,fGenRand()*0.1f,1.0f);
		trunkVec.normalize();
		rootVec.setFXYZRef(&trunkVec);
		rootVec.multXYZ(-1.0f);

		if (trunkNode == NULL) {
			trunkNode = new GamePlantNode();
		}
		if (rootsNode == NULL) {
			rootsNode = new GamePlantNode();
		}


		initBase(rootRules, rootsNode, &rootVec);
		initBase(trunkRules, trunkNode, &trunkVec);

	}
void GamePlant::initBase (PlantRules * rules, GamePlantNode * curNode, FIVector4 * baseVec)
          {
		int i;
		float curLerp;
		float maxLength = 0.0f;
		//float curMult = 1.0f;
		int maxGen = rules->numGenerations;

		
		curNode->init(NULL,rules->numChildren[1],gv(rules->numChildren));
		//curNode->tangent.setFXYZRef(baseVec);
		curNode->begPoint.setFXYZRef(&origin);
		curNode->endPoint.setFXYZRef(&origin);
		curNode->endPoint.addXYZRef(baseVec,rules->curLength[0]);
		curNode->updateTangent(gv(rules->divergenceAngleV));

		for (i = 1; i <= maxGen; i++) {
			maxLength += rules->curLength[i]; // *curMult;
			//curMult *= rules->nodeLengthMultiplier;
		}

		

		// curLerp = rules->curLength[0]/maxLength;
		// curNode->endThickness = (1.0f-curLerp)*rules->begThickness + curLerp*rules->endThickness;

		// curLerp = 0.0f;
		// curNode->begThickness = curNode->endThickness;//(1.0f-curLerp)*rules->begThickness + curLerp*rules->endThickness;

		// curNode->midThickness = (curNode->begThickness+curNode->endThickness)*0.5f;

		curNode->begThickness = rules->begThickness;
		curNode->endThickness = curNode->begThickness;
		curNode->midThickness = curNode->begThickness;

		


		applyRules(
			rules,
			curNode,
			0,
			maxGen,
			//rules->baseLength*(rules->nodeLengthMultiplier),
			0.0f,
			maxLength
		);
	}
void GamePlant::applyRules (PlantRules * rules, GamePlantNode * curParent, int curGen, int maxGen, float totLength, float maxLength)
          {


		//cout << "curLength: " << curLength << "\n";

		int i;
		float fi;
		float fCurGen = (float)curGen;
		float fNumChildren;
		float curLerp;
		float twoPi = 6.283185307f;
		float curLength = rules->curLength[curGen];

		GamePlantNode* curChild;

		fNumChildren = (float)(curParent->numChildren);

		for (i = 0; i < curParent->numChildren; i++) {

			fi = ((float)i)/fNumChildren;

			curChild = &(curParent->children[i]);


			if (curGen == maxGen) {
				curChild->init(curParent,0,0);
			}
			else {
				curChild->init(curParent,rules->numChildren[1], max( gv(rules->numChildren)-(float)curGen, 1.0f) );
			}

			
			curChild->begPoint.setFXYZRef(&(curParent->endPoint));
			curChild->endPoint.setFXYZRef(&(curParent->endPoint));

			axisRotationInstance.doRotation(
				&tempv0,
				&(curParent->baseShoot),
				&(curParent->tangent),
				fi*twoPi + (fGenRand()-0.5f)*twoPi*(1.0f-rules->angleUniformityU)/fNumChildren
			);
			curChild->endPoint.addXYZRef(&tempv0,curLength);
			curChild->updateTangent(gv(rules->divergenceAngleV));

			curLerp = (totLength/maxLength);
			curChild->begThickness = (1.0f-curLerp)*rules->begThickness + curLerp*rules->endThickness;

			curLerp = ((totLength+curLength)/maxLength);
			curChild->endThickness = (1.0f-curLerp)*rules->begThickness + curLerp*rules->endThickness;

			curChild->midThickness = (curChild->begThickness+curChild->endThickness)*0.5f;

			if ( rules->sphereGen == fCurGen ) {
				curChild->sphereRad = rules->sphereRad*singleton->pixelsPerMeter; //(maxLength-totLength) + 
			}

			if (curGen < maxGen) {
				applyRules(rules, curChild, curGen + 1, maxGen, totLength+curLength, maxLength);
			}

		}
	}
#undef LZZ_INLINE
 
// f00350_gamepage.h
//

#include "f00350_gamepage.e"
#define LZZ_INLINE inline
GamePage::GamePage ()
                   {
		terRes = -1;
		parentBlock = NULL;
		volData = NULL;
		volDataLinear = NULL;
	}
void GamePage::init (Singleton * _singleton, GamePageHolder * _parentGPH, int _thisPageId, int offsetX, int offsetY, int offsetZ, int oxLoc, int oyLoc, int ozLoc, bool _isEntity)
          {


		isEntity = false;
		hasLines = false;
		hasSolids = false;
		hasTrans = false;
		isDirty = true;
		

		isEntity = _isEntity;

		thisPageId = _thisPageId;
		singleton = _singleton;
		parentGPH = _parentGPH;
		gw = singleton->gw;
		
		if (!isEntity) {
			parentBlock = gw->getBlockAtId(parentGPH->blockId);
		}
		
		

		maxEntries = 32;
		isRendering = true;

		int i;

		volDataModified = false;
		threadRunning = false;


		//maxHeightInUnits = (singleton->maxHeightInUnits);



		int visPageSizeInUnits = singleton->visPageSizeInUnits;
		bufferedPageSizeInUnits = (visPageSizeInUnits) * (singleton->bufferMult);

		offsetInPages.setIXYZ(offsetX, offsetY, offsetZ);
		offsetInUnits.copyFrom(&offsetInPages);
		offsetInUnits.multXYZ(singleton->visPageSizeInUnits);

		offsetInPagesLocal.setIXYZ(oxLoc, oyLoc, ozLoc);

		float hzp = (float)(singleton->holderSizeInPages);

		pageDepth = ((1.0f - ( (offsetInPagesLocal.getFZ() * hzp * hzp + offsetInPagesLocal.getFY() * hzp + offsetInPagesLocal.getFX()) / (hzp * hzp * hzp) )) * 0.9f + 0.05f) * 0.5f;


		unitSizeInPixels = (float)(singleton->unitSizeInPixels);



		iVolumeSize = bufferedPageSizeInUnits * bufferedPageSizeInUnits * bufferedPageSizeInUnits;




		worldMinVisInPixels.copyFrom(&offsetInUnits);
		worldMaxVisInPixels.copyFrom(&offsetInUnits);
		worldMaxVisInPixels.addXYZ(visPageSizeInUnits);
		worldMinVisInPixels.multXYZ((float)unitSizeInPixels);
		worldMaxVisInPixels.multXYZ((float)unitSizeInPixels);

		worldUnitMin.copyFrom(&offsetInUnits);
		worldUnitMax.copyFrom(&offsetInUnits);
		worldUnitMax.addXYZ(visPageSizeInUnits);

		worldUnitMin.addXYZ( -(bufferedPageSizeInUnits - visPageSizeInUnits) / 2 );
		worldUnitMax.addXYZ( (bufferedPageSizeInUnits - visPageSizeInUnits) / 2 );

		worldMinBufInPixels.copyFrom(&worldUnitMin);
		worldMaxBufInPixels.copyFrom(&worldUnitMax);
		worldMinBufInPixels.multXYZ((float)unitSizeInPixels);
		worldMaxBufInPixels.multXYZ((float)unitSizeInPixels);

		voroSize.setFXYZ(
			singleton->visPageSizeInPixels,
			singleton->visPageSizeInPixels,
			singleton->visPageSizeInPixels
		);


		centerPosition.copyFrom(&worldMinVisInPixels);
		centerPosition.addXYZRef(&worldMaxVisInPixels);
		centerPosition.multXYZ(0.5f);

		
		
		hasWater = ( singleton->getSLInPixels() >= worldMinVisInPixels.getFZ() );
		
		
		if (isEntity) {
			addEntityGeom(true);
		}
		else {			
			addGeom(true);
		}
		
		



	}
uint * GamePage::getVolData ()
                           {
		int i;

		if (volData == NULL) {
			volData = new uint[iVolumeSize];
			for (i = 0; i < iVolumeSize; i++) {
				volData[i] = 0;
			}
		}

		return volData;

	}
uint * GamePage::getVolDataLinear ()
                                 {
		int i;

		if (volDataLinear == NULL) {
			volDataLinear = new uint[iVolumeSize];
			for (i = 0; i < iVolumeSize; i++) {
				volDataLinear[i] = (0 << 24) | (0 << 16) | (0 << 8) | (0);
			}
		}

		return volDataLinear;
	}
void GamePage::copyToTexture (bool isForEmptyVD)
                                              {


		int id1 = singleton->volId;
		int id2 = singleton->volIdLinear;

		if (isForEmptyVD) {
			id1 = singleton->volIdEmpty;
			id2 = singleton->volIdEmptyLinear;
		}

		glBindTexture(GL_TEXTURE_3D, id1);
		glTexSubImage3D(
			GL_TEXTURE_3D,
			0,

			0,
			0,
			0,

			bufferedPageSizeInUnits,
			bufferedPageSizeInUnits,
			bufferedPageSizeInUnits,

			GL_RGBA,
			GL_UNSIGNED_BYTE,

			getVolData()
		);

		glBindTexture(GL_TEXTURE_3D, 0);
		glBindTexture(GL_TEXTURE_3D, id2);
		glTexSubImage3D(
			GL_TEXTURE_3D,
			0,

			0,
			0,
			0,

			bufferedPageSizeInUnits,
			bufferedPageSizeInUnits,
			bufferedPageSizeInUnits,

			GL_RGBA,
			GL_UNSIGNED_BYTE,

			getVolDataLinear()
		);
		glBindTexture(GL_TEXTURE_3D, 0);





		/*
		glTexSubImage2D(
		  GLenum    target,
		  GLint   level,
		  GLint   xoffset,
		  GLint   yoffset,
		  GLsizei   width,
		  GLsizei   height,
		  GLenum    format,
		  GLenum    type,
		  const GLvoid *    data
		 );


		void glTexSubImage3D(

		  GLenum target,
		  GLint level,
		  GLint xoffset,
		  GLint yoffset,
		  GLint zoffset,
		  GLsizei width,
		  GLsizei height,
		  GLsizei depth,
		  GLenum format,
		  GLenum type,


		glBindTexture(GL_TEXTURE_2D, singleton->volId);
		  glTexSubImage2D(
		    GL_TEXTURE_2D,
		    0,

		    xoff,
		    yoff,

		    width,
		    height,

		    GL_RGBA,
		    GL_UNSIGNED_SHORT,

		    cpuArrPtr
		  );
		glBindTexture(GL_TEXTURE_2D, 0);


		*/


	}
void GamePage::setFalse ()
                        {
		hasLines = false;
		hasSolids = false;
		hasTrans = false;
		hasTree = false;
		hasWindow = false;
		hasGeom = false;
		hasTerrain = false;
	}
void GamePage::addEntityGeom (bool justTesting)
                                             {
		
		int i;
		int j;
		int k;
		int m;
		int n;
		int p;
		int ind;
		int bufSize = (singleton->visPageSizeInPixels * singleton->bufferMult);
		int geomInPage;
		int baseInd;

		GamePageHolder *gph;
		GameGeom *gg;

		paramsPerEntry = E_GP_LENGTH * 3;
		numEntries = 0;

		bool doProc;

		for (i = 0; i < E_MAT_PARAM_LENGTH; i++) {
			singleton->matCountArr[i] = 0.0f;
		}

		


		if (justTesting) {
			setFalse();
		}

		
		gph = parentGPH;

		if (gph) {
			geomInPage = gph->entityGeom.size();
			

			for (m = 0; m < geomInPage; m++) {
				
				gg = gph->entityGeom[m];

				if (

					FIVector4::intersect( gg->getVisMinInPixelsT(), gg->getVisMaxInPixelsT(), &worldMinBufInPixels, &worldMaxBufInPixels )
					&& (gg->visible)

				) {

					if (justTesting) {
						
						
						if (gg->buildingType == E_CT_LINES) {
							hasLines = true;
						}
						else {
							hasGeom = true;
						}
						
						
					}
					else {
						for (p = 0; p < E_GP_LENGTH; p++) {
							baseInd = numEntries * paramsPerEntry + p * 3;
							singleton->paramArr[baseInd + 0] = gg->geomParams[p].getFX();
							singleton->paramArr[baseInd + 1] = gg->geomParams[p].getFY();
							singleton->paramArr[baseInd + 2] = gg->geomParams[p].getFZ();
						}

						singleton->matCountArr[gg->geomParams[E_GP_MATPARAMS].getIX()] += 1.0f;

						numEntries++;
						
					}
				}
			}
		}
		
		

		if (justTesting) {
			parentGPH->hasTrans = false;
			hasTrans = false;
			if (hasGeom||hasLines) {
				parentGPH->hasSolids = true;
				hasSolids = true;
			}
		}
		else {
			if (numEntries > maxEntries) {
				numEntries = maxEntries;
				doTraceND("limit exceeded");
			}

			totParams = numEntries * paramsPerEntry;
		}


	}
void GamePage::addGeom (bool justTesting)
                                       {

		int i;
		int j;
		int k;
		int m;
		int n;
		int p;
		int ind;
		int bufSize = (singleton->visPageSizeInPixels * singleton->bufferMult);
		intPair curId;
		int geomInPage;
		int baseInd;

		FIVector4 start;
		FIVector4 end;

		GamePageHolder *gph;
		GameGeom *gg;

		paramsPerEntry = E_GP_LENGTH * 3;
		numEntries = 0;

		bool doProc;

		start.copyFrom( &worldMinBufInPixels );
		end.copyFrom( &worldMaxBufInPixels );

		start.addXYZ(-bufSize);
		end.addXYZ(bufSize);

		start.intDivXYZ(singleton->holderSizeInPixels);
		end.intDivXYZ(singleton->holderSizeInPixels);

		start.clampZ( singleton->origin.getFZ(), singleton->worldSizeInHolders.getFZ() - 1.0f );
		end.clampZ( singleton->origin.getFZ(), singleton->worldSizeInHolders.getFZ() - 1.0f );

		for (i = 0; i < E_MAT_PARAM_LENGTH; i++) {
			singleton->matCountArr[i] = 0.0f;
		}

		if (justTesting) {
			setFalse();
		}


		for (k = start.getIZ(); k <= end.getIZ(); k++ ) {
			for (j = start.getIY(); j <= end.getIY(); j++ ) {
				for (i = start.getIX(); i <= end.getIX(); i++ ) {
					gph = gw->getHolderAtCoords(i, j, k);

					// TODO critical: make sure holders are ready before pages


					if (gph) {
						geomInPage = gph->containsGeomIds.size();

						for (m = 0; m < geomInPage; m++) {
							curId = gph->containsGeomIds[m];
							gg = gw->blockData[curId.v0]->gameGeom[curId.v1];


							if (

								FIVector4::intersect( gg->getVisMinInPixelsT(), gg->getVisMaxInPixelsT(), &worldMinBufInPixels, &worldMaxBufInPixels )
								&& (gg->visible)

							) {

								if (justTesting) {
									if ( (gg->buildingType == E_CT_WINDOW) || (gg->buildingType == E_CT_LANTERN)) {
										hasWindow = true;
									}

									if (gg->buildingType == E_CT_TREE) {
										hasTree = true;
									}
									hasGeom = true;
								}
								else {

									doProc = true;

									for (n = 0; n < numEntries; n++) {
										if (singleton->geomIdArr[n] == gg->globalId) {
											doProc = false;
										}
									}

									if (doProc) {

										singleton->geomIdArr[numEntries] = gg->globalId;



										for (p = 0; p < E_GP_LENGTH; p++) {

											baseInd = numEntries * paramsPerEntry + p * 3;

											singleton->paramArr[baseInd + 0] = gg->geomParams[p].getFX();
											singleton->paramArr[baseInd + 1] = gg->geomParams[p].getFY();
											singleton->paramArr[baseInd + 2] = gg->geomParams[p].getFZ();
										}

										singleton->matCountArr[gg->geomParams[E_GP_MATPARAMS].getIX()] += 1.0f;

										numEntries++;
									}
								}
							}
						}
					}
				}
			}
		}

		if (justTesting) {
			
			terRes = parentBlock->isNearTerrain(&centerPosition);
			
			hasTerrain = (terRes == E_TER_GROUNDLEVEL);
			
			if (terRes == E_TER_UNDERGROUND) {
				
			}
			else {
				if (hasWindow || hasWater) {
					parentGPH->hasTrans = true;
					hasTrans = true;
					if (MAX_LAYERS < 2) {
						parentGPH->hasSolids = true;
						hasSolids = true;
					}
				}

				if (hasTerrain || hasGeom || volDataModified) {
					parentGPH->hasSolids = true;
					hasSolids = true;
				}
			}
			
			
						
			
		}
		else {
			if (numEntries > maxEntries) {
				numEntries = maxEntries;
				cout << "limit exceeded " << numEntries << " / " << maxEntries << "\n";
			}

			totParams = numEntries * paramsPerEntry;
		}




	}
void GamePage::getVoroPoints ()
                             {


		int i, j, k;

		int counter = 0;
		int rad = 2;
		int tempi = 0;
		
		//int iMaxPoints = 27;
		//float fMaxPoints = (float)iMaxPoints;

		float fi, fj, fk;

		
		FIVector4 posFloored;
		FIVector4 posFlooredInPixels;
		
		// posFloored.copyFrom(&worldMaxVisInPixels);
		// posFloored.addXYZRef(&worldMinVisInPixels);
		// posFloored.multXYZ(0.5f);

		posFloored.copyFrom(&offsetInPages);
		posFloored.addXYZ(0.5f);
		
		posFlooredInPixels.copyFrom(&posFloored);
		posFlooredInPixels.multXYZ(&voroSize);

		// posFloored.divXYZ(&voroSize);
		// posFloored.floorXYZ();


		int totVoro = 27;
		
		

		for (i = -rad; i <= rad; i++) {
			fi = (float)i;
			for (j = -rad; j <= rad; j++) {
				fj = (float)j;
				for (k = -rad; k <= rad; k++) {
					fk = (float)k;


					curPos.copyFrom(&posFloored);
					curPos.addXYZ(fi, fj, fk);


					// if (
					//  (curPos.getIX() + curPos.getIY() + curPos.getIZ()) % 3 == 0
					// ) {




					//if (curPos.getIZ()%3 == 0) {

					randNum.setRand(&curPos);
					//randNum.multXYZ(1.0f);

					singleton->voroVecArr[counter].copyFrom(&curPos);
					singleton->voroVecArr[counter].addXYZRef(&randNum);
					singleton->voroVecArr[counter].multXYZ(&voroSize);

					//testNum.setRand(&curPos);

					//if (testNum.getFX() > 1.0f - (fMaxPoints/125.0f) ) { //true) {//
					// singleton->voroArr[counter * 4 + 0] = newPos.getFX();
					// singleton->voroArr[counter * 4 + 1] = newPos.getFY();
					// singleton->voroArr[counter * 4 + 2] = newPos.getFZ();
					//singleton->voroArr[counter * 4 + 3] = (testNum.getFX()) * 0.5 + 0.5;
					counter++;
					//}

					// if (counter >= iMaxPoints) {
					// 	counter = iMaxPoints;
					// 	goto VORO_DONE;
					// }
					//}



				}
			}
		}

// VORO_DONE:
// 		voroCount = counter;


		


		for (i = 0; i < 125; i++){
			singleton->indexArr[i].index1 = i;
			singleton->indexArr[i].value = singleton->voroVecArr[i].distance(&posFlooredInPixels);
		}
		
		bubbleSortF(singleton->indexArr, 125);
		
		int curInd = 0;
		for (i = 0; i < 27; i++) {
			curInd = singleton->indexArr[i].index1;
			singleton->voroArr[i * 4 + 0] = singleton->voroVecArr[curInd].getFX();
			singleton->voroArr[i * 4 + 1] = singleton->voroVecArr[curInd].getFY();
			singleton->voroArr[i * 4 + 2] = singleton->voroVecArr[curInd].getFZ();
		}

		
		voroCount = 27;
	}
void GamePage::generateVolume (bool dd)
                                             {
		PAGE_COUNT++;

		int curVGFBO = CUR_VG_FBO;
		CUR_VG_FBO++;
		if (CUR_VG_FBO >= MAX_VG_FBOS) {
			CUR_VG_FBO = 0;
		}
		
		// 1 = 0
		// 2 = 1
		// 4 = 2
		// 8 = 2
		
		float curBlendAmount = 0.5f;
		

		int hspLog = 2;
		
		switch (singleton->holderSizeInPages) {
			case 1:
				hspLog = 0;
			break;
			case 2:
				hspLog = 1;
			break;
		}
		
		
		int resIndex = 0;
		int i;
		isRendering = true;
		
		if (volDataModified) {
			copyToTexture(false);
		}
		else {
			if (singleton->emptyVDNotReady) {
				singleton->emptyVDNotReady = false;
				copyToTexture(true);
			}
		}
		
		if (isEntity) {
			curBlendAmount = 1.0f;
			addEntityGeom(true);
			addEntityGeom(false);
		}
		else {
			resIndex = parentBlock->copyTerToTexture();
			addGeom(true);
			addGeom(false);
			
		}
		

		parentGPH->clearSet(); //false
		getVoroPoints();


		if (dd) {
			
			hasTerrain = true;
			hasSolids = true;
			parentGPH->hasSolids = true;
			
		}


		/////////////////////////////////////////
		// BEGIN GEN VOLUME
		/////////////////////////////////////////


		if (isEntity) {
			singleton->bindShader("GenerateVolumeEnt");
		}
		else {
			singleton->bindShader("GenerateVolume");
		}

		

		singleton->bindFBODirect(&(singleton->vgFBOArr[curVGFBO]), 0);

		if (volDataModified) {
			singleton->setShaderTexture3D(0, singleton->volId);
			singleton->setShaderTexture3D(1, singleton->volIdLinear);
		}
		else {
			singleton->setShaderTexture3D(0, singleton->volIdEmpty);
			singleton->setShaderTexture3D(1, singleton->volIdEmptyLinear);
		}

		singleton->sampleFBO("hmFBOLinear", 2);
		
		if (!isEntity) {
			singleton->setShaderTexture3D(4, singleton->terTextures[resIndex].texId);
		}
		
		
		singleton->setShaderFloat("totLayers", MAX_LAYERS);
		singleton->setShaderFloat("pixelsPerMeter", singleton->pixelsPerMeter);	
		singleton->setShaderFloat("volumePitch", (float)( singleton->volGenFBOX ));
		singleton->setShaderfVec4("worldMinBufInPixels", &(worldMinBufInPixels));
		singleton->setShaderfVec4("worldMaxBufInPixels", &(worldMaxBufInPixels));

		if (isEntity) {
			
		}
		else {
			singleton->setShaderfVec4("worldSizeInPixels", &(singleton->worldSizeInPixels));	
			singleton->setShaderFloat("seaLevel", singleton->getSLInPixels() );
			singleton->setShaderfVec4("blockMinBufInPixels", &(parentBlock->blockMinBufInPixels));
			singleton->setShaderfVec4("blockMaxBufInPixels", &(parentBlock->blockMaxBufInPixels));
		}
		
		


		singleton->setShaderInt("hasTree", (int)hasTree);
		singleton->setShaderInt("hasGeom", (int)hasGeom);
		singleton->setShaderInt("hasTerrain", (int)hasTerrain);
		singleton->setShaderInt("hasLines", (int)hasLines);

		if (hasGeom||hasTree||hasLines) {
			singleton->setShaderInt("paramsPerEntry", (paramsPerEntry / 3) );
			singleton->setShaderInt("numEntries", numEntries);
			singleton->setShaderArrayfVec3("paramArr", singleton->paramArr, totParams / 3);
			singleton->setShaderArray("matCountArr", singleton->matCountArr, E_MAT_PARAM_LENGTH);
		}

		//singleton->setShaderInt("voroCount", voroCount);
		singleton->setShaderArrayfVec4("voroArr", singleton->voroArr, voroCount);

		singleton->drawFSQuad(1.0f);

		if (!isEntity) {
			singleton->setShaderTexture3D(4, 0);
		}

		
		//singleton->setShaderTexture(3,0);
		singleton->unsampleFBO("hmFBOLinear", 2);
		singleton->setShaderTexture3D(1, 0);
		singleton->setShaderTexture3D(0, 0);
		singleton->unbindFBO();
		singleton->unbindShader();


		/////////////////////////////////////////
		// END GEN VOLUME
		/////////////////////////////////////////







		/////////////////////////////////////////
		// BEGIN RENDER VOLUME
		/////////////////////////////////////////


		if (parentGPH->gpuRes != NULL) {
			getCoords();
			singleton->bindShader("RenderVolume");


			for (i = 0; i < MAX_LAYERS; i++) {

				if (
					(
						(i == 0) &&
						(
							(hasTerrain || hasGeom || hasLines) ||
							((MAX_LAYERS < 2)&&(hasWater))
						)
					) ||
					((i == 1) && (hasWater || hasWindow))
				) {
					singleton->bindFBODirect(parentGPH->gpuRes->getFBOS(i), 0);
					//singleton->sampleFBO("volGenFBO0", 0);
					singleton->sampleFBODirect(&(singleton->vgFBOArr[curVGFBO]),0);
					singleton->sampleFBO("frontFaceFBO", 2);
					singleton->sampleFBO("backFaceFBO", 3);

					singleton->setShaderFloat("blendAmount",curBlendAmount);
					singleton->setShaderFloat("curLayer", i);
					//singleton->setShaderFloat("pageDepth", (float)( pageDepth ));
					singleton->setShaderFloat("volumePitch", (float)( singleton->volGenFBOX ));
					singleton->setShaderFloat("tiltAmount", singleton->tiltAmount);
					singleton->setShaderFloat("holderSizeInPagesLog", hspLog);
					singleton->setShaderFloat("bufferMult", (float)(singleton->bufferMult));
					singleton->setShaderFloat("visPageSizeInPixels", (float)(singleton->visPageSizeInPixels));
					singleton->setShaderfVec3("worldMinVisInPixels", &(worldMinVisInPixels));
					singleton->setShaderfVec3("worldMaxVisInPixels", &(worldMaxVisInPixels));
					singleton->setShaderfVec4("scaleAndOffset", &scaleAndOffset);

					//glCallList(singleton->volTris);
					singleton->drawFSQuad(1.0f);

					
					singleton->unsampleFBO("backFaceFBO",3);
					singleton->unsampleFBO("frontFaceFBO",2);
					//singleton->unsampleFBO("volGenFBO0",0);
					singleton->unsampleFBODirect(&(singleton->vgFBOArr[curVGFBO]),0);
					singleton->unbindFBO();
				}

			}

			singleton->unbindShader();
		}


		/////////////////////////////////////////
		// END RENDER VOLUME
		/////////////////////////////////////////




		isDirty = false;
		isRendering = false;

	}
void GamePage::getCoords ()
                         {



		float dx = offsetInPagesLocal.getFX();
		float dy = offsetInPagesLocal.getFY();
		float dz = offsetInPagesLocal.getFZ();

		float pitchSrc = (float)((singleton->visPageSizeInPixels * 2.0f));
		float pitchSrc2 = (pitchSrc) / 2.0f;

		float dxmod = dx * pitchSrc2;
		float dymod = dy * pitchSrc2;
		float dzmod = dz * pitchSrc2;


		// float fx1 = (dxmod - dymod) - pitchSrc2;
		// //float fy1 = (-(dxmod / 2.0f) + -(dymod / 2.0f) + dzmod) - pitchSrc2;
		// float tilt = 1.0-singleton->tiltAmount;
		// float fy1 = (-tilt*dxmod + -tilt*dymod + (1.0-tilt)*2.0f*dzmod) - pitchSrc2;
		
		float tilt = singleton->tiltAmount;
		float itilt = 1.0f-singleton->tiltAmount;
		
		tempVec2.setFXYZ(dxmod,dymod,dzmod);
		singleton->worldToScreenBase(&tempVec1,&tempVec2);
		float fx1 = tempVec1.getFX()*(singleton->fHolderMod);
		float fy1 = tempVec1.getFY()*(singleton->fHolderMod);
		
		
		
		
		fx1 -= pitchSrc2;
		fy1 -= pitchSrc2;
		
		
		float fx2 = fx1 + pitchSrc;
		float fy2 = fy1 + pitchSrc + 2.0;// + 2.0; // TODO: THIS "+ 2.0" is a hack used to cover cracks between pages, it should not be used

		float sx = singleton->holderSizeInPixels;
		float sy = singleton->holderSizeInPixels;


		fx1 = fx1 / sx;
		fy1 = fy1 / sy;
		fx2 = fx2 / sx;
		fy2 = fy2 / sy;

		scaleAndOffset.setFXYZW(
			(fx2 - fx1) / 2.0f,
			(fy2 - fy1) / 2.0f,
			(fx1 + fx2) / 2.0f,
			(fy1 + fy2) / 2.0f

		);

	}
GamePage::~ GamePage ()
                    {

		if (volData != NULL) {
			delete[] volData;
		}
		if (volDataLinear != NULL) {
			delete[] volDataLinear;
		}
	}
#undef LZZ_INLINE
 
// f00351_gamepageholder.h
//

#include "f00351_gamepageholder.e"
#define LZZ_INLINE inline
GamePageHolder::GamePageHolder ()
                         {
		isEntity = false;
		usingPoolId = -1;
		hasTrans = false;
		hasSolids = false;
	}
void GamePageHolder::init (Singleton * _singleton, int _blockId, int _holderId, int trueX, int trueY, int trueZ, bool _isEntity)
          {

		entityGeomCounter = 0;

		int i;
		int j;
		int k;
		int ind;
		
		readyForClear = true;

		isEntity = _isEntity;

		blockId = _blockId;
		holderId = _holderId;

		childrenDirty = true;

		singleton = _singleton;
		usingPoolId = -1;

		holderSizeInPixels = singleton->holderSizeInPixels;
		halfHolderSizeInPixels = holderSizeInPixels*0.5f;
		
		origOffset.setFXYZ(halfHolderSizeInPixels,halfHolderSizeInPixels,halfHolderSizeInPixels);

		offsetInHolders.setIXYZ(trueX,trueY,trueZ);
		offsetInBlocks.copyFrom(&offsetInHolders);
		offsetInBlocks.intDivXYZ(singleton->blockSizeInHolders);
		
		gphMinInPixels.copyFrom(&offsetInHolders);
		gphMaxInPixels.copyFrom(&offsetInHolders);

		gphMaxInPixels.addXYZ(1);

		gphMinInPixels.multXYZ(singleton->holderSizeInPixels);
		gphMaxInPixels.multXYZ(singleton->holderSizeInPixels);

		gphCenInPixels.copyFrom(&gphMaxInPixels);
		gphCenInPixels.addXYZRef(&gphMinInPixels);
		gphCenInPixels.multXYZ(0.5f);
		
		holderSizeInPages = singleton->holderSizeInPages;
		iPageDataVolume = holderSizeInPages*holderSizeInPages*holderSizeInPages;
		pageData = new GamePage*[iPageDataVolume];
		
		

		for (i = 0; i < iPageDataVolume; i++) {
			pageData[i] = NULL;
		}
		
		
		refreshGeom();
		
		
		for (k = 0; k < holderSizeInPages; k++) {
			for (j = 0; j < holderSizeInPages; j++) {
				for (i = 0; i < holderSizeInPages; i++) {
					ind = k*holderSizeInPages*holderSizeInPages + j*holderSizeInPages + i;
					
					if (pageData[ind] == NULL) {
						
						if (isEntity) {
							pageData[ind] = getPageAtCoordsLocal(
								offsetInHolders.getIX()*holderSizeInPages + i,
								offsetInHolders.getIY()*holderSizeInPages + j,
								offsetInHolders.getIZ()*holderSizeInPages + k,
								true
							);
						}
						else {
							pageData[ind] = singleton->gw->getPageAtCoords(
								offsetInHolders.getIX()*holderSizeInPages + i,
								offsetInHolders.getIY()*holderSizeInPages + j,
								offsetInHolders.getIZ()*holderSizeInPages + k,
								true	
							);
						}
						
						
					}
				}
			}
		}
		
	}
GamePage * GamePageHolder::getPageAtCoordsLocal (int x, int y, int z, bool createOnNull)
                                                                                       {
		

		int hx, hy, hz;
		int px, py, pz;
		int gpInd;
		int newX = x;
		int newY = y;
		int newZ = z;
		int ind =
			newZ * holderSizeInPages * holderSizeInPages +
			newY * holderSizeInPages +
			newX;

		GamePage *gp = NULL;

		px = newX % holderSizeInPages;
		py = newY % holderSizeInPages;
		pz = newZ % holderSizeInPages;
		



		gpInd = pz * holderSizeInPages * holderSizeInPages + py * holderSizeInPages + px;

		if (gpInd == -1)
		{
			// prob
			cout << "Invalid holder index\n";
		}
		else
		{
			gp = pageData[gpInd];

			if (gp)
			{

			}
			else
			{
				if (createOnNull)
				{
					pageData[gpInd] = new GamePage();
					gp = pageData[gpInd];
					gp->init(
						singleton,
						this,
						ind,
						x, y, z,
						px, py, pz,
						true
					);
				}
			}
		}

		

		return gp;

		
	}
void GamePageHolder::refreshGeom ()
                           {
		if (isEntity) {
			entityGeomCounter = 0;
			//fetchEntityGeom();
			addNewLinesGeom(singleton->testHuman->baseNode, singleton->pixelsPerMeter);
		}
		else {
			fetchGeom();
		}
	}
void GamePageHolder::clearSet ()
                        { //bool forceClear
		int i;
		

		//bool doClear = forceClear;

		if (usingPoolId == -1) {
			
			if (isEntity) {
				usingPoolId = singleton->entityPool->requestPoolId(blockId,holderId);
				gpuRes = singleton->entityPool->holderPoolItems[usingPoolId];
			}
			else {
				usingPoolId = singleton->gpuPool->requestPoolId(blockId,holderId);
				gpuRes = singleton->gpuPool->holderPoolItems[usingPoolId];
			}
			

			readyForClear = true;
		}

		if (readyForClear) {
			readyForClear = false;
			
			for (i = 0; i < MAX_LAYERS; i++) {
				// clear fbo by binding it with auto flag
				singleton->bindFBODirect(gpuRes->getFBOS(i));
				singleton->unbindFBO();
			}
		}
		
	}
int GamePageHolder::passiveRefresh ()
                             {
		int i;
		int changeCount;
		
		childrenDirty = false;
		changeCount = 0;

		bool finished = true;
				

		for (i = 0; i < iPageDataVolume; i++) {
			
			if (changeCount >= singleton->maxChangesInPages) {
				childrenDirty = true;
				finished = false;
				break;
			}
			
			if (pageData[i] == NULL) {
				
			}
			else {
				if (
					(pageData[i]->hasSolids || pageData[i]->hasTrans)
				) {
					if (pageData[i]->isDirty) {
						pageData[i]->generateVolume();
						changeCount++;
					}
				}
				
				
				
			}
		}
		
		if (finished) {
			
		}
		
		return changeCount;	

	}
void GamePageHolder::refreshChildren (bool refreshImmediate, bool clearEverything, bool refreshUnderground)
          {
		int i;
		
		
		
		
		
		
		readyForClear = true;
		if (clearEverything) {
			clearSet();
		}
		
		for (i = 0; i < iPageDataVolume; i++) {
			if (pageData[i] == NULL) {

			}
			else {
				
				
				if (refreshImmediate) {
					if (
						(
							(pageData[i]->hasSolids || pageData[i]->hasTrans)
						) ||
						refreshUnderground
					) {
						if (refreshUnderground) {
							pageData[i]->isDirty = true;
						}
						pageData[i]->generateVolume(refreshUnderground);
					}
					childrenDirty = false;
				}
				else {
					childrenDirty = true;
					pageData[i]->isDirty = true;
				}
				
				
				
			}
		}
		

		
	}
void GamePageHolder::addNewGeom (int _curBT, int _curAlign, float _baseOffset, FIVector4 * _p1, FIVector4 * _p2, FIVector4 * _rad, FIVector4 * _cornerRad, FIVector4 * _visInsetFromMin, FIVector4 * _visInsetFromMax, FIVector4 * _powerVals, FIVector4 * _powerVals2, FIVector4 * _thickVals, FIVector4 * _matParams, FIVector4 * _centerPoint, FIVector4 * _anchorPoint, int _minRot, int _maxRot)
          {
		
		if (entityGeomCounter >= entityGeom.size()) {
			entityGeom.push_back(new GameGeom());
		}
		
		
		entityGeom[entityGeomCounter]->initBounds(
			_curBT,
			entityGeomCounter,
			entityGeomCounter,
			_curAlign,
			_baseOffset,
			_p1,
			_p2,
			_rad,
			_cornerRad,
			_visInsetFromMin,
			_visInsetFromMax,
			_powerVals,
			_powerVals2,
			_thickVals,
			_matParams,
			_centerPoint,
			_anchorPoint,
			_minRot,
			_maxRot
		);
		entityGeomCounter++;
	}
void GamePageHolder::addNewLinesGeom (GameEntNode * curNode, float scale)
          {
		
		int i;
		
		
		if (curNode->parent == NULL) {
			
		}
		else {
			
			if (curNode == singleton->selectedNode) {
				tempVec.setFXYZ(E_ENT_PARAM_LINES,10.0f,entityGeomCounter);
			}
			else {
				tempVec.setFXYZ(E_ENT_PARAM_LINES,curNode->material,entityGeomCounter);
			}
			
			tempVec2.copyFrom(&(curNode->tbnRotC[0]));
			tempVec2.multXYZ(curNode->boneLengthHalf*scale*curNode->boneLengthScale);
			
			
			if (entityGeomCounter >= entityGeom.size()) {
				entityGeom.push_back(new GameGeom());
			}
			
			entityGeom[entityGeomCounter]->initLines(
				E_CT_LINES,
				entityGeomCounter,
				entityGeomCounter,
				scale,
				
				&origOffset,
				
				&(curNode->orgTrans[1]),
				&(tempVec2),
				&(curNode->tbnRotC[1]),
				&(curNode->tbnRotC[2]),
				&(curNode->tbnRadInMeters0),
				&(curNode->tbnRadInMeters1),
				&(curNode->tbnRadScale0),
				&(curNode->tbnRadScale1),
				&tempVec
				
			);
			entityGeomCounter++;
		}
		
		
		
		for (i = 0; i < curNode->children.size(); i++) {
			addNewLinesGeom(curNode->children[i],scale);
		}
		
		
	}
void GamePageHolder::fetchEntityGeom ()
                               {
		int curBT;
		int curAlign;
		float baseOffset;
		FIVector4 p1;
		FIVector4 p2;
		FIVector4 rad;
		FIVector4 cornerRad;
		FIVector4 visInsetFromMin;
		FIVector4 visInsetFromMax;
		FIVector4 powerVals;
		FIVector4 powerVals2;
		FIVector4 thickVals;
		FIVector4 matParams;
		FIVector4 centerPoint;
		FIVector4 anchorPoint;
		int minRot;
		int maxRot;
		
		
		FIVector4 orig;
		FIVector4 maxRad;
		
		orig.setFXYZRef(&gphMinInPixels);
		orig.addXYZRef(&gphMaxInPixels);
		orig.multXYZ(0.5f);
		
		
		
		
		
		
		curBT = E_CT_OBJECT;
		curAlign = E_ALIGN_MIDDLE;
		baseOffset = 0.0f;
		p1.setFXYZRef(&orig);
		p2.setFXYZRef(&orig);
		rad.setFXYZ(
			halfHolderSizeInPixels,
			halfHolderSizeInPixels,
			halfHolderSizeInPixels	
		);
		cornerRad.setFXYZ(
			halfHolderSizeInPixels,
			halfHolderSizeInPixels,
			halfHolderSizeInPixels	
		);
		visInsetFromMin.setFXYZ(0.0f,0.0f,0.0f);
		visInsetFromMax.setFXYZ(0.0f,0.0f,0.0f);
		powerVals.setFXYZ(2.0f,2.0f,0.0f);
		powerVals2.setFXYZ(2.0f,2.0f,0.0f);
		thickVals.setFXYZ(0.0f,0.0f,0.0f);
		matParams.setFXYZ(E_ENT_PARAM_GEOM,0.0f,0.0f);
		centerPoint.setFXYZRef(&orig);
		anchorPoint.setFXYZRef(&orig);
		minRot = 0;
		maxRot = 0;		
		addNewGeom(
			curBT,
			curAlign,
			baseOffset,
			&p1,
			&p2,
			&rad,
			&cornerRad,
			&visInsetFromMin,
			&visInsetFromMax,
			&powerVals,
			&powerVals2,
			&thickVals,
			&matParams,
			&centerPoint,
			&anchorPoint,
			minRot,
			maxRot
		);
		
		
	}
void GamePageHolder::fetchGeom ()
                         {
		int i;
		int j;
		int k;
		int bufSize = (singleton->visPageSizeInPixels*singleton->bufferMult)*2;
		
		GameBlock* curBlock;
		GamePageHolder* gph;
		FIVector4 start;
		FIVector4 end;
		GameGeom* geom;

		containsGeomIds.clear();

		for (i = -1; i <= 1; i++) {
			for (j = -1; j <= 1; j++) {
				curBlock = singleton->gw->getBlockAtCoords(
					offsetInBlocks.getIX()+i,
					offsetInBlocks.getIY()+j,
					true
				);

				for (k = 0; k < curBlock->gameGeom.size(); k++) {


					geom = curBlock->gameGeom[k];


					start.copyFrom( &(geom->moveMinInPixels) );
					end.copyFrom( &(geom->moveMaxInPixels) );

					start.addXYZ(-bufSize);
					end.addXYZ(bufSize);

					//start.intDivXYZ(singleton->holderSizeInPixels);
					//end.intDivXYZ(singleton->holderSizeInPixels);

					start.clampZ(0.0,singleton->worldSizeInPixels.getFZ()-1.0f);
					end.clampZ(0.0,singleton->worldSizeInPixels.getFZ()-1.0f);

					if (FIVector4::intersect(&start,&end,&gphMinInPixels,&gphMaxInPixels)) {
						containsGeomIds.push_back(intPair());
						containsGeomIds.back().v0 = curBlock->blockId;
						containsGeomIds.back().v1 = k;
					}
				}
			}
		}
	}
void GamePageHolder::unbindGPUResources ()
                                  {

		usingPoolId = -1;
		gpuRes = NULL;
		childrenDirty = true;

	}
#undef LZZ_INLINE
 
// f00352_gameblock.h
//

#include "f00352_gameblock.e"
#define LZZ_INLINE inline
GameBlock::GameBlock ()
                    {
		terData = NULL;
		buildingData = NULL;
	}
void GameBlock::init (Singleton * _singleton, int _blockId, int _x, int _y, int _xw, int _yw)
                                                                                         {


		dirModX[0] = 1;
		dirModX[1] = -1;
		dirModX[2] = 0;
		dirModX[3] = 0;
		dirModX[4] = 0;
		dirModX[5] = 0;

		dirModY[0] = 0;
		dirModY[1] = 0;
		dirModY[2] = 1;
		dirModY[3] = -1;
		dirModY[4] = 0;
		dirModY[5] = 0;

		dirModZ[0] = 0;
		dirModZ[1] = 0;
		dirModZ[2] = 0;
		dirModZ[3] = 0;
		dirModZ[4] = 1;
		dirModZ[5] = -1;

		opDir[0] = 1;
		opDir[1] = 0;
		opDir[2] = 3;
		opDir[3] = 2;
		opDir[4] = 5;
		opDir[5] = 4;

		forceUpdate = false;

		singleton = _singleton;
		blockId = _blockId;
		offsetInBlocks.setIXYZ(_x, _y, 0);
		offsetInBlocksWrapped.setIXYZ(_xw, _yw, 0);

		localGeomCounter = 0;
		lightCounter = 0;

		origin.setFXYZ(0.0f, 0.0f, 0.0f);




		int i;
		int j;
		int k;
		int m;
		int n;
		int p;
		int q;
		
		int tempInt;
		int incVal;
		
		int minRot = 0;
		int maxRot = 0;


		for (i = 0; i < E_CT_LENGTH; i++) {
			isTraversable[i] = false;
			isRoom[i] = false;
			isBase[i] = false;
			isBuilding[i] = false;
			isRoad[i] = false;
			ctClasses[i] = E_CTC_NOTHING;
			layerHash[i] = 0;
		}
		
		
		layerHash[E_CT_FOUNDATION] = 2;
		
		layerHash[E_CT_LANTERN] = 3;
		layerHash[E_CT_WINDOWFRAME] = 1;
		layerHash[E_CT_WINDOW] = 1;
		layerHash[E_CT_DOORWAY] = 1;
		layerHash[E_CT_DOOR] = 1;
		
		
		
		isTraversable[E_CT_ROAD] = true;
		isTraversable[E_CT_CONNECTED] = true;
		
		isRoad[E_CT_ROAD] = true;
		
		isBuilding[E_CT_ROOM_BRICK] = true;
		isBuilding[E_CT_ROOM_TUDOR] = true;
		isBuilding[E_CT_WALKWAY] = true;
		isBuilding[E_CT_ROOF] = true;

		isRoom[E_CT_ROOM_BRICK] = true;
		isRoom[E_CT_ROOM_TUDOR] = true;
		isRoom[E_CT_WALKWAY] = true;

		isBase[E_CT_ROOM_BRICK] = true;
		isBase[E_CT_ROAD] = true;
		
		
		ctClasses[E_CT_NULL] = E_CTC_NOTHING;
		ctClasses[E_CT_CONNECTED] = E_CTC_NOTHING;
		ctClasses[E_CT_ROAD] = E_CTC_ROAD;
		ctClasses[E_CT_ROOF] = E_CTC_ROOF;
		ctClasses[E_CT_WALKWAY_TOP] = E_CTC_ROOM;
		ctClasses[E_CT_ROOM_BRICK] = E_CTC_ROOM;
		ctClasses[E_CT_ROOM_TUDOR] = E_CTC_ROOM;
		ctClasses[E_CT_WALKWAY] = E_CTC_ROOM;
		ctClasses[E_CT_STAIRS] = E_CTC_STAIRS;
		ctClasses[E_CT_LENGTH] = E_CTC_NOTHING;

		int nMax;

		int curAlign = 0;

		float x1;
		float y1;
		float z1;

		float x2;
		float y2;
		float z2;


		float hingeDis = 0.0f;

		//float z;

		float zmax;


		int curDir = 0; // 0:x, 1:y, 2:z

		int roofType = 0;

		maxFloors = 3;

		terDataTexScale = singleton->terDataTexScale;

		blockSizeInHolders = singleton->blockSizeInHolders;
		blockSizeInLots = singleton->blockSizeInLots;

		blockSizeInPixels = singleton->blockSizeInPixels;
		fBlockSizeInPixels = (float)blockSizeInPixels;

		pixelsPerMeter = singleton->pixelsPerMeter;


		float uvSizeInMeters = 1.0;
		float uvSizeInPixels = uvSizeInMeters * pixelsPerMeter; // 64

		float offsetPerFloor = 0.25;
		float floorOffset;

		bool notFound;
		bool foundA;
		bool foundB;
		bool foundC;
		
		bool isInside;
		bool isWingBeg;
		bool isWingEnd;
		bool isWingBeg2;
		bool isWingEnd2;
		
		
		float wingMult;
		float newWingMult;
		float nDir;

		float hm = 0.0f;

		float cr1;
		float cr2;
		float cr3;
		float cr4;

		float doorMod = 0.0f;

		gw = singleton->gw;

		FBOWrapper *fbow = singleton->getFBOWrapper("hmFBO", 0);
		FBOWrapper *fbow2 = singleton->getFBOWrapper("cityFBO", 0);

		int maxLoop;
		int lotX;
		int lotY;
		int lotZ;


		float xmod1;
		float ymod1;
		float zmod1;

		float xmod2;
		float ymod2;
		float zmod2;


		int curLev = 0;
		int kt = 0;
		int kmax = 0;
		int kmin = 0;
		int kstep = 0;

		int testX;
		int testY;


		int baseI = 0;
		int baseJ = 0;


		int res;
		int res2;
		int res3;

		unsigned int nodeFlags = 0;

		int counter;

		int houseColor = 0;
		int lotSizeO2 = singleton->pixelsPerLot / 2;

		int XP = 0;
		int XN = 1;
		int YP = 2;
		int YN = 3;
		int curChannel = 0;

		int ktemp = 0;
		int curId = 0;
		int curBT = 0;
		int curBT2 = 0;
		int curBT3 = 0;
		int curHeight = 0;

		int wingDir;

		floorHeightInMeters = singleton->floorHeightInMeters;
		float roofHeightInMeters;// = singleton->roofHeightInMeters;
		float wallRadInMeters;
		float flushRadInMeters;
		float fi;
		float fj;
		float fk;

		float tempf;
		float pv1;
		float pv2;
		float pv3;
		float pv4;

		float perc1;
		float perc2;
		float baseOffset = 0.0f;
		float holderSizeInPixels = singleton->holderSizeInPixels;

		bool doProc = false;
		bool isVert;
		bool isDif;

		int curInd = 0;
		int testInd = 0;
		int testInd2 = 0;
		int testInd3 = 0;
		int testVal;
		int testVal2;
		int conType;
		int testConType;
		int seaLev;

		int curType;
		uint uiSimp;
		float fSimp;

		int newCount = 0;
		int io, jo, ko;
		
		float doorThickness = 0.0625f;
		float lanternOffset = 0.1875f;
		float doorInset = 0.0f;
		float doorScale = 0.625f;
		
		int iNodeDivsPerLot = singleton->iNodeDivsPerLot;

		iHolderSize = blockSizeInHolders * blockSizeInHolders * blockSizeInHolders;
		holderData = new GamePageHolder*[iHolderSize];
		for (i = 0; i < iHolderSize; i++) {
			holderData[i] = NULL;
		}


		terDataBufAmount = singleton->terDataBufAmount;
		terDataVisSize = singleton->terDataVisSize;
		terDataBufSize = singleton->terDataBufSize;

		terDataVisPitchXY = singleton->terDataVisPitchXY;
		fTerDataVisPitchXY = singleton->terDataVisPitchXY;
		terDataBufPitchXY = singleton->terDataBufPitchXY;
		terDataBufPitchScaledXY = singleton->terDataBufPitchScaledXY;

		terDataVisPitchZ = singleton->terDataVisPitchZ;
		fTerDataVisPitchZ = singleton->terDataVisPitchZ;
		terDataBufPitchZ = singleton->terDataBufPitchZ;
		terDataBufPitchScaledZ = singleton->terDataBufPitchScaledZ;

		
		seaLev = singleton->getSLNormalized()*fTerDataVisPitchZ + terDataBufAmount;

		float fTerDataBufAmount = (float)(singleton->terDataBufAmount);
		float bmodXY = fTerDataBufAmount / (fTerDataVisPitchXY);
		float bmodZ = fTerDataBufAmount / (fTerDataVisPitchZ);

		blockMinBufInPixels.copyFrom(&(offsetInBlocks));
		blockMinBufInPixels.addXYZ(-bmodXY, -bmodXY, -bmodZ);
		blockMinBufInPixels.multXYZ(fBlockSizeInPixels);


		blockMaxBufInPixels.copyFrom(&(offsetInBlocks));
		blockMaxBufInPixels.addXYZ(1.0f + bmodXY, 1.0f + bmodXY, 1.0f + bmodZ);
		blockMaxBufInPixels.multXYZ(fBlockSizeInPixels);


		



		terData = new uint[terDataBufSize];
		buildingData = new BuildingNode[terDataBufSize];

		for (i = 0; i < terDataBufSize; i++) {
			terData[i] = 0;

			buildingData[i].id = -1;
			buildingData[i].visited = 0;
			buildingData[i].mazeIndex = -1;
			buildingData[i].nearTerrain = false;
			buildingData[i].nearAir = false;

			for (j = 0; j < TOT_NODE_VALS; j++) {
				curCon = &(buildingData[i].con[j]);
				curCon->conType = E_CT_NULL;
				curCon->nodeFlags = 0;
				curCon->heightDelta = 0;
				curCon->wingMult = 1.0f;
				curCon->wallRadInMeters = singleton->wallRadInMeters;
			}


		}

		// Create Map Data


		
		// iBuildingNodesPerSideM1 = blockSizeInLots*iNodeDivsPerLot;
		// fBuildingNodesPerSideM1 = (float)iBuildingNodesPerSideM1;
		// iBuildingNodesPerSide = iBuildingNodesPerSideM1 + 1;
		int iMapBufSize = terDataBufPitchXY * terDataBufPitchXY;

		mapData = new MapNode[iMapBufSize];

		for (i = 0; i < iMapBufSize; i++) {
			mapData[i].id = 0;
			for (j = 0; j < TOT_MAP_DIRS; j++) {
				mapData[i].connectionProps[j] = E_CT_NULL;
			}
		}




		// Create Ter Data

		p = 1;
		for (i = 0; i < terDataBufPitchXY; i++) {
			fi = (float)((i / p) * p);
			for (j = 0; j < terDataBufPitchXY; j++) {
				fj = (float)((j / p) * p);
				for (k = 0; k < terDataBufPitchZ; k++) {
					fk = (float)k;


					curInd = getNodeIndex(i, j, k, 0);

					// fSimp = simplexScaledNoise(
					//  4.0f, //octaves
					//  2.0f, //persistence (amount added in each successive generation)
					//  1.0f/32.0f, //scale (frequency)
					//  0.0f, // lo bound
					//  1.0f, // hi bound
					//  fi + offsetInBlocks.getFX()*((float)terDataVisPitchXY) - 1.0f,
					//  fj + offsetInBlocks.getFY()*((float)terDataVisPitchXY) - 1.0f,
					//  fk + offsetInBlocks.getFZ()*((float)terDataVisPitchZ) - 1.0f
					// );
					// uiSimp = clampfZO(fSimp)*255.0f;


					tempVec.setFXYZ(
						fi + offsetInBlocks.getFX()*fTerDataVisPitchXY - fTerDataBufAmount,
						fj + offsetInBlocks.getFY()*fTerDataVisPitchXY - fTerDataBufAmount,
						fk + offsetInBlocks.getFZ()*fTerDataVisPitchZ - fTerDataBufAmount
					);
					tempVec.multXYZ(
						fBlockSizeInPixels / fTerDataVisPitchXY,
						fBlockSizeInPixels / fTerDataVisPitchXY,
						fBlockSizeInPixels / fTerDataVisPitchZ	
					);

					tempf = singleton->getHeightAtPixelPos(tempVec.getFX(), tempVec.getFY());

					if ( tempVec.getFZ() < tempf) {//tempVec.getFZ() < singleton->getSLInPixels() + 4.0*pixelsPerMeter ) {//
						uiSimp = 255;
					} else {
						uiSimp = 0;
					}



					// if ((i+j+k)%2 == 0) {
					//  uiSimp = 255;
					// }
					// else {
					//  uiSimp = 0;
					// }

					terData[curInd] = (uiSimp << 24) | (uiSimp << 16) | (uiSimp << 8) | uiSimp;
				}
			}
		}






		// Get Ter Data Height

		for (i = 0; i < terDataBufPitchXY; i++) {
			for (j = 0; j < terDataBufPitchXY; j++) {

				testInd2 = -1;
				for (k = 0; k < terDataBufPitchZ; k++) {
					curInd = getNodeIndex(i, j, k, 0);

					if (terData[curInd] != 0) {
						singleton->rbHeightStack[curInd] = 0;
					} else {

						if (testInd2 == -1) {
							testInd2 = k;
						}

						testInd = getNodeIndex(i, j, k - 1, 0);

						if (testInd > -1) {
							singleton->rbHeightStack[curInd] = singleton->rbHeightStack[testInd] + 1;
						} else {
							singleton->rbHeightStack[curInd] = 0;
						}
					}
				}

				

				mapData[getMapNodeIndex(i, j, 0)].terHeight = testInd2;
				mapData[getMapNodeIndex(i, j, 0)].adjustedHeight = testInd2;
			}
		}


		












		// Layout Map Roads

		for (i = -1; i <= blockSizeInLots; i++) {
			for (j = -1; j <= blockSizeInLots; j++) {


				for (m = 0; m < 2; m++) {

					switch (m) {
					case 0:
						//curChannel = gw->stChannel;
						curChannel = gw->pathChannel;
						break;
					case 1:
						curChannel = gw->btChannel;
						break;
					}

					//one lot = one map pixel
					lotX = blockSizeInLots * (offsetInBlocks.getIX()) + i;
					lotY = blockSizeInLots * (offsetInBlocks.getIY()) + j;
					res = fbow2->getPixelAtWrapped(lotX, lotY, curChannel);


					// if (
					// 	singleton->getHeightAtPixelPos(lotX*singleton->pixelsPerLot,lotY*singleton->pixelsPerLot) <=
					// 	singleton->getSLInPixels()  + 1.0f * pixelsPerMeter
					// ) {
					// 	curType = E_CT_DOCK;
					// }
					// else {
						curType = E_CT_ROAD;
					//}




					// roads
					for (k = 0; k < TOT_MAP_DIRS; k++) {

						if ( (res & gw->dirFlagsO[k]) > 0) { // has road

							baseI = i * iNodeDivsPerLot + terDataBufAmount;
							baseJ = j * iNodeDivsPerLot + terDataBufAmount;

							for (m = 0; m < iNodeDivsPerLot; m++) {
								switch (k) {
								case 0: // x+
									connectMapNodes(baseI + iNodeDivsPerLot, baseJ + m, baseI + iNodeDivsPerLot, baseJ + m + 1, curType, -1, 0);
									break;
								case 1: // x-
									connectMapNodes(baseI, baseJ + m, baseI, baseJ + m + 1, curType, -1, 0);
									break;
								case 2: // y+
									connectMapNodes(baseI + m, baseJ + iNodeDivsPerLot, baseI + m + 1, baseJ + iNodeDivsPerLot, curType, -1, 0);
									break;
								case 3: // y-
									connectMapNodes(baseI + m, baseJ, baseI + m + 1, baseJ, curType, -1, 0);
									break;

								}
							}

						}
					}
				}


			}
		}

		// houses

		for (i = 0; i < blockSizeInLots; i++) {
			for (j = 0; j < blockSizeInLots; j++) {

				lotX = blockSizeInLots * (offsetInBlocks.getIX()) + i;
				lotY = blockSizeInLots * (offsetInBlocks.getIY()) + j;


				res = fbow2->getPixelAtWrapped(lotX, lotY, gw->houseChannel);
				res3 = fbow2->getPixelAtWrapped(lotX, lotY, gw->btChannel);

				if (res != 0) {
					for (k = 0; k < TOT_MAP_DIRS; k++) {

						res2 = fbow2->getPixelAtWrapped(lotX + dirModX[k], lotY + dirModY[k], gw->houseChannel);

						if ( (res == res2)  && ( touchesMap(i,j,E_CT_ROAD,0) == 0 ) ) { // house id matches, there is a house in that direction




							baseI = i * iNodeDivsPerLot + terDataBufAmount + iNodeDivsPerLot / 2;
							baseJ = j * iNodeDivsPerLot + terDataBufAmount + iNodeDivsPerLot / 2;

							for (m = 0; m < iNodeDivsPerLot / 2; m++) {

								
								switch (k) {
								case 0: // x+
									connectMapNodes(baseI + m, baseJ, baseI + m + 1, baseJ, E_CT_MAINHALL, res % 6, terDataBufAmount+1);
									break;
								case 1: // x-
									connectMapNodes(baseI - (m + 1), baseJ, baseI - m, baseJ, E_CT_MAINHALL, res % 6, terDataBufAmount+1);
									break;
								case 2: // y+
									connectMapNodes(baseI, baseJ + m, baseI, baseJ + m + 1, E_CT_MAINHALL, res % 6, terDataBufAmount+1);
									break;
								case 3: // y-
									connectMapNodes(baseI, baseJ - (m + 1), baseI, baseJ - m, E_CT_MAINHALL, res % 6, terDataBufAmount+1);
									break;

								}


							}


						}
					}
				}

			}
		}



		// connect wings

		for (i = 0; i < terDataBufPitchXY; i++) {
			for (j = 0; j < terDataBufPitchXY; j++) {
				if ( touchesMap(i, j, E_CT_NULL, 0) == 4 ) {

					notFound = true;
					for (k = 0; (k < 4) && notFound; k++) {

						isVert = k >= 2;

						testX = i + dirModX[k];
						testY = j + dirModY[k];

						if ( touchesMap(testX, testY, E_CT_MAINHALL, 0) >= 1 ) {

							if (
								(touches2Map(i, j, E_CT_WING, 0) == 0)
								
								// TODO: must ensure any random number
								// is persistent across the world with iSeedRand2
								
							) {

								if (true) {

									testInd = getMapNodeIndex(testX, testY, 0);

									if (testInd > -1) {
										testInd2 = mapData[testInd].id;
									} else {
										testInd2 = 0;
									}

									connectMapNodes(i, j, testX, testY, E_CT_WING, testInd2, 0 );

									testX = i + dirModX[ gw->opDir[k] ];
									testY = j + dirModY[ gw->opDir[k] ];

									if (touchesMap(testX, testY, E_CT_ROAD, 0) >= 1) {
										connectMapNodes(i, j, testX, testY, E_CT_ROAD, -1, 0);

										

									}
									
									notFound = false;
								}

							}
						}
					}
				}
			}
		}
		
		
		tempVec2.setFXYZ(93.989f, 67.345f, 54.256f);
		
		
		for (i = 0; i < terDataBufPitchXY; i++) {
			for (j = 0; j < terDataBufPitchXY; j++) {
				testInd = getMapNodeIndex(i, j, 0);
				tempVec.setFXYZ(i*2.132f,j*4.10523f,15.23523f);

				mapData[testInd].houseHeight = iGetRandSeeded(&tempVec,&tempVec2, 0, 1);
			}
		}
		
		
		
		
		
		
		
		
		if (singleton->treesOn) {
			for (i = terDataBufAmount*2; i < terDataBufPitchXY-terDataBufAmount*2; i++) {
				for (j = terDataBufAmount*2; j < terDataBufPitchXY-terDataBufAmount*2; j++) {
					if ( (touchesWithinRadMap(i,j,E_CT_TREE, 3, 0) == 0) && (touches2Map(i,j,E_CT_NULL,0) == 16) ) {

						lotX = blockSizeInLots * (offsetInBlocks.getIX()) + i;
						lotY = blockSizeInLots * (offsetInBlocks.getIY()) + j;

						x1 = lotX + (i*blockSizeInPixels)/terDataBufPitchXY;
						y1 = lotY + (j*blockSizeInPixels)/terDataBufPitchXY;

						testInd = getMapNodeIndex(i, j, 0);
						
						tempVec.setFXYZ(i,j,15.0);

						if (
							
							//singleton->getHeightAtPixelPos(x1,y1) >
							//singleton->getSLInPixels() + 2.0f * pixelsPerMeter
							
							( ((float)(mapData[testInd].terHeight))/fTerDataVisPitchZ ) >
							(singleton->getSLNormalized() + 1.0f/255.0f)
							
						) {
							
							
							
							if ( iGetRandSeeded(&tempVec,&tempVec2, 0, 100) > 20 ) {
								mapData[testInd].connectionProps[0] = E_CT_TREE;
							}
						}

						
					}
				}
			}
		}




		// even out adjusted heights for terrain to be within one unit of eachother

		counter = 0;
		
		int newSeaLev = seaLev+1;
		
		do {

			notFound = false;

			for (i = 0; i < terDataBufPitchXY; i++) {
				for (j = 0; j < terDataBufPitchXY; j++) {

					curInd = getMapNodeIndex(i, j, 0);
					
					if (curInd > -1) {
						m = mapData[curInd].adjustedHeight;

						p = 0;

						for (k = 0; k < TOT_MAP_DIRS; k++) {
							testX = i + dirModX[k];// * q;
							testY = j + dirModY[k];// * q;
							testInd = getMapNodeIndex(testX, testY, 0);

							if (testInd > -1) {
								p = max(p, mapData[testInd].adjustedHeight);
							}
						}

						if (p - m > 1) {
							mapData[curInd].adjustedHeight = p - 1;
							notFound = true;
						}
						
						if ( newSeaLev > mapData[curInd].adjustedHeight) {
							mapData[curInd].adjustedHeight = max(mapData[curInd].adjustedHeight, newSeaLev);
							notFound = true;
						}
					}
					


				}
			}

			counter++;

		} while (notFound && (counter < 16));
















		



		


		// building layout

		for (n = 0; n < E_BG_LENGTH; n++) {

			if (n == E_BG_DOORS) {
				incVal = 1;
			}
			else {
				incVal = 2;
			}

			for (ktemp = 0; ktemp < terDataBufPitchZ; ktemp++) {

				if (n == E_BG_FILL_TERRAIN) {
					k = (terDataBufPitchZ - 1) - ktemp;
				}
				else {
					k = ktemp;
				}


				fk = (float)k;
				for (j = 0; j < terDataBufPitchXY; j++) {
					fj = (float)j;
					for (i = 0; i < terDataBufPitchXY; i++) {
						fi = (float)i;

						curInd = getNodeIndex(i, j, k, 0);




						if (curInd > -1) {

							for (m = 0; m < 6; m += incVal) {



								conType = buildingData[curInd].con[m].conType;
								nodeFlags = 0;

								switch (n) {

								case E_BG_ROADS_AND_BUILDINGS:




									if (m < 4) {
										testInd = getMapNodeIndex(i, j, 0);
										testInd2 = getMapNodeIndex(i + dirModX[m], j + dirModY[m], 0);

										if (
											(testInd > -1) &&
											(testInd2 > -1)
										) {

											curBT = mapData[testInd].connectionProps[m];
											//curBT2 = mapData[testInd2].connectionProps[m];

											testVal = mapData[testInd].adjustedHeight;
											testVal2 = mapData[testInd2].adjustedHeight;


											/*
											int _x1,
											int _y1,
											int _z1,
											int _x2,
											int _y2,
											int _z2,
											int ct,
											int id = -1,
											int _heightDelta = 0,
											int _direction = 0,
											float _wallRadInMeters = -1.0f
											*/


											switch (curBT) {
												case E_CT_ROAD:
												case E_CT_MAINHALL:
												case E_CT_WING:
													
													
													if (
														testVal == (k+1)
													) {
														connectNodes(
															i,
															j,
															k,
															i + dirModX[m],
															j + dirModY[m],
															k + dirModZ[m],

															E_CT_FOUNDATION,
															-1,
															testVal2 - testVal, // heightDelta,
															0,
															singleton->wallRadInMeters + 1.0f
														);
													}												
												break;
											}

											switch (curBT) {
											case E_CT_ROAD:

												if (
													testVal == k
												) {
													connectNodes(
														i,
														j,
														k,
														i + dirModX[m],
														j + dirModY[m],
														k + dirModZ[m],

														E_CT_ROAD,
														-1,
														testVal2 - testVal // heightDelta
													);
												}

												break;


											case E_CT_TREE:

												if (
													testVal == k
												) {
													connectNodes(
														i,
														j,
														k,
														i + dirModX[m],
														j + dirModY[m],
														k + dirModZ[m],

														E_CT_TREE,
														-1,
														0 // heightDelta
													);
												}

												break;


											


											/*
											int _x1,
											int _y1,
											int _z1,
											int _x2,
											int _y2,
											int _z2,
											
											int ct,
											int id = -1,
											int _heightDelta = 0,
											int _direction = 0,
											float _wallRadInMeters = -1.0f,
											unsigned int _nodeFlags = 0
											*/


												
											case E_CT_MAINHALL:
											case E_CT_WING:
												if (
													// max(
													// 	mapData[testInd].adjustedHeight,
													// 	mapData[testInd2].adjustedHeight
													// )
													// == k
													
													(
														(k >= mapData[testInd].adjustedHeight) &&
														(k <= mapData[testInd].adjustedHeight + mapData[testInd].houseHeight)
													)
													||
													(
														(k >= mapData[testInd2].adjustedHeight) &&
														(k <= mapData[testInd2].adjustedHeight)
													)
												) {

													tempf = -1.0f;
												
													// if (
													// 	((mapData[testInd].adjustedHeight + mapData[testInd].houseHeight - k) == 0) &&
													// 	(mapData[testInd].houseHeight == 1)
													// ) {
													// 	tempf = singleton->wallRadInMeters + 1.0;
													// }

													connectNodes(
														i,
														j,
														k,
														i + dirModX[m],
														j + dirModY[m],
														k + dirModZ[m],

														E_CT_ROOM_TUDOR,
														mapData[testInd].id,
														0,
														0,
														tempf
													);


												}
												break;
											}


										}


									}


									break;

								// case E_BG_STAIRS: // add stairs
								// 	if (m == 4) {

								// 		// only put stairs in placed building segments
								// 		if (conType > E_CT_CONNECTED) {
								// 			foundA = false;
								// 			testInd = -1;

								// 			// find best direction for stairs
								// 			for (p = 0; p < 4; p++) {
								// 				if (buildingData[curInd].con[p].conType == conType) {
								// 					foundA = true;
								// 					if (p % 2 == 0) {
								// 						if (testInd == -1) {
								// 							testInd = p;
								// 						} else {

								// 						}

								// 					}
								// 					break;
								// 				}
								// 			}

								// 			if (foundA) { // make stairs straight
								// 				if (testInd > -1) {
								// 					connectNodes(
								// 						i,
								// 						j,
								// 						k,
								// 						i + dirModX[testInd],
								// 						j + dirModY[testInd],
								// 						k + dirModZ[testInd],

								// 						E_CT_STAIRS,

								// 						
								// 					);
								// 				}

								// 			} else { // is tower, make winding stairs
								// 				connectNodes(
								// 					i,
								// 					j,
								// 					k,
								// 					i + dirModX[m],
								// 					j + dirModY[m],
								// 					k + dirModZ[m],

								// 					E_CT_STAIRS,

								// 					
								// 				);
								// 			}
								// 		}

								// 	}
								// 	break;


								// case E_BG_REMOVE_REDUNDANT_Z_SEGMENTS:
								
									

								// 	if (m == 4) {
										
								// 		doProc = false;
										
								// 		if ( ctClasses[conType] == E_CTC_ROAD ) {
								// 			if ( touchesPlanarClass(i,j,k+1,E_CTC_ROAD, 0) ) {
								// 				doProc = true;
								// 			}
								// 		}
										
								// 		if (touchesRoomOnLevel(i, j, k)) {
								// 			doProc = true;
								// 		}
										
								// 		if (doProc) {
								// 			connectNodes(
								// 				i,
								// 				j,
								// 				k,
								// 				i,
								// 				j,
								// 				k + 1,

								// 				E_CT_CONNECTED
								// 			);
								// 		}
										
								// 	}


								// 	break;


								case E_BG_ROOFS:





									//if (m < 4) {

									roofType = E_CT_NULL;


									if (conType == E_CT_ROOM_TUDOR) {
										roofType = E_CT_ROOF;
										
									}
									if (conType == E_CT_WALKWAY) {
										roofType = E_CT_WALKWAY_TOP;
									}




									if (roofType != E_CT_NULL) {

										testInd = getNodeIndex(i, j, k + 1, 0);

										if (testInd > -1) {
											testConType = buildingData[testInd].con[m].conType;
											if (testConType <= E_CT_CONNECTED) {


												if (m == 4) {
													foundA = !( touchesRoomOnLevel(i, j, k + 1) );
												} else {
													foundA = true;
												}

												if (foundA) {
													connectNodes(
														i,
														j,
														k + 1,
														i + dirModX[m],
														j + dirModY[m],
														k + dirModZ[m] + 1,

														roofType,

														buildingData[curInd].id,
														
														0,
														0,
														singleton->wallRadInMeters + 0.5f

													);
												}
											}
										}
									}
									//}



									break;

								// case E_BG_BASEMENTS:



								// 	// if (isRoom[conType] && (conType != E_CT_ROOM_BRICK)) {


								// 	// 	if ( !hasRoomBelow(i, j, k, m) ) { //hasTerrainBelow(i,j,k,m,false) ) {
								// 	// 		connectNodes(
								// 	// 			i,
								// 	// 			j,
								// 	// 			k - 1,
								// 	// 			i + dirModX[m],
								// 	// 			j + dirModY[m],
								// 	// 			k + dirModZ[m] - 1,

								// 	// 			E_CT_ROOM_BRICK
								// 	// 		);
								// 	// 	}


								// 	// }
								
									
								// 	if (
								// 		(ctClasses[conType] == E_CTC_ROAD)
								// 		 || (ctClasses[conType] == E_CTC_ROOM)
								// 	) {


										

								// 		if ( !hasRoomBelow(i, j, k, m) ) { //hasTerrainBelow(i,j,k,m,false) ) {
								// 			connectNodes(
								// 				i,
								// 				j,
								// 				k - 1,
								// 				i + dirModX[m],
								// 				j + dirModY[m],
								// 				k + dirModZ[m] - 1,

								// 				E_CT_FOUNDATION,
								// 				-1,
								// 				buildingData[curInd].con[m].heightDelta,
								// 				0,
								// 				singleton->wallRadInMeters - 1.0f
								// 			);
								// 		}


								// 	}
								


								// 	break;

								case E_BG_WING_TIPS:
									if (m < 4) {


										


										testInd = getMapNodeIndex(i, j, 0);
										testInd2 = getMapNodeIndex(i + dirModX[m], j + dirModY[m], 0);
										testInd3 = getMapNodeIndex(i - dirModX[m], j - dirModY[m], 0);

										tempf = 1.0f;
										foundA = false;
										foundB = false;

										if (
											(testInd > -1) && (testInd2 > -1) && (testInd3 > -1)
										) {

											curBT = mapData[testInd].connectionProps[m];
											curBT2 = mapData[testInd2].connectionProps[m];
											curBT3 = mapData[testInd3].connectionProps[m];
											
											
											
											
											// if ( (curBT == E_CT_WING) && (curBT2 == E_CT_ROAD) ) {
											// 	tempf = 0.75f;
											// }
											// if ( (curBT == E_CT_ROAD) && (curBT2 == E_CT_WING) ) {
											// 	tempf = 1.25f;
											// }
											
											if ( (curBT == E_CT_WING) && (curBT2 == E_CT_ROAD) ) {
												foundB = true;
											}
											if ( (curBT == E_CT_ROAD) && (curBT2 == E_CT_WING) ) {
												foundB = true;
											}
											
											if ( (curBT == E_CT_WING) && (curBT3 == E_CT_ROAD) ) {
												foundA = true;
											}
											if ( (curBT == E_CT_ROAD) && (curBT3 == E_CT_WING) ) {
												foundA = true;
											}
											
											
											if (foundA || foundB) {
												if (isBuilding[conType]) {
													//tempf = 0.75f;
												}
												else {//if (isRoad[conType]) {
													//tempf = 1.25f;
												}
											}
											
											
											// if (tempf != 1.0f) {
											// 	foundA = (touchesPlanarClass(i, j, k, ctClasses[conType], 0) == 1);
											// 	foundB = (touchesPlanarClass(i + dirModX[m], j + dirModY[m], k, ctClasses[conType], 0) == 1);
											// }
											
										}
										
										
										for (q = 0; q < MAX_NODE_VALS; q++) {
											
											if (q != layerHash[E_CT_FOUNDATION]) {
												applyWingValues(
													i,
													j,
													k,
													i + dirModX[m],
													j + dirModY[m],
													k + dirModZ[m],
													q,
													foundA,
													foundB,
													tempf
													
												);
											}
											
											
										}
										

										
									}
									break;
								
								case E_BG_DOORS:
								
								
									if (m < 4) {
										
										
										isWingBeg = (buildingData[curInd].con[m].nodeFlags & BC_FLAG_WING_BEG)>0;
										isWingEnd = (buildingData[curInd].con[m].nodeFlags & BC_FLAG_WING_END)>0;
										
										//if ( (m%2) == 0 ) {}
										
										
										
										
										if (
											(ctClasses[conType] == E_CTC_ROOM) &&
											(isWingEnd)
										) {
											
											curBT = E_CT_WINDOWFRAME;
											
											testInd = getNodeIndex(i + dirModX[m], j + dirModY[m], k, 0);
											if (testInd > -1) {
												if (
													ctClasses[buildingData[testInd].con[m].conType] == E_CTC_ROAD	
												) {
													curBT = E_CT_DOORWAY;
												}
											}
											
											
											if ( (m%2) == 0 ) {
												curDir = 1;
											}
											else {
												curDir = -1;
											}
											
											connectNodes(
												i,
												j,
												k,
												i + dirModX[m],
												j + dirModY[m],
												k + dirModZ[m],
												curBT,
												-1,
												0,
												curDir

											);
											
											
											
											if ( (curDir==1) ) { // 
												
												if (curBT == E_CT_DOORWAY) {
													
												}
												else {
													nodeFlags |= BC_FLAG_INSIDE;
												}
												
												/*
												void connectNodes(
													int _x1,
													int _y1,
													int _z1,
													int _x2,
													int _y2,
													int _z2,
													
													int ct,
													int id = -1,
													
													int _heightDelta = 0,
													int _direction = 0,
													
													float _wallRadInMeters = -1.0f,
													unsigned int _nodeFlags = 0
												)
												*/
												
												connectNodes(
													i,
													j,
													k,
													i + dirModX[m],
													j + dirModY[m],
													k + dirModZ[m],
													
													E_CT_LANTERN,
													-1,
													
													0,
													curDir,
													
													-1.0f,
													nodeFlags

												);
											}
											
											
											
										}
										
										
										
										
										
										
										
										
										
										if (conType <= E_CT_CONNECTED) {
											
											doProc = true;
											
											for (q = 0; q < 4; q++) {
												if (
													
													(
														( (q%2) == 1 ) &&
														( (buildingData[curInd].con[q].nodeFlags&BC_FLAG_WING_BEG) > 0)
													)
												) {
													doProc = false;
												}
											}
											
											
											if (doProc) {
												if (touchesPlanarClass(i, j, k, E_CTC_ROOM, 0) > 0) {
													
													if ( (m%2) == 0 ) {
														curDir = 1;
													}
													else {
														curDir = -1;
													}
													
													connectNodes(
														i,
														j,
														k,
														i + dirModX[m],
														j + dirModY[m],
														k + dirModZ[m],
														E_CT_WINDOWFRAME,
														-1,
														0,
														curDir

													);
													
													if (curDir == 1) {
														nodeFlags |= BC_FLAG_INSIDE;
														connectNodes(
															i,
															j,
															k,
															i + dirModX[m],
															j + dirModY[m],
															k + dirModZ[m],
															
															E_CT_LANTERN,
															-1,
															
															0,
															curDir,
															
															-1.0f,
															nodeFlags

														);
													}
													
													
												}
											}
											
											
											
											
											
										}
										
									}
									
									break;
									
									
									
									
								case E_BG_FILL_TERRAIN:
									if (terData[curInd] == 0) {

										testInd = getNodeIndex(i, j, k + 1, 0);

										if (testInd > -1) {
											testVal = terData[testInd];
											if (touchesBaseOnLevel(i, j, k+1, 2) || (testVal != 0)) {
												uiSimp = 255;
												terData[curInd] = (uiSimp << 24) | (uiSimp << 16) | (uiSimp << 8) | uiSimp;
											}
										}
										
									}
									break;
									
								}

							}
						}
					}
				}
			}
		}
		
		
		
		
		if (singleton->cavesOn) {
			makeMazeUG();
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		int minRad = -1;
		int minRadZ = -1;
		// if (pixelsPerMeter <= 32) {
		// 	minRad = -2;
		// }
		// if (pixelsPerMeter <= 64) {
		// 	minRadZ = -2;
		// }
		
		
		bool nearAir = false;
		
		for (k = 0; k < terDataBufPitchZ; k++) {
			for (j = 0; j < terDataBufPitchXY; j++) {
				for (i = 0; i < terDataBufPitchXY; i++) {

					curInd = getNodeIndex(i, j, k, 0);

					

					if (curInd > -1) {
						nearAir = false;
						
						
						
						for (ko = minRadZ; ko <= 1; ko++) {
							for (jo = minRad; jo <= 1; jo++) {
								for (io = minRad; io <= 1; io++) {
									testInd = getNodeIndex(i + io, j + jo, k + ko, 0);

									if (testInd > -1) {
										if (terData[testInd] == 0) {
											buildingData[curInd].nearAir = true;
											nearAir = true;
										}
										else {
											buildingData[curInd].nearTerrain = true;
										}
									}
								}
							}
						}
					}
				}
			}
		}



		// geometry generation
		
		lotX = blockSizeInPixels * offsetInBlocks.getIX();
		lotY = blockSizeInPixels * offsetInBlocks.getIY();
		lotZ = 0;

		for (k = 0; k <= terDataBufPitchZ; k++) {

			for (i = 0; i < terDataBufPitchXY; i++) {

				for (j = 0; j < terDataBufPitchXY; j++) {
					
					

					curInd = getNodeIndex(i, j, k, terDataBufAmount); //terDataBufAmount

					

					if (curInd > -1) {
						for (q = 0; q < TOT_NODE_VALS; q += 2) {

							m = q % MAX_NODE_DIRS;

							curDir = m / 2;

							conType = buildingData[curInd].con[q].conType;

							if (conType != E_CT_NULL) {

								
								

								xmod1 = 0.0f;
								ymod1 = 0.0f;
								zmod1 = 0.0f;
								xmod2 = dirModX[m];
								ymod2 = dirModY[m];
								zmod2 = buildingData[curInd].con[q].heightDelta;

								if (conType == E_CT_FOUNDATION) {
									zmod1 -= 1.0f;
									zmod2 -= 1.0f;
									
									testInd = getMapNodeIndex(i, j, 0);
									testInd2 = getMapNodeIndex(i + dirModX[m], j + dirModY[m], 0);
									
									if ( (testInd > -1) && (testInd2 > -1) ) {
										if (
											mapData[testInd].adjustedHeight == mapData[testInd2].adjustedHeight
										) {
											zmod2 += 1.0;
										}
									}
									
									
								}
								
								
								
								isInside = (buildingData[curInd].con[q].nodeFlags & BC_FLAG_INSIDE) > 0;
								isWingBeg = (buildingData[curInd].con[q].nodeFlags & BC_FLAG_WING_BEG) > 0;
								isWingEnd = (buildingData[curInd].con[q].nodeFlags & BC_FLAG_WING_END) > 0;
								wingMult = buildingData[curInd].con[q].wingMult;
								newWingMult = (wingMult - 1.0f);
								nDir = buildingData[curInd].con[q].direction;
								
								
								
								// todo: fix this!
								wallRadInMeters = buildingData[curInd].con[q].wallRadInMeters;
								flushRadInMeters = wallRadInMeters;
								for (n = 0; n < 4; n++) {
									
									if (
										ctClasses[buildingData[curInd].con[ n ].conType] == E_CTC_ROOM
									) {
										flushRadInMeters = max(
											flushRadInMeters,
											buildingData[curInd].con[ n ].wallRadInMeters
										);
									}
									
									
								}
									
								
								
								
								for (n = 0; n < 2; n++) {
									if (n == 0) {
										
									}
									else {
										
										
										
										if (curDir == E_DIR_X) {
											if (isWingBeg) {
												xmod1 -= newWingMult;
											}
											if (isWingEnd) {
												xmod2 += newWingMult;
											}
										}
										if (curDir == E_DIR_Y) {
											if (isWingBeg) {
												ymod1 -= newWingMult;
											}
											if (isWingEnd) {
												ymod2 += newWingMult;
											}
										}
										
										
										if (
											(conType == E_CT_DOORWAY) ||
											(conType == E_CT_WINDOWFRAME) ||
											(conType == E_CT_LANTERN)
										) {
											
											
											if (isWingBeg||isWingEnd) {
												
													if (curDir == E_DIR_X) {
														if (isWingBeg) {
															xmod2 = xmod1;
														}
														if (isWingEnd) {
															xmod1 = xmod2;
														}
														
													}
													if (curDir == E_DIR_Y) {
														if (isWingBeg) {
															ymod2 = ymod1;
														}
														if (isWingEnd) {
															ymod1 = ymod2;
														}
														
													}
													
													if (nDir == 1.0f) {
														tempf = -1.0f;
													}
													else {
														tempf = 1.0f;
													}
													
													if (conType == E_CT_LANTERN) {
														
														if (isInside) {
															tempf *= 2.0f;	
														}
														else {
															tempf *= -2.0f;	
														}
														
														
													}
													
													
													
													xmod1 += tempf*doorThickness*dirModX[m]*0.5f;
													ymod1 += tempf*doorThickness*dirModY[m]*0.5f;
													xmod2 += tempf*doorThickness*dirModX[m]*0.5f;
													ymod2 += tempf*doorThickness*dirModY[m]*0.5f;
													
													
													
													if (conType == E_CT_LANTERN) {
														
															if (isInside) {
																zmod1 += 0.125f;
																zmod2 += 0.125f;
															}
															else {
																xmod1 += lanternOffset*dirModY[m];
																ymod1 += lanternOffset*dirModX[m];
																xmod2 += lanternOffset*dirModY[m];
																ymod2 += lanternOffset*dirModX[m];
															}
														
															
													}
													else {
														xmod1 -= doorThickness*dirModX[m]*0.5f;
														ymod1 -= doorThickness*dirModY[m]*0.5f;
														xmod2 += doorThickness*dirModX[m]*0.5f;
														ymod2 += doorThickness*dirModY[m]*0.5f;
													}
													
													
												}
												else {
													if (nDir == 1.0f) {
														tempf = (flushRadInMeters*pixelsPerMeter)/(fBlockSizeInPixels / fTerDataVisPitchXY);
													}
													else {
														tempf = 1.0f-(flushRadInMeters*pixelsPerMeter)/(fBlockSizeInPixels / fTerDataVisPitchXY);
													}
													
													xmod1 = tempf*dirModX[m];
													ymod1 = tempf*dirModY[m];
													xmod2 = xmod1;
													ymod2 = ymod1;
													
													if (conType == E_CT_LANTERN) {
														if (nDir == 1.0f) {
															tempf = -1.0f;
														}
														else {
															tempf = 1.0f;
														}
														
														if (isInside) {
															tempf *= 2.0f;	
														}
														else {
															tempf *= -2.0f;	
														}
														
														xmod1 += tempf*doorThickness*dirModX[m]*0.5f;
														ymod1 += tempf*doorThickness*dirModY[m]*0.5f;
														xmod2 += tempf*doorThickness*dirModX[m]*0.5f;
														ymod2 += tempf*doorThickness*dirModY[m]*0.5f;
														
														
													}
													else {
														if (nDir == 1.0f) {
															xmod1 -= doorThickness*dirModX[m];
															ymod1 -= doorThickness*dirModY[m];
														}
														else {
															xmod2 += doorThickness*dirModX[m];
															ymod2 += doorThickness*dirModY[m];
														}
													}
													
													
												}
											
										}
										
										
									}
										
									x1 = lotX + ( ((float)(i - terDataBufAmount) + xmod1 + 0.5f) * fBlockSizeInPixels) / fTerDataVisPitchXY;
									y1 = lotY + ( ((float)(j - terDataBufAmount) + ymod1 + 0.5f) * fBlockSizeInPixels) / fTerDataVisPitchXY;
									z1 = lotZ + ( ((float)(k - terDataBufAmount) + zmod1 + 0.5f) * fBlockSizeInPixels) / fTerDataVisPitchZ;

									x2 = lotX + ( ((float)(i - terDataBufAmount) + xmod2 + 0.5f) * fBlockSizeInPixels) / fTerDataVisPitchXY;
									y2 = lotY + ( ((float)(j - terDataBufAmount) + ymod2 + 0.5f) * fBlockSizeInPixels) / fTerDataVisPitchXY;
									z2 = lotZ + ( ((float)(k - terDataBufAmount) + zmod2 + 0.5f) * fBlockSizeInPixels) / fTerDataVisPitchZ;
									
									if (n == 0) {
										centerPoint.setFXYZ(
											(x1+x2)*0.5f,
											(y1+y2)*0.5f,
											(z1+z2)*0.5f
										);
									}
									
									
								}
								

							
								

								p1.setFXYZ(x1, y1, z1);
								p2.setFXYZ(x2, y2, z2);


								


								switch (conType) {
								case E_CT_NULL:
								case E_CT_CONNECTED:
								case E_CT_ROAD:
									nMax = 0;
									break;
								case E_CT_DOORWAY:
								case E_CT_WINDOWFRAME:
									nMax = 3;
									break;
								default:
									nMax = 1;
									break;

								}


								// todo: fix this
								if (ctClasses[conType] == E_CTC_ROOM) {
									roofHeightInMeters = singleton->wallRadInMeters;
								}
								else {
									roofHeightInMeters = wallRadInMeters;
									
								}



								

								for (n = 0; n < nMax; n++) {
									
									curBT = conType;
									rad.setFXYZ(
										wallRadInMeters * pixelsPerMeter,
										wallRadInMeters * pixelsPerMeter,
										(floorHeightInMeters * 0.5f + roofHeightInMeters)*pixelsPerMeter
									);
									cornerRad.setFXYZ(
										wallRadInMeters * pixelsPerMeter,
										wallRadInMeters * pixelsPerMeter,
										roofHeightInMeters * pixelsPerMeter
									);
									powerVals.setFXYZ(2.0f, 1.0f, 0.0f);
									powerVals2.setFXYZ(2.0f, 1.0f, 0.0f);
									
									
									switch (buildingData[curInd].con[q].heightDelta) {
										case -1:
											powerVals.setFZ(1.0f);
											powerVals2.setFZ(0.0f);
										break;
										
										case 0:
											powerVals.setFZ(0.0f);
											powerVals2.setFZ(0.0f);
											
										break;
										
										case 1:
											powerVals.setFZ(0.0f);
											powerVals2.setFZ(1.0f);
											
										break;
										default:
											cout << "invalid height delta of " << buildingData[curInd].con[q].heightDelta << "\n";
										break;
									}
									
									
									
									
									thickVals.setFXYZ(0.0f, floorHeightInMeters, 0.0f);
									baseOffset = 0.0f;
									curAlign = E_ALIGN_MIDDLE;
									minRot = 0;
									maxRot = 0;
									anchorPoint.setFXYZRef(&centerPoint);

									switch (conType) {
										
										case E_CT_NULL:
												
											break;
										
										
										case E_CT_TREE:
											baseOffset = 0.0f;
											matParams.setFXYZ(E_MAT_PARAM_TREE, 0.0, 0.0f);

											visInsetFromMin.setFXYZ(0.0f,0.0f,0.0f);
											visInsetFromMax.setFXYZ(0.0f,0.0f,0.0f);
											
											tempVec4.setFXYZRef(&p1);
											tempVec4.addXYZ(0.0f,0.0f,2.0f*pixelsPerMeter);

											tempVec.setIXYZ(i,j,k);
											tempVec.multXYZ(102.33,305.44,609.121);
											tempVec2.setFXYZ(93.989f, 67.345f, 54.256f);
											tempInt = iGetRandSeeded(&tempVec,&tempVec2,0,E_PT_LENGTH/2 - 1);
											
											
											
											singleton->gamePlants[tempInt]->init(
												singleton,
												&(GamePlant::allPlantRules[tempInt*2+1]),
												&(GamePlant::allPlantRules[tempInt*2]),
												&origin
											);
											matParams.setFY(tempInt*2+1);
											addPlantNodes(singleton->gamePlants[tempInt]->rootsNode, &tempVec4, 1.0f);
											matParams.setFY(tempInt*2);
											addPlantNodes(singleton->gamePlants[tempInt]->trunkNode, &tempVec4, 1.0f);
											
											
											
											// if (tempf > 0.66) {
											// 	bareTree.init(
											// 		singleton,
											// 		&(GamePlant::allPlantRules[E_PT_BARE_OAK_ROOTS]),
											// 		&(GamePlant::allPlantRules[E_PT_BARE_OAK_TRUNK]),
											// 		&origin
											// 	);
											// 	matParams.setFY()
											// 	addPlantNodes(bareTree.rootsNode, &tempVec4, 1.0f);
											// 	addPlantNodes(bareTree.trunkNode, &tempVec4, 1.0f);
											// }
											// else if (tempf > 0.33) {
											// 	oakTree2.init(
											// 		singleton,
											// 		&(GamePlant::allPlantRules[E_PT_OAK2_ROOTS]),
											// 		&(GamePlant::allPlantRules[E_PT_OAK2_TRUNK]),
											// 		&origin
											// 	);

											// 	addPlantNodes(oakTree2.rootsNode, &tempVec4, 1.0f);
											// 	addPlantNodes(oakTree2.trunkNode, &tempVec4, 1.0f);
											// }
											// else {
											// 	oakTree.init(
											// 		singleton,
											// 		&(GamePlant::allPlantRules[E_PT_OAK_ROOTS]),
											// 		&(GamePlant::allPlantRules[E_PT_OAK_TRUNK]),
											// 		&origin
											// 	);

											// 	addPlantNodes(oakTree.rootsNode, &tempVec4, 1.0f);
											// 	addPlantNodes(oakTree.trunkNode, &tempVec4, 1.0f);
											// }

											
											
											goto SKIP_ADD_GEOM;
											
										break;
										
										
										case E_CT_LANTERN:
										

											matParams.setFXYZ(E_MAT_PARAM_LANTERN, 0.0, 0.0f);

											curAlign = E_ALIGN_MIDDLE;

											// floorHeight = 0.5f;
											// roofHeight = 0.25f;
											// baseOffset = 0.0f;
											rad.setFXYZ(
												(0.25f)*pixelsPerMeter,
												(0.25f)*pixelsPerMeter,
												(0.5f)*pixelsPerMeter
											);
											cornerRad.setFXYZ(
												(0.0625f)*pixelsPerMeter,
												(0.0625f)*pixelsPerMeter,
												(0.25f)*pixelsPerMeter
											);
											thickVals.setFX(0.25f*pixelsPerMeter);											

											visInsetFromMin.setFXYZ(0.0f,0.0f,cornerRad.getFZ() - 0.0625*pixelsPerMeter);
											visInsetFromMax.setFXYZ(0.0f,0.0f,0.0f);

											powerVals.setFXYZ(2.0f, 1.0f, 0.0f);
											powerVals2.setFXYZRef(&powerVals);

											curBT = E_CT_LANTERN;




											
										break;
										
										case E_CT_DOORWAY:
										case E_CT_WINDOWFRAME:
										
											if (conType == E_CT_DOORWAY) {
												tempf = 0.0f;
											}
											else {
												tempf = 1.0f;
											}
										
											if (n == 0) {
												matParams.setFXYZ(E_MAT_PARAM_DOORWAY, 0.0f, tempf);
												doorMod = 0.0f;

											}
											else {
												matParams.setFXYZ(E_MAT_PARAM_DOOR, 0.0f, tempf);
												doorMod = 0.25f;
											}
											
											curAlign = E_ALIGN_BOTTOM;
											baseOffset = -(rad.getFZ() - (cornerRad.getFZ()+(0.25+doorMod)*pixelsPerMeter) ) + tempf*2.0f*pixelsPerMeter;
											

											
											floorHeight = 2.0f-doorMod;
											roofHeight = 1.5f-doorMod;
											
											rad.setFXYZ(
												(1.5f - doorMod)*pixelsPerMeter,
												(1.5f - doorMod)*pixelsPerMeter,
												(floorHeight*0.5f + roofHeight + tempf*0.5f)*pixelsPerMeter
											);
											cornerRad.setFXYZ(
												(1.5f - doorMod)*pixelsPerMeter,
												(1.5f - doorMod)*pixelsPerMeter,
												roofHeight*pixelsPerMeter
											);
											thickVals.setFX(0.25f*pixelsPerMeter);	
										
											doorInset = doorMod*pixelsPerMeter*1.25f;
											
											
											anchorPoint.copyFrom(&p1);
											anchorPoint.addXYZRef(&p2);
											anchorPoint.multXYZ(0.5f);
											
											hingeDis = p1.distance(&p2)*0.5f;
											
											switch (n) {
												case 0:
												
													if (conType == E_CT_DOORWAY) {
														curBT = E_CT_DOORWAY;
													}
													else {
														curBT = E_CT_WINDOWFRAME;
													}
												
													cr1 = 0.0f;
													cr2 = 0.0f;
												break;
												
												case 1:
												
													if (conType == E_CT_DOORWAY) {
														curBT = E_CT_DOOR;
													}
													else {
														curBT = E_CT_WINDOW;
													}
												
													
													cr1 = 0.0f;
													cr2 = 1.0f;
													
													if (curDir == E_DIR_Y) {
														anchorPoint.addXYZ(-(rad.getFX()+hingeDis),0.0f,0.0f);
													}
													else {
														anchorPoint.addXYZ(0.0f,-(rad.getFY()+hingeDis),0.0f);
													}
													
													
													if (
														((curDir == E_DIR_Y)&&(nDir==1)) ||
														((curDir == E_DIR_X)&&(nDir==-1))
													) { //(m == 1) || (m == 2) ) {
														minRot = 0;
														maxRot = 1;
													}
													else {
														minRot = -1;
														maxRot = 0;
													}
													
												
													
												break;
												
												case 2:
													
													
													if (conType == E_CT_DOORWAY) {
														curBT = E_CT_DOOR;
													}
													else {
														curBT = E_CT_WINDOW;
													}
													
													cr1 = 1.0f;
													cr2 = 0.0f;
													
													if (curDir == E_DIR_Y) {
														anchorPoint.addXYZ(rad.getFX()+hingeDis,0.0f,0.0f);
													}
													else {
														anchorPoint.addXYZ(0.0f,rad.getFY()+hingeDis,0.0f);
													}
													

													if (
														((curDir == E_DIR_X)&&(nDir==1)) ||
														((curDir == E_DIR_Y)&&(nDir==-1))
													) { //(m == 0) || (m == 3) ) {
														minRot = 0;
														maxRot = 1;
													}
													else {
														minRot = -1;
														maxRot = 0;
													}
													
													
												break;
											}
											
											if (curDir == E_DIR_X) {
												visInsetFromMin.setFXYZ(cornerRad.getFX()+doorInset, cr1*rad.getFY(), cornerRad.getFZ());
												visInsetFromMax.setFXYZ(cornerRad.getFX()+doorInset, cr2*rad.getFY(), 0.0f);
											}
											else {
												visInsetFromMin.setFXYZ(cr1*rad.getFX(), cornerRad.getFY()+doorInset, cornerRad.getFZ());
												visInsetFromMax.setFXYZ(cr2*rad.getFX(), cornerRad.getFY()+doorInset, 0.0f);
											}

											
											
											powerVals.setFX(2.0f);
											powerVals.setFY(2.0f);
											powerVals2.setFX(2.0f);
											powerVals2.setFY(2.0f);
											
											
										
											
											
											
										
											break;
											
										case E_CT_FOUNDATION:

											//testInd = getMapNodeIndex(i, j, 0);
											//testInd2 = getMapNodeIndex(i + dirModX[m], j + dirModY[m], 0);

											visInsetFromMin.setFXYZ(0.0f, 0.0f, roofHeightInMeters * pixelsPerMeter);
											visInsetFromMax.setFXYZ(0.0f, 0.0f, roofHeightInMeters * pixelsPerMeter);
											
											
											baseOffset = 0.0f;// -(floorHeightInMeters)*pixelsPerMeter;
											rad.addXYZ(
												0.0f,
												0.0f,
												(floorHeightInMeters+1.0f)*pixelsPerMeter
											);

											
											if (
												singleton->getHeightAtPixelPos(p1.getFX(), p1.getFY()) <=
												singleton->getSLInPixels()  + 2.0f * pixelsPerMeter
											) {
												rad.addXYZ(
													0.0f,
													0.0f,
													(2.0f)*pixelsPerMeter
												);
												matParams.setFXYZ(E_MAT_PARAM_FOUNDATION, E_MAT_SUBPARAM_DOCK, 0.0f);
											}
											else {
												matParams.setFXYZ(E_MAT_PARAM_FOUNDATION, E_MAT_SUBPARAM_BRICK, 0.0f);
											}

											

											

											break;
										case E_CT_ROOM_BRICK:
											matParams.setFXYZ(E_MAT_PARAM_BUILDING, E_MAT_SUBPARAM_BRICK, 0.0f);
											visInsetFromMin.setFXYZ(0.0f, 0.0f, roofHeightInMeters * pixelsPerMeter);
											visInsetFromMax.setFXYZ(0.0f, 0.0f, roofHeightInMeters * pixelsPerMeter);
											break;
										case E_CT_ROOM_TUDOR:

											//rad.addXYZ(-0.5f*pixelsPerMeter,-0.5f*pixelsPerMeter,0.0f);
											//cornerRad.addXYZ(-0.5f*pixelsPerMeter);

											matParams.setFXYZ(E_MAT_PARAM_BUILDING, E_MAT_SUBPARAM_TUDOR, 0.0f);
											visInsetFromMin.setFXYZ(0.0f, 0.0f, roofHeightInMeters * pixelsPerMeter);
											visInsetFromMax.setFXYZ(0.0f, 0.0f, roofHeightInMeters * pixelsPerMeter);
											break;

										// case E_CT_WALKWAY:

										// 	matParams.setFXYZ(E_MAT_PARAM_WALKWAY, E_MAT_SUBPARAM_BRICK_ARCH, 0.0f);
										// 	visInsetFromMin.setFXYZ(0.0f, 0.0f, roofHeightInMeters * pixelsPerMeter);
										// 	visInsetFromMax.setFXYZ(0.0f, 0.0f, roofHeightInMeters * pixelsPerMeter);

										// 	break;

										// case E_CT_WALKWAY_TOP:
										// 	matParams.setFXYZ(E_MAT_PARAM_WALKWAY_TOP, E_MAT_SUBPARAM_BRICK_ARCH, 0.0f);
										// 	visInsetFromMin.setFXYZ(0.0f, 0.0f, roofHeightInMeters * pixelsPerMeter);
										// 	visInsetFromMax.setFXYZ(0.0f, 0.0f, (roofHeightInMeters + (floorHeightInMeters * 0.75))*pixelsPerMeter);

										// 	break;

										case E_CT_ROOF:
											baseOffset = -floorHeightInMeters * pixelsPerMeter;
											matParams.setFXYZ(E_MAT_PARAM_ROOF, E_MAT_SUBPARAM_TUDOR, buildingData[curInd].id);

											if (curDir == E_DIR_Z) {
												visInsetFromMin.setFXYZ(0.0f, 0.0f, (roofHeightInMeters + floorHeightInMeters * 2.0f)*pixelsPerMeter);
											} else {
												visInsetFromMin.setFXYZ(0.0f, 0.0f, (roofHeightInMeters + floorHeightInMeters)*pixelsPerMeter);
											}
											visInsetFromMax.setFXYZ(0.0f, 0.0f, 0.0f);
											break;

										// case E_CT_STAIRS:

										// 	switch (curDir) {
										// 	case E_DIR_X:
										// 		rad.multXYZ(0.5f, 0.5f, 1.0f);
										// 		cornerRad.multXYZ(0.5f, 0.5f, 1.0f);

										// 		if ((k % 2) == 0) {
										// 			visInsetFromMin.setFXYZ(cornerRad.getFX(), rad.getFY(), roofHeightInMeters * pixelsPerMeter);
										// 			visInsetFromMax.setFXYZ(cornerRad.getFX(), 0.0f, roofHeightInMeters * pixelsPerMeter);
										// 		} else {
										// 			visInsetFromMin.setFXYZ(cornerRad.getFX(), 0.0f, roofHeightInMeters * pixelsPerMeter);
										// 			visInsetFromMax.setFXYZ(cornerRad.getFX(), rad.getFY(), roofHeightInMeters * pixelsPerMeter);
										// 		}
										// 		break;

										// 	case E_DIR_Y:
										// 		rad.multXYZ(0.5f, 0.5f, 1.0f);
										// 		cornerRad.multXYZ(0.5f, 0.5f, 1.0f);

										// 		if ((k % 2) == 0) {
										// 			visInsetFromMin.setFXYZ(rad.getFX(), cornerRad.getFY(), roofHeightInMeters * pixelsPerMeter);
										// 			visInsetFromMax.setFXYZ(0.0f, cornerRad.getFY(), roofHeightInMeters * pixelsPerMeter);
										// 		} else {
										// 			visInsetFromMin.setFXYZ(0.0f, cornerRad.getFY(), roofHeightInMeters * pixelsPerMeter);
										// 			visInsetFromMax.setFXYZ(rad.getFX(), cornerRad.getFY(), roofHeightInMeters * pixelsPerMeter);
										// 		}

										// 		break;

										// 	case E_DIR_Z:
										// 		rad.multXYZ(0.75f, 0.75f, 1.0f);
										// 		cornerRad.multXYZ(0.75f, 0.75f, 1.0f);
										// 		visInsetFromMin.setFXYZ(0.0f, 0.0f, roofHeightInMeters * pixelsPerMeter);
										// 		visInsetFromMax.setFXYZ(0.0f, 0.0f, roofHeightInMeters * pixelsPerMeter);

										// 		break;
										// 	}

										// 	matParams.setFXYZ(E_MAT_PARAM_STAIRS, E_MAT_SUBPARAM_NONE, (float)(k % 2));
										// 	baseOffset = 1.0f * pixelsPerMeter;

										// 	break;

										
									}

									if (curDir != E_DIR_Z) {
										

										switch (conType) {
										case E_CT_ROAD:
										case E_CT_ROOF:
										case E_CT_ROOM_TUDOR:
										case E_CT_ROOM_BRICK:

											// }

											if (curDir == E_DIR_X) {
												if (isWingBeg) {
													visInsetFromMin.setFX(cornerRad.getFX());
												}
												if (isWingEnd) {
													visInsetFromMax.setFX(cornerRad.getFX());
												}
											}
											if (curDir == E_DIR_Y) {
												if (isWingBeg) {
													visInsetFromMin.setFY(cornerRad.getFY());
												}
												if (isWingEnd) {
													visInsetFromMax.setFY(cornerRad.getFY());
												}
											}


											break;
										}
									}


									addNewGeom(
										curBT,
										curAlign,
										baseOffset,
										&p1,
										&p2,
										&rad,
										&cornerRad,
										&visInsetFromMin,
										&visInsetFromMax,
										&powerVals,
										&powerVals2,
										&thickVals,
										&matParams,
										&centerPoint,
										&anchorPoint,
										minRot,
										maxRot
									);
									
SKIP_ADD_GEOM:
									
									;

								}

							}
						}


					}


				}
			}
		}



	}
int GameBlock::getNodeIndexClamped (int _x, int _y, int _z)
                                                        {

	
			int x = clamp(_x,0,terDataBufPitchXY-1);
			int y = clamp(_y,0,terDataBufPitchXY-1);
			int z = clamp(_z,0,terDataBufPitchZ-1);
		
			return x + y * terDataBufPitchXY + z * terDataBufPitchXY * terDataBufPitchXY;
		
	}
int GameBlock::getNodeIndex (int x, int y, int z, int bufAmount)
                                                             {

		if (
			(x < bufAmount) ||
			(y < bufAmount) ||
			(z < bufAmount) ||
			(x >= terDataBufPitchXY - bufAmount) ||
			(y >= terDataBufPitchXY - bufAmount) ||
			(z >= terDataBufPitchZ - bufAmount)
		) {
			return -1;
		} else {
			return x + y * terDataBufPitchXY + z * terDataBufPitchXY * terDataBufPitchXY;
		}
	}
int GameBlock::touchesPlanarBN (int x, int y, int z, int buildingType, int bufAmount)
                                                                                  {
		int i;
		int tot = 0;
		int ind;

		ind = getNodeIndex(x, y, z, bufAmount);

		if (ind > -1) {
			for (i = 0; i < 4; i++) {
				if (buildingData[ind].con[i].conType == buildingType) {
					tot++;
				}
			}
		}

		return tot;
	}
int GameBlock::touchesPlanarClass (int x, int y, int z, int classType, int bufAmount)
                                                                                  {
		int i;
		int tot = 0;
		int ind;

		ind = getNodeIndex(x, y, z, bufAmount);

		if (ind > -1) {
			for (i = 0; i < 4; i++) {
				if (ctClasses[buildingData[ind].con[i].conType] == classType) {
					tot++;
				}
			}
		}

		return tot;
	}
bool GameBlock::isLCorner (int x, int y, int z, int classType, bool includeSingle)
                                                                               {
		int i;
		int tot = 0;
		int ind;
		

		ind = getNodeIndex(x, y, z, 0);

		if (ind > -1) {
			for (i = 0; i < 4; i++) {
				if ( ctClasses[buildingData[ind].con[i].conType] == classType) {
					tot++;
				}
			}
			
			if ((tot == 1)&&includeSingle) {
				return true;
			}
			
			if (tot == 2) {
				tot = 0;
				for (i = 0; i < 2; i++) {
					if (ctClasses[buildingData[ind].con[i].conType] == classType) {
						tot++;
					}
				}
				
				if (tot == 1) {
					return true;
				}
				
			}
			
		}
		
		

		return false;
	}
void GameBlock::applyWingValues (int _x1, int _y1, int _z1, int _x2, int _y2, int _z2, int cnum, bool isWingBeg, bool isWingEnd, float multiplier)
          {


		// 0: x+
		// 1: x-
		// 2: y+
		// 3: y-
		// 4: z+
		// 5: z-

		int x1 = _x1;
		int y1 = _y1;
		int x2 = _x2;
		int y2 = _y2;
		int z1 = _z1;
		int z2 = _z2;

		if (x1 > x2) {
			std::swap(x1, x2);
		}
		if (y1 > y2) {
			std::swap(y1, y2);
		}
		if (z1 > z2) {
			std::swap(z1, z2);
		}

		int baseDir = 0;

		int ind1 = getNodeIndex(x1, y1, z1, 0);
		int ind2 = getNodeIndex(x2, y2, z2, 0);
		
		int finalInd1;
		int finalInd2;
		
		uint tempFlags;

		if ((ind1 < 0) || (ind2 < 0)) {
			// invalid connection
		} else {

			if ((x1 == x2) && (y1 == y2)) {
				// up/down connection
				baseDir = 4;
			} else {
				if (x1 == x2) {
					// north/south connection
					baseDir = 2;
				}
				if (y1 == y2) {
					// east/west connection
					baseDir = 0;
				}
			}

			finalInd1 = baseDir + cnum * MAX_NODE_DIRS;
			finalInd2 = baseDir + 1 + cnum * MAX_NODE_DIRS;
			
			
			
			// WAS DOING: MAKE SURE TO SET FLAGS EXPLICITLY, NO OR "|" operator
			
			
			tempFlags = 0;
			if (isWingBeg) {
				tempFlags |= BC_FLAG_WING_BEG;
			}
			if (isWingEnd) {
				tempFlags |= BC_FLAG_WING_END;
			}
			
			buildingData[ind1].con[finalInd1].nodeFlags &= ~(BC_FLAG_WING_BEG|BC_FLAG_WING_END);
			buildingData[ind2].con[finalInd2].nodeFlags &= ~(BC_FLAG_WING_BEG|BC_FLAG_WING_END);
			
			buildingData[ind1].con[finalInd1].nodeFlags |= tempFlags;
			buildingData[ind1].con[finalInd1].wingMult = multiplier;

			tempFlags = 0;
			if (isWingEnd) {
				tempFlags |= BC_FLAG_WING_BEG;
			}
			if (isWingBeg) {
				tempFlags |= BC_FLAG_WING_END;
			}

			buildingData[ind2].con[finalInd2].nodeFlags |= tempFlags;
			//buildingData[ind2].con[finalInd2].wingMult = 2.0f-multiplier;
			
			

		}
	}
void GameBlock::addPlantNodes (GamePlantNode * curPlantNode, FIVector4 * orig, float scale)
                                                                                       {
		int i;

		float begThickness;
		float endThickness;

		if (curPlantNode->parent == NULL) {

		}
		else {

			if (curPlantNode->parent->parent == NULL) {
				tempVec.setFXYZ(0.0f,0.0f,0.0f); //Ref(&(curPlantNode->parent->begPoint));

				begThickness = curPlantNode->midThickness;
				endThickness = curPlantNode->midThickness;

			}
			else {
				tempVec.setFXYZRef(&(curPlantNode->parent->begPoint));
				tempVec.addXYZRef(&(curPlantNode->parent->endPoint));
				tempVec.multXYZ(0.5f);

				begThickness = curPlantNode->parent->midThickness;
				endThickness = curPlantNode->midThickness;
			}


			// if (curPlantNode->numChildren == 0) {
			// 	endThickness = 0.5f*singleton->pixelsPerMeter;
			// }

			
			
			tempVec2.setFXYZRef(&(curPlantNode->begPoint));
			tempVec2.addXYZRef(&(curPlantNode->endPoint));
			tempVec2.multXYZ(0.5f);
			
			tempVec3.setFXYZRef(&(curPlantNode->begPoint));

			tempVec.multXYZ(scale);
			tempVec2.multXYZ(scale);
			tempVec3.multXYZ(scale);

			tempVec.addXYZRef(orig);
			tempVec2.addXYZRef(orig);
			tempVec3.addXYZRef(orig);

			gameGeom.push_back(new GameGeom());
			gameGeom.back()->initTree(
				
				E_CT_TREE,
				localGeomCounter,
				singleton->geomCounter,
								
				&tempVec,
				&tempVec2,
				&tempVec3,

				begThickness*scale,//curPlantNode->begThickness,
				endThickness*scale,//curPlantNode->endThickness,	
				curPlantNode->sphereRad*scale,			
										
				&matParams
			);
			singleton->geomCounter++;
			localGeomCounter++;
		}

		

		for (i = 0; i < curPlantNode->numChildren; i++) {
			addPlantNodes( &(curPlantNode->children[i]), orig, scale);
		}
	}
void GameBlock::addNewGeom (int _curBT, int _curAlign, float _baseOffset, FIVector4 * _p1, FIVector4 * _p2, FIVector4 * _rad, FIVector4 * _cornerRad, FIVector4 * _visInsetFromMin, FIVector4 * _visInsetFromMax, FIVector4 * _powerVals, FIVector4 * _powerVals2, FIVector4 * _thickVals, FIVector4 * _matParams, FIVector4 * _centerPoint, FIVector4 * _anchorPoint, int _minRot, int _maxRot)
          {
		
		
		
		
		
		gameGeom.push_back(new GameGeom());
		gameGeom.back()->initBounds(
			_curBT,
			localGeomCounter,
			singleton->geomCounter,
			_curAlign,
			_baseOffset,
			_p1,
			_p2,
			_rad,
			_cornerRad,
			_visInsetFromMin,
			_visInsetFromMax,
			_powerVals,
			_powerVals2,
			_thickVals,
			_matParams,
			_centerPoint,
			_anchorPoint,
			_minRot,
			_maxRot
		);
		
		if (_curBT == E_CT_LANTERN) {
			lightVec.setFXYZ(1.0f,0.5f,0.1f);
			gameLights.push_back(new GameLight());
			gameLights.back()->init(
				lightCounter,
				singleton->lightCounter,
				_p1,
				&lightVec
			);
			singleton->lightCounter++;
			lightCounter++;
			gameGeom.back()->light = gameLights.back();
		}
		
		
		
		singleton->geomCounter++;
		localGeomCounter++;
	}
void GameBlock::connectNodes (int _x1, int _y1, int _z1, int _x2, int _y2, int _z2, int ct, int id, int _heightDelta, int _direction, float _wallRadInMeters, unsigned int _nodeFlags)
          {


		// 0: x+
		// 1: x-
		// 2: y+
		// 3: y-
		// 4: z+
		// 5: z-

		float wallRad = _wallRadInMeters;
		if (wallRad == -1.0f) {
			wallRad = singleton->wallRadInMeters;
		}

		int x1 = _x1;
		int y1 = _y1;
		int x2 = _x2;
		int y2 = _y2;
		int z1 = _z1;
		int z2 = _z2;

		if (x1 > x2) {
			std::swap(x1, x2);
		}
		if (y1 > y2) {
			std::swap(y1, y2);
		}
		if (z1 > z2) {
			std::swap(z1, z2);
		}

		int ind1 = getNodeIndex(x1, y1, z1, 0);
		int ind2 = getNodeIndex(x2, y2, z2+_heightDelta, 0);
		int baseDir = 0;
		
		int resInd1;
		int resInd2;
		
		int cnum = layerHash[ct];

		if ((ind1 < 0) || (ind2 < 0)) {
			// invalid connection
		} else {

			if (id >= 0) {
				buildingData[ind1].id = id;
				buildingData[ind2].id = id;
			}


			if ((x1 == x2) && (y1 == y2)) {
				// up/down connection
				baseDir = 4;
			} else {
				if (x1 == x2) {
					// north/south connection
					baseDir = 2;
				}
				if (y1 == y2) {
					// east/west connection
					baseDir = 0;
				}
			}

			

			resInd1 = baseDir + cnum * MAX_NODE_DIRS;
			resInd2 = baseDir + 1 + cnum * MAX_NODE_DIRS;

			buildingData[ind1].con[resInd1].conType = ct;
			buildingData[ind2].con[resInd2].conType = ct;
			buildingData[ind1].con[resInd1].heightDelta = _heightDelta;
			buildingData[ind2].con[resInd2].heightDelta = -_heightDelta;
			buildingData[ind1].con[resInd1].direction = _direction;
			buildingData[ind2].con[resInd2].direction = -_direction;
			
			buildingData[ind1].con[resInd1].nodeFlags |= _nodeFlags;
			buildingData[ind2].con[resInd2].nodeFlags |= _nodeFlags;
			
			buildingData[ind1].con[resInd1].wallRadInMeters = wallRad;
			buildingData[ind2].con[resInd2].wallRadInMeters = wallRad;
			
			
		}
	}
int GameBlock::getMapNodeIndex (int x, int y, int bufAmount)
                                                         {

		if (
			(x < bufAmount) ||
			(y < bufAmount) ||
			(x >= terDataBufPitchXY - bufAmount) ||
			(y >= terDataBufPitchXY - bufAmount)
		) {
			return -1;
		} else {
			return x + y * terDataBufPitchXY;
		}

	}
int GameBlock::touchesMap (int x, int y, int buildingType, int bufAmount)
                                                                      {
		int i;
		int tot = 0;

		int ind;

		ind = getMapNodeIndex(x, y, bufAmount);
		if (ind > -1) {
			for (i = 0; i < 4; i++) {
				if (mapData[ind].connectionProps[i] == buildingType) {
					tot++;
				}
			}
		}

		return tot;
	}
int GameBlock::touchesWithinRadMap (int x, int y, int buildingType, int rad, int bufAmount)
                                                                                        {
		int i;
		int j;
		
		int tot = 0;
		int testX;
		int testY;
		

		for (i = -rad; i <= rad; i++) {
			for (j = -rad; j <= rad; j++) {
				testX = x + i;
				testY = y + j;

				tot += touchesMap(testX, testY, buildingType, bufAmount);
			}
		}

		return tot;

	}
int GameBlock::touches2Map (int x, int y, int buildingType, int bufAmount)
                                                                       {
		int i;
		int tot = 0;
		int testX;
		int testY;

		for (i = 0; i < 4; i++) {

			testX = x + dirModX[i];
			testY = y + dirModY[i];

			tot += touchesMap(testX, testY, buildingType, bufAmount);

		}

		return tot;

	}
void GameBlock::connectMapNodes (int _x1, int _y1, int _x2, int _y2, int buildingType, int id, int bufAmount)
                                                                                                          {


		// 0: x+
		// 1: x-
		// 2: y+
		// 3: y-

		int x1 = _x1;
		int y1 = _y1;
		int x2 = _x2;
		int y2 = _y2;

		int boff = 0;

		int i;

		int ind1;
		int ind2;

		if (x1 > x2) {
			std::swap(x1, x2);
		}
		if (y1 > y2) {
			std::swap(y1, y2);
		}

		int n[2];


		n[0] = getMapNodeIndex(x1, y1, bufAmount);
		n[1] = getMapNodeIndex(x2, y2, bufAmount);

		if (
			(n[0] < 0) ||
			(n[1] < 0)
		) {
			
		} else {

			if (id >= 0) {
				mapData[n[0]].id = id;
				mapData[n[1]].id = id;
			}

			if (x1 == x2) { // is vertical
				boff = 2;
			} else {
				boff = 0;
			}

			for (i = 0; i < 2; i++) {
				mapData[n[i]].connectionProps[i + boff] = buildingType;
			}

		}


	}
int GameBlock::getAdjustedHeightInHolders (int xInHolders, int yInHolders)
                                                                       {

		float holderSizeInPixels = singleton->holderSizeInPixels;

		tempVec.setFXYZ(xInHolders*holderSizeInPixels, yInHolders*holderSizeInPixels, 0.0f);

		tempVec.addXYZ(
			-fBlockSizeInPixels * offsetInBlocks.getFX(),
			-fBlockSizeInPixels * offsetInBlocks.getFY(),
			0.0f
		);

		tempVec.multXYZ(
			fTerDataVisPitchXY / fBlockSizeInPixels,
			fTerDataVisPitchXY / fBlockSizeInPixels,
			fTerDataVisPitchZ / fBlockSizeInPixels
		);
		tempVec.addXYZ((float)terDataBufAmount);

		tempVec.addXYZ(0.5f);


		
		int ind = getMapNodeIndex(tempVec.getIX(), tempVec.getIY(), 0);
		int res = 0;
		float fres = 0.0f;

		if (ind > -1) {
			fres = ((float)(mapData[ind].terHeight))/fTerDataVisPitchZ; //adjustedHeight
			
			res = fres*singleton->worldSizeInHolders.getFZ();
			
		} else {
			res = 0;
		}
		
		return res;

	}
float GameBlock::fIsNearTerrain (FIVector4 * worldMinVisInPixels)
          {

		int ind;
		int ind2;
		
		int i;
		int j;
		int k;
		
		tempVec.copyFrom(worldMinVisInPixels);

		tempVec.addXYZ(
			-fBlockSizeInPixels * offsetInBlocks.getFX(),
			-fBlockSizeInPixels * offsetInBlocks.getFY(),
			0.0f
		);

		tempVec.multXYZ(
			fTerDataVisPitchXY / fBlockSizeInPixels,
			fTerDataVisPitchXY / fBlockSizeInPixels,
			fTerDataVisPitchZ / fBlockSizeInPixels
		);
		tempVec.addXYZ((float)terDataBufAmount);

		for (i = 0; i <= 1; i++) {
			for (j = 0; j <= 1; j++) {
				for (k = 0; k <= 1; k++) {
					ind = getNodeIndexClamped(
						tempVec.getIX() + i,
						tempVec.getIY() + j,
						tempVec.getIZ() + k
					);
					ind2 = k*4 + j*2 + i;
					if (terData[ind] > 0) {
						trilin[ind2] = 1.0f;
					}
					else {
						trilin[ind2] = 0.0f;
					}
				}
				
			}
		}
		
		// 0 1
		// 2 3
		
		// 4 5
		// 6 7

		float lerpX = tempVec.getFX() - tempVec.getIX();
		float lerpY = tempVec.getFY() - tempVec.getIY();
		float lerpZ = tempVec.getFZ() - tempVec.getIZ();
		float ilerpX = 1.0f - lerpX;
		float ilerpY = 1.0f - lerpY;
		float ilerpZ = 1.0f - lerpZ;
		
		trilin[0] = trilin[0]*ilerpX + trilin[1]*lerpX;
		trilin[2] = trilin[2]*ilerpX + trilin[3]*lerpX;
		trilin[4] = trilin[4]*ilerpX + trilin[5]*lerpX;
		trilin[6] = trilin[6]*ilerpX + trilin[7]*lerpX;
		
		trilin[0] = trilin[0]*ilerpY + trilin[2]*lerpY;
		trilin[4] = trilin[4]*ilerpY + trilin[6]*lerpY;
		
		trilin[0] = trilin[0]*ilerpZ + trilin[4]*lerpZ;

		return trilin[0];
	}
void GameBlock::refreshHoldersInArea (FIVector4 * worldPos)
          {


		int ind;
		int curInd;
		int testInd;
		int i;
		int j;
		int k;
		
		int holderSizeInPixels = singleton->holderSizeInPixels;
	
		float bsih = blockSizeInHolders;
	
		tempVec.copyFrom(worldPos);
		tempVec.intDivXYZ(holderSizeInPixels);
		
		
		doTraceVecND("refreshHoldersInArea", &tempVec);
		
		
		int rad = 2;
		
		for (i = -rad; i <= rad; i++) {
			for (j = -rad; j <= rad; j++) {
				for (k = -rad; k <= rad; k++) {
					
					
					
					gw->getHolderAtCoords(
						tempVec.getIX()+i,
						tempVec.getIY()+j,
						tempVec.getIZ()+k,
						true
					)->refreshChildren(true,true,true);
				}
			}
		}
		


	}
void GameBlock::modifyTerrain (FIVector4 * worldPos, bool doSub)
          {

		int ind;
		int curInd;
		int testInd;
		int i;
		int j;
		int k;
		int n;
		
		int io;
		int jo;
		int ko;
		
		uint newValue = 255;
		if (doSub) {
			newValue = 0;
		}
		
		
		tempVec.copyFrom(worldPos);
		

		tempVec.addXYZ(
			-fBlockSizeInPixels * offsetInBlocks.getFX(),
			-fBlockSizeInPixels * offsetInBlocks.getFY(),
			0.0f
		);

		tempVec.multXYZ(
			fTerDataVisPitchXY / fBlockSizeInPixels,
			fTerDataVisPitchXY / fBlockSizeInPixels,
			fTerDataVisPitchZ / fBlockSizeInPixels
		);
		tempVec.addXYZ((float)terDataBufAmount);

		//tempVec.addXYZ(0.5f);
		
		
		
		i = tempVec.getIX();
		j = tempVec.getIY();
		k = tempVec.getIZ();
		
		float xm = tempVec.getFX() - tempVec.getIX();
		float ym = tempVec.getFY() - tempVec.getIY();
		float zm = tempVec.getFZ() - tempVec.getIZ();
		
		
		if ((xm >= ym) && (xm >= zm)) {
			n = 0;
		}
		if ((ym >= xm) && (ym >= zm)) {
			n = 1;
		}
		if ((zm >= xm) && (zm >= ym)) {
			n = 2;
		}
		
		
		int counterMod = 1;
		
		if (doSub) {
			counterMod = -1;
		}
		
		int counterK = 0;
		while (true) {
			
			
			
			switch(n) {
				case 0:
					i = tempVec.getIX()+counterK*counterMod;
					j = tempVec.getIY();
					k = tempVec.getIZ();
				break;
				case 1:
					i = tempVec.getIX();
					j = tempVec.getIY()+counterK*counterMod;
					k = tempVec.getIZ();
				break;
				case 2:
					i = tempVec.getIX();
					j = tempVec.getIY();
					k = tempVec.getIZ()+counterK*counterMod;
				break;
			}
			
			
			ind = getNodeIndex(i, j, k, 0);
			if (ind > -1) {
				if ( (!doSub) && (terData[ind] == 0) ) {
					// found a place to add
					goto FOUND_ADD_SUB;
				}
				
				if ( (doSub) && (terData[ind] != 0) ) {
					// found a place to sub
					goto FOUND_ADD_SUB;
				}
			}
			else {				
				return;
			}
			
			
			
			counterK++;
		}
		
		
		FOUND_ADD_SUB:
		
		
		
		
		terData[ind] = (newValue << 24) | (newValue << 16) | (newValue << 8) | newValue;

		
		
		
		int rad2 = 3;
		int rad = 2;
		
		
		
		for (i = -rad2; i <= rad2; i++) {
			for (j = -rad2; j <= rad2; j++) {
				for (k = -rad2; k <= rad2; k++) {
					curInd = getNodeIndex(i, j, k, 0);

					if (curInd > -1) {
						buildingData[curInd].nearAir = false;
						buildingData[curInd].nearTerrain = false;
					}
					
				}
			}
		}
		
		for (i = -rad2; i <= rad2; i++) {
			for (j = -rad2; j <= rad2; j++) {
				for (k = -rad2; k <= rad2; k++) {
					curInd = getNodeIndex(i, j, k, 0);

					

					if (curInd > -1) {
						
						for (ko = -rad; ko <= rad; ko++) {
							for (jo = -rad; jo <= rad; jo++) {
								for (io = -rad; io <= rad; io++) {
									testInd = getNodeIndex(i + io, j + jo, k + ko, 0);

									if (testInd > -1) {
										if (terData[testInd] == 0) {
											buildingData[curInd].nearAir = true;
										}
										else {
											buildingData[curInd].nearTerrain = true;
										}
									}
								}
							}
						}
					}
					
				}
			}
		}
		
		forceUpdate = true;

		//copyTerToTexture(true);
		
		//refreshHoldersInArea(worldPos);

	}
int GameBlock::isNearTerrain (FIVector4 * worldPosInPix)
                                                    {

		int ind;
		
		int i;
		int j;
		int k;
		
		tempVec.copyFrom(worldPosInPix);
		tempVec.addXYZ(
			-fBlockSizeInPixels * offsetInBlocks.getFX(),
			-fBlockSizeInPixels * offsetInBlocks.getFY(),
			0.0f
		);

		tempVec.multXYZ(
			fTerDataVisPitchXY / fBlockSizeInPixels,
			fTerDataVisPitchXY / fBlockSizeInPixels,
			fTerDataVisPitchZ / fBlockSizeInPixels
		);
		tempVec.addXYZ((float)terDataBufAmount);

		tempVec.addXYZ(0.5f);

		bool nearT = false;
		bool nearA = false;

		
		i = tempVec.getIX();
		j = tempVec.getIY();
		k = tempVec.getIZ();
		ind = getNodeIndex(i, j, k, 0);
		if (ind > -1) {
			nearT = buildingData[ind].nearTerrain;
			nearA = buildingData[ind].nearAir;
		}

		if (nearT) {
			if (nearA) {
				return E_TER_GROUNDLEVEL;
			}
			else {
				return E_TER_UNDERGROUND;
			}
		}
		
		return E_TER_AIR;

	}
int GameBlock::findNearestNode (FIVector4 * worldPositionInPixelsIn, FIVector4 * posInNodesOut, FIVector4 * posInPixelsOut)
                                                                                                                      {

		int i;
		int j;
		int k;
		int m;
		int curInd;
		int offset;
		int bestInd = -1;
		
		float zBias = floorHeightInMeters*pixelsPerMeter*0.5f;

		bool notFound = true;
		
		
		tempVec.copyFrom(worldPositionInPixelsIn);
		tempVec.addXYZ(
			-fBlockSizeInPixels * offsetInBlocks.getFX(),
			-fBlockSizeInPixels * offsetInBlocks.getFY(),
			zBias
		);

		tempVec.multXYZ(
			fTerDataVisPitchXY / fBlockSizeInPixels,
			fTerDataVisPitchXY / fBlockSizeInPixels,
			fTerDataVisPitchZ / fBlockSizeInPixels
		);
		tempVec.addXYZ((float)terDataBufAmount);

		
		i = tempVec.getIX();
		j = tempVec.getIY();
		k = tempVec.getIZ();
		
		
		for (m = 0; m < 3; m++) {
			switch (m) {
				case 0:
					offset = 0;
				break;
				case 1:
					offset = -1;
				break;
				case 2:
					offset = 1;
				break;
			}
			
			curInd = getNodeIndex(i,j,k+offset,0);
			
			if (curInd > -1) {
				if (touchesPlanarClass(i,j,k+offset,E_CTC_ROAD,0)) {
					bestInd = curInd;
					break;
				}
			}
		}
		
		
		
		
		if (bestInd > -1) {
			posInNodesOut->setIXYZ(
				i + offsetInBlocks.getIX()*terDataVisPitchXY - terDataBufAmount,
				j + offsetInBlocks.getIY()*terDataVisPitchXY - terDataBufAmount,
				k + offset - terDataBufAmount
			);
			nodeIndexToWorldSpaceInPixels(bestInd,posInPixelsOut);
		}
		
		
		return bestInd;

	}
void GameBlock::nodeIndexToWorldSpaceInPixels (int ind, FIVector4 * posInPixelsOut)
                                                                                {


		int k = ind / (terDataBufPitchXY * terDataBufPitchXY);
		int j = (ind - k * terDataBufPitchXY * terDataBufPitchXY) / terDataBufPitchXY;
		int i = ind - (k * terDataBufPitchXY * terDataBufPitchXY + j * terDataBufPitchXY);
				
		posInPixelsOut->setFXYZ(
			blockSizeInPixels * offsetInBlocks.getIX() + ( ((float)(i - terDataBufAmount) + 0.5f) * fBlockSizeInPixels) / fTerDataVisPitchXY,
			blockSizeInPixels * offsetInBlocks.getIY() + ( ((float)(j - terDataBufAmount) + 0.5f) * fBlockSizeInPixels) / fTerDataVisPitchXY,
			0 + ( ((float)(k - terDataBufAmount) + 0.5f) * fBlockSizeInPixels) / fTerDataVisPitchZ
		);

	}
bool GameBlock::hasTerrainBelow (int i, int j, int k, int conDir, bool bothEnds)
                                                                             {
		bool foundA = false;
		bool foundB = false;

		int testInd = getNodeIndex(i, j, k - 1, 0);
		int testInd2 = getNodeIndex(i + dirModX[conDir], j + dirModY[conDir], k + dirModZ[conDir] - 1, 0);


		if (conDir < 4) {
			if (testInd > -1) {
				if (terData[testInd] != 0) {
					foundA = true;
				}
			}

			if (testInd2 > -1) {
				if (terData[testInd2] != 0) {
					foundB = true;
				}
			}

		} else {
			if (testInd > -1) {
				if (
					(terData[testInd] != 0)
				) {
					foundA = true;
					foundB = true;
				}
			}
		}

		if (bothEnds) {
			return foundA && foundB;
		} else {
			return foundA || foundB;
		}
	}
bool GameBlock::hasRoomBelow (int i, int j, int k, int conDir)
                                                           {

		int testInd = getNodeIndex(i, j, k - 1, 0);
		int p;

		if (testInd > -1) {
			if (isRoom[buildingData[testInd].con[conDir].conType]) {
				return true;
			}

			if (conDir >= 4) {
				for (p = 0; p < 4; p++) {
					if (isRoom[buildingData[testInd].con[p].conType]) {
						return true;
					}
				}
			}
		}

		return false;
	}
bool GameBlock::isSupportedBelow (int i, int j, int k, int conDir, bool bothEnds)
                                                                              {

		bool foundA = false;
		bool foundB = false;

		int testInd = getNodeIndex(i, j, k - 1, 0);
		int testInd2 = getNodeIndex(i + dirModX[conDir], j + dirModY[conDir], k + dirModZ[conDir] - 1, 0);

		int p;

		if (conDir < 4) {
			if (testInd > -1) {
				if (terData[testInd] != 0) {
					foundA = true;
				}

				for (p = 0; p < 5; p++) {
					if (isRoom[buildingData[testInd].con[p].conType]) {
						foundA = true;
					}
				}

			}

			if (testInd2 > -1) {
				if (terData[testInd2] != 0) {
					foundB = true;
				}

				for (p = 0; p < 5; p++) {
					if (isRoom[buildingData[testInd2].con[p].conType]) {
						foundB = true;
					}
				}

			}

		} else {
			if (testInd > -1) {
				if (
					(terData[testInd] != 0)
				) {
					foundA = true;
					foundB = true;
				}



				for (p = 0; p < 5; p++) {
					if (isRoom[buildingData[testInd].con[p].conType]) {
						foundA = true;
						foundB = true;
					}
				}


			}
		}

		if (bothEnds) {
			return foundA && foundB;
		} else {
			return foundA || foundB;
		}


	}
bool GameBlock::touchesRoomOnLevel (int i, int j, int k)
                                                     {

		int testInd = getNodeIndex(i, j, k, 0);
		int p;

		if (testInd > -1) {
			for (p = 0; p < 4; p++) {
				if (isRoom[buildingData[testInd].con[p].conType]) {
					return true;
				}
			}
		}

		return false;
	}
bool GameBlock::touchesBaseOnLevel (int i, int j, int k, int layer)
                                                                {

		int testInd;
		int p;
		int m;
		int conType;

		//for (m = 0; m < 2; m++) {}
		
		m = 0;
		
		testInd = getNodeIndex(i, j, k+m, 0);
		if (testInd > -1) {
			for (p = 0; p < 4; p++) {
				conType = buildingData[testInd].con[p+layer*MAX_NODE_DIRS].conType;
				
				if (conType == E_CT_FOUNDATION) {
					return true;
				}
				
				
				// if (m == 0) {
				// 	if (
				// 		isBase[conType]
				// 		&& (!isRoad[conType])
				// 	) {
				// 		return true;
				// 	}
				// }
				// else {
				// 	if (isRoad[conType]) {
				// 		return true;
				// 	}
				// }
				
				
			}
		}

		
		
		
		return false;
	}
bool GameBlock::buildingAbove (int x, int y, int z)
                                                {

		int newInd = getNodeIndex(x, y, z, 0);
		int i;
		int testConType;

		if (newInd > -1) {
			for (i = 0; i < 5; i++) { // skip downwards direction
				testConType = buildingData[newInd].con[i].conType;
				if (isRoom[testConType]) {
					return true;
				}
			}
		}

		return false;
	}
int GameBlock::copyTerToTexture ()
                               {

		int resIndex = singleton->requestTerIndex(blockId);

		int i;
		int j;
		int k;
		int indSource;
		int indDest;

		uint uiSimp;

		uint *finalTex;

		if (singleton->terTextures[resIndex].alreadyBound && (!forceUpdate)) {
			
		} else {
			
			forceUpdate = false;

			doTraceND("copyTerToTexture resIndex: ", i__s(resIndex));

			singleton->terTextures[resIndex].alreadyBound = true;


			// if (terDataTexScale == 1) {
			// 	finalTex = terData;
			// } else {
				
			// }
			
			tempVec2.setFXYZ(93.989f, 67.345f, 54.256f);
			
			
			for (k = 0; k < terDataBufPitchScaledZ; k++) {
				for (j = 0; j < terDataBufPitchScaledXY; j++) {
					for (i = 0; i < terDataBufPitchScaledXY; i++) {
						indDest = k * terDataBufPitchScaledXY * terDataBufPitchScaledXY + j * terDataBufPitchScaledXY + i;
						indSource =
							(k / terDataTexScale) * terDataBufPitchXY * terDataBufPitchXY +
							(j / terDataTexScale) * terDataBufPitchXY +
							(i / terDataTexScale);
							
						if (terData[indSource] == 0) {
							uiSimp = 0;
						}
						else {
							if (buildingData[indSource].nearAir) {
								
								// TODO: rand num should be hashed based on location
								
								
								
								
								
								if (
									(i >= terDataBufPitchScaledXY-terDataBufAmount*4) ||
									(i <= terDataBufAmount*4) ||
									(j >= terDataBufPitchScaledXY-terDataBufAmount*4) ||
									(j <= terDataBufAmount*4)
								) {
									uiSimp = 255; // make sure block borders match up
								}
								else {
									
									tempVec.setIXYZ(
										i + offsetInBlocks.getIX()*terDataVisPitchXY - terDataBufAmount,
										j + offsetInBlocks.getIY()*terDataVisPitchXY - terDataBufAmount,
										k + offsetInBlocks.getIZ()*terDataVisPitchZ - terDataBufAmount
									);
									
									uiSimp = iGetRandSeeded(&tempVec,&tempVec2,200,255);
								}
								
							}
							else {
								uiSimp = 255;
							}
						}

						singleton->terDataScaled[indDest] = (uiSimp << 24) | (uiSimp << 16) | (uiSimp << 8) | uiSimp;//terData[indSource];
					}
				}
			}

			finalTex = singleton->terDataScaled;
			
			
			

			glBindTexture(GL_TEXTURE_3D, singleton->terTextures[resIndex].texId);

			glTexSubImage3D(
				GL_TEXTURE_3D,
				0,

				0,
				0,
				0,

				terDataBufPitchScaledXY,
				terDataBufPitchScaledXY,
				terDataBufPitchScaledZ,

				GL_RGBA,
				GL_UNSIGNED_BYTE,

				finalTex

			);
			glBindTexture(GL_TEXTURE_3D, 0);
		}

		return resIndex;

	}
void GameBlock::makeMazeUG ()
                                  {

			//cout << "q\n";

			int i;
			int rbInd = 0;
			int curInd = 0;
			int startDir = 0;
			int count = 0;

			int testX = 0;
			int testY = 0;
			int testZ = 0;

			int curX = 0;
			int curY = 0;
			int curZ = 0;
			
			int ind1;
			int ind2;

			int testInd = 0;
			int bestInd = 0;
			int bestDir = 0;
			int curDir = 0;
			int blockOffset = offsetInBlocks.getIX() + offsetInBlocks.getIY();

			int ct;

			bool isOddX, isOddY, isOddZ;
			bool doProc;

			int divSize = 4;
			int tunnelCount = 0;

			rbInd = 0;
			


			//ind1 = getMapNodeIndex(terDataBufSize/2,terDataBufSize/2, 0);
			
			singleton->rbStack[0] = getNodeIndex(
																terDataBufPitchXY/2,
																terDataBufPitchXY/2,
																terDataBufPitchZ/2,
																0
															);
			
			




			while (rbInd > -1) {



				curInd = singleton->rbStack[rbInd];
				buildingData[curInd].visited = 1;
				buildingData[curInd].mazeIndex = rbInd;

				curZ = curInd / (terDataBufPitchXY * terDataBufPitchXY);
				curY = (curInd - curZ * terDataBufPitchXY * terDataBufPitchXY) / terDataBufPitchXY;
				curX = curInd - (curZ * terDataBufPitchXY * terDataBufPitchXY + curY * terDataBufPitchXY);

				startDir = rbInd * 37 + blockOffset;
				count = 0;

				isOddX = ((curX + terDataBufAmount) % divSize) != 0;
				isOddY = ((curY + terDataBufAmount) % divSize) != 0;
				isOddZ = ((curZ + terDataBufAmount) % divSize) != 0;

				do {

					curDir = (startDir + count) % 6;

					testX = curX + dirModX[curDir];
					testY = curY + dirModY[curDir];
					testZ = curZ + dirModZ[curDir];

					testInd = getNodeIndex(testX, testY, testZ, 0);



					if (testInd >= 0) {
						
						//cout << "b\n";

						if ( true ) { // terData[testInd] != 0
							if ( buildingData[testInd].visited == 0 ) {

								

								doProc = false;

								if (isOddX) {
									if (curDir <= 1) {
										doProc = true;
									}
								}
								else {
									if (isOddY) {
										if ((curDir == 2) || (curDir == 3)) {
											doProc = true;
										}
									}
									else {
										if (isOddZ) {
											if (curDir >= 4) {
												doProc = true;
											}
										}
										else {
											doProc = true;
										}
									}
								}
								if (doProc) {
									//not visited, proceed

									

									bestDir = curDir;
									bestInd = testInd;
									goto DONE_SEARCHING;
								}



							}
						}


					}



					count++;


				} while (count < 6);

	DONE_SEARCHING:

				if (count >= 6) { // dead end, back up
					rbInd--;
				} else {

					//ct = E_CT_CONNECTED;//iGenRand(E_CT_ROAD,E_CT_ROOM_TUDOR);
					//connectNodes( curX, curY, curZ, testX, testY, testZ, E_CT_CONNECTED);
					
					//cout << "a\n";
					
					ind1 = getNodeIndex(curX,curY,curZ, 0);
					ind2 = getNodeIndex(testX,testY,testZ, 0);
					
					if (ind1 > -1) {
						terData[ind1] = 0;
					}
					if (ind2 > -1) {
						terData[ind2] = 0;
					}

					rbInd++;

					


					singleton->rbStack[rbInd] = bestInd;
					
					
					tunnelCount++;
					
					if (tunnelCount >= terDataBufSize/16) {
						return;
					}
					
				}



			}

		}
#undef LZZ_INLINE
 
// f00380_gameworld.h
//

#include "f00380_gameworld.e"
#define LZZ_INLINE inline
GameWorld::GameWorld ()
        {

		// Notes
		// -----
		// Depth: 16 bits
		// Material: 16 bits
		// AO val: 8 bits, normal: 24 bits

	}
void GameWorld::init (Singleton * _singleton)
        {

		//pushTrace("GameWorld init()");

		

		singleton = _singleton;
		
		curLoadRadius = singleton->minWInPages;

		int i;
		int j;
		
		//finalInd = -1;

		lightCount = 1;

		noiseGenerated = false;

		finalPath = NULL;

		blockSizeInHolders = singleton->blockSizeInHolders;

		dirFlagsO[0] = 1;
		dirFlagsO[1] = 2;
		dirFlagsO[2] = 4;
		dirFlagsO[3] = 8;

		dirFlagsOpO[0] = 2;
		dirFlagsOpO[1] = 1;
		dirFlagsOpO[2] = 8;
		dirFlagsOpO[3] = 4;

		dirFlags[0] = ~1;
		dirFlags[1] = ~2;
		dirFlags[2] = ~4;
		dirFlags[3] = ~8;

		dirFlagsOp[0] = ~2;
		dirFlagsOp[1] = ~1;
		dirFlagsOp[2] = ~8;
		dirFlagsOp[3] = ~4;

		dirModX[0] = 1;
		dirModX[1] = -1;
		dirModX[2] = 0;
		dirModX[3] = 0;
		dirModX[4] = 0;
		dirModX[5] = 0;

		dirModY[0] = 0;
		dirModY[1] = 0;
		dirModY[2] = 1;
		dirModY[3] = -1;
		dirModY[4] = 0;
		dirModY[5] = 0;

		dirModZ[0] = 0;
		dirModZ[1] = 0;
		dirModZ[2] = 0;
		dirModZ[3] = 0;
		dirModZ[4] = 1;
		dirModZ[5] = -1;

		opDir[0] = 1;
		opDir[1] = 0;
		opDir[2] = 3;
		opDir[3] = 2;

		dirFlagClear = ~15;
		visFlag = 16;
		visFlagO = ~16;

		foundPath = false;

		activeFBO = 0;
		mapLockOn = false;

		numProvinces = 32;
		provinceGrid = new int[numProvinces * numProvinces];
		provinceX = new int[numProvinces];
		provinceY = new int[numProvinces];

		mapSwapFlag = 0;
		mapStep = 0.0f;

		pageCount = 0;
		procResultAccum = false;
		lastProcResult = true;
		maxThreads = 7;
		availThreads = maxThreads;

		for (i = 0; i < maxThreads; i++)
		{
			ocThreads.push_back(-1);
		}

		hmChannel = 0;
		idChannel = 1;
		densityChannel = 2;
		blockChannel = 3;

		stChannel = 0;
		btChannel = 1;
		pathChannel = 2;
		houseChannel = 3;




		MIN_MIP = 0;
		MAX_MIP = 1;
		AVG_MIP = 2;


		doDrawFBO = false;

		// for (j = 0; j < E_RENDER_LENGTH; j++)
		// {
		// 	for (i = 0; i < E_STATE_LENGTH; i++)
		// 	{
		// 		diagrams[j][i] = E_STATE_WAIT;
		// 	}
		// }

		cutPos = &(singleton->dynObjects[E_OBJ_CUTAWAY]->pos);
		fogPos = &(singleton->dynObjects[E_OBJ_FOG]->pos);
		cameraPos = &(singleton->dynObjects[E_OBJ_CAMERA]->pos);

		renderMethod = (int)E_RENDER_VOL;

		worldSizeInPages.copyFrom( &(singleton->worldSizeInPages) );
		worldSizeInHolders.copyFrom( &(singleton->worldSizeInHolders) );
		worldSizeInBlocks.copyFrom( &(singleton->worldSizeInBlocks) );

		visPageSizeInPixels = singleton->visPageSizeInPixels;

		// diagrams[E_RENDER_VOL][E_STATE_INIT_END] = E_STATE_GENERATEVOLUME_LAUNCH;
		// diagrams[E_RENDER_VOL][E_STATE_GENERATEVOLUME_END] = E_STATE_LENGTH;
		// curDiagram = diagrams[renderMethod];

		holderSizeInPages = singleton->holderSizeInPages;
		visPageSizeInUnits = singleton->visPageSizeInUnits;

		iBlockSize = worldSizeInBlocks.getIX() * worldSizeInBlocks.getIY();



		blockData = new GameBlock*[iBlockSize];
		for (i = 0; i < iBlockSize; i++)
		{
			blockData[i] = NULL;
		}

		
		
		


		//popTrace();
	}
GameBlock * GameWorld::getBlockAtCoords (int xInBlocks, int yInBlocks, bool createOnNull)
        {





		int newX = wrapCoord(xInBlocks, worldSizeInBlocks.getIX());
		int newY = wrapCoord(yInBlocks, worldSizeInBlocks.getIY());

		//cout << "xy " << newX << " " << newY << "\n";

		int ind =
			newY * worldSizeInBlocks.getIX() +
			newX;

		if (blockData[ind] == NULL) {
			if (createOnNull) {
				blockData[ind] = new GameBlock();
				blockData[ind]->init(singleton, ind, xInBlocks, yInBlocks, newX, newY);
			}
		}

		return blockData[ind];

	}
GamePageHolder * GameWorld::getHolderAtCoords (int x, int y, int z, bool createOnNull)
        {

		GamePageHolder **holderData;

		int newX = wrapCoord(x, worldSizeInHolders.getIX());
		int newY = wrapCoord(y, worldSizeInHolders.getIY());
		int newZ = z;

		int holderX = newX - intDiv(newX, blockSizeInHolders) * blockSizeInHolders;
		int holderY = newY - intDiv(newY, blockSizeInHolders) * blockSizeInHolders;
		int holderZ = newZ - intDiv(newZ, blockSizeInHolders) * blockSizeInHolders;

		int holderId = holderZ * blockSizeInHolders * blockSizeInHolders + holderY * blockSizeInHolders + holderX;


		GameBlock *curBlock = getBlockAtCoords(
														intDiv(x, blockSizeInHolders),
														intDiv(y, blockSizeInHolders),
														createOnNull
													);

		if (curBlock == NULL)
		{
			return NULL;
		}
		else
		{
			holderData = curBlock->holderData;


			if (holderData[holderId] == NULL)
			{
				if (createOnNull)
				{
					holderData[holderId] = new GamePageHolder();
					holderData[holderId]->init(singleton, curBlock->blockId, holderId, x, y, z); //, x, y, z
				}
			}

			return holderData[holderId];


		}



	}
uint GameWorld::getTerDataAtCoords (int x, int y, int z)
        {

		int tdvpXY = singleton->terDataVisPitchXY;
		int tdvpZ = singleton->terDataVisPitchZ;

		int newX = wrapCoord(x, singleton->worldSizeInTerData.getIX());
		int newY = wrapCoord(y, singleton->worldSizeInTerData.getIY());
		int newZ = z;


		int holderX = newX - intDiv(newX, tdvpXY) * tdvpXY;
		int holderY = newY - intDiv(newY, tdvpXY) * tdvpXY;
		int holderZ = newZ - intDiv(newZ, tdvpZ) * tdvpZ;

		int holderId = holderZ * tdvpXY * tdvpXY + holderY * tdvpXY + holderX;


		GameBlock *curBlock = getBlockAtCoords(
														intDiv(x, tdvpXY),
														intDiv(y, tdvpXY),
														true
													);

		return curBlock->terData[holderId];


	}
GamePageHolder * GameWorld::getHolderAtId (intPair id)
        {

		if (blockData[id.v0] == NULL)
		{
			return NULL;
		}
		else
		{
			return blockData[id.v0]->holderData[id.v1];
		}
	}
GameBlock * GameWorld::getBlockAtId (int id)
        {


		if ((id < 0) || (id >= iBlockSize))
		{
			doTraceND("BLOCK INDEX OUT OF RANGE");
			return NULL;
		}
		else
		{
			if (blockData[id] == NULL)
			{
				doTraceND("BLOCK DATA IS NULL");
				return NULL;
			}
			else
			{
				return blockData[id];
			}
		}



	}
GamePage * GameWorld::getPageAtIndex (int ind)
        {
		//pushTrace("getPageAtIndex()");

		int newInd = ind;
		int x, y, z;
		GamePage *gp;

		z = newInd / (worldSizeInPages.getIX() * worldSizeInPages.getIY());
		newInd -= z * (worldSizeInPages.getIX() * worldSizeInPages.getIY());

		y = newInd / (worldSizeInPages.getIX());
		newInd -= y * (worldSizeInPages.getIX());

		x = newInd;

		gp = getPageAtCoords(x, y, z, false);

		//popTrace();

		return gp;

	}
GamePage * GameWorld::getPageAtCoords (int x, int y, int z, bool createOnNull)
        {

		//pushTrace("getPageAtCoords()");
		int hx, hy, hz;
		int px, py, pz;
		int gpInd;
		//int xmod = 0;
		//int ymod = 0;
		int newX = wrapCoord(x, worldSizeInPages.getIX());
		int newY = wrapCoord(y, worldSizeInPages.getIY());
		int newZ = z;
		int ind =
			newZ * worldSizeInPages.getIX() * worldSizeInPages.getIY() +
			newY * worldSizeInPages.getIX() +
			newX;

		GamePage *gp = NULL;

		px = newX % holderSizeInPages;
		py = newY % holderSizeInPages;
		pz = newZ % holderSizeInPages;




		GamePageHolder *gph = getHolderAtCoords(
														intDiv(x, holderSizeInPages),
														intDiv(y, holderSizeInPages),
														intDiv(z, holderSizeInPages),
														createOnNull
													);


		if ( gph )
		{



			gpInd = pz * holderSizeInPages * holderSizeInPages + py * holderSizeInPages + px;
			//gph->getPageIndex(px,py,pz);

			if (gpInd == -1)
			{
				// prob
				cout << "Invalid holder index\n";
			}
			else
			{
				gp = gph->pageData[gpInd];

				if (gp == NULL) {
					if (createOnNull) {

						gph->pageData[gpInd] = new GamePage();
						gp = gph->pageData[gpInd];
						gp->init(
							singleton,
							gph,
							ind,
							x, y, z,//newX, newY, newZ,
							px, py, pz
						);
					}
				}
			}

		}

		//popTrace();
		return gp;

	}
bool GameWorld::checkBounds (int k, int km)
                                        {
		
		return ((k >= 0)&&(k<km));

	}
void GameWorld::update ()
        {
		
		bool procResult = false;
		

		//pushTrace("update()");

		singleton->updateLock = true;

		int i;

		float x;
		float y;
		float z;
		
		

		newZoom = max(1.0f, singleton->cameraZoom);

		bool doFinalDraw = false;
		
		singleton->testHuman->basePosition.copyFrom(&(singleton->dynObjects[E_OBJ_HUMAN]->pos));
		transformEnt(singleton->testHuman);

		mapTrans = 1.0f-smoothstep(1.0f/128.0f,1.0f/32.0f,singleton->cameraZoom);
		//1.0f - (singleton->cameraZoom * ((float)DEF_SCALE_FACTOR)) / 0.01f;
		if (mapTrans > 0.91)
		{
			mapTrans = 1.0;
		}
		if (mapTrans < 0.1)
		{
			mapTrans = 0.0;
		}
		
    bool changesMade = false;
    bool bufferInvalid = false;

		if (mapLockOn)
		{
			goto DO_RETURN_UPDATE;
		}

		if (singleton->mapInvalid)
		{


			goto DO_RETURN_UPDATE;
		}

		if (noiseGenerated)
		{

		}
		else
		{
			noiseGenerated = true;
			singleton->bindShader("NoiseShader");
			singleton->bindFBO("noiseFBO");
			singleton->drawFSQuad(1.0f);
			singleton->unbindFBO();
			singleton->unbindShader();
		}

		changesMade = singleton->changesMade;
		bufferInvalid = singleton->bufferInvalid;
		

		if (mapTrans < 1.0f)
		{

			if ( singleton->isZooming ) //
			{

			}
			else
			{
				procResult = procPages();
				
				procResultAccum = procResultAccum || procResult;
				
				if (singleton->skipFrames > 1) {
					if ( (singleton->frameCount % singleton->skipFrames) != 0) {
						doFinalDraw = true;
						goto FINAL_DRAW;
					}
				}
				
				
				procResultAccum = false;
				

				if ( (lastProcResult != procResultAccum)  ) // && (procResultAccum == false)
				{
					singleton->wsBufferInvalid = true;
				}
			}

			if (
				procResultAccum ||
				changesMade ||
				(singleton->charState == E_CHAR_STATE_RENDERED) ||
				(singleton->tiltChanged)
			)
			{
				actionOnHolders(E_HOLDER_ACTION_RENDER);
				combineHolders();

			}

		}

		if (
			procResultAccum ||
			changesMade ||
			bufferInvalid ||
			singleton->abDown || 
			//(singleton->charState == E_CHAR_STATE_SKEL) ||
			(singleton->charState == E_CHAR_STATE_RENDERED) ||
			(singleton->tiltChanged)
			
		)	{

			doFinalDraw = true;

			renderGeom();
			combineBuffers();
			renderWorldSpaceGPU();


		}




		////////////


		if (doFinalDraw || singleton->waterOn || (mapTrans > 0.0))
		{
			glClearColor(0.6f, 0.6f, 0.7f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			if ( mapTrans < 1.0 )
			{

				postProcess();

			}

			if ( mapTrans > 0.0 )
			{
				if (doFinalDraw) {
					singleton->createVTListTilt();
				}				
				drawMap();
			}

			

			glutSwapBuffers();
			glFlush();
		}



		////////////


		if (singleton->forceGetPD)
		{
			singleton->forceGetPD = false;
			getWorldSpaceBuffer();
		}

FINAL_DRAW:


DO_RETURN_UPDATE:

		if (
			(singleton->skipFrames <= 1) ||
			((singleton->frameCount % singleton->skipFrames) == 0)
		) {
			lastProcResult = procResultAccum;
		}
		
		if (procResult) {
			
		}
		else {
			curLoadRadius++;
			curLoadRadius = min(curLoadRadius,singleton->maxWInPages);
		}
		
		
		singleton->updateLock = false;
		//popTrace();


	}
bool GameWorld::procPages ()
        {



		int counter;
		int i, j, k;
		int res;


		int ii;
		int jj;
		int kk;

		int incVal;

		bool cmade = false;

		
		// if (singleton->autoScroll) {
		// 	camTerPos.copyFrom( &(singleton->cameraPosAdjusted) );
		// 	camPagePos.copyFrom( &(singleton->cameraPosAdjusted) );
		// 	camBlockPos.copyFrom( &(singleton->cameraPosAdjusted) );
		// }
		// else {
			camTerPos.copyFrom( cameraPos );
			camPagePos.copyFrom( cameraPos );
			camBlockPos.copyFrom( cameraPos );
		//}
		
		
		camTerPos.intDivXYZ(
			singleton->terDataVisPitchXY,
			singleton->terDataVisPitchXY,
			singleton->terDataVisPitchZ	
		);
		
		//camPagePos.setFZ(heightAtPoint);
		camPagePos.intDivXYZ(visPageSizeInPixels);
		camPagePos.addXYZ(1.0f,1.0f,1.0f);

		camHolderPos.copyFrom(&camPagePos);
		camHolderPos.intDivXYZ(singleton->holderSizeInPages);

		camHolderPos.addXYZ(1.0f,1.0f,1.0f);

		cutHolderPos.copyFrom(cutPos);
		cutHolderPos.intDivXYZ(singleton->holderSizeInPixels);
		
		

		
		camBlockPos.intDivXYZ(singleton->blockSizeInPixels);


		GamePageHolder* curHolder;
		GameBlock *curBlock;

		int m;
		//E_STATES nState;

		int loadRad = curLoadRadius; //singleton->maxWInPages;
		int loadRad2 = singleton->maxHInPages; //curLoadRadius; //
		
		if (singleton->changingGenVal) {
			loadRad2 = 1;
		}
		
		int changeCount = 0;

		int maxChangesInHolders = singleton->maxChangesInHolders;
		
		
		if (
			(singleton->hitGUI) ||
			(singleton->rbDown && singleton->bShift)
		) {
			
		}
		else {
			if (
				(singleton->abDown || singleton->isZooming)
			) {
				maxChangesInHolders = 1;
			}
		}


		// // check for threads to free
		// if (availThreads < maxThreads)
		// {
		// 	for (i = 0; i < ocThreads.size(); i++)
		// 	{
		// 		if ( ocThreads[i] == -1)
		// 		{
		// 			// already freed
		// 		}
		// 		else
		// 		{
		// 			if ( getPageAtIndex(ocThreads[i]) == NULL )
		// 			{
		// 				// page was destroyed, free thread

		// 				ocThreads[i] = -1;
		// 				availThreads++;
		// 			}
		// 			else
		// 			{
		// 				if (getPageAtIndex(ocThreads[i])->threadRunning)
		// 				{

		// 				}
		// 				else
		// 				{
		// 					ocThreads[i] = -1;
		// 					availThreads++;
		// 				}
		// 			}
		// 		}
		// 	}
		// }


		// if (availThreads == 0)
		// {
		// 	goto DO_RETURN_PP;
		// }

		

		

		// first fetch all the blocks to make sure they get created
		// don't remove this, necessary for overlapping geom
		
		int blockRad = 1;
		for (j = -blockRad; j <= blockRad; j++)
		{
			for (i = -blockRad; i <= blockRad; i++)
			{
				ii = i + camBlockPos.getIX();
				jj = j + camBlockPos.getIY();

				curBlock = getBlockAtCoords(ii, jj, true);

			}
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		//////////////
		
		bool foundIt = false;
		int terVal = 0;
		
		int MAX_CAM_CAST = singleton->terDataVisPitchXY;
		for (i = 0; i < MAX_CAM_CAST; i++) {
			
			ii = camTerPos.getIX()-i;
			jj = camTerPos.getIY()-i;
			kk = camTerPos.getIZ()-i;
			
			if (
				(kk < 0)
			) {
				break;
			}
			
			if (kk >= singleton->terDataVisPitchZ) {
				
			}
			else {
				terVal = getTerDataAtCoords(ii,jj,kk);
			}
			
			if (terVal > 0) {
				foundIt = true;
				break;
			}
			
			
		}
		
		
		float ftPitchXY = singleton->terDataVisPitchXY;
		float ftPitchZ = singleton->terDataVisPitchZ;
		
		if (foundIt) {
			
			camHolderPos.setIXYZ(ii,jj,kk);
			camHolderPos.multXYZ(
				singleton->blockSizeInPixels/ftPitchXY,
				singleton->blockSizeInPixels/ftPitchXY,
				singleton->blockSizeInPixels/ftPitchZ
			);
			
			camHolderPos.multXYZ(1.0f/((float)(singleton->holderSizeInPixels)));
			
		}
		
		
		minLRInPixels.copyFrom(&camHolderPos);
		maxLRInPixels.copyFrom(&camHolderPos);
		minLRInPixels.addXYZ(-singleton->minWInPages, -singleton->minWInPages, -loadRad2);
		maxLRInPixels.addXYZ(singleton->minWInPages, singleton->minWInPages, loadRad2);
		
		minLRInPixels.addXYZ(-0.5f);
		maxLRInPixels.addXYZ(0.5f);
		
		minLRInPixels.multXYZ(singleton->holderSizeInPixels);
		maxLRInPixels.multXYZ(singleton->holderSizeInPixels);
		
		
		//////////////
		
		
		
		
		int tempVal = 0;

		int mink = camHolderPos.getIZ() - loadRad2;
		int maxk = camHolderPos.getIZ() + loadRad2;
		int minj = camHolderPos.getIY() - loadRad;
		int maxj = camHolderPos.getIY() + loadRad;
		int mini = camHolderPos.getIX() - loadRad;
		int maxi = camHolderPos.getIX() + loadRad;
		int curHeight = 0;

		minLRInHolders.setIXYZ(mini + 1, minj + 1, mink + 1);
		maxLRInHolders.setIXYZ(maxi - 1, maxj - 1, maxk - 1);

		int curMC;
		int n;
		int nMax;
		
		if (maxChangesInHolders == 1) {
			nMax = 1;
			curMC = maxChangesInHolders;
		}
		else {
			nMax = 2;
			curMC = maxChangesInHolders/2;
		}
		
		

		for (n = 0; n < nMax; n++) {
			
			if (n == 1) {
				curMC = maxChangesInHolders;
			}
			
			for (jj = maxj; jj >= minj; jj--) {
				
				if (curLoadRadius == singleton->minWInPages) {
					incVal = 1;
				}
				else {
					if ( (jj == minj) || (jj == maxj) ) {
						incVal = 1;
					}
					else {
						incVal = maxi - mini;
					}
				}
				
				for (ii = maxi; ii >= mini; ii -= incVal) {
					
					
					for (kk = maxk; kk >= mink; kk--) {
						if ( checkBounds(kk, worldSizeInHolders.getIZ()) ) {
							
							if (n == 0) {
								curHolder = getHolderAtCoords(ii, jj, kk, true);
							}
							else {
								curHolder = getHolderAtCoords(jj, ii, kk, true);
							}
							
							
							
							
							if (curHolder->childrenDirty) {
								
								tempVal = curHolder->passiveRefresh();
								changeCount += tempVal;
								
								if (tempVal > 0) {
									cmade = true;
								}
								
							}
							
							
							
							if (changeCount >= curMC)
							{
								
								if ((n == 0) && (maxChangesInHolders > 1)) {
									goto FINISH_CUR_LOOP_PP;
								}
								else {
									goto DO_RETURN_PP;
								}
								
							}
						}
					}
					
				}
			}
			
FINISH_CUR_LOOP_PP:
			;
			
		}
		
		
		


DO_RETURN_PP:

		//popTrace();
		return cmade;
	}
bool GameWorld::addHolderToRefresh (GamePageHolder * toAdd)
        {
		int i;

		bool wasFound = false;

		if (toAdd == NULL)
		{
			return false;
		}

		for (i = 0; i < holdersToRefresh.size(); i++)
		{
			if (holdersToRefresh[i] == toAdd)
			{
				wasFound = true;
			}
		}

		if (wasFound)
		{
			return false;
		}
		else
		{
			holdersToRefresh.push_back(toAdd);
			return true;
		}
	}
int GameWorld::getHoldersInGeom (GameGeom * gg)
        {

		int i;
		int j;
		int k;

		geomMin.copyFrom(gg->getVisMinInPixelsT());
		geomMin.intDivXYZ(singleton->holderSizeInPixels);

		geomMax.copyFrom(gg->getVisMaxInPixelsT());
		geomMax.intDivXYZ(singleton->holderSizeInPixels);

		GamePageHolder *gphMin = getHolderAtCoords(geomMin.getIX(), geomMin.getIY(), geomMin.getIZ(), true);
		GamePageHolder *gphMax = getHolderAtCoords(geomMax.getIX(), geomMax.getIY(), geomMax.getIZ(), true);

		//doTraceVecND("min: ", &(gphMin->offsetInHolders));
		//doTraceVecND("max: ", &(gphMax->offsetInHolders));

		int totCount = 0;

		bool wasAdded;


		for (i = gphMin->offsetInHolders.getIX(); i <= gphMax->offsetInHolders.getIX(); i++)
		{
			for (j = gphMin->offsetInHolders.getIY(); j <= gphMax->offsetInHolders.getIY(); j++)
			{
				for (k = gphMin->offsetInHolders.getIZ(); k <= gphMax->offsetInHolders.getIZ(); k++)
				{
					wasAdded = addHolderToRefresh(getHolderAtCoords(i, j, k, false));
					if (wasAdded)
					{
						totCount++;
					}

				}
			}
		}

		return totCount;

	}
void GameWorld::refreshHoldersInList (bool doImmediate, bool clearEverything)
        {
		int i;

		for (i = 0; i < holdersToRefresh.size(); i++)
		{
			holdersToRefresh[i]->refreshChildren(doImmediate, clearEverything);
		}
	}
void GameWorld::actionOnHolders (int action, bool instantRefresh, bool clearEverything)
        {

		//pushTrace("renderHolders()");

		int i, j, k, m;
		int res;
		int drawnPageCount = 0;
		int skippedPages = 0;
		intPair cid;
		int ppSize = singleton->gpuPool->orderedIds.size();
		GamePageHolder* gp;
		
		bool entPass = false;
		
		float zOffR = 0.0f;
		float zOffG = 0.0f;
		
		GameEnt* activeEnt = singleton->testHuman;
		GamePageHolder* gphEnt = activeEnt->gph;

		if (singleton->charState == E_CHAR_STATE_RENDERED) {
			
			
			
			
			if (  (gphEnt->childrenDirty)&&(singleton->entOn)  ) {
				
				// TOOD: this must be called before other pages or potential crash from lack of memory to alloc
				//transformEnt(singleton->testHuman);
				
				
				gphEnt->refreshGeom();
				gphEnt->refreshChildren(true);
				
				
			}
		}
		

		singleton->bindShader("BlitShader");

		for (k = 0; k < MAX_LAYERS*2; k++)
		{
			
			
			j = k % MAX_LAYERS;
			entPass = k >= MAX_LAYERS;

			if (entPass) {
				if (j == 0)
				{
					singleton->bindFBO("pages3FBO");
				}
				else
				{
					singleton->bindFBO("water3FBO");
				}
			}
			else {
				if (j == 0)
				{
					singleton->bindFBO("pages2FBO");
				}
				else
				{
					singleton->bindFBO("water2FBO");
				}
			}

			


			singleton->setShaderFloat("zOffset",0.0f);

			for (i = 0; i < ppSize; i++)
			{
				cid = singleton->gpuPool->orderedIds[i];

				if ( pairIsNeg(cid) )
				{

				}
				else
				{
					gp = getHolderAtId(cid);

					if (gp == NULL)
					{

					}
					else
					{

						switch (action)
						{
						case E_HOLDER_ACTION_RENDER:
							if (
								(cutHolderPos.getFX() - 1.0f < gp->offsetInHolders.getFX()) &&
								(cutHolderPos.getFY() - 1.0f < gp->offsetInHolders.getFY()) &&
								(cutHolderPos.getFZ() - 1.0f < gp->offsetInHolders.getFZ())


							)
							{

							}
							else
							{
								
								if ( ((j == 0) && gp->hasSolids) || ((j == 1) && gp->hasTrans) )
								{

									//cout << "drawHolder\n";

									//if ( gp->offsetInHolders.inBoundsXYZ(&minLRInHolders,&maxLRInHolders) ) {
									drawHolder(gp, j, 0.0f, 0.0f, 0.0f);
									//}

								}
								
								
								
							}
							break;
						case E_HOLDER_ACTION_RESET:
						
							gp->refreshChildren(instantRefresh, clearEverything);
						
							
							break;
						}


					}
				}
			}
			
			
			if (singleton->charState == E_CHAR_STATE_RENDERED) {
				
				
				if (entPass) {
					switch (action)
					{
					case E_HOLDER_ACTION_RENDER:
						
						singleton->setShaderFloat("zOffset",activeEnt->basePosition[2]);
						
						
						if ( ((j == 0) && gphEnt->hasSolids) || ((j == 1) && gphEnt->hasTrans) )
						{
							
							if (singleton->entOn) {
								drawHolder(
									gphEnt,
									j,
									activeEnt->basePosition[0],
									activeEnt->basePosition[1],
									activeEnt->basePosition[2]
								);
							}
							

						}
						
						
						break;
					case E_HOLDER_ACTION_RESET:
						if (singleton->entOn) {
							gphEnt->refreshChildren(true);							
						}
						break;
					}
					
					
				}
				
			}



			singleton->unbindFBO();
		}

		singleton->unbindShader();


		//doTrace( "POSSIBLE ERROR: " , i__s(glGetError()) , "\n" );

		//popTrace();
	}
void GameWorld::drawHolder (GamePageHolder * gp, int curLayer, float xoff, float yoff, float zoff)
        {
		//pushTrace("drawHolder()");


		float dx = gp->offsetInHolders.getFX();
		float dy = gp->offsetInHolders.getFY();
		float dz = gp->offsetInHolders.getFZ();

		float pitchSrc = (float)((singleton->holderSizeInPixels * 2.0f));
		float pitchSrc2 = pitchSrc / 2.0f;

		float itilt = 1.0-singleton->tiltAmount;
		float tilt = singleton->tiltAmount;

		float dxmod = dx * pitchSrc2 + xoff - cameraPos->getFX();
		float dymod = dy * pitchSrc2 + yoff - cameraPos->getFY();
		float dzmod = dz * pitchSrc2 + zoff - cameraPos->getFZ();


		// float tilt = 1.0-singleton->tiltAmount;
		
		// float fx1 = (dxmod - dymod);
		// //float fy1 = (-(dxmod / 2.0f) + -(dymod / 2.0f) + dzmod) - pitchSrc2;
		// float fy1 = (-tilt*dxmod + -tilt*dymod + (1.0-tilt)*2.0f*dzmod);


		tempVec2.setFXYZ(dxmod,dymod,dzmod);
		singleton->worldToScreenBase(&tempVec1,&tempVec2);
		float fx1 = tempVec1.getFX();
		float fy1 = tempVec1.getFY();
		
		pitchSrc /= singleton->fHolderMod;
		pitchSrc2 /= singleton->fHolderMod;

		fy1 -= (0.5-tilt)*pitchSrc;

		fx1 -= pitchSrc2;
		fy1 -= pitchSrc2;
		float fx2 = fx1 + pitchSrc;
		float fy2 = fy1 + pitchSrc;




		// TODO: should be baseW/H?

		float sx = singleton->bufferDim.getFX();
		float sy = singleton->bufferDim.getFY();

		float myZoom = std::min(1.0f, singleton->cameraZoom);


		fx1 = fx1 * (myZoom) / sx;
		fy1 = fy1 * (myZoom) / sy;
		fx2 = fx2 * (myZoom) / sx;
		fy2 = fy2 * (myZoom) / sy;


		if (gp->gpuRes != NULL)
		{
			singleton->sampleFBODirect(gp->gpuRes->getFBOS(curLayer));


			glColor4f(1, 1, 1, 1);
			glBegin(GL_QUADS);
			glNormal3f(0, 0, 1);


			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(fx1, fy1, 0.0f);

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(fx2, fy1, 0.0f);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(fx2, fy2, 0.0f);

			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(fx1, fy2, 0.0f);

			glEnd();

			singleton->unsampleFBODirect(gp->gpuRes->getFBOS(curLayer));
		}




		//popTrace();

	}
void GameWorld::combineHolders ()
        {
		
		int i;
		
		
		bool entOff = false;
		
		
		if (entOff) {
			singleton->copyFBO("pages2FBO", "pagesFBO");
			singleton->copyFBO("water2FBO", "waterFBO");
		}
		else {
			singleton->bindShader("CombineShader");
			for (i = 0; i < 2; i++) {

				if (i == 0) {
					singleton->bindFBO("pagesFBO");
					singleton->sampleFBO("pages2FBO", 0);
					singleton->sampleFBO("pages3FBO", 2);
				}
				else {
					singleton->bindFBO("waterFBO");
					singleton->sampleFBO("water2FBO", 0);
					singleton->sampleFBO("water3FBO", 2);
				}
				

				singleton->drawFSQuad(1.0f);

				if (i == 0) {
					singleton->unsampleFBO("pages3FBO", 2);
					singleton->unsampleFBO("pages2FBO", 0);
				}
				else {
					singleton->unsampleFBO("water3FBO", 2);
					singleton->unsampleFBO("water2FBO", 0);
				}

				singleton->unbindFBO();
				
				
			}
			singleton->unbindShader();
		}
		
		
		
		
		
	}
void GameWorld::combineBuffers ()
        {

		singleton->bindShader("CombineShader");
		singleton->bindFBO("combineFBO");

		singleton->sampleFBO("pagesFBO", 0);
		singleton->sampleFBO("geomFBO", 2);

		singleton->drawFSQuad(1.0f);

		singleton->unsampleFBO("geomFBO", 2);
		singleton->unsampleFBO("pagesFBO", 0);

		singleton->unbindFBO();
		singleton->unbindShader();
	}
void GameWorld::transformEnt (GameEnt * curEnt)
                                           {
		
		// GameEntNode* curNode = NULL;
		
		// curNode = curEnt->baseNode->getNode(E_BONE_L_UPPERARM);
		// curNode->rotThe = sin(singleton->curTime/1000.0f)*3.14159f * 0.25f;
		
		// curNode = curNode->getNode(E_BONE_L_LOWERARM);
		// curNode->rotThe = sin(singleton->curTime/1000.0f)*3.14159f * 0.25f;
		// curNode->rotPhi = sin(singleton->curTime/1000.0f)*3.14159f * 2.0f;
		
		curEnt->baseNode->doTransform(singleton);
	}
void GameWorld::drawEnt (GameEnt * curEnt, bool drawAll)
                                                    {
		
		
		float scale = 1.0f*((float)(singleton->pixelsPerMeter));
		
		
		glLineWidth(0);
		
		
		
		// tangents
		singleton->setShaderFloat("matVal", getPackedColor(255, 0, 0));
		drawNodeEnt((curEnt->baseNode),&(curEnt->basePosition), scale, 0, drawAll);
		
		// bitangents
		singleton->setShaderFloat("matVal", getPackedColor(0, 255, 0));
		drawNodeEnt((curEnt->baseNode),&(curEnt->basePosition), scale, 1, drawAll);
		
		// normals
		singleton->setShaderFloat("matVal", getPackedColor(0, 0, 255));
		drawNodeEnt((curEnt->baseNode),&(curEnt->basePosition), scale, 2, drawAll);
		
		if (drawAll) {
			// nodes
			singleton->setShaderFloat("matVal", getPackedColor(254, 254, 254));
			drawNodeEnt((curEnt->baseNode),&(curEnt->basePosition), scale, 3, drawAll);
		}
		
		
		
	}
void GameWorld::drawNodeEnt (GameEntNode * curNode, FIVector4 * basePosition, float scale, int drawMode, bool drawAll)
          {
		
		// if (curNode == singleton->selectedNode) {
		// 	glLineWidth(3);
		// }
		// else {
		// 	glLineWidth(0);
		// }
		
		bool doProc = false;
		
		if (drawAll) {
			doProc = true;
		}
		else {
			if (curNode == singleton->selectedNode) {
				doProc = true;
			}
		}
		
		int i;
		
		
		if (doProc) {
			lineSeg[0].setFXYZRef(&(curNode->orgTrans[0]));
			lineSeg[0].multXYZ(  scale  );
			
			if (drawAll) {
				lineSeg[1].setFXYZRef(&(curNode->tbnTrans[drawMode%3]));
				lineSeg[1].multXYZ(  scale  );
			}
			else {
				lineSeg[1].setFXYZRef(&(curNode->tbnRotC[drawMode%3]));
				lineSeg[1].multXYZ(  (curNode->tbnRadInMeters0[drawMode%3]*scale*16.0f)  );
				lineSeg[1].multXYZ(&(curNode->tbnRadScale0));
				lineSeg[1].addXYZRef(&(lineSeg[0]));
			}
			
			
			lineSeg[0].addXYZRef(basePosition);
			lineSeg[1].addXYZRef(basePosition);
			
			
			
			switch(drawMode) {
				case 0: // tangents
				case 1: // bitangents
				case 2: // normals
					singleton->drawLine(&(lineSeg[0]),&(lineSeg[1]));
				break;
				case 3: // nodes
					singleton->drawCubeCentered(&(lineSeg[1]),0.0125f*scale);
				break;
				
			}
		}
		
		
		for (i = 0; i < curNode->children.size(); i++) {
			drawNodeEnt(curNode->children[i], basePosition, scale, drawMode, drawAll);
		}
		
	}
void GameWorld::clearVisitedPaths (PathHolder * pathHolder)
                                                       {
		while (pathHolder->visitedList.size() > 0) {
			blockData[
				pathHolder->visitedList.back().blockId
			]->buildingData[
				pathHolder->visitedList.back().index
			].visited = 0;
			pathHolder->visitedList.pop_back();
		}
	}
void GameWorld::clearPathList (PathHolder * pathHolder)
                                                   {
		pathHolder->pathList.clear();
	}
float GameWorld::getIdealPathLength (PathNode * blockAndIndex)
                                                          {
		return 		
			abs(blockAndIndex[0].x-blockAndIndex[1].x) +
			abs(blockAndIndex[0].y-blockAndIndex[1].y) +
			abs(blockAndIndex[0].z-blockAndIndex[1].z);
	}
int GameWorld::findAIPathRBT (PathHolder * pathHolder, PathNode * blockAndIndex, float _pathSlack)
          {


		//int begInd, int endInd

		float pathSlack = _pathSlack;

		int i;
		//int rbInd = 0;
		PathNode curInd;

		int testX = 0;
		int testY = 0;
		int testZ = 0;
		
		int wrappedX;
		int wrappedY;
		int wrappedZ;

		int curX = 0;
		int curY = 0;
		int curZ = 0;
		
		float idealPathLength = getIdealPathLength(blockAndIndex);
		
		int bestBlockId;
		int bestX;
		int bestY;
		int bestZ;
		int bestInd = 0;

		int testInd = 0;
		int curDir = 0;
		

		int endZ = blockAndIndex[1].z;
		int endY = blockAndIndex[1].y;
		int endX = blockAndIndex[1].x;
		
		int terDataVisPitchXY = singleton->terDataVisPitchXY;
		
		int conType;
		
		int pathCost;
		int bestCost;
		int invalidCost = 1<<30;

		int maxPops;

		PathNode tempNode;

		
		
		
		int numPathSteps = 0;
		
		
		
		//cout << "\n\n\nSTART COORD " << blockAndIndex[0].x << " " << blockAndIndex[0].y << " " << blockAndIndex[0].z << "\n";
		//cout << "END COORD " << blockAndIndex[1].x << " " << blockAndIndex[1].y << " " << blockAndIndex[1].z << "\n";
		

		BuildingNode* curBuildingData;
		GameBlock* testBlock;

		while ( (pathHolder->pathList.size() > 0) ) { // && (numPathSteps < 10)
			
			numPathSteps++;
			bestInd = -1;
			bestCost = invalidCost;

			curInd = pathHolder->pathList.back();
			
			
			
			if (curInd == blockAndIndex[1]) {
				goto DONE_FINDING_PATH;
			}
			
			//cout << "curBlockId " << curInd.blockId << "\n";
			
			curBuildingData = &(blockData[curInd.blockId]->buildingData[curInd.index]); 
			curBuildingData->visited = 1;
			pathHolder->visitedList.push_back(curInd);
			
			
			if (pathHolder->pathList.size() > idealPathLength*pathSlack) {
				cout << "Exceeded Path Slack\n";
				return false;
			}
				
			// 	maxPops = pathHolder->pathList.size() / 2;
			// 	pathSlack *= 1.1f;
				
			// 	if (pathSlack > 5.0f) {
			// 		cout << "Exceeded max path length\n";
			// 		return false;
			// 	}
				
			// 	for (i = 0; i < maxPops; i++) {
					
			// 		if (i < maxPops/2) {
			// 			blockData[
			// 				pathHolder->pathList.back().blockId
			// 			]->buildingData[
			// 				pathHolder->pathList.back().index
			// 			].visited = 0;
			// 		}
					
					
			// 		pathHolder->pathList.pop_back();
			// 	}
				
			// 	goto SKIP_PATH;
			
			

			curZ = curInd.z;
			curY = curInd.y;
			curX = curInd.x;

			
			for (curDir = 0; curDir < 4; curDir++) {


				testX = curX + dirModX[curDir];
				testY = curY + dirModY[curDir];
				testZ = curZ + dirModZ[curDir] + curBuildingData->con[curDir].heightDelta;
				
				
				wrappedX = (wrapCoord(testX,terDataVisPitchXY*worldSizeInBlocks.getIX())%terDataVisPitchXY)+singleton->terDataBufAmount;
				wrappedY = (wrapCoord(testY,terDataVisPitchXY*worldSizeInBlocks.getIY())%terDataVisPitchXY)+singleton->terDataBufAmount;
				wrappedZ = testZ+singleton->terDataBufAmount;
				
				testBlock = getBlockAtCoords(
					intDiv(testX,terDataVisPitchXY),
					intDiv(testY,terDataVisPitchXY),
					true
				);
				
				
				if (testBlock != NULL) {
					testInd = testBlock->getNodeIndex(wrappedX, wrappedY, wrappedZ, 0);

					if (testInd >= 0) {

						conType = curBuildingData->con[curDir].conType;
						
						//cout << "conType " << conType << " visited " << testBlock->buildingData[testInd].visited << "\n";
						
						if (
							( testBlock->isTraversable[conType] ) &&
							( testBlock->buildingData[testInd].visited == 0 )
						) {
							
							
							pathCost = abs(testX-endX) + abs(testY-endY) + abs(testZ-endZ);

							//cout << "pathCost " << pathCost << " bestCost " << bestCost << "\n";

							if (pathCost < bestCost) {
								bestInd = testInd;
								bestBlockId = testBlock->blockId;
								bestCost = pathCost;
								bestX = testX;
								bestY = testY;
								bestZ = testZ;
							}
						}
					}
				}
				
				
			}


			
			if (bestInd == -1) { // dead end, back up
				pathHolder->pathList.pop_back();
				
				//cout << "pop_back\n";
				//cout << "new length: " << pathHolder->pathList.size() << "\n\n";
			} else {
				tempNode.index = bestInd;
				tempNode.blockId = bestBlockId;
				tempNode.x = bestX;
				tempNode.y = bestY;
				tempNode.z = bestZ;
				pathHolder->pathList.push_back(tempNode);
				
				//cout << bestInd << " " << bestBlockId << " " << bestX << " " << bestY << " " << bestZ << "\n\n";
				
			}

SKIP_PATH:
			;
			
			

		}
		
DONE_FINDING_PATH:
		;
		
		return pathHolder->pathList.size() > 0;

	}
void GameWorld::drawPathLine (PathHolder * curPath, int r, int g, int b, float lw, float zoff)
                                                                                          {
		// IMPORTANT: size is a uint, do not let underflow happen!
		int totSize = curPath->pathList.size();
		totSize -= 1;
		int i;
		
		glLineWidth(lw);
		
		singleton->setShaderFloat("matVal", getPackedColor(r,g,b));
		for (i = 0; i < totSize; i++) {
			blockData[curPath->pathList[i].blockId]->nodeIndexToWorldSpaceInPixels(curPath->pathList[i].index, &(lineSeg[0]));
			blockData[curPath->pathList[i+1].blockId]->nodeIndexToWorldSpaceInPixels(curPath->pathList[i+1].index, &(lineSeg[1]));
			lineSeg[0].addXYZ(0.0f,0.0f,zoff);
			lineSeg[1].addXYZ(0.0f,0.0f,zoff);
			singleton->drawLine(&(lineSeg[0]),&(lineSeg[1]));
		}
	}
void GameWorld::drawAIPath (PathHolder * pathHolder, PathHolder * splitPathHolder)
                                                                             {
		
		
		
		
		int i;
		int curStep = singleton->currentStep;
		int curInd;
		int totSize;
		bool pathResult;
		bool doCont;
		
		float maxSlack = 8.0f;
		
		int numDivisions;
		int splitSize = 100;
		
		//int terDataBufPitchXY2 = singleton->terDataBufPitchXY*singleton->terDataBufPitchXY;
		//int endSegInd;
		
		// 0 - nothing
		// 1 - first marker placed
		// 2 - second marker placed
		// 3 - clear markers
		
		
		singleton->setShaderFloat("isWire", 0.0f);
		for (i = 0; i < curStep; i++) {
			
			blockPos[i].copyFrom(&(singleton->moveNodes[i]));
			blockPos[i].intDivXYZ(singleton->blockSizeInPixels);
			blockRef[i] = getBlockAtCoords(blockPos[i].getIX(), blockPos[i].getIY(), true);
			nodeInd[i] = blockRef[i]->findNearestNode(
				&(singleton->moveNodes[i]),
				&(nodePos[i]),
				&(nodePosInPixels[i])
			);
			blockAndIndexPath[i].index = nodeInd[i];
			blockAndIndexPath[i].blockId = blockRef[i]->blockId;
			blockAndIndexPath[i].x = nodePos[i].getIX();
			blockAndIndexPath[i].y = nodePos[i].getIY();
			blockAndIndexPath[i].z = nodePos[i].getIZ();
			
			singleton->setShaderFloat("matVal", getPackedColor(i*255, (1-i)*255, 0));
			singleton->drawCubeCentered(
				&(nodePosInPixels[i]),
				1.0f * singleton->pixelsPerMeter
			);
		}
		
		
		
		if (curStep == 2) {
			
			if (!foundPath) {
				
				finalPath = NULL;
				foundPath = true;
				
				if (
					//(blockRef[0] == blockRef[1]) &&
					(nodeInd[0] != -1) &&
					(nodeInd[1] != -1)
				) {
					
					clearVisitedPaths( pathHolder );
					clearPathList( pathHolder );
					clearVisitedPaths( splitPathHolder );
					clearPathList( splitPathHolder );
					
					
					pathHolder->pathList.push_back(blockAndIndexPath[0]);
					
					pathResult = findAIPathRBT(
						pathHolder,
						blockAndIndexPath,
						maxSlack
					);
					
					clearVisitedPaths( pathHolder );
					if (pathResult) {
						finalPath = pathHolder;
					}
					
					
					
					// if (pathResult) {	
					// 	numDivisions = pathHolder->pathList.size()/splitSize;
					// 	if (
					// 		(numDivisions >= 2) &&
					// 		(pathHolder->pathList.size() > getIdealPathLength(blockAndIndexPath)*1.5f)
					// 	) {
							
					// 		cout << "splitting path " << numDivisions << " times\n";
					// 		cout << "total path size is " << pathHolder->pathList.size() << "\n";
							
							
					// 		splitPathHolder->pathList.push_back(blockAndIndexPath[0]);
							
							
					// 		i = 0;
					// 		doCont = true;
					// 		while (doCont) {
					// 			blockAndIndexSplitPath[0] = pathHolder->pathList[i*splitSize];
								
								
					// 			cout << "split number " << i << "\n";
								
					// 			if ( (i+1)*splitSize >= pathHolder->pathList.size() ) {
					// 				blockAndIndexSplitPath[1] = pathHolder->pathList.back();
					// 				doCont = false;
					// 			}
					// 			else {
					// 				blockAndIndexSplitPath[1] = pathHolder->pathList[(i+1)*splitSize];
					// 			}
								
									
					// 			pathResult = findAIPathRBT(
					// 				splitPathHolder,
					// 				blockAndIndexSplitPath,
					// 				maxSlack
					// 			);
								
					// 			if (pathResult) {
									
					// 			}
					// 			else {
					// 				doCont = false;
					// 				cout << "Failed to find path at split #" << i << "\n";
					// 			}
								
					// 			i++;
								
					// 		}
							
					// 		finalPath = splitPathHolder;
							
					// 	}
						
					// }
					
				
					cout << "DONE FINDING PATH\n";
					
					//finalInd = blockRef[0]->findPath(nodeInd[0],nodeInd[1]);
					//doTraceND("finalInd ", i__s(finalInd), " nodeInd ", i__s(nodeInd[0]), " ", i__s(nodeInd[1]));
				}
				else {
					// doTraceND("Different Blocks");
				}
				
			}
			
		}
		else {
			foundPath = false;
			//finalInd = -1;
		}
		
		
		if ( (finalPath != NULL) && foundPath) {
			drawPathLine(pathHolder, 255, 255, 0, 2.0f, 0.0f);
			drawPathLine(splitPathHolder, 255, 0, 0, 2.0f, 4.0f*((float)singleton->pixelsPerMeter));
		}
		
		
		
		
	}
void GameWorld::renderGeom ()
        {
		//pushTrace("renderGeom()");

		int i;
		bool doProc;


		//glEnable(GL_DEPTH_TEST);

		singleton->bindShader("GeomShader");

		singleton->setShaderFloat("objectId",0.0);
		singleton->setShaderFloat("tiltAmount", singleton->tiltAmount);
		singleton->setShaderFloat("curTime", singleton->curTime);
		singleton->setShaderFloat("cameraZoom", singleton->cameraZoom);
		singleton->setShaderfVec3("cameraPos", cameraPos);
		singleton->setShaderfVec2("bufferDim", &(singleton->bufferModDim));
		

		singleton->bindFBO("geomFBO");
		//singleton->sampleFBO("pagesFBO");


		glEnable(GL_DEPTH_TEST);
		//remember 2x radius

		

		// if (!(singleton->entOn)) {
		// 	if (singleton->bShift) {
		// 		singleton->setShaderFloat("isWire", 1.0);
		// 		singleton->setShaderFloat("matVal", getPackedColor(255,0,255));
				
		// 		singleton->drawBox(&minLRInPixels,&maxLRInPixels);
		// 	}
		// }
		
		
		singleton->setShaderFloat("isWire", 0.0);

		switch (singleton->mouseState)
		{

		case E_MOUSE_STATE_MOVE:

			if (singleton->gridOn == 1.0f)
			{
				// singleton->setShaderFloat("matVal", getPackedColor(255, 0, 255));
				// singleton->setShaderFloat("isWire", 1.0f);
				// singleton->drawBox(&minLRInPixels, &maxLRInPixels);
			}
			
			
			

			break;
		
		case E_MOUSE_STATE_BRUSH:
			singleton->setShaderFloat("matVal", getPackedColor(255, 0, 0));
			singleton->setShaderFloat("isWire", 1.0);
			singleton->drawCubeCentered(&lastUnitPos, ((int)singleton->curBrushRad) * (singleton->unitSizeInPixels)  );
			glClear(GL_DEPTH_BUFFER_BIT);
		break;
		// case E_MOUSE_STATE_OBJECTS:



			



		// 	break;
		case E_MOUSE_STATE_PICKING:
			// singleton->setShaderFloat("matVal", getPackedColor(0,255,0));
			// singleton->drawBoxUp(lastUnitPos, 0.25f*singleton->pixelsPerMeter, 0.25f*singleton->pixelsPerMeter, 2.0f*singleton->pixelsPerMeter);



			if (singleton->highlightedGeom == NULL)
			{

			}
			else
			{
				singleton->setShaderFloat("matVal", getPackedColor(254, 254, 254));
				singleton->setShaderFloat("isWire", 1.0);

				minv.setFXYZRef(singleton->highlightedGeom->getVisMinInPixelsT());
				maxv.setFXYZRef(singleton->highlightedGeom->getVisMaxInPixelsT());

				minv.addXYZ(-0.25 * singleton->pixelsPerMeter);
				maxv.addXYZ(0.25 * singleton->pixelsPerMeter);


				singleton->drawBox(&minv, &maxv);
			}

			if (singleton->selectedGeom == NULL)
			{

			}
			else
			{
				singleton->setShaderFloat("matVal", getPackedColor(255, 255, 0));
				singleton->setShaderFloat("isWire", 1.0);

				minv.setFXYZRef(singleton->selectedGeom->getVisMinInPixelsT());
				maxv.setFXYZRef(singleton->selectedGeom->getVisMaxInPixelsT());

				// minv.addXYZ(-0.25 * singleton->pixelsPerMeter);
				// maxv.addXYZ(0.25 * singleton->pixelsPerMeter);


				singleton->drawBox(&minv, &maxv);
			}


			break;

		}
		
		if (singleton->pathfindingOn) {
			drawAIPath( &(singleton->charPathHolder), &(singleton->splitPathHolder) );
		}
		
		if (singleton->bCtrl) {
			for (i = 1; i < singleton->dynObjects.size(); i++) {
				if (singleton->dynObjects[i]->doRender)
				{

					doProc = false;

					if (i >= E_OBJ_LIGHT0)
					{
						if (i - E_OBJ_LIGHT0 < singleton->numDynLights)
						{
							doProc = true;
						}
					}
					else
					{
						doProc = true;
					}

					if (doProc)
					{
						singleton->setShaderFloat("objectId",i);
						singleton->setShaderFloat("matVal", singleton->dynObjects[i]->colPacked);
						curBoxPos = &(singleton->dynObjects[i]->pos);
						singleton->drawCubeCentered(curBoxPos, singleton->dynObjects[i]->radius);


						if (i == singleton->activeObject)
						{
							//singleton->drawCrossHairs(singleton->dynObjects[i]->pos,4.0f);
						}
					}


				}
			}
		}

		singleton->setShaderFloat("objectId",0.0);

		if (singleton->charState == E_CHAR_STATE_RENDERED) { //E_CHAR_STATE_SKEL
			//transformEnt(singleton->testHuman);
			drawEnt(singleton->testHuman, false);
		}
		


		// for (i = 1; i < lightCount; i++) {
		//  singleton->setShaderFloat("matVal", activeLights[i]->colPacked);
		//  curBoxPos = &(activeLights[i]->pos);
		//  singleton->drawCubeCentered(curBoxPos,0.125f*singleton->pixelsPerMeter);
		// }



		glDisable(GL_DEPTH_TEST);



		//singleton->unsampleFBO("pagesFBO");
		singleton->unbindFBO();
		singleton->unbindShader();

		//glDisable(GL_DEPTH_TEST);

		//popTrace();

	}
void GameWorld::modifyUnit (FIVector4 * fPixelWorldCoordsBase, E_BRUSH brushAction)
        {
		
		//pushTrace("modifyUnit()");

		int radius = ((int)singleton->curBrushRad);

		FIVector4 fPixelWorldCoords;
		fPixelWorldCoords.copyFrom(fPixelWorldCoordsBase);


		uint *vd_ptr;
		uint *vdl_ptr;

		GamePage *curPage;


		int ind2;
		int pageSizeMult = visPageSizeInUnits * (singleton->bufferMult);


		int i, j, k, m, n, o, p;

		int ii;
		int jj;
		int kk;

		int pixelPS = (singleton->unitSizeInPixels * singleton->visPageSizeInUnits);



		lastUnitPos.copyFrom(&fPixelWorldCoords);
		lastUnitPos.intDivXYZ(singleton->unitSizeInPixels);
		lastUnitPos.multXYZ(singleton->unitSizeInPixels);
		lastUnitPos.setFW(singleton->unitSizeInPixels);
		
		
		

		lastPagePos.copyFrom(&fPixelWorldCoords);
		lastPagePos.intDivXYZ(pixelPS);
		lastPagePos.multXYZ(pixelPS);
		lastPagePos.setFW(pixelPS);

		bool changes = false;

		int newRad = 2 + radius / visPageSizeInUnits;


		uint linV;
		uint nearV;

		uint linR;
		uint linG;
		uint linB;
		uint linA;

		uint nearR;
		uint nearG;
		uint nearB;
		uint nearA;

		bool isInside;
		
		
		
		
		


		pagePos.copyFrom(&fPixelWorldCoords);
		unitPos.copyFrom(&fPixelWorldCoords);

		pagePos.intDivXYZ( pixelPS );
		unitPos.intDivXYZ( singleton->unitSizeInPixels );


		unitPosMin.copyFrom(&unitPos);
		unitPosMax.copyFrom(&unitPos);
		unitPosMin.addXYZ((float)radius, -1.0f);
		unitPosMax.addXYZ((float)radius, 1.0f);

		unitPosCenter.copyFrom(&unitPosMin);
		unitPosCenter.addXYZRef(&unitPosMax);
		unitPosCenter.multXYZ(0.5f);
		
		
		float unitPosRad = (unitPosMax.getFX()-unitPosMin.getFX())*0.5f;
		float unitPosCurDis = 0.0f;
		
		FIVector4 blockPos;
		blockPos.copyFrom(&pagePos);
		blockPos.intDivXYZ(singleton->blockSizeInPages);
		GameBlock *curBlock = getBlockAtCoords(blockPos.getIX(),blockPos.getIY(),true);


		// unitPosMinIS.copyFrom(&unitPos);
		// unitPosMaxIS.copyFrom(&unitPos);
		// unitPosMinIS.addXYZ((float)radius+1, -1.0f);
		// unitPosMaxIS.addXYZ((float)radius-1, 1.0f);


		if (brushAction == E_BRUSH_MOVE)
		{
			//popTrace();
			return;
		}
		
		cout << "modifyUnit\n";

		if (singleton->isMacro) {
			
			curBlock->modifyTerrain(
				&fPixelWorldCoords,
				brushAction == E_BRUSH_SUB
			);
			
		}

		


		for (m = 0; m < 2; m++)
		{
			for (i = -newRad; i <= newRad; i++)
			{
				for (j = -newRad; j <= newRad; j++)
				{
					for (k = -newRad; k <= newRad; k++)
					{




						ii = i + pagePos.getIX();
						jj = j + pagePos.getIY();
						kk = k + pagePos.getIZ();
						
						

						if (
							checkBounds(kk,worldSizeInPages.getIZ())
							
						)
						{

							//

							curPage = getPageAtCoords(ii, jj, kk, true);


							if (true) {


								startBounds.maxXYZ(&unitPosMin, &(curPage->worldUnitMin));
								endBounds.minXYZ(&unitPosMax, &(curPage->worldUnitMax));




								




								if (
									(startBounds.getFX() > endBounds.getFX()) ||
									(startBounds.getFY() > endBounds.getFY()) ||
									(startBounds.getFZ() > endBounds.getFZ())
								)
								{

								}
								else
								{




									for (n = startBounds.getIX(); n < endBounds.getIX(); n++)
									{
										for (o = startBounds.getIY(); o < endBounds.getIY(); o++)
										{
											for (p = startBounds.getIZ(); p < endBounds.getIZ(); p++)
											{
												
												
												

												tempVec.setIXYZ(n, o, p);
												isInside = tempVec.inBoundsXYZ(&unitPosMin, &unitPosMax);

												unitPosCurDis = unitPosCenter.distance(&tempVec);

												//TODO: fix this to wrap
												if (
													tempVec.inBoundsXYZ(
														&(curPage->worldUnitMin),
														&(curPage->worldUnitMax)
													) &&
													(
														unitPosCurDis < unitPosRad
													)
												)
												{
													tempVec.addXYZRef( &(curPage->worldUnitMin), -1.0);

													ind2 = tempVec.getIZ() * pageSizeMult * pageSizeMult + tempVec.getIY() * pageSizeMult + tempVec.getIX();

													if (
														(ind2 < 0) ||
														(ind2 >= pageSizeMult * pageSizeMult * pageSizeMult)
													)	{
														// index out of range	
														cout << "index out of range\n";
													}
													else
													{

														if (m == 0)
														{

															
															
															if (singleton->isMacro) {
																
															}
															else {
																vd_ptr = curPage->getVolData();
																vdl_ptr = curPage->getVolDataLinear();

																linV = vdl_ptr[ind2];
																nearV = vd_ptr[ind2];

																linR = (linV) & 255;
																linG = (linV >> 8) & 255;
																linB = (linV >> 16) & 255; // used for subtraction
																linA = (linV >> 24) & 255; // used for addition

																nearR = (nearV) & 255;
																nearG = (nearV >> 8) & 255;
																nearB = (nearV >> 16) & 255;
																nearA = (nearV >> 24) & 255;


																if (p >= singleton->worldSizeInUnits.getFZ()) {

																	linA = 0;
																}
																else
																{

																	if (brushAction == E_BRUSH_SUB) {
																		if (isInside)
																		{
																			linA = 0;
																			//linB = 255;
																			
																			linB += 40;
																			if (linB > 255) {
																				linB = 255;
																			}
																			
																			// (tex2.b > 0.5)
																			// 1.0 = nothing
																			// 0.0 = solid
																			// linB = clampf(
																				
																			// 	(unitPosCurDis/unitPosRad - unitPosCurDis/(unitPosRad+1)),
																			// 	0.0f,
																			// 	1.0f
																			// )*255.0f;
																		}

																	}
																	else
																	{

																		if (isInside)
																		{
																			//linA = 255;
																			linA += 40;
																			if (linA > 255) {
																				linA = 255;
																			}
																			linB = 0;
																		}

																		nearA = 0;

																	}
																}

																vd_ptr[ind2] = (nearA << 24) | (nearB << 16) | (nearG << 8) | (nearR);
																vdl_ptr[ind2] = (linA << 24) | (linB << 16) | (linG << 8) | (linR);
																curPage->volDataModified = true;	
															}

															curPage->parentGPH->childrenDirty = true;
															curPage->isDirty = true;
															changes = true;
														}
														else
														{
															if (curPage->parentGPH->childrenDirty)
															{
																curPage->parentGPH->refreshChildren(true,true,true);
															}
														}

													}

												}


											}
										}
									}
								}
							}

						}




					}
				}
			}
		}
		
		if (changes)
		{
			singleton->changesMade = true;
			singleton->wsBufferInvalid = true;
		}



		//popTrace();

	}
void GameWorld::renderWorldSpaceGPU ()
        {
		singleton->bindShader("WorldSpaceShader");

		singleton->bindFBO("worldSpaceFBO");
		singleton->sampleFBO("pagesFBO", 0);
		singleton->sampleFBO("waterFBO", 2);
		singleton->sampleFBO("geomFBO", 4);

		//MUST BE CALLED AFTER FBO IS BOUND
		
		singleton->setShaderInt("iMax", 4);
		singleton->setShaderVec2("resolution", singleton->currentFBOResolutionX, singleton->currentFBOResolutionY);
		singleton->setShaderVec2("mouseCoords", singleton->mouseX, singleton->mouseY);
		singleton->setShaderfVec3("cameraPos", cameraPos);
		singleton->setShaderfVec2("bufferDim", &(singleton->bufferModDim) );
		singleton->setShaderFloat("cameraZoom", singleton->cameraZoom);
		singleton->setShaderFloat("tiltAmount", singleton->tiltAmount);

		singleton->drawFSQuad(1.0f);

		
		singleton->unsampleFBO("geomFBO", 4);
		singleton->unsampleFBO("waterFBO", 2);
		singleton->unsampleFBO("pagesFBO", 0);


		singleton->unbindFBO();
		singleton->unbindShader();
		
		
	}
void GameWorld::getWorldSpaceBuffer (int bufNum)
        {

		if (singleton->autoScroll) {
			
		}
		else {
			singleton->getFBOWrapper("worldSpaceFBO", bufNum)->getPixels();
		}

		singleton->wsBufferInvalid = false;

	}
float GameWorld::weighPath (float x1, float y1, float x2, float y2, float rad, bool doSet, bool isOcean)
        {

		int i;
		int iMax = (int)min(64.0f, rad * 4.0f);

		float fi;
		float fMax = (float)(iMax - 1);
		float lerp;

		float curX;
		float curY;


		float startVal = curFBO->getPixelAtWrapped((int)x1, (int)y1, hmChannel);
		float lastRes = startVal;
		float curRes;
		float curRes2;
		float tempRes;
		float tot = 0.0f;

		bool startsInWater = startVal <= seaLevel;

		for (i = 1; i < iMax; i++)
		{
			fi = (float)i;
			lerp = fi / fMax;
			curX = (1.0f - lerp) * x1 + (lerp) * x2;
			curY = (1.0f - lerp) * y1 + (lerp) * y2;
			curRes = curFBO->getPixelAtWrapped((int)curX, (int)curY, hmChannel);

			if (isOcean)
			{
				if (doSet)
				{

					if (curRes > seaLevel)
					{

						tempRes = abs(curRes - lastRes);
						tempRes = tempRes * tempRes * tempRes;
						//tempRes = 255-curRes;
					}
					else
					{
						tempRes = curRes;
					}


					//tempRes = abs(curRes-lastRes);
					//tempRes = tempRes*tempRes*tempRes;
					if ((curRes > seaLevel) != (lastRes > seaLevel))
					{
						tempRes += 100000.0f;
					}

					// if (startsInWater) {
					//  if (curRes > seaLevel) {
					//      tempRes += 1000000.0f;
					//  }
					// }

				}
				else
				{
					tempRes = 0.0;
					if (curRes > seaLevel)
					{
						tempRes = 1.0f;
					}
					else
					{
						tempRes = -1.0f;
					}
				}
			}
			else
			{
				tempRes = abs(curRes - lastRes) * 10.0 + curRes;
				//tempRes = tempRes;
				if (curRes <= seaLevel - 20.0f)
				{
					tempRes += 100000.0f;
				}
				if ((curRes > seaLevel) != (lastRes > seaLevel))
				{
					tempRes += 100000.0f;
				}
			}


			tot += tempRes;
			lastRes = curRes;

		}

		return tot;
	}
float GameWorld::findBestPath (float x1, float y1, float x2, float y2, int generation, int roadIndex, bool doSet, bool isOcean)
        {
		int i;
		int j;

		coordAndIndex baseCoord;
		coordAndIndex bestCoord;
		coordAndIndex testCoord;

		float mpx = (x1 + x2) / 2.0;
		float mpy = (y1 + y2) / 2.0;
		float dis = quickDis(x1, y1, x2, y2);
		float rad = dis / 2.0;
		float mpxTemp;
		float mpyTemp;
		float delta;
		float bestDis;
		float curDis;
		float bestDelta = FLT_MAX;
		float bestX;
		float bestY;
		float genMod;

		int q;
		int p;

		int ibx;
		int iby;
		int ix2;
		int iy2;
		int tot1 = 0;
		int tot2 = 0;
		int iRad;
		int numTries = max((int)(rad), 20);

		if ( (rad < 2.0f) || (generation > 1024) )
		{
			// do manhattan distance

			if (doSet)
			{
				ibx = x1;
				iby = y1;
				ix2 = x2;
				iy2 = y2;


				while (ibx != ix2)
				{
					curFBO2->setPixelAtWrapped(ibx, iby, pathChannel, 255);
					if (ibx < ix2)
					{
						ibx++;
					}
					else
					{
						ibx--;
					}
				}
				while (iby != iy2)
				{
					curFBO2->setPixelAtWrapped(ibx, iby, pathChannel, 255);
					if (iby < iy2)
					{
						iby++;
					}
					else
					{
						iby--;
					}
				}

				curFBO2->setPixelAtWrapped(ibx, iby, pathChannel, 255);
			}
			else
			{

			}

			return 0.0f;

		}



		genMod = 2.0f;

		// if (generation > 32) {
		//  return 0.0f;
		// }




		for (i = 0; i < numTries; i++)
		{
			mpxTemp = mpx + (fGenRand() * dis - rad) / genMod;
			mpyTemp = mpy + (fGenRand() * dis - rad) / genMod;

			delta = weighPath(x1, y1, mpxTemp, mpyTemp, rad / 2.0f, doSet, isOcean);
			delta += weighPath(mpxTemp, mpyTemp, x2, y2, rad / 2.0f, doSet, isOcean);

			if (delta < bestDelta)
			{
				bestDelta = delta;
				bestX = mpxTemp;
				bestY = mpyTemp;
			}

		}



		if (doSet)
		{



			if (generation < 8)
			{

				baseCoord.x = bestX;
				baseCoord.y = bestY;
				baseCoord.index = roadIndex;
				//roadCoords.push_back(baseCoord);

				bestDis = FLT_MAX;
				for (i = 0; i < roadCoords.size(); i++)
				{
					testCoord = roadCoords[i];


					if (baseCoord.index == testCoord.index)
					{

					}
					else
					{
						curDis = coordDis(&baseCoord, &testCoord);

						if (curDis < bestDis)
						{
							bestDis = curDis;
							bestCoord = roadCoords[i];
						}
					}


				}

				if (bestDis != FLT_MAX)
				{
					curDis = coordDis(&bestCoord, &baseCoord);

					if (curDis < min(400.0f, rad) )   //
					{
						baseCoord = bestCoord;
						baseCoord.index = roadIndex;
					}

					bestX = baseCoord.x;
					bestY = baseCoord.y;
				}

				roadCoords.push_back(baseCoord);
			}


			//curFBO2->setPixelAtWrapped((int)bestX, (int)bestY, pathChannel, 255);
			//curFBO2->setPixelAtWrapped((int)bestX, (int)bestY, breadCrumbChannel, 255);
			findBestPath(x1, y1, bestX, bestY, generation + 1, roadIndex, doSet, isOcean);
			findBestPath(bestX, bestY, x2, y2, generation + 1, roadIndex, doSet, isOcean);
		}

		return bestDelta;

	}
void GameWorld::initMap ()
        {
		mapLockOn = true;

		//pushTrace("initMap()");

		mapSwapFlag = 0;

		mapStep = 0.0f;



		FBOWrapper *fbow = singleton->getFBOWrapper("hmFBO", 0);
		FBOWrapper *fbow2 = singleton->getFBOWrapper("cityFBO", 0);

		curFBO = fbow;
		curFBO2 = fbow2;

		

		FIVector4 startVec;
		FIVector4 endVec;
		FIVector4 midPointVec;

		int w = fbow2->width;
		int h = fbow2->height;


		//0:r
		//1:g
		//2:b
		//3:a




		int i;
		int j;
		int k;
		int m;
		int totSize = w * h;
		int *btStack = new int[totSize];
		int btStackInd = 0;
		int curInd;
		int curX;
		int curY;
		int destX;
		int destY;
		int lastDir;
		int curXRight;
		int curXLeft;
		int curYUp;
		int curYDown;
		int testX;
		int testY;
		int testInd;
		int basePix;
		int basePix2;
		int testPix;
		int testPix1;
		int testPix2;
		int testPix3;
		int testPix4;
		int count;
		int p1;
		int p2;



		// int alleyFlag = 32;
		// int streetFlag = 64;
		// int highwayFlag = 128;

		int startDir;
		int curDir;
		blockMip = intLogB2(singleton->blockSizeInLots);

		int cx1;
		int cy1;
		int cx2;
		int cy2;

		int histogram[256];

		float delta;
		float bestDelta;
		float nextBestDelta;

		int nextBestInd;
		int bestDir;
		int nextBestDir;

		int bestInd;
		int tempVal;

		int xind;
		int yind;
		int curHeight;

		bool isValid;
		bool notFound;
		bool touchesWater;
		bool doBreak;

		float mult;
		float tempDis;





		for (i = 0; i < 16; i++)
		{
			singleton->paramArrMap[i * 3 + 0] = fGenRand();
			singleton->paramArrMap[i * 3 + 1] = fGenRand();
			singleton->paramArrMap[i * 3 + 2] = fGenRand();
		}

		for (i = 0; i < 6; i++)
		{
			singleton->paramArrMap[i * 3 + 0] = i;
		}

		for (i = 0; i < 30; i++)
		{
			p1 = iGenRand(0, 5);
			p2 = iGenRand(0, 5);

			if (p1 != p2)
			{
				tempVal = singleton->paramArrMap[p1];
				singleton->paramArrMap[p1] = singleton->paramArrMap[p2];
				singleton->paramArrMap[p2] = tempVal;
			}
		}



		singleton->bindShader("Simplex2D");
		singleton->bindFBO("simplexFBO");
		singleton->setShaderFloat("curTime", fGenRand() * 100.0f); //singleton->curTime);
		singleton->drawFSQuad(1.0f);
		singleton->unbindFBO();
		singleton->unbindShader();

		singleton->bindShader("TerrainMix");
		singleton->bindFBO("hmFBOLinear");
		singleton->sampleFBO("simplexFBO", 0);
		singleton->setShaderTexture(1, singleton->imageHM0->tid);
		singleton->setShaderTexture(2, singleton->imageHM1->tid);
		singleton->setShaderArrayfVec3("paramArrMap", singleton->paramArrMap, 16 );
		singleton->setShaderFloat("mapSampScale", 1.0f); //singleton->mapSampScale
		singleton->drawFSQuad(1.0f);
		singleton->setShaderTexture(2, 0);
		singleton->setShaderTexture(1, 0);
		singleton->unsampleFBO("simplexFBO", 0);
		singleton->unbindFBO();
		singleton->unbindShader();

		singleton->copyFBO("hmFBOLinear", "hmFBO");


		fbow->getPixels(true);
		fbow->setAllPixels(densityChannel, 255);
		fbow->setAllPixels(idChannel, 0);
		fbow->setAllPixels(blockChannel, 0);


		// determine sea level

		for (i = 0; i < 256; i++)
		{
			histogram[i] = 0;
		}
		
		int minSL = 0;
		int maxSL = 0;
		int curSL = 0;
		int avgSL = 0;
		
		for (i = 0; i < totSize; i++)
		{
			curSL = fbow->getPixelAtIndex(i, hmChannel);
			
			if (curSL < minSL) {
				minSL = curSL;
			}
			if (curSL > maxSL) {
				maxSL = curSL;
			}
			
			histogram[curSL]++;
		}

		int totFilled = 0;
		i = 0;
		while (totFilled < (totSize * 40) / 100 )
		{
			totFilled += histogram[i];
			i++;
		}
		
		avgSL = (minSL*3+maxSL*1)/4;


		seaLevel = i+20; //avgSL;//
		seaSlack = seaLevel - 1;
		cout << "Sea Level: " << seaLevel << "\n";



		cout << "start place cities\n";

		for (i = 1; i < numProvinces; i++)
		{

			isValid = false;

			do
			{

				xind = (int)(fGenRand() * fbow->width);
				yind = (int)(fGenRand() * fbow->height);

				tempVec1.setFXYZ(xind, yind, 0.0f);

				notFound = false;
				for (j = 1; j < i; j++)
				{
					tempVec2.setFXYZ(provinceX[j], provinceY[j], 0.0f);
					tempDis = tempVec2.wrapDistance(&tempVec1, w, false);

					if (tempDis < 200.0f * singleton->mapSampScale)
					{
						notFound = true;
					}

				}

				if (notFound)
				{

				}
				else
				{
					if (fbow->getPixelAtC(xind, yind, idChannel) == 0)
					{
						curHeight = fbow->getPixelAtC(xind, yind, hmChannel);

						if (
							(curHeight > seaLevel)
						)
						{

							provinceX[i] = xind;
							provinceY[i] = yind;
							fbow->setPixelAtC(xind, yind, idChannel, i);
							fbow->setPixelAtC(xind, yind, densityChannel, 0);
							isValid = true;

						}
					}
				}



			}
			while (!isValid);

		}

		cout << "end place cities\n";


		cout << "start grow provinces\n";

		fbow->cpuToGPU();

		singleton->copyFBO("hmFBO", "swapFBO0");
		singleton->bindShader("MapBorderShader");
		mapStep = 0.0f;
		for (i = 0; i < 1024; i++)
		{

			singleton->bindFBO("swapFBO", mapSwapFlag);
			singleton->sampleFBO("swapFBO", 0, mapSwapFlag);
			singleton->setShaderFloat("seaSlack", ((float)seaSlack) / 255.0 );
			singleton->setShaderFloat("mapStep", mapStep);
			singleton->setShaderFloat("texPitch", w);
			singleton->drawFSQuad(1.0f);
			singleton->unsampleFBO("swapFBO", 0, mapSwapFlag);
			singleton->unbindFBO();


			mapSwapFlag = 1 - mapSwapFlag;
			mapStep += 1.0f;
		}
		singleton->unbindShader();


		singleton->bindShader("MapBorderShader");
		mapStep = 1.0f;
		for (i = 0; i < 256; i++)
		{

			singleton->bindFBO("swapFBO", mapSwapFlag);
			singleton->sampleFBO("swapFBO", 0, mapSwapFlag);
			singleton->setShaderFloat("seaSlack", ((float)seaSlack) / 255.0 );
			singleton->setShaderFloat("mapStep", -mapStep);
			singleton->setShaderFloat("texPitch", w);
			singleton->drawFSQuad(1.0f);
			singleton->unsampleFBO("swapFBO", 0, mapSwapFlag);
			singleton->unbindFBO();


			mapSwapFlag = 1 - mapSwapFlag;
			mapStep += 1.0f;
		}
		singleton->unbindShader();


		singleton->copyFBO("swapFBO0", "hmFBO");


		fbow->getPixels();
		fbow->updateMips();

		cout << "end grow provinces\n";


		cout << "start find neighboring cities\n";

		for (i = 0; i < numProvinces * numProvinces; i++)
		{
			provinceGrid[i] = 0;
		}

		for (k = 0; k < totSize; k++)
		{
			curInd = k;
			curY = curInd / w;
			curX = curInd - curY * w;

			basePix = fbow->getPixelAtIndex(curInd, idChannel);

			testPix = fbow->getPixelAtIndex(fbow->getIndex(curX + 1, curY), idChannel);
			testPix2 = fbow->getPixelAtIndex(fbow->getIndex(curX, curY + 1), idChannel);


			if (basePix != 0)
			{
				if (testPix != 0)
				{
					if (basePix != testPix)
					{

						provinceGrid[basePix * numProvinces + testPix] = 1;
						provinceGrid[basePix + testPix * numProvinces] = 1;

					}
				}
				if (testPix2 != 0)
				{
					if (basePix != testPix2)
					{
						provinceGrid[basePix * numProvinces + testPix2] = 1;
						provinceGrid[basePix + testPix2 * numProvinces] = 1;
					}
				}
			}


		}

		cout << "end find neighboring cities\n";




		// 1 - x+
		// 2 - x-
		// 4 - y+
		// 8 - y-


		cout << "start find city blocks\n";


		fbow2->getPixels(true);
		fbow2->setAllPixels(btChannel, 15);
		fbow2->setAllPixels(stChannel, 0);
		fbow2->setAllPixels(pathChannel, 0);
		fbow2->setAllPixels(houseChannel, 0);


		int blockMod = singleton->blockSizeInLots;
		for (k = 0; k < totSize; k++)
		{
			curInd = k;
			curY = curInd / w;
			curX = curInd - curY * w;

			basePix = fbow->getMipVal(curX, curY, blockMip, idChannel, MAX_MIP);
			testPix = fbow->getMipVal(curX, curY, blockMip, densityChannel, AVG_MIP);

			testPix1 = fbow->getMipVal(curX, curY, blockMip, idChannel, MAX_MIP, -1, -1, 0);
			testPix2 = fbow->getMipVal(curX, curY, blockMip, idChannel, MAX_MIP, -1, 1, 0);
			testPix3 = fbow->getMipVal(curX, curY, blockMip, idChannel, MAX_MIP, -1, 0, -1);
			testPix4 = fbow->getMipVal(curX, curY, blockMip, idChannel, MAX_MIP, -1, 0, 1);



			if (testPix1 != testPix2 || testPix3 != testPix4 || testPix > 120 )
			{
				fbow->setPixelAtIndex(curInd, blockChannel, 0);
			}
			else
			{
				fbow->setPixelAtIndex(curInd, blockChannel, basePix);
			}

		}

		fbow->cpuToGPU();
		singleton->copyFBO("hmFBO", "hmFBOLinear");

		cout << "end find city blocks\n";


		cout << "start add in city roads\n";
		//add in city roads

		for (i = 0; i < numProvinces; i++)
		{
			// recursive backtrack
			btStack[0] = fbow2->getIndex(provinceX[i], provinceY[i]);
			btStackInd = 0;

			while (btStackInd > -1)
			{

				curInd = btStack[btStackInd];
				curY = curInd / w;
				curX = curInd - curY * w;

				fbow2->orPixelAtIndex(curInd, btChannel, visFlag);

				startDir = 0;
				count = 0;
				notFound = true;
				bestDelta = FLT_MAX;


				testPix2 = fbow->getPixelAtIndex(curInd, blockChannel);

				//testPix2 = fbow->getMipVal(curX,curY,blockMip,densityChannel,AVG_MIP);
				//testPix3 = fbow->getMipVal(curX,curY,blockMip,idChannel,MIN_MIP);
				//testPix4 = fbow->getMipVal(curX,curY,blockMip,idChannel,MAX_MIP);


				if ( testPix2 != 0 )
				{
					do
					{
						curDir = (startDir + count) % 4;

						testX = curX + dirModX[curDir];
						testY = curY + dirModY[curDir];
						testInd = fbow2->getIndex(testX, testY);
						testPix = fbow2->getPixelAtIndex(testInd, btChannel);
						testPix3 = fbow->getPixelAtIndex(testInd, blockChannel);

						if ( (testPix & visFlag) == 0 && (testPix3 != 0))
						{
							//not visited, proceed
							notFound = false;


							delta = abs(
												fbow->getPixelAtIndex(curInd, hmChannel) -
												fbow->getPixelAtIndex(testInd, hmChannel)
											);

							if (delta < bestDelta)
							{
								bestDelta = delta;
								bestDir = curDir;
								bestInd = testInd;
							}

						}

						count++;
					}
					while (count < 4); //notFound &&
				}

				if (notFound)
				{
					btStackInd--;
				}
				else
				{

					// join the two and remove walls
					fbow2->andPixelAtIndex(curInd, btChannel, dirFlags[bestDir]);
					fbow2->andPixelAtIndex(bestInd, btChannel, dirFlagsOp[bestDir]);

					btStackInd++;
					btStack[btStackInd] = bestInd;
				}

			}
		}

		cout << "end add in city roads\n";



		// clear visited
		for (k = 0; k < totSize; k++)
		{
			testPix = fbow2->getPixelAtIndex(k, btChannel);
			if ( (testPix & visFlag) == 0)
			{
				//not visited
				for (i = 0; i < 4; i++)
				{
					fbow2->andPixelAtIndex(k, btChannel, dirFlags[i]);
				}
			}
			else
			{
				//visited
			}

			fbow2->andPixelAtIndex(k, btChannel, visFlagO );
		}



		cout << "start link close cities\n";

		// link close cities

		for (i = 1; i < numProvinces - 1; i++)
		{
			for (j = i + 1; j < numProvinces; j++)
			{

				curInd = i + j * numProvinces;

				if (provinceGrid[curInd] == 1)
				{
					p1 = i;
					p2 = j;



					tempVec1.setIXYZ(provinceX[p1], provinceY[p1], 0);
					tempVec2.setIXYZ(provinceX[p2], provinceY[p2], 0);

					tempVec2.wrapDistance(&tempVec1, w);
					tempVec3.copyFrom(&tempVec1);

					findBestPath(
						tempVec2.getFX(),
						tempVec2.getFY(),
						tempVec3.getFX(),
						tempVec3.getFY(),
						0,
						curInd,
						true,
						false
					);

				}

			}
		}



		cout << "end link close cities\n";



		floatAndIndex *oceanRes = new floatAndIndex[numProvinces * numProvinces];

		for (i = 0; i < numProvinces * numProvinces; i++)
		{
			oceanRes[i].value = FLT_MAX;
			oceanRes[i].index1 = 0;
			oceanRes[i].index2 = 0;
		}

		cout << "start find biggest ocean gaps\n";


		for (k = 0; k < 2; k++)
		{

			cout << "iteration: " << k << "\n";

			count = 0;

			if (k == 0)
			{
				for (i = 1; i < numProvinces - 1; i++)
				{
					for (j = i + 1; j < numProvinces; j++)
					{
						curInd = i + j * numProvinces;
						if (provinceGrid[curInd] != 1)
						{
							p1 = i;
							p2 = j;



							tempVec1.setIXYZ(provinceX[p1], provinceY[p1], 0);
							tempVec2.setIXYZ(provinceX[p2], provinceY[p2], 0);

							tempVec2.wrapDistance(&tempVec1, w);
							tempVec3.copyFrom(&tempVec1);


							oceanRes[count].value = findBestPath(
																				tempVec2.getFX(),
																				tempVec2.getFY(),
																				tempVec3.getFX(),
																				tempVec3.getFY(),
																				0,
																				curInd,
																				false,
																				true
																			);
							oceanRes[count].index1 = i;
							oceanRes[count].index2 = j;

							count++;

						}

					}
				}
			}
			else
			{
				bubbleSortF(oceanRes, numProvinces * numProvinces);


				for (i = 0; i < 30; i++)
				{

					p1 = oceanRes[i].index1;
					p2 = oceanRes[i].index2;

					curInd = p1 + p2 * numProvinces;

					tempVec1.setIXYZ(provinceX[p1], provinceY[p1], 0);
					tempVec2.setIXYZ(provinceX[p2], provinceY[p2], 0);

					tempVec2.wrapDistance(&tempVec1, w);
					tempVec3.copyFrom(&tempVec1);

					findBestPath(
						tempVec2.getFX(),
						tempVec2.getFY(),
						tempVec3.getFX(),
						tempVec3.getFY(),
						0,
						curInd,
						true,
						true
					);
				}

			}


		}



		cout << "end find biggest ocean gaps\n";








		mapSwapFlag = 0;
		mapStep = 0.0f;

		fbow2->cpuToGPU();
		singleton->copyFBO("cityFBO", "swapFBO0");
		singleton->bindShader("DilateShader");
		for (i = 0; i < 2; i++)
		{

			singleton->bindFBO("swapFBO", mapSwapFlag);
			singleton->sampleFBO("swapFBO", 0, mapSwapFlag);
			singleton->sampleFBO("hmFBO", 1);
			singleton->setShaderFloat("seaLevel", singleton->getSLNormalized() );
			singleton->setShaderFloat("mapStep", 1.0);
			singleton->setShaderFloat("doDilate", 1.0);
			singleton->setShaderFloat("texPitch", w);
			singleton->drawFSQuad(1.0f);
			singleton->unsampleFBO("hmFBO", 1);
			singleton->unsampleFBO("swapFBO", 0, mapSwapFlag);
			singleton->unbindFBO();

			mapSwapFlag = 1 - mapSwapFlag;
			mapStep += 1.0f;
		}
		singleton->unbindShader();
		singleton->copyFBO("swapFBO0", "cityFBO");
		fbow2->getPixels();
		//fbow2->updateMips();






		//bool notCovered = true;
		int id = 1;
		int totCount;
		int fillColor;
		bool incId;

		cout << "start road regions\n";

		for (i = 0; i < totSize; i++)
		{

			if (fbow2->getPixelAtIndex(i, pathChannel) == 0)
			{



				for (j = 0; j < 2; j++)
				{
					btStack[0] = i;
					btStackInd = 0;
					totCount = 0;

					if (j == 0)
					{
						fillColor = id;
					}
					else
					{
						fillColor = 255;
					}


					while (btStackInd > -1)
					{

						curInd = btStack[btStackInd];
						curY = curInd / w;
						curX = curInd - curY * w;

						if (j == 0)
						{
							fbow2->orPixelAtIndex(curInd, btChannel, visFlag);
						}
						else
						{
							fbow2->andPixelAtIndex(curInd, btChannel, visFlagO );
						}


						fbow2->setPixelAtIndex(curInd, pathChannel, fillColor );


						count = 0;
						notFound = true;



						do
						{
							curDir = count;

							testX = curX + dirModX[curDir];
							testY = curY + dirModY[curDir];
							testInd = fbow2->getIndex(testX, testY);
							testPix = fbow2->getPixelAtIndex(testInd, btChannel);
							testPix2 = fbow2->getPixelAtIndex(testInd, pathChannel);


							if (j == 0)
							{
								if ( ( (testPix & visFlag) == 0 ) && (testPix2 == 0))
								{
									notFound = false;
									totCount++;

								}
							}
							else
							{
								if ( ( (testPix & visFlag) > 0) && (testPix2 == id))
								{
									notFound = false;
									totCount++;
								}
							}




							count++;
						}
						while (notFound && count < 4);

						if (notFound)
						{
							btStackInd--;
						}
						else
						{

							// join the two and remove walls
							//fbow2->andPixelAtIndex(curInd, btChannel, dirFlags[bestDir]);
							//fbow2->andPixelAtIndex(bestInd, btChannel, dirFlagsOp[bestDir]);


							btStackInd++;
							btStack[btStackInd] = testInd;
						}

					}

					incId = false;

					if (j == 0)
					{
						if (totCount < 1000)
						{
							//cout << "Too Small\n";
						}
						else
						{
							incId = true;
							j++;
						}
					}
					else
					{
						incId = true;
					}

					if (incId)
					{
						//cout << "Id: " << id << "\n";
						id++;
						if (id > 254)
						{
							id = 1;
						}
					}
				}




			}

		}


		cout << "end road regions\n";

		// clear visited
		for (k = 0; k < totSize; k++)
		{
			fbow2->andPixelAtIndex(k, btChannel, visFlagO );
		}

		fbow2->cpuToGPU();


		mapSwapFlag = 0;
		mapStep = 0.0f;
		singleton->copyFBO("cityFBO", "swapFBO0");



		singleton->bindShader("SkeletonShader");
		for (k = 0; k < 19; k++)
		{

			singleton->bindFBO("swapFBO", mapSwapFlag);
			singleton->sampleFBO("swapFBO", 0, mapSwapFlag);
			//singleton->sampleFBO("hmFBO",1);
			singleton->setShaderFloat("seaLevel", singleton->getSLNormalized() );
			singleton->setShaderFloat("mapStep", 0.0);
			singleton->setShaderFloat("texPitch", w);
			singleton->drawFSQuad(1.0f);
			//singleton->unsampleFBO("hmFBO",1);
			singleton->unsampleFBO("swapFBO", 0, mapSwapFlag);
			singleton->unbindFBO();
			mapSwapFlag = 1 - mapSwapFlag;
			mapStep += 1.0f;

		}
		singleton->unbindShader();


		singleton->bindShader("RoadShader");
		for (k = 0; k < 1; k++)
		{

			singleton->bindFBO("swapFBO", mapSwapFlag);
			singleton->sampleFBO("swapFBO", 0, mapSwapFlag);
			//singleton->sampleFBO("hmFBO",1);
			singleton->setShaderFloat("seaLevel", singleton->getSLNormalized() );
			singleton->setShaderFloat("mapStep", 0.0);
			singleton->setShaderFloat("texPitch", w);
			singleton->drawFSQuad(1.0f);
			//singleton->unsampleFBO("hmFBO",1);
			singleton->unsampleFBO("swapFBO", 0, mapSwapFlag);
			singleton->unbindFBO();
			mapSwapFlag = 1 - mapSwapFlag;
			mapStep += 1.0f;

		}
		singleton->unbindShader();


		singleton->copyFBO("swapFBO0", "cityFBO");
		fbow2->getPixels();







		// generate streets

		int *streetFlagsV = new int[w]; //runs vertical
		int *streetFlagsH = new int[h]; //runs horizontal

		for (i = 0; i < w; i++)
		{
			streetFlagsV[i] = 0;
		}
		for (i = 0; i < h; i++)
		{
			streetFlagsH[i] = 0;
		}

		// 1 - x+
		// 2 - x-
		// 4 - y+
		// 8 - y-

		for (i = 0; i < w; i += singleton->blockSizeInLots )
		{

			curInd = i - 1;

			while (curInd < 0)
			{
				curInd += w;
			}

			streetFlagsV[curInd] |= 1;
			streetFlagsV[i] |= 2;
		}
		for (i = 0; i < h; i += singleton->blockSizeInLots )
		{

			curInd = i - 1;

			while (curInd < 0)
			{
				curInd += h;
			}

			streetFlagsH[curInd] |= 4;
			streetFlagsH[i] |= 8;
		}












		//add in main streets
		for (k = 0; k < totSize; k++)
		{
			curInd = k;
			curY = curInd / w;
			curX = curInd - curY * w;

			testPix = fbow->getPixelAtIndex(curInd, blockChannel);

			if (testPix != 0)
			{
				fbow2->orPixelAtIndex(curInd, btChannel, streetFlagsH[curY] | streetFlagsV[curX]);
				fbow2->orPixelAtIndex(curInd, stChannel, streetFlagsH[curY] | streetFlagsV[curX]); //stChannel
			}


		}


		// for (k = 0; k < totSize; k++) {

		//  // int stChannel;
		//  // int btChannel;
		//  // int pathChannel;
		//  // int houseChannel;

		//  testPix = fbow2->getPixelAtIndex(k, stChannel);
		//  fbow2->orPixelAtIndex(k, btChannel, testPix );

		//  testPix = fbow2->getPixelAtIndex(k, pathChannel);
		//  fbow2->orPixelAtIndex(k, btChannel, testPix );
		// }


		/*
		for (i = 0; i < numProvinces-1; i++) {
		    for (j = i + 1; j < numProvinces; j++) {
		        if (provinceGrid[i + j*numProvinces] == 1) {

		            k = fbow->numMips-1;

		            cx1 = provinceX[i];
		            cy1 = provinceY[i];
		            cx2 = provinceX[j];
		            cy2 = provinceY[j];

		            while (getMipInd(cx1,cy1,k) == getMipInd(cx2,cy2,k)) {
		                k--;
		            }

		        }
		    }
		}



		// remove any road that touches water or is out of town

		int cityLevel = 0;
		for (k = 0; k < totSize; k++) {
		    curInd = k;
		    curY = curInd/w;
		    curX = curInd-curY*w;

		    touchesWater = false;

		    for (j = -1; j <= 1; j++) {
		        for (i = -1; i <= 1; i++) {
		            testX = curX + i;
		            testY = curY + j;
		            testInd = fbow->getIndex(testX,testY);
		            testPix = fbow->getPixelAtIndex(testInd, hmChannel);


		            if (testPix < seaLevel + 10) {
		                touchesWater = true;
		                break;
		            }

		        }
		        if (touchesWater) {
		            break;
		        }
		    }

		    testPix2 = fbow->getPixelAtIndex(curInd, densityChannel);


		    if (touchesWater) { // || (testPix2 > 120)
		        fbow2->andPixelAtIndex(curInd, btChannel, dirFlagClear);
		        fbow2->andPixelAtIndex(curInd, stChannel, dirFlagClear);

		        //TODO: repair all broken (half) edges
		    }
		    // if (testPix2 > 80) {
		    //  fbow2->andPixelAtIndex(curInd, stChannel, dirFlagClear);
		    // }


		}



		// fix half streets

		for (k = 0; k < totSize; k++) {
		    curInd = k;
		    curY = curInd/w;
		    curX = curInd-curY*w;

		    basePix = fbow2->getPixelAtIndex(curInd, btChannel);
		    basePix2 = fbow2->getPixelAtIndex(curInd, stChannel);

		    for (i = 0; i < 4; i++) {



		        curDir = i;

		        testX = curX + dirModX[curDir];
		        testY = curY + dirModY[curDir];
		        testInd = fbow2->getIndex(testX,testY);
		        testPix = fbow2->getPixelAtIndex(testInd, btChannel);
		        testPix2 = fbow2->getPixelAtIndex(testInd, stChannel);


		        if ( (basePix & dirFlagsO[curDir]) != (testPix & dirFlagsOpO[curDir]) ) {
		            fbow2->orPixelAtIndex(curInd, btChannel, dirFlagsO[curDir]);
		            fbow2->orPixelAtIndex(testInd, btChannel, dirFlagsOpO[curDir]);
		        }

		        if ( (basePix2 & dirFlagsO[curDir]) != (testPix2 & dirFlagsOpO[curDir]) ) {
		            fbow2->orPixelAtIndex(curInd, stChannel, dirFlagsO[curDir]);
		            fbow2->orPixelAtIndex(testInd, stChannel, dirFlagsOpO[curDir]);
		        }

		    }

		}

		*/


















		// ?????




		cout << "start filling houses\n";

		// clear visited
		for (k = 0; k < totSize; k++)
		{
			fbow2->andPixelAtIndex(k, btChannel, visFlagO );
		}

		fbow->updateMips();




		int wb = worldSizeInBlocks.getIX();
		int hb = worldSizeInBlocks.getIY();
		int blockInd;

		for (i = 0; i < wb; i++)
		{
			for (j = 0; j < hb; j++)
			{
				blockInd = i + j * wb;

				testPix = fbow->getMipAtIndex(blockInd, blockMip, blockChannel, MIN_MIP);

				if (testPix != 0)
				{



					id = 1;

					for (k = i * blockMod; k < (i + 1)*blockMod; k++)
					{
						for (m = j * blockMod; m < (j + 1)*blockMod; m++)
						{
							curInd = k + m * w;
							curX = k;
							curY = m;


							testPix = fbow2->getPixelAtIndex(curInd, btChannel);

							if (testPix & visFlag)
							{

							}
							else
							{
								btStack[0] = curInd;
								btStackInd = 0;
								totCount = 0;


								while ( (btStackInd > -1) && (totCount < 3) )
								{

									curInd = btStack[btStackInd];
									curY = curInd / w;
									curX = curInd - curY * w;

									fbow2->orPixelAtIndex(curInd, btChannel, visFlag);
									fbow2->setPixelAtIndex(curInd, houseChannel, id );


									count = 0;
									notFound = true;

									testPix2 = fbow2->getPixelAtIndex(curInd, btChannel);
									//testPix3 = fbow2->getPixelAtIndex(curInd, stChannel);
									testPix4 = fbow2->getPixelAtIndex(curInd, pathChannel);

									do
									{
										curDir = count;

										testX = curX + dirModX[curDir];
										testY = curY + dirModY[curDir];

										testInd = fbow2->getIndex(testX, testY);

										testPix = fbow2->getPixelAtIndex(testInd, btChannel);

										if (
											( (testPix & visFlag) == 0 ) &&
											( (testPix2 & dirFlagsO[curDir]) == 0) &&
											//( (testPix3 & dirFlagsO[curDir]) == 0) &&
											( (testPix4 & dirFlagsO[curDir]) == 0)
										)
										{
											notFound = false;
											totCount++;

										}


										count++;
									}
									while (notFound && count < 4);

									if (notFound)
									{
										btStackInd--;
									}
									else
									{

										// join the two and remove walls
										//fbow2->andPixelAtIndex(curInd, btChannel, dirFlags[bestDir]);
										//fbow2->andPixelAtIndex(bestInd, btChannel, dirFlagsOp[bestDir]);


										btStackInd++;
										btStack[btStackInd] = testInd;
									}

								}

								id++;
								if (id > 254)
								{
									id = 1;
								}




							}


						}
					}

				}

			}
		}


		cout << "end filling houses\n";

		// clear visited
		for (k = 0; k < totSize; k++)
		{
			fbow2->andPixelAtIndex(k, btChannel, visFlagO );
		}



		// ?????










		fbow2->cpuToGPU();

		delete[] btStack;
		delete[] streetFlagsH;
		delete[] streetFlagsV;
		delete[] oceanRes;

		//////////



		singleton->mapInvalid = false;

		singleton->setCameraToElevation();

		cout << "DONE WITH MAP\n";

		mapLockOn = false;

		//popTrace();
	}
void GameWorld::drawMap ()
        {


		//pushTrace("drawMap()");

		FBOWrapper *fbow = singleton->getFBOWrapper("hmFBOLinear", 0);

		
		//singleton->setCameraToElevationBase();


		singleton->bindShader("TopoShader");
		
		singleton->bindFBO("resultFBO0");
		
		singleton->sampleFBO("palFBO", 0);
		singleton->sampleFBO("hmFBO", 1); //Linear
		singleton->sampleFBO("cityFBO", 2);
		singleton->sampleFBO("backFaceMapFBO",3);
		singleton->sampleFBO("frontFaceMapFBO",4);

		
		singleton->setShaderFloat("timeOfDay", singleton->timeOfDay);
		singleton->setShaderfVec4("mapFreqs", &(singleton->mapFreqs) );
		singleton->setShaderfVec4("mapAmps", &(singleton->mapAmps) );
		singleton->setShaderFloat("tiltAmount", singleton->tiltAmount);
		singleton->setShaderFloat("cameraZoom", singleton->cameraZoom);
		singleton->setShaderfVec3("cameraPos", cameraPos);
		singleton->setShaderFloat("mapTrans", mapTrans);
		singleton->setShaderFloat("seaLevel", singleton->getSLNormalized() );
		singleton->setShaderFloat("curTime", singleton->curTime);
		singleton->setShaderVec2("mapDimInPixels", fbow->width, fbow->height);
		singleton->setShaderfVec3("worldSizeInPixels", &(singleton->worldSizeInPixels) );

		// singleton->drawQuadBounds(
		// 	-singleton->worldSizeInPixels.getFX() / 2.0f,// + cameraPos->getFX(),
		// 	-singleton->worldSizeInPixels.getFY() / 2.0f,// + cameraPos->getFY(),
		// 	singleton->worldSizeInPixels.getFX() / 2.0f,// + cameraPos->getFX(),
		// 	singleton->worldSizeInPixels.getFY() / 2.0f,// + cameraPos->getFY(),
		// 	0.0f//cameraPos->getFZ()//singleton->getHeightAtPixelPos(cameraPos->getFX(), cameraPos->getFY()) //0.0f// + cameraPos->getFZ()
		// );

		
		singleton->drawFSQuad(1.0f);

		
		singleton->unsampleFBO("frontFaceMapFBO",4);
		singleton->unsampleFBO("backFaceMapFBO",3);
		singleton->unsampleFBO("cityFBO", 2);
		singleton->unsampleFBO("hmFBO", 1);
		singleton->unsampleFBO("palFBO", 0);
		
		
		singleton->unbindFBO();
		
		singleton->unbindShader();

		
		//singleton->drawFBO("resultFBO", 0, newZoom, 1 - activeFBO);
		
		glEnable(GL_BLEND);
		singleton->drawFBO("resultFBO0",0,1.0f);
		glDisable(GL_BLEND);


		//popTrace();
	}
void GameWorld::doBlur (string fboName)
        {
		int i;
		mapSwapFlag = 0;
		
		singleton->bindShader("BlurShader");
		singleton->setShaderFloat("cameraZoom", singleton->cameraZoom);
		singleton->setShaderFloat("numBlurPixelsPerSide", 4.0); // value of 4 is a 9x9 kernel (4*2+1)
		singleton->setShaderFloat("sigma", 4.0);
		
		for (i = 0; i < 2; i++)
		{
			
			singleton->bindFBO(fboName, mapSwapFlag);
			singleton->sampleFBO(fboName, 0, mapSwapFlag);
			
			if (i == 0) { // horizontal
				singleton->setShaderFloat("blurSize", 1.0f/(singleton->currentFBOResolutionX));
				singleton->setShaderVec2("blurMultiplyVec", 1.0f, 0.0f);
			}
			else { // vertical
				singleton->setShaderFloat("blurSize", 1.0f/(singleton->currentFBOResolutionY));
				singleton->setShaderVec2("blurMultiplyVec", 0.0f, 1.0f);
			}

			
			singleton->drawFSQuad(1.0f);
			
			singleton->unsampleFBO(fboName, 0, mapSwapFlag);
			singleton->unbindFBO();
			

			mapSwapFlag = 1 - mapSwapFlag;

		}
		
		
		singleton->unbindShader();
		
	}
void GameWorld::updateLights ()
        {

		int i;
		int j;
		int k;

		int flag = 1;

		GameLight *tempLight;



		int ii;
		int jj;

		int blockRad = 1;

		lightCount = singleton->numDynLights;
		GameLight *curLight;
		GameBlock *curBlock;

		//activeLights[0] = &globalLight;

		if (singleton->targetTimeOfDay <= 0.5)
		{
			for (j = -blockRad; j <= blockRad; j++)
			{
				for (i = -blockRad; i <= blockRad; i++)
				{
					ii = i + camBlockPos.getIX();
					jj = j + camBlockPos.getIY();

					curBlock = getBlockAtCoords(ii, jj, true);


					for (k = 0; k < curBlock->gameLights.size(); k++)
					{
						curLight = curBlock->gameLights[k];

						// TODO: cache screen coords

						singleton->worldToScreen(&lScreenCoords, &(curLight->pos), true);

						curLight->screenDistance = lScreenCoords.length();

						if ( (curLight->screenDistance < 2.0f ) && (curLight->isOn) )
						{

							// if (lightCount == singleton->numLights) {

							// }

							activeLights[lightCount] = curBlock->gameLights[k];
							lightCount++;
						}

						if (lightCount >= MAX_EVAL_LIGHTS)
						{
							goto UPDATE_LIGHTS_END;
						}

					}
				}
			}

UPDATE_LIGHTS_END:

			for (i = singleton->numDynLights + 1; (i <= lightCount) && flag; i++)
			{
				flag = 0;
				for (j = singleton->numDynLights; j < (lightCount - 1); j++)
				{
					if (activeLights[j + 1]->screenDistance < activeLights[j]->screenDistance) // ascending order simply changes to <
					{
						tempLight = activeLights[j];
						activeLights[j] = activeLights[j + 1];
						activeLights[j + 1] = tempLight;
						flag = 1;
					}
				}
			}

			lightCount = min(lightCount, MAX_LIGHTS);
		}



	}
void GameWorld::postProcess ()
        {

		

		int i;
		int iMin;

		int k;
		int baseInd;

		GameLight *curLight;

		//pushTrace("postProcess()");

		// NOTE: ALWAYS UNSAMPLE IN REVERSE ORDER!!!




		//globalLight.initFrom( singleton->dynObjects[E_OBJ_LIGHT0] );
		//activeLights[0] = &globalLight;

		for (i = 0; i < singleton->numDynLights; i++)
		{
			activeLights[i] = singleton->dynObjects[E_OBJ_LIGHT0 + i]->getLight();
		}


		for (k = 0; k < lightCount; k++)
		{
			baseInd = k * FLOATS_PER_LIGHT;

			// lightPosBase.copyFrom(&(singleton->dynObjects[E_OBJ_LIGHT0 + k]->pos));
			// lightPosBase.addXYZ(
			//  sin(singleton->curTime/1300.0)*4.0f*singleton->pixelsPerMeter,
			//  sin(singleton->curTime/700.0)*4.0f*singleton->pixelsPerMeter,
			//  sin(singleton->curTime/1100.0)*4.0f*singleton->pixelsPerMeter
			// );
			// lightPos = &lightPosBase;

			curLight = activeLights[k];

			lightPos = &(curLight->pos);

			// if (k == 0) {
			//  globLightPos = lightPos;
			// }
			// if (k == 1) {
			//  lightPos->setFXYZ(
			//      cameraPos->getFX()-(globLightPos->getFX() - cameraPos->getFX()),
			//      cameraPos->getFY()-(globLightPos->getFY() - cameraPos->getFY()),
			//      globLightPos->getFZ()
			//  );
			// }

			singleton->worldToScreen(&lScreenCoords, lightPos);

			singleton->lightArr[baseInd + 0] = lightPos->getFX();
			singleton->lightArr[baseInd + 1] = lightPos->getFY();
			singleton->lightArr[baseInd + 2] = lightPos->getFZ();

			// light radius
			if (k == 0)
			{
				// global light
				singleton->lightArr[baseInd + 3] = 4096.0f * singleton->pixelsPerMeter;
			}
			else
			{
				// if (k == 1) {
				//  singleton->lightArr[baseInd + 3] = 4096.0f*singleton->pixelsPerMeter;
				// }
				// else {
				// other lights
				singleton->lightArr[baseInd + 3] = 16.0f * singleton->pixelsPerMeter;
				//}

			}

			singleton->lightArr[baseInd + 4] = lScreenCoords.getFX();
			singleton->lightArr[baseInd + 5] = lScreenCoords.getFY();
			singleton->lightArr[baseInd + 6] = 0.0f;
			singleton->lightArr[baseInd + 7] = 0.0f;


			// light color

			singleton->lightArr[baseInd + 8] = curLight->color.getFX(); // light red
			singleton->lightArr[baseInd + 9] = curLight->color.getFY(); // light green
			singleton->lightArr[baseInd + 10] = curLight->color.getFZ(); // light blue

			switch (k)
			{
			case 0:
				singleton->lightArr[baseInd + 11] = 1.0f; // light intensity (unused?)
				singleton->lightArr[baseInd + 12] = 0.0f; // light colorization (0-1)
				singleton->lightArr[baseInd + 13] = 0.0f; // light flooding (colorizes regardless of shadows) (0-1)
				break;
			default:
				singleton->lightArr[baseInd + 11] = 1.0f;
				singleton->lightArr[baseInd + 12] = 1.0f;
				singleton->lightArr[baseInd + 13] = 0.0f;
				break;

			}


		}

		if ( mapTrans < 1.0 )
		{




			activeFBO = 0;


			if (singleton->waterOn)	{


				singleton->bindShader("WaveHeightShader");
				singleton->bindFBO("waveFBO");
				singleton->sampleFBO("worldSpaceFBO", 4);
				
				singleton->setShaderFloat("tiltAmount", singleton->tiltAmount);
				singleton->setShaderFloat("waveSpacing", singleton->pixelsPerMeter * 2.0f);
				singleton->setShaderVec2("resolution", singleton->currentFBOResolutionX, singleton->currentFBOResolutionY);
				singleton->setShaderfVec3("cameraPos", cameraPos);
				singleton->setShaderFloat("cameraZoom", singleton->cameraZoom);
				singleton->setShaderfVec2("bufferDim", &(singleton->bufferModDim));
				singleton->setShaderFloat("curTime", singleton->curTime);
				singleton->drawFSQuad(1.0f);
				
				
				singleton->unsampleFBO("worldSpaceFBO", 4);
				singleton->unbindFBO();
				singleton->unbindShader();

				iMin = 0;

				singleton->bindShader("WaterShaderCombine");
				singleton->bindFBO("combineFBOWithWater");
				singleton->sampleFBO("combineFBO", 0);
				singleton->sampleFBO("waterFBO", 2);
				singleton->sampleFBO("waveFBO", 4);
				singleton->sampleFBO("worldSpaceFBO", 5);
				
				//singleton->setShaderFloat("maxWaveHeight", singleton->pixelsPerMeter * 2.0f);
				singleton->setShaderFloat("pixelsPerMeter", singleton->pixelsPerMeter);
				singleton->setShaderVec2("resolution", singleton->currentFBOResolutionX, singleton->currentFBOResolutionY);
				singleton->setShaderfVec3("cameraPos", cameraPos);
				singleton->setShaderFloat("cameraZoom", singleton->cameraZoom);
				singleton->setShaderfVec2("bufferDim", &(singleton->bufferModDim));
				singleton->setShaderFloat("curTime", singleton->curTime);
				singleton->setShaderFloat("seaLevel", singleton->getSLInPixels() );
				singleton->drawFSQuad(1.0f);
				
				singleton->unsampleFBO("worldSpaceFBO", 5);
				singleton->unsampleFBO("waveFBO", 4);
				singleton->unsampleFBO("waterFBO", 2);
				singleton->unsampleFBO("combineFBO", 0);
				singleton->unbindFBO();
				singleton->unbindShader();
				
				
				
				// copy waves to new world space fbo
				
				singleton->bindShader("WorldSpaceShader");
				singleton->bindFBO("worldSpaceWavesFBO");
				singleton->sampleFBO("combineFBOWithWater", 0);
				singleton->setShaderInt("iMax", 1);
				singleton->setShaderVec2("resolution", singleton->currentFBOResolutionX, singleton->currentFBOResolutionY);
				singleton->setShaderVec2("mouseCoords", singleton->mouseX, singleton->mouseY);
				singleton->setShaderfVec3("cameraPos", cameraPos);
				singleton->setShaderfVec2("bufferDim", &(singleton->bufferModDim) );
				singleton->setShaderFloat("cameraZoom", singleton->cameraZoom);
				singleton->setShaderFloat("tiltAmount", singleton->tiltAmount);
				singleton->drawFSQuad(1.0f);
				singleton->unsampleFBO("combineFBOWithWater", 0);
				singleton->unbindFBO();
				singleton->unbindShader();
				
				
				
				
			}
			else
			{
				singleton->copyFBO("worldSpaceFBO", "worldSpaceWavesFBO", 3);
				singleton->copyFBO2("combineFBO", "combineFBOWithWater");

				iMin = 1;
			}





			singleton->bindShader("PreLightingShader");

			for (i = iMin; i < 2; i++)
			{
				if (i == 0)
				{
					singleton->bindFBO("swapFBOLinHalf0");
					singleton->sampleFBO("combineFBO", 0);
				}
				else
				{
					
					singleton->bindFBO("resultFBO", activeFBO);
					singleton->sampleFBO("combineFBOWithWater", 0);
				}

				singleton->sampleFBO("palFBO", 2);
				
				
				
				if ((i==1)&&(singleton->waterOn)) {
					singleton->setShaderTexture(3, singleton->getFBOWrapper("worldSpaceWavesFBO",0)->color_tex);
				}
				else {
					//worldSpaceFBO
					singleton->setShaderTexture(3, singleton->getFBOWrapper("worldSpaceFBO",0)->color_tex);
				}
				
				
				
				
				//worldSpaceFBO
				//singleton->setShaderTexture(4, singleton->getFBOWrapper("worldSpaceBlurFBO0",0)->color_tex);
				
				
				singleton->setShaderVec2("resolution", singleton->currentFBOResolutionX, singleton->currentFBOResolutionY); //MUST BE CALLED AFTER FBO IS BOUND
				singleton->setShaderVec2("mouseCoords", singleton->mouseX, singleton->mouseY);
				singleton->setShaderfVec3("cameraPos", cameraPos);
				
				singleton->setShaderInt("gridOn", (int)(singleton->gridOn));
				singleton->setShaderInt("testOn", (int)(singleton->testOn));
				
				singleton->setShaderInt("solidPass",i);
				
				singleton->setShaderFloat("holderMod",singleton->holderMod);
				singleton->setShaderFloat("curTime", singleton->curTime);
				singleton->setShaderFloat("tiltAmount", singleton->tiltAmount);
				singleton->setShaderInt("iNumSteps", singleton->iNumSteps);


				singleton->setShaderArrayfVec4("lightArr", singleton->lightArr, (FLOATS_PER_LIGHT * lightCount) / 4);
				
				singleton->setShaderFloat("pixelsPerMeter", singleton->pixelsPerMeter);
				singleton->setShaderFloat("blockSizeInMeters", singleton->blockSizeInMeters);
				singleton->setShaderFloat("lightCount", lightCount);
				singleton->setShaderFloat("cameraZoom", singleton->cameraZoom);
				singleton->setShaderFloat("timeOfDay", singleton->timeOfDay);
				singleton->setShaderfVec2("bufferDim", &(singleton->bufferModDim));
				singleton->drawFSQuad(1.0f);

				//singleton->setShaderTexture(4,0);
				singleton->setShaderTexture(3,0);
				singleton->unsampleFBO("palFBO", 2);

				if (i == 0)
				{
					singleton->unsampleFBO("combineFBO", 0);
				}
				else
				{
					singleton->unsampleFBO("combineFBOWithWater", 0);
				}

				singleton->unbindFBO();
			}

			singleton->unbindShader();

			activeFBO = 1 - activeFBO;


			if (singleton->waterOn)
			{
				doBlur("swapFBOLinHalf");
				singleton->bindShader("WaterShader");
				singleton->bindFBO("resultFBO", activeFBO);
				singleton->sampleFBO("combineFBO", 0);
				singleton->sampleFBO("combineFBOWithWater", 2);
				singleton->sampleFBO("resultFBO", 4, activeFBO);
				singleton->sampleFBO("swapFBOLinHalf0", 5);
				singleton->sampleFBO("noiseFBO", 6);
				singleton->sampleFBO("waveFBO", 7);
				singleton->sampleFBO("worldSpaceFBO", 8);
				
				singleton->setShaderFloat("tiltAmount", singleton->tiltAmount);
				singleton->setShaderFloat("pixelsPerMeter", singleton->pixelsPerMeter);
				singleton->setShaderFloat("timeOfDay", singleton->timeOfDay);
				singleton->setShaderVec2("resolution", singleton->currentFBOResolutionX, singleton->currentFBOResolutionY);
				singleton->setShaderfVec3("cameraPos", cameraPos);
				singleton->setShaderFloat("cameraZoom", singleton->cameraZoom);
				singleton->setShaderfVec2("bufferDim", &(singleton->bufferModDim));
				singleton->setShaderFloat("curTime", singleton->curTime);
				singleton->setShaderFloat("seaLevel", singleton->getSLInPixels() );
				singleton->drawFSQuad(1.0f);
				
				singleton->unsampleFBO("worldSpaceFBO", 8);
				singleton->unsampleFBO("waveFBO", 7);
				singleton->unsampleFBO("noiseFBO", 6);
				singleton->unsampleFBO("swapFBOLinHalf0", 5);
				singleton->unsampleFBO("resultFBO", 4, activeFBO);
				singleton->unsampleFBO("waterFBO", 2);
				singleton->unsampleFBO("combineFBO", 0);
				singleton->unbindFBO();
				singleton->unbindShader();

				activeFBO = 1 - activeFBO;
			}


			if (singleton->radiosityOn || singleton->fogOn)
			{

				if (activeFBO == 0)
				{
					singleton->copyFBO("resultFBO0", "swapFBOBLin0");
				}
				else
				{
					singleton->copyFBO("resultFBO1", "swapFBOBLin0");
				}


				doBlur("swapFBOBLin");
			}



			if (singleton->radiosityOn)
			{

				singleton->bindShader("RadiosityShader");

				singleton->bindFBO("swapFBOLinHalf0");
				singleton->sampleFBO("combineFBOWithWater", 0);
				singleton->sampleFBO("swapFBOBLin0", 2);
				singleton->sampleFBO("worldSpaceWavesFBO", 4);
				singleton->setShaderFloat("cameraZoom", singleton->cameraZoom);
				singleton->setShaderVec2("resolution", singleton->currentFBOResolutionX, singleton->currentFBOResolutionY); //MUST BE CALLED AFTER FBO IS BOUND
				singleton->setShaderfVec2("bufferDim", &(singleton->bufferModDim));
				singleton->setShaderfVec3("cameraPos", cameraPos);
				singleton->setShaderfVec3("lightPosWS", lightPos);
				singleton->setShaderInt("iNumSteps", singleton->iNumSteps);
				singleton->drawFSQuad(1.0f);
				singleton->unsampleFBO("worldSpaceWavesFBO", 4);
				singleton->unsampleFBO("swapFBOBLin0", 2);
				singleton->unsampleFBO("combineFBOWithWater", 0);
				singleton->unbindFBO();
				singleton->unbindShader();


				doBlur("swapFBOLinHalf");

				singleton->bindShader("RadiosityCombineShader");
				singleton->bindFBO("resultFBO", activeFBO);
				singleton->sampleFBO("resultFBO", 0, activeFBO);
				singleton->sampleFBO("swapFBOLinHalf0", 1);
				singleton->sampleFBO("combineFBOWithWater", 2);
				singleton->setShaderInt("testOn", (int)(singleton->testOn));
				singleton->drawFSQuad(1.0f);
				singleton->unsampleFBO("combineFBOWithWater", 2);
				singleton->unsampleFBO("swapFBOLinHalf0", 1);
				singleton->unsampleFBO("resultFBO", 0, activeFBO);
				singleton->unbindFBO();
				singleton->unbindShader();

				activeFBO = 1 - activeFBO;


			}

			if (singleton->fogOn == 1.0f)
			{
				mapSwapFlag = 0;

				singleton->bindShader("FogShader");



				singleton->bindFBO("resultFBO", activeFBO);

				singleton->sampleFBO("combineFBOWithWater", 0);
				singleton->sampleFBO("resultFBO", 2, activeFBO);
				singleton->sampleFBO("swapFBOBLin0", 3);
				singleton->sampleFBO("worldSpaceFBO", 4);

				// todo: replace with worldSpaceWavesFBO
				
				singleton->setShaderFloat("tiltAmount", singleton->tiltAmount);
				singleton->setShaderFloat("timeOfDay", singleton->timeOfDay);
				singleton->setShaderFloat("cameraZoom", singleton->cameraZoom);
				singleton->setShaderVec2("resolution", singleton->currentFBOResolutionX, singleton->currentFBOResolutionY); //MUST BE CALLED AFTER FBO IS BOUND
				singleton->setShaderfVec2("bufferDim", &(singleton->bufferModDim));
				singleton->setShaderfVec3("cameraPos", cameraPos);
				singleton->setShaderfVec4("fogPos", fogPos);

				singleton->drawFSQuad(1.0f);

				singleton->unsampleFBO("worldSpaceFBO", 4);
				singleton->unsampleFBO("swapFBOBLin0", 3);
				singleton->unsampleFBO("resultFBO", 2, activeFBO);
				singleton->unsampleFBO("combineFBOWithWater", 0);

				singleton->unbindFBO();
				singleton->unbindShader();


				activeFBO = 1 - activeFBO;

			}

			//singleton->drawFBO("swapFBOBLin0", 0, newZoom);
			
			
			//singleton->drawFBO("frontFaceFBO", 0, 1.0f);

			

			// if (singleton->testOn) {
			// 	doBlur("resultFBO");
			// }

			if (singleton->guiOn) {
				if (singleton->mainGUI->isReady) {
					singleton->mainGUI->renderGUI(newZoom, 1 - activeFBO);
				}
				
			}
			else {
				singleton->drawFBO("resultFBO", 0, newZoom, 1 - activeFBO);
			}
			






			// singleton->bindShader("CopyShader");
			// singleton->setShaderTexture(0,singleton->testPat->tid);
			// singleton->drawFSQuad(0.25f);
			// singleton->setShaderTexture(0,0);
			// singleton->unbindShader();





		}


		//popTrace();


	}
GameWorld::~ GameWorld ()
        {

		//threadpool.stopAll();

		int i;
		int j;

	}
#undef LZZ_INLINE
 



Singleton* singleton;


void processSpecialKeys(int key, int x, int y) {
    singleton->processSpecialKeys(key,x,y);
}
void processKey(unsigned char key, int x, int y, bool isPressed) {
    singleton->processKey(key,x,y,isPressed);
}
void keyboardUp(unsigned char key, int x, int y) {
    singleton->keyboardUp(key,x,y);
}
void keyboardDown(unsigned char key, int x, int y) {
    singleton->keyboardDown(key,x,y);
}
void mouseMovementWithButton(int x, int y) {
    singleton->mouseMove(x,y);
}
void mouseMovementWithoutButton(int x, int y) {
    singleton->mouseMove(x,y);
}
void mouseClick(int button, int state, int x, int y) {
    singleton->mouseClick(button,state,x,y);
}

void display(void) {
    singleton->display();
}

void reshape (int w, int h) {
    singleton->reshape(w,h);
}
void idleFunc(void) {
    singleton->display();
}

int MAX_CONSOLE_LINES = 500;

void RedirectIOToConsole()

{
#ifdef WIN32
    int hConHandle;

    long lStdHandle;

    CONSOLE_SCREEN_BUFFER_INFO coninfo;

    FILE *fp;

    // allocate a console for this app

    AllocConsole();

    // set the screen buffer to be big enough to let us scroll text

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),

                               &coninfo);

    coninfo.dwSize.Y = MAX_CONSOLE_LINES;

    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),

                               coninfo.dwSize);

    // redirect unbuffered STDOUT to the console

    lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);

    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

    fp = _fdopen( hConHandle, "w" );

    *stdout = *fp;

    setvbuf( stdout, NULL, _IONBF, 0 );

    // redirect unbuffered STDIN to the console

    lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);

    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

    fp = _fdopen( hConHandle, "r" );

    *stdin = *fp;

    setvbuf( stdin, NULL, _IONBF, 0 );

    // redirect unbuffered STDERR to the console

    lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);

    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

    fp = _fdopen( hConHandle, "w" );

    *stderr = *fp;

    setvbuf( stderr, NULL, _IONBF, 0 );

#endif

    std::ios::sync_with_stdio();

}



#ifdef USE_POCO
WebSocketServer myWebsocketServer;
#endif



int main(int argc, char* argv[])
{

    int winWidth;
    int winHeight;
    int scaleFactor;
    
    winWidth = DEF_WIN_W;
    winHeight = DEF_WIN_H;
    scaleFactor = DEF_SCALE_FACTOR;

    RedirectIOToConsole();

    glutInit(&argc, argv);


    //glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  //GLUT_SINGLE

    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB); //|GLUT_MULTISAMPLE
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(250, 50);
    glutCreateWindow("VoxelQuest");

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        doTrace("There was an error with GLEW");
    }
    else {
        doTrace("GLEW_OK");
    }

    
    ////////////
    singleton = new Singleton();
    singleton->init(
        winWidth,
        winHeight,
        scaleFactor
        #ifdef USE_POCO
        ,&myWebsocketServer
        #endif
        
    );
    

    glutDisplayFunc(display);
    glutIdleFunc(idleFunc);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(mouseMovementWithoutButton);
    glutMotionFunc(mouseMovementWithButton);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(processSpecialKeys);
    
    #ifdef USE_POCO
        myWebsocketServer.run(argc, argv);
    #else
        glutMainLoop();    
    #endif
    

    


    

    return 0;
}
 

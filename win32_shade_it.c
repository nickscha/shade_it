/* win32_shade_it.c - v0.4 - public domain data structures - nickscha 2026

A C89 standard compliant, single header, nostdlib (no C Standard Library) OpenGL Shader Playground (SHADE_IT).

LICENSE

  Placed in the public domain and also MIT licensed.
  See end of file for detailed license information.

*/

/* #############################################################################
 * # TYPES & COMPILER SETTINGS
 * #############################################################################
 */
#if __STDC_VERSION__ >= 199901L
#define SHADE_IT_INLINE inline
typedef long long i64;
typedef unsigned long long u64;
#elif defined(__GNUC__) || defined(__clang__)
#define SHADE_IT_INLINE __inline__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wlong-long"
typedef long long i64;
typedef unsigned long long u64;
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#define SHADE_IT_INLINE __inline
typedef __int64 i64;
typedef unsigned __int64 u64;
#else
#define SHADE_IT_INLINE
typedef long i64;
typedef unsigned long u64;
#endif

#define SHADE_IT_API static

typedef char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int i32;
typedef float f32;
typedef double f64;

#define TYPES_STATIC_ASSERT(c, m) typedef char types_assert_##m[(c) ? 1 : -1]
TYPES_STATIC_ASSERT(sizeof(s8) == 1, s8_size_must_be_1);
TYPES_STATIC_ASSERT(sizeof(u8) == 1, u8_size_must_be_1);
TYPES_STATIC_ASSERT(sizeof(u16) == 2, u16_size_must_be_2);
TYPES_STATIC_ASSERT(sizeof(u32) == 4, u32_size_must_be_4);
TYPES_STATIC_ASSERT(sizeof(i32) == 4, i32_size_must_be_4);
TYPES_STATIC_ASSERT(sizeof(f32) == 4, f32_size_must_be_4);
TYPES_STATIC_ASSERT(sizeof(f64) == 8, f64_size_must_be_8);
TYPES_STATIC_ASSERT(sizeof(u64) == 8, u64_size_must_be_8);
TYPES_STATIC_ASSERT(sizeof(i64) == 8, i64_size_must_be_8);

/* #############################################################################
 * # Force Discrete GPU
 * #############################################################################
 */
__declspec(dllexport) u32 NvOptimusEnablement = 0x00000001;         /* NVIDIA Force discrete GPU */
__declspec(dllexport) i32 AmdPowerXpressRequestHighPerformance = 1; /* AMD Force discrete GPU    */

/* #############################################################################
 * # Win32 "windows.h" subsitution for fast builds
 * #############################################################################
 */
#define WIN32_API(r) __declspec(dllimport) r __stdcall

#define STD_OUTPUT_HANDLE ((u32) - 11)
#define INVALID_FILE_SIZE ((u32)0xFFFFFFFF)
#define INVALID_HANDLE ((void *)-1)
#define GENERIC_READ (0x80000000L)
#define FILE_SHARE_READ 0x00000001
#define FILE_SHARE_WRITE 0x00000002
#define FILE_SHARE_DELETE 0x00000004
#define OPEN_EXISTING 3
#define FILE_ATTRIBUTE_NORMAL 0x00000080
#define FILE_FLAG_SEQUENTIAL_SCAN 0x08000000

#define MEM_COMMIT 0x00001000
#define MEM_RESERVE 0x00002000
#define MEM_RELEASE 0x00008000
#define PAGE_READWRITE 0x04

#define WM_ERASEBKGND 0x0014
#define WM_CREATE 0x0001
#define WM_CLOSE 0x0010
#define WM_QUIT 0x0012
#define WM_SIZE 0x0005

#define SIZE_MINIMIZED 1

#define CS_OWNDC 0x0020

#define WS_CLIPSIBLINGS 0x04000000
#define WS_CLIPCHILDREN 0x02000000
#define WS_THICKFRAME 0x00040000L
#define WS_MINIMIZEBOX 0x00020000L
#define WS_MAXIMIZEBOX 0x00010000L
#define WS_CAPTION 0x00C00000L
#define WS_SYSMENU 0x00080000L

#define SW_SHOW 5

#define GWLP_USERDATA -21

#define PM_REMOVE 0x0001

#define PFD_DOUBLEBUFFER 0x00000001
#define PFD_SUPPORT_OPENGL 0x00000020
#define PFD_DRAW_TO_WINDOW 0x00000004
#define PFD_TYPE_RGBA 0

#define LOWORD(l) ((u16)(((u64)(l)) & 0xffff))
#define HIWORD(l) ((u16)((((u64)(l)) >> 16) & 0xffff))
#define MAKEINTRESOURCEA(i) ((s8 *)((u32)((u16)(i))))
#define IDC_ARROW MAKEINTRESOURCEA(32512)

typedef void *(*PROC)(void);
typedef i64 (*WNDPROC)(void *, u32, u64, i64);

typedef struct tagCREATESTRUCTA
{
  void *lpCreateParams;
  void *hInstance;
  void *hMenu;
  void *hwndParent;
  i32 cy;
  i32 cx;
  i32 y;
  i32 x;
  i32 style;
  s8 *lpszName;
  s8 *lpszClass;
  u32 dwExStyle;
} CREATESTRUCTA, *LPCREATESTRUCTA;

typedef struct WNDCLASSA
{
  u32 style;
  WNDPROC lpfnWndProc;
  i32 cbClsExtra;
  i32 cbWndExtra;
  void *hInstance;
  void *hIcon;
  void *hCursor;
  void *hbrBackground;
  s8 *lpszMenuName;
  s8 *lpszClassName;
} WNDCLASSA;

typedef struct tagPOINT
{
  i32 x;
  i32 y;
} POINT;

typedef struct tagRECT
{
  i32 left;
  i32 top;
  i32 right;
  i32 bottom;
} RECT, *PRECT, *LPRECT;

typedef struct tagMSG
{
  void *hwnd;
  u32 message;
  u64 wParam;
  i64 lParam;
  u32 time;
  POINT pt;
  u32 lPrivate;
} MSG, *LPMSG;

typedef struct tagPIXELFORMATDESCRIPTOR
{
  u16 nSize;
  u16 nVersion;
  u32 dwFlags;
  u8 iPixelType;
  u8 cColorBits;
  u8 cRedBits;
  u8 cRedShift;
  u8 cGreenBits;
  u8 cGreenShift;
  u8 cBlueBits;
  u8 cBlueShift;
  u8 cAlphaBits;
  u8 cAlphaShift;
  u8 cAccumBits;
  u8 cAccumRedBits;
  u8 cAccumGreenBits;
  u8 cAccumBlueBits;
  u8 cAccumAlphaBits;
  u8 cDepthBits;
  u8 cStencilBits;
  u8 cAuxBuffers;
  u8 iLayerType;
  u8 bReserved;
  u32 dwLayerMask;
  u32 dwVisibleMask;
  u32 dwDamageMask;
} PIXELFORMATDESCRIPTOR, *LPPIXELFORMATDESCRIPTOR;

typedef struct LARGE_INTEGER
{
  i64 QuadPart;

} LARGE_INTEGER;

typedef struct FILETIME
{
  u32 dwLowDateTime;
  u32 dwHighDateTime;
} FILETIME;

typedef struct WIN32_FILE_ATTRIBUTE_DATA
{
  u32 dwFileAttributes;
  FILETIME ftCreationTime;
  FILETIME ftLastAccessTime;
  FILETIME ftLastWriteTime;
  u32 nFileSizeHigh;
  u32 nFileSizeLow;
} WIN32_FILE_ATTRIBUTE_DATA;

typedef enum GET_FILEEX_INFO_LEVELS
{
  GetFileExInfoStandard,
  GetFileExMaxInfoLevel
} GET_FILEEX_INFO_LEVELS;

WIN32_API(void *)
GetStdHandle(u32 nStdHandle);

WIN32_API(i32)
CloseHandle(void *hObject);

WIN32_API(void *)
VirtualAlloc(void *lpAddress, u32 dwSize, u32 flAllocationType, u32 flProtect);

WIN32_API(i32)
VirtualFree(void *lpAddress, u32 dwSize, u32 dwFreeType);

WIN32_API(void *)
CreateFileA(s8 *lpFileName, u32 dwDesiredAccess, u32 dwShareMode, void *, u32 dwCreationDisposition, u32 dwFlagsAndAttributes, void *hTemplateFile);

WIN32_API(u32)
GetFileSize(void *hFile, u32 *lpFileSizeHigh);

WIN32_API(i32)
ReadFile(void *hFile, void *lpBuffer, u32 nNumberOfBytesToRead, u32 *lpNumberOfBytesRead, void *lpOverlapped);

WIN32_API(i32)
WriteFile(void *hFile, void *lpBuffer, u32 nNumberOfBytesToWrite, u32 *lpNumberOfBytesWritten, void *lpOverlapped);

WIN32_API(i32)
CompareFileTime(FILETIME *lpFileTime1, FILETIME *lpFileTime2);

WIN32_API(i32)
GetFileAttributesExA(s8 *lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, void *lpFileInformation);

WIN32_API(void)
Sleep(u32 dwMilliseconds);

WIN32_API(void)
ExitProcess(u32 uExitCode);

WIN32_API(i32)
PeekMessageA(LPMSG lpMsg, void *hWnd, u32 wMsgFilterMin, u32 wMsgFilterMax, u32 wRemoveMsg);

WIN32_API(i32)
GetMessageA(LPMSG lpMsg, void *hWnd, u32 wMsgFilterMin, u32 wMsgFilterMax);

WIN32_API(i32)
TranslateMessage(MSG *lpMsg);

WIN32_API(i64)
DispatchMessageA(MSG *lpMsg);

WIN32_API(i64)
DefWindowProcA(void *hWnd, u32 Msg, u64 wParam, i64 lParam);

WIN32_API(i64)
SetWindowLongPtrA(void *hWnd, i32 nIndex, i64 dwNewLong);

WIN32_API(i64)
GetWindowLongPtrA(void *hWnd, i32 nIndex);

WIN32_API(void *)
GetModuleHandleA(s8 *lpModuleName);

WIN32_API(void *)
LoadCursorA(void *hInstance, s8 *lpCursorName);

WIN32_API(u16)
RegisterClassA(WNDCLASSA *lpWndClass);

WIN32_API(void *)
CreateWindowExA(u32 dwExStyle, s8 *lpClassName, s8 *lpWindowName, u32 dwStyle, i32 X, i32 Y, i32 nWidth, i32 nHeight, void *hWndParent, void *hMenu, void *hInstance, void *lpParam);

WIN32_API(void *)
GetDC(void *hWnd);

WIN32_API(i32)
ReleaseDC(void *hWnd, void *hDC);

WIN32_API(i32)
SwapBuffers(void *unnamedParam1);

WIN32_API(i32)
ChoosePixelFormat(void *hdc, PIXELFORMATDESCRIPTOR *ppfd);

WIN32_API(i32)
SetPixelFormat(void *hdc, i32 format, PIXELFORMATDESCRIPTOR *ppfd);

WIN32_API(i32)
DescribePixelFormat(void *hdc, i32 iPixelFormat, u32 nBytes, LPPIXELFORMATDESCRIPTOR ppfd);

WIN32_API(i32)
ShowWindow(void *hWnd, i32 nCmdShow);

WIN32_API(i32)
DestroyWindow(void *hWnd);

WIN32_API(i32)
AdjustWindowRect(LPRECT lpRect, u32 dwStyle, i32 bMenu);

WIN32_API(i32)
QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount);

WIN32_API(i32)
QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency);

WIN32_API(s8 *)
GetCommandLineA(void);

/* WGL */
WIN32_API(void *)
wglCreateContext(void *unnamedParam1);

WIN32_API(void *)
wglGetCurrentContext(void);

WIN32_API(void *)
wglGetCurrentDC(void);

WIN32_API(i32)
wglDeleteContext(void *unnamedParam1);

WIN32_API(i32)
wglMakeCurrent(void *unnamedParam1, void *unnamedParam2);

WIN32_API(PROC)
wglGetProcAddress(s8 *unnamedParam1);

/* OpenGL functions provided by win32 */
WIN32_API(void)
glClearColor(f32 red, f32 green, f32 blue, f32 alpha);

WIN32_API(void)
glClear(u32 mask);

WIN32_API(void)
glViewport(i32 x, i32 y, i32 width, i32 height);

WIN32_API(void)
glEnable(u32 cap);

WIN32_API(void)
glDisable(u32 cap);

WIN32_API(u8 *)
glGetString(u32 name);

/* #############################################################################
 * # OpenGL Functions not automatically provided by win32 opengl32
 * # Needs to be loaded during runtime
 * #############################################################################
 */
#define WGL_DRAW_TO_WINDOW_ARB 0x2001
#define WGL_SUPPORT_OPENGL_ARB 0x2010
#define WGL_DOUBLE_BUFFER_ARB 0x2011
#define WGL_PIXEL_TYPE_ARB 0x2013
#define WGL_TYPE_RGBA_ARB 0x202B
#define WGL_ACCELERATION_ARB 0x2003
#define WGL_FULL_ACCELERATION_ARB 0x2027
#define WGL_COLOR_BITS_ARB 0x2014
#define WGL_ALPHA_BITS_ARB 0x201B
#define WGL_DEPTH_BITS_ARB 0x2022
#define WGL_STENCIL_BITS_ARB 0x2023
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#define WGL_CONTEXT_FLAGS_ARB 0x2094
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x00000002

typedef i32 (*PFNWGLCHOOSEPIXELFORMATARBPROC)(void *hdc, i32 *piAttribIList, f32 *pfAttribFList, u32 nMaxFormats, i32 *piFormats, u32 *nNumFormats);
static PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;

typedef void *(*PFNWGLCREATECONTEXTATTRIBSARBPROC)(void *hDC, void *hShareContext, i32 *attribList);
static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

typedef i32 (*PFNWGLSWAPINTERVALEXTPROC)(i32 interval);
static PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;

/* OpenGL functions directly part of opengl32 lib */
#define GL_TRUE 1
#define GL_TRIANGLES 0x0004
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_FRAMEBUFFER_SRGB 0x8DB9
#define GL_MULTISAMPLE 0x809D
#define GL_COMPILE_STATUS 0x8B81
#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_LINK_STATUS 0x8B82
#define GL_VENDOR 0x1F00
#define GL_RENDERER 0x1F01
#define GL_VERSION 0x1F02

typedef u32 (*PFNGLCREATESHADERPROC)(u32 shaderType);
static PFNGLCREATESHADERPROC glCreateShader;

typedef u32 (*PFNGLCREATEPROGRAMPROC)(void);
static PFNGLCREATEPROGRAMPROC glCreateProgram;

typedef void (*PFNGLDELETEPROGRAMPROC)(u32 program);
static PFNGLDELETEPROGRAMPROC glDeleteProgram;

typedef void (*PFNGLATTACHSHADERPROC)(u32 program, u32 shader);
static PFNGLATTACHSHADERPROC glAttachShader;

typedef void (*PFNGLSHADERSOURCEPROC)(u32 shader, i32 count, s8 **string, i32 *length);
static PFNGLSHADERSOURCEPROC glShaderSource;

typedef void (*PFNGLCOMPILESHADERPROC)(u32 shader);
static PFNGLCOMPILESHADERPROC glCompileShader;

typedef void (*PFNGLGETSHADERIVPROC)(u32 shader, u32 pname, i32 *params);
static PFNGLGETSHADERIVPROC glGetShaderiv;

typedef void (*PFNGLGETSHADERINFOLOGPROC)(u32 shader, i32 maxLength, i32 *length, s8 *infoLog);
static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

typedef void (*PFNGLLINKPROGRAMPROC)(u32 program);
static PFNGLLINKPROGRAMPROC glLinkProgram;

typedef void (*PFNGLGETPROGRAMIVPROC)(u32 program, u32 pname, i32 *params);
static PFNGLGETPROGRAMIVPROC glGetProgramiv;

typedef void (*PFNGLGETPROGRAMINFOLOGPROC)(u32 program, i32 maxLength, i32 *length, s8 *infoLog);
static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;

typedef void (*PFNGLDELETESHADERPROC)(u32 shader);
static PFNGLDELETESHADERPROC glDeleteShader;

typedef void (*PFNGLDRAWARRAYSPROC)(u32 mode, i32 first, i32 count);
static PFNGLDRAWARRAYSPROC glDrawArrays;

typedef void (*PFNGLUSEPROGRAMPROC)(u32 program);
static PFNGLUSEPROGRAMPROC glUseProgram;

typedef void (*PFNGLGENVERTEXARRAYSPROC)(i32 n, u32 *arrays);
static PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;

typedef void (*PFNGLBINDVERTEXARRAYPROC)(u32 array);
static PFNGLBINDVERTEXARRAYPROC glBindVertexArray;

typedef i32 (*PFNGLGETUNIFORMLOCATIONPROC)(u32 program, s8 *name);
static PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;

typedef void (*PFNGLUNIFORM1FPROC)(i32 location, f32 v0);
static PFNGLUNIFORM1FPROC glUniform1f;

typedef void (*PFNGLUNIFORM1IPROC)(i32 location, i32 v0);
static PFNGLUNIFORM1IPROC glUniform1i;

typedef void (*PFNGLUNIFORM3FPROC)(i32 location, f32 v0, f32 v1, f32 v2);
static PFNGLUNIFORM3FPROC glUniform3f;

/* #############################################################################
 * # Main Code
 * #############################################################################
 */
SHADE_IT_API void win32_print(s8 *str)
{
  static u32 written;
  static void *stdout_handle;

  if (!stdout_handle)
  {
    stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
  }

  {
    s8 *p = str;
    u32 len = 0;

    while (*p++)
    {
      len++;
    }

    WriteFile(stdout_handle, str, len, &written, 0);
  }
}

SHADE_IT_API u8 *win32_file_read(s8 *filename, u32 *file_size_out)
{
  void *hFile = INVALID_HANDLE;
  u32 fileSize = 0;
  u32 bytesRead = 0;

  u8 *buffer = 0;
  i32 attempt;

  /* Retry loop for hot-reload: file might be locked or partially written */
  for (attempt = 0; attempt < 4; ++attempt)
  {
    hFile = CreateFileA(
        filename,
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, /* Hot-reload safe */
        0,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
        0);

    if (hFile != INVALID_HANDLE)
    {
      break;
    }

    Sleep(5); /* Small delay, adjust as needed */
  }

  if (hFile == INVALID_HANDLE)
  {
    return (void *)0;
  }

  fileSize = GetFileSize(hFile, 0);

  if (fileSize == INVALID_FILE_SIZE || fileSize == 0)
  {
    CloseHandle(hFile);
    return (void *)0;
  }

  buffer = (u8 *)VirtualAlloc(0, fileSize + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

  if (!buffer)
  {
    CloseHandle(hFile);
    return (void *)0;
  }

  if (!ReadFile(hFile, buffer, fileSize, &bytesRead, 0) || bytesRead != fileSize)
  {
    VirtualFree(buffer, 0, MEM_RELEASE);
    CloseHandle(hFile);
    return (void *)0;
  }

  buffer[fileSize] = '\0';

  *file_size_out = fileSize;
  CloseHandle(hFile);
  return buffer;
}

SHADE_IT_API SHADE_IT_INLINE FILETIME win32_file_mod_time(s8 *file)
{
  static FILETIME empty = {0, 0};
  WIN32_FILE_ATTRIBUTE_DATA fad;
  return GetFileAttributesExA(file, GetFileExInfoStandard, &fad) ? fad.ftLastWriteTime : empty;
}

typedef struct win32_shade_it_state
{

  u32 window_width;
  u32 window_height;

  f32 window_clear_color_g;
  f32 window_clear_color_b;
  f32 window_clear_color_r;
  f32 window_clear_color_a;

  i32 iFrame;     /* Frames processed count               */
  f64 iTime;      /* Total elapsed time in seconds        */
  f64 iTimeDelta; /* Current render frame time in seconds */
  f64 iFrameRate; /* Frame Rate per second                */

  u8 running;
  u8 minimized;

  void *window_handle;
  void *dc;

} win32_shade_it_state;

SHADE_IT_API SHADE_IT_INLINE i64 win32_window_callback(void *window, u32 message, u64 wParam, i64 lParam)
{
  win32_shade_it_state *state = (win32_shade_it_state *)GetWindowLongPtrA(window, GWLP_USERDATA);

  i64 result = 0;

  switch (message)
  {
  case WM_ERASEBKGND:
    return 1;
  case WM_CREATE:
  {
    CREATESTRUCTA *cs = (CREATESTRUCTA *)lParam;
    state = (win32_shade_it_state *)cs->lpCreateParams;
    SetWindowLongPtrA(window, GWLP_USERDATA, (i64)state);
  }
  break;
  case WM_CLOSE:
  {
    if (!state)
    {
      break;
    }

    state->running = 0;
  }
  break;
  case WM_SIZE:
  {
    if (!state)
    {
      break;
    }

    if (wParam == SIZE_MINIMIZED)
    {
      state->minimized = 1;
    }
    else
    {
      state->minimized = 0;
      state->window_width = LOWORD(lParam);
      state->window_height = HIWORD(lParam);
      glViewport(0, 0, (i32)state->window_width, (i32)state->window_height);
    }
  }
  break;
  default:
  {
    result = DefWindowProcA(window, message, wParam, lParam);
  }
  break;
  }

  return (result);
}

SHADE_IT_API i32 opengl_shader_compile(
    s8 *shaderCode,
    u32 shaderType)
{
  u32 shaderId = glCreateShader(shaderType);
  i32 success;

  glShaderSource(shaderId, 1, &shaderCode, 0);
  glCompileShader(shaderId);
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

  if (!success)
  {
    char infoLog[1024];
    glGetShaderInfoLog(shaderId, 1024, 0, infoLog);

    win32_print("[opengl] shader compilation error:\n");
    win32_print(infoLog);
    win32_print("\n");

    return -1;
  }

  return (i32)shaderId;
}

SHADE_IT_API i32 opengl_shader_create(
    u32 *shader_program,
    s8 *shader_vertex_code,
    s8 *shader_fragment_code)
{
  i32 vertex_shader_id;
  i32 fragment_shader_id;
  i32 success;

  vertex_shader_id = opengl_shader_compile(shader_vertex_code, GL_VERTEX_SHADER);

  if (vertex_shader_id == -1)
  {
    return 0;
  }

  fragment_shader_id = opengl_shader_compile(shader_fragment_code, GL_FRAGMENT_SHADER);

  if (vertex_shader_id == -1)
  {
    return 0;
  }

  *shader_program = glCreateProgram();
  glAttachShader(*shader_program, (u32)vertex_shader_id);
  glAttachShader(*shader_program, (u32)fragment_shader_id);
  glLinkProgram(*shader_program);
  glGetProgramiv(*shader_program, GL_LINK_STATUS, &success);
  glDeleteShader((u32)vertex_shader_id);
  glDeleteShader((u32)fragment_shader_id);

  if (!success)
  {
    char infoLog[1024];
    glGetProgramInfoLog(*shader_program, 1024, 0, infoLog);

    win32_print("[opengl] program creation error:\n");
    win32_print(infoLog);
    win32_print("\n");

    return 0;
  }

  return 1;
}

typedef struct shader
{
  u32 created;
  u32 program;

  i32 loc_iResolution;
  i32 loc_iTime;
  i32 loc_iTimeDelta;
  i32 loc_iFrame;
  i32 loc_iFrameRate;

} shader;

SHADE_IT_API void opengl_shader_load(shader *shader, s8 *shader_file_name)
{
  static s8 *shader_code_vertex =
      "#version 330 core\n"
      "\n"
      " vec2 positions[3] = vec2[3](\n"
      "  vec2(-1.0, -1.0),\n"
      "  vec2( 3.0, -1.0),\n"
      "  vec2(-1.0,  3.0)\n"
      ");\n"
      "\n"
      "void main()\n"
      "{\n"
      "  gl_Position = vec4(positions[gl_VertexID], 0.0, 1.0);\n"
      "}\n";

  u32 size = 0;
  u8 *src = win32_file_read(shader_file_name, &size);
  u32 new_program = 0;

  if (!src || size < 1)
  {
    return;
  }

  if (opengl_shader_create(&new_program, shader_code_vertex, (s8 *)src))
  {
    if (shader->created)
    {
      glDeleteProgram(shader->program);
    }

    shader->program = new_program;

    glUseProgram(shader->program);

    shader->loc_iResolution = glGetUniformLocation(shader->program, "iResolution");
    shader->loc_iTime = glGetUniformLocation(shader->program, "iTime");
    shader->loc_iTimeDelta = glGetUniformLocation(shader->program, "iTimeDelta");
    shader->loc_iFrame = glGetUniformLocation(shader->program, "iFrame");
    shader->loc_iFrameRate = glGetUniformLocation(shader->program, "iFrameRate");

    shader->created = 1;

    win32_print("[opengl] fragment shader loaded\n");
  }
  else
  {
    win32_print("[opengl] compile failed, keeping old shader\n");
  }

  VirtualFree(src, 0, MEM_RELEASE);
}

SHADE_IT_API i32 start(i32 argc, u8 **argv)
{
  /* Default fragment shader file name to load if no file is passed as an argument in cli */
  s8 *fragment_shader_file_name = "shade_it.fs";

  win32_shade_it_state state = {0};
  shader main_shader = {0};

  if (argv && argc > 1)
  {
    fragment_shader_file_name = (s8 *)argv[1];
  }

  win32_print("[opengl] load shader file: ");
  win32_print(fragment_shader_file_name);
  win32_print("\n");

  state.running = 1;
  state.window_width = 800;
  state.window_height = 600;
  state.window_clear_color_r = 0.5f;
  state.window_handle = 0;
  state.dc = 0;

  /******************************/
  /* Window and OpenGL context  */
  /******************************/
  {
    void *instance = GetModuleHandleA(0);
    WNDCLASSA windowClass = {0};

    void *fakeWND;
    void *fakeDC;
    i32 fakePFDID;
    void *fakeRC;

    u32 windowStyle;

    PIXELFORMATDESCRIPTOR fakePFD = {0};
    RECT rect = {0};

    i32 pixelAttribs[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_ALPHA_BITS_ARB, 8,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        0};

    i32 contextAttribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0};

    windowClass.style = CS_OWNDC;
    windowClass.lpfnWndProc = win32_window_callback;
    windowClass.hInstance = instance;
    windowClass.hCursor = LoadCursorA(0, IDC_ARROW);
    windowClass.hbrBackground = 0;
    windowClass.lpszClassName = "shade_it v0.4";

    if (!RegisterClassA(&windowClass))
    {
      return 1;
    }

    fakeWND = CreateWindowExA(
        0,
        windowClass.lpszClassName,
        windowClass.lpszClassName,
        WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
        0, 0,
        1, 1,
        0, 0,
        instance, 0);

    if (!fakeWND)
    {
      return 1;
    }

    fakeDC = GetDC(fakeWND);

    fakePFD.nSize = sizeof(fakePFD);
    fakePFD.nVersion = 1;
    fakePFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    fakePFD.iPixelType = PFD_TYPE_RGBA;
    fakePFD.cColorBits = 32;
    fakePFD.cAlphaBits = 8;
    fakePFD.cDepthBits = 24;

    fakePFDID = ChoosePixelFormat(fakeDC, &fakePFD);

    if (!fakePFDID || !SetPixelFormat(fakeDC, fakePFDID, &fakePFD))
    {
      return 1;
    }

    fakeRC = wglCreateContext(fakeDC);

    if (!fakeRC || !wglMakeCurrent(fakeDC, fakeRC))
    {
      return 1;
    }

    windowStyle = WS_CAPTION | WS_SYSMENU | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME;

    rect.right = (i32)state.window_width;
    rect.bottom = (i32)state.window_height;
    AdjustWindowRect(&rect, windowStyle, 0);

    state.window_handle = CreateWindowExA(
        0,
        windowClass.lpszClassName,
        windowClass.lpszClassName,
        windowStyle,
        0, 0,
        (i32)state.window_width, (i32)state.window_height,
        0, 0,
        instance,
        &state /* Pass pointer to user data to the window callback */
    );

    state.dc = GetDC(state.window_handle);

#ifdef _MSC_VER
#pragma warning(disable : 4068)
#endif
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
    /* Core WGL functions */
    wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
    wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
    wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

    if (!wglChoosePixelFormatARB || !wglCreateContextAttribsARB)
    {
      win32_print("[opengl] required WGL extensions 'wglChoosePixelFormatARB', 'wglCreateContextAttribsARB' missing!\n");
      return 1;
    }

    /* OpenGL functions that are not part of the opengl32 lib */
    glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
    glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
    glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
    glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
    glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
    glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
    glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
    glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
    glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
    glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
    glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
    glDrawArrays = (PFNGLDRAWARRAYSPROC)wglGetProcAddress("glDrawArrays");
    glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
    glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
    glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
    glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
    glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
    glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
    glUniform3f = (PFNGLUNIFORM3FPROC)wglGetProcAddress("glUniform3f");

#pragma GCC diagnostic pop

    /* Set Pixel Format */
    {
      i32 pixelFormatID;
      u32 numFormats;

      if (!wglChoosePixelFormatARB(state.dc, pixelAttribs, 0, 1, &pixelFormatID, &numFormats) || !numFormats)
      {
        return 1;
      }

      SetPixelFormat(state.dc, pixelFormatID, 0);
    }

    /* Create the OpenGL context */
    {
      void *rc = wglCreateContextAttribsARB(state.dc, 0, contextAttribs);

      wglMakeCurrent(0, 0);
      wglDeleteContext(fakeRC);
      ReleaseDC(fakeWND, fakeDC);
      DestroyWindow(fakeWND);

      if (!rc || !wglMakeCurrent(state.dc, rc))
      {
        return 1;
      }
    }

    /* Disable VSync */
    if (wglSwapIntervalEXT)
    {
      wglSwapIntervalEXT(0);
    }

    /* Avoid clear color flickering */
    glClearColor(state.window_clear_color_r, state.window_clear_color_g, state.window_clear_color_b, state.window_clear_color_a);
    glClear(GL_COLOR_BUFFER_BIT);
    SwapBuffers(state.dc);

    /* Make the window visible */
    ShowWindow(state.window_handle, SW_SHOW);
    glDisable(GL_FRAMEBUFFER_SRGB);
    glDisable(GL_MULTISAMPLE);
    glViewport(0, 0, (i32)state.window_width, (i32)state.window_height);

    /* Generate a dummy vao with no buffer */
    {
      u32 vao;
      glGenVertexArrays(1, &vao);
      glBindVertexArray(vao);

      /* TODO: check failures */
      opengl_shader_load(&main_shader, fragment_shader_file_name);
    }

    /* Print opengl information */
    {
      s8 *vendor = (s8 *)glGetString(GL_VENDOR);
      s8 *renderer = (s8 *)glGetString(GL_RENDERER);
      s8 *version = (s8 *)glGetString(GL_VERSION);

      win32_print("[opengl] vendor  : ");
      win32_print(vendor);
      win32_print("\n");

      win32_print("[opengl] renderer: ");
      win32_print(renderer);
      win32_print("\n");

      win32_print("[opengl] version : ");
      win32_print(version);
      win32_print("\n");
    }
  }

  {
    LARGE_INTEGER perf_freq;
    LARGE_INTEGER time_start;
    LARGE_INTEGER time_start_fps_cap;
    LARGE_INTEGER time_last;

    FILETIME fs_last = win32_file_mod_time(fragment_shader_file_name);

    QueryPerformanceFrequency(&perf_freq);
    QueryPerformanceCounter(&time_start);
    QueryPerformanceCounter(&time_start_fps_cap);

    time_last = time_start;

    while (state.running)
    {
      /******************************/
      /* Timing                     */
      /******************************/
      {
        LARGE_INTEGER time_now;
        QueryPerformanceCounter(&time_now);

        state.iTimeDelta = (f64)(time_now.QuadPart - time_last.QuadPart) / (f64)perf_freq.QuadPart;
        state.iTime = (f64)(time_now.QuadPart - time_start.QuadPart) / (f64)perf_freq.QuadPart;

        time_last = time_now;

        if (state.iTimeDelta > 0.0)
        {
          state.iFrameRate = 1.0 / state.iTimeDelta;
        }
      }

      /******************************/
      /* Idle when window minimized */
      /******************************/
      if (state.minimized)
      {
        MSG msg;
        GetMessageA(&msg, 0, 0, 0);
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
        continue;
      }

      /******************************/
      /* Hot Reload Fragment Shader */
      /******************************/
      {
        FILETIME fs_now = win32_file_mod_time(fragment_shader_file_name);

        if (CompareFileTime(&fs_now, &fs_last) != 0)
        {
          /* TODO: check failures */
          opengl_shader_load(&main_shader, fragment_shader_file_name);
          fs_last = fs_now;

          /* Reset iTime elapsed seconds on hot reload */
          QueryPerformanceCounter(&time_start);
        }
      }

      /******************************/
      /* Input Processing           */
      /******************************/
      {
        MSG message = {0};

        while (PeekMessageA(&message, 0, 0, 0, PM_REMOVE))
        {
          switch (message.message)
          {
          case WM_QUIT:
            state.running = 0;
            break;
          default:
            TranslateMessage(&message);
            DispatchMessageA(&message);
            break;
          }
        }
      }

      /******************************/
      /* Rendering                  */
      /******************************/
      glClear(GL_COLOR_BUFFER_BIT);
      glUniform3f(main_shader.loc_iResolution, (f32)state.window_width, (f32)state.window_height, 1.0f);
      glUniform1f(main_shader.loc_iTime, (f32)state.iTime);
      glUniform1f(main_shader.loc_iTimeDelta, (f32)state.iTimeDelta);
      glUniform1i(main_shader.loc_iFrame, state.iFrame);
      glUniform1f(main_shader.loc_iFrameRate, (f32)state.iFrameRate);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      SwapBuffers(state.dc);

      /******************************/
      /* Frame Rate Limiting        */
      /******************************/
      {
        LARGE_INTEGER time_end;

        f64 frame_time;
        f64 remaining;
        f64 target_frame_time = 1.0 / 60.0;

        QueryPerformanceCounter(&time_end);

        frame_time = (f64)(time_end.QuadPart - time_start_fps_cap.QuadPart) / (f64)perf_freq.QuadPart;

        remaining = target_frame_time - frame_time;

        if (remaining > 0.0)
        {
          /* Sleep most of it (milliseconds) */
          if (remaining > 0.002)
          {
            u32 sleep_ms = (u32)((remaining - 0.001) * 1000.0);

            if (sleep_ms > 0)
            {
              Sleep(sleep_ms);
            }
          }

          /* Spin for the rest */
          for (;;)
          {
            QueryPerformanceCounter(&time_end);

            frame_time = (f64)(time_end.QuadPart - time_start_fps_cap.QuadPart) / (f64)perf_freq.QuadPart;

            if (frame_time >= target_frame_time)
            {
              break;
            }
          }
        }

        /* Start timing next frame */
        time_start_fps_cap = time_end;
      }

      state.iFrame++;
    }
  }

  return 0;
}

#ifdef __clang__
#elif __GNUC__
__attribute((externally_visible))
#endif
#ifdef __i686__
__attribute((force_align_arg_pointer))
#endif
i32 mainCRTStartup(void)
{
  u8 *cmdline = (u8 *)GetCommandLineA();
  u8 *argv[8];
  i32 argc = 0;

  i32 return_code;

  /* Parse command line arguments into argv */
  while (*cmdline)
  {
    /* skip whitespace */
    while (*cmdline == ' ' || *cmdline == '\t')
    {
      cmdline++;
    }

    if (!*cmdline)
    {
      break;
    }

    if (argc < 9)
    {
      argv[argc++] = cmdline;
    }

    /* parse token (basic, no quote handling) */
    while (*cmdline && *cmdline != ' ' && *cmdline != '\t')
    {
      cmdline++;
    }

    if (*cmdline)
    {
      *cmdline++ = '\0';
    }
  }

  argv[argc] = (u8 *)0;

  /* Run the program and exit with return code */
  return_code = start(argc, argv);
  ExitProcess((u32)return_code);
  return return_code;
}

/*
   ------------------------------------------------------------------------------
   This software is available under 2 licenses -- choose whichever you prefer.
   ------------------------------------------------------------------------------
   ALTERNATIVE A - MIT License
   Copyright (c) 2026 nickscha
   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to
   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
   of the Software, and to permit persons to whom the Software is furnished to do
   so, subject to the following conditions:
   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
   ------------------------------------------------------------------------------
   ALTERNATIVE B - Public Domain (www.unlicense.org)
   This is free and unencumbered software released into the public domain.
   Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
   software, either in source code form or as a compiled binary, for any purpose,
   commercial or non-commercial, and by any means.
   In jurisdictions that recognize copyright laws, the author or authors of this
   software dedicate any and all copyright interest in the software to the public
   domain. We make this dedication for the benefit of the public at large and to
   the detriment of our heirs and successors. We intend this dedication to be an
   overt act of relinquishment in perpetuity of all present and future rights to
   this software under copyright law.
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
   WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
   ------------------------------------------------------------------------------
*/

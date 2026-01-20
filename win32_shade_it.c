/* shade_it.h - v0.3 - public domain data structures - nickscha 2026

A C89 standard compliant, single header, nostdlib (no C Standard Library) OpenGL Shader Playground (SHADE_IT).

LICENSE

  Placed in the public domain and also MIT licensed.
  See end of file for detailed license information.

*/

/* #############################################################################
 * # COMPILER SETTINGS
 * #############################################################################
 */
#if __STDC_VERSION__ >= 199901L
#define SHADE_IT_INLINE inline
#elif defined(__GNUC__) || defined(__clang__)
#define SHADE_IT_INLINE __inline__
#elif defined(_MSC_VER)
#define SHADE_IT_INLINE __inline
#else
#define SHADE_IT_INLINE
#endif

#define SHADE_IT_API static

/* #############################################################################
 * # Force Discrete GPU
 * #############################################################################
 */
__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001; /* NVIDIA Force discrete GPU */
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;   /* AMD Force discrete GPU    */

/* #############################################################################
 * # Win32 "windows.h" subsitution for fast builds
 * #############################################################################
 */
#define WIN32_API(r) __declspec(dllimport) r __stdcall
#define WIN32_API_CALLBACK __stdcall

#define STD_OUTPUT_HANDLE ((unsigned long)-11)
#define INVALID_FILE_SIZE ((unsigned long)0xFFFFFFFF)
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

#define HWND_TOPMOST ((void *)-1)
#define SWP_NOSIZE 0x0001
#define SWP_NOMOVE 0x0002

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

#define GL_TRUE 1
#define GL_TRIANGLES 0x0004
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_MULTISAMPLE 0x809D

#if defined(_WIN64)

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wlong-long"
typedef long long LONG_PTR;
typedef unsigned long long UINT_PTR;
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
typedef __int64 LONG_PTR;
typedef unsigned __int64 UINT_PTR;
#else
#error "Unsupported compiler"
#endif

#else

typedef long LONG_PTR;
typedef unsigned long UINT_PTR;

#endif

#define LOWORD(l) ((unsigned short)(((UINT_PTR)(l)) & 0xffff))
#define HIWORD(l) ((unsigned short)((((UINT_PTR)(l)) >> 16) & 0xffff))
#define MAKEINTRESOURCEA(i) ((char *)((unsigned long)((unsigned short)(i))))
#define IDC_ARROW MAKEINTRESOURCEA(32512)

typedef void *(*PROC)(void);
typedef LONG_PTR(WIN32_API_CALLBACK *WNDPROC)(void *, unsigned int, UINT_PTR, LONG_PTR);

typedef struct tagCREATESTRUCTA
{
  void *lpCreateParams;
  void *hInstance;
  void *hMenu;
  void *hwndParent;
  int cy;
  int cx;
  int y;
  int x;
  long style;
  char *lpszName;
  char *lpszClass;
  unsigned long dwExStyle;
} CREATESTRUCTA, *LPCREATESTRUCTA;

typedef struct WNDCLASSA
{
  unsigned int style;
  WNDPROC lpfnWndProc;
  int cbClsExtra;
  int cbWndExtra;
  void *hInstance;
  void *hIcon;
  void *hCursor;
  void *hbrBackground;
  char *lpszMenuName;
  char *lpszClassName;
} WNDCLASSA;

typedef struct tagPOINT
{
  long x;
  long y;
} POINT;

typedef struct tagRECT
{
  long left;
  long top;
  long right;
  long bottom;
} RECT, *PRECT, *LPRECT;

typedef struct tagMSG
{
  void *hwnd;
  unsigned int message;
  UINT_PTR wParam;
  LONG_PTR lParam;
  unsigned long time;
  POINT pt;
  unsigned long lPrivate;
} MSG, *LPMSG;

typedef struct tagPIXELFORMATDESCRIPTOR
{
  unsigned short nSize;
  unsigned short nVersion;
  unsigned long dwFlags;
  unsigned char iPixelType;
  unsigned char cColorBits;
  unsigned char cRedBits;
  unsigned char cRedShift;
  unsigned char cGreenBits;
  unsigned char cGreenShift;
  unsigned char cBlueBits;
  unsigned char cBlueShift;
  unsigned char cAlphaBits;
  unsigned char cAlphaShift;
  unsigned char cAccumBits;
  unsigned char cAccumRedBits;
  unsigned char cAccumGreenBits;
  unsigned char cAccumBlueBits;
  unsigned char cAccumAlphaBits;
  unsigned char cDepthBits;
  unsigned char cStencilBits;
  unsigned char cAuxBuffers;
  unsigned char iLayerType;
  unsigned char bReserved;
  unsigned long dwLayerMask;
  unsigned long dwVisibleMask;
  unsigned long dwDamageMask;
} PIXELFORMATDESCRIPTOR, *LPPIXELFORMATDESCRIPTOR;

typedef struct LARGE_INTEGER
{
  LONG_PTR QuadPart;

} LARGE_INTEGER;

typedef struct FILETIME
{
  unsigned long dwLowDateTime;
  unsigned long dwHighDateTime;
} FILETIME;

typedef struct WIN32_FILE_ATTRIBUTE_DATA
{
  unsigned long dwFileAttributes;
  FILETIME ftCreationTime;
  FILETIME ftLastAccessTime;
  FILETIME ftLastWriteTime;
  unsigned long nFileSizeHigh;
  unsigned long nFileSizeLow;
} WIN32_FILE_ATTRIBUTE_DATA;

typedef enum GET_FILEEX_INFO_LEVELS
{
  GetFileExInfoStandard,
  GetFileExMaxInfoLevel
} GET_FILEEX_INFO_LEVELS;

WIN32_API(void *)
GetStdHandle(unsigned long nStdHandle);

WIN32_API(int)
CloseHandle(void *hObject);

WIN32_API(void *)
VirtualAlloc(void *lpAddress, unsigned int dwSize, unsigned long flAllocationType, unsigned long flProtect);

WIN32_API(int)
VirtualFree(void *lpAddress, unsigned int dwSize, unsigned long dwFreeType);

WIN32_API(void *)
CreateFileA(char *lpFileName, unsigned long dwDesiredAccess, unsigned long dwShareMode, void *, unsigned long dwCreationDisposition, unsigned long dwFlagsAndAttributes, void *hTemplateFile);

WIN32_API(unsigned long)
GetFileSize(void *hFile, unsigned long *lpFileSizeHigh);

WIN32_API(int)
ReadFile(void *hFile, void *lpBuffer, unsigned long nNumberOfBytesToRead, unsigned long *lpNumberOfBytesRead, void *lpOverlapped);

WIN32_API(int)
WriteFile(void *hFile, void *lpBuffer, unsigned long nNumberOfBytesToWrite, unsigned long *lpNumberOfBytesWritten, void *lpOverlapped);

WIN32_API(long)
CompareFileTime(FILETIME *lpFileTime1, FILETIME *lpFileTime2);

WIN32_API(int)
GetFileAttributesExA(char *lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, void *lpFileInformation);

WIN32_API(void)
Sleep(unsigned long dwMilliseconds);

WIN32_API(void)
ExitProcess(unsigned int uExitCode);

WIN32_API(int)
PeekMessageA(LPMSG lpMsg, void *hWnd, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax, unsigned int wRemoveMsg);

WIN32_API(int)
TranslateMessage(MSG *lpMsg);

WIN32_API(LONG_PTR)
DispatchMessageA(MSG *lpMsg);

WIN32_API(LONG_PTR)
DefWindowProcA(void *hWnd, unsigned int Msg, UINT_PTR wParam, LONG_PTR lParam);

WIN32_API(LONG_PTR)
SetWindowLongPtrA(void *hWnd, int nIndex, LONG_PTR dwNewLong);

WIN32_API(LONG_PTR)
GetWindowLongPtrA(void *hWnd, int nIndex);

WIN32_API(void *)
GetModuleHandleA(char *lpModuleName);

WIN32_API(void *)
LoadCursorA(void *hInstance, char *lpCursorName);

WIN32_API(unsigned short)
RegisterClassA(WNDCLASSA *lpWndClass);

WIN32_API(void *)
CreateWindowExA(unsigned long dwExStyle, char *lpClassName, char *lpWindowName, unsigned long dwStyle, int X, int Y, int nWidth, int nHeight, void *hWndParent, void *hMenu, void *hInstance, void *lpParam);

WIN32_API(int)
SetWindowPos(void *hWnd, void *hWndInsertAfter, int X, int Y, int cx, int cy, unsigned int uFlags);

WIN32_API(void *)
GetDC(void *hWnd);

WIN32_API(int)
ReleaseDC(void *hWnd, void *hDC);

WIN32_API(int)
SwapBuffers(void *unnamedParam1);

WIN32_API(int)
ChoosePixelFormat(void *hdc, PIXELFORMATDESCRIPTOR *ppfd);

WIN32_API(int)
SetPixelFormat(void *hdc, int format, PIXELFORMATDESCRIPTOR *ppfd);

WIN32_API(int)
DescribePixelFormat(void *hdc, int iPixelFormat, unsigned int nBytes, LPPIXELFORMATDESCRIPTOR ppfd);

WIN32_API(int)
ShowWindow(void *hWnd, int nCmdShow);

WIN32_API(int)
DestroyWindow(void *hWnd);

WIN32_API(int)
AdjustWindowRect(LPRECT lpRect, unsigned long dwStyle, int bMenu);

WIN32_API(int)
QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount);

WIN32_API(int)
QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency);

WIN32_API(char *)
GetCommandLineA(void);

/* WGL */
WIN32_API(void *)
wglCreateContext(void *unnamedParam1);
WIN32_API(void *)
wglGetCurrentContext(void);
WIN32_API(void *)
wglGetCurrentDC(void);
WIN32_API(int)
wglDeleteContext(void *unnamedParam1);
WIN32_API(int)
wglMakeCurrent(void *unnamedParam1, void *unnamedParam2);
WIN32_API(PROC)
wglGetProcAddress(char *unnamedParam1);

/* OpenGL functions provided by win32 */
WIN32_API(void)
glClearColor(float red, float green, float blue, float alpha);
WIN32_API(void)
glClear(unsigned int mask);
WIN32_API(void)
glViewport(int x, int y, int width, int height);
WIN32_API(void)
glEnable(unsigned int cap);
WIN32_API(void)
glDisable(unsigned int cap);
WIN32_API(unsigned char *)
glGetString(unsigned int name);

/* #############################################################################
 * # OpenGL Functions not automatically provided by win32 opengl32
 * # Needs to be loaded during runtime
 * #############################################################################
 */
typedef int (*PFNWGLCHOOSEPIXELFORMATARBPROC)(void *hdc, int *piAttribIList, float *pfAttribFList, unsigned int nMaxFormats, int *piFormats, unsigned int *nNumFormats);
typedef void *(*PFNWGLCREATECONTEXTATTRIBSARBPROC)(void *hDC, void *hShareContext, int *attribList);
typedef int (*PFNWGLSWAPINTERVALEXTPROC)(int interval);

/* #############################################################################
 * # Main Code
 * #############################################################################
 */
typedef struct shade_it_state
{

  unsigned int window_width;
  unsigned int window_height;

  float window_clear_color_g;
  float window_clear_color_b;
  float window_clear_color_r;
  float window_clear_color_a;

  unsigned char running;

} shade_it_state;

SHADE_IT_API SHADE_IT_INLINE LONG_PTR WIN32_API_CALLBACK win32_shade_it_window_callback(void *window, unsigned int message, UINT_PTR wParam, LONG_PTR lParam)
{
  shade_it_state *state = (shade_it_state *)GetWindowLongPtrA(window, GWLP_USERDATA);

  LONG_PTR result = 0;

  switch (message)
  {
  case WM_ERASEBKGND:
    return 1;
  case WM_CREATE:
  {
    CREATESTRUCTA *cs = (CREATESTRUCTA *)lParam;
    state = (shade_it_state *)cs->lpCreateParams;
    SetWindowLongPtrA(window, GWLP_USERDATA, (LONG_PTR)state);
  }
  break;
  case WM_CLOSE:
  {
    if (state)
    {
      state->running = 0;
    }
  }
  break;
  case WM_SIZE:
  {
    if (state)
    {
      state->window_width = (unsigned int)LOWORD(lParam);
      state->window_height = (unsigned int)HIWORD(lParam);

      glViewport(0, 0, (int)state->window_width, (int)state->window_height);
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

#define GL_COMPILE_STATUS 0x8B81
#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_LINK_STATUS 0x8B82
#define GL_VENDOR 0x1F00
#define GL_RENDERER 0x1F01
#define GL_VERSION 0x1F02

typedef unsigned int (*PFNGLCREATESHADERPROC)(unsigned int shaderType);
static PFNGLCREATESHADERPROC glCreateShader;

typedef unsigned int (*PFNGLCREATEPROGRAMPROC)(void);
static PFNGLCREATEPROGRAMPROC glCreateProgram;

typedef void (*PFNGLDELETEPROGRAMPROC)(unsigned int program);
static PFNGLDELETEPROGRAMPROC glDeleteProgram;

typedef void (*PFNGLATTACHSHADERPROC)(unsigned int program, unsigned int shader);
static PFNGLATTACHSHADERPROC glAttachShader;

typedef void (*PFNGLSHADERSOURCEPROC)(unsigned int shader, int count, char **string, int *length);
static PFNGLSHADERSOURCEPROC glShaderSource;

typedef void (*PFNGLCOMPILESHADERPROC)(unsigned int shader);
static PFNGLCOMPILESHADERPROC glCompileShader;

typedef void (*PFNGLGETSHADERIVPROC)(unsigned int shader, unsigned int pname, int *params);
static PFNGLGETSHADERIVPROC glGetShaderiv;

typedef void (*PFNGLGETSHADERINFOLOGPROC)(unsigned int shader, int maxLength, int *length, char *infoLog);
static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

typedef void (*PFNGLLINKPROGRAMPROC)(unsigned int program);
static PFNGLLINKPROGRAMPROC glLinkProgram;

typedef void (*PFNGLGETPROGRAMIVPROC)(unsigned int program, unsigned int pname, int *params);
static PFNGLGETPROGRAMIVPROC glGetProgramiv;

typedef void (*PFNGLGETPROGRAMINFOLOGPROC)(unsigned int program, int maxLength, int *length, char *infoLog);
static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;

typedef void (*PFNGLDELETESHADERPROC)(unsigned int shader);
static PFNGLDELETESHADERPROC glDeleteShader;

typedef void (*PFNGLDRAWARRAYSPROC)(unsigned int mode, int first, int count);
static PFNGLDRAWARRAYSPROC glDrawArrays;

typedef void (*PFNGLUSEPROGRAMPROC)(unsigned int program);
static PFNGLUSEPROGRAMPROC glUseProgram;

typedef void (*PFNGLGENVERTEXARRAYSPROC)(int n, unsigned int *arrays);
static PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;

typedef void (*PFNGLBINDVERTEXARRAYPROC)(unsigned int array);
static PFNGLBINDVERTEXARRAYPROC glBindVertexArray;

typedef int (*PFNGLGETUNIFORMLOCATIONPROC)(unsigned int program, char *name);
static PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;

typedef void (*PFNGLUNIFORM1FPROC)(int location, float v0);
static PFNGLUNIFORM1FPROC glUniform1f;

typedef void (*PFNGLUNIFORM1IPROC)(int location, int v0);
static PFNGLUNIFORM1IPROC glUniform1i;

typedef void (*PFNGLUNIFORM3FPROC)(int location, float v0, float v1, float v2);
static PFNGLUNIFORM3FPROC glUniform3f;

SHADE_IT_API void win32_print(char *str)
{
  static unsigned long written;
  static void *stdout_handle;

  if (!stdout_handle)
  {
    stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
  }

  {
    char *p = str;
    unsigned long len = 0;

    while (*p++)
    {
      len++;
    }

    WriteFile(stdout_handle, str, len, &written, 0);
  }
}

SHADE_IT_API unsigned char *win32_read_file(char *filename, unsigned int *file_size_out)
{
  void *hFile = INVALID_HANDLE;
  unsigned long fileSize = 0;
  unsigned long bytesRead = 0;

  unsigned char *buffer = 0;
  int attempt;

  /* Retry loop for hot-reload: file might be locked or partially written */
  for (attempt = 0; attempt < 4; ++attempt)
  {
    hFile = CreateFileA(
        filename,
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, /* Hot-reload safe */
        (void *)0,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
        (void *)0);

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

  fileSize = GetFileSize(hFile, (void *)0);

  if (fileSize == INVALID_FILE_SIZE || fileSize == 0)
  {
    CloseHandle(hFile);
    return (void *)0;
  }

  /* Small file: read normally */
  buffer = (unsigned char *)VirtualAlloc((void *)0, fileSize + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

  if (!buffer)
  {
    CloseHandle(hFile);
    return (void *)0;
  }

  if (!ReadFile(hFile, buffer, fileSize, &bytesRead, (void *)0) || bytesRead != fileSize)
  {
    VirtualFree(buffer, 0, MEM_RELEASE);
    CloseHandle(hFile);
    return (void *)0;
  }

  buffer[fileSize] = '\0'; /* Null-terminate */

  *file_size_out = fileSize;
  CloseHandle(hFile);
  return buffer;
}

SHADE_IT_API SHADE_IT_INLINE FILETIME win32_file_mod_time(char *file)
{
  static FILETIME empty = {0, 0};
  WIN32_FILE_ATTRIBUTE_DATA fad;
  return GetFileAttributesExA(file, GetFileExInfoStandard, &fad) ? fad.ftLastWriteTime : empty;
}

/* ############################################################################
 * # Command line parsing
 * ############################################################################
 *
 * Basic (non-quoted) command line parser
 * Converts "program.exe arg1 arg2" -> argc=3, argv={"program.exe","arg1","arg2",NULL}
 * In-place: modifies the command line buffer.
 */
SHADE_IT_API int win32_parse_command_line(unsigned char *cmdline, unsigned char ***argv_out)
{
  static unsigned char *argv_local[8]; /* up to 8 args */
  int argc = 0;

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

    if (argc < 63)
    {
      argv_local[argc++] = cmdline;
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

  argv_local[argc] = (unsigned char *)0;
  *argv_out = argv_local;

  return argc;
}

SHADE_IT_API int opengl_shader_compile(
    char *shaderCode,
    unsigned int shaderType)
{
  unsigned int shaderId = glCreateShader(shaderType);
  int success;

  glShaderSource(shaderId, 1, &shaderCode, (void *)0);
  glCompileShader(shaderId);

  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

  if (!success)
  {
    char infoLog[1024];
    glGetShaderInfoLog(shaderId, 1024, (void *)0, infoLog);

    win32_print("[opengl] shader compilation error:\n");
    win32_print(infoLog);
    win32_print("\n");

    return -1;
  }

  return (int)shaderId;
}

SHADE_IT_API int opengl_shader_create(
    unsigned int *shader_program,
    char *shader_vertex_code,
    char *shader_fragment_code)
{
  int vertex_shader_id;
  int fragment_shader_id;
  int success;

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
  glAttachShader(*shader_program, (unsigned int)vertex_shader_id);
  glAttachShader(*shader_program, (unsigned int)fragment_shader_id);
  glLinkProgram(*shader_program);
  glGetProgramiv(*shader_program, GL_LINK_STATUS, &success);
  glDeleteShader((unsigned int)vertex_shader_id);
  glDeleteShader((unsigned int)fragment_shader_id);

  if (!success)
  {
    char infoLog[1024];
    glGetProgramInfoLog(*shader_program, 1024, (void *)0, infoLog);

    win32_print("[opengl] program creation error:\n");
    win32_print(infoLog);
    win32_print("\n");

    return 0;
  }

  return 1;
}

typedef struct shader
{
  unsigned int created;
  unsigned int program;

  int loc_iResolution;
  int loc_iTime;
  int loc_iTimeDelta;
  int loc_iFrame;
  int loc_iFrameRate;

} shader;

SHADE_IT_API void opengl_shader_load(shader *shader, char *shader_file_name)
{
  static char *shader_code_vertex =
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

  unsigned int size = 0;
  unsigned char *src = win32_read_file(shader_file_name, &size);

  if (src && size > 0)
  {
    unsigned int new_program = 0;

    if (opengl_shader_create(&new_program, shader_code_vertex, (char *)src))
    {
      glUseProgram(0);

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
}

SHADE_IT_API int start(int argc, unsigned char **argv)
{
  void *window_handle = (void *)0;
  void *dc = (void *)0;

  char *fragment_shader_file_name = "shade_it.fs";

  shader main_shader = {0};
  shade_it_state state = {0};

  if (argv && argc > 1)
  {
    fragment_shader_file_name = (char *)argv[1];
  }

  win32_print("[opengl] load shader file: ");
  win32_print(fragment_shader_file_name);
  win32_print("\n");

  state.running = 1;
  state.window_width = 800;
  state.window_height = 600;
  state.window_clear_color_r = 0.5f;

  /******************************/
  /* Window and OpenGL context  */
  /******************************/
  {
    void *instance = GetModuleHandleA(0);
    WNDCLASSA windowClass = {0};

    void *fakeWND;
    void *fakeDC;
    int fakePFDID;
    void *fakeRC;

    unsigned long windowStyle;

    PIXELFORMATDESCRIPTOR fakePFD = {0};
    RECT rect = {0};

    int pixelAttribs[] = {
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

    int pixelFormatID;
    unsigned int numFormats;
    int status;

    int contextAttribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0};

    void *rc;

    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
    PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;

    windowClass.style = CS_OWNDC;
    windowClass.lpfnWndProc = win32_shade_it_window_callback;
    windowClass.hInstance = instance;
    windowClass.hCursor = LoadCursorA(0, IDC_ARROW);
    windowClass.hbrBackground = 0;
    windowClass.lpszClassName = "shade_it";

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

    rect.right = (long)state.window_width;
    rect.bottom = (long)state.window_height;

    AdjustWindowRect(&rect, windowStyle, 0);
    state.window_width = (unsigned int)(rect.right - rect.left);
    state.window_height = (unsigned int)(rect.bottom - rect.top);

    window_handle = CreateWindowExA(
        0,
        windowClass.lpszClassName,
        windowClass.lpszClassName,
        windowStyle,
        0, 0,
        (int)state.window_width, (int)state.window_height,
        0, 0,
        instance,
        &state /* Pass pointer to user data to the window callback */
    );

    /* Modal window */
    SetWindowPos(window_handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    dc = GetDC(window_handle);

#ifdef _MSC_VER
#pragma warning(disable : 4068)
#endif
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
    wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");

    if (!wglChoosePixelFormatARB)
    {
      return 1;
    }

    wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

    if (!wglCreateContextAttribsARB)
    {
      return 1;
    }

    wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

    /* OpenGL Shaders */
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

    status = wglChoosePixelFormatARB(dc, pixelAttribs, 0, 1, &pixelFormatID, &numFormats);

    if (!status || !numFormats)
    {
      return 1;
    }

    SetPixelFormat(dc, pixelFormatID, 0);

    /* Open GL 3.3 specification */
    rc = wglCreateContextAttribsARB(dc, 0, contextAttribs);

    if (!rc)
    {
      return 1;
    }

    wglMakeCurrent(0, 0);
    wglDeleteContext(fakeRC);
    ReleaseDC(fakeWND, fakeDC);
    DestroyWindow(fakeWND);

    if (!wglMakeCurrent(dc, rc))
    {
      return 1;
    }

    /* Disable VSync */
    if (wglSwapIntervalEXT)
    {
      wglSwapIntervalEXT(0);
    }

    /* Avoid clear color flickering */
    glClearColor(state.window_clear_color_r, state.window_clear_color_g, state.window_clear_color_b, state.window_clear_color_a);
    glClear(GL_COLOR_BUFFER_BIT);
    SwapBuffers(dc);

    /* Make the window visible */
    ShowWindow(window_handle, SW_SHOW);
  }

  /******************************/
  /* OpenGL Preparation         */
  /******************************/
  glDisable(GL_MULTISAMPLE);
  glViewport(0, 0, (int)state.window_width, (int)state.window_height);

  {
    /* Generate a dummy vao with no buffer */
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    /* TODO: check failures */
    opengl_shader_load(&main_shader, fragment_shader_file_name);
  }

  {
    LARGE_INTEGER perf_freq;
    LARGE_INTEGER time_start;
    LARGE_INTEGER time_start_fps_cap;
    LARGE_INTEGER time_last;

    int iFrame = 0;
    double iTime = 0.0;
    double iTimeDelta = 0.0;
    double iFrameRate = 0.0;

    FILETIME fs_last = win32_file_mod_time(fragment_shader_file_name);

    /* Print opengl information */
    {
      char *vendor = (char *)glGetString(GL_VENDOR);
      char *renderer = (char *)glGetString(GL_RENDERER);
      char *version = (char *)glGetString(GL_VERSION);

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

        iTimeDelta =
            (double)(time_now.QuadPart - time_last.QuadPart) /
            (double)perf_freq.QuadPart;

        iTime =
            (double)(time_now.QuadPart - time_start.QuadPart) /
            (double)perf_freq.QuadPart;

        time_last = time_now;

        if (iTimeDelta > 0.0)
        {
          iFrameRate = 1.0 / iTimeDelta;
        }
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
      glUniform3f(main_shader.loc_iResolution, (float)state.window_width, (float)state.window_height, 1.0f);
      glUniform1f(main_shader.loc_iTime, (float)iTime);
      glUniform1f(main_shader.loc_iTimeDelta, (float)iTimeDelta);
      glUniform1i(main_shader.loc_iFrame, iFrame);
      glUniform1f(main_shader.loc_iFrameRate, (float)iFrameRate);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      SwapBuffers(dc);

      /******************************/
      /* Cap FPS to 60 Hz           */
      /******************************/
      {
        LARGE_INTEGER time_end;
        double frame_time;
        double remaining;
        double target_frame_time = 1.0 / 60.0;

        QueryPerformanceCounter(&time_end);

        frame_time =
            (double)(time_end.QuadPart - time_start_fps_cap.QuadPart) /
            (double)perf_freq.QuadPart;

        remaining = target_frame_time - frame_time;

        if (remaining > 0.0)
        {
          /* Sleep most of it (milliseconds) */
          if (remaining > 0.002)
          {
            unsigned long sleep_ms = (unsigned long)((remaining - 0.001) * 1000.0);
            if (sleep_ms > 0)
            {
              Sleep(sleep_ms);
            }
          }

          /* Spin for the rest */
          for (;;)
          {
            QueryPerformanceCounter(&time_end);

            frame_time =
                (double)(time_end.QuadPart - time_start_fps_cap.QuadPart) /
                (double)perf_freq.QuadPart;

            if (frame_time >= target_frame_time)
            {
              break;
            }
          }
        }

        /* Start timing next frame */
        time_start_fps_cap = time_end;
      }

      iFrame++;
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
int mainCRTStartup(void)
{
  unsigned char *cmdline = (unsigned char *)GetCommandLineA();
  unsigned char **argv;

  int argc = win32_parse_command_line(cmdline, &argv);
  int return_code = start(argc, argv);

  ExitProcess((unsigned int)return_code);
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

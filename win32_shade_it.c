/* win32_shade_it.c - v0.7 - public domain data structures - nickscha 2026

A C89 standard compliant, single file, nostdlib (no C Standard Library) OpenGL Live Shader Coding Playground (SHADE_IT).

LICENSE

  Placed in the public domain and also MIT licensed.
  See end of file for detailed license information.

*/

/* #############################################################################
 * # [SECTION] TYPES & COMPILER SETTINGS
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
typedef short i16;
typedef int i32;
typedef float f32;
typedef double f64;

#define TYPES_STATIC_ASSERT(c, m) typedef char types_assert_##m[(c) ? 1 : -1]
TYPES_STATIC_ASSERT(sizeof(s8) == 1, s8_size_must_be_1);
TYPES_STATIC_ASSERT(sizeof(u8) == 1, u8_size_must_be_1);
TYPES_STATIC_ASSERT(sizeof(u16) == 2, u16_size_must_be_2);
TYPES_STATIC_ASSERT(sizeof(i16) == 2, i16_size_must_be_2);
TYPES_STATIC_ASSERT(sizeof(u32) == 4, u32_size_must_be_4);
TYPES_STATIC_ASSERT(sizeof(i32) == 4, i32_size_must_be_4);
TYPES_STATIC_ASSERT(sizeof(f32) == 4, f32_size_must_be_4);
TYPES_STATIC_ASSERT(sizeof(f64) == 8, f64_size_must_be_8);
TYPES_STATIC_ASSERT(sizeof(u64) == 8, u64_size_must_be_8);
TYPES_STATIC_ASSERT(sizeof(i64) == 8, i64_size_must_be_8);

/* Unfortunaly "modern" compilers sometimes inject memset intrinsics in the generated code
 * even if the application does not call memset and even with -fno-builtin, ... set.
 * Therefore we have to provide our own memset function.
 */
#ifdef _MSC_VER
#pragma function(memset)
#endif
void *memset(void *dest, i32 c, u32 count)
{
  s8 *bytes = (s8 *)dest;
  while (count--)
  {
    *bytes++ = (s8)c;
  }
  return dest;
}

/* #############################################################################
 * # [SECTION] Force Discrete GPU
 * #############################################################################
 */
__declspec(dllexport) u32 NvOptimusEnablement = 0x00000001;         /* NVIDIA Force discrete GPU */
__declspec(dllexport) i32 AmdPowerXpressRequestHighPerformance = 1; /* AMD Force discrete GPU    */

/* #############################################################################
 * # [SECTION] win32 "windows.h" subsitution for fast builds
 * #############################################################################
 */
#define WIN32_API(r) __declspec(dllimport) r __stdcall

#define INVALID_FILE_SIZE ((u32)0xFFFFFFFF)
#define INVALID_HANDLE ((void *)-1)
#define GENERIC_READ (0x80000000L)
#define GENERIC_WRITE (0x40000000L)
#define CREATE_ALWAYS 2
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
#define WM_INPUT 0x00FF
#define WM_DEVICECHANGE 0x0219

#define DBT_DEVICEARRIVAL 0x8000
#define DBT_DEVICEREMOVECOMPLETE 0x8004
#define DBT_DEVNODES_CHANGED 0x0007

#define SIZE_MINIMIZED 1

#define CS_OWNDC 0x0020

#define HWND_TOPMOST ((void *)-1)
#define HWND_TOP ((void *)0)

#define WS_CLIPSIBLINGS 0x04000000
#define WS_CLIPCHILDREN 0x02000000
#define WS_THICKFRAME 0x00040000L
#define WS_MINIMIZEBOX 0x00020000L
#define WS_MAXIMIZEBOX 0x00010000L
#define WS_CAPTION 0x00C00000L
#define WS_SYSMENU 0x00080000L
#define WS_OVERLAPPED 0x00000000L
#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)

#define SWP_NOSIZE 0x0001
#define SWP_NOMOVE 0x0002
#define SWP_NOZORDER 0x0004
#define SWP_SHOWWINDOW 0x0040
#define SWP_NOOWNERZORDER 0x0200
#define SWP_FRAMECHANGED 0x0020
#define SW_SHOW 5

#define GWL_STYLE -16
#define GWLP_USERDATA -21

#define MONITOR_DEFAULTTONEAREST 0x00000002

#define PM_REMOVE 0x0001

#define PFD_DOUBLEBUFFER 0x00000001
#define PFD_SUPPORT_OPENGL 0x00000020
#define PFD_DRAW_TO_WINDOW 0x00000004
#define PFD_TYPE_RGBA 0

#define MAKEINTRESOURCEA(i) ((s8 *)((u32)((u16)(i))))
#define IDC_ARROW MAKEINTRESOURCEA(32512)

#define RIDEV_INPUTSINK 0x00000100
#define RID_INPUT 0x10000003
#define RIM_TYPEMOUSE 0
#define RIM_TYPEKEYBOARD 1
#define RI_KEY_BREAK 1

#define HIGH_PRIORITY_CLASS 0x80
#define THREAD_PRIORITY_HIGHEST 2
#define ES_SYSTEM_REQUIRED ((u32)0x00000001)
#define ES_DISPLAY_REQUIRED ((u32)0x00000002)
#define ES_CONTINUOUS ((u32)0x80000000)

#define TH32CS_SNAPTHREAD 0x00000004

typedef void *(*PROC)(void);
typedef i64 (*WNDPROC)(void *, u32, u64, i64);

typedef struct CREATESTRUCTA
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
} CREATESTRUCTA;

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

typedef struct POINT
{
  i32 x;
  i32 y;
} POINT;

typedef struct RECT
{
  i32 left;
  i32 top;
  i32 right;
  i32 bottom;
} RECT;

typedef struct MSG
{
  void *hwnd;
  u32 message;
  u64 wParam;
  i64 lParam;
  u32 time;
  POINT pt;
  u32 lPrivate;
} MSG;

typedef struct PIXELFORMATDESCRIPTOR
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
} PIXELFORMATDESCRIPTOR;

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

typedef struct RAWINPUTDEVICE
{
  u16 usUsagePage;
  u16 usUsage;
  u32 dwFlags;
  void *hwndTarget;
} RAWINPUTDEVICE;

typedef struct RAWINPUTHEADER
{
  u32 dwType;
  u32 dwSize;
  void *hDevice;
  u64 wParam;
} RAWINPUTHEADER;

typedef struct RAWKEYBOARD
{
  u16 MakeCode;
  u16 Flags;
  u16 Reserved;
  u16 VKey;
  u32 Message;
  u32 ExtraInformation;
} RAWKEYBOARD;

typedef struct RAWMOUSE
{
  u16 usFlags;
  u16 usButtonFlags;
  u16 usButtonData;
  u32 ulRawButtons;
  i32 lLastX;
  i32 lLastY;
  u32 ulExtraInformation;
} RAWMOUSE;

typedef struct RAWHID
{
  u32 dwSizeHid;
  u32 dwCount;
  u8 bRawData[1];
} RAWHID;

typedef struct RAWINPUT
{
  RAWINPUTHEADER header;
  union
  {
    RAWMOUSE mouse;
    RAWKEYBOARD keyboard;
    RAWHID hid;
  } data;
} RAWINPUT;

typedef struct PROCESS_MEMORY_COUNTERS_EX
{
  u32 cb;
  u32 PageFaultCount;
  u64 PeakWorkingSetSize;
  u64 WorkingSetSize;
  u64 QuotaPeakPagedPoolUsage;
  u64 QuotaPagedPoolUsage;
  u64 QuotaPeakNonPagedPoolUsage;
  u64 QuotaNonPagedPoolUsage;
  u64 PagefileUsage;
  u64 PeakPagefileUsage;
  u64 PrivateUsage;
} PROCESS_MEMORY_COUNTERS_EX;

typedef struct THREADENTRY32
{
  u32 dwSize;
  u32 cntUsage;
  u32 th32ThreadID;
  u32 th32OwnerProcessID;
  i32 tpBasePri;
  i32 tpDeltaPri;
  u32 dwFlags;
} THREADENTRY32;

typedef struct WINDOWPLACEMENT
{
  u32 length;
  u32 flags;
  u32 showCmd;
  POINT ptMinPosition;
  POINT ptMaxPosition;
  RECT rcNormalPosition;
  RECT rcDevice;
} WINDOWPLACEMENT;

typedef struct MONITORINFO
{
  u32 cbSize;
  RECT rcMonitor;
  RECT rcWork;
  u32 dwFlags;
} MONITORINFO;

/* clang-format off */
WIN32_API(void *) GetStdHandle(u32 nStdHandle);
WIN32_API(i32)    CloseHandle(void *hObject);
WIN32_API(void *) LoadLibraryA(s8 *lpLibFileName);
WIN32_API(i32)    FreeLibrary(void *hLibModule);
WIN32_API(void *) GetProcAddress(void *hModule, char *lpProcName);
WIN32_API(i32)    SetProcessDPIAware(void);
WIN32_API(void *) VirtualAlloc(void *lpAddress, u32 dwSize, u32 flAllocationType, u32 flProtect);
WIN32_API(i32)    VirtualFree(void *lpAddress, u32 dwSize, u32 dwFreeType);
WIN32_API(void *) CreateFileA(s8 *lpFileName, u32 dwDesiredAccess, u32 dwShareMode, void *, u32 dwCreationDisposition, u32 dwFlagsAndAttributes, void *hTemplateFile);
WIN32_API(u32)    GetFileSize(void *hFile, u32 *lpFileSizeHigh);
WIN32_API(i32)    ReadFile(void *hFile, void *lpBuffer, u32 nNumberOfBytesToRead, u32 *lpNumberOfBytesRead, void *lpOverlapped);
WIN32_API(i32)    WriteFile(void *hFile, void *lpBuffer, u32 nNumberOfBytesToWrite, u32 *lpNumberOfBytesWritten, void *lpOverlapped);
WIN32_API(i32)    CompareFileTime(FILETIME *lpFileTime1, FILETIME *lpFileTime2);
WIN32_API(i32)    GetFileAttributesExA(s8 *lpFileName, u32 fInfoLevelId, void *lpFileInformation);
WIN32_API(void)   Sleep(u32 dwMilliseconds);
WIN32_API(void)   ExitProcess(u32 uExitCode);
WIN32_API(i32)    PeekMessageA(MSG* lpMsg, void *hWnd, u32 wMsgFilterMin, u32 wMsgFilterMax, u32 wRemoveMsg);
WIN32_API(i32)    GetMessageA(MSG* lpMsg, void *hWnd, u32 wMsgFilterMin, u32 wMsgFilterMax);
WIN32_API(i32)    TranslateMessage(MSG *lpMsg);
WIN32_API(i64)    DispatchMessageA(MSG *lpMsg);
WIN32_API(i64)    DefWindowProcA(void *hWnd, u32 Msg, u64 wParam, i64 lParam);
WIN32_API(i64)    SetWindowLongPtrA(void *hWnd, i32 nIndex, i64 dwNewLong);
WIN32_API(i64)    GetWindowLongPtrA(void *hWnd, i32 nIndex);
WIN32_API(void *) GetModuleHandleA(s8 *lpModuleName);
WIN32_API(void *) LoadCursorA(void *hInstance, s8 *lpCursorName);
WIN32_API(void *) LoadIconA(void *hInstance, s8 *lpIconName);
WIN32_API(u16)    RegisterClassA(WNDCLASSA *lpWndClass);
WIN32_API(void *) CreateWindowExA(u32 dwExStyle, s8 *lpClassName, s8 *lpWindowName, u32 dwStyle, i32 X, i32 Y, i32 nWidth, i32 nHeight, void *hWndParent, void *hMenu, void *hInstance, void *lpParam);
WIN32_API(void *) GetDC(void *hWnd);
WIN32_API(i32)    ReleaseDC(void *hWnd, void *hDC);
WIN32_API(i32)    SwapBuffers(void *unnamedParam1);
WIN32_API(i32)    ChoosePixelFormat(void *hdc, PIXELFORMATDESCRIPTOR *ppfd);
WIN32_API(i32)    SetPixelFormat(void *hdc, i32 format, PIXELFORMATDESCRIPTOR *ppfd);
WIN32_API(i32)    DescribePixelFormat(void *hdc, i32 iPixelFormat, u32 nBytes, PIXELFORMATDESCRIPTOR* ppfd);
WIN32_API(i32)    ShowWindow(void *hWnd, i32 nCmdShow);
WIN32_API(i32)    DestroyWindow(void *hWnd);
WIN32_API(i32)    AdjustWindowRect(RECT* lpRect, u32 dwStyle, i32 bMenu);
WIN32_API(i32)    QueryPerformanceCounter(i64 *lpPerformanceCount);
WIN32_API(i32)    QueryPerformanceFrequency(i64 *lpFrequency);
WIN32_API(s8 *)   GetCommandLineA(void);
WIN32_API(i32)    RegisterRawInputDevices(RAWINPUTDEVICE* pRawInputDevices, u32 uiNumDevices, u32 cbSize);
WIN32_API(u32)    GetRawInputData(void *hRawInput, u32 uiCommand, void *pData, u32 *pcbSize, u32 cbSizeHeader);
WIN32_API(i32)    GetCursorPos(POINT *lpPoint);
WIN32_API(i32)    ScreenToClient(void *hWnd, POINT *lpPoint);

WIN32_API(i32)    GetWindowLongA(void *hWnd, i32 nIndex);
WIN32_API(i32)    GetWindowPlacement(void *hWnd, WINDOWPLACEMENT *lpwndpl);
WIN32_API(i32)    GetMonitorInfoA(void *hMonitor, MONITORINFO* lpmi);
WIN32_API(void *) MonitorFromWindow(void *hwnd, u32 dwFlags);
WIN32_API(i32)    SetWindowLongA(void *hWnd, i32 nIndex, i32 dwNewLong);
WIN32_API(i32)    SetWindowPos(void *hWnd, void *hWndInsertAfter, i32 X, i32 Y, i32 cx, i32 cy, u32 uFlags);
WIN32_API(i32)    SetWindowPlacement(void *hWnd, WINDOWPLACEMENT *lpwndpl);
WIN32_API(i32)    GetClientRect(void *hWnd, RECT* lpRect);

WIN32_API(void *) GetCurrentProcess(void);
WIN32_API(u32)    GetCurrentProcessId(void);
WIN32_API(i32)    SetPriorityClass(void *hProcess, u32 dwPriorityClass);
WIN32_API(void *) GetCurrentThread(void);
WIN32_API(i32)    SetThreadPriority(void *hThread, i32 nPriority);
WIN32_API(u32)    SetThreadExecutionState(u32 esFlags);
WIN32_API(i32)    GetProcessHandleCount(void* hProcess, u32* pdwHandleCount);
WIN32_API(void *) CreateToolhelp32Snapshot(u32 dwFlags, u32 th32ProcessID);
WIN32_API(i32)    Thread32First(void* hSnapshot, THREADENTRY32* lpte);
WIN32_API(i32)    Thread32Next(void* hSnapshot, THREADENTRY32* lpte);

/* WGL */
WIN32_API(void *) wglCreateContext(void *unnamedParam1);
WIN32_API(void *) wglGetCurrentContext(void);
WIN32_API(void *) wglGetCurrentDC(void);
WIN32_API(i32)    wglDeleteContext(void *unnamedParam1);
WIN32_API(i32)    wglMakeCurrent(void *unnamedParam1, void *unnamedParam2);
WIN32_API(PROC)   wglGetProcAddress(s8 *unnamedParam1);

/* OpenGL functions provided by win32 */
WIN32_API(void)   glClearColor(f32 red, f32 green, f32 blue, f32 alpha);
WIN32_API(void)   glClear(u32 mask);
WIN32_API(void)   glViewport(i32 x, i32 y, i32 width, i32 height);
WIN32_API(void)   glEnable(u32 cap);
WIN32_API(void)   glDisable(u32 cap);
WIN32_API(u8 *)   glGetString(u32 name);
WIN32_API(void)   glGenTextures(i32 n, u32 *textures);
WIN32_API(void)   glBindTexture(u32 target, u32 texture);
WIN32_API(void)   glTexImage2D(u32 target, i32 level, i32 internalformat, i32 width, i32 height, i32 border, i32 format, u32 type, void *pixels);
WIN32_API(void)   glTexParameteri(u32 target, u32 pname, i32 param);
WIN32_API(void)   glPixelStorei(u32 pname, i32 param);
WIN32_API(void)   glReadPixels(i32 x, i32 y, i32 width, i32 height, i32 format, i32 type, void  *pixels);
WIN32_API(void)   glBlendFunc(u32 sfactor, u32 dfactor);

/* clang-format on */

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
#define GL_FALSE 0
#define GL_UNSIGNED_SHORT 0x1403
#define GL_FLOAT 0x1406
#define GL_TRIANGLES 0x0004
#define GL_TRIANGLE_FAN 0x0006
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
#define GL_STREAM_DRAW 0x88E0
#define GL_STATIC_DRAW 0x88E4
#define GL_DYNAMIC_DRAW 0x88E8
#define GL_ARRAY_BUFFER 0x8892

#define GL_UNSIGNED_BYTE 0x1401
#define GL_TEXTURE_2D 0x0DE1
#define GL_NEAREST 0x2600
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_PACK_ALIGNMENT 0x0D05
#define GL_UNPACK_ALIGNMENT 0x0CF5
#define GL_RGB 0x1907
#define GL_RED 0x1903
#define GL_R8 0x8229
#define GL_TEXTURE0 0x84C0
#define GL_BLEND 0x0BE2
#define GL_SRC_ALPHA 0x0302
#define GL_ONE_MINUS_SRC_ALPHA 0x0303

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

typedef void (*PFNGLUNIFORM4FPROC)(i32 location, f32 v0, f32 v1, f32 v2, f32 v3);
static PFNGLUNIFORM4FPROC glUniform4f;

typedef void (*PFNGLUNIFORM4FVPROC)(i32 location, i32 count, f32 *value);
static PFNGLUNIFORM4FVPROC glUniform4fv;

typedef void (*PFNGLACTIVETEXTUREPROC)(u32 texture);
static PFNGLACTIVETEXTUREPROC glActiveTexture;

typedef void (*PFNGLGENBUFFERSPROC)(i32 n, u32 *buffers);
static PFNGLGENBUFFERSPROC glGenBuffers;

typedef void (*PFNGLBINDBUFFERPROC)(u32 target, u32 buffer);
static PFNGLBINDBUFFERPROC glBindBuffer;

typedef void (*PFNGLBUFFERDATAPROC)(u32 target, i32 size, void *data, u32 usage);
static PFNGLBUFFERDATAPROC glBufferData;

typedef void (*PFNGLENABLEVERTEXATTRIBARRAYPROC)(u32 index);
static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;

typedef void (*PFNGLVERTEXATTRIBPOINTERPROC)(u32 index, i32 size, u32 type, u8 normalized, i32 stride, void *pointer);
static PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;

typedef void (*PFNGLVERTEXATTRIBIPOINTERPROC)(u32 index, i32 size, u32 type, i32 stride, void *pointer);
static PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer;

typedef void (*PFNGLVERTEXATTRIBDIVISORPROC)(u32 index, u32 divisor);
static PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor;

typedef void (*PFNGLDRAWARRAYSINSTANCED)(i32 mode, i32 first, i32 count, u32 primcount);
static PFNGLDRAWARRAYSINSTANCED glDrawArraysInstanced;

/* #############################################################################
 * # [SECTION] XINPUT gamepad controller support
 * #############################################################################
 */
#define XINPUT_USER_MAX_COUNT 4
#define XINPUT_GAMEPAD_DPAD_UP 0x0001
#define XINPUT_GAMEPAD_DPAD_DOWN 0x0002
#define XINPUT_GAMEPAD_DPAD_LEFT 0x0004
#define XINPUT_GAMEPAD_DPAD_RIGHT 0x0008
#define XINPUT_GAMEPAD_START 0x0010
#define XINPUT_GAMEPAD_BACK 0x0020
#define XINPUT_GAMEPAD_LEFT_THUMB 0x0040
#define XINPUT_GAMEPAD_RIGHT_THUMB 0x0080
#define XINPUT_GAMEPAD_LEFT_SHOULDER 0x0100
#define XINPUT_GAMEPAD_RIGHT_SHOULDER 0x0200
#define XINPUT_GAMEPAD_A 0x1000
#define XINPUT_GAMEPAD_B 0x2000
#define XINPUT_GAMEPAD_X 0x4000
#define XINPUT_GAMEPAD_Y 0x8000
#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE 7849
#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE 8689
#define XINPUT_GAMEPAD_TRIGGER_THRESHOLD 30

typedef struct XINPUT_GAMEPAD
{
  u16 wButtons;
  u8 bLeftTrigger;
  u8 bRightTrigger;
  i16 sThumbLX;
  i16 sThumbLY;
  i16 sThumbRX;
  i16 sThumbRY;
} XINPUT_GAMEPAD;

typedef struct XINPUT_STATE
{
  u32 dwPacketNumber;
  XINPUT_GAMEPAD Gamepad;
} XINPUT_STATE;

typedef u32(__stdcall *XInputGetStateFunc)(u32 dwUserIndex, XINPUT_STATE *pState);
static XInputGetStateFunc XInputGetState = 0;

/* #############################################################################
 * # [SECTION] WIN32 specifiy functions
 * #############################################################################
 */
SHADE_IT_API void win32_print(s8 *str)
{
  static u32 written;
  static void *log_file;

  if (!log_file)
  {
    log_file = CreateFileA("shade_it.log", GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
  }

  {
    s8 *p = str;
    u32 len = 0;

    while (*p++)
    {
      len++;
    }

    WriteFile(log_file, str, len, &written, 0);
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
    hFile = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, 0);

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
  return GetFileAttributesExA(file, 0, &fad) ? fad.ftLastWriteTime : empty;
}

SHADE_IT_API SHADE_IT_INLINE u8 win32_enable_high_priority(void)
{
  /* TODO(nickscha): Check integrated plus discrete GPU
   *
   * It was noticed that on a device with a integrated GPU (intel)
   * and a discrete GPU (NVIDIA) the fans were spinning high even
   * though there was only 1.5% total CPU and 2.4% GPU usage.
   * Check carefully when these priority functions can be set safely.
   *
  if (!SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS))
  {
    return 1;
  }

  if (!SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST))
  {
    return 1;
  }

  if (!SetThreadExecutionState(ES_CONTINUOUS | ES_DISPLAY_REQUIRED | ES_SYSTEM_REQUIRED))
  {
    return 1;
  }
  */
  (void)HIGH_PRIORITY_CLASS;
  (void)THREAD_PRIORITY_HIGHEST;
  (void)ES_CONTINUOUS;
  (void)ES_DISPLAY_REQUIRED;
  (void)ES_SYSTEM_REQUIRED;

  return 1;
}

SHADE_IT_API SHADE_IT_INLINE u8 win32_enable_dpi_awareness(void)
{
  /* Try Windows 10 / 11 (Per-Monitor V2) */
  void *user32 = GetModuleHandleA("user32.dll");

  void *shcore;

  if (user32)
  {
    typedef i32(__stdcall * SetProcessDpiAwarenessContextProc)(void *);
    SetProcessDpiAwarenessContextProc setProcessDpiAwarenessContext;

    *(void **)(&setProcessDpiAwarenessContext) = GetProcAddress(user32, "SetProcessDpiAwarenessContext");

    if (setProcessDpiAwarenessContext && setProcessDpiAwarenessContext((void *)-4)) /* DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2  */
    {
      return 1;
    }
  }

  shcore = LoadLibraryA("Shcore.dll");

  if (shcore)
  {
    typedef i32(__stdcall * SetProcessDpiAwarenessProc)(i32);
    SetProcessDpiAwarenessProc setDpiAwareness;

    *(void **)(&setDpiAwareness) = GetProcAddress(shcore, "SetProcessDpiAwareness");

    if (setDpiAwareness)
    {
      setDpiAwareness(2); /* PROCESS_PER_MONITOR_DPI_AWARE */
    }

    FreeLibrary(shcore);
  }
  else
  {
    SetProcessDPIAware();
  }

  return 1;
}

SHADE_IT_API SHADE_IT_INLINE u8 win32_enable_high_resolution_timer(void)
{
  void *winmm = LoadLibraryA("Winmm.dll");

  if (winmm)
  {
    typedef u32(__stdcall * timeBeginPeriodProc)(u32);
    timeBeginPeriodProc timeBeginPeriod;

    u32 res = 0;

    *(void **)(&timeBeginPeriod) = GetProcAddress(winmm, "timeBeginPeriod");

    if (!timeBeginPeriod)
    {
      return 0;
    }

    res = timeBeginPeriod(1);

    FreeLibrary(winmm);

    /* TIMERR_NOCANDO */
    if (res == 97)
    {
      return 0;
    }
  }

  return 1;
}

SHADE_IT_API i32 win32_process_thread_count(void)
{
  u32 pid = GetCurrentProcessId();
  void *snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
  THREADENTRY32 te;
  i32 count = 0;

  if (snapshot == INVALID_HANDLE)
  {
    return 0;
  }

  te.dwSize = sizeof(te);

  if (Thread32First(snapshot, &te))
  {
    do
    {
      if (te.th32OwnerProcessID == pid)
      {
        count++;
      }
    } while (Thread32Next(snapshot, &te));
  }

  CloseHandle(snapshot);

  return count;
}

#define KEYS_COUNT 256

typedef struct win32_controller_state
{

  u8 button_a;
  u8 button_b;
  u8 button_x;
  u8 button_y;

  u8 shoulder_left;
  u8 shoulder_right;

  u8 trigger_left;
  u8 trigger_right;

  u8 dpad_up;
  u8 dpad_down;
  u8 dpad_left;
  u8 dpad_right;

  u8 stick_left;
  u8 stick_right;

  u8 start;
  u8 back;

  f32 stick_left_x;
  f32 stick_left_y;
  f32 stick_right_x;
  f32 stick_right_y;

  f32 trigger_left_value;
  f32 trigger_right_value;

  u8 id; /* The XInput id associated with this controller */
  u8 connected;
  u8 check_needed; /* If a device is plugged in or disconnected we should check XInput controller state again */

} win32_controller_state;

SHADE_IT_API u8 xinput_load(void)
{
  void *xinput_lib = LoadLibraryA("xinput1_4.dll");

  if (!xinput_lib)
  {
    xinput_lib = LoadLibraryA("xinput1_3.dll");
  }

  if (!xinput_lib)
  {
    xinput_lib = LoadLibraryA("xinput9_1_0.dll");
  }

  if (!xinput_lib)
  {
    return 0;
  }

  *(void **)(&XInputGetState) = GetProcAddress(xinput_lib, "XInputGetState");

  return 1;
}

SHADE_IT_API f32 xinput_process_thumbstick(i16 value, i16 deadzone)
{
  f32 result = 0.0f;

  if (value > deadzone)
  {
    result = (f32)(value - deadzone) / (32767.0f - deadzone);
  }
  else if (value < -deadzone)
  {
    result = (f32)(value + deadzone) / (32768.0f - deadzone);
  }

  return result;
}

SHADE_IT_API SHADE_IT_INLINE f32 xinput_process_trigger(u8 value)
{
  return value > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? (f32)value / 255.0f : 0.0f;
}

typedef struct process_memory_info
{
  u64 private_bytes; /* Commit charge (what you asked for) */
  u64 working_set;   /* RAM currently used */
  u64 peak_working_set;
} process_memory_info;

u8 win32_process_memory(process_memory_info *out)
{
  typedef i32(__stdcall * GetProcessMemoryInfo_Fn)(void *, PROCESS_MEMORY_COUNTERS_EX *, u32);
  static GetProcessMemoryInfo_Fn pGetMemInfo = 0;
  static i32 initialized = 0;

  PROCESS_MEMORY_COUNTERS_EX pmc;

  if (!initialized)
  {
    /* Win7+ */
    void *kernel32 = LoadLibraryA("kernel32.dll");

    if (kernel32)
    {
      *(void **)(&pGetMemInfo) = GetProcAddress(kernel32, "K32GetProcessMemoryInfo");
    }

    /* Vista and older */
    if (!pGetMemInfo)
    {
      void *psapi = LoadLibraryA("psapi.dll");

      if (psapi)
      {
        *(void **)(&pGetMemInfo) = GetProcAddress(psapi, "GetProcessMemoryInfo");
      }
    }

    initialized = 1;
  }

  if (!pGetMemInfo)
  {
    return 0;
  }

  pmc.cb = sizeof(pmc);

  if (!pGetMemInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
  {
    return 0;
  }

  out->private_bytes = (u64)pmc.PrivateUsage;
  out->working_set = (u64)pmc.WorkingSetSize;
  out->peak_working_set = (u64)pmc.PeakWorkingSetSize;

  return 1;
}

typedef struct win32_shade_it_state
{

  u32 window_width;
  u32 window_height;

  u32 window_width_pending;
  u32 window_height_pending;

  f32 window_clear_color_g;
  f32 window_clear_color_b;
  f32 window_clear_color_r;
  f32 window_clear_color_a;

  i32 iFrame;        /* Frames processed count               */
  f64 iTime;         /* Total elapsed time in seconds        */
  f64 iTimeDelta;    /* Current render frame time in seconds */
  f64 iFrameRate;    /* Frame Rate per second                */
  f64 iFrameRateRaw; /* Frame Rate per second raw (no cap)   */

  u8 running;
  u8 window_minimized;
  u8 window_size_changed;

  u8 shader_paused;
  u8 ui_enabled;
  u8 fullscreen_enabled;
  u8 borderless_enabled;
  u8 screen_recording_enabled;
  u8 screen_recording_initialized;

  u32 target_frames_per_second;

  s8 *window_title;

  void *window_handle;
  void *device_context;

  /* Input state */
  i32 mouse_dx; /* Relative movement delta for x  */
  i32 mouse_dy; /* Relative movement delta for y  */
  i32 mouse_x;  /* Mouse position on screen for x */
  i32 mouse_y;  /* Mouse position on screen for y */

  /* State Examples:
    Key Pressed:  state.keys_is_down[0x0D] && !state.keys_was_down[0x0D]
    Key Released: !state.keys_is_down[0x0D] && state.keys_was_down[0x0D]

    Example of a Toggle switch (when pressed first toggles on, when pressed second time toggles off):

    static u8 ui_enabled = 0;

    if (state.keys_is_down[0x70] && !state.keys_was_down[0x70])
    {
      ui_enabled = !ui_enabled;
    }
  */
  u8 keys_is_down[KEYS_COUNT];
  u8 keys_was_down[KEYS_COUNT];

  win32_controller_state controller;

  s8 *gl_version;
  s8 *gl_renderer;
  s8 *gl_vendor;

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

    /* Setup raw input for mouse and keyboard */
    {
      RAWINPUTDEVICE rid[2] = {0};

      (void)RIDEV_INPUTSINK; /* Receive input even when not focused */

      rid[0].usUsagePage = 0x01;
      rid[0].usUsage = 0x06; /* Keyboard */
      rid[0].dwFlags = 0;    /* Receive input only when focused */
      rid[0].hwndTarget = window;

      rid[1].usUsagePage = 0x01;
      rid[1].usUsage = 0x02; /* Mouse */
      rid[1].dwFlags = 0;    /* Receive input only when focused */
      rid[1].hwndTarget = window;

      if (!RegisterRawInputDevices(rid, 2, sizeof(rid[0])))
      {
        win32_print("[win32] Failed to register RAWINPUT device\n");
      }
    }
  }
  break;
  case WM_CLOSE:
  case WM_QUIT:
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
      state->window_minimized = 1;
    }
    else
    {
      state->window_minimized = 0;
      state->window_size_changed = 1;
      state->window_width_pending = (u16)(((u64)(lParam)) & 0xffff);          /* Low Word  */
      state->window_height_pending = (u16)((((u64)(lParam)) >> 16) & 0xffff); /* High Word */
    }
  }
  break;
  case WM_INPUT:
  {
    static u8 rawBuffer[128];
    RAWINPUT *raw = (RAWINPUT *)rawBuffer;

    u32 dwSize = 0;

    if (!state)
    {
      break;
    }

    GetRawInputData((RAWINPUT *)lParam, RID_INPUT, (void *)0, &dwSize, sizeof(RAWINPUTHEADER));

    if (dwSize > sizeof(rawBuffer) ||
        GetRawInputData((RAWINPUT *)lParam, RID_INPUT, raw, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
    {
      return result;
    }

    if (raw->header.dwType == RIM_TYPEKEYBOARD)
    {
      RAWKEYBOARD *keyboard = &raw->data.keyboard;

      u16 vKey = keyboard->VKey;

      if (vKey < KEYS_COUNT)
      {
        /*key->was_down = key->is_down;*/
        state->keys_is_down[vKey] = !(keyboard->Flags & RI_KEY_BREAK); /* 1 if pressed, 0 if released */
      }
    }
    else if (raw->header.dwType == RIM_TYPEMOUSE)
    {
      RAWMOUSE *mouse = &raw->data.mouse;

      i32 dx = mouse->lLastX;
      i32 dy = mouse->lLastY;

      state->mouse_dx += dx;
      state->mouse_dy += dy;
    }
  }
  break;
  case WM_DEVICECHANGE:
  {
    /* Check if a device notification arrived in order to find out when to requery XInput controller states */
    /* DBT_DEVNODES_CHANGED is the most reliable for USB plugging/unplugging */
    if (wParam == DBT_DEVNODES_CHANGED || wParam == DBT_DEVICEARRIVAL || wParam == DBT_DEVICEREMOVECOMPLETE)
    {
      state->controller.check_needed = 1;
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

static WINDOWPLACEMENT g_wpPrev = {0};

SHADE_IT_API void win32_window_enter_fullscreen(win32_shade_it_state *state)
{
  i32 dwStyle = GetWindowLongA(state->window_handle, GWL_STYLE);

  if (dwStyle & WS_OVERLAPPEDWINDOW)
  {
    if (GetWindowPlacement(state->window_handle, &g_wpPrev))
    {
      MONITORINFO mi;
      mi.cbSize = sizeof(mi);

      GetMonitorInfoA(MonitorFromWindow(state->window_handle, MONITOR_DEFAULTTONEAREST), &mi);
      SetWindowLongA(state->window_handle, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);

      SetWindowPos(
          state->window_handle, HWND_TOP,
          mi.rcMonitor.left, mi.rcMonitor.top,
          mi.rcMonitor.right - mi.rcMonitor.left,
          mi.rcMonitor.bottom - mi.rcMonitor.top,
          SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_SHOWWINDOW);

      state->window_width_pending = (u32)(mi.rcMonitor.right - mi.rcMonitor.left);
      state->window_height_pending = (u32)(mi.rcMonitor.bottom - mi.rcMonitor.top);
      state->window_size_changed = 1;
    }
  }
}

SHADE_IT_API void win32_window_enter_borderless(win32_shade_it_state *state)
{
  if (GetWindowPlacement(state->window_handle, &g_wpPrev))
  {
    i32 dwStyle = GetWindowLongA(state->window_handle, GWL_STYLE);

    MONITORINFO mi;
    mi.cbSize = sizeof(mi);

    GetMonitorInfoA(MonitorFromWindow(state->window_handle, MONITOR_DEFAULTTONEAREST), &mi);
    SetWindowLongA(state->window_handle, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);

    SetWindowPos(
        state->window_handle, HWND_TOP,
        mi.rcMonitor.left, mi.rcMonitor.top,
        mi.rcMonitor.right - mi.rcMonitor.left,
        mi.rcMonitor.bottom - mi.rcMonitor.top,
        SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_SHOWWINDOW);

    state->window_width_pending = (u32)(mi.rcMonitor.right - mi.rcMonitor.left);
    state->window_height_pending = (u32)(mi.rcMonitor.bottom - mi.rcMonitor.top);
    state->window_size_changed = 1;
  }
}

SHADE_IT_API void win32_window_enter_windowed(win32_shade_it_state *state)
{
  i32 dwStyle = GetWindowLongA(state->window_handle, GWL_STYLE);

  if (!(dwStyle & WS_OVERLAPPEDWINDOW))
  {
    RECT rect;

    SetWindowLongA(state->window_handle, GWL_STYLE, WS_OVERLAPPEDWINDOW);
    SetWindowPlacement(state->window_handle, &g_wpPrev);
    SetWindowPos(state->window_handle, (void *)0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_SHOWWINDOW);
    GetClientRect(state->window_handle, &rect);

    state->window_width_pending = (u32)(rect.right - rect.left);
    state->window_height_pending = (u32)(rect.bottom - rect.top);
    state->window_size_changed = 1;
  }
  else
  {
    /* resize windowed mode */
    RECT rect = {0};
    rect.right = (i32)state->window_width;
    rect.bottom = (i32)state->window_height;

    AdjustWindowRect(&rect, (u32)GetWindowLongA(state->window_handle, GWL_STYLE), 0);
    SetWindowPos(state->window_handle, (void *)0, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
  }
}

/* #############################################################################
 * # [SECTION] Font Loading and Parsing
 * #############################################################################
 */
/* 1-bit bitmap, packed, row-major */
/* width=210, height=7 */
/* Charset: "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789:%+-.<" */
#define SHADE_IT_FONT_WIDTH 215
#define SHADE_IT_FONT_HEIGHT 7
#define SHADE_IT_FONT_GLYPH_WIDTH 5
#define SHADE_IT_FONT_GLYPH_HEIGHT 7

static u8 shade_it_font[] = {
    0x77, 0x9D, 0xCF, 0xFD, 0xD1, 0x73, 0xE3, 0x08, 0xE5, 0xDE, 0x77, 0x9D,
    0xF8, 0xC6, 0x31, 0x8F, 0xDC, 0x47, 0x7A, 0x5F, 0x77, 0xDC, 0xE0, 0x64,
    0x00, 0x00, 0x05, 0x18, 0xC6, 0x50, 0x84, 0x62, 0x41, 0x4A, 0x1B, 0xCC,
    0x63, 0x18, 0xC4, 0x91, 0x8C, 0x63, 0x10, 0xC5, 0x91, 0x0C, 0xA1, 0x10,
    0xC6, 0x20, 0xD0, 0x48, 0x00, 0x1A, 0x31, 0x84, 0x61, 0x08, 0x44, 0x82,
    0xA4, 0x2B, 0x58, 0xC6, 0x31, 0x81, 0x23, 0x18, 0xA9, 0x42, 0x99, 0x02,
    0x19, 0x42, 0x02, 0x8C, 0x40, 0x21, 0x10, 0x00, 0x77, 0xFD, 0x08, 0xFB,
    0xD7, 0xF9, 0x05, 0x88, 0x56, 0xB1, 0xF4, 0x7C, 0xE2, 0x46, 0x35, 0x21,
    0x09, 0x52, 0x09, 0xDF, 0xF7, 0x88, 0xE7, 0x90, 0x84, 0xFB, 0xC1, 0xE8,
    0xC6, 0x11, 0x84, 0x23, 0x12, 0x4A, 0x90, 0x8D, 0x63, 0x0A, 0xCC, 0x24,
    0x8A, 0xAA, 0xA2, 0x23, 0x24, 0x20, 0x44, 0x18, 0x92, 0x21, 0x02, 0x10,
    0x40, 0x01, 0xD1, 0x8C, 0x65, 0x08, 0x46, 0x24, 0x94, 0xA1, 0x19, 0xC6,
    0x12, 0x8C, 0x49, 0x15, 0x3A, 0x24, 0x84, 0x48, 0x80, 0x88, 0x31, 0x24,
    0x42, 0x45, 0xC0, 0x80, 0x31, 0xA3, 0xE7, 0x73, 0xF0, 0x74, 0x5C, 0xC8,
    0xFE, 0x33, 0x74, 0x1B, 0x17, 0x11, 0xC4, 0x54, 0x49, 0xF7, 0x3B, 0xFE,
    0x17, 0x9C, 0x47, 0x38, 0x13, 0x00, 0x00, 0x61, 0x00};

/* clang-format off */
/* Charset: "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789:%+-.<" */
SHADE_IT_API i32 font_char_to_glyph_index(s8 c)
{
  /* Convert to uppercase */
  if (c >= 'a' && c <= 'z')
  {
    c = (s8)(c - 'a' + 'A');
  }

  if (c >= 'A' && c <= 'Z') return c - 'A';
  if (c >= '0' && c <= '9') return 26 + (c - '0');
  if (c == ':') return 36;
  if (c == '%') return 37;
  if (c == '/') return 38;
  if (c == '+') return 39;
  if (c == '-') return 40;
  if (c == '.') return 41;
  if (c == '<') return 42;
  if (c == '>') return 42;

  return -1;
}
/* clang-format on */

SHADE_IT_API void unpack_1bit_to_8bit(
    u8 *dst, /* width * height bytes */
    u8 *src, /* packed bits */
    u32 width,
    u32 height)
{
  u32 x;
  u32 y;

  for (y = 0; y < height; ++y)
  {
    for (x = 0; x < width; ++x)
    {
      u32 bit_index = y * width + x;
      u32 byte_index = bit_index >> 3;
      u32 bit = 7 - (bit_index & 7);
      u8 b = (src[byte_index] >> bit) & 1;

      /* 1 = black, 0 = white */
      dst[bit_index] = b ? 0xFF : 0x00;
    }
  }
}

typedef struct text
{
  u32 size;
  u32 length;
  s8 *buffer;
} text;

SHADE_IT_API void text_append_str(text *src, s8 *s)
{
  u32 len = src->length;
  u32 cap = src->size;

  if (len >= cap)
  {
    return;
  }

  while (*s && (len + 1 < cap))
  {
    src->buffer[len++] = *s++;
  }

  src->buffer[len] = 0;
  src->length = len;
}

SHADE_IT_API void text_append_i32(text *src, i32 v)
{
  s8 tmp[12];
  i32 i = 0;
  u32 u;
  u32 len = src->length;
  u32 cap = src->size;

  if (len + 1 >= cap)
  {
    return;
  }

  if (v < 0)
  {
    src->buffer[len++] = '-';
    u = (u32)(-v);
  }
  else
  {
    u = (u32)v;
  }

  if (u == 0)
  {
    src->buffer[len++] = '0';
    src->buffer[len] = 0;
    src->length = len;
    return;
  }

  while (u && i < 12)
  {
    tmp[i++] = (s8)('0' + (u % 10));
    u /= 10;
  }

  while (i-- && (len + 1 < cap))
  {
    src->buffer[len++] = tmp[i];
  }

  src->buffer[len] = 0;
  src->length = len;
}

SHADE_IT_API void text_append_f64(text *src, f64 v, i32 decimals)
{
  i32 i;
  f64 frac;
  u32 len = src->length;
  u32 cap = src->size;

  if (len + 1 >= cap)
  {
    return;
  }

  if (v < 0.0)
  {
    src->buffer[len++] = '-';
    v = -v;
  }

  src->length = len;
  text_append_i32(src, (i32)v);
  len = src->length;

  if (len + 1 >= cap)
  {
    return;
  }

  src->buffer[len++] = '.';

  frac = v - (f64)((i32)v);

  for (i = 0; i < decimals && (len + 1 < cap); ++i)
  {
    frac *= 10.0;
    src->buffer[len++] = (s8)('0' + (i32)frac);
    frac -= (i32)frac;
  }

  src->buffer[len] = 0;
  src->length = len;
}

typedef struct glyph
{
  u16 x;
  u16 y;
  u16 packed_glyph_state; /* packs the glyph_index | (state_blink << 8); */
  u16 packed_color;       /* rgb565_color */
} glyph;

SHADE_IT_API u16 pack_rgb565(u8 r, u8 g, u8 b)
{
  return (u16)(((r >> 3) << 11) |
               ((g >> 2) << 5) |
               ((b >> 3) << 0));
}

SHADE_IT_API u32 text_to_glyphs(
    s8 *text,
    glyph *out_glyphs,
    u32 max_glyphs,
    f32 start_x,
    f32 start_y,
    f32 font_scale)
{
  u32 count = 0;
  f32 x = start_x;
  f32 y = start_y;

  u16 default_color = pack_rgb565(255, 255, 255);

  f32 advance_x = (f32)(SHADE_IT_FONT_GLYPH_WIDTH + 1) * font_scale;
  f32 advance_y = ((f32)SHADE_IT_FONT_GLYPH_HEIGHT * font_scale) + (f32)SHADE_IT_FONT_GLYPH_HEIGHT;

  u8 blink = 0;
  u8 flip_vertical = 0;
  u8 flip_horizontal = 0;

  while (*text && count < max_glyphs)
  {
    s8 c = *text++;
    i32 glyph_index = font_char_to_glyph_index(c);

    if (c == '\n')
    {
      x = start_x;
      y += advance_y;
      blink = 0;
      flip_vertical = 0;
      flip_horizontal = 0;
      continue;
    }

    /* skip spaces explicitly */
    if (c == ' ')
    {
      x += advance_x;
      continue;
    }

    if (glyph_index < 0)
    {
      continue;
    }

    out_glyphs[count].x = (u16)x;
    out_glyphs[count].y = (u16)y;
    out_glyphs[count].packed_glyph_state = glyph_index | ((glyph_index == 42 ? 1 : blink) << 8) | (flip_vertical << 9) | ((c == '>' ? 1 : flip_horizontal) << 10);
    out_glyphs[count++].packed_color = default_color;

    x += advance_x;
  }

  return count;
}

/* #############################################################################
 * # [SECTION] OpenGL Context Creation and Shader Management
 * #############################################################################
 */
typedef struct shader_header
{
  u32 created;
  u32 program;
  u8 had_failure;

} shader_header;

typedef struct shader_main
{
  shader_header header;

  i32 loc_iResolution;
  i32 loc_iTime;
  i32 loc_iTimeDelta;
  i32 loc_iFrame;
  i32 loc_iFrameRate;
  i32 loc_iMouse;
  i32 loc_iTextureInfo;
  i32 loc_iTexture;
  i32 loc_iController;

} shader_main;

typedef struct shader_font
{
  shader_header header;

  i32 loc_iResolution;
  i32 loc_iTime;
  i32 loc_iTextureInfo;
  i32 loc_iTexture;
  i32 loc_iFontScale;

} shader_font;

typedef struct shader_recording
{
  shader_header header;

  i32 loc_iResolution;
  i32 loc_iTime;

} shader_recording;

static s8 shader_info_log[1024];

static u32 opengl_failed_function_load_count = 0;

SHADE_IT_API PROC opengl_load_function(s8 *name)
{
  PROC gl_function = wglGetProcAddress(name);

  /* Some GPU drivers do not return a valid null pointer if requested OpenGL function is not available */
  if (gl_function == (PROC)0 || gl_function == (PROC)0x1 || gl_function == (PROC)0x2 || gl_function == (PROC)0x3 || gl_function == (PROC)-1)
  {
    /* Try falling back to opengl32 */
    static void *gl_lib = 0;
    void *object_ptr;

    if (!gl_lib)
    {
      gl_lib = GetModuleHandleA("opengl32.dll");
    }

    object_ptr = (void *)GetProcAddress(gl_lib, name);

    gl_function = *(PROC *)&object_ptr;
  }

  if (gl_function == (PROC)0)
  {
    win32_print("[opengl] \"");
    win32_print(name);
    win32_print("\" not found!\n");

    opengl_failed_function_load_count++;
  }

  return gl_function;
}

SHADE_IT_API SHADE_IT_INLINE i32 opengl_create_context(win32_shade_it_state *state)
{
  void *window_instance = GetModuleHandleA(0);
  WNDCLASSA window_class = {0};
  u32 window_style = WS_CAPTION | WS_SYSMENU | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME;
  RECT rect = {0};

  void *fake_window;
  void *fake_device_context;
  void *fake_rc;
  i32 fake_pixel_format;
  PIXELFORMATDESCRIPTOR fake_pfd = {0};

  window_class.style = CS_OWNDC;
  window_class.lpfnWndProc = win32_window_callback;
  window_class.hInstance = window_instance;
  window_class.hCursor = LoadCursorA(0, IDC_ARROW);
  window_class.hIcon = LoadIconA(window_instance, MAKEINTRESOURCEA(1));
  window_class.hbrBackground = 0;
  window_class.lpszClassName = state->window_title;

  if (!RegisterClassA(&window_class))
  {
    return 0;
  }

  fake_window = CreateWindowExA(
      0,
      window_class.lpszClassName,
      window_class.lpszClassName,
      WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
      0, 0,
      1, 1,
      0, 0,
      window_instance, 0);

  if (!fake_window)
  {
    return 0;
  }

  fake_device_context = GetDC(fake_window);

  fake_pfd.nSize = sizeof(fake_pfd);
  fake_pfd.nVersion = 1;
  fake_pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  fake_pfd.iPixelType = PFD_TYPE_RGBA;
  fake_pfd.cColorBits = 32;
  fake_pfd.cAlphaBits = 8;
  fake_pfd.cDepthBits = 24;

  fake_pixel_format = ChoosePixelFormat(fake_device_context, &fake_pfd);

  if (!fake_pixel_format || !SetPixelFormat(fake_device_context, fake_pixel_format, &fake_pfd))
  {
    return 0;
  }

  fake_rc = wglCreateContext(fake_device_context);

  if (!fake_rc || !wglMakeCurrent(fake_device_context, fake_rc))
  {
    return 0;
  }

  rect.right = (i32)state->window_width;
  rect.bottom = (i32)state->window_height;
  AdjustWindowRect(&rect, window_style, 0);

  state->window_handle = CreateWindowExA(
      0,
      window_class.lpszClassName,
      window_class.lpszClassName,
      window_style,
      0, 0,
      rect.right - rect.left,
      rect.bottom - rect.top,
      0, 0,
      window_instance,
      state /* Pass pointer to user data to the window callback */
  );

  /* Modal window */
  SetWindowPos(state->window_handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

  state->device_context = GetDC(state->window_handle);

#ifdef _MSC_VER
#pragma warning(disable : 4068)
#endif
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
  /* Core WGL functions */
  wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)opengl_load_function("wglChoosePixelFormatARB");
  wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)opengl_load_function("wglCreateContextAttribsARB");
  wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)opengl_load_function("wglSwapIntervalEXT");

  /* OpenGL 1.1+ Functions that are part of the GPU driver rather than opengl32.dll */
  glCreateShader = (PFNGLCREATESHADERPROC)opengl_load_function("glCreateShader");
  glCreateProgram = (PFNGLCREATEPROGRAMPROC)opengl_load_function("glCreateProgram");
  glDeleteProgram = (PFNGLDELETEPROGRAMPROC)opengl_load_function("glDeleteProgram");
  glAttachShader = (PFNGLATTACHSHADERPROC)opengl_load_function("glAttachShader");
  glShaderSource = (PFNGLSHADERSOURCEPROC)opengl_load_function("glShaderSource");
  glCompileShader = (PFNGLCOMPILESHADERPROC)opengl_load_function("glCompileShader");
  glGetShaderiv = (PFNGLGETSHADERIVPROC)opengl_load_function("glGetShaderiv");
  glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)opengl_load_function("glGetShaderInfoLog");
  glLinkProgram = (PFNGLLINKPROGRAMPROC)opengl_load_function("glLinkProgram");
  glGetProgramiv = (PFNGLGETPROGRAMIVPROC)opengl_load_function("glGetProgramiv");
  glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)opengl_load_function("glGetProgramInfoLog");
  glDeleteShader = (PFNGLDELETESHADERPROC)opengl_load_function("glDeleteShader");
  glDrawArrays = (PFNGLDRAWARRAYSPROC)opengl_load_function("glDrawArrays");
  glUseProgram = (PFNGLUSEPROGRAMPROC)opengl_load_function("glUseProgram");
  glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)opengl_load_function("glGenVertexArrays");
  glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)opengl_load_function("glBindVertexArray");
  glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)opengl_load_function("glGetUniformLocation");
  glUniform1f = (PFNGLUNIFORM1FPROC)opengl_load_function("glUniform1f");
  glUniform1i = (PFNGLUNIFORM1IPROC)opengl_load_function("glUniform1i");
  glUniform3f = (PFNGLUNIFORM3FPROC)opengl_load_function("glUniform3f");
  glUniform4f = (PFNGLUNIFORM4FPROC)opengl_load_function("glUniform4f");
  glUniform4fv = (PFNGLUNIFORM4FVPROC)opengl_load_function("glUniform4fv");
  glActiveTexture = (PFNGLACTIVETEXTUREPROC)opengl_load_function("glActiveTexture");
  glGenBuffers = (PFNGLGENBUFFERSPROC)opengl_load_function("glGenBuffers");
  glBindBuffer = (PFNGLBINDBUFFERPROC)opengl_load_function("glBindBuffer");
  glBufferData = (PFNGLBUFFERDATAPROC)opengl_load_function("glBufferData");
  glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)opengl_load_function("glEnableVertexAttribArray");
  glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)opengl_load_function("glVertexAttribPointer");
  glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC)opengl_load_function("glVertexAttribIPointer");
  glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC)opengl_load_function("glVertexAttribDivisor");
  glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCED)opengl_load_function("glDrawArraysInstanced");

#pragma GCC diagnostic pop

  if (opengl_failed_function_load_count > 0)
  {
    win32_print("[opengl] Some of the required OpenGL functions are not available on your machine (see log file above)!\n");
    return 0;
  }

  /* Set Pixel Format */
  {

    i32 pixel_attributes[] = {
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

    i32 pixel_format_id;
    u32 num_formats;

    if (!wglChoosePixelFormatARB(state->device_context, pixel_attributes, 0, 1, &pixel_format_id, &num_formats) || !num_formats)
    {
      return 0;
    }

    SetPixelFormat(state->device_context, pixel_format_id, 0);
  }

  /* Create the OpenGL context */
  {
    i32 context_attributes[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0};

    void *rc = wglCreateContextAttribsARB(state->device_context, 0, context_attributes);

    wglMakeCurrent(0, 0);
    wglDeleteContext(fake_rc);
    ReleaseDC(fake_window, fake_device_context);
    DestroyWindow(fake_window);

    if (!rc || !wglMakeCurrent(state->device_context, rc))
    {
      return 0;
    }
  }

  /* Disable VSync */
  if (wglSwapIntervalEXT)
  {
    wglSwapIntervalEXT(0);
  }

  /* Print opengl information */
  state->gl_vendor = (s8 *)glGetString(GL_VENDOR);
  state->gl_renderer = (s8 *)glGetString(GL_RENDERER);
  state->gl_version = (s8 *)glGetString(GL_VERSION);

  win32_print("[opengl] vendor  : ");
  win32_print(state->gl_vendor);
  win32_print("\n");

  win32_print("[opengl] renderer: ");
  win32_print(state->gl_renderer);
  win32_print("\n");

  win32_print("[opengl] version : ");
  win32_print(state->gl_version);
  win32_print("\n");

  return 1;
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
    glGetShaderInfoLog(shaderId, 1024, 0, shader_info_log);

    win32_print("[opengl] shader compilation error:\n");
    win32_print(shader_info_log);
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

  if (fragment_shader_id == -1)
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
    glGetProgramInfoLog(*shader_program, 1024, 0, shader_info_log);

    win32_print("[opengl] program creation error:\n");
    win32_print(shader_info_log);
    win32_print("\n");

    return 0;
  }

  return 1;
}

SHADE_IT_API u32 opengl_shader_load(shader_header *shader, s8 *shader_code_vertex, s8 *shader_code_fragment)
{
  u32 new_program;

  if (!opengl_shader_create(&new_program, shader_code_vertex, shader_code_fragment))
  {
    win32_print("[opengl] compile failed, keeping old shader is present\n");
    shader->had_failure = 1;
    return 0;
  }

  shader->had_failure = 0;

  /* If there has been already a shader created delete the old one */
  if (shader->created)
  {
    glDeleteProgram(shader->program);
  }

  shader->program = new_program;

  glUseProgram(shader->program);

  shader->created = 1;

  return 1;
}

static s8 *shader_code_vertex =
    "#version 330 core\n"
    "vec2 quad[3]=vec2[3]("
    "vec2(-1.0,-1.0),"
    "vec2(3.0,-1.0),"
    "vec2(-1.0,3.0)"
    ");"
    "void main(){gl_Position=vec4(quad[gl_VertexID],0.0,1.0);}";

SHADE_IT_API void opengl_shader_load_shader_main(shader_main *shader, s8 *shader_file_name)
{

  u32 size = 0;
  u8 *shader_code_fragment = win32_file_read(shader_file_name, &size);

  if (!shader_code_fragment || size < 1)
  {
    return;
  }

  if (opengl_shader_load(&shader->header, shader_code_vertex, (s8 *)shader_code_fragment))
  {
    shader->loc_iResolution = glGetUniformLocation(shader->header.program, "iResolution");
    shader->loc_iTime = glGetUniformLocation(shader->header.program, "iTime");
    shader->loc_iTimeDelta = glGetUniformLocation(shader->header.program, "iTimeDelta");
    shader->loc_iFrame = glGetUniformLocation(shader->header.program, "iFrame");
    shader->loc_iFrameRate = glGetUniformLocation(shader->header.program, "iFrameRate");
    shader->loc_iMouse = glGetUniformLocation(shader->header.program, "iMouse");
    shader->loc_iTextureInfo = glGetUniformLocation(shader->header.program, "iTextureInfo");
    shader->loc_iTexture = glGetUniformLocation(shader->header.program, "iTexture");
    shader->loc_iController = glGetUniformLocation(shader->header.program, "iController");
  }

  VirtualFree(shader_code_fragment, 0, MEM_RELEASE);
}

SHADE_IT_API void opengl_shader_load_shader_font(shader_font *shader)
{
  static s8 *shader_font_code_vertex =
      "#version 330 core\n"
      "layout(location=0)in vec2 p;"
      "layout(location=1)in uvec4 g;"
      "uniform vec3 r;"
      "uniform vec4 t;"
      "uniform float s;"
      "out vec2 vUV;"
      "out vec3 vC;"
      "flat out uint b;"
      "void main(){"
      "float i=g.z&255u,C=t.x/t.z;"
      "b=(g.z>>8)&1u;"
      "float v=(g.z>>9)&1u,h=(g.z>>10)&1u;"
      "vec2 Q=vec2(p.x*(1.-2.*h)+h,p.y*(1.-2.*v)+v);"
      "vec2 p2=vec2(g.xy)+Q*t.zw*s;"
      "vec2 N=p2/r.xy*2.-1.;"
      "gl_Position=vec4(N.x,-N.y,0,1);"
      "vUV=vec2((mod(i,C)+p.x)*t.z/t.x,(floor(i/C)+p.y)*t.w/t.y);"
      "uint K=g.w;"
      "vC=vec3((K>>11&31u)/31.,(K>>5&63u)/63.,(K&31u)/31.);"
      "}";

  static s8 *shader_font_code_fragment =
      "#version 330 core\n"
      "in vec2 vUV;"
      "in vec3 vC;"
      "flat in uint b;"
      "uniform sampler2D iTexture;"
      "uniform float iTime;"
      "out vec4 F;"
      "void main(){"
      "float a=texture(iTexture,vUV).r;"
      "if(b==1u&&fract(iTime)<.5)a=0.;" /* Blink Support */
      "F=vec4(vC,a);"
      "}";

  if (opengl_shader_load(&shader->header, shader_font_code_vertex, shader_font_code_fragment))
  {
    shader->loc_iResolution = glGetUniformLocation(shader->header.program, "r");
    shader->loc_iTextureInfo = glGetUniformLocation(shader->header.program, "t");
    shader->loc_iFontScale = glGetUniformLocation(shader->header.program, "s");
    shader->loc_iTime = glGetUniformLocation(shader->header.program, "iTime");
    shader->loc_iTexture = glGetUniformLocation(shader->header.program, "iTexture");
  }
}

SHADE_IT_API void opengl_shader_load_shader_recording(shader_recording *shader)
{
  static s8 *shader_code_fragment =
      "#version 330 core\n"
      "out vec4 FragColor;"
      "uniform float iTime;"
      "uniform vec3 iRes;"
      "void main()"
      "{"
      "float r=10.0;"
      "float m=10.0;"
      "vec2 p=gl_FragCoord.xy;"
      "vec2 c=vec2(iRes.x-r-m, r+m);"
      "float d=length(p-c);"
      "float blink=0.5+0.5*sin(iTime*12.0);"
      "float b=4.0;"
      "if ((d<=r&&blink>0.5)||(p.x<b||p.y<b||p.x>=iRes.x-b||p.y>=iRes.y-b))"
      " FragColor=vec4(1.0,0.0,0.0,blink);"
      "else"
      " discard;"
      "}";

  if (opengl_shader_load(&shader->header, shader_code_vertex, shader_code_fragment))
  {
    shader->loc_iResolution = glGetUniformLocation(shader->header.program, "iRes");
    shader->loc_iTime = glGetUniformLocation(shader->header.program, "iTime");
  }
}

/* #############################################################################
 * # [SECTION] Main Entry Point
 * #############################################################################
 */
SHADE_IT_API i32 start(i32 argc, u8 **argv)
{
  /* Default fragment shader file name to load if no file is passed as an argument in cli */
  s8 *fragment_shader_file_name = (argv && argc > 1) ? (s8 *)argv[1] : "shade_it.fs";

  win32_shade_it_state state = {0};
  shader_main main_shader = {0};
  shader_font font_shader = {0};
  shader_recording recording_shader = {0};

  u32 main_vao;
  u32 font_vao;
  u32 glyph_vbo;

  state.running = 1;
  state.window_title = "shade_it v0.7 (F1=Debug UI, F2=Screen Recording, R=Reset, P=Pause, F9=Borderless, F11=Fullscreen)";
  state.window_width = 800;
  state.window_height = 600;
  state.window_clear_color_r = 0.5f;
  state.target_frames_per_second = 60; /* 60 FPS, 0 = unlimited */
  state.controller.check_needed = 1;   /* By default we have to query first XInput state */

  /******************************/
  /* Set Process Priorities     */
  /******************************/
  if (!win32_enable_high_priority())
  {
    win32_print("[WARNING] Failed to set high priority process\n");
  }

  /******************************/
  /* Set DPI aware mode         */
  /******************************/
  if (!win32_enable_dpi_awareness())
  {
    win32_print("[WARNING] Cannot set DPI awareness\n");
  }

  /******************************/
  /* HighRes timer for Sleep(1) */
  /******************************/
  if (!win32_enable_high_resolution_timer())
  {
    win32_print("[WARNING] Cannot set win32 high resolution timer using Winmm.dll (timeBeginPeriod)\n");
  }

  /******************************/
  /* Load XInput Controller     */
  /******************************/
  if (!xinput_load())
  {
    win32_print("[WARNING] Could not load XInput (xinput1_4.dll, xinput1_3.dll or xinput9_1_0.dll)! XInput gamepads/controllers (e.g. XBOX) are not functional.\n");
  }

  /******************************/
  /* Window and OpenGL context  */
  /******************************/
  if (!opengl_create_context(&state))
  {
    win32_print("[ERROR] Could not create opengl context!\n");
    return 1;
  }

  /* Avoid clear color flickering */
  glViewport(0, 0, (i32)state.window_width, (i32)state.window_height);
  glClearColor(state.window_clear_color_r, state.window_clear_color_g, state.window_clear_color_b, state.window_clear_color_a);
  glDisable(GL_FRAMEBUFFER_SRGB);
  glDisable(GL_MULTISAMPLE);
  glClear(GL_COLOR_BUFFER_BIT);

  SwapBuffers(state.device_context);

  /* Make the window visible */
  ShowWindow(state.window_handle, SW_SHOW);

  /******************************/
  /* Initialize Shaders         */
  /******************************/
  {
    /* Generate a dummy vao with no buffer */
    glGenVertexArrays(1, &main_vao);
    glBindVertexArray(main_vao);

    /* Load Fragment Shader source code from file */
    win32_print("[opengl] load shader file: ");
    win32_print(fragment_shader_file_name);
    win32_print("\n");

    opengl_shader_load_shader_main(&main_shader, fragment_shader_file_name);
    opengl_shader_load_shader_font(&font_shader);
    opengl_shader_load_shader_recording(&recording_shader);
  }

  /******************************/
  /* Initialize Font Texture    */
  /******************************/
  {
    /* Generate font texture */
    u8 shade_it_font_pixels[SHADE_IT_FONT_WIDTH * SHADE_IT_FONT_HEIGHT];
    u32 tex;

    /* OpenGL does not allow 1bit packed texture data so we convert each bit to 1 byte */
    unpack_1bit_to_8bit(shade_it_font_pixels, shade_it_font, SHADE_IT_FONT_WIDTH, SHADE_IT_FONT_HEIGHT);

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, SHADE_IT_FONT_WIDTH, SHADE_IT_FONT_HEIGHT, 0, GL_RED, GL_UNSIGNED_BYTE, shade_it_font_pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glActiveTexture(GL_TEXTURE0);
  }

  /******************************/
  /* Initialize Font Buffers    */
  /******************************/
  {
    static f32 quad_vertices[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f};

    u32 quad_vbo;

    glGenVertexArrays(1, &font_vao);
    glBindVertexArray(font_vao);

    glGenBuffers(1, &quad_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);

    /* pos (location = 0) */
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(f32), (void *)0);
    glVertexAttribDivisor(0, 0);

    glGenBuffers(1, &glyph_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, glyph_vbo);

    /* iGlyph (location = 1) */
    glEnableVertexAttribArray(1);
    glVertexAttribIPointer(1, 4, GL_UNSIGNED_SHORT, sizeof(glyph), (void *)0);
    glVertexAttribDivisor(1, 1);
  }

  {
    i64 perf_freq;
    i64 time_start;
    i64 time_start_fps_cap;
    i64 time_last;

    i32 thread_count = win32_process_thread_count();

    FILETIME fs_last = win32_file_mod_time(fragment_shader_file_name);

    QueryPerformanceFrequency(&perf_freq);
    QueryPerformanceCounter(&time_start);
    QueryPerformanceCounter(&time_start_fps_cap);

    time_last = time_start;

    while (state.running)
    {
      i64 time_now;

      /******************************/
      /* Timing                     */
      /******************************/
      {
        QueryPerformanceCounter(&time_now);

        state.iTimeDelta = (f64)(time_now - time_last) / (f64)perf_freq;
        state.iTime = (f64)(time_now - time_start) / (f64)perf_freq;

        time_last = time_now;

        if (state.iTimeDelta > 0.0)
        {
          state.iFrameRate = 1.0 / state.iTimeDelta;
        }
      }

      /******************************/
      /* Idle when window minimized */
      /******************************/
      if (state.window_minimized)
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
          opengl_shader_load_shader_main(&main_shader, fragment_shader_file_name);
          fs_last = fs_now;

          /* Reset iTime elapsed seconds on hot reload */
          QueryPerformanceCounter(&time_start);
          state.iFrame = 0;
        }
      }

      /******************************/
      /* Input Processing           */
      /******************************/
      {
        MSG message = {0};
        u32 i;

        u64 *src = (u64 *)state.keys_is_down;
        u64 *dst = (u64 *)state.keys_was_down;

        /* 256 bytes / 8 bytes (u64) = 32 chunks. */
        for (i = 0; i < 8; ++i)
        {
          *dst++ = *src++;
          *dst++ = *src++;
          *dst++ = *src++;
          *dst++ = *src++;
        }

        /* Reset accumulated mouse relative speeds every frame before processing new mouse messages */
        state.mouse_dx = 0;
        state.mouse_dy = 0;

        while (PeekMessageA(&message, 0, 0, 0, PM_REMOVE))
        {
          TranslateMessage(&message);
          DispatchMessageA(&message);
        }
      }

      /* Get current frames mouse position */
      {
        POINT p;
        GetCursorPos(&p);
        ScreenToClient(state.window_handle, &p);

        state.mouse_x = p.x;
        state.mouse_y = (i32)state.window_height - 1 - p.y;
      }

      /******************************/
      /* XInput Controller          */
      /******************************/
      if (XInputGetState)
      {

        /* If we recieve a WM_DEVICECHANGE message (hardware connected or disconnected to machine)
         * we need to check again the XInput Controller state.
         */
        if (state.controller.check_needed)
        {
          u8 i = 0;

          XINPUT_STATE xinput_state = {0};

          state.controller.connected = 0;

          for (i = 0; i < XINPUT_USER_MAX_COUNT; ++i)
          {
            u32 result = XInputGetState(i, &xinput_state);

            if (result == 0)
            {
              state.controller.id = i;
              state.controller.connected = 1;
              break;
            }
          }

          state.controller.check_needed = 0;
        }

        if (state.controller.connected)
        {
          XINPUT_STATE xinput_state = {0};
          u32 result = XInputGetState(state.controller.id, &xinput_state);

          if (result == 0)
          {
            XINPUT_GAMEPAD *gp = &xinput_state.Gamepad;
            state.controller.button_a = (gp->wButtons & XINPUT_GAMEPAD_A) ? 1 : 0;
            state.controller.button_b = (gp->wButtons & XINPUT_GAMEPAD_B) ? 1 : 0;
            state.controller.button_x = (gp->wButtons & XINPUT_GAMEPAD_X) ? 1 : 0;
            state.controller.button_y = (gp->wButtons & XINPUT_GAMEPAD_Y) ? 1 : 0;
            state.controller.shoulder_left = (gp->wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) ? 1 : 0;
            state.controller.shoulder_right = (gp->wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) ? 1 : 0;
            state.controller.dpad_up = (gp->wButtons & XINPUT_GAMEPAD_DPAD_UP) ? 1 : 0;
            state.controller.dpad_down = (gp->wButtons & XINPUT_GAMEPAD_DPAD_DOWN) ? 1 : 0;
            state.controller.dpad_left = (gp->wButtons & XINPUT_GAMEPAD_DPAD_LEFT) ? 1 : 0;
            state.controller.dpad_right = (gp->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) ? 1 : 0;
            state.controller.start = (gp->wButtons & XINPUT_GAMEPAD_START) ? 1 : 0;
            state.controller.back = (gp->wButtons & XINPUT_GAMEPAD_BACK) ? 1 : 0;
            state.controller.stick_left = (gp->wButtons & XINPUT_GAMEPAD_LEFT_THUMB) ? 1 : 0;
            state.controller.stick_right = (gp->wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) ? 1 : 0;
            state.controller.trigger_left_value = xinput_process_trigger(gp->bLeftTrigger);
            state.controller.trigger_right_value = xinput_process_trigger(gp->bRightTrigger);
            state.controller.trigger_left = state.controller.trigger_left_value > 0.0f ? 1 : 0;
            state.controller.trigger_right = state.controller.trigger_right_value > 0.0f ? 1 : 0;
            state.controller.stick_left_x = xinput_process_thumbstick(gp->sThumbLX, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
            state.controller.stick_left_y = xinput_process_thumbstick(gp->sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
            state.controller.stick_right_x = xinput_process_thumbstick(gp->sThumbRX, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
            state.controller.stick_right_y = xinput_process_thumbstick(gp->sThumbRY, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
          }
          else
          {
            state.controller.check_needed = 1;
            state.controller.connected = 0;
          }
        }
      }

      /******************************/
      /* Full or Borderless (F9,F11)*/
      /******************************/
      if (state.keys_is_down[0x78] && !state.keys_was_down[0x78]) /* F9 */
      {
        state.borderless_enabled = !state.borderless_enabled;

        if (state.borderless_enabled && !state.fullscreen_enabled)
        {
          win32_window_enter_borderless(&state);
        }
        else
        {
          state.fullscreen_enabled = 0;
          state.borderless_enabled = 0;
          win32_window_enter_windowed(&state);
        }
      }

      if (state.keys_is_down[0x7A] && !state.keys_was_down[0x7A]) /* F11 */
      {
        state.fullscreen_enabled = !state.fullscreen_enabled;

        if (state.fullscreen_enabled && !state.borderless_enabled)
        {
          win32_window_enter_fullscreen(&state);
        }
        else
        {
          state.fullscreen_enabled = 0;
          state.borderless_enabled = 0;
          win32_window_enter_windowed(&state);
        }
      }

      /******************************/
      /* Handle Window Size changes */
      /******************************/
      if (state.window_size_changed && !state.screen_recording_enabled)
      {
        state.window_width = state.window_width_pending;
        state.window_height = state.window_height_pending;

        glViewport(0, 0, (i32)state.window_width, (i32)state.window_height);

        state.window_size_changed = 0;
      }

      glClear(GL_COLOR_BUFFER_BIT);

      /******************************/
      /* Pause Shader (P)           */
      /******************************/
      if (state.keys_is_down[0x50] && !state.keys_was_down[0x50]) /* P */
      {
        state.shader_paused = !state.shader_paused;
      }

      /******************************/
      /* Reset Timer (R)            */
      /******************************/
      if (state.keys_is_down[0x52] && !state.keys_was_down[0x52]) /* R */
      {
        /* Reset iTime elapsed seconds on hot reload */
        QueryPerformanceCounter(&time_start);
        state.iFrame = 0;
      }

      /******************************/
      /* Main Shader Rendering      */
      /******************************/
      glUseProgram(main_shader.header.program);

      if (!state.shader_paused)
      {
        glUniform3f(main_shader.loc_iResolution, (f32)state.window_width, (f32)state.window_height, 1.0f);
        glUniform1f(main_shader.loc_iTime, (f32)state.iTime);
        glUniform1f(main_shader.loc_iTimeDelta, (f32)state.iTimeDelta);
        glUniform1i(main_shader.loc_iFrame, state.iFrame);
        glUniform1f(main_shader.loc_iFrameRate, (f32)state.iFrameRate);
        glUniform4f(main_shader.loc_iMouse, (f32)state.mouse_x, (f32)state.mouse_y, (f32)state.mouse_dx, (f32)state.mouse_dy);
        glUniform4f(main_shader.loc_iTextureInfo, SHADE_IT_FONT_WIDTH, SHADE_IT_FONT_HEIGHT, SHADE_IT_FONT_GLYPH_WIDTH, SHADE_IT_FONT_GLYPH_HEIGHT);
        glUniform1i(main_shader.loc_iTexture, 0);

        /* Pack XInput Controller State into uniform vec4 iController[2];*/
        if (state.controller.connected)
        {
          union
          {
            f32 f;
            u32 u;
          } punner;

          f32 iControllerData[8];
          iControllerData[0] = state.controller.stick_left_x;
          iControllerData[1] = state.controller.stick_left_y;
          iControllerData[2] = state.controller.stick_right_x;
          iControllerData[3] = state.controller.stick_right_y;
          iControllerData[4] = state.controller.trigger_left_value;
          iControllerData[5] = state.controller.trigger_right_value;

          /* Pack button state in u32 bitmask */
          punner.u = (state.controller.button_a << 0) |
                     (state.controller.button_b << 1) |
                     (state.controller.button_x << 2) |
                     (state.controller.button_y << 3) |
                     (state.controller.shoulder_left << 4) |
                     (state.controller.shoulder_right << 5) |
                     (state.controller.trigger_left << 6) |
                     (state.controller.trigger_right << 7) |
                     (state.controller.dpad_up << 8) |
                     (state.controller.dpad_down << 9) |
                     (state.controller.dpad_left << 10) |
                     (state.controller.dpad_right << 11) |
                     (state.controller.stick_left << 12) |
                     (state.controller.stick_right << 13) |
                     (state.controller.start << 14) |
                     (state.controller.back << 15) |
                     (state.controller.connected << 16);

          iControllerData[6] = punner.f;
          iControllerData[7] = 0.0f; /* padding*/

          glUniform4fv(main_shader.loc_iController, 2, iControllerData);
        }
      }

      glBindVertexArray(main_vao);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      /******************************/
      /* UI Rendering (F1 pressed)  */
      /******************************/
      if (state.keys_is_down[0x70] && !state.keys_was_down[0x70]) /* F1 */
      {
        state.ui_enabled = !state.ui_enabled;
      }

      if (state.ui_enabled)
      {
        s8 buffer[1024];
        text t = {0};

        glyph glyphs[1024];
        u32 glyph_count;
        f32 font_scale = 2.0f;

        u32 handle_count = 0;
        process_memory_info mem = {0};

        /* build UI string */
        t.size = sizeof(buffer);
        t.buffer = buffer;

        text_append_str(&t, "STATE      : ");
        if (state.shader_paused)
        {
          text_append_str(&t, "PAUSED ");
        }
        if (state.borderless_enabled)
        {
          text_append_str(&t, "BORDERLESS ");
        }
        else if (state.fullscreen_enabled)
        {
          text_append_str(&t, "FULLSCREEN ");
        }
        else
        {
          text_append_str(&t, "WINDOWED ");
        }
        if (state.screen_recording_enabled)
        {
          text_append_str(&t, "RECORDING ");
        }
        text_append_str(&t, "\nFPS        : ");
        text_append_f64(&t, state.iFrameRate, 2);
        text_append_str(&t, "\nFPS TARGET : <");
        text_append_f64(&t, state.target_frames_per_second, 2);
        text_append_str(&t, ">\nFPS RAW    : ");
        text_append_f64(&t, state.iFrameRateRaw, 2);
        text_append_str(&t, "\nFRAME      : ");
        text_append_i32(&t, state.iFrame);
        text_append_str(&t, "\nDELTA      : ");
        text_append_f64(&t, state.iTimeDelta, 6);
        text_append_str(&t, "\nTIME       : ");
        text_append_f64(&t, state.iTime, 6);
        text_append_str(&t, "\nMOUSE X/Y  : ");
        text_append_i32(&t, state.mouse_x);
        text_append_str(&t, "/");
        text_append_i32(&t, state.mouse_y);
        text_append_str(&t, "\nMOUSE DX/DY: ");
        text_append_i32(&t, state.mouse_dx);
        text_append_str(&t, "/");
        text_append_i32(&t, state.mouse_dy);
        text_append_str(&t, "\nSIZE  X/Y  : ");
        text_append_i32(&t, (i32)state.window_width);
        text_append_str(&t, "/");
        text_append_i32(&t, (i32)state.window_height);
        text_append_str(&t, "\nTHREADS    : ");
        text_append_i32(&t, thread_count);

        if (GetProcessHandleCount(GetCurrentProcess(), &handle_count))
        {
          text_append_str(&t, "\nHANDLES    : ");
          text_append_i32(&t, (i32)handle_count);
        }

        if (win32_process_memory(&mem))
        {
          text_append_str(&t, "\nMEM WORK   : ");
          text_append_i32(&t, (i32)(mem.working_set / 1024));
          text_append_str(&t, "\nMEM PEAK   : ");
          text_append_i32(&t, (i32)(mem.peak_working_set / 1024));
          text_append_str(&t, "\nMEM COMMIT : ");
          text_append_i32(&t, (i32)(mem.private_bytes / 1024));
        }

        text_append_str(&t, "\nGL VENDOR  : ");
        text_append_str(&t, state.gl_vendor);
        text_append_str(&t, "\nGL RENDER  : ");
        text_append_str(&t, state.gl_renderer);
        text_append_str(&t, "\nGL VERSION : ");
        text_append_str(&t, state.gl_version);
        text_append_str(&t, "\nGL ERROR FS: ");
        text_append_str(&t, main_shader.header.had_failure ? shader_info_log : "NONE");

        if (state.controller.connected)
        {
          text_append_str(&t, "\nCONTROLLER : CONNECTED");
          text_append_str(&t, "\nSTICK L X/Y: ");
          text_append_f64(&t, state.controller.stick_left_x, 6);
          text_append_str(&t, "/");
          text_append_f64(&t, state.controller.stick_left_y, 6);
          text_append_str(&t, "\nSTICK R X/Y: ");
          text_append_f64(&t, state.controller.stick_right_x, 6);
          text_append_str(&t, "/");
          text_append_f64(&t, state.controller.stick_right_y, 6);
          text_append_str(&t, "\nTRIGGER L/R: ");
          text_append_f64(&t, state.controller.trigger_left_value, 6);
          text_append_str(&t, "/");
          text_append_f64(&t, state.controller.trigger_right_value, 6);
          text_append_str(&t, "\nBUTTONS    : ");

          /* clang-format off */
          if (state.controller.button_a)       text_append_str(&t, "A ");
          if (state.controller.button_b)       text_append_str(&t, "B ");
          if (state.controller.button_x)       text_append_str(&t, "X ");
          if (state.controller.button_y)       text_append_str(&t, "Y ");
          if (state.controller.dpad_left)      text_append_str(&t, "DLEFT ");
          if (state.controller.dpad_right)     text_append_str(&t, "DRIGHT ");
          if (state.controller.dpad_up)        text_append_str(&t, "DUP ");
          if (state.controller.dpad_down)      text_append_str(&t, "DDOWN ");
          if (state.controller.stick_left)     text_append_str(&t, "LSTICK ");
          if (state.controller.stick_right)    text_append_str(&t, "RSTICK ");
          if (state.controller.shoulder_left)  text_append_str(&t, "LSHOULDER ");
          if (state.controller.shoulder_right) text_append_str(&t, "RSHOULDER ");
          /* clang-format on */
        }
        else
        {
          text_append_str(&t, "\nCONTROLLER : NOT FOUND");
        }

        glyph_count = text_to_glyphs(
            t.buffer,
            glyphs,
            sizeof(glyphs) / sizeof(glyphs[0]),
            10.0f, /* x */
            10.0f, /* y */
            font_scale);

        /* TODO(nickscha): Measure GPU difference of STREAM_DRAW vs DYNAMIC_DRAW */
        (void)GL_DYNAMIC_DRAW;

        glBufferData(GL_ARRAY_BUFFER, (i32)(glyph_count * sizeof(glyph)), glyphs, GL_STREAM_DRAW);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glUseProgram(font_shader.header.program);
        glUniform3f(font_shader.loc_iResolution, (f32)state.window_width, (f32)state.window_height, 1.0f);
        glUniform1f(font_shader.loc_iTime, (f32)state.iTime);
        glUniform4f(font_shader.loc_iTextureInfo, SHADE_IT_FONT_WIDTH, SHADE_IT_FONT_HEIGHT, SHADE_IT_FONT_GLYPH_WIDTH, SHADE_IT_FONT_GLYPH_HEIGHT);
        glUniform1i(font_shader.loc_iTexture, 0);
        glUniform1f(font_shader.loc_iFontScale, font_scale);
        glBindVertexArray(font_vao);
        glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, glyph_count);

        glDisable(GL_BLEND);
      }

      /******************************/
      /* Screen Recording (F2)      */
      /******************************/
      {
        static u8 *framebuffer;
        static void *video_file_handle;

        if (state.keys_is_down[0x71] && !state.keys_was_down[0x71]) /* F2 */
        {
          state.screen_recording_enabled = !state.screen_recording_enabled;
        }

        if (state.screen_recording_enabled)
        {

          u32 written = 0;

          if (!state.screen_recording_initialized)
          {
            s8 buffer[128];
            text t = {0};

            t.size = sizeof(buffer);
            t.buffer = buffer;

            /* Create recording output file name.
             * Format:  shade_it_capture_<window_width>x<window_height>_<target_frames_per_second>.raw
             * Example: shade_it_capture_800x600_60.raw
             */
            text_append_str(&t, "shade_it_capture_");
            text_append_i32(&t, (i32)(state.window_width));
            text_append_str(&t, "x");
            text_append_i32(&t, (i32)(state.window_height));
            text_append_str(&t, "_");
            text_append_i32(&t, (i32)(state.target_frames_per_second));
            text_append_str(&t, ".raw");

            framebuffer = VirtualAlloc(0, state.window_width * state.window_height * 3, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
            video_file_handle = CreateFileA(t.buffer, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

            glPixelStorei(GL_PACK_ALIGNMENT, 1);

            state.screen_recording_initialized = 1;
          }
          glReadPixels(0, 0, (i32)state.window_width, (i32)state.window_height, GL_RGB, GL_UNSIGNED_BYTE, framebuffer);

          WriteFile(video_file_handle, framebuffer, state.window_width * state.window_height * 3, &written, 0);

          /* Render recording indicator */
          glUseProgram(recording_shader.header.program);
          glUniform3f(recording_shader.loc_iResolution, (f32)state.window_width, (f32)state.window_height, 1.0f);
          glUniform1f(recording_shader.loc_iTime, (f32)state.iTime);
          glBindVertexArray(main_vao);
          glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        else if (state.screen_recording_initialized)
        {
          VirtualFree(framebuffer, 0, MEM_RELEASE);
          CloseHandle(video_file_handle);
          state.screen_recording_initialized = 0;
        }
      }

      SwapBuffers(state.device_context);

      /* Measure RAW FPS (rendering without cap)*/
      {
        i64 time_render_now;
        QueryPerformanceCounter(&time_render_now);
        state.iFrameRateRaw = 1.0 / ((f64)(time_render_now - time_last) / (f64)perf_freq);
      }

      /******************************/
      /* Frame Rate Limiting        */
      /******************************/
      if (state.target_frames_per_second > 0)
      {
        i64 time_end;

        f64 frame_time;
        f64 remaining;
        f64 target_frame_time = 1.0 / (f64)state.target_frames_per_second;

        QueryPerformanceCounter(&time_end);

        frame_time = (f64)(time_end - time_start_fps_cap) / (f64)perf_freq;
        remaining = target_frame_time - frame_time;

        if (remaining > 0.0)
        {
          /* Sleep most of it (milliseconds) */
          if (remaining > 0.0005)
          {
            u32 sleep_ms = (u32)((remaining - 0.00025) * 1000.0);

            if (sleep_ms > 0)
            {
              Sleep(sleep_ms);
            }
          }

          /* Spin for the rest */
          for (;;)
          {
            QueryPerformanceCounter(&time_end);

            frame_time = (f64)(time_end - time_start_fps_cap) / (f64)perf_freq;

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

/* #############################################################################
 * # [SECTION] nostdlib entry point
 * #############################################################################
 */
#ifdef __clang__
#elif __GNUC__
__attribute((externally_visible))
#endif
i32 WinMainCRTStartup(void)
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

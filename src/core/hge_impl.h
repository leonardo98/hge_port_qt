/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Common core implementation header
*/


#ifndef HGE_IMPL_H
#define HGE_IMPL_H

#include <QGLWidget>
#include "../../include/hge.h"
#include <stdio.h>

#define DEMO

#define _MAX_PATH 1024

#define D3DFVF_HGEVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define VERTEX_BUFFER_SIZE 4000

struct CRenderTargetList
{
    int					width;
    int					height;
    GLuint				framebuffer;
    HTEXTURE			pTex;
    bool				bDepth;
    CRenderTargetList*	next;
};

struct CTextureList
{
	HTEXTURE			tex;
	int					width;
	int					height;
	CTextureList*		next;
};

struct CResourceList
{
	char				filename[_MAX_PATH];
	char				password[64];
	CResourceList*		next;
};

struct CStreamList
{
	HSTREAM				hstream;
	void*				data;
	CStreamList*		next;
};

struct CInputEventList
{
	hgeInputEvent		event;
	CInputEventList*	next;
};


void DInit();
void DDone();
bool DFrame();


/*
** HGE Interface implementation
*/
class HGE_Impl : public HGE
{
public:
    virtual	void		Release();

    virtual bool		System_Initiate();
    virtual void		System_Shutdown();
    virtual bool		System_Start();
    virtual void		System_SetStateBool  (hgeBoolState   state, bool        value);
    virtual void		System_SetStateFunc  (hgeFuncState   state, hgeCallback value);
    virtual void		System_SetStateInt   (hgeIntState    state, int         value);
    virtual void		System_SetStateString(hgeStringState state, const char *value);
    virtual bool		System_GetStateBool  (hgeBoolState  );
    virtual hgeCallback	System_GetStateFunc  (hgeFuncState  );
    virtual int			System_GetStateInt   (hgeIntState   );
    virtual const char*	System_GetStateString(hgeStringState);
    virtual char*		System_GetErrorMessage();
    virtual	void		System_Log(const char *format, ...);
    virtual bool		System_Launch(const char *url);
    virtual void		System_Snapshot(const char *filename=0);

    virtual void*		Resource_Load(const char *filename, DWORD *size=0);
    virtual void		Resource_Free(void *res);
    virtual bool		Resource_AttachPack(const char *filename, const char *password=0);
    virtual void		Resource_RemovePack(const char *filename);
    virtual void		Resource_RemoveAllPacks();
    virtual char*		Resource_MakePath(const char *filename=0);
    virtual char*		Resource_EnumFiles(const char *wildcard=0);
    virtual char*		Resource_EnumFolders(const char *wildcard=0);

    virtual	void		Ini_SetInt(const char *section, const char *name, int value);
    virtual	int 		Ini_GetInt(const char *section, const char *name, int def_val);
    virtual	void		Ini_SetFloat(const char *section, const char *name, float value);
    virtual	float		Ini_GetFloat(const char *section, const char *name, float def_val);
    virtual	void		Ini_SetString(const char *section, const char *name, const char *value);
    virtual	char*		Ini_GetString(const char *section, const char *name, const char *def_val);

    virtual void		Random_Seed(int seed=0);
    virtual int			Random_Int(int min, int max);
    virtual float		Random_Float(float min, float max);

    virtual float		Timer_GetTime();
    virtual float		Timer_GetDelta();
    virtual int			Timer_GetFPS();

    virtual HEFFECT		Effect_Load(const char *filename, DWORD size=0);
    virtual void		Effect_Free(HEFFECT eff);
    virtual HCHANNEL	Effect_Play(HEFFECT eff);
    virtual HCHANNEL	Effect_PlayEx(HEFFECT eff, int volume=100, int pan=0, float pitch=1.0f, bool loop=false);

    virtual HMUSIC		Music_Load(const char *filename, DWORD size=0);
    virtual void		Music_Free(HMUSIC mus);
    virtual HCHANNEL	Music_Play(HMUSIC mus, bool loop, int volume = 100, int order = 0, int row = 0);
    virtual void		Music_SetAmplification(HMUSIC music, int ampl);
    virtual int			Music_GetAmplification(HMUSIC music);
    virtual int			Music_GetLength(HMUSIC music);
    virtual void		Music_SetPos(HMUSIC music, int order, int row);
    virtual bool		Music_GetPos(HMUSIC music, int *order, int *row);
    virtual void		Music_SetInstrVolume(HMUSIC music, int instr, int volume);
    virtual int			Music_GetInstrVolume(HMUSIC music, int instr);
    virtual void		Music_SetChannelVolume(HMUSIC music, int channel, int volume);
    virtual int			Music_GetChannelVolume(HMUSIC music, int channel);

    virtual HSTREAM		Stream_Load(const char *filename, DWORD size=0);
    virtual void		Stream_Free(HSTREAM stream);
    virtual HCHANNEL	Stream_Play(HSTREAM stream, bool loop, int volume = 100);

    virtual void		Channel_SetPanning(HCHANNEL chn, int pan);
    virtual void		Channel_SetVolume(HCHANNEL chn, int volume);
    virtual void		Channel_SetPitch(HCHANNEL chn, float pitch);
    virtual void		Channel_Pause(HCHANNEL chn);
    virtual void		Channel_Resume(HCHANNEL chn);
    virtual void		Channel_Stop(HCHANNEL chn);
    virtual void		Channel_PauseAll();
    virtual void		Channel_ResumeAll();
    virtual void		Channel_StopAll();
    virtual bool		Channel_IsPlaying(HCHANNEL chn);
    virtual float		Channel_GetLength(HCHANNEL chn);
    virtual float		Channel_GetPos(HCHANNEL chn);
    virtual void		Channel_SetPos(HCHANNEL chn, float fSeconds);
    virtual void		Channel_SlideTo(HCHANNEL channel, float time, int volume, int pan = -101, float pitch = -1);
    virtual bool		Channel_IsSliding(HCHANNEL channel);

    virtual void		Input_GetMousePos(float *x, float *y);
    virtual void		Input_SetMousePos(float x, float y);
    virtual int			Input_GetMouseWheel();
    virtual bool		Input_IsMouseOver();
    virtual bool		Input_KeyDown(int key);
    virtual bool		Input_KeyUp(int key);
    virtual bool		Input_GetKeyState(int key);
    virtual char*		Input_GetKeyName(int key);
    virtual int			Input_GetKey();
    virtual int			Input_GetChar();
    virtual bool		Input_GetEvent(hgeInputEvent *event);

    virtual bool		Gfx_BeginScene(HTARGET target=0);
    virtual void		Gfx_EndScene();
    virtual void		Gfx_Clear(DWORD color);
    virtual void		Gfx_RenderLine(float x1, float y1, float x2, float y2, DWORD color=0xFFFFFFFF, float z=0.5f);
    virtual void		Gfx_RenderTriple(const hgeTriple *triple);
    virtual void		Gfx_RenderQuad(const hgeQuad *quad);
    virtual hgeVertex*	Gfx_StartBatch(int prim_type, HTEXTURE tex, int blend, int *max_prim);
    virtual void		Gfx_FinishBatch(int nprim);
    virtual void		Gfx_SetClipping(int x=0, int y=0, int w=0, int h=0);
    virtual void		Gfx_SetTransform(float x=0, float y=0, float dx=0, float dy=0, float rot=0, float hscale=0, float vscale=0);

    virtual HTARGET		Target_Create(int width, int height, bool zbuffer);
    virtual void		Target_Free(HTARGET target);
    virtual HTEXTURE	Target_GetTexture(HTARGET target);

    virtual HTEXTURE	Texture_Create(int width, int height);
    virtual HTEXTURE	Texture_Load(const char *filename, DWORD size=0, bool bMipmap=false);
    virtual void		Texture_Free(HTEXTURE tex);
    virtual int			Texture_GetWidth(HTEXTURE tex, bool bOriginal=false);
    virtual int			Texture_GetHeight(HTEXTURE tex, bool bOriginal=false);
    virtual DWORD*		Texture_Lock(HTEXTURE tex, bool bReadOnly=true, int left=0, int top=0, int width=0, int height=0);
    virtual void		Texture_Unlock(HTEXTURE tex);

	//////// Implementation ////////

	static HGE_Impl*	_Interface_Get();
	void				_FocusChange(bool bAct);
	void				_PostError(char *error);

	bool				bActive;
	char				szError[256];
	char				szAppPath[_MAX_PATH];
	char				szIniString[256];


	// System States
	bool				(*procFrameFunc)();
	bool				(*procRenderFunc)();
	bool				(*procFocusLostFunc)();
	bool				(*procFocusGainFunc)();
	bool				(*procGfxRestoreFunc)();
	bool				(*procExitFunc)();
	const char*			szIcon;
	char				szWinTitle[256];
	int					nScreenWidth;
	int					nScreenHeight;
	int					nScreenBPP;
	bool				bWindowed;
	bool				bZBuffer;
	bool				bTextureFilter;
	char				szIniFile[_MAX_PATH];
	char				szLogFile[_MAX_PATH];
	bool				bUseSound;
	int					nSampleRate;
	int					nFXVolume;
	int					nMusVolume;
	int					nStreamVolume;
	int					nHGEFPS;
	bool				bHideMouse;
	bool				bDontSuspend;

	#ifdef DEMO
	bool				bDMO;
	#endif


	// Power
	int							nPowerStatus;
//	GetSystemPowerStatusFunc	lpfnGetSystemPowerStatus;

	void				_InitPowerStatus();
	void				_UpdatePowerStatus();
	void				_DonePowerStatus();


	// Graphics
//	D3DPRESENT_PARAMETERS*  d3dpp;

//	D3DPRESENT_PARAMETERS   d3dppW;
//	RECT					rectW;

//	D3DPRESENT_PARAMETERS   d3dppFS;
//	RECT					rectFS;

//	IDirect3D8*				pD3D;
//	IDirect3DDevice8*		pD3DDevice;
//	IDirect3DVertexBuffer8*	pVB;
//	IDirect3DIndexBuffer8*	pIB;

//	IDirect3DSurface8*	pScreenSurf;
//	IDirect3DSurface8*	pScreenDepth;
	CRenderTargetList*	pTargets;
	CRenderTargetList*	pCurTarget;

//	D3DXMATRIX			matView;
//	D3DXMATRIX			matProj;

	CTextureList*		textures;
	hgeVertex*			VertArray;

	int					nPrim;
	int					CurPrimType;
	int					CurBlendMode;
	HTEXTURE			CurTexture;

	bool				_GfxInit();
	void				_GfxDone();
	bool				_GfxRestore();
	void				_AdjustWindow();
	void				_Resize(int width, int height);
	bool				_init_lost();
	void				_render_batch(bool bEndScene=false);
//	int					_format_id(D3DFORMAT fmt);
	void				_SetBlendMode(int blend);
	void				_SetProjectionMatrix(int width, int height);
	

	// Audio
	bool				bSilent;
	CStreamList*		streams;
	bool				_SoundInit();
	void				_SoundDone();
	void				_SetMusVolume(int vol);
	void				_SetStreamVolume(int vol);
	void				_SetFXVolume(int vol);


	// Input
	int					VKey;
	int					Char;
	int					Zpos;
	float				Xpos;
	float				Ypos;
	bool				bMouseOver;
	bool				bCaptured;
	char				keyz[256];
	CInputEventList*	queue;
	void				_UpdateMouse();
	void				_InputInit();
	void				_ClearQueue();
	void				_BuildEvent(int type, int key, int scan, int flags, int x, int y);


	// Resources
	char				szTmpFilename[_MAX_PATH];
	CResourceList*		res;
//	HANDLE				hSearch;
//	WIN32_FIND_DATA		SearchData;


	// Timer
	float				fTime;
	float				fDeltaTime;
	DWORD				nFixedDelta;
	int					nFPS;
	DWORD				t0, t0fps, dt;
	int					cfps;

    bool                hBass;


private:
	HGE_Impl();
};

extern HGE_Impl*		pHGE;

#endif


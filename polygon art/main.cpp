/*================================================================
		Window�̕\��[main.cpp]
										Author	:	Fujino Shuma
										Date	:	2019/05/08

==================================================================*/
/*���p����t�@�C���̎w��=============================================
#pragma comment(lib,"d3d9.lib")
#if defined(DEBUG)||defined(_DEBUG)
#pragma comment(lib,"d3dx9d.lib")
#else
#pragma comment(lib,"d3dx9.lib")
#endif
===================================================================*/

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>

/*--------------------------------------------------------------------
		�萔��`
---------------------------------------------------------------------*/

#define CLASS_NAME	"GameWindow"
#define WINDOW_CAPTION	"polygon art"
#define SCREEN_WIDTH (1080)
#define SCREEN_HEIGHT (600)
#define WINDOW_STYLE WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX)
#define CIRCLE_COUNTER (600)
#define COLOR_NUM (255)


/*--------------------------------------------------------------------
		�v���g�^�C�v�錾
---------------------------------------------------------------------*/

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static HWND Init(HWND, HINSTANCE, int);
static void Uninit(void);
static void Update(void);
static void Draw(void);

static HWND InitApp(HINSTANCE, int);
static bool InitDirect3D(HWND);
static bool InitGemetry();
static bool CleanupDirect3D();
static bool RenderDirect3D();
void MoveCircle(float vx, float vy, float ox, float oy, float r, float *Nx, float *Ny);
void SetCircle(D3DXVECTOR4 _center, D3DCOLOR _color, float _radius);
void SetTriangle(D3DXVECTOR4 _center, D3DCOLOR _color, float _radius, float _angle);
void SetWave(float _angle);
void MoveWave(float _width, float _height, float _counter, float *Nx, float *Ny);
void SetStar(D3DXVECTOR4 _center, D3DCOLOR _color, float _radius, float _angle);


/*--------------------------------------------------------------------
		�O���[�o���ϐ�
---------------------------------------------------------------------*/

static LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pDevive = NULL;	//Direct3D�f�o�C�X�̎擾

//���_�̌`��\�����钸�_�\���̂�錾����
typedef struct Vertex2d_tag {
	//x,y,z,w		���W�ϊ��ςݒ��_�̗��p�@->�@RHW��1.0f��ݒ�
	D3DXVECTOR4 position;	//���W
	D3DCOLOR color;
	D3DXVECTOR2 uv;	//texcord
	//	u = �摜��x���W / �摜�̕�
	//	v = �摜��y�摜 / �摜�̍��� 
}Vertex2d;
//�f�o�C�X�ɒ��_�̌`��`���邽�߂�FVF��錾����
#define FVF_VERTEX2D ((D3DFVF_XYZRHW)|(D3DFVF_DIFFUSE)|D3DFVF_TEX1)

float radius = 100.0f;
D3DXVECTOR2 center = { 200.0f,200.0f };
float pcount = (2 * D3DX_PI*radius + 1.0f);
float angle = 0;
Vertex2d v[SCREEN_WIDTH];
D3DXVECTOR4 circleCenter = { 400.0f,400.0f,0.0f,1.0f };
D3DXVECTOR4 triangleCenter = { 400.0f,400.0f,0.0f,1.0f };
Vertex2d wave[SCREEN_WIDTH];

D3DCOLOR color[COLOR_NUM];
LPDIRECT3DTEXTURE9 g_pTexture = NULL;

Vertex2d g_VertexDate[] = {
	{D3DXVECTOR4(256.0f + 150.0f - 0.5f,0.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f)},
	{D3DXVECTOR4(256.0f + 150.0f - 0.5f,256.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,1.0f)},
	{D3DXVECTOR4(0.0f + 150.0f - 0.5f,0.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f)},
	{D3DXVECTOR4(0.0f + 150.0f - 0.5f,256.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,1.0f)},
	//{D3DXVECTOR4(SCREEN_WIDTH - 100.0f,400.0f - (float)(100.0f*sqrt(3)),0.0f,1.0f),D3DCOLOR_RGBA(255,0,255,255)}

};

/*--------------------------------------------------------------------
	���C��
----------------------------------------------------------------------*/

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg = {};
	HWND hWnd = 0;
	hWnd = Init(hWnd, hInstance, nCmdShow);
	if (!hWnd) return false;


	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//�Q�[������
			Update();
			Draw();
		}
	}
	return(int)msg.wParam;
}




/*========================================
				Init all.
=========================================*/
HWND Init(HWND hWnd, HINSTANCE hInstance, int nCmdShow) {
	hWnd = InitApp(hInstance, nCmdShow);

	if (!hWnd)return false;
	if (!InitDirect3D(hWnd))return false;
	if (!InitGemetry())return false;

	return hWnd;
}

/*===================================
		Appllication Init.
====================================*/
HWND InitApp(HINSTANCE hInstance, int nCmdShow) {

	HWND hWnd;

	WNDCLASS wc = {};	//������
	wc.lpfnWndProc = WndProc;	//�E�B���h�E�v���V�[�W���R�[���o�b�N�֐��̓o�^
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	//���̐ݒ�
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);	//�F�ݒ�

	if (!RegisterClass(&wc)) {
		return false;
	}



	/*�E�B���h�E=>�E�B���h���\������p�[�c��"�e�L�X�g�{�b�N�X","�{�^��",�Ȃ�
	�V�X�e���ɂ����p�[�c�̃N���X(*���̃N���X��C++��"�N���X"�Ƃ͖��֌W)���o�^����Ă���
	�I���W�i���̃E�B���h�E�͎����ŃN���X���V�X�e���ɓo�^����K�v������B*/



	RECT window_rect{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	DWORD window_style = WINDOW_STYLE;
	AdjustWindowRect(&window_rect, window_style, FALSE);

	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);

	int window_width = max(window_rect.right - window_rect.left, 0);
	int window_height = max(window_rect.bottom - window_rect.top, 0);

	int window_x = max((desktop_width - window_width) / 2, 0);
	int window_y = max((desktop_height - window_height) / 2, 0);

	hWnd = CreateWindow(
		CLASS_NAME,
		WINDOW_CAPTION,
		window_style,//�r�b�g���Z�̏��Ԃɂ��C��t����
		window_x,	//x
		window_y,	//y
		window_width,	//w
		window_height,	//h
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hWnd)return false;



	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}




/*===============================
		DirectX	Init.
================================*/
bool InitDirect3D(HWND hWnd) {
	D3DPRESENT_PARAMETERS d3dpp = {};
	HRESULT hr;

	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL) {
		MessageBox(NULL, "Direct3DCreate9 is null", "", MB_OK);
		return false;
	}



	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;	//�o�b�N�o�b�t�@�̕�
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;	//�o�b�N�o�b�t�@�̍���
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	//�o�b�N�o�b�t�@�̎��
	d3dpp.BackBufferCount = 1;		//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//�X���b�v���@(��{�R��)
	d3dpp.Windowed = TRUE;	//�E�B���h�E���[�h�̎w��(true=�E�B���h�E���[�h false=�t���X�N���[��)
	d3dpp.EnableAutoDepthStencil = TRUE;	//DepthBuffer������
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	hr = g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pDevive
	);

	hr = D3DXCreateTextureFromFile(
		g_pDevive,
		"puyoRED.png",
		&g_pTexture
	);


	//g_pDevive->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//g_pDevive->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//g_pDevive->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	//g_pDevive->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	g_pDevive->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	////���u�����h�p�����[�^
	////������`���|���S����RGB*������`���|���S���̃�+��ʂ�RGB*(1-������`���|���S���̃�)
	g_pDevive->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevive->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	g_pDevive->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pDevive->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pDevive->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pDevive->SetTextureStageState(0, D3DTSS_COLOROP, D3DTA_TEXTURE);
	g_pDevive->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
	g_pDevive->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);



	//FAILED(hr) hr�����s��������^ SUCCEEDED(hr) hr��������������^
	if (FAILED(hr)) {
		MessageBox(hWnd, "Can't create device", "error", MB_OK);

		return false;
	}

	return true;

}

bool InitGemetry() {
	srand((unsigned)time(NULL));
	for (int i = 0; i < COLOR_NUM; i++) {
		color[i] = D3DCOLOR_RGBA(rand() % 156 + 100, rand() % 156 + 100, rand() % 156 + 100, 255);
	}
	return true;
}


/*=====================================
			Uninit all.
======================================*/
void Uninit(void) {
	CleanupDirect3D();
}

/*===============================
		Direct3D Uninit
=================================*/
bool CleanupDirect3D() {

	if (g_pDevive != NULL)
		g_pDevive->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();

	return true;

}

/*====================================
			Update all.
======================================*/
void Update(void) {
	//�O���f�[�V����
	//angle += D3DXToRadian(1);
	//if (angle >= D3DXToRadian(360))angle = 0;
}



/*============================================
			Draw all.
=============================================*/
void Draw(void) {
	RenderDirect3D();
}

bool RenderDirect3D() {

	g_pDevive->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(204, 153, 255, 255), 1.0f, 0);
	//																			�J���[				z,�X�e���V��
	g_pDevive->BeginScene();

	//�|���S���`�施��
	g_pDevive->SetFVF(FVF_VERTEX2D);

	//for (int i = 0; i < 360; i++) {
	//	if (i < 90)
	//		SetTriangle(
	//			D3DXVECTOR4{
	//			SCREEN_WIDTH*(float)cos(D3DXToRadian(i)),
	//			SCREEN_HEIGHT*(float)sin(D3DXToRadian(i)),
	//			0.0f,
	//			1.0f
	//			},
	//			color[i%COLOR_NUM],
	//			0.75f*(i%90),
	//			angle + D3DXToRadian(30 * i)
	//		);
	//	if (i >= 90 && i < 180)
	//		SetTriangle(
	//			D3DXVECTOR4{
	//			SCREEN_WIDTH*(float)cos(D3DXToRadian(i)) + SCREEN_WIDTH,
	//			SCREEN_HEIGHT*(float)sin(D3DXToRadian(i)),
	//			0.0f,
	//			1.0f },
	//			color[i%COLOR_NUM],
	//			0.75f*(i % 90),
	//			angle + D3DXToRadian(30 * i)
	//			);
	//	if (i >= 180 && i < 270)
	//		SetTriangle(D3DXVECTOR4{
	//		SCREEN_WIDTH*(float)cos(D3DXToRadian(i)) + SCREEN_WIDTH,
	//		SCREEN_HEIGHT*(float)sin(D3DXToRadian(i)) + SCREEN_HEIGHT,
	//		0.0f,
	//		1.0f },
	//		color[i%COLOR_NUM],
	//		0.75f*(i % 90),
	//		angle + D3DXToRadian(30 * i)
	//		);
	//	if (i >= 270 && i < 360)
	//		SetTriangle(D3DXVECTOR4{
	//		SCREEN_WIDTH*(float)cos(D3DXToRadian(i)),
	//		SCREEN_HEIGHT*(float)sin(D3DXToRadian(i)) + SCREEN_HEIGHT,
	//		0.0f,
	//		1.0f },
	//		color[i%COLOR_NUM],
	//		0.75f*(i % 90),
	//		angle + D3DXToRadian(30 * i)
	//		);
	//	//SetTriangle(D3DXVECTOR4{ -(SCREEN_WIDTH*(float)cos(D3DXToRadian(i))+ SCREEN_WIDTH),SCREEN_HEIGHT*(float)sin(D3DXToRadian(i)),0.0f,1.0f }, color[i%COLOR_NUM], 50.0f, angle + D3DXToRadian(30 * i));
	//}


	//SetStar(D3DXVECTOR4{ 300.0f,300.0f,0.0f,1.0f }, color[4], 100.0f, angle);
	g_pDevive->SetTexture(0, g_pTexture);
	g_pDevive->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_VertexDate, sizeof(Vertex2d));

	g_pDevive->EndScene();
	g_pDevive->Present(NULL, NULL, NULL, NULL);

	return true;
}



/*===============================================
			window proc.
================================================*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}break;
	case WM_CLOSE:
		if (MessageBox(hWnd, "�{���ɏI�����Ă�낵���ł����H", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);
		}
		return 0;
	case WM_DESTROY:
		Uninit();
		PostQuitMessage(0);
		return 0;
	};
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


void MoveCircle(float vx, float vy, float ox, float oy, float r, float *Nx, float *Ny) {
	*Nx = (vx - ox) * (float)cos(r) - (vy - oy) * (float)sin(r) + ox;
	*Ny = (vx - ox) * (float)sin(r) + (vy - oy) * (float)cos(r) + oy;
}

void MoveWave(float _width, float _height, float _counter, float *Nx, float *Ny) {
	//�g�`��
	for (int i = 0; i < _counter; i++) {
		*Nx = _width;
		*Ny = (float)sin(D3DXToRadian(30)*angle)*_height;
	}
}

void SetTriangle(D3DXVECTOR4 _center, D3DCOLOR _color, float _radius, float _angle) {
	Vertex2d *triangle = (Vertex2d *)malloc(sizeof(Vertex2d)*(3 + 2));
	float angleT = _angle;
	for (int i = 0; i < 3; i++) {
		triangle[i].position = D3DXVECTOR4(
			(FLOAT)(_radius * cos(angleT) + _center.x),
			(FLOAT)(_radius * sin(angleT) + _center.y),
			_center.z,
			_center.w
		);
		triangle[i].color = _color;
		angleT += D3DXToRadian(120);
	}

	g_pDevive->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, triangle, sizeof(Vertex2d));
}

void SetCircle(D3DXVECTOR4 _center, D3DCOLOR _color, float _radius) {
	Vertex2d *circle = (Vertex2d *)malloc(sizeof(Vertex2d)*(CIRCLE_COUNTER + 2));
	float angleC = 0;
	for (int i = 0; i < CIRCLE_COUNTER; i++) {

		circle[i].position = D3DXVECTOR4(
			(FLOAT)(_radius * cos(angleC) + _center.x),
			(FLOAT)(_radius * sin(angleC) + _center.y),
			_center.z,
			_center.w
		);
		circle[i].color = _color;

		angleC += D3DXToRadian(0.899f);
	}
	g_pDevive->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, CIRCLE_COUNTER - 2, circle, sizeof(Vertex2d));
}

void SetWave(float _angle) {

	float angleW = _angle;
	//�g�`��
	for (int i = 0; i < SCREEN_WIDTH; i++) {
		//float a = (sinf(0.05f*i)) * (rand() % 30);
		//float b = (sinf(0.5f*i));
		//float c = (sinf(0.15f*i));
		//float d = (sinf(0.40f*i) * 20);
		wave[i].position = D3DXVECTOR4((float)i, (float)(SCREEN_HEIGHT*0.5f + sin(angleW) * 20), 0.0f, 1.0f);
		wave[i].color = D3DCOLOR_RGBA(i % 255 + 254, (i + 64) % 255 + 1, (i + 128) % 255 + 1, 255);
	}
	g_pDevive->DrawPrimitiveUP(D3DPT_LINESTRIP, SCREEN_WIDTH - 1, v, sizeof(Vertex2d));

}


void SetStar(D3DXVECTOR4 _center, D3DCOLOR _color, float _radius, float _angle) {
	Vertex2d *star = (Vertex2d *)malloc(sizeof(Vertex2d)*(11 + 2));
	float angleT = _angle;
	for (int i = 0; i < 11; i++) {
		if (i == 0) {
			star[0].position = _center;
			star[0].color = _color;
		}
		if (i > 0) {
			if (i % 2 == 1) {
				star[i].position = D3DXVECTOR4(
					(FLOAT)(_radius * cos(angleT) + _center.x),
					(FLOAT)(_radius * sin(angleT)) + _center.y,
					_center.z,
					_center.w
				);
				star[i].color = _color;
			}
			else
			{
				star[i].position = D3DXVECTOR4(
					(FLOAT)(_radius*pow(cos(angleT), 2) + _center.x),
					(FLOAT)(_radius*sin(angleT)*cos(angleT) + _center.y),
					_center.z,
					_center.w
				);
				star[i].color = _color;

			}
			angleT += D3DXToRadian(36);

		}
	}

	g_pDevive->DrawPrimitiveUP(D3DPT_LINESTRIP, 11, star, sizeof(Vertex2d));
}
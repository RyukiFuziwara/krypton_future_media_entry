//==============================================================
//
//C+�|���S��(main.cpp)
//Author: Fujiwara Ryuki
//
//==============================================================
#include"main.h"
#include"manager.h"

//****************//
//   �}�N����`   //
//****************//
#define CLASS_NAME		"ClassNAME"
#define WINDOWS_NAME	"DX�\������"

//****************//
//�v���g�^�C�v�錾//
//****************//
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//****************//
// �O���[�o���錾 //
//****************//
MAIN g_main;

//================================================================
//���C���֐�
//================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hinstancePrev, LPSTR lpCmdLine, int nCmdshow)
{
	DWORD	dwCurrentTime;
	DWORD	dwExeLasttime;
	DWORD	dwFrameCount;
	DWORD	dwFPSLastTime;
	int		nCountFPS = 0;

	CManager *pManager = NULL;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION),
	};

	MSG msg;

	RegisterClassEx(&wcex);

	g_main.hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOWS_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	WindowMode(true);

	dwCurrentTime = 0;
	dwExeLasttime = timeGetTime();

	ShowWindow(g_main.hWnd, nCmdshow);
	UpdateWindow(g_main.hWnd);

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//�}�l�[�W���[�̃������𐶐�
	pManager = new CManager;

	if (pManager != NULL)
	{//���������m�ۂ���Ă���Ƃ�

		//����������
		if (FAILED(pManager->Init(hInstance, g_main.hWnd, TRUE)))
		{//���������������s�����Ƃ�
			return -1;
		}
		
		ShowWindow(g_main.hWnd, nCmdshow);
		UpdateWindow(g_main.hWnd);

		//���b�Z�[�W���[�v
		while (1)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
			{
				if (msg.message == WM_QUIT)
				{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
					break;
				}
				else
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);

				}
			}
			else
			{//DirectX�̏���

				dwCurrentTime = timeGetTime();

				if ((dwCurrentTime - dwFPSLastTime) >= 500)
				{
					nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

					dwFPSLastTime = dwCurrentTime;

					dwFrameCount = 0;
				}

				if ((dwCurrentTime - dwExeLasttime) >= (1000 / 60))
				{
					dwExeLasttime = dwCurrentTime;

					//�X�V����
					pManager->Update();

					//�`�揈��
					pManager->Draw(nCountFPS);

					dwFrameCount++;
				}
			}
		}

		if (pManager != NULL)
		{//�������m�ۂ���Ă���Ƃ�

			//�I������
			pManager->Uninit();

			//�������J��
			delete pManager;
			pManager = NULL;
		}

		UnregisterClass(CLASS_NAME, wcex.hInstance);
	}

	return(int)msg.wParam;
}
//===========================================================
//�E�C���h�E�v���V�[�W��
//===========================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{

	case WM_DESTROY:	//�E�C���h�E�j���̃��b�Z�[�W

		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:

		switch (wParam)
		{

		case VK_ESCAPE:	//esc�L�[

			nID = MessageBox(hWnd, "�I�����܂���", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}

			break;
		}

		break;

	case WM_CLOSE:	//����{�^���������b�Z�[�W

		nID = MessageBox(hWnd, "�I��", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;	//0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}

		break;

	case WM_LBUTTONDOWN:

		SetFocus(hWnd);
		break;

	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//===========================================================
//�E�C���h�E�̃��[�h
//===========================================================
void WindowMode(bool bScreen)
{


	HDC hDC			// �f�X�N�g�b�v�̃n���h��
		= GetDC(GetDesktopWindow());
	int nScrSizeX	// �f�X�N�g�b�v�̉�ʃT�C�YX
		= GetDeviceCaps(hDC, HORZRES);
	int nScrSizeY	// �f�X�N�g�b�v�̉�ʃT�C�YY
		= GetDeviceCaps(hDC, VERTRES);
	// �f�X�N�g�b�v�̃n���h���������
	ReleaseDC(GetDesktopWindow(), hDC);
	if (bScreen)
	{// �S��ʃt���O���^�̎��A
	 // �E�C���h�E�̈ʒu��ݒ�
		SetWindowPos(
			g_main.hWnd,
			HWND_TOP,
			0,
			0,
			nScrSizeX,
			nScrSizeY,
			SWP_SHOWWINDOW);
		// �E�C���h�E�X�^�C����ύX
		SetWindowLong(g_main.hWnd, GWL_STYLE, WS_POPUP);
	}
	else
	{// �S��ʃt���O���U�̎��A
	 // �E�C���h�E�̈ʒu��ݒ�
		SetWindowPos(
			g_main.hWnd,
			HWND_TOP,
			(nScrSizeX * 0.5f) - (SCREEN_WIDTH * 0.5f),
			(nScrSizeY * 0.5f) - (SCREEN_HEIGHT * 0.5f),
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SWP_SHOWWINDOW);
		// �E�C���h�E�X�^�C����ύX
		SetWindowLong(g_main.hWnd, GWL_STYLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
	}
	// �E�C���h�E�̕\����Ԃ�ݒ�
	ShowWindow(g_main.hWnd, SW_NORMAL);
	// �N���C�A���g�̈���X�V
	UpdateWindow(g_main.hWnd);
}



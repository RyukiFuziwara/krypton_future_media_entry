//==============================================================
//
//C+ポリゴン(main.cpp)
//Author: Fujiwara Ryuki
//
//==============================================================
#include"main.h"
#include"manager.h"

//****************//
//   マクロ定義   //
//****************//
#define CLASS_NAME		"ClassNAME"
#define WINDOWS_NAME	"DX表示処理"

//****************//
//プロトタイプ宣言//
//****************//
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//****************//
// グローバル宣言 //
//****************//
MAIN g_main;

//================================================================
//メイン関数
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

	//マネージャーのメモリを生成
	pManager = new CManager;

	if (pManager != NULL)
	{//メモリが確保されているとき

		//初期化処理
		if (FAILED(pManager->Init(hInstance, g_main.hWnd, TRUE)))
		{//初期化処理が失敗したとき
			return -1;
		}
		
		ShowWindow(g_main.hWnd, nCmdshow);
		UpdateWindow(g_main.hWnd);

		//メッセージループ
		while (1)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
			{
				if (msg.message == WM_QUIT)
				{//WM_QUITメッセージを受け取ったらメッセージループを抜ける
					break;
				}
				else
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);

				}
			}
			else
			{//DirectXの処理

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

					//更新処理
					pManager->Update();

					//描画処理
					pManager->Draw(nCountFPS);

					dwFrameCount++;
				}
			}
		}

		if (pManager != NULL)
		{//メモリ確保されているとき

			//終了処理
			pManager->Uninit();

			//メモリ開放
			delete pManager;
			pManager = NULL;
		}

		UnregisterClass(CLASS_NAME, wcex.hInstance);
	}

	return(int)msg.wParam;
}
//===========================================================
//ウインドウプロシージャ
//===========================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{

	case WM_DESTROY:	//ウインドウ破棄のメッセージ

		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:

		switch (wParam)
		{

		case VK_ESCAPE:	//escキー

			nID = MessageBox(hWnd, "終了しますか", "終了メッセージ", MB_YESNO);

			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}

			break;
		}

		break;

	case WM_CLOSE:	//閉じるボタン押下メッセージ

		nID = MessageBox(hWnd, "終了", "終了メッセージ", MB_YESNO);

		if (nID == IDYES)
		{
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;	//0を返さないと終了してしまう
		}

		break;

	case WM_LBUTTONDOWN:

		SetFocus(hWnd);
		break;

	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//===========================================================
//ウインドウのモード
//===========================================================
void WindowMode(bool bScreen)
{


	HDC hDC			// デスクトップのハンドル
		= GetDC(GetDesktopWindow());
	int nScrSizeX	// デスクトップの画面サイズX
		= GetDeviceCaps(hDC, HORZRES);
	int nScrSizeY	// デスクトップの画面サイズY
		= GetDeviceCaps(hDC, VERTRES);
	// デスクトップのハンドルを手放す
	ReleaseDC(GetDesktopWindow(), hDC);
	if (bScreen)
	{// 全画面フラグが真の時、
	 // ウインドウの位置を設定
		SetWindowPos(
			g_main.hWnd,
			HWND_TOP,
			0,
			0,
			nScrSizeX,
			nScrSizeY,
			SWP_SHOWWINDOW);
		// ウインドウスタイルを変更
		SetWindowLong(g_main.hWnd, GWL_STYLE, WS_POPUP);
	}
	else
	{// 全画面フラグが偽の時、
	 // ウインドウの位置を設定
		SetWindowPos(
			g_main.hWnd,
			HWND_TOP,
			(nScrSizeX * 0.5f) - (SCREEN_WIDTH * 0.5f),
			(nScrSizeY * 0.5f) - (SCREEN_HEIGHT * 0.5f),
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SWP_SHOWWINDOW);
		// ウインドウスタイルを変更
		SetWindowLong(g_main.hWnd, GWL_STYLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
	}
	// ウインドウの表示状態を設定
	ShowWindow(g_main.hWnd, SW_NORMAL);
	// クライアント領域を更新
	UpdateWindow(g_main.hWnd);
}



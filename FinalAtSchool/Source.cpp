/*  CIT-284 Final Exam Project Fall 2019
*  Create a graphical OS with hard-coded equivalents to system commands
*
*  By Marisha Kulseng
*  Modified 12/18/2019
*
*  Splash screen images adapted from JoyPixels Emoji
*  https://www.joypixels.com/
*
*/


using namespace std;
#include <afxwin.h>
#include <afxdlgs.h>
#include "resource.h"
#include <strstream> //<strstrea.h> ?? not working??

#include <sstream>
#include <fstream>
#include <string>//.h>
#include <io.h>
#include <stdlib.h>//.h>
#include <time.h>//.h>

#include <dos.h>
#include <direct.h>
#include <string>
#include <iomanip>
#include <cstdio>
//#include <list>
#include<vector>
#include <algorithm>
#include <stdlib.h>
#include <atlimage.h>

//printer language definitions
#define COMPRESS "\x1b(s16.5H"
#define LANDSCAPE "\x1b&l1O"
#define PORTRAIT "\x1b&l0O"

#define IDC_EDIT 500

char buffer[MAX_PATH];
char *APP_PATH = _getcwd(buffer, sizeof(buffer));


char * workingPath;// = _getcwd(buffer, sizeof(buffer));
				   //wchar_t currentPath = (wchar_t)path; // get current dir path


				   //void copyFile(string oldName, string newName, string path = "");
void copyFile(CString oldName, CString newName, CString oldPath = "", CString newPath = "");
//void typeFile(CString fileNme, CString path);
/*vector<string>*/string sortFile(CString path, CString name);

// Define filters for use with File Dialog
const char fileDialogFilter[] =
"C++ Files (*.cpp) | *.cpp | Header Files\
(*.h) | *.h | ResourceFiles (*.rc) | *.rc } Text Files (*.txt) | *.txt | All Files (*.*) | *.* ||";

const char fileDialogExt[] = "cpp";

CString findString;



// define the application object class

class CApp : public CWinApp {
public:
	virtual BOOL InitInstance();
};

// define the edit window class

class CWindow : public CFrameWnd {
private:
	static UINT findMessage;
	CMenu *menu;

public:
	CEdit m_edit;
	string currentOp = "";
	CWindow();
	afx_msg void HandleType();
	afx_msg void HandlePrint();
	afx_msg void HandleQuit();
	afx_msg void HandleFind();
	afx_msg void HandleDelete();
	afx_msg void HandleUndo();
	afx_msg void HandleDate();
	afx_msg void HandleCut();
	afx_msg void HandleCopy();
	afx_msg void HandlePaste();
	afx_msg void HandleSave();
	afx_msg void HandleClear();
	afx_msg void HandleAbout();
	afx_msg LONG FindHelper(UINT wParam, LONG lParam);
	afx_msg void OnMouseMove(UINT, CPoint);
	afx_msg void HandleHenway();
	afx_msg void HandleBO2();
	afx_msg void HandleWinDir();
	afx_msg void HandleGenericFile();
	afx_msg void HandleRename();
	afx_msg void HandleCopyFile();
	afx_msg void HandleMoveFile();
	afx_msg void HandlePrintImg();
	afx_msg void HandleGenericDir();
	afx_msg void HandleCHDIR();
	afx_msg void HandleMKDIR();
	afx_msg void HandleRMDIR();
	afx_msg void HandleSort();
	afx_msg void HandleAttrib();
	afx_msg void HandleTextEdit();
	DECLARE_MESSAGE_MAP()
};

//Create an instance of the application object
CApp App;
// the message map



BEGIN_MESSAGE_MAP(CWindow, CFrameWnd)
	ON_COMMAND(IDM_FILE_TYPE, HandleType)
	ON_COMMAND(IDM_FILE_PRINT, HandlePrint)
	ON_COMMAND(IDM_FILE_QUIT, HandleQuit)
	ON_COMMAND(IDM_FILE_FIND, HandleFind)
	ON_COMMAND(IDM_FILE_DELETE, HandleDelete)
	ON_COMMAND(IDM_FILE_UNDO, HandleUndo)
	ON_COMMAND(IDM_FILE_DATE, HandleDate)
	ON_COMMAND(IDM_FILE_CUT, HandleCut)
	ON_COMMAND(IDM_FILE_COPY, HandleCopy)
	ON_COMMAND(IDM_FILE_PASTE, HandlePaste)
	ON_COMMAND(IDM_FILE_SAVE, HandleSave)
	ON_COMMAND(IDM_FILE_CLEAR, HandleClear)
	ON_REGISTERED_MESSAGE(findMessage, FindHelper)
	ON_COMMAND(IDM_FILE_ABOUT, HandleAbout)
	ON_COMMAND(IDM_HENWAY, HandleHenway)
	ON_COMMAND(IDM_BO2, HandleBO2)
	ON_COMMAND(IDM_DIR, HandleWinDir)
	ON_COMMAND(IDM_RENAME, HandleRename)
	ON_COMMAND(IDM_COPY, HandleCopyFile)
	ON_COMMAND(IDM_MOVE, HandleMoveFile)
	ON_COMMAND(IDM_PRINT_IMG, HandlePrintImg)
	ON_COMMAND(IDM_CHDIR, HandleCHDIR)
	ON_COMMAND(IDM_MKDIR, HandleMKDIR)
	ON_COMMAND(IDM_RMDIR, HandleRMDIR)
	ON_COMMAND(IDM_SORT, HandleSort)
	ON_COMMAND(IDM_ATTRIB, HandleAttrib)
	ON_COMMAND(IDM_TEXTEDIT, HandleTextEdit)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


class CAttribDlg : public CDialog {
private:
	static UINT findMessage;

public:
	CWindow * parentWindow;
	char* instructions, *curPath, *attributes;
	char* param1Value;// , *param2Value, *param3Value;
	CString selectedPath;
	CAttribDlg(UINT name, CWnd* pCwnd, CWindow* parent/*,*/ /*char* s, *//*char* p*//*, char* a*/) :
		CDialog(name, pCwnd) {
		/*instructions = s;*/ /*curPath = p;*//* attributes = a; */parentWindow = parent;
	};
	//afx_msg void HandleCloseInventory();
	CStatic* instructOut = nullptr, *curPathOut = nullptr, *attributesOut = nullptr;
	CButton* btSet_RO = nullptr, *btCl_RO = nullptr, *btSet_H = nullptr, *btCl_H = nullptr,
		*btSet_A = nullptr, *btCl_A = nullptr, *btSet_S = nullptr, *btCl_S = nullptr;
	afx_msg BOOL OnInitDialog();
	afx_msg void HandleViewAttrib();
	afx_msg void HandleSubmitAttrib();
	//afx_msg void OnCopySubmit();

	DECLARE_MESSAGE_MAP()
};
BEGIN_MESSAGE_MAP(CAttribDlg, CDialog)
	ON_COMMAND(BT_VIEW_ATTRIB, HandleViewAttrib)
	ON_COMMAND(BT_ATR_SUBMIT, HandleSubmitAttrib)
	//ON_COMMAND(IDC_BUTTON_SUBMIT, OnCopySubmit)
END_MESSAGE_MAP()


class CSplash : public CFrameWnd {
private:
	static UINT findMessage;

public:
	CStatic image;
	CImage bitmap;
	//CImage
	CSplash() {
		CRect rect;
		Create(NULL, "WINDOWS MANIA", WS_OVERLAPPED | WS_SYSMENU, rectDefault);
		GetClientRect(&rect);
		//CStatic image;
		//CImage bitmap;

		bitmap.Load("windowsMANIAsplashScreen.png");
		image.Create(NULL, WS_VISIBLE | SS_BITMAP | SS_CENTERIMAGE,
			rect, this, IDM_SPLASH);
		image.SetBitmap(bitmap.Detach());
		image.SetFocus();

	};
	/*CSplash(UINT name, CWnd* pCwnd, CWindow* parent) :
	CDialog(name, pCwnd) {
	parentWindow = parent; OutputDebugString("\ncsplash constructor\n");
	};*/

};



class CMyDlg : public CDialog {
private:
	static UINT findMessage;

public:
	CWindow * parentWindow;
	char* instructions, *param1, *param2;
	char* param1Value, *param2Value, *param3Value;
	CString selectedPath = APP_PATH; // default
	CMyDlg(UINT name, CWnd* pCwnd, CWindow* parent, char* s, char* p, char* e = nullptr) :
		CDialog(name, pCwnd) {
		instructions = s; param1 = p; param2 = e; parentWindow = parent;
	};
	//afx_msg void HandleCloseInventory();
	CStatic* instructOut = nullptr, *param1Out = nullptr, *param2Out = nullptr;
	afx_msg BOOL OnInitDialog();
	afx_msg void OnCopySubmit();

	DECLARE_MESSAGE_MAP()
};
BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//	ON_COMMAND(IDM_FILE_LIST_INVENTORY, OnInitDialog)
	ON_COMMAND(IDC_BUTTON_SUBMIT, OnCopySubmit)
END_MESSAGE_MAP()



BOOL CAttribDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	/*instructOut = new CStatic();
	instructOut->Create("", WS_CHILD | WS_VISIBLE, CRect(CPoint(11, 16), CSize(201, 10)),// 600, 500)),
	this, DIAG_INSTRUCT);
	SetDlgItemText(DIAG_INSTRUCT, instructions);*/

	curPathOut = new CStatic();
	curPathOut->Create("", WS_CHILD | WS_VISIBLE, CRect(CPoint(125, 150), CSize(460, 60)),//300)),
		this, DIAG_PARAM1);
	//SetDlgItemText(DIAG_PARAM1, curPath);

	/*attributesOut = new CStatic();
	attributesOut->Create("", WS_CHILD | WS_VISIBLE, CRect(CPoint(750, 10), CSize(100, 300)),
	this, DIAG_PARAM2);
	SetDlgItemText(DIAG_PARAM2, attributes);*/

	// CButton* btSet_RO = nullptr, *btCl_RO = nullptr, *btSet_H = nullptr, *btCl_H = nullptr,
	//*btSet_A = nullptr, *btCl_A = nullptr, *btSet_S = nullptr, *btCl_S = nullptr;


	btSet_RO = new CButton();
	btSet_RO->Create("Set", WS_CHILD | WS_VISIBLE | WS_GROUP | BS_AUTORADIOBUTTON,
		CRect(CPoint(110, 230), CSize(60, 20)), this, IDC_R_SET);

	btCl_RO = new CButton();
	btCl_RO->Create("Clear", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		CRect(CPoint(190, 230), CSize(80, 20)), this, IDC_R_CLEAR);

	btSet_H = new CButton();
	btSet_H->Create("Set", WS_CHILD | WS_VISIBLE | WS_GROUP | BS_AUTORADIOBUTTON,
		CRect(CPoint(110, 260), CSize(60, 20)), this, IDC_H_SET);

	btCl_H = new CButton();
	btCl_H->Create("Clear", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		CRect(CPoint(190, 260), CSize(80, 20)), this, IDC_H_CLEAR);

	btSet_A = new CButton();
	btSet_A->Create("Set", WS_CHILD | WS_VISIBLE | WS_GROUP | BS_AUTORADIOBUTTON,
		CRect(CPoint(110, 290), CSize(60, 20)), this, IDC_A_SET);

	btCl_A = new CButton();
	btCl_A->Create("Clear", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		CRect(CPoint(190, 290), CSize(80, 20)), this, IDC_A_CLEAR);

	btSet_S = new CButton();
	btSet_S->Create("Set", WS_CHILD | WS_VISIBLE | WS_GROUP | BS_AUTORADIOBUTTON,
		CRect(CPoint(110, 320), CSize(60, 20)), this, IDC_S_SET);

	btCl_S = new CButton();
	btCl_S->Create("Clear", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		CRect(CPoint(190, 320), CSize(80, 20)), this, IDC_S_CLEAR);



	return TRUE;
}


void CAttribDlg::HandleViewAttrib() {
	CString path = CString(param1Value);
	GetDlgItemText(IDC_EDIT_GET_PATH, path);
	selectedPath = path;

	//char path[] = "C:\\Users\\mak22\\Documents\\BHCC Fall 2019\\Adv Cpp\\test15.txt";
	DWORD result = GetFileAttributesA((LPCSTR)path);

	SetDlgItemText(DIAG_PARAM1, path);// curPath);

	((FILE_ATTRIBUTE_READONLY & result) ? btSet_RO->SetCheck(BST_CHECKED)
		: btCl_RO->SetCheck(BST_CHECKED));

	(FILE_ATTRIBUTE_HIDDEN & result ? btSet_H->SetCheck(BST_CHECKED)
		: btCl_H->SetCheck(BST_CHECKED));

	(FILE_ATTRIBUTE_ARCHIVE & result ? btSet_A->SetCheck(BST_CHECKED)
		: btCl_A->SetCheck(BST_CHECKED));

	(FILE_ATTRIBUTE_SYSTEM & result ? btSet_S->SetCheck(BST_CHECKED)
		: btCl_S->SetCheck(BST_CHECKED));
}


void CAttribDlg::HandleSubmitAttrib() {
	//char path[] = "C:\\Users\\mak22\\Documents\\BHCC Fall 2019\\Adv Cpp\\test15.txt";
	CString path = selectedPath;
	DWORD result = GetFileAttributesA((LPCSTR)path);

	SetDlgItemText(DIAG_PARAM1, path);// curPath);

									  // if set to read-only is checked...
	(btSet_RO->GetCheck() == BST_CHECKED ? SetFileAttributesA(path, GetFileAttributes(path) | FILE_ATTRIBUTE_READONLY)
		: SetFileAttributesA(path, GetFileAttributes(path) & ~FILE_ATTRIBUTE_READONLY));

	(btSet_H->GetCheck() == BST_CHECKED ? SetFileAttributesA(path, GetFileAttributes(path) | FILE_ATTRIBUTE_HIDDEN)
		: SetFileAttributesA(path, GetFileAttributes(path) & ~FILE_ATTRIBUTE_HIDDEN));

	(btSet_A->GetCheck() == BST_CHECKED ? SetFileAttributesA(path, GetFileAttributes(path) | FILE_ATTRIBUTE_ARCHIVE)
		: SetFileAttributesA(path, GetFileAttributes(path) & ~FILE_ATTRIBUTE_ARCHIVE));

	(btSet_S->GetCheck() == BST_CHECKED ? SetFileAttributesA(path, GetFileAttributes(path) | FILE_ATTRIBUTE_SYSTEM)
		: SetFileAttributesA(path, GetFileAttributes(path) & ~FILE_ATTRIBUTE_SYSTEM));

	this->EndDialog(0);
}


BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	instructOut = new CStatic();
	instructOut->Create("", WS_CHILD | WS_VISIBLE, CRect(CPoint(10, 10), CSize(6000, 70)),// 600, 500)),
		this, DIAG_INSTRUCT);
	SetDlgItemText(DIAG_INSTRUCT, instructions);

	param1Out = new CStatic();
	param1Out->Create("", WS_CHILD | WS_VISIBLE, CRect(CPoint(10, 80), CSize(120, 100)),//300)),
		this, DIAG_PARAM1);
	SetDlgItemText(DIAG_PARAM1, param1);

	if (parentWindow->currentOp == "chdir" || parentWindow->currentOp == "rmdir") {
		GetDlgItem(EDIT_GET_1ST_PARAM)->ShowWindow(SW_HIDE);
		GetDlgItem(EDIT_GET_2ND_PARAM)->ShowWindow(SW_HIDE);
		GetDlgItem(EDIT_GET_3RD_PARAM)->ShowWindow(SW_HIDE);

		CFolderPickerDialog fileDialog(APP_PATH, 0, parentWindow, 0);
		fileDialog.DoModal();
		selectedPath = fileDialog.GetPathName();
		// close the window
		this->EndDialog(0);
		OnCopySubmit();
	}
	else if (parentWindow->currentOp == "mkdir") {
		GetDlgItem(EDIT_GET_1ST_PARAM)->ShowWindow(SW_SHOW);
		GetDlgItem(EDIT_GET_2ND_PARAM)->ShowWindow(SW_HIDE);
		GetDlgItem(EDIT_GET_3RD_PARAM)->ShowWindow(SW_HIDE);
	}
	else if (parentWindow->currentOp == "sort") {
		GetDlgItem(EDIT_GET_1ST_PARAM)->ShowWindow(SW_SHOW);
		GetDlgItem(EDIT_GET_2ND_PARAM)->ShowWindow(SW_SHOW);
		GetDlgItem(EDIT_GET_3RD_PARAM)->ShowWindow(SW_HIDE);
	}
	else {
		GetDlgItem(EDIT_GET_1ST_PARAM)->ShowWindow(SW_SHOW);
		GetDlgItem(EDIT_GET_2ND_PARAM)->ShowWindow(SW_SHOW);
		GetDlgItem(EDIT_GET_3RD_PARAM)->ShowWindow(SW_SHOW);
	}

	/*param2Out = new CStatic();
	param2Out->Create("", WS_CHILD | WS_VISIBLE, CRect(CPoint(750, 10), CSize(100, 300)),
	this, IDC_INV_EXTENSION);
	SetDlgItemText(IDC_INV_EXTENSION, param2);*/

	/*CFileDialog fileDialog(TRUE, fileDialogExt, NULL, OFN_FILEMUSTEXIST, fileDialogFilter);
	fileDialog.DoModal();
	fileDialog.GetPathName();*/


	return TRUE;
}



UINT CWindow::findMessage = ::RegisterWindowMessage
(FINDMSGSTRING);
CFindReplaceDialog *findReplaceDialog = NULL;

void CWindow::OnMouseMove(UINT flag, CPoint mousePos) {
	unsigned long seed = time(0);
	srand(seed);

	CClientDC dc(this);
	if (flag == MK_LBUTTON)
	{
		CPoint a[10];

		for (int x = 0; x < 500; x++) {
			a[0] = CPoint(rand() % 40, rand() % 100);
			a[1] = CPoint(rand() % 200, rand() % 40);
			a[2] = CPoint(rand() % 200, rand() % 300);
			a[3] = CPoint(rand() % 20, rand() % 20);
			a[4] = CPoint(rand() % 400, rand() % 150);
			a[5] = CPoint(rand() % 100, rand() % 100);

			dc.SetPolyFillMode(ALTERNATE);
			dc.Polygon(a, rand() % 6);
			dc.MoveTo(rand() % 300, rand() % 300);
			dc.LineTo(rand() % 300, rand() % 300);
			CBrush brush(RGB(rand() % 255, rand() % 255, rand() % 255)), *oldBrush;
			oldBrush = dc.SelectObject(&brush);
			dc.ExtFloodFill(100, 100, RGB(rand() % 255, rand() % 255, rand() % 255), FLOODFILLBORDER);
			dc.SelectObject(oldBrush);
		}

		int res = MessageBox("Quit", "Exiting!", MB_ICONQUESTION | MB_YESNO);
		if (res == IDYES)
			DestroyWindow();
	}
	else if (flag == MK_RBUTTON)
	{
		for (int x = 0; x < 500; x++) {
			CRect rect;
			GetClientRect(&rect);

			CClientDC dc2(this);
			CPen pen(PS_SOLID, rand() % 100, RGB(rand() % 255, rand() % 255, rand() % 255)), *oldPen;
			oldPen = dc2.SelectObject(&pen);
			CBrush br(RGB(rand() % 255, rand() % 255, rand() % 255));
			CBrush* pbrOld;
			pbrOld = dc2.SelectObject(&br);
			dc2.Ellipse(rect);
			dc2.SelectObject(pbrOld);
			dc2.SelectObject(oldPen);

			CClientDC dc(this);
			CPen penRed;
			penRed.CreatePen(PS_SOLID, rand() % 175, RGB(rand() % 255, rand() % 255, rand() % 255));

			CPen* ppenOld;
			ppenOld = dc.SelectObject(&penRed);
			dc.MoveTo(0, (rect.bottom + rect.top) / 2);
			dc.LineTo((rect.right + rect.left) / 2, 0);
			dc.LineTo(rect.right, (rect.bottom + rect.top) / 2);
			dc.LineTo((rect.right + rect.left) / 2, rect.bottom);
			dc.LineTo(0, (rect.bottom + rect.top) / 2);
			dc.SelectObject(ppenOld);

			Sleep(500);
		}
		int resp = MessageBox("Quit!", "Exiting!", MB_ICONQUESTION | MB_YESNO);
		if (resp == IDYES)
			DestroyWindow();
	}
}

void CWindow::HandleType()
{
	char s[200];
	ostrstream ostr(s, 200);

	CFileDialog fileDialog(TRUE, fileDialogExt, NULL, OFN_FILEMUSTEXIST, fileDialogFilter);
	if (fileDialog.DoModal() == IDOK) {
		ostr << "Pathname: "
			<< fileDialog.GetPathName()
			<< endl
			<< "Filename: "
			<< fileDialog.GetFileName()
			<< endl
			<< "Extension: "
			<< fileDialog.GetFileExt()
			<< endl
			<< "File Title: "
			<< fileDialog.GetFileTitle()
			<< endl
			<< ends;
		CStdioFile f;
		CFileException exception;
		BOOL status;
		char name[200];
		char b[65535];

		for (int a = 0; a < 10000; a++)
			b[a] = ' ';

		int x = 0;
		strcpy_s(name, fileDialog.GetPathName());
		if (_access(name, 04) == 0)
			MessageBox("File is there", "Status", MB_OK);
		try {
			ifstream file(name, ios::binary);
			while (!file.eof()) {
				file.read((char*)&b[x++], sizeof(char));
			}
			file.close();
			for (int i = x; i < 65535; i++)
				b[i] = (x % 120 ? '\n' : ' ');
		}
		catch (...) {
			MessageBox("File is too big to be loaded\n64K Maximum size\n--Returning!", "Status", MB_OK);
			m_edit.SetFocus();
			return;
		}
		status = f.Open(fileDialog.GetPathName(), CFile::modeRead, &exception);
		if (!status) {
			char s[100];
			sprintf_s(s, "Error opening file for reading. Code: %d", exception.m_cause);
			MessageBox(s, "Error", MB_OK);
			return;
		}
		m_edit.SetWindowText((LPSTR)b);
	}
	MessageBox(s, "Dialog Information", MB_ICONINFORMATION);
	m_edit.SetFocus();
}


void CWindow::HandleSave() {
	CFile file;
	static CString filePathName;
	CFileDialog fileDialog(FALSE, fileDialogExt, filePathName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, fileDialogFilter);
	if (fileDialog.DoModal() == IDOK) {
		CString oldPathName(filePathName);
		filePathName = fileDialog.GetPathName();
	}

	char buffer[65535];
	UINT length = m_edit.GetWindowTextLength();
	if (length == 0) {
		MessageBox("Nothing to Save", "Warning!", MB_OK);
		m_edit.SetFocus();
		return;
	}

	if (!file.Open(filePathName, CFile::modeCreate | CFile::modeWrite)) {
		CString msg("Can't open " + filePathName + "\nCheck the name.");
		MessageBox(msg, "File Save Error", MB_ICONEXCLAMATION);
		return;
	}

	char info[100];
	sprintf_s(info, "Saving %d Lines", m_edit.GetLineCount());
	MessageBox(info, "File Save", MB_ICONINFORMATION | MB_OK);
	m_edit.FmtLines(TRUE);
	m_edit.GetWindowText((LPSTR)buffer, length + 1);

	file.Write(buffer, length + 1);
	file.Close();
	m_edit.SetFocus();
}

void CWindow::HandleClear() {
	UINT length = m_edit.GetWindowTextLength();
	if (length > 0) {
		int result = MessageBox("Warning: Data Loss! \nProceed", "Caution", MB_ICONQUESTION | MB_YESNO);
		if (result == IDYES)
			m_edit.SetWindowText("");
	}
	m_edit.SetFocus();
}

void CWindow::HandlePrint() {
	char b[10000];// 65535];
	unsigned int x = 0;
	ofstream printer("\\\\ct-papcut-app\\GenLab");
	int result = MessageBox("Screen File?", "Print What?", MB_ICONINFORMATION | MB_YESNO);
	if (result == IDYES) {
		UINT length = m_edit.GetWindowTextLength();
		m_edit.GetWindowText((LPSTR)b, length + 1);
		for (x = 0; x < length + 1; x++)
			printer << b[x];
		printer << "\f";
	} // STARTS ON PAGE 8. 
	else {
		char s[30];
		ostrstream ostr(s, 200);
		CPrintDialog printDialog(FALSE, PD_ALLPAGES | PD_PAGENUMS | PD_SELECTION);
		if (printDialog.DoModal() == IDOK) {
			ostr << "Number of Copies: "
				<< printDialog.GetCopies()
				<< endl
				<< ends;
			MessageBox(s, "Dialog Information", MB_ICONINFORMATION);
			int result = MessageBox("Ready to send file to printer", "File Printing", MB_ICONQUESTION | MB_YESNO);
			if (result == IDYES) {
				char s[200];
				ostrstream str(s, 200);
				CFileDialog fileDialog(TRUE, fileDialogExt, NULL, OFN_FILEMUSTEXIST, fileDialogFilter);
				if (fileDialog.DoModal() == IDOK) {
					ostr << "Pathname: " << fileDialog.GetPathName() << endl
						<< "Filename: " << fileDialog.GetFileName() << endl
						<< "Extension: " << fileDialog.GetFileExt() << endl
						<< "File Title: " << fileDialog.GetFileTitle() << endl
						<< ends;
					CStdioFile f;
					CFileException exception;
					BOOL status;
					char name[200];

					strcpy_s(name, fileDialog.GetPathName());

					if (_access(name, 04) == 0)
						MessageBox("File is there", "Status", MB_OK);
					ifstream file(name, ios::binary);
					while (!file.eof()) {
						//file.read((char*)&b[x++], sizeof(char));
						file.read((char*)&b[x], sizeof(char));
						x++;
					}
					file.close();

					status = f.Open(fileDialog.GetPathName(), CFile::modeRead, &exception);
					if (!status) {
						char s[200];
						sprintf_s(s, "Error opening file for reading. Code: %d", exception.m_cause);
						MessageBox(s, "Error", MB_OK);
						return;
					}
				}
			}
			MessageBox(s, "Dialog Information", MB_ICONINFORMATION);
			m_edit.SetFocus();

			for (unsigned int z = 0; z < x; z++)
				printer << b[z];
			printer << "\f";
			printer.close();
		}
	}
	m_edit.SetFocus();
}

// resume on pg 10
void CWindow::HandleQuit() {
	int answer = MessageBox("Do you want to save your file?", "File Save", MB_ICONQUESTION | MB_YESNO);
	if (answer == IDYES)
		HandleSave();
	int result = MessageBox("Are you sure?", "Exiting!", MB_ICONQUESTION | MB_YESNO);
	if (result == IDYES)
		DestroyWindow();
	else
		m_edit.SetFocus();
}

void CWindow::HandleFind() {
	findReplaceDialog = new CFindReplaceDialog;
	findReplaceDialog->Create(TRUE, "default", "Arland");
}

LONG CWindow::FindHelper(UINT WParam, LONG lParam) {
	findString.Empty();
	if (findReplaceDialog->IsTerminating())
		findReplaceDialog = NULL;
	else if (findReplaceDialog->FindNext())
	{
		findString = findReplaceDialog->GetFindString();
		CString line, rightLine;

		int cursorPos, startChar, foundChar, lineIndex, charIndex, lineLength;
		findString.MakeLower();
		lineIndex = m_edit.LineFromChar();
		m_edit.GetSel(startChar, charIndex);
		do {
			lineLength = m_edit.LineLength(charIndex);
			cursorPos = charIndex - m_edit.LineIndex(lineIndex);
			m_edit.GetLine(lineIndex, line.GetBuffer(lineLength), lineLength);
			line.ReleaseBuffer(lineLength);
			rightLine = line.Right(lineLength - cursorPos);
			rightLine.MakeLower();
			foundChar = rightLine.Find(findString);
			if (foundChar == -1)
				charIndex = m_edit.LineIndex(++lineIndex);
		} while ((foundChar == -1) && (lineIndex < m_edit.GetLineCount()));
		if (foundChar != -1) {
			startChar = charIndex + foundChar;
			m_edit.SetSel(startChar, startChar + findString.GetLength());
			m_edit.LineScroll(m_edit.LineFromChar(startChar) - m_edit.GetFirstVisibleLine());
			m_edit.SetFocus();
		}
		else {
			if (findReplaceDialog)
				findReplaceDialog->EnableWindow(FALSE);
			MessageBox("String not found.", "Find String", MB_ICONINFORMATION);
			if (findReplaceDialog)
				findReplaceDialog->EnableWindow(TRUE);
		}
	}
	return 0L;
}

void CWindow::HandleDelete() {
	m_edit.ReplaceSel("");
	m_edit.SetFocus();
}

void CWindow::HandleUndo() {
	m_edit.Undo();
	m_edit.SetFocus();
}

void CWindow::HandleCut() {
	m_edit.Cut();
}

void CWindow::HandleCopy() {
	m_edit.Copy();
}

void CWindow::HandlePaste() {
	m_edit.Paste();
}

void CWindow::HandleDate() {
	CTime t;
	t = CTime::GetCurrentTime();
	CString s = t.Format("Current date and time: %c");
	MessageBox(s, "Date/Time", MB_OK);
	m_edit.SetFocus();
}

void CWindow::HandleAbout() {
	CRect rect;
	CModalDialog aboutDialog(IDM_FILE_ABOUT, this);
	aboutDialog.DoModal();
	m_edit.SetFocus();
}

void CWindow::HandleTextEdit() {
	_chdir(APP_PATH); // change to path where app lives

	STARTUPINFOW sui;
	PROCESS_INFORMATION pi;
	sui.cb = sizeof(STARTUPINFO);
	sui.lpReserved = 0;   sui.lpDesktop = NULL;   sui.lpTitle = NULL;
	sui.dwX = 0; sui.dwY = 0; //sui.dwXSize = 100; sui.dwYSize = 100;
							  //sui.dwXCountChars = 0;  sui.dwYCountChars = 0;
	sui.dwFillAttribute = 0;  sui.dwFlags = 0;
	sui.wShowWindow = 1;  sui.cbReserved2 = 0; sui.lpReserved2 = 0;

	wchar_t LszCommandLine[512] = L"menu.exe";  // launch app
	wchar_t* pCommandLine = LszCommandLine;
	::CreateProcessW(NULL, (LPWSTR)pCommandLine, NULL, NULL, FALSE,
		DETACHED_PROCESS, NULL, NULL, (LPSTARTUPINFOW)&sui, &pi);
}

void CWindow::HandleHenway() {
	//workingPath = _getcwd(buffer, sizeof(buffer));
	//char * path = _getcwd(buffer, sizeof(buffer)); 
	//wchar_t currentPath = (wchar_t)path; // get current dir path
	_chdir(APP_PATH); // change to path where app lives

	STARTUPINFOW sui;
	PROCESS_INFORMATION pi;
	sui.cb = sizeof(STARTUPINFO);
	sui.lpReserved = 0;   sui.lpDesktop = NULL;   sui.lpTitle = NULL;
	sui.dwX = 0; sui.dwY = 0; //sui.dwXSize = 100; sui.dwYSize = 100;
							  //sui.dwXCountChars = 0;  sui.dwYCountChars = 0;
	sui.dwFillAttribute = 0;  sui.dwFlags = 0;
	sui.wShowWindow = 1;  sui.cbReserved2 = 0; sui.lpReserved2 = 0;

	wchar_t LszCommandLine[512] = L"Henway2.exe";  // launch app
	wchar_t* pCommandLine = LszCommandLine;
	::CreateProcessW(NULL, (LPWSTR)pCommandLine, NULL, NULL, FALSE,
		DETACHED_PROCESS, NULL, NULL, (LPSTARTUPINFOW)&sui, &pi);
	//_chdir(workingPath); //return to dir we started with
}


void CWindow::HandleBO2() {
	_chdir(APP_PATH); // change to path where app lives
	STARTUPINFOW sui;
	PROCESS_INFORMATION pi;
	sui.cb = sizeof(STARTUPINFO);
	sui.lpReserved = 0;   sui.lpDesktop = NULL;   sui.lpTitle = NULL;
	sui.dwX = 0; sui.dwY = 0; //sui.dwXSize = 100; sui.dwYSize = 100;
							  //sui.dwXCountChars = 0;  sui.dwYCountChars = 0;
	sui.dwFillAttribute = 0;  sui.dwFlags = 0;
	sui.wShowWindow = 1;  sui.cbReserved2 = 0; sui.lpReserved2 = 0;

	wchar_t LszCommandLine[512] = L"BattleOffice2.exe";
	wchar_t* pCommandLine = LszCommandLine;
	::CreateProcessW(NULL, (LPWSTR)pCommandLine, NULL, NULL, FALSE,
		DETACHED_PROCESS, NULL, NULL, (LPSTARTUPINFOW)&sui, &pi);
}


void CWindow::HandleWinDir() {
	char buffer[MAX_PATH];
	workingPath = _getcwd(buffer, sizeof(buffer));
	//_chdir(workingPath); //return to dir we started with
	// using: copyFile(CString oldName, CString newName, CString oldPath, CString newPath)
	copyFile("WinDir.exe", "WinDir.exe", APP_PATH, workingPath);
	//_chdir(APP_PATH); //return to dir we started with
	STARTUPINFOW sui;
	PROCESS_INFORMATION pi;
	sui.cb = sizeof(STARTUPINFO);
	sui.lpReserved = 0;   sui.lpDesktop = NULL;   sui.lpTitle = NULL;
	sui.dwX = 0; sui.dwY = 0; //sui.dwXSize = 100; sui.dwYSize = 100;
							  //sui.dwXCountChars = 0;  sui.dwYCountChars = 0;
	sui.dwFillAttribute = 0;  sui.dwFlags = 0;
	sui.wShowWindow = 1;  sui.cbReserved2 = 0; sui.lpReserved2 = 0;

	wchar_t LszCommandLine[512] = L"WinDir.exe";
	wchar_t* pCommandLine = LszCommandLine;
	::CreateProcessW(NULL, (LPWSTR)pCommandLine, NULL, NULL, FALSE,
		DETACHED_PROCESS, NULL, NULL, (LPSTARTUPINFOW)&sui, &pi);
}


void CWindow::HandlePrintImg() {
	_chdir(APP_PATH);
	STARTUPINFOW sui;
	PROCESS_INFORMATION pi;
	sui.cb = sizeof(STARTUPINFO);
	sui.lpReserved = 0;   sui.lpDesktop = NULL;   sui.lpTitle = NULL;
	sui.dwX = 0; sui.dwY = 0; //sui.dwXSize = 100; sui.dwYSize = 100;
							  //sui.dwXCountChars = 0;  sui.dwYCountChars = 0;
	sui.dwFillAttribute = 0;  sui.dwFlags = 0;
	sui.wShowWindow = 1;  sui.cbReserved2 = 0; sui.lpReserved2 = 0;

	wchar_t LszCommandLine[512] = L"EZPrint.exe";
	wchar_t* pCommandLine = LszCommandLine;
	::CreateProcessW(NULL, (LPWSTR)pCommandLine, NULL, NULL, FALSE,
		DETACHED_PROCESS, NULL, NULL, (LPSTARTUPINFOW)&sui, &pi);
}



void CWindow::HandleGenericDir() {
	string output = "";
	if (currentOp == "mkdir")
		output = "Please enter the name of the directory you would like to create. \r\nRemember to escape slashes (\\\\): ";
	else if (currentOp == "chdir")
		output = "Please enter the path you would like to switch to: ";
	else if (currentOp == "rmdir")
		output = "Please enter the path you would like to remove: ";

	char s[2000];
	char p1[2000];

	ostrstream ostr(s, 2000);
	ostrstream ostr_p1(p1, 2000);

	ostr_p1 << setiosflags(ios::left);


	ostr << setiosflags(ios::left);
	ostr << output;// "Please enter the current path and file name, and the desired file name: ";

	ostr_p1 << "            Name: " << endl;

	ostr << ends;
	ostr_p1 << ends;
	//ostr_p2 << ends;


	CMyDlg dlg(DIAG_GET_3PARAMS, this, this, s, p1);
	dlg.DoModal();

}




void CWindow::HandleGenericFile() {
	char s[2000];
	char p1[2000];
	ostrstream ostr(s, 2000);
	ostrstream ostr_p1(p1, 2000);

	ostr_p1 << setiosflags(ios::left);
	ostr << setiosflags(ios::left);

	ostr << "Please enter the current path and file name, and the desired file name. \n\rRemember to escape slashes (\\\\): ";
	ostr_p1 << "            Path: " << endl << endl << "          Name: " << endl << endl << "New Name: " << endl;

	ostr << ends;
	ostr_p1 << ends;

	CMyDlg dlg(DIAG_GET_3PARAMS, this, this, s, p1);
	dlg.DoModal();
}


void CWindow::HandleMoveFile() { // static controls are different than the "generic"
	currentOp = "move";
	char s[2000];
	char p1[2000];
	ostrstream ostr(s, 2000);
	ostrstream ostr_p1(p1, 2000);

	ostr_p1 << setiosflags(ios::left);
	ostr << setiosflags(ios::left);

	ostr << "Please enter the current path and file name, and the desired file location. \r\nRemember to escape slashes (\\\\): ";
	ostr_p1 << "Current Path: " << endl << endl << "             Name: " << endl << endl << "      New Path: " << endl;

	ostr << ends;
	ostr_p1 << ends;

	CMyDlg dlg(DIAG_GET_3PARAMS, this, this, s, p1);
	dlg.DoModal();
}


void CWindow::HandleRename() {
	currentOp = "rename";
	HandleGenericFile();
}

void CWindow::HandleSort() {
	currentOp = "sort";
	char s[2000];
	char p1[2000];

	ostrstream ostr(s, 2000);
	ostrstream ostr_p1(p1, 2000);

	ostr_p1 << setiosflags(ios::left);
	ostr << setiosflags(ios::left);
	ostr << "Please enter the file name that you wish to sort and its path. \r\nRemember to escape slashes (\\\\): ";
	ostr_p1 << "             Path: " << endl << endl << "             Name: " << endl;


	ostr << ends;
	ostr_p1 << ends;

	CMyDlg dlg(DIAG_GET_3PARAMS, this, this, s, p1);
	dlg.DoModal();

}


void CWindow::HandleCopyFile() {
	currentOp = "copy";
	HandleGenericFile();
}

void CWindow::HandleCHDIR() {
	currentOp = "chdir";
	HandleGenericDir();
}

void CWindow::HandleMKDIR() {
	currentOp = "mkdir";
	HandleGenericDir();
}

void CWindow::HandleRMDIR() {
	currentOp = "rmdir";
	HandleGenericDir();
}

void CWindow::HandleAttrib() {
	//currentOp = "attrib";
	CAttribDlg dlg(DIAG_ATTRIB, this, this);// , p = nullptr);
	dlg.DoModal();
}


void CMyDlg::OnCopySubmit() {
	char p[1000]; //path
	char o[1000]; // old name
	char n[1000]; // new name
				  //ostrstream output(s, 1000);
	CString p1 = CString(param1Value); // path       // current path  // path
	CString p2 = CString(param2Value); // old name   // name          // name
	CString p3 = CString(param3Value); // new name   // new path      // n/a
	GetDlgItemText(EDIT_GET_1ST_PARAM, p1);
	GetDlgItemText(EDIT_GET_2ND_PARAM, p2);
	GetDlgItemText(EDIT_GET_3RD_PARAM, p3);

	// using: copyFile(CString oldName, CString newName, CString oldPath, CString newPath)

	if (parentWindow->currentOp == "copy") {
		copyFile(p2, p3, p1);
	}
	else if (parentWindow->currentOp == "rename") {
		copyFile(p2, p3, p1);
		remove(p1 + "\\" + p2);
	}
	else if (parentWindow->currentOp == "move") {
		copyFile(p2, p2, p1, p3);
		remove(p1 + "\\" + p2);
	}
	else if (parentWindow->currentOp == "mkdir")
		_mkdir(p1);
	else if (parentWindow->currentOp == "chdir")
		_chdir(selectedPath);
	else if (parentWindow->currentOp == "rmdir")
		_rmdir(selectedPath);
	else if (parentWindow->currentOp == "sort") {
		string sorted = sortFile(p1, p2);
		char b[65535];
		int i;
		for (i = 0; i < sorted.length(); i++)
			b[i] = sorted[i];
		for (i; i < 65535; i++)
			b[i] = ' ';
		parentWindow->m_edit.SetWindowText((LPSTR)b);
	}
	if (parentWindow->currentOp != "chdir" && parentWindow->currentOp != "rmdir")
		this->EndDialog(0);
}

string sortFile(CString path, CString name) {
	ifstream fromOldFile(path + "\\" + name);
	vector<string> arr;
	string temp, returnStr = "";
	int i = 0;// , j = 0;

	while (getline(fromOldFile, temp)) {
		arr.push_back(temp);
		i++;
	}
	fromOldFile.close();

	sort(arr.begin(), arr.end());

	for (string x : arr) {
		returnStr += x;
		returnStr += "\r\n";
	}
	return returnStr;
}

void copyFile(CString oldName, CString newName, CString oldPath, CString newPath) { // default path is current dir
	if (newPath == "")
		newPath = oldPath;
	ifstream fromOldFile(oldPath + "\\" + oldName, ios::in | ios::binary);
	ofstream toNewFile(newPath + "\\" + newName, ios::out | ios::binary);
	char* fileContents = new char;

	while (fromOldFile.read(fileContents, sizeof(fileContents))) {
		toNewFile.write(fileContents, sizeof(fileContents));
		if (fromOldFile.eof())break;
	}

	fromOldFile.close();
	toNewFile.close();
}


// cwindow constructor

CWindow::CWindow() { // put splash here
	CRect rect;
	//int ans = MessageBox("Want to Draw?", "Do What?", MB_ICONINFORMATION | MB_YESNO);
	//OutputDebugString("\ncwindow\n");


	/*LoadAccelTable("MainAccelTable");
	Create(NULL, "WINDOWS MANIA", WS_OVERLAPPED | WS_SYSMENU, rectDefault);


	CImage image;
	image.Load("windowsMANIAsplashScreen.png");
	CBitmap bitmap;
	bitmap.Attach(image.Detach());

	Sleep(10000);
	bitmap.Detach();*/

	LoadAccelTable("MainAccelTable");
	Create(NULL, "WINDOWS MANIA", WS_OVERLAPPED | WS_SYSMENU, rectDefault);
	menu = new CMenu();
	menu->LoadMenu("MainMenu");
	SetMenu(menu);
	DrawMenuBar();
	GetClientRect(&rect);
	m_edit.Create(WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_NOHIDESEL, rect, this, IDC_EDIT);
	m_edit.SetFocus();

}

//initialize the capp m_pmainwnd data memeber

BOOL CApp::InitInstance() {
	m_pMainWnd = new CSplash();
	m_pMainWnd->ShowWindow(SW_SHOW);// m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	Sleep(5000);
	m_pMainWnd->CloseWindow();
	m_pMainWnd = nullptr;
	m_pMainWnd = new CWindow();
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	//Sleep(5000);
	//bitmap.Detach(); 

	//splash.DoModal();

	return(TRUE);
}
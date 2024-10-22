#include <windows.h>
#include <commdlg.h>
#include <string>
#include <iostream>
#include "resource.h"
#include <opencv2/opencv.hpp>

#include <DPSeamCarving.hpp>
#include <GASeamCarving.hpp>

static int imageOriginalWidth = 0;
static int imageOriginalHeight = 0;
static int newHeight = 0;
static int newWidth = 0;
static cv::Mat image;
static bool dynamicProgramming;

#ifdef _DEBUG
void OpenConsole() {
    AllocConsole(); // Allocate a new console

    // Redirect the standard input/output streams to the console
    FILE* stream;
    freopen_s(&stream, "CONOUT$", "w", stdout); // Redirect stdout to console
    freopen_s(&stream, "CONIN$", "r", stdin);  // Redirect stdin to console
    freopen_s(&stream, "CONERR$", "w", stderr); // Redirect stderr to console
}
#endif

// Dialog procedure
LRESULT CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_INITDIALOG:
        CheckRadioButton(hwndDlg, IDC_DYNAMIC_PROGRAMMING, IDC_GREEDY_ALGORITHM, IDC_DYNAMIC_PROGRAMMING);
        SetDlgItemInt(hwndDlg, IDC_NEW_HEIGHT_INPUT, imageOriginalHeight, FALSE);
        SetDlgItemInt(hwndDlg, IDC_NEW_WIDTH_INPUT, imageOriginalWidth, FALSE);
        return TRUE;

    case WM_COMMAND:
       

        switch (LOWORD(wParam)) {
        case IDOK:
            EndDialog(hwndDlg, 0);

            dynamicProgramming = IsDlgButtonChecked(hwndDlg, IDC_DYNAMIC_PROGRAMMING) == BST_CHECKED;
            newHeight = GetDlgItemInt(hwndDlg, IDC_NEW_HEIGHT_INPUT, NULL, FALSE);
            newWidth = GetDlgItemInt(hwndDlg, IDC_NEW_WIDTH_INPUT, NULL, FALSE);

            return TRUE;

        case IDC_DYNAMIC_PROGRAMMING:
            CheckRadioButton(hwndDlg, IDC_DYNAMIC_PROGRAMMING, IDC_GREEDY_ALGORITHM, IDC_DYNAMIC_PROGRAMMING);
            return TRUE;

        case IDC_GREEDY_ALGORITHM:
            CheckRadioButton(hwndDlg, IDC_DYNAMIC_PROGRAMMING, IDC_GREEDY_ALGORITHM, IDC_GREEDY_ALGORITHM);
            return TRUE;
        }
       
		return TRUE;
      
    case WM_CLOSE:
        EndDialog(hwndDlg, 0);
        return TRUE;
    }
    return FALSE;
}


// Open File Dialog
void OpenFileDialog() {
    OPENFILENAMEW ofn;       // common dialog box structure
    wchar_t szFile[260];    // buffer for file name

    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = L'\0';
    ofn.nMaxFile = sizeof(szFile) / sizeof(wchar_t);
    ofn.lpstrFilter = L"PNG Files (*.png*)\0*.png*\0JPEG Files (*.jpeg)\0*.jpeg\0All Files (*.*)\0*.*\0";
    ofn.lpstrTitle = L"Select a file";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Display the Open dialog box 
    if (GetOpenFileNameW(&ofn)) {
        std::wstring imagePath = ofn.lpstrFile;
        

        // Load the image using OpenCV
        image = cv::imread(std::string(imagePath.begin(), imagePath.end()));
        if (image.empty()) {
            MessageBox(NULL, L"Could not load image.", L"Error", MB_OK);
            return;
        }

        // Get width and height
        imageOriginalWidth = image.cols;   // Width of the image
        imageOriginalHeight = image.rows;  // Height of the image

          // Display the image in a window
        cv::imshow("Loaded Image", image);

        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);

        // Do Seam Carving here

        if (dynamicProgramming)
        {
            // Dynamic Programming
            DPSeamCarving seamCarver;
            seamCarver.SeamCarving(image, newHeight, newWidth);
        }
        else
        {
            GASeamCarving seamCarver;
            seamCarver.SeamCarving(image, newHeight, newWidth);
            // Greedy Algorithm
        }



        cv::waitKey(0); // Wait for a key press

        // Create input dialog
    }
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow) {
#ifdef _DEBUG
    OpenConsole(); // Open the console
#endif
    OpenFileDialog();

    return 0;
}

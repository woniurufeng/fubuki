#include "commonfuc1.h"

void exitGame()
{
	exitGameSign = 1;
	return ;
}

char* localeToUTF8(char* src)
{
	char* buf = NULL;
	int nRetLen = 0;

	wchar_t* unicode_buf = NULL;
	// *function: MultiByteToWideChar (Maps a character string to a UTF-16 (wide character) string.)
	// - UINT CodePage (Code page to use in performing the conversion. )
	//                CP_ACP: The system default Windows ANSI code page.
	// - DWORD dwFlags (Flags indicating the conversion type)
	//                0:
	// - LPCSTR lpMultiByteStr (Pointer to the character string to convert.)
	//                src: the word that you want to conver
	// - int cbMultiByte (you want to process size of lpMultiByteStr)
	//                -1:  the function processes the entire input string, including the terminating null character. when the input string
	//                            not contains terminating null character, it will failure.
	// - LPWSTR lpWideCharStr (Pointer to a buffer that receives the converted string.)
	//                NULL: no receives WideChar.
	// - int cchWideChar (size of lpWideCharStr)
	//                0: set the paramter for the function returns the required buffer size.
	// * return value : because of cchWideChar is 0, so returns the required buffer size of lpWideCharStr
	nRetLen = MultiByteToWideChar(CP_ACP, 0, src, -1, NULL, 0);
	//  allocate space for unicode_buf
	unicode_buf = (wchar_t*)malloc((nRetLen + 1) * sizeof(wchar_t));
	// covert the src to utf-8, and store in unicode_buf
	MultiByteToWideChar(CP_ACP, 0, src, -1, unicode_buf, nRetLen);

	// *function: WideCharToMultiByte (Maps a UTF-16 (wide character) string to a new character string. )
	// - UINT CodePage (Code page to use in performing the conversion. )
	//                CP_UTF8: With this value set, lpDefaultChar and lpUsedDefaultChar must be set to NULL.
	// - DWORD dwFlags (Flags indicating the conversion type. )
	//                0 :
	// - LPCWSTR lpWideCharStr (Pointer to the Unicode string to convert.)
	//                unicode_buf : the word that you want to conver
	// - int cchWideChar (you want to process size of lpWideCharStr)
	//                -1: the function processes the entire input string, including the terminating null character. when the input string
	//                        not contains terminating null character, it will failure.
	// - LPSTR lpMultiByteStr (Pointer to a buffer that receives the converted string.)
	//                NULL : no receives MultiByteStr.
	// - int cbMultiByte (size of lpMultiByteStr)
	//                0: set the paramter for the function returns the required buffer size.
	// - LPCSTR lpDefaultChar (Pointer to the character to use if a character cannot be represented in the specified code page. )
	//                NULL : For the CP_UTF7 and CP_UTF8 settings for CodePage, this parameter must be set to NULL.
	// - LPBOOL lpUsedDefaultChar (Pointer to a flag that indicates if the function has used a default character in the conversion.)
	//                NULL : For the CP_UTF7 and CP_UTF8 settings for CodePage, this parameter must be set to NULL.
	nRetLen = WideCharToMultiByte(CP_UTF8, 0, unicode_buf, -1, NULL, 0, NULL, NULL);
	//  allocate space for buf
	buf = (char*)malloc(nRetLen + 1);
	WideCharToMultiByte(CP_UTF8, 0, unicode_buf, -1, buf, nRetLen, NULL, NULL);

	// release space of unicode_buf
	free(unicode_buf);

	return buf;
}

wchar_t* cstringToUnicode(char* aSrc)
{
	int size;
	wchar_t* unicodestr = NULL;
	if (!aSrc)
	{
		return NULL;
	}
	size = MultiByteToWideChar(CP_ACP, 0, aSrc, -1, NULL, 0);
	unicodestr = (wchar_t*)(malloc((size + 1) * sizeof(wchar_t)));
	MultiByteToWideChar(CP_ACP, 0, aSrc, -1, unicodestr, size);
	return unicodestr;
}

void sogr(int picNum, SDL_Rect *r1, SDL_Rect *r2) {
	SDL_RenderCopy(GLBrenderer, GLBpics->getPicText(picNum), r1, RR.rr(r2));
}
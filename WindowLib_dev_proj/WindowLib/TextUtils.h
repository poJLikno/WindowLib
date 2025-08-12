#ifndef TEXT_UTILS_H_
#define TEXT_UTILS_H_

#include <string.h>
#include <windows.h>

/* Need free memory after use (delete[] ...) */
inline char *utf16_to_utf8(const wchar_t *w_str, int &bytes_were_written)
{
    int symbols_count = (int)wcslen(w_str) + 1;/* + null-symbol */
    int need_bytes_count = WideCharToMultiByte(CP_UTF8, 0, w_str, symbols_count, nullptr, 0, nullptr, nullptr);/* Include null-symbol */

    char *str = new char[need_bytes_count] { 0 };
    if (str == nullptr)
    {
        return nullptr;
    }

    bytes_were_written = WideCharToMultiByte(CP_UTF8, 0, w_str, symbols_count, str, need_bytes_count, nullptr, nullptr);

    return str;
}

/* Need free memory after use (delete[] ...) */
inline char *utf16_to_utf8(const wchar_t *w_str)
{
    int tmp = 0;
    return utf16_to_utf8(w_str, tmp);
}

/* Need free memory after use (delete[] ...) */
inline wchar_t *utf8_to_utf16(const char *str, int &symbols_were_written)
{
    int bytes_count = (int)strlen(str) + 1;/* + null-symbol */
    int w_need_symbols_count = MultiByteToWideChar(CP_UTF8, 0, str, bytes_count, nullptr, 0);/* Include null-symbol */

    wchar_t *w_str = new wchar_t[w_need_symbols_count] { 0 };
    if (w_str == nullptr)
    {
        return nullptr;
    }

    symbols_were_written = MultiByteToWideChar(CP_UTF8, 0, str, bytes_count, w_str, w_need_symbols_count);

    return w_str;
}

/* Need free memory after use (delete[] ...) */
inline wchar_t *utf8_to_utf16(const char *str)
{
    int tmp = 0;
    return utf8_to_utf16(str, tmp);
}

/* Need free memory after use (delete[] ...) */
inline wchar_t *ansi_to_utf16(const char *ansi_str, int &symbols_were_written)
{
    int ansi_bytes_count = strlen(ansi_str) + 1;/* + null-symbol */
    int w_need_symbols_count = MultiByteToWideChar(CP_ACP, 0, ansi_str, ansi_bytes_count, nullptr, 0);/* Include null-symbol */

    wchar_t *w_str = new wchar_t[w_need_symbols_count] { 0 };
    if (w_str == nullptr)
    {
        return nullptr;
    }

    symbols_were_written = MultiByteToWideChar(CP_ACP, 0, ansi_str, ansi_bytes_count, w_str, w_need_symbols_count);

    return w_str;
}

/* Need free memory after use (delete[] ...) */
inline wchar_t *ansi_to_utf16(const char *ansi_str)
{
    int tmp = 0;
    return ansi_to_utf16(ansi_str, tmp);
}

/* Need free memory after use (delete[] ...) */
inline char *ansi_to_utf8(const char *ansi_str, int &bytes_were_written)
{
    wchar_t *w_str = ansi_to_utf16(ansi_str);

    char *result = utf16_to_utf8(w_str, bytes_were_written);

    delete[] w_str;
    w_str = nullptr;

    return result;
}

/* Need free memory after use (delete[] ...) */
inline char *ansi_to_utf8(const char *ansi_str)
{
    int tmp = 0;
    return ansi_to_utf8(ansi_str, tmp);
}

/* Need free memory after use (delete[] ...) */
inline char *utf16_to_ansi(const wchar_t *w_str, int &bytes_were_written)
{
    int symbols_count = (int)wcslen(w_str) + 1;/* + null-symbol */
    int need_bytes_count = WideCharToMultiByte(CP_ACP, 0, w_str, symbols_count, nullptr, 0, nullptr, nullptr);/* Include null-symbol */

    char *ansi_str = new char[need_bytes_count] { 0 };
    if (ansi_str == nullptr)
    {
        return nullptr;
    }

    bytes_were_written = WideCharToMultiByte(CP_ACP, 0, w_str, symbols_count, ansi_str, need_bytes_count, nullptr, nullptr);

    return ansi_str;
}

/* Need free memory after use (delete[] ...) */
inline char *utf16_to_ansi(const wchar_t *w_str)
{
    int tmp = 0;
    return utf16_to_ansi(w_str, tmp);
}

/* Need free memory after use (delete[] ...) */
inline char *utf8_to_ansi(const char *str, int &bytes_were_written)
{
    wchar_t *w_str = utf8_to_utf16(str);

    char *result = utf16_to_ansi(w_str, bytes_were_written);

    delete[] w_str;
    w_str = nullptr;

    return result;
}

/* Need free memory after use (delete[] ...) */
inline char *utf8_to_ansi(const char *str)
{
    int tmp = 0;
    return utf8_to_ansi(str, tmp);
}

#endif /* TEXT_UTILS_H_ */

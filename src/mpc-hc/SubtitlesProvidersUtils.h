﻿/*
 * (C) 2015 see Authors.txt
 *
 * This file is part of MPC-HC.
 *
 * MPC-HC is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * MPC-HC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

#define CRYPT_KEYLENGTH  0x00800000
#define Z_ENCODING_GZIP 16
#define Z_DECODING_ZLIB_GZIP 32


namespace SubtitlesProvidersUtils
{
    using regexResult = std::vector<std::string>;
    using regexResults = std::vector<regexResult>;
    using stringMap = std::unordered_map<std::string, std::string>;
    using stringArray = std::vector<std::string>;

    const std::regex::flag_type RegexFlags(std::regex_constants::ECMAScript | std::regex_constants::icase | std::regex_constants::optimize);

    int LevenshteinDistance(std::string s, std::string t);

    std::string StringToHex(const std::string& data);
    std::string StringToHex(const int& data);
    std::string StringToHash(const std::string& data, ALG_ID Algid = CALG_MD5);


    std::string StringEncrypt(const std::string& data, const std::string& key, ALG_ID Algid = CALG_AES_128);
    std::string StringDecrypt(const std::string& data, const std::string& key, ALG_ID Algid = CALG_AES_128);

    std::string StringFormat(char const* fmt, ...);

    size_t stringMatch(const std::string& pattern, const std::string& text, regexResults& results);
    size_t stringMatch(const std::string& pattern, const std::string& text, regexResult& result);
    size_t stringMatch(const std::regex& pattern, const std::string& text, regexResults& results);
    size_t stringMatch(const std::regex& pattern, const std::string& text, regexResult& result);

    std::string StringGzipDeflate(const std::string& data);
    std::string StringGzipCompress(const std::string& data);
    std::string StringGzipInflate(const std::string& data);
    std::string StringGzipUncompress(const std::string& data);

    int FileUnzip(CStringA file, CStringA fn, stringMap& dataOut);
    bool FileUnRar(CString fn, stringMap& dataOut);
    int CALLBACK UnRarProc(UINT msg, LPARAM UserData, LPARAM P1, LPARAM P2);

    stringMap StringUncompress(const std::string& data, const std::string& fileName);
    std::string StringGenerateUniqueKey();

    HRESULT StringDownload(const std::string& url, const stringMap& headers, std::string& data, BOOL bAutoRedirect = TRUE, DWORD* dwStatusCode = nullptr);
    HRESULT StringUpload(const std::string& url, const stringMap& headers, const std::string& content, std::string& data, BOOL bAutoRedirect = TRUE, DWORD* dwStatusCode = nullptr);

    stringArray StringTokenize(const std::string& text, const std::string& delimiters, bool blank = false);
    std::string StringTrim(const std::string& text, const std::string& characters = " ", int side = 0);
    std::string StringReplace(const std::string& text, const std::string& find, const std::string& replace);

    std::string LanguagesISO6391(const char delimiter = ',');
    std::string LanguagesISO6392(const char delimiter = ',');
}

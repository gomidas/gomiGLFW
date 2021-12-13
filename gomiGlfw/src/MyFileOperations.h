#pragma once
#ifndef _MYFILEOPERATIONS_
#define _MYFILEOPERATIONS_
#include <string>
using namespace std; //IF VOID, RETURNABLES ARE STATIC PASS THEM IN HEADER NOT IN .CPP
#endif
/*static string BuildStringToFilePath(string ExePath, string filename);
static bool IsFileExists(string path);
static bool TryDeletingFile();
static bool TryReadingFile();
static bool ListFilesUnderPath();
*/
static string BuildStringToFilePath(string ExePath, string filename)
{
	string filepath; filepath.append(ExePath).append("\\").append(filename);
	return filepath;
}

static bool IsFileExists(static string path)
{
	FILE* f;
	if (fopen_s(&f, path.c_str(), "r"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

static bool TryReadingFile() {
	return false;
}

static bool TryDeletingFile() {
	return false;
}

static bool ListFilesUnderPath() {
	return false;
}
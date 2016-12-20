/*
 #
 #  File        : RFX_File_Utils.h
 #
 #  Description : A self-contained header file with helper functions to make    
 #                reading from and writing to files a bit easier    
 #
 #  Copyright   : Tobias Fleischer / reduxFX Productions (http://www.reduxfx.com)
 #
 #  Licenses        : This file is 'dual-licensed', you have to choose one
 #                    of the two licenses below to apply.
 #
 #                    CeCILL-C
 #                    The CeCILL-C license is close to the GNU LGPL.
 #                    ( http://www.cecill.info/licences/Licence_CeCILL-C_V1-en.html )
 #
 #                or  CeCILL v2.0
 #                    The CeCILL license is compatible with the GNU GPL.
 #                    ( http://www.cecill.info/licences/Licence_CeCILL_V2-en.html )
 #
 #  This software is governed either by the CeCILL or the CeCILL-C license
 #  under French law and abiding by the rules of distribution of free software.
 #  You can  use, modify and or redistribute the software under the terms of
 #  the CeCILL or CeCILL-C licenses as circulated by CEA, CNRS and INRIA
 #  at the following URL: "http://www.cecill.info".
 #
 #  As a counterpart to the access to the source code and  rights to copy,
 #  modify and redistribute granted by the license, users are provided only
 #  with a limited warranty  and the software's author,  the holder of the
 #  economic rights,  and the successive licensors  have only  limited
 #  liability.
 #
 #  In this respect, the user's attention is drawn to the risks associated
 #  with loading,  using,  modifying and/or developing or reproducing the
 #  software by the user in light of its specific status of free software,
 #  that may mean  that it is complicated to manipulate,  and  that  also
 #  therefore means  that it is reserved for developers  and  experienced
 #  professionals having in-depth computer knowledge. Users are therefore
 #  encouraged to load and test the software's suitability as regards their
 #  requirements in conditions enabling the security of their systems and/or
 #  data to be ensured and,  more generally, to use and operate it in the
 #  same conditions as regards security.
 #
 #  The fact that you are presently reading this means that you have had
 #  knowledge of the CeCILL and CeCILL-C licenses and that you accept its terms.
 #
*/

#ifdef _WIN32
#pragma warning (disable:4996)
#endif
#pragma once
#ifndef _RFX_FILEUTILS_H
#define _RFX_FILEUTILS_H

#include <string>
#include <iostream>
#include <fstream>

#include "RFX_StringUtils.h"

using namespace std;

namespace reduxfx {

static bool fileExists(const string inFilename)
{
    FILE *fileP;
#ifndef _WIN32
	fileP = fopen(inFilename.c_str(), "r");
#else
	fopen_s(&fileP, inFilename.c_str(), "r");
#endif
	if (fileP == NULL) return false;
	fclose(fileP);
	return true;
}

static int loadBufferFromFile(const string filename, unsigned char** bufferP, unsigned int& bufferSize, const bool piggybackMode = false)
{
	bufferSize = 0;
	*bufferP = NULL;
	if (filename == "") return -1;
	ifstream infile;
    infile.open(filename.c_str(), ios::in | ios::binary | ios::ate);
    if (infile.is_open()) {
		if (piggybackMode) {
			infile.seekg(0, ios::end);
			unsigned int flen = (unsigned int)infile.tellg();
			int ofs = (int)flen - sizeof(int);
			infile.seekg(ofs, ios::beg);
			infile.read((char*)(&bufferSize), sizeof(int));
			ofs = (int)flen - (int)bufferSize - sizeof(int);
			if (ofs < 0 || bufferSize == 0) {
				infile.close();
				return -1;
			}
	        infile.seekg(ofs, ios::beg);
		} else {
			bufferSize = (unsigned int)infile.tellg();
	        infile.seekg(0, ios::beg);
		}
        *bufferP = new unsigned char[bufferSize];
        infile.read((char*)*bufferP, bufferSize);
		if (!infile) bufferSize = (unsigned int)infile.gcount();
        
		infile.close();
		return 0;
    }
    return -1;
}

static string loadStringFromFile(const string filename, const bool loadOnlyText = false)
{
    string res;
	if (filename == "") return res;
	ifstream infile;
    infile.open(filename.c_str(), ios::in | ios::binary | ios::ate);
    if (infile.is_open()) {
        int size = (int)infile.tellg();
        char* bufferP = new char[size];
        infile.seekg (0, ios::beg);
        infile.read(bufferP, size);
		if (!infile) size = (int)infile.gcount();
        infile.close();

		if (!loadOnlyText) {
			res = string(reinterpret_cast<const char*>(bufferP), size);
		} else {
			for (int i = 0; i < size; i++) {
				if ((unsigned char)bufferP[i] >= 13 && (unsigned char)bufferP[i] <= 127)
					res += bufferP[i];
			}
		}
		delete[] bufferP;
    }
    return res;
}

static int saveStringToFile(string s, const string filename, const bool unifyLineEndings = true)
{
    ofstream myfile(filename.c_str(), ios::out | ios::binary);
    if (myfile.is_open()) {
		if (unifyLineEndings) {
			s = strReplace(s, "\r\n", "\n");
			s = strReplace(s, "\r", "\n");
			s = strReplace(s, "\n", "\r\n");
		}
        myfile.write(s.c_str(), s.size());
        myfile.close();
	    return 0;
    }
	return -1;
}

static int saveBufferToFile(const unsigned char** bufferP, const unsigned int bufferSize, const string filename, const bool piggybackMode = false)
{
	ofstream outfile;
	if (piggybackMode) {
		outfile.open(filename.c_str(), ios::out | ios::binary | ios::app);
	} else {
		outfile.open(filename.c_str(), ios::out | ios::binary);
	}
    if (outfile.is_open()) {
        outfile.write((char*)(*bufferP), bufferSize);
		if (piggybackMode) outfile.write((char*)&bufferSize, sizeof(int));
        outfile.close();			
		return 0;
    }
	return -1;
}

};
#endif
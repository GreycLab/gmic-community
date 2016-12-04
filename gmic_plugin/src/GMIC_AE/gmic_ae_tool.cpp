/*
 #
 #  File        : gmic_ae_tool.cpp
 #
 #  Description : The sources for a tool that creates effect plugins 
 #                for Adobe After Effects from a binary template file
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


#include "../../Helpers/gmic_parser.h"
using namespace std;

#ifdef _WIN32
#include <direct.h>
#include <Windows.h>
#include <conio.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#define _mkdir mkdir
#endif

#define PIPL
#define AE_PLUGIN
#include "../gmic_plugin.cpp"
#undef PIPL

unsigned int replacebin(unsigned char* p, long length, string s1, string s2, bool addNull = true, bool addLength = true)
{
	unsigned int r = 0;
	for (unsigned int i = 0; i < length - s1.length(); i++) {
		bool bad = false;
		for (unsigned int j = 0; j < s1.length(); j++) {
			if ((unsigned char)p[i + j] != (unsigned char)s1[j]) { bad = true; break; }
		}
		if (!bad) {
			r++;
			for (unsigned int j = 0; j < s2.length(); j++) p[i + j] = s2[j];
			if (addNull) p[i + s2.length()] = 0;
			if (addLength && i > (unsigned int)length / 2) //set PIPL length
				p[i - 1] = min((int)s2.length(), 255);
		}
	}
	return r;
}

void patchbin(string pf, string pfout, const EffectData& ed)
{
	unsigned char* p = NULL;
	int len = 0;
	loadBufferFromFile(pf, &p, len);
	replacebin(p, len, PLUGIN_NAME, ed.name);
	replacebin(p, len, PLUGIN_CATEGORY, ed.category);
	replacebin(p, len, PLUGIN_UNIQUEID, ed.uniqueId);
	saveBufferToFile(&p, len, pfout);
	delete[] p;
}

void patchtxt(string pf, string pfout, const EffectData& ed)
{
	long len = 0;
	string l = loadStringFromFile(pf);
	strReplace(l, PLUGIN_NAME, ed.name);
	strReplace(l, PLUGIN_CATEGORY, ed.category);
	strReplace(l, PLUGIN_UNIQUEID, ed.uniqueId);
	saveStringToFile(l, pfout);
}

static bool skip_msg = false;

int build(const string infile)
{
	EffectData ed;
	string data = loadStringFromFile(infile);
	gmic_parse_single(data, ed);
	ed.category = "G'MIC " + ed.category;
	strReplace(ed.category, "[", "");
	strReplace(ed.category, "]", "");
	strReplace(ed.category, " - ", " ");
	ed.category = ed.category.substr(0, 31);
	ed.name = "G'MIC " + ed.name;
	strReplace(ed.name, "[", "");
	strReplace(ed.name, "]", "");
	strReplace(ed.name, " - ", " ");
	ed.name = ed.name.substr(0, 31);
	ed.uniqueId = ed.uniqueId.substr(0, 31);
	string filename = infile;
	strReplace(filename, ".gmic", "");

	string filenameWin = master_name + ".aex";
	if (!fileExists(filenameWin)) {
		if (!skip_msg) cout << "error: could not open master binary file for Windows '" << filenameWin << "', skipping creation of Windows plugins..." << endl;
	} else {
		string dst = filename + ".aex";
		patchbin(filenameWin, dst, ed);
	}

	string filenameMac = master_name + ".plugin/Contents/Info.plist";
	if (!fileExists(filenameMac)) {
		if (!skip_msg) cout << "error: could not open master binary file for MacOS '" << filenameMac << "', skipping creation of MacOS plugins..." << endl;
	} else {
		string src_dir = master_name + ".plugin";
		string dst_dir = filename + ".plugin";
		_mkdir(dst_dir.c_str());
		_mkdir(string(dst_dir + "/Contents").c_str());
		_mkdir(string(dst_dir + "/Contents/MacOS").c_str());
		_mkdir(string(dst_dir + "/Contents/Resources").c_str());
		patchtxt(src_dir + "/Contents/PkgInfo", dst_dir + "/Contents/PkgInfo", ed);
		patchtxt(src_dir + "/Contents/Info.plist", dst_dir + "/Contents/Info.plist", ed);
		patchbin(src_dir + "/Contents/Resources/" + master_name + ".rsrc", dst_dir + "/Contents/Resources/" + filename + ".rsrc", ed);
		patchbin(src_dir + "/Contents/MacOS/" + master_name, dst_dir + "/Contents/MacOS/" + filename, ed);
	}
	skip_msg = true;
	return 0;
}

int extract(string infile, bool build_file = false)
{
	string content = loadStringFromFile(infile);
	if (content == "") {
		cout << "error: input file '" << infile << "' not found or empty, exiting" << endl;
		return -1;
	}
//    EffectData cd; string ss = gmic_parse_single(content, cd);

	vector<EffectData> cds;
	vector<string> lines;
	gmic_parse_multi(content, &cds, &lines);
	for (int i = 0; i < cds.size(); i++)
	{
		string fn = cds[i].name + ".gmic";
		cout << "creating effect '" << fn << "'" << endl;
		{
		ofstream outf(fn);
		outf << lines[i];
		}
		if (build_file) {
			build(fn);
		}
	}
	cout << endl << ">>>> " << cds.size() << " effects created" << endl;
	return 0;
}

int main(int argc, char* argv[])
{
	if (argc != 3) {
		cout << "usage: gmic_ae_tool {x|b|xb} input_file\n\nuse 'x' for extracting all commands usable in AE from the standard G'MIC library (given in input_file) into separate G'MIC files\n";
		cout << "\nuse 'b' for building an AE binary plugin from a specific G'MIC file (given in input_file) with a single effect\n";
		cout << "\nuse 'xb' for extracting all suitable commands and building them in one step\n";
		return -1;
	}
	if (string(argv[1]) == "x") {
		extract(string(argv[2]), false);
	} else if (string(argv[1]) == "xb") {
		extract(string(argv[2]), true);
	} else if (string(argv[1]) == "b") {
		build(string(argv[2]));
	}
	return 0;
}


/*
 #
 #  File        : gmic_parser.h
 #
 #  Description : A self-contained header file with helper functions to
 #                parse the G'MIC standard library file into a param structure
 #
 #  Copyright   : Tobias Fleischer / reduxFX Productions (http://www.reduxfx.com)
 #
 #  Licenses        : This file is 'dual-licensed', you have to choose one
 #                    of the two licenses below to apply.
 #
 #                    CeCILL-C
 #                    The CeCILL-C license is close to the GNU LGPL.
 #                    ( http://cecill.info/licences/Licence_CeCILL-C_V1-en.html )
 #
 #                or  CeCILL v2.0
 #                    The CeCILL license is compatible with the GNU GPL.
 #                    ( http://cecill.info/licences/Licence_CeCILL_V2-en.html )
 #
 #  This software is governed either by the CeCILL or the CeCILL-C license
 #  under French law and abiding by the rules of distribution of free software.
 #  You can  use, modify and or redistribute the software under the terms of
 #  the CeCILL or CeCILL-C licenses as circulated by CEA, CNRS and INRIA
 #  at the following URL: "http://cecill.info".
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


#ifndef _GMIC_PARSER_H
#define _GMIC_PARSER_H

#include <string>
#include <iostream>
#include <fstream>

#include "RFX_StringUtils.h"
using namespace std;
using namespace reduxfx;

const string src_prefix_old = "#@gimp";
const string src_prefix = "#@gui";
const string dst_prefix = "#@gmic_plugin";
const string master_name = "gmic_ae";

struct EffectParameter {
	string name;
	string minValue;
	string maxValue;
	string defaultValue;
	string text;
	string paramType;
};

struct EffectData {
	string category;
	string name;
	string uniqueId;
	string command;
	string preview_command;
	string notes;
	bool multiLayer;
	vector<EffectParameter> param;
};

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

static int loadBufferFromFile(const string filename, unsigned char** bufferP, int& bufferSize)
{
	if (filename == "") return -1;
	ifstream infile;
    infile.open(filename.c_str(), ios::in | ios::binary | ios::ate);
    if (infile.is_open()) {
        bufferSize = (int)infile.tellg();
        *bufferP = new unsigned char[bufferSize];
        infile.seekg (0, ios::beg);
        infile.read((char*)*bufferP, bufferSize);
		if (!infile) bufferSize = (int)infile.gcount();
        infile.close();
		return 0;
    }
    return -1;
}

static int saveBufferToFile(unsigned char** bufferP, const int bufferSize, const string filename)
{
    ofstream myfile(filename.c_str(), ios::out | ios::binary);
    if (myfile.is_open()) {
        myfile.write((char*)(*bufferP), bufferSize);
        myfile.close();
	    return 0;
    }
	return -1;
}

static string loadStringFromFile(const string filename)
{
    string res;
	if (filename == "") return res;
	ifstream infile;
    infile.open(filename.c_str(), ios::in | ios::binary | ios::ate);
    if (infile.is_open()) {
        int size = (int)infile.tellg();
        char* bufferP = new char[size+1];
        infile.seekg (0, ios::beg);
        infile.read(bufferP, size);
		if (!infile) size = (int)infile.gcount();
        infile.close();
		bufferP[size] = 0;
		res = string(reinterpret_cast<const char*>(bufferP), size+1);
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

string getUniqueId(string name)
{
	string uniqueid = "";
	for (unsigned int i = 0; i < name.size(); i++) {
		if ((name[i] >= 'a' && name[i] <= 'z')
			|| (name[i] >= 'A' && name[i] <= 'Z')
			|| (name[i] >= '0' && name[i] <= '9'))
			uniqueid += name[i];
	}
	return "gmic_" + strLowercase(uniqueid);
}

void processCommand(const string s, EffectData& cd)
{
	string r = s;
	if (r == dst_prefix + " :") return;
	r = strRemoveXmlTags(r, false);
	int sPos = (int)r.find(":");
	if (sPos < 0) return;
	string r1 = r.substr(0, sPos - 1);
	int sPos2 = (int)r1.find(dst_prefix);
	if (sPos2 >= 0) cd.name = strTrim(r1.substr(sPos2 + dst_prefix.size()), " \n");

	string r2 = r.substr(sPos + 1);
	string r3 = r2;
	sPos = (int)r2.find(",");
	if (sPos >= 0) {
		r3 = r2.substr(sPos + 1);
		r2 = r2.substr(1, sPos - 1);
	}
	strReplace(r3, "(0)", "");
	strReplace(r3, "(1)", "");
	strReplace(r3, "(2)", "");
	strReplace(r3, "+", "");

	sPos = (int)r2.find("_none_");
	if (sPos >= 0) r2 = r3;
	sPos = (int)r3.find("_none_");
	if (sPos >= 0) r3 = r2;

	cd.command = strTrim(r2, " \n");
	cd.preview_command = strTrim(r3, " \n");
	if (cd.preview_command == "") cd.preview_command = cd.command;
}

void processNote(const string s, EffectData& cd)
{
	string r = s;
	// r = replaceHtml(r);
	strReplace(r, "note(0,", "note(");
	string n = strLowercase(r);
	int p1 = (int)n.find("note(");
	if (p1 >= 0) {
		r = r.substr(p1 + 4);
		p1 = (int)r.find_last_of(")]}");
		if (p1 > 0) {
			r = r.substr(0, p1 - 1);
		}
	}
	strReplace(r, "\",\"", ": ");
	strReplace(r, "\")", "");
	strReplace(r, "(\"", "");
	strReplace(r, "\"", "");
	strReplace(r, "}", "");
	strReplace(r, "]", "");
	strReplace(r, "\\n", "");
	strReplace(r, ": : ", ": ");
	strReplace(r, dst_prefix + " : ", "");
	if (r != "") cd.notes += r + "\n";
}

void processParam(const string s, EffectParameter& cp)
{
	string r = s;
	cp.minValue = "";
	cp.maxValue = "";
	cp.defaultValue = "";
	cp.text = "";
	int p1 = (int)r.find(":");
	int p2 = (int)r.find("=");
	if (p2 < 0) return;
	cp.name = strTrim(r.substr(p1 + 1, p2 - p1 - 2));
	r = strTrim(r.substr(p2 + 1));
	p1 = (int)r.find_first_of("([{");
	if (p1 < 0) return;
	cp.paramType = strTrim(r.substr(0, p1));
	strReplace(cp.paramType, "_", "");
	cp.paramType = strLowercase(cp.paramType);
	string pval = strTrim(r.substr(p1 + 1));
	pval = pval.substr(0, pval.size() - 1);
	strLowercase(pval);
	strReplace(pval, "true", "1");
	strReplace(pval, "false", "0");

	if (cp.paramType == "bool") {
		cp.defaultValue = pval;
		cp.minValue = "0";
		cp.maxValue = "1";
	} else if (cp.paramType == "file") {
//		cp.paramType = "text";
		cp.text = strTrim(pval, "\"");
		if (cp.text == "") cp.text = "test.txt";
		cp.defaultValue = cp.text;
	} else if (cp.paramType == "folder") {
//		cp.paramType = "text";
		cp.text = strTrim(pval, "\"");
		if (cp.text == "") cp.text = "./";
		cp.defaultValue = cp.text;
	} else if (cp.paramType == "button") {
		cp.paramType = "bool";
		cp.minValue = "0";
		cp.maxValue = "1";
		cp.defaultValue = "0";
	} else if (cp.paramType == "text") { // || cp.paramType == "flags") {
		p1 = (int)pval.find(",");
		p2 = (int)pval.find("\"");
		if (p1 >= 0 && p1 < p2) {
			cp.maxValue = pval.substr(0, p1);
			pval = pval.substr(p1 + 1);
		} else {
			cp.maxValue = "0";
		}
		cp.text = strTrim(pval, "\"");
		cp.defaultValue = cp.text;
	} else if (cp.paramType == "color") {
		cp.defaultValue = pval;
		strReplace(cp.defaultValue, ",", "|");
	} else if (cp.paramType == "int" || cp.paramType == "float") {
		p1 = (int)pval.find(",");
		p2 = (int)pval.rfind(",");
		if (p1 == p2) {
			cp.minValue = pval.substr(0, p1);
			cp.maxValue = pval.substr(p1);
			cp.defaultValue = cp.minValue;
		} else {
			cp.defaultValue = pval.substr(0, p1);
			cp.maxValue = pval.substr(p2 + 1);
			cp.minValue = pval.substr(p1 + 1, p2 - p1 - 1);
		}
	} else if (cp.paramType == "input") {
		cp.defaultValue = strTrim(pval, "\"");
	} else if (cp.paramType == "choice") {
		p1 = (int)pval.find(",");
		p2 = (int)pval.find("\"");
		if (p1 < p2) {
			cp.defaultValue = pval.substr(0, p1);
			cp.text = pval.substr(p1 + 1);
		} else {
			cp.defaultValue = "0";
			cp.text = pval;
		}
		vector<string> c;
		strSplit(cp.text, ',', c);
		cp.text = "";
		for (int i = 0; i < (int)c.size() - 1; i++) {
			cp.text += strTrim(c[i]) + "|";
		}
		cp.text += strTrim(c[(int)c.size() - 1]);
		strReplace(cp.text, "\"", "");
		cp.minValue = "0";
		cp.maxValue = intToString((int)c.size() - 1);
	}
}

string gmic_parse_single(const string content, EffectData& cd)
{
	string result;
	bool inNote = false;
	bool inChoice = false;
	cd.name = "";
	cd.command = "";
	cd.preview_command = "";
	cd.notes = "";
	cd.param.clear();

	vector<string> lines;
	strSplit(content, '\n', lines);
	for (int i = 0; i < (int)lines.size(); i++) {
		string line = strTrim(lines[i], " \r\n\t");
		if (line.size() > 0 && line[0] != '#') result += line + "\n";
		strReplace(line, src_prefix_old, dst_prefix);
		strReplace(line, src_prefix, dst_prefix);
		string n = strTrim(line, " \r\n\t");
		int sPos = (int)line.find(":");
		int sPos2 = (int)line.find("#");
		if (sPos >= 0 && sPos2 == 0) {
			if (line.substr(0, dst_prefix.size() + 3) != dst_prefix + " : ") {
				processCommand(line, cd);
			} else {
				n = strLowercase(n);
				if (inNote) {
					processNote(line, cd);
					if (n != "" && (n[n.size() - 1] == ')' || n[n.size() - 1] == ']' || n[n.size() - 1] == '}')) {
						inNote = false;
					}
				} else {
					strReplace(n, "note{", "note(");
					strReplace(n, "note[", "note(");
					strReplace(n, "link(", "note(");
					strReplace(n, "link{", "note(");
					strReplace(n, "link[", "note(");
					sPos = (int)n.find("note(");
					if (sPos >= 0 || inNote) {
						if (n != "" &&
							(n[n.size() - 1] != ')' && n[n.size() - 1] != ']' && n[n.size() - 1] != '}')
							) inNote = true;
						if (sPos >= 0) n = n.substr(sPos + 5);
						processNote(n, cd);
					} else {
						if (inChoice) {
							string p = line;
							strReplace(p, dst_prefix + " : ", "");
							cd.param[cd.param.size() - 1].name += p;
							line = strTrim(line);
							if (n[n.size() - 1] == ')' || n[n.size() - 1] == ']' || n[n.size() - 1] == '}') {
								inChoice = false;
							}
						} else if (line != "" && line != dst_prefix + " : ") {
							EffectParameter p;
							p.name = line;
							sPos = (int)line.find("eparator");
							if (sPos > 0) {
								p.name = line.substr(sPos);
								sPos = (int)p.name.find(")");
								p.name = p.name.substr(sPos + 1);
								p.name = strTrim(p.name, ", ");
							}
							if ((int)p.name.find("(") > 0 || (int)p.name.find("[") > 0 || (int)p.name.find("{") > 0) {
								cd.param.push_back(p);
							}
						}

						if ( (int)n.find("choice(") >= 0 || (int)n.find("choice{") >= 0 || (int)n.find("choice[") >= 0 ) {
							if (n[n.size() - 1] != ')' && n[n.size() - 1] != ']' && n[n.size() - 1] != '}') {
								inChoice = true;
							}
						}
					}
				}
			}
		} else if (sPos2 == 0) {
			sPos = (int)n.find(" ");
			if (sPos >= 0) {
				n = n.substr(sPos);
				n = strRemoveXmlTags(n, false);
				strReplace(n, " & ", " and ");
				n = strTrim(n, " \r\n\t_");
				if (n != "") {
					cd.category = n;
				}
			}
		}
	}
	for (int i = 0; i < (int)cd.param.size(); i++) {
		processParam(cd.param[i].name, cd.param[i]);
		bool ok = false;
		int cnt = 2;
		string t = cd.param[i].name;
		while (!ok) {
			ok = true;
			for (int j = 0; j < i; j++) {
				if (cd.param[j].name == cd.param[i].name) {
					cd.param[i].name = t + "_" + intToString(cnt++);
					ok = false;
					break;
				}
			}
		}
	}
	if ((int)content.find(" layers") > 0)
		cd.multiLayer = true;
	else
		cd.multiLayer = false;
	cd.uniqueId = getUniqueId(cd.name);
	cd.notes = strTrim(cd.notes, "\n");

#ifdef OFX_PLUGIN
	strReplace(cd.name, "&amp;", "&&");
	strReplace(cd.category, "&amp;", "&&");
	strReplace(cd.notes, "&amp;", "&&");
#else
	strReplace(cd.name, "&amp;", "&");
	strReplace(cd.category, "&amp;", "&");
	strReplace(cd.notes, "&amp;", "&");
#endif
	return result;
}

void gmic_parse_multi(const string content, vector<EffectData>* cds, vector<string>* lines)
{
	stringstream ss(content);
	bool inEffect = false;
	string line, line2, cat;
	EffectData cd;
	int l = 0;
	while (getline(ss, line)) {
		if ( (line.substr(0, src_prefix.size() + 1) == src_prefix + " ") ||
             (line.substr(0, src_prefix_old.size() + 1) == src_prefix_old + " ") ) {
			if (line != "") line2 += line + "\n";
			l++;
			inEffect = true;
		} else if (strTrim(line).substr(0, 1) != "#") {
			if (inEffect) {
				if (line2 != "") {
					if (l == 1) {
						if ( (line2 != src_prefix + " _\n") && (line2 != src_prefix_old + " _\n") ) cat = line2;
					} else {
						line2 = cat + line2;
						strReplace(line2, src_prefix, dst_prefix);
						strReplace(line2, src_prefix_old, dst_prefix);
                        gmic_parse_single(line2, cd);
					}

					bool doOutput = true;
					// skip entries from the about category
					if ((int)strLowercase(cd.category).find("about") >= 0) {
						doOutput = false;
					} else if ((int)strLowercase(cd.category).find("various") >= 0) {
						doOutput = false;
					} else if ((int)strLowercase(line2).find("[interactive]") >= 0) {
						doOutput = false;
					} else if ((int)strLowercase(line2).find("[animated]") >= 0) {
						doOutput = false;
					}
					if (doOutput && cd.name != "" && l > 1) {
						cd.name = "G'MIC " + cd.name;
						strReplace(cd.name, "[", "");
						strReplace(cd.name, "]", "");
						strReplace(cd.name, " - ", " ");
						strReplace(cd.name, "inverse", "inv.");
						//cd.category = "G'MIC " + cd.category;
cd.category = "GMIC/" + cd.category;
						if (cds) cds->push_back(cd);
						if (lines) lines->push_back(line2);
					}

					line2 = "";
					l = 0;
				}
				inEffect = false;
			}
		}
	}
}


#endif

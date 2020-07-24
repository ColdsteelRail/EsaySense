/**
* @file
* @brief initialization file read and write API
* @author Deng Yangjun
* @date 2007-12-9
* @version 0.2
*  (C)2007 Midapex
* This program is free software; you can redistribute it and/or modify it
*  under the terms of the GNU Library General Public License as published
*  by the Free Software Foundation; either version 2 of the License,
*  or (at your option) any later version.
*/
#ifndef INI_FILE_CPP_H_
#define INI_FILE_CPP_H_

#include <string>
#include <stdlib.h>
using namespace std;


class  IniFile
{
public:
	IniFile(const string & fileName);
public:
	virtual ~IniFile(void);
	
	const string & getFileName() const;

	const string &getSection() const;
	void setSection(const string &section);
	
	bool write(const string &key, const string & value) const ;
	bool write(const string &key, int value) const ;

	string readStr(const string &key,const string &default_value) const;
	int readInt(const string &key, int default_value) const;

	/**add**/
	string readStrEnv(const string &key, const string &default_value) const;
	int readIntEnv(const string &key, int default_value) const;
	/**add**/

public:
	static int read_profile_string( const char *section, const char *key,const char *default_value,char *value, 
		int size, const char *file);
	static int read_profile_int( const char *section, const char *key,int default_value, 
		const char *file);
	static int write_profile_string(const char *section, const char *key,
		const char *value, const char *file);
private:
	string m_fileName;
	string m_section;
};

#endif


#ifndef BOARDKEY_H
#define BOARDKEY_H

class BoardKey
{
public:
	__readonly map<string, int> codeFromName;
	__readonly map<int, string> nameFromCode;
	BoardKey();
};

#endif
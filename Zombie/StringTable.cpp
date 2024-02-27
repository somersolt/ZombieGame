#include "pch.h"
#include "StringTable.h"
#include "rapidcsv.h"

StringTable::StringTable(Types t) : DataTable(t)
{
}

StringTable::~StringTable()
{
}

const std::string& StringTable::Get(const std::string& id)
{
	auto find = table.find(id);
	if (find == table.end())
		return "Undefined ID";
	return find->second;
}

bool StringTable::Load()
{
	return Load(currLang);
}

bool StringTable::Load(Languages language)
{
	static std::vector<std::string> filePathArray = 
	{"tables/StringTable_KR.csv",
		"tables/StringTable_EN.csv"
		};

	currLang = language;

	table.clear();

	rapidcsv::Document doc(filePathArray[(int)language],
		rapidcsv::LabelParams(0, -1));

	for (int i = 0; i < doc.GetRowCount(); ++i)
	{
		std::vector<std::string> pair = doc.GetRow<std::string>(i);
		table.insert({ pair[0], pair[1] });
	}
	return true;
}


void StringTable::Release()
{
	table.clear();
}
